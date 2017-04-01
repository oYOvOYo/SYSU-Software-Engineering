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
var1:       .word   3
array1:     .byte   'a', 'b'
array2:     .space  40

  .text 
add $s1 $zero 1