# MIPS PROGRAM Helloworld 
# By jskyzero 2017/04/01

  .data     # Data section
out_string: .asciiz "Hello World!\n"

  .text     # Text section
main:       # Start of code section 
  li $v0, 4 # System call to print out_string
  la $a0, out_string
  syscall