/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 The ChromiumOS Authors.  All rights reserved.
 * Copyright (C) 2014 Vladimir Serbinenko
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*	Vendor Name    : IDT
 *	Vendor ID      : 0x10ec0269
 *	Subsystem ID   : 0x17aa21fa
 *	Revision ID    : 0x100303
 */


static const u32 mainboard_cim_verb_data[] = {
	/* coreboot specific header */
  	0x10ec0269,	// Codec Vendor / Device ID: Realtek ALC269VC
  	0x17aa21fa,	// Subsystem ID
	0x0000007d,	// Number of 4 dword sets

/* Bits 31:28 - Codec Address */
/* Bits 27:20 - NID */
/* Bits 19:8 - Verb ID */
/* Bits 7:0  - Payload */

/* NID 0x01 - NodeInfo */
	AZALIA_SUBVENDOR(0x0, 0x17AA21FA),

/* NID 0x0A - External Microphone Connector
 * Config=0x04A11020 (External,Right; MicIn,3.5mm; Black,JD; DA,Seq)
 */
	AZALIA_PIN_CFG(0x0, 0x0A, 0x04A11020),

/* NID 0x0B - Headphone Connector
 * Config=0x0421101F (External,Right; HP,3.5mm; Black,JD; DA,Seq)
 */
	AZALIA_PIN_CFG(0x0, 0x0B, 0x0421101F),

/* NID 0x0C - Not connected
 * Config=0x40F000F0 (N/A,N/A; Other,Unknown; Unknown,JD; DA,Seq)
 */
	AZALIA_PIN_CFG(0x0, 0x0C, 0x40F000F0),

/* NID 0x0D - Internal Speakers
 * Config=0x90170110 (Fixed,Int; Speaker,Other Analog; Unknown,nJD; DA,Seq)
 */
	AZALIA_PIN_CFG(0x0, 0x0D, 0x90170110),

/* NID 0x0F - Not connected
 * Config=0x40F000F0
 */
	AZALIA_PIN_CFG(0x0, 0x0F, 0x40F000F0),

/* NID 0x11 - Internal Microphone
 * Config=0xD5A30140 (Fixed internal,Top; Mic In,ATIPI; Unknown,nJD; DA,Seq)
 */
	AZALIA_PIN_CFG(0x0, 0x11, 0xD5A30140),
	AZALIA_PIN_CFG(0x0, 0x12, 0x90A60140),
	AZALIA_PIN_CFG(0x0, 0x14, 0x90170110),
	AZALIA_PIN_CFG(0x0, 0x15, 0x03211020),
	AZALIA_PIN_CFG(0x0, 0x18, 0x03A11830),
	AZALIA_PIN_CFG(0x0, 0x19, 0x411111F0),

	0x01970804,
	0x01870803,
	0x01470740,
	0x00970600,

	0x00370600,
	0x00270600,
	0x00270600,
	0x00270600,

	AZALIA_PIN_CFG(0x0, 0x1A, 0x411111F0),
	AZALIA_PIN_CFG(0x0, 0x1D, 0x40138205),
	AZALIA_PIN_CFG(0x0, 0x1E, 0x411111F0),

	/*
	 * Hardware EQ Parameters
	 * Sample Rate 88200
	 */
	0x0227A63F,	0x0227A73E,	0x0227A8EB,	0x0227A93F,
	0x0227AA3E,	0x0227ABEB,	0x0227AC00,	0x0227AD80,
	0x0227A681,	0x0227A782,	0x0227A829,	0x0227A981,
	0x0227AA82,	0x0227AB29,	0x0227AC01,	0x0227AD80,
	0x0227A63F,	0x0227A73E,	0x0227A8EB,	0x0227A93F,
	0x0227AA3E,	0x0227ABEB,	0x0227AC02,	0x0227AD80,
	0x0227A67E,	0x0227A77B,	0x0227A846,	0x0227A97E,
	0x0227AA7B,	0x0227AB46,	0x0227AC03,	0x0227AD80,
	0x0227A6C1,	0x0227A77F,	0x0227A898,	0x0227A9C1,
	0x0227AA7F,	0x0227AB98,	0x0227AC04,	0x0227AD80,
	0x0227A63E,	0x0227A7D1,	0x0227A84F,	0x0227A93E,
	0x0227AAD1,	0x0227AB4F,	0x0227AC05,	0x0227AD80,
	0x0227A683,	0x0227A7BE,	0x0227A855,	0x0227A983,
	0x0227AABE,	0x0227AB55,	0x0227AC06,	0x0227AD80,
	0x0227A63D,	0x0227A7B9,	0x0227A856,	0x0227A93D,
	0x0227AAB9,	0x0227AB56,	0x0227AC07,	0x0227AD80,
	0x0227A67C,	0x0227A741,	0x0227A8AB,	0x0227A97C,
	0x0227AA41,	0x0227ABAB,	0x0227AC08,	0x0227AD80,
	0x0227A6C3,	0x0227A775,	0x0227A85A,	0x0227A9C3,
	0x0227AA75,	0x0227AB5A,	0x0227AC09,	0x0227AD80,
	0x0227A63F,	0x0227A79E,	0x0227A829,	0x0227A93F,
	0x0227AA9E,	0x0227AB29,	0x0227AC0A,	0x0227AD80,
	0x0227A682,	0x0227A7E3,	0x0227A867,	0x0227A982,
	0x0227AAE3,	0x0227AB67,	0x0227AC0B,	0x0227AD80,
	0x0227A63E,	0x0227A74F,	0x0227A89D,	0x0227A93E,
	0x0227AA4F,	0x0227AB9D,	0x0227AC0C,	0x0227AD80,
	0x0227A67D,	0x0227A71C,	0x0227A899,	0x0227A97D,
	0x0227AA1C,	0x0227AB99,	0x0227AC0D,	0x0227AD80,
	0x0227A6C2,	0x0227A712,	0x0227A839,	0x0227A9C2,
	0x0227AA12,	0x0227AB39,	0x0227AC0E,	0x0227AD80,
	0x0227A63F,	0x0227A708,	0x0227A856,	0x0227A93F,
	0x0227AA08,	0x0227AB56,	0x0227AC0F,	0x0227AD80,
	0x0227A68E,	0x0227A7ED,	0x0227A89D,	0x0227A98E,
	0x0227AAED,	0x0227AB9D,	0x0227AC10,	0x0227AD80,
	0x0227A637,	0x0227A78F,	0x0227A853,	0x0227A937,
	0x0227AA8F,	0x0227AB53,	0x0227AC11,	0x0227AD80,
	0x0227A671,	0x0227A712,	0x0227A863,	0x0227A971,
	0x0227AA12,	0x0227AB63,	0x0227AC12,	0x0227AD80,
	0x0227A6C9,	0x0227A768,	0x0227A856,	0x0227A9C9,
	0x0227AA68,	0x0227AB56,	0x0227AC13,	0x0227AD80,
	0x0227A642,	0x0227A709,	0x0227A838,	0x0227A942,
	0x0227AA09,	0x0227AB38,	0x0227AC14,	0x0227AD80,
	0x0227A69C,	0x0227A78A,	0x0227A867,	0x0227A99C,
	0x0227AA8A,	0x0227AB67,	0x0227AC15,	0x0227AD80,
	0x0227A634,	0x0227A717,	0x0227A8E3,	0x0227A934,
	0x0227AA17,	0x0227ABE3,	0x0227AC16,	0x0227AD80,
	0x0227A663,	0x0227A775,	0x0227A899,	0x0227A963,
	0x0227AA75,	0x0227AB99,	0x0227AC17,	0x0227AD80,
	0x0227A6C9,	0x0227A7DE,	0x0227A8E5,	0x0227A9C9,
	0x0227AADE,	0x0227ABE5,	0x0227AC18,	0x0227AD80,
	0x0227A640,	0x0227A700,	0x0227A800,	0x0227A940,
	0x0227AA00,	0x0227AB00,	0x0227AC19,	0x0227AD80,

	/*
	 * Hardware EQ Parameters
	 * Sample Rate 96000
	 */
	0x0227A63F,	0x0227A74E,	0x0227A888,	0x0227A93F,
	0x0227AA4E,	0x0227AB88,	0x0227AC1A,	0x0227AD80,
	0x0227A681,	0x0227A762,	0x0227A8EE,	0x0227A981,
	0x0227AA62,	0x0227ABEE,	0x0227AC1B,	0x0227AD80,
	0x0227A63F,	0x0227A74E,	0x0227A888,	0x0227A93F,
	0x0227AA4E,	0x0227AB88,	0x0227AC1C,	0x0227AD80,
	0x0227A67E,	0x0227A79A,	0x0227A8E7,	0x0227A97E,
	0x0227AA9A,	0x0227ABE7,	0x0227AC1D,	0x0227AD80,
	0x0227A6C1,	0x0227A760,	0x0227A8C3,	0x0227A9C1,
	0x0227AA60,	0x0227ABC3,	0x0227AC1E,	0x0227AD80,
	0x0227A63E,	0x0227A7E9,	0x0227A84B,	0x0227A93E,
	0x0227AAE9,	0x0227AB4B,	0x0227AC1F,	0x0227AD80,
	0x0227A683,	0x0227A76C,	0x0227A8F2,	0x0227A983,
	0x0227AA6C,	0x0227ABF2,	0x0227AC20,	0x0227AD80,
	0x0227A63D,	0x0227A7E7,	0x0227A880,	0x0227A93D,
	0x0227AAE7,	0x0227AB80,	0x0227AC21,	0x0227AD80,
	0x0227A67C,	0x0227A793,	0x0227A80E,	0x0227A97C,
	0x0227AA93,	0x0227AB0E,	0x0227AC22,	0x0227AD80,
	0x0227A6C3,	0x0227A72F,	0x0227A835,	0x0227A9C3,
	0x0227AA2F,	0x0227AB35,	0x0227AC23,	0x0227AD80,
	0x0227A63F,	0x0227A7A5,	0x0227A8FE,	0x0227A93F,
	0x0227AAA5,	0x0227ABFE,	0x0227AC24,	0x0227AD80,
	0x0227A682,	0x0227A798,	0x0227A89D,	0x0227A982,
	0x0227AA98,	0x0227AB9D,	0x0227AC25,	0x0227AD80,
	0x0227A63E,	0x0227A772,	0x0227A839,	0x0227A93E,
	0x0227AA72,	0x0227AB39,	0x0227AC26,	0x0227AD80,
	0x0227A67D,	0x0227A767,	0x0227A863,	0x0227A97D,
	0x0227AA67,	0x0227AB63,	0x0227AC27,	0x0227AD80,
	0x0227A6C1,	0x0227A7E7,	0x0227A8C8,	0x0227A9C1,
	0x0227AAE7,	0x0227ABC8,	0x0227AC28,	0x0227AD80,
	0x0227A63F,	0x0227A71B,	0x0227A81A,	0x0227A93F,
	0x0227AA1B,	0x0227AB1A,	0x0227AC29,	0x0227AD80,
	0x0227A68D,	0x0227A763,	0x0227A872,	0x0227A98D,
	0x0227AA63,	0x0227AB72,	0x0227AC2A,	0x0227AD80,
	0x0227A638,	0x0227A733,	0x0227A809,	0x0227A938,
	0x0227AA33,	0x0227AB09,	0x0227AC2B,	0x0227AD80,
	0x0227A672,	0x0227A79C,	0x0227A88E,	0x0227A972,
	0x0227AA9C,	0x0227AB8E,	0x0227AC2C,	0x0227AD80,
	0x0227A6C8,	0x0227A7B1,	0x0227A8DD,	0x0227A9C8,
	0x0227AAB1,	0x0227ABDD,	0x0227AC2D,	0x0227AD80,
	0x0227A641,	0x0227A7E1,	0x0227A8D8,	0x0227A941,
	0x0227AAE1,	0x0227ABD8,	0x0227AC2E,	0x0227AD80,
	0x0227A699,	0x0227A70D,	0x0227A820,	0x0227A999,
	0x0227AA0D,	0x0227AB20,	0x0227AC2F,	0x0227AD80,
	0x0227A634,	0x0227A7FE,	0x0227A823,	0x0227A934,
	0x0227AAFE,	0x0227AB23,	0x0227AC30,	0x0227AD80,
	0x0227A666,	0x0227A7F2,	0x0227A8E0,	0x0227A966,
	0x0227AAF2,	0x0227ABE0,	0x0227AC31,	0x0227AD80,
	0x0227A6C9,	0x0227A720,	0x0227A804,	0x0227A9C9,
	0x0227AA20,	0x0227AB04,	0x0227AC32,	0x0227AD80,
	0x0227A640,	0x0227A700,	0x0227A800,	0x0227A940,
	0x0227AA00,	0x0227AB00,	0x0227AC33,	0x0227AD80,

	/* SAFEDSP Parameters */
	0x022782C1,	0x02277127,	0x02277227,	0x02278801,
	0x02278C58,	0x02278E90,	0x0227890A,	0x02278A14,
	0x02278B0F,	0x0017B008,

	/* Misc entries */
		0x00B707C0, /* Enable PortB as Output with HP amp */
		0x00D70740, /* Enable PortD as Output */
		0x0017A200, /* Disable ClkEn of PortSenseTst */
		0x0017C621, /* Slave Port - Port A used as microphone input for
		                            combo Jack
		               Master Port - Port B used for Jack Presence Detect
		               Enable Combo Jack Detection */
		0x0017A208, /* Enable ClkEn of PortSenseTst */
		0x00170500, /* Set power state to D0 */

	/* --- Next Codec --- */

/*	Vendor Name    : Intel
 *	Vendor ID      : 0x80862806
 *	Subsystem ID   : 0x80860101
 *	Revision ID    : 0x100000
 */
	/* coreboot specific header */
	0x80862806,	// Codec Vendor / Device ID: Intel PantherPoint HDMI
	0x80860101,	// Subsystem ID
	0x00000004,	// Number of IDs

	/* NID 0x01, HDA Codec Subsystem ID Verb Table: 0x80860101 */
	AZALIA_SUBVENDOR(0x3, 0x80860101),

	/* Pin Complex (NID 0x05) Digital Out at Int HDMI */
	AZALIA_PIN_CFG(0x3, 0x05, 0x18560010),

	/* Pin Complex (NID 0x06) Digital Out at Int HDMI */
	AZALIA_PIN_CFG(0x3, 0x06, 0x18560020),

	/* Pin Complex (NID 0x07) Digital Out at Int HDMI */
	AZALIA_PIN_CFG(0x3, 0x07, 0x18560030)
};

static const u32 mainboard_pc_beep_verbs[] = {
	0x02177a00, /* Digital PCBEEP Gain: 0h=-9db, 1h=-6db ... 4h=+3db, 5h=+6db */
};

static const u32 mainboard_pc_beep_verbs_size =
	ARRAY_SIZE(mainboard_pc_beep_verbs);
