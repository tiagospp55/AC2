.data
.text
.globl main

main:
    lui $t0 SFR_BASE_HIGH
    

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFFE
    sw $t1, TRISE($t0)

    
    lw $t2, TRISD($t0)
    ori $t2, $t2, 0x0100
    sw $t2, TRISD($t0)

loop:
    lw $t1, PORTD($t0)
    andi $t1, $t1, 0x0100
    lw $t2, LATE($t0)
    andi $t2, $t2, 0xFFFE
    or $t2, $t2, $t1
    sw $t1, LATE($t0)
    j loop

endloop: 
li $v0, 0 
jr $ra


