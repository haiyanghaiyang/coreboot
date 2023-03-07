/* SPDX-License-Identifier: GPL-2.0-only */

/* TODO: Check if this is still correct */

/* ACPI - create the Fixed ACPI Description Tables (FADT) */

#include <acpi/acpi.h>
#include <acpi/acpigen.h>
#include <amdblocks/acpi.h>
#include <amdblocks/cppc.h>
#include <amdblocks/cpu.h>
#include <amdblocks/acpimmio.h>
#include <amdblocks/ioapic.h>
#include <arch/ioapic.h>
#include <arch/smp/mpspec.h>
#include <console/console.h>
#include <cpu/amd/cpuid.h>
#include <cpu/amd/msr.h>
#include <cpu/x86/smm.h>
#include <soc/acpi.h>
#include <soc/iomap.h>
#include <soc/msr.h>
#include <types.h>
#include "chip.h"

unsigned long acpi_fill_madt(unsigned long current)
{
	/* create all subtables for processors */
	current = acpi_create_madt_lapics_with_nmis(current);

	current += acpi_create_madt_ioapic_from_hw((acpi_madt_ioapic_t *)current, IO_APIC_ADDR);

	current += acpi_create_madt_ioapic_from_hw((acpi_madt_ioapic_t *)current,
						   GNB_IO_APIC_ADDR);

	/* PIT is connected to legacy IRQ 0, but IOAPIC GSI 2 */
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)current,
		MP_BUS_ISA, 0, 2,
		MP_IRQ_TRIGGER_DEFAULT | MP_IRQ_POLARITY_DEFAULT);
	/* SCI IRQ type override */
	current += acpi_create_madt_irqoverride((acpi_madt_irqoverride_t *)current,
		MP_BUS_ISA, ACPI_SCI_IRQ, ACPI_SCI_IRQ,
		MP_IRQ_TRIGGER_LEVEL | MP_IRQ_POLARITY_LOW);
	current = acpi_fill_madt_irqoverride(current);

	return current;
}

/*
 * Reference section 5.2.9 Fixed ACPI Description Table (FADT)
 * in the ACPI 3.0b specification.
 */
void acpi_fill_fadt(acpi_fadt_t *fadt)
{
	const struct soc_amd_mendocino_config *cfg = config_of_soc();

	printk(BIOS_DEBUG, "pm_base: 0x%04x\n", ACPI_IO_BASE);

	fadt->sci_int = ACPI_SCI_IRQ;

	if (permanent_smi_handler()) {
		fadt->smi_cmd = APM_CNT;
		fadt->acpi_enable = APM_CNT_ACPI_ENABLE;
		fadt->acpi_disable = APM_CNT_ACPI_DISABLE;
	}

	fadt->pm1a_evt_blk = ACPI_PM_EVT_BLK;
	fadt->pm1a_cnt_blk = ACPI_PM1_CNT_BLK;
	fadt->pm_tmr_blk = ACPI_PM_TMR_BLK;
	fadt->gpe0_blk = ACPI_GPE0_BLK;

	fadt->pm1_evt_len = 4;	/* 32 bits */
	fadt->pm1_cnt_len = 2;	/* 16 bits */
	fadt->pm_tmr_len = 4;	/* 32 bits */
	fadt->gpe0_blk_len = 8;	/* 64 bits */

	fill_fadt_extended_pm_regs(fadt);

	/* p_lvl2_lat and p_lvl3_lat match what the AGESA code does, but those values are
	   overridden by the _CST packages in the processor devices. */
	fadt->p_lvl2_lat = ACPI_FADT_C2_NOT_SUPPORTED;
	fadt->p_lvl3_lat = ACPI_FADT_C3_NOT_SUPPORTED;
	fadt->day_alrm = RTC_DATE_ALARM;
	fadt->century = RTC_ALT_CENTURY;
	fadt->iapc_boot_arch = cfg->common_config.fadt_boot_arch; /* legacy free default */
	fadt->flags |=	ACPI_FADT_WBINVD | /* See table 5-34 ACPI 6.3 spec */
			ACPI_FADT_C1_SUPPORTED |
			ACPI_FADT_S4_RTC_WAKE |
			ACPI_FADT_32BIT_TIMER |
			ACPI_FADT_PCI_EXPRESS_WAKE |
			ACPI_FADT_PLATFORM_CLOCK |
			ACPI_FADT_S4_RTC_VALID |
			ACPI_FADT_REMOTE_POWER_ON;
	if (cfg->s0ix_enable)
		fadt->flags |= ACPI_FADT_LOW_PWR_IDLE_S0;

	fadt->flags |= cfg->common_config.fadt_flags; /* additional board-specific flags */
}

static uint32_t get_pstate_core_freq(msr_t pstate_def)
{
	uint32_t core_freq, core_freq_mul, core_freq_div;
	bool valid_freq_divisor;

	/* Core frequency multiplier */
	core_freq_mul = pstate_def.lo & PSTATE_DEF_LO_FREQ_MUL_MASK;

	/* Core frequency divisor ID */
	core_freq_div =
		(pstate_def.lo & PSTATE_DEF_LO_FREQ_DIV_MASK) >> PSTATE_DEF_LO_FREQ_DIV_SHIFT;

	if (core_freq_div == 0) {
		return 0;
	} else if ((core_freq_div >= PSTATE_DEF_LO_FREQ_DIV_MIN)
		   && (core_freq_div <= PSTATE_DEF_LO_EIGHTH_STEP_MAX)) {
		/* Allow 1/8 integer steps for this range */
		valid_freq_divisor = 1;
	} else if ((core_freq_div > PSTATE_DEF_LO_EIGHTH_STEP_MAX)
		   && (core_freq_div <= PSTATE_DEF_LO_FREQ_DIV_MAX) && !(core_freq_div & 0x1)) {
		/* Only allow 1/4 integer steps for this range */
		valid_freq_divisor = 1;
	} else {
		valid_freq_divisor = 0;
	}

	if (valid_freq_divisor) {
		/* 25 * core_freq_mul / (core_freq_div / 8) */
		core_freq =
			((PSTATE_DEF_LO_CORE_FREQ_BASE * core_freq_mul * 8) / (core_freq_div));
	} else {
		printk(BIOS_WARNING, "Undefined core_freq_div %x used. Force to 1.\n",
		       core_freq_div);
		core_freq = (PSTATE_DEF_LO_CORE_FREQ_BASE * core_freq_mul);
	}
	return core_freq;
}

static uint32_t get_pstate_core_power(msr_t pstate_def)
{
	uint32_t voltage_in_uvolts, core_vid, current_value_amps, current_divisor, power_in_mw;

	/* Core voltage ID */
	core_vid =
		(pstate_def.lo & PSTATE_DEF_LO_CORE_VID_MASK) >> PSTATE_DEF_LO_CORE_VID_SHIFT;

	/* Current value in amps */
	current_value_amps =
		(pstate_def.lo & PSTATE_DEF_LO_CUR_VAL_MASK) >> PSTATE_DEF_LO_CUR_VAL_SHIFT;

	/* Current divisor */
	current_divisor =
		(pstate_def.lo & PSTATE_DEF_LO_CUR_DIV_MASK) >> PSTATE_DEF_LO_CUR_DIV_SHIFT;

	/* Voltage */
	if (core_vid == 0x00) {
		/* Voltage off for VID code 0x00 */
		voltage_in_uvolts = 0;
	} else {
		voltage_in_uvolts =
			SERIAL_VID_BASE_MICROVOLTS + (SERIAL_VID_DECODE_MICROVOLTS * core_vid);
	}

	/* Power in mW */
	power_in_mw = (voltage_in_uvolts) / 10 * current_value_amps;

	switch (current_divisor) {
	case 0:
		power_in_mw = power_in_mw / 100L;
		break;
	case 1:
		power_in_mw = power_in_mw / 1000L;
		break;
	case 2:
		power_in_mw = power_in_mw / 10000L;
		break;
	case 3:
		/* current_divisor is set to an undefined value.*/
		printk(BIOS_WARNING, "Undefined current_divisor set for enabled P-state .\n");
		power_in_mw = 0;
		break;
	}

	return power_in_mw;
}

/*
 * Populate structure describing enabled p-states and return count of enabled p-states.
 */
size_t get_pstate_info(struct acpi_sw_pstate *pstate_values,
		       struct acpi_xpss_sw_pstate *pstate_xpss_values)
{
	msr_t pstate_def;
	size_t pstate_count, pstate;
	uint32_t pstate_enable, max_pstate;

	pstate_count = 0;
	max_pstate = (rdmsr(PS_LIM_REG).lo & PS_LIM_MAX_VAL_MASK) >> PS_MAX_VAL_SHFT;

	for (pstate = 0; pstate <= max_pstate; pstate++) {
		pstate_def = rdmsr(PSTATE_MSR(pstate));

		pstate_enable = (pstate_def.hi & PSTATE_DEF_HI_ENABLE_MASK)
				>> PSTATE_DEF_HI_ENABLE_SHIFT;
		if (!pstate_enable)
			continue;

		pstate_values[pstate_count].core_freq = get_pstate_core_freq(pstate_def);
		pstate_values[pstate_count].power = get_pstate_core_power(pstate_def);
		pstate_values[pstate_count].transition_latency = 0;
		pstate_values[pstate_count].bus_master_latency = 0;
		pstate_values[pstate_count].control_value = pstate;
		pstate_values[pstate_count].status_value = pstate;

		pstate_xpss_values[pstate_count].core_freq =
			(uint64_t)pstate_values[pstate_count].core_freq;
		pstate_xpss_values[pstate_count].power =
			(uint64_t)pstate_values[pstate_count].power;
		pstate_xpss_values[pstate_count].transition_latency = 0;
		pstate_xpss_values[pstate_count].bus_master_latency = 0;
		pstate_xpss_values[pstate_count].control_value = (uint64_t)pstate;
		pstate_xpss_values[pstate_count].status_value = (uint64_t)pstate;
		pstate_count++;
	}

	return pstate_count;
}

const acpi_cstate_t cstate_cfg_table[] = {
	[0] = {
		.ctype = 1,
		.latency = 1,
		.power = 0,
	},
	[1] = {
		.ctype = 2,
		.latency = 0x12,
		.power = 0,
	},
	[2] = {
		.ctype = 3,
		.latency = 350,
		.power = 0,
	},
};

const acpi_cstate_t *get_cstate_config_data(size_t *size)
{
	*size = ARRAY_SIZE(cstate_cfg_table);
	return cstate_cfg_table;
}
