.data
.text
.globl main
.equ putChar, 3
.equ getChar, 2
.equ state, 0
.equ cnt, 0
.equ up, 1
.equ down, 0
.equ printInt,
.equ inkey, 

main: 
    li $s0, 0
    li $s1, down
loop:

    addiu $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 0($sp)
    sw $s1, 0($sp)
    
    li $v0, putChar
    li $a0, '\r'
    syscall

    li $a1, 0x0003000A
    li $v0, printInt
    move $a0, $s0
    syscall

    li $v0, putChar
    li $a0, '\t'
    syscall

    li $a1, 0x00080002
    li $v0, printInt
    move $a0, $s0
    syscall

    li $a0, 5
    jal wait

    li $v0, inkey
    syscall

    move $t0, $v0
if:
    bne $t0, '+', else
    li $s1, up
    j endif
else:
    bne $t0, '-', endif
    li $s1, down

endif: 
    
if1:
    bne $s1, up, else1
    addi $s0, $s0, 1
    andi $s0, $s0, 0xFF
    j endif1
else1:
    addi $s0, $s0, -1
    andi $s0, $s0, 0xFF

endif1: 
    beq $t0, 'q', endloop
    j loop

endloop:
    
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    
    li $v0, 0
    jr $ra


wait: 
    li $t0, 0
    li $t2, 515000 
    mul $t1, $t2, $a0
for:
    bge $t1, $t0, endfor
    addi $t0, $t0, 1
    j for
endfor: 
    jr $ra
