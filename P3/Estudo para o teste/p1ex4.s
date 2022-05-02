.data
.text
.globl main


main:

    li $t0, STR_BRUH

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFF0
    sw $t1, TRISE($t0)


    lw $t2, TRISB($t0)
    ori $t2, $t2, 0x000F
    sw $t2, TRISB($t0)

loop:
    lw $t1, PORTE($t0)
    andi $t1, $t1, 0x000F
    xori $t1, $t1, 0x0009
    lw $t2, LATE($t0)
    andi $t2, $t2, 0xFFF0
    or $t2, $t2, $t1
    sw $t2, LATE($t0)

    j loop
endloop: 
    li $v0, 0
    jr $ra
