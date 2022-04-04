.data
.text
.globl main
.equ putChar, 3
.equ getChar, 2
main: 

do: 
    li $v0, getChar
    syscall
    move $a0, $v0
    li $v0, putChar
    syscall
if:
    beq $a0,, '\n', endwhile
    j do
endwhile:
    li $v0, 0 
    jr $ra