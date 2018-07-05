# 要求：
# 从键盘输入10个无符号字数并从大到小进行排序，排序结果在屏幕上显示出来。
# 暂时不想把时间花在 无符号字 读入，这种问题，不管是用double存还是str存再转化都很烦

  .data
array:        .space  40 # 10 word and 1 word 4 bit
welcome_str:  .asciiz "please enter 10 32-bit signed num\n"
separate:     .asciiz "  "
str:          .asciiz "The answer is:\n"

  .text
main:
  # store array address in $s0
  la $s0, array 
  # print welcome_str
  la $a0, welcome_str
  li $v0, 4
  syscall
  # read 10 32-bit signed num 
  li $t0, 0     # initial value 
  li $t1, 40    # initial end value 
read_int:
  slt $t3, $t0, $t1             # $t0 < $t1 => $t3 = 0
  beq $t3, $zero, finished_read # $t0 < $t1 => loop 
  li $v0, 5                     # use system call to read num
  syscall
  add $t2, $s0, $t0             # store target address
  sw $v0, 0($t2)                # write read_num to $t2 (array[i]) 
  addi $t0, $t0, 4              # update i
  j read_int
finished_read:  

# sort array
  li $t0, 0                     # loop 1:
  li $t1, 10                    # t0 < t1
loop1:
  move $t4, $t0                 # loop 2:
  li $t3, 10                    # t4 < t3
loop2:
  li $t6, 4
  mul $t6, $t6, $t3
  addi $t7, $t6, -4
  add $s1, $s0, $t6
  add $s2, $s0, $t7
  lw $s3, 0($s1)                # load
  lw $s4, 0($s2)
  slt $s5, $s4, $s3
  bne $s5, $zero, skip          # left < right => skip
  sw $s3, 0($s2)
  sw $s4, 0($s1)
skip:
  slt $t5, $t4, $t3
  addi $t3, $t3, -1             # t3--
  bne $t5, $zero, loop2

  slt $t2, $t0, $t1
  addi $t0, $t0, 1              # t0++
  bne $t2, $zero, loop1


# print sorted values 
# same structure like read
  li $t0, 0
  li $t1, 40
print_int:
  slt $t3, $t0, $t1
  beq $t3, $zero, finished_print
  add $t2, $s0, $t0
  ld $a0, 0($t2)
  li $v0, 1
  syscall
  la $a0, separate
  li $v0, 4
  syscall
  addi $t0, $t0, 4
  j print_int
finished_print:
