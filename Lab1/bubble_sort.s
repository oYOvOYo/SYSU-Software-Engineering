# 要求：
# 从键盘输入10个无符号字数并从大到小进行排序，排序结果在屏幕上显示出来。
# 暂时不想把时间花在 无符号字 读入，这种问题，不管是用double存还是str存再转化都很烦

  .data
welcome_str: .asciiz "welcome"
array: .space 40
separate:.asciiz "  "
str:.asciiz "The answer is:\n"

  .text
main:
  la $s0, array

  li $t0, 0
  li $t1, 40
read_int:
  slt $t3, $t0, $t1
  beq $t3, $zero, finished_read # $t0 < $t1
  li $v0, 5
  syscall
  add $t2, $s0, $t0 # $t2 
  sw $v0, 0($t2)
  addi $t0, $t0, 4
  j read_int
finished_read:

 addi $s1,$zero,9    #第一重循环 i = 9
loop1:               #进入第一重循环
 la $s0, array       #读取数组头地址
 addi $s2,$zero,0    #第二重循环 j = 0
loop2:               #进入第二重循环
 lw   $t0,0($s0)       #t0取数组当前位置的数 array[j]
 lw   $t1,4($s0)       #t1取下一个数 array[j+1]
 slt $t2,$t1,$t0       #if(t1 < t0) t2 = 1; else t2 = 0;
 bne $t2,$zero,skip	#if (t0>t1) goto skip; else if (t0<t1) swap                      
 sw   $t1,0($s0)        #把t1的数（大数）放在前面
 sw   $t0,4($s0)        #把t0的数（小数）放在后面
skip:                   #跳过当前的交换
 addi $s2,$s2,1         #j++
 addi $s0,$s0,4         #array[j]
 slt  $t2,$s2,$s1       
 bne $t2,$zero,loop2    #if j<i,goto loop2
 addi $s1,$s1,-1        #i--
 bne $s1,$zero,loop1    #下一次循环开始

 la    $a0,str       #$a0存字符串的地址
 li    $v0,4         #输出字符串
 syscall             #系统调用

 la $s0, array        #$s0存数组头的地址
 addi $t0,$zero,10    #未输出数字个数
output:               #输出10个数的循环
 lw $a0,0($s0)        #从数组当前位置读取数字到$a0
 li $v0,1             #系统调用打印数字
 syscall              #系统调用
 la    $a0,separate   #用“ ”分隔数字
 li    $v0,4          #输出空格“ ”
 syscall              #系统调用
 addi $t0,$t0,-1      #未输出数字减一
 addi $s0,$s0,4       #当前数组地址+4指向数组下一个数字
 bne $t0,$zero,output #如果10个数字没有输出完继续循环输出


#   li $t0, 0
#   li $t1, 4
# print_int:
#   slt $t3, $t0, $t1
#   beq $t3, $zero, finished_print
#   li $v0, 1
#   add $t2, $s0, $t0
#   ld $a0, 0($t2)
#   syscall
#   addi $t0, $t0, 4
#   j print_int
# finished_print:
