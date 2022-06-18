.data
.text
.globl main

main:
        lui $s0, SFR_Bruh

        lw $t0, TRISB($s0)
        ori $t0, $t0, 0x000F
        sw $t0, TRISB($s0)
        
        lw $t0, TRISE($s0)
        andi $t0, $t0, 0xFFF0
        sw $t0, TRISE($s0)

loop:
        lw $t0, PORTB($s0)
        andi $t0, $t0, 0x000F #Clean all the bits that we don't neeed
        
        lw $t1, LATE($s0)
        andi $t1, $t1, 0xFFF0 #Clean all the bits that we need
        or $t1, $t1, $t0 #concatnate the led with the dip-switch
        sw $t1, LATE($s0) #change the registers

        j loop

        li $v0, 0
        jr $ra