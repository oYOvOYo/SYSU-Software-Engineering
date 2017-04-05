# 要求：
# 从键盘输入10个无符号字数并从大到小进行排序，排序结果在屏幕上显示出来。
# 暂时不想把时间花在 无符号字 读入，这种问题，不管是用double存还是str存再转化都很烦

  .data
welcome_str: .asciiz "welcome"
num_array: .space 40

  .text
main:
  la $s0, num_array

  li $t0, 0
  li $t1, 8
read_int:
  slt $t3, $t0, $t1
  beq $t3, $zero, finished_read
  li $v0, 5
  syscall
  add $t2, $s0, $t0
  sw $v0, 0($t2)
  addi $t0, $t0, 4
  j read_int
finished_read:

  li $t0, 0
  li $t1, 4
print_int:
  slt $t3, $t0, $t1
  beq $t3, $zero, finished_print
  li $v0, 1
  add $t2, $s0, $t0
  ld $a0, 0($t2)
  syscall
  addi $t0, $t0, 4
  j print_int
finished_print:
