# quick_start.s 
# By jskyzero 2017/04/01

# Data Types
# Istruction 32 bits
# byte(8 bits), halfword(2 bytes), word(4 bytes)
# integer(4 bytes), a character(1 byte)

# Registers
# both register number (e.g. $0)and equivalent is right (e.g. $zero)
# $zero         the value zero
# $at           reserved by the assembler
# $v0 - $v1     function results
# $a0 - $a3     subroutine parameters
# $t0 - $t7     temp values 
# $s0 - $s7     saved values 
# $t8 - $t9     temp values
# #k0 - $k1     reserved for interrupt / trap 
# $gp           global pointer
# $sp           stack pointer
# $s8/$fp       save valuses / frame pointer
# $ra           return address

  .data 
# name: storage_type value(s)
# value(s) or space size
var1:       .word   3
array1:     .byte   'a', 'b'
# str1:     .asciiz "ab"
array2:     .space  40
# in my PCSpim 
# 	DATA
# [0x10000000]...[0x10010000]	0x00000000
# [0x10010000]		        0x00000003  0x00006261  0x00000000  0x00000000
# [0x10010010]...[0x10040000]	0x00000000

# this means that this is big head, for high value weight in low address weight

  .text 
main:
  add $s1, $zero 1
# use RAM with load or store instructions or use register

# load
  lw $s2, array1
  lb $s3, array1 # to low-order byte of destination register
# in my PCSpim 
# R2  (v0) = 00000000  R10 (t2) = 00000000  R18 (s2) = 00006261  R26 (k0) = 00000000
# R3  (v1) = 00000000  R11 (t3) = 00000000  R19 (s3) = 00000061  R27 (k1) = 00000000

# store
  sw $s2, array1
  sb $s1, array1
# in my PCSpim 
# [0x10010000]		        0x00000003  0x00006201  0x00000000  0x00000000

# load immediate
  li $s1, 1
  li $s2, 2
# in my PCSpim 
# R1  (at) = 10010000  R9  (t1) = 00000000  R17 (s1) = 00000001  R25 (t9) = 00000000
# R2  (v0) = 00000000  R10 (t2) = 00000000  R18 (s2) = 00000002  R26 (k0) = 00000000

# use register to store address and do more thing

  la $s4, array1
  lw $s5, ($s4)
  lw $s6, 0($s4)
  lb $s7, 1($s4)
# in my PCSpim 
# R0  (r0) = 00000000  R8  (t0) = 00000000  R16 (s0) = 00000000  R24 (t8) = 00000000
# R1  (at) = 10010000  R9  (t1) = 00000000  R17 (s1) = 00000001  R25 (t9) = 00000000
# R2  (v0) = 00000000  R10 (t2) = 00000000  R18 (s2) = 00000002  R26 (k0) = 00000000
# R3  (v1) = 00000000  R11 (t3) = 00000000  R19 (s3) = 00000061  R27 (k1) = 00000000
# R4  (a0) = 00000000  R12 (t4) = 00000000  R20 (s4) = 10010004  R28 (gp) = 10008000
# R5  (a1) = 7ffff83c  R13 (t5) = 00000000  R21 (s5) = 00006201  R29 (sp) = 7ffff838
# R6  (a2) = 7ffff840  R14 (t6) = 00000000  R22 (s6) = 00006201  R30 (s8) = 00000000
# R7  (a3) = 00000000  R15 (t7) = 00000000  R23 (s7) = 00000062  R31 (ra) = 00400018

# arithmetic instructions (can only use register)
  li $s1, 0
  li $s2, -1
  add $t0 $s1 $s2
  addu $t1, $s1, $s2
  addi $t2, $s2, -2

  mult $t2, $s2
  mflo $t3
  mfhi $t4

  div $s2, $t2 # -1 / -3
  mflo $t5 # -1 / -3 = 0 
  mfhi $t6 # -1 % -3 = -1 

  move $t7, $t6

# control structures
# branch 
  b orz # unconditional branch to program label target 
# beq blt ble bgt bge bne also are branch instructions

# jumps 
  j orz1 
# jr  $t3 is also avilable 

# subroutines
  # jal sub_label
  # jr $ra

# system call
# first supply appropriate values in registers $v0 and $a0-$a1
# result returned in register $v0
#  server       v0  use 
# print_int     1   $a0
# print_string  4   $a0
# read_int      5   $v0
# read_string   8   $a0(buffer) $a1(size)
# exit 


orz:
 li $s0, 0

orz1:
 li $s1, 1
 li $v0, 10
 syscall