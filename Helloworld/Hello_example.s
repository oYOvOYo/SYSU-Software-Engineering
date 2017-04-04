	.file	1 ""
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 1
	.abicalls
	.rdata
	.align	2
$LC0:
	.ascii	"helloworld\012\000"
	.text
	.align	2
	.globl	main
$LFB0 = .
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.cpload	$25
	.set	nomacro
	
	addiu	$sp,$sp,-32
$LCFI0:
	sw	$31,28($sp)
$LCFI1:
	sw	$fp,24($sp)
	movz	$31,$31,$0
$LCFI2:
	move	$fp,$sp
$LCFI3:
	.cprestore	16
	lw	$2,%got($LC0)($28)
	nop
	addiu	$4,$2,%lo($LC0)
	lw	$2,%call16(puts)($28)
	nop
	move	$25,$2
	jalr	$25
	nop

	lw	$28,16($fp)
	move	$2,$0
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
$LFE0:
	.size	main, .-main
	.section	.eh_frame,"aw",@progbits
$Lframe1:
	.4byte	$LECIE1-$LSCIE1
$LSCIE1:
	.4byte	0x0
	.byte	0x1
	.globl	__gxx_personality_v0
	.ascii	"zP\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x1f
	.uleb128 0x5
	.byte	0x0
	.4byte	__gxx_personality_v0
	.byte	0xc
	.uleb128 0x1d
	.uleb128 0x0
	.align	2
$LECIE1:
$LSFDE1:
	.4byte	$LEFDE1-$LASFDE1
$LASFDE1:
	.4byte	$LASFDE1-$Lframe1
	.4byte	$LFB0
	.4byte	$LFE0-$LFB0
	.uleb128 0x0
	.byte	0x4
	.4byte	$LCFI0-$LFB0
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	$LCFI2-$LCFI0
	.byte	0x11
	.uleb128 0x1e
	.sleb128 2
	.byte	0x11
	.uleb128 0x1f
	.sleb128 1
	.byte	0x4
	.4byte	$LCFI3-$LCFI2
	.byte	0xd
	.uleb128 0x1e
	.align	2
$LEFDE1:
	.ident	"GCC: (Debian 4.4.5-8) 4.4.5"