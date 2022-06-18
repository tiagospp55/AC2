.equ resetCoreTimer, 12
.equ readCoreTImer, 11
.equ putChar, 3
.equ PrintInt, 6
.equ Counter, $t0
.data
.text
.globl main

main:   li $t0, 0 
loop1:  li $v0, resetCoreTimer
        syscall
loop2:  li $v0, readCoreTImer
        syscall
        bge $v0, 200000, endloop2 
        j loop2
endloop2:

        li $v0, PrintInt
        li $a1, 0x0004000A
        move $a0, Counter
        syscall


        addi Counter,Counter, 1

        li $v0, putChar
        li $a1, 10
        li $a0, '\r'
        syscall

        j loop1

        li $v0, 0
        jr $ra
