  .data
equal_str: .asciiz "they are equal\n"
not_equal_str: .asciiz "they are not equal\n"
exit_str: .asciiz "exit\n"
  .text
main:
  li $s0, 1
  li $s1, 1
  li $s2, 2
  bne $s0, $s1, not_equal
  j equal

equal:
  li $v0, 4
  la $a0, equal_str
  syscall
  j exit

not_equal:
  li $v0, 4
  la $a0, not_equal_str
  j exit

exit:
  li $v0, 4
  la $a0, exit_str
  syscall
  li $v0 10
  syscall