# code in C 
# int fact( int n )
# {
#   if (n < 1) 
#     return 1;
#   else
#     return n * fact(n-1); 
# }

  .text

# $a0 : n
# $v0 : return value
fact:
  addi $sp, $sp, -8
  sw $ra, 4($sp)
  sw $a0, 8($sp)

  slti $t0, $a0, 1
  beq $t0, $zero, L1
  addi $v0, $zero, 1
  addi $sp, 8
  jr $ra

L1:
  addi $a0, $a0, -1
  jal fact
  lw $a0, 8($sp)
  lw $ra, 4($sp)
  addi $sp, $sp, 8
  mul $v0, $v0, $a0
  jr $ra

main:
  li $a0, 4
  jal fact
  move $a0, $v0
  li $v0, 1
  syscall
  li $v0, 10
  syscall