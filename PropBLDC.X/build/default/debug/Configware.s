	.file "C:\\Users\\DenisT\\Desktop\\Master_2\\bULBot\\secondaryRobot-secondaryRobot2016\\PropBLDC.X\\Configware.c"
	.section	.debug_abbrev,info
.Ldebug_abbrev0:
	.section	.debug_info,info
.Ldebug_info0:
	.section	.debug_line,info
.Ldebug_line0:
	.section	.text,code
.Ltext0:
	.global	__FICD	; export
	.section	__FICD.sec,code
	.align	2
	.type	__FICD,@object
__FICD:
	.word	-33
	.global	__FWDT	; export
	.section	__FWDT.sec,code
	.align	2
	.type	__FWDT,@object
__FWDT:
	.word	-129
	.global	__FGS	; export
	.section	__FGS.sec,code
	.align	2
	.type	__FGS,@object
__FGS:
	.word	-1
	.global	__FOSCSEL	; export
	.section	__FOSCSEL.sec,code
	.align	2
	.type	__FOSCSEL,@object
__FOSCSEL:
	.word	-8
	.global	__FOSC	; export
	.section	__FOSC.sec,code
	.align	2
	.type	__FOSC,@object
__FOSC:
	.word	-131
	.section	.text,code
	.align	2
	.global	_canPinAssign	; export
	.type	_canPinAssign,@function
_canPinAssign:
.LFB0:
.LSM0:
	.set ___PA___,1
	lnk	#0
.LSM1:
	mov	#10,w1
	mov	#11,w0
	rcall	_ppsInConfig
.LSM2:
	mov	#11,w1
	mov	#16,w0
	rcall	_ppsOutConfig
.LSM3:
	ulnk	
	return	
	.set ___PA___,0
.LFE0:
	.section	.debug_frame,info
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.byte	0
	.uleb128 0x1
	.sleb128 2
	.byte	0x25
	.byte	0x12
	.uleb128 0xf
	.sleb128 -2
	.byte	0x9
	.uleb128 0x25
	.uleb128 0xf
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x324
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_21) (A) Build date: Jan  2 2014"
	.byte	0x1
	.asciz	"Configware.c"
	.ascii	"C:\\\\Users\\\\DenisT\\\\Desktop\\\\Master_2\\\\bULBot\\\\secondaryR"
	.asciz	"obot-secondaryRobot2016\\\\PropBLDC.X"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x2
	.byte	0x1a
	.4byte	0x1d3
	.uleb128 0x3
	.asciz	"PPS_C1OUT"
	.sleb128 1
	.uleb128 0x3
	.asciz	"PPS_C2OUT"
	.sleb128 2
	.uleb128 0x3
	.asciz	"PPS_U1TX"
	.sleb128 3
	.uleb128 0x3
	.asciz	"PPS_U1RTS"
	.sleb128 4
	.uleb128 0x3
	.asciz	"PPS_U2TX"
	.sleb128 5
	.uleb128 0x3
	.asciz	"PPS_U2RTS"
	.sleb128 6
	.uleb128 0x3
	.asciz	"PPS_SDO1"
	.sleb128 7
	.uleb128 0x3
	.asciz	"PPS_OUT_SCK1"
	.sleb128 8
	.uleb128 0x3
	.asciz	"PPS_OUT_SS1"
	.sleb128 9
	.uleb128 0x3
	.asciz	"PPS_SDO2"
	.sleb128 10
	.uleb128 0x3
	.asciz	"PPS_OUT_SCK2"
	.sleb128 11
	.uleb128 0x3
	.asciz	"PPS_OUT_SS2"
	.sleb128 12
	.uleb128 0x3
	.asciz	"PPS_CSDO"
	.sleb128 13
	.uleb128 0x3
	.asciz	"PPS_CSCKOUT"
	.sleb128 14
	.uleb128 0x3
	.asciz	"PPS_COFSOUT"
	.sleb128 15
	.uleb128 0x3
	.asciz	"PPS_C1TX"
	.sleb128 16
	.uleb128 0x3
	.asciz	"PPS_OC1"
	.sleb128 18
	.uleb128 0x3
	.asciz	"PPS_OC2"
	.sleb128 19
	.uleb128 0x3
	.asciz	"PPS_OC3"
	.sleb128 20
	.uleb128 0x3
	.asciz	"PPS_OC4"
	.sleb128 21
	.uleb128 0x3
	.asciz	"PPS_UPDN1"
	.sleb128 26
	.uleb128 0x3
	.asciz	"PPS_UPDN2"
	.sleb128 27
	.byte	0x0
	.uleb128 0x2
	.byte	0x2
	.byte	0x2
	.byte	0x41
	.4byte	0x290
	.uleb128 0x3
	.asciz	"PPS_U1RX"
	.sleb128 1
	.uleb128 0x3
	.asciz	"PPS_U1CTS"
	.sleb128 2
	.uleb128 0x3
	.asciz	"PPS_U2RX"
	.sleb128 3
	.uleb128 0x3
	.asciz	"PPS_U2CTS"
	.sleb128 4
	.uleb128 0x3
	.asciz	"PPS_SDI1"
	.sleb128 5
	.uleb128 0x3
	.asciz	"PPS_IN_SCK1"
	.sleb128 6
	.uleb128 0x3
	.asciz	"PPS_IN_SS1"
	.sleb128 7
	.uleb128 0x3
	.asciz	"PPS_SDI2"
	.sleb128 8
	.uleb128 0x3
	.asciz	"PPS_IN_SCK2"
	.sleb128 9
	.uleb128 0x3
	.asciz	"PPS_IN_SS2"
	.sleb128 10
	.uleb128 0x3
	.asciz	"PPS_IN_C1RX"
	.sleb128 11
	.uleb128 0x3
	.asciz	"PPS_QEA1"
	.sleb128 12
	.uleb128 0x3
	.asciz	"PPS_QEB1"
	.sleb128 13
	.uleb128 0x3
	.asciz	"PPS_QEA2"
	.sleb128 14
	.uleb128 0x3
	.asciz	"PPS_QEB2"
	.sleb128 15
	.byte	0x0
	.uleb128 0x4
	.byte	0x2
	.byte	0x7
	.asciz	"unsigned int"
	.uleb128 0x5
	.byte	0x1
	.asciz	"canPinAssign"
	.byte	0x1
	.byte	0x1f
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5e
	.uleb128 0x6
	.asciz	"_FGS"
	.byte	0x3
	.2byte	0x5ae6
	.4byte	0x290
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FGS
	.uleb128 0x6
	.asciz	"_FOSCSEL"
	.byte	0x3
	.2byte	0x5b0a
	.4byte	0x290
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FOSCSEL
	.uleb128 0x6
	.asciz	"_FOSC"
	.byte	0x3
	.2byte	0x5b34
	.4byte	0x290
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FOSC
	.uleb128 0x6
	.asciz	"_FWDT"
	.byte	0x3
	.2byte	0x5b66
	.4byte	0x290
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FWDT
	.uleb128 0x6
	.asciz	"_FICD"
	.byte	0x3
	.2byte	0x5bed
	.4byte	0x290
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__FICD
	.byte	0x0
	.section	.debug_abbrev,info
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x53
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x328
	.4byte	0x2a0
	.asciz	"canPinAssign"
	.4byte	0x2bc
	.asciz	"_FGS"
	.4byte	0x2d0
	.asciz	"_FOSCSEL"
	.4byte	0x2e8
	.asciz	"_FOSC"
	.4byte	0x2fd
	.asciz	"_FWDT"
	.4byte	0x312
	.asciz	"_FICD"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0xe
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x328
	.4byte	0x0
	.section	.debug_aranges,info
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_line,info
	.4byte	.LELT0-.LSLT0
.LSLT0:
	.2byte	0x2
	.4byte	.LELTP0-.LASLTP0
.LASLTP0:
	.byte	0x1
	.byte	0x1
	.byte	0xf6
	.byte	0xf5
	.byte	0xa
	.byte	0x0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.byte	0x1
	.ascii	"../libdspic"
	.byte 0
	.ascii	"c:\\program files (x86)\\microchip\\xc16\\v1.21\\bin\\bin\\../..\\su"
	.ascii	"pport\\dsPIC33F\\h"
	.byte 0
	.byte	0x0
	.asciz	"Configware.c"
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"pps.h"
	.uleb128 0x1
	.uleb128 0x0
	.uleb128 0x0
	.asciz	"p33FJ128MC804.h"
	.uleb128 0x2
	.uleb128 0x0
	.uleb128 0x0
	.byte	0x0
.LELTP0:
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.Letext0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM0
	.byte	0x32
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM3
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
