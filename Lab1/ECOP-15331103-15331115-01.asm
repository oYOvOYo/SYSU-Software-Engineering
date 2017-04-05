
###################################################################
#
#  从键盘输入10个无符号字数并从大到小进行排序，排序结果在屏幕上显示出来
#
###################################################################
.globl main
.text                #代码段声明
main:
 la $s0, array       #$s0存数组头的地址
 addi $t0,$zero,10   #未读数据个数
input:               #读取10个数的循环
 li $v0,5            #系统调用输入数据
 syscall             #系统调用
 sw $v0,0($s0)       #把输入的数字存进去数组
 addi $t0,$t0,-1     #未读数据-1
 addi $s0,$s0,4      #当前数组地址+4指向数组下一个数字
 bne $t0,$zero,input #如果未读数据不为0继续循环

 addi $s1,$zero,9    #第一重循环 i = 9
loop1:               #进入第一重循环
 la $s0, array       #读取数组头地址
 addi $s2,$zero,0    #第二重循环 j = 0
loop2:               #进入第二重循环
 lw   $t0,0($s0)       #t0取数组当前位置的数 array[j]
 lw   $t1,4($s0)       #t1取下一个数 array[j+1]
 slt $t2,$t1,$t0       #if(t1 < t0) t2 = 0; else t2 = 1;
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

.data                 #数据段声明
array:.word 12,11,9,4,5,6,7,0,0,1
separate:.asciiz "  "
str:.asciiz "The answer is:\n"
