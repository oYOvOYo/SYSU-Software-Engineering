# 要求：
# 从键盘输入10个无符号字数并从大到小进行排序，排序结果在屏幕上显示出来。
# 暂时不想把时间花在 无符号字 读入，这种问题，不管是用double存还是str存再转化都很烦

  .data
array:        .space  40 # 10 word and 1 word 4 bit
welcome_str:  .asciiz "please enter 2 32-bit signed num\n"
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
  li $t0, 0  # initial value 
  li $t1, 8  # initial end value 
read_int:
  slt $t3, $t0, $t1 # $t0 < $t1 => $t3 = 0
  beq $t3, $zero, finished_read # $t0 < $t1 => loop 
  li $v0, 5 # use system call to read num
  syscall
  add $t2, $s0, $t0 # store target address
  sw $v0, 0($t2) # write read_num to $t2 (array[i]) 
  addi $t0, $t0, 4 # update i
  j read_int
finished_read:  

# print sorted values 
  li $t0, 0
  li $t1, 8
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
