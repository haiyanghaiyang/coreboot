/*
 * This file is part of the coreboot project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * These are the qemu firmware config interface defines and structs.
 * Copied over from qemu soure tree,
 * include/standard-headers/linux/qemu_fw_cfg.h and modified accordingly.
 */
#ifndef FW_CFG_IF_H
#define FW_CFG_IF_H

#include <stdint.h>

enum fw_cfg_enum {
	FW_CFG_SIGNATURE,
	FW_CFG_ID,
	FW_CFG_UUID,
	FW_CFG_RAM_SIZE,
	FW_CFG_NOGRAPHIC,
	FW_CFG_NB_CPUS,
	FW_CFG_MACHINE_ID,
	FW_CFG_KERNEL_ADDR,
	FW_CFG_KERNEL_SIZE,
	FW_CFG_KERNEL_CMDLINE,
	FW_CFG_INITRD_ADDR,
	FW_CFG_INITRD_SIZE,
	FW_CFG_BOOT_DEVICE,
	FW_CFG_NUMA,
	FW_CFG_BOOT_MENU,
	FW_CFG_MAX_CPUS,
	FW_CFG_KERNEL_ENTRY,
	FW_CFG_KERNEL_DATA,
	FW_CFG_INITRD_DATA,
	FW_CFG_CMDLINE_ADDR,
	FW_CFG_CMDLINE_SIZE,
	FW_CFG_CMDLINE_DATA,
	FW_CFG_SETUP_ADDR,
	FW_CFG_SETUP_SIZE,
	FW_CFG_SETUP_DATA,
	FW_CFG_FILE_DIR
};

#define FW_CFG_FILE_FIRST       0x20
#define FW_CFG_FILE_SLOTS       0x10
#define FW_CFG_MAX_ENTRY        (FW_CFG_FILE_FIRST+FW_CFG_FILE_SLOTS)

#define FW_CFG_WRITE_CHANNEL    0x4000
#define FW_CFG_ARCH_LOCAL       0x8000
#define FW_CFG_ENTRY_MASK       ~(FW_CFG_WRITE_CHANNEL | FW_CFG_ARCH_LOCAL)

#define FW_CFG_ACPI_TABLES      (FW_CFG_ARCH_LOCAL + 0)
#define FW_CFG_SMBIOS_ENTRIES   (FW_CFG_ARCH_LOCAL + 1)
#define FW_CFG_IRQ0_OVERRIDE    (FW_CFG_ARCH_LOCAL + 2)
#define FW_CFG_E820_TABLE       (FW_CFG_ARCH_LOCAL + 3)
#define FW_CFG_HPET             (FW_CFG_ARCH_LOCAL + 4)

#define FW_CFG_INVALID          0xffff

typedef struct FWCfgFile {
    uint32_t  size;        /* file size */
    uint16_t  select;      /* write this to 0x510 to read it */
    uint16_t  reserved;
    char      name[56];
} FWCfgFile;

typedef struct FWCfgFiles {
    uint32_t  count;
    FWCfgFile f[];
} FWCfgFiles;

typedef struct FwCfgE820Entry {
    uint64_t address;
    uint64_t length;
    uint32_t type;
} FwCfgE820Entry __attribute((__aligned__(4)));


#define SMBIOS_FIELD_ENTRY 0
#define SMBIOS_TABLE_ENTRY 1

typedef struct FwCfgSmbios {
	uint16_t length;
	uint8_t  headertype;
	uint8_t  tabletype;
	uint16_t fieldoffset;
} FwCfgSmbios;

#endif /* FW_CFG_IF_H */
