# MIPS PROGRAM Helloworld 
# By jskyzero 2017/04/01

# A MIPS Program Structure 
# just plain text file with data declaration and program code 

# Data Declaration
# declares cariables names used in program 
# storage allocated in main memory
  .data     # Data section
# name:     storage_type  value(s)
out_string: .asciiz       "Hello World!\n"


# Code 
# contails program code 
# start point for code e.g.ecution label main:
# ending point of main code should use exit system call (this time not use)
  .text     # Text section
main:       # Start of code section 
  li $v0, 4 # System call to print out_string
  la $a0, out_string
  syscall
