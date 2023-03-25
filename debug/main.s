	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.global	vectors
	.section	.isr_vector,"aw"
	.align	2
	.type	vectors, %object
	.size	vectors, 272
vectors:
	.word	_estack
	.word	Reset_Handler
	.space	264
	.section	.text.main,"ax",%progbits
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
.LFB0:
	.file 1 "main.c"
	.loc 1 46 1
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	add	r7, sp, #0
.LCFI1:
	.cfi_def_cfa_register 7
	.loc 1 47 15
	ldr	r3, .L3
	ldr	r3, [r3, #48]
	ldr	r2, .L3
	orr	r3, r3, #4
	str	r3, [r2, #48]
	.loc 1 49 15
	ldr	r3, .L3+4
	ldr	r3, [r3]
	ldr	r2, .L3+4
	and	r3, r3, #-268435456
	str	r3, [r2]
	.loc 1 51 18
	ldr	r3, .L3+4
	ldr	r3, [r3]
	ldr	r2, .L3+4
	orr	r3, r3, #67108864
	str	r3, [r2]
.L2:
	.loc 1 54 9 discriminator 1
	movs	r1, #13
	ldr	r0, .L3+4
	bl	gpio_set
	.loc 1 55 3 discriminator 1
	mov	r0, #500
	bl	ms_delay
	.loc 1 56 9 discriminator 1
	movs	r1, #13
	ldr	r0, .L3+4
	bl	gpio_reset
	.loc 1 57 3 discriminator 1
	mov	r0, #500
	bl	ms_delay
	.loc 1 54 9 discriminator 1
	b	.L2
.L4:
	.align	2
.L3:
	.word	1073887232
	.word	1073874944
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.text.Reset_Handler,"ax",%progbits
	.align	1
	.global	Reset_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	Reset_Handler, %function
Reset_Handler:
.LFB1:
	.loc 1 64 1
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	add	r7, sp, #0
.LCFI3:
	.cfi_def_cfa_register 7
	.loc 1 67 40
	ldr	r2, .L7
	ldr	r3, .L7+4
	subs	r3, r2, r3
	asrs	r3, r3, #2
	.loc 1 67 5
	mov	r2, r3
	ldr	r1, .L7+8
	ldr	r0, .L7+4
	bl	memcpy
	.loc 1 68 30
	ldr	r2, .L7+12
	ldr	r3, .L7+16
	subs	r3, r2, r3
	asrs	r3, r3, #2
	.loc 1 68 5
	mov	r2, r3
	movs	r1, #0
	ldr	r0, .L7+16
	bl	memset
	.loc 1 70 5
	bl	main
.L6:
	.loc 1 71 10 discriminator 1
	b	.L6
.L8:
	.align	2
.L7:
	.word	_edata
	.word	_sdata
	.word	_la_data
	.word	_ebss
	.word	_sbss
	.cfi_endproc
.LFE1:
	.size	Reset_Handler, .-Reset_Handler
	.section	.text.memcpy,"ax",%progbits
	.align	1
	.weak	memcpy
	.syntax unified
	.thumb
	.thumb_func
	.type	memcpy, %function
memcpy:
.LFB2:
	.loc 1 75 1
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI4:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #28
.LCFI5:
	.cfi_def_cfa_offset 32
	add	r7, sp, #0
.LCFI6:
	.cfi_def_cfa_register 7
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
.LBB2:
	.loc 1 76 19
	movs	r3, #0
	str	r3, [r7, #20]
	.loc 1 76 5
	b	.L10
.L11:
	.loc 1 78 40 discriminator 3
	ldr	r2, [r7, #8]
	ldr	r3, [r7, #20]
	add	r2, r2, r3
	.loc 1 78 22 discriminator 3
	ldr	r1, [r7, #12]
	ldr	r3, [r7, #20]
	add	r3, r3, r1
	.loc 1 78 40 discriminator 3
	ldrb	r2, [r2]	@ zero_extendqisi2
	.loc 1 78 26 discriminator 3
	strb	r2, [r3]
	.loc 1 76 34 discriminator 3
	ldr	r3, [r7, #20]
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L10:
	.loc 1 76 5 discriminator 1
	ldr	r2, [r7, #20]
	ldr	r3, [r7, #4]
	cmp	r2, r3
	bcc	.L11
.LBE2:
	.loc 1 80 12
	ldr	r3, [r7, #12]
	.loc 1 81 1
	mov	r0, r3
	adds	r7, r7, #28
.LCFI7:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI8:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI9:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE2:
	.size	memcpy, .-memcpy
	.section	.text.memset,"ax",%progbits
	.align	1
	.weak	memset
	.syntax unified
	.thumb
	.thumb_func
	.type	memset, %function
memset:
.LFB3:
	.loc 1 83 71
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #28
.LCFI11:
	.cfi_def_cfa_offset 32
	add	r7, sp, #0
.LCFI12:
	.cfi_def_cfa_register 7
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
	.loc 1 84 8
	ldr	r3, [r7, #12]
	str	r3, [r7, #20]
	.loc 1 85 8
	b	.L14
.L15:
	.loc 1 86 10
	ldr	r3, [r7, #8]
	uxtb	r2, r3
	.loc 1 86 8
	ldr	r3, [r7, #20]
	strb	r2, [r3]
	.loc 1 87 6
	ldr	r3, [r7, #20]
	adds	r3, r3, #1
	str	r3, [r7, #20]
.L14:
	.loc 1 85 15
	ldr	r3, [r7, #4]
	subs	r2, r3, #1
	str	r2, [r7, #4]
	.loc 1 85 8
	cmp	r3, #0
	bne	.L15
	.loc 1 89 9
	ldr	r3, [r7, #12]
	.loc 1 90 1
	mov	r0, r3
	adds	r7, r7, #28
.LCFI13:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI14:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI15:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE3:
	.size	memset, .-memset
	.section	.text.ms_delay,"ax",%progbits
	.align	1
	.global	ms_delay
	.syntax unified
	.thumb
	.thumb_func
	.type	ms_delay, %function
ms_delay:
.LFB4:
	.loc 1 93 1
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI16:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #20
.LCFI17:
	.cfi_def_cfa_offset 24
	add	r7, sp, #0
.LCFI18:
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
	.loc 1 94 11
	b	.L18
.L21:
.LBB3:
	.loc 1 96 22
	mov	r3, #1000
	str	r3, [r7, #12]
	.loc 1 97 15
	b	.L19
.L20:
	.loc 1 98 13
	.syntax unified
@ 98 "main.c" 1
	nop
@ 0 "" 2
	.thumb
	.syntax unified
.L19:
	.loc 1 97 17
	ldr	r3, [r7, #12]
	subs	r2, r3, #1
	str	r2, [r7, #12]
	.loc 1 97 15
	cmp	r3, #0
	bgt	.L20
.L18:
.LBE3:
	.loc 1 94 14
	ldr	r3, [r7, #4]
	subs	r2, r3, #1
	str	r2, [r7, #4]
	.loc 1 94 11
	cmp	r3, #0
	bgt	.L21
	.loc 1 100 1
	nop
	nop
	adds	r7, r7, #20
.LCFI19:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI20:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI21:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE4:
	.size	ms_delay, .-ms_delay
	.section	.text.gpio_set,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	gpio_set, %function
gpio_set:
.LFB5:
	.loc 1 102 61
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI22:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #12
.LCFI23:
	.cfi_def_cfa_offset 16
	add	r7, sp, #0
.LCFI24:
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
	str	r1, [r7]
	.loc 1 103 16
	ldr	r3, [r7, #4]
	ldr	r3, [r3, #24]
	.loc 1 103 21
	movs	r1, #1
	ldr	r2, [r7]
	lsl	r2, r1, r2
	.loc 1 103 16
	orrs	r2, r2, r3
	ldr	r3, [r7, #4]
	str	r2, [r3, #24]
	.loc 1 104 1
	nop
	adds	r7, r7, #12
.LCFI25:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI26:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI27:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE5:
	.size	gpio_set, .-gpio_set
	.section	.text.gpio_reset,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	gpio_reset, %function
gpio_reset:
.LFB6:
	.loc 1 106 63
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
.LCFI28:
	.cfi_def_cfa_offset 4
	.cfi_offset 7, -4
	sub	sp, sp, #12
.LCFI29:
	.cfi_def_cfa_offset 16
	add	r7, sp, #0
.LCFI30:
	.cfi_def_cfa_register 7
	str	r0, [r7, #4]
	str	r1, [r7]
	.loc 1 107 16
	ldr	r3, [r7, #4]
	ldr	r3, [r3, #24]
	.loc 1 107 29
	ldr	r2, [r7]
	adds	r2, r2, #16
	.loc 1 107 21
	movs	r1, #1
	lsl	r2, r1, r2
	.loc 1 107 16
	orrs	r2, r2, r3
	ldr	r3, [r7, #4]
	str	r2, [r3, #24]
	.loc 1 108 1
	nop
	adds	r7, r7, #12
.LCFI31:
	.cfi_def_cfa_offset 4
	mov	sp, r7
.LCFI32:
	.cfi_def_cfa_register 13
	@ sp needed
	pop	{r7}
.LCFI33:
	.cfi_restore 7
	.cfi_def_cfa_offset 0
	bx	lr
	.cfi_endproc
.LFE6:
	.size	gpio_reset, .-gpio_reset
	.text
.Letext0:
	.file 2 "/Applications/ARM/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/Applications/ARM/arm-none-eabi/include/sys/_stdint.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x563
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF66
	.byte	0xc
	.4byte	.LASF67
	.4byte	.LASF68
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x58
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x5
	.4byte	0x6d
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x4c
	.uleb128 0x5
	.4byte	0x80
	.uleb128 0x6
	.ascii	"rcc\000"
	.byte	0x88
	.byte	0x1
	.byte	0x6
	.byte	0x8
	.4byte	0x262
	.uleb128 0x7
	.ascii	"CR\000"
	.byte	0x1
	.byte	0x7
	.byte	0x15
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF11
	.byte	0x1
	.byte	0x7
	.byte	0x19
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF12
	.byte	0x1
	.byte	0x7
	.byte	0x22
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x7
	.ascii	"CIR\000"
	.byte	0x1
	.byte	0x7
	.byte	0x28
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.4byte	.LASF13
	.byte	0x1
	.byte	0x7
	.byte	0x2d
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.4byte	.LASF14
	.byte	0x1
	.byte	0x7
	.byte	0x37
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x1
	.byte	0x7
	.byte	0x41
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x1
	.byte	0x8
	.byte	0x7
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x1
	.byte	0x8
	.byte	0x12
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x1
	.byte	0x8
	.byte	0x1c
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x1
	.byte	0x8
	.byte	0x26
	.4byte	0x272
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x1
	.byte	0x8
	.byte	0x34
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x1
	.byte	0x8
	.byte	0x3d
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.4byte	.LASF22
	.byte	0x1
	.byte	0x8
	.byte	0x46
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.4byte	.LASF23
	.byte	0x1
	.byte	0x9
	.byte	0x7
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x8
	.4byte	.LASF24
	.byte	0x1
	.byte	0x9
	.byte	0x12
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.4byte	.LASF25
	.byte	0x1
	.byte	0x9
	.byte	0x1b
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.4byte	.LASF26
	.byte	0x1
	.byte	0x9
	.byte	0x24
	.4byte	0x272
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.4byte	.LASF27
	.byte	0x1
	.byte	0x9
	.byte	0x32
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x8
	.4byte	.LASF28
	.byte	0x1
	.byte	0x9
	.byte	0x3d
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x8
	.4byte	.LASF29
	.byte	0x1
	.byte	0xa
	.byte	0x7
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.4byte	.LASF30
	.byte	0x1
	.byte	0xa
	.byte	0x12
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x8
	.4byte	.LASF31
	.byte	0x1
	.byte	0xa
	.byte	0x1d
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.4byte	.LASF32
	.byte	0x1
	.byte	0xa
	.byte	0x28
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x8
	.4byte	.LASF33
	.byte	0x1
	.byte	0xa
	.byte	0x33
	.4byte	0x272
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x8
	.4byte	.LASF34
	.byte	0x1
	.byte	0xa
	.byte	0x41
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0x7
	.ascii	"CSR\000"
	.byte	0x1
	.byte	0xa
	.byte	0x47
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0x8
	.4byte	.LASF35
	.byte	0x1
	.byte	0xb
	.byte	0x7
	.4byte	0x272
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0x8
	.4byte	.LASF36
	.byte	0x1
	.byte	0xb
	.byte	0x15
	.4byte	0x8c
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0x8
	.4byte	.LASF37
	.byte	0x1
	.byte	0xb
	.byte	0x1c
	.4byte	0x8c
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.byte	0
	.uleb128 0x9
	.4byte	0x8c
	.4byte	0x272
	.uleb128 0xa
	.4byte	0x79
	.byte	0x1
	.byte	0
	.uleb128 0x5
	.4byte	0x262
	.uleb128 0xb
	.4byte	.LASF38
	.byte	0x28
	.byte	0x1
	.byte	0x11
	.byte	0x8
	.4byte	0x30c
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x1
	.byte	0x12
	.byte	0x15
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x1
	.byte	0x12
	.byte	0x1c
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF41
	.byte	0x1
	.byte	0x12
	.byte	0x24
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF42
	.byte	0x1
	.byte	0x12
	.byte	0x2d
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x7
	.ascii	"IDR\000"
	.byte	0x1
	.byte	0x12
	.byte	0x34
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x7
	.ascii	"ODR\000"
	.byte	0x1
	.byte	0x12
	.byte	0x39
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x1
	.byte	0x12
	.byte	0x3e
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF44
	.byte	0x1
	.byte	0x12
	.byte	0x44
	.4byte	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x7
	.ascii	"AFR\000"
	.byte	0x1
	.byte	0x12
	.byte	0x4a
	.4byte	0x272
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.byte	0
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x30
	.byte	0x1
	.byte	0x15
	.byte	0x6
	.4byte	0x333
	.uleb128 0xd
	.4byte	.LASF45
	.byte	0
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF47
	.byte	0x2
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0x3
	.byte	0
	.uleb128 0x9
	.4byte	0x343
	.4byte	0x343
	.uleb128 0xa
	.4byte	0x79
	.byte	0x43
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x349
	.uleb128 0xf
	.byte	0x1
	.uleb128 0x10
	.4byte	.LASF60
	.byte	0x1
	.byte	0x27
	.byte	0x8
	.4byte	0x333
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	vectors
	.uleb128 0x11
	.4byte	.LASF50
	.byte	0x1
	.byte	0x6a
	.byte	0x14
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.4byte	.LLST6
	.byte	0x1
	.4byte	0x397
	.uleb128 0x12
	.4byte	.LASF49
	.byte	0x1
	.byte	0x6a
	.byte	0x2c
	.4byte	0x397
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x13
	.ascii	"pin\000"
	.byte	0x1
	.byte	0x6a
	.byte	0x3b
	.4byte	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x277
	.uleb128 0x11
	.4byte	.LASF51
	.byte	0x1
	.byte	0x66
	.byte	0x14
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	.LLST5
	.byte	0x1
	.4byte	0x3d6
	.uleb128 0x12
	.4byte	.LASF49
	.byte	0x1
	.byte	0x66
	.byte	0x2a
	.4byte	0x397
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x13
	.ascii	"pin\000"
	.byte	0x1
	.byte	0x66
	.byte	0x39
	.4byte	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF58
	.byte	0x1
	.byte	0x5c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LLST4
	.byte	0x1
	.4byte	0x417
	.uleb128 0x13
	.ascii	"ms\000"
	.byte	0x1
	.byte	0x5c
	.byte	0x13
	.4byte	0x6d
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x15
	.4byte	.LBB3
	.4byte	.LBE3
	.uleb128 0x16
	.ascii	"x\000"
	.byte	0x1
	.byte	0x60
	.byte	0x16
	.4byte	0x74
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.byte	0
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF55
	.byte	0x1
	.byte	0x53
	.byte	0x1d
	.byte	0x1
	.4byte	0x471
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LLST3
	.byte	0x1
	.4byte	0x471
	.uleb128 0x12
	.4byte	.LASF52
	.byte	0x1
	.byte	0x53
	.byte	0x2a
	.4byte	0x471
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x13
	.ascii	"c\000"
	.byte	0x1
	.byte	0x53
	.byte	0x34
	.4byte	0x6d
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x12
	.4byte	.LASF53
	.byte	0x1
	.byte	0x53
	.byte	0x40
	.4byte	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x16
	.ascii	"dst\000"
	.byte	0x1
	.byte	0x54
	.byte	0x8
	.4byte	0x473
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.uleb128 0x18
	.byte	0x4
	.uleb128 0xe
	.byte	0x4
	.4byte	0x479
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF54
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF56
	.byte	0x1
	.byte	0x4a
	.byte	0x1d
	.byte	0x1
	.4byte	0x471
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LLST2
	.byte	0x1
	.4byte	0x4e2
	.uleb128 0x12
	.4byte	.LASF57
	.byte	0x1
	.byte	0x4a
	.byte	0x2a
	.4byte	0x471
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x13
	.ascii	"src\000"
	.byte	0x1
	.byte	0x4a
	.byte	0x3c
	.4byte	0x4e2
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x13
	.ascii	"n\000"
	.byte	0x1
	.byte	0x4a
	.byte	0x4a
	.4byte	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x15
	.4byte	.LBB2
	.4byte	.LBE2
	.uleb128 0x16
	.ascii	"i\000"
	.byte	0x1
	.byte	0x4c
	.byte	0x13
	.4byte	0x80
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x4e8
	.uleb128 0x19
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF59
	.byte	0x1
	.byte	0x3f
	.byte	0x6
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LLST1
	.byte	0x1
	.4byte	0x54b
	.uleb128 0x1b
	.4byte	.LASF61
	.byte	0x1
	.byte	0x41
	.byte	0x15
	.4byte	0x80
	.byte	0x1
	.byte	0x1
	.uleb128 0x1b
	.4byte	.LASF62
	.byte	0x1
	.byte	0x41
	.byte	0x1d
	.4byte	0x80
	.byte	0x1
	.byte	0x1
	.uleb128 0x1b
	.4byte	.LASF63
	.byte	0x1
	.byte	0x41
	.byte	0x25
	.4byte	0x80
	.byte	0x1
	.byte	0x1
	.uleb128 0x1b
	.4byte	.LASF64
	.byte	0x1
	.byte	0x41
	.byte	0x2f
	.4byte	0x80
	.byte	0x1
	.byte	0x1
	.uleb128 0x1b
	.4byte	.LASF65
	.byte	0x1
	.byte	0x41
	.byte	0x36
	.4byte	0x80
	.byte	0x1
	.byte	0x1
	.byte	0
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF69
	.byte	0x1
	.byte	0x2d
	.byte	0x5
	.byte	0x1
	.4byte	0x6d
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LLST0
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x15
	.byte	0
	.uleb128 0x27
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2116
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST6:
	.4byte	.LFB6
	.4byte	.LCFI28
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI28
	.4byte	.LCFI29
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI29
	.4byte	.LCFI30
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI30
	.4byte	.LCFI31
	.2byte	0x2
	.byte	0x77
	.sleb128 16
	.4byte	.LCFI31
	.4byte	.LCFI32
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI32
	.4byte	.LCFI33
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI33
	.4byte	.LFE6
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LFB5
	.4byte	.LCFI22
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI22
	.4byte	.LCFI23
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI23
	.4byte	.LCFI24
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI24
	.4byte	.LCFI25
	.2byte	0x2
	.byte	0x77
	.sleb128 16
	.4byte	.LCFI25
	.4byte	.LCFI26
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI26
	.4byte	.LCFI27
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI27
	.4byte	.LFE5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LFB4
	.4byte	.LCFI16
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI16
	.4byte	.LCFI17
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI17
	.4byte	.LCFI18
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	.LCFI18
	.4byte	.LCFI19
	.2byte	0x2
	.byte	0x77
	.sleb128 24
	.4byte	.LCFI19
	.4byte	.LCFI20
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI20
	.4byte	.LCFI21
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI21
	.4byte	.LFE4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LFB3
	.4byte	.LCFI10
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI10
	.4byte	.LCFI11
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI11
	.4byte	.LCFI12
	.2byte	0x2
	.byte	0x7d
	.sleb128 32
	.4byte	.LCFI12
	.4byte	.LCFI13
	.2byte	0x2
	.byte	0x77
	.sleb128 32
	.4byte	.LCFI13
	.4byte	.LCFI14
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI14
	.4byte	.LCFI15
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI15
	.4byte	.LFE3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LFB2
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI5
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 32
	.4byte	.LCFI6
	.4byte	.LCFI7
	.2byte	0x2
	.byte	0x77
	.sleb128 32
	.4byte	.LCFI7
	.4byte	.LCFI8
	.2byte	0x2
	.byte	0x77
	.sleb128 4
	.4byte	.LCFI8
	.4byte	.LCFI9
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI9
	.4byte	.LFE2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LFB1
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI3
	.4byte	.LFE1
	.2byte	0x2
	.byte	0x77
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LFB0
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI1
	.4byte	.LFE0
	.2byte	0x2
	.byte	0x77
	.sleb128 8
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x4c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	.LFB6
	.4byte	.LFE6
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF45:
	.ascii	"GPIO_MODE_INPUT\000"
.LASF41:
	.ascii	"OSPEEDR\000"
.LASF61:
	.ascii	"_sdata\000"
.LASF17:
	.ascii	"APB1RSTR\000"
.LASF21:
	.ascii	"AHB2ENR\000"
.LASF2:
	.ascii	"short int\000"
.LASF63:
	.ascii	"_la_data\000"
.LASF34:
	.ascii	"BDCR\000"
.LASF62:
	.ascii	"_edata\000"
.LASF37:
	.ascii	"PLLI2SCFGR\000"
.LASF69:
	.ascii	"main\000"
.LASF9:
	.ascii	"__uint32_t\000"
.LASF32:
	.ascii	"APB2LPENR\000"
.LASF36:
	.ascii	"SSCGR\000"
.LASF52:
	.ascii	"dst0\000"
.LASF13:
	.ascii	"AHB1RSTR\000"
.LASF56:
	.ascii	"memcpy\000"
.LASF12:
	.ascii	"CFGR\000"
.LASF29:
	.ascii	"AHB3LPENR\000"
.LASF30:
	.ascii	"RESERVED4\000"
.LASF24:
	.ascii	"APB1ENR\000"
.LASF35:
	.ascii	"RESERVED6\000"
.LASF51:
	.ascii	"gpio_set\000"
.LASF40:
	.ascii	"OTYPER\000"
.LASF22:
	.ascii	"AHB3ENR\000"
.LASF6:
	.ascii	"long long int\000"
.LASF42:
	.ascii	"PUPDR\000"
.LASF55:
	.ascii	"memset\000"
.LASF28:
	.ascii	"AHB2LPENR\000"
.LASF4:
	.ascii	"long int\000"
.LASF68:
	.ascii	"/Users/csrohit/code/black-pill/baremetal/debug\000"
.LASF43:
	.ascii	"BSRR\000"
.LASF39:
	.ascii	"MODER\000"
.LASF18:
	.ascii	"APB2RSTR\000"
.LASF48:
	.ascii	"GPIO_MODE_ANALOG\000"
.LASF57:
	.ascii	"dest\000"
.LASF53:
	.ascii	"length\000"
.LASF66:
	.ascii	"GNU C17 10.3.1 20210824 (release) -mcpu=cortex-m4 -"
	.ascii	"mfloat-abi=soft -mthumb -march=armv7e-m -g -gdwarf-"
	.ascii	"2 -fdata-sections -ffunction-sections\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF25:
	.ascii	"APB2ENR\000"
.LASF0:
	.ascii	"signed char\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF10:
	.ascii	"uint32_t\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF14:
	.ascii	"AHB2RSTR\000"
.LASF59:
	.ascii	"Reset_Handler\000"
.LASF11:
	.ascii	"PLLCFGR\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF54:
	.ascii	"char\000"
.LASF27:
	.ascii	"AHB1LPENR\000"
.LASF49:
	.ascii	"port\000"
.LASF50:
	.ascii	"gpio_reset\000"
.LASF16:
	.ascii	"RESERVED0\000"
.LASF19:
	.ascii	"RESERVED1\000"
.LASF23:
	.ascii	"RESERVED2\000"
.LASF26:
	.ascii	"RESERVED3\000"
.LASF67:
	.ascii	"main.c\000"
.LASF33:
	.ascii	"RESERVED5\000"
.LASF5:
	.ascii	"long unsigned int\000"
.LASF20:
	.ascii	"AHB1ENR\000"
.LASF38:
	.ascii	"gpio\000"
.LASF46:
	.ascii	"GPIO_MODE_OUTPUT\000"
.LASF15:
	.ascii	"AHB3RSTR\000"
.LASF47:
	.ascii	"GPIO_MODE_AF\000"
.LASF60:
	.ascii	"vectors\000"
.LASF44:
	.ascii	"LCKR\000"
.LASF31:
	.ascii	"APB1LPENR\000"
.LASF65:
	.ascii	"_ebss\000"
.LASF64:
	.ascii	"_sbss\000"
.LASF58:
	.ascii	"ms_delay\000"
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
