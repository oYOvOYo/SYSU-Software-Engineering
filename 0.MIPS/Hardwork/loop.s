  .text
main:
  li $s0, 0
  j Loop

Loop:
  li $t0, 10
  beq $s0, $t0, Exit
  # print each time value 
  li $v0, 1
  move $a0, $s0
  syscall
  # add 1 to value 
  addi $s0, $s0, 1
  j Loop

Exit:
  li $v0, 10
  syscall