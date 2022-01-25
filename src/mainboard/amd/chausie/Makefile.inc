# SPDX-License-Identifier: GPL-2.0-only

bootblock-y += bootblock.c
bootblock-y += early_gpio.c

romstage-y += port_descriptors.c

ramstage-y += chromeos.c

#TODO: add APCB binaries
#APCB_SOURCES = $(MAINBOARD_BLOBS_DIR)/APCB_CZN_D4.bin
#APCB_SOURCES_RECOVERY = $(MAINBOARD_BLOBS_DIR)/APCB_CZN_D4_DefaultRecovery.bin

ifeq ($(CONFIG_CHAUSIE_HAVE_MCHP_FW),y)
$(call add_intermediate, add_mchp_fw)
	$(CBFSTOOL) $(obj)/coreboot.pre write -r EC -f $(CONFIG_CHAUSIE_MCHP_FW_FILE) --fill-upward
else
files_added:: warn_no_mchp
endif # CONFIG_CHAUSIE_HAVE_MCHP_FW

PHONY+=warn_no_mchp
warn_no_mchp:
	printf "\n\t** WARNING **\n"
	printf "coreboot has been built without the Microchip EC FW.\n"
	printf "Do not flash this image.  Your Chausie's power button\n"
	printf "will not respond when you press it.\n\n"