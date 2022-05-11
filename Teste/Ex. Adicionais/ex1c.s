.data
.text
.globl main

main:
        lui $s0, SFR_Bruh

        lw $t0, TRISB($s0)
        ori $t0, $t0, 0x000F
        sw $t0, TRISB($s0)
        
        lw $t0, TRISE($s0)
        andi $t0, $t0, 0xFF00
        sw $t0, TRISE($s0)

loop:
        lw $t0, PORTB($s0)
        andi $t0, $t0, 0x000F
        move $t1, $t0
        sll $t0, $t0, 4
        xori $t1, $t1, 1
        andi $t1, $t1, 0x000F
        or $t0, $t1, $t0

        lw $s0, LATE($s0)
        andi $s0, $s0, 0xFF00
        or $s0, $s0, $t0
        sw $S0, LATE($s0)

        j loop
endloop:
        li $v0, 0
        jr $ra