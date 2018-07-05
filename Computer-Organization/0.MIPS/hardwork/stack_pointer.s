  .text
main:
  addi $sp, $sp, -8
  li $t0, 1
  sw $t0, 4($sp)
  sw $t0, 8($sp)
  lw $t1, 4($sp)
  lw $t2, 8($sp)