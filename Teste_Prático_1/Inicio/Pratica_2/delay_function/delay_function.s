.equ resetCoreTimer, 12
.equ readCoreTImer, 11
.equ putChar, 3
.equ PrintInt, 6
.equ Counter, $t0
.equ MS, $t1
.equ k, 20000
.data
.text
.globl main

main:   li Counter, 0 
        li MS, 3000
loop1: 
        move $a0, MS
        jal delay

        li $v0, PrintInt
        li $a1, 0x0004000A
        move $a0, Counter
        syscall


        addi Counter,Counter, 1

        li $v0, putChar
        li $a0, '\r'
        syscall

        j loop1

        li $v0, 0
        jr $ra






# ------------bruh-----------------
delay:  mul $a0, $a0, k
        li $v0, resetCoreTimer
        syscall
loop2:  li $v0, readCoreTImer
        syscall
        bge $v0, $a0, endloop2
        j loop2
endloop2: jr $ra
