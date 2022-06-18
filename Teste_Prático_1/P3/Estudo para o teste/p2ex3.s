.data
.text
.globl main



delay:                                  # void delay(int ms) {
        move    $t0, $a0                #       $t0 = ms;
        
for:    ble     $t0, 0, endfor          #       for(; ms > 0; ms--) {
        li      $v0, RESET_CORE_TIMER   #               
        syscall                         #               resetCoreTimer();
read:   li      $v0, READ_CORE_TIMER    #
        syscall                         #               readCoreTimer();
        blt     $v0, 20000, read        #               while(readCoreTimer() < K);
        addi    $t0, $t0, -1            #               ms--;
        j       for                     #       }
endfor:                                 #       
        jr      $ra                     # }



main: 
    
    addiu $sp, $sp, -8
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    
    lui $t0, SFR_Bruh

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFF0
    sw $t1, TRISE($t0)

    lw $ $t1, TRISB
    ori $t1, $t1, 0x000F
    sw $t1, TRISB($t0)
    # s0 é o counter
    li $s0, 0

loop:

    lw $t2, PORTB
    andi $t2, $t2, 0x0008

if:
    bne $t2, 0, else
    addi $s0, $s0, -1
    j endif
else: 
    addi $s0, $s0, 1
endif:
    lw $t1, LATE($t0)
    andi $t1, $t1, 0xFFF0
    andi $s0, $s0, 0x000F
    or $t1, $t1, $s0
    sw $t1, LATE($t0)
    addi $s0, $s0, 1

    li $a0, 1000
    jal delay 

    j loop
endloop:

    lw $ra, 0($t0)
    lw $s0, 4($t0)
    addi $sp, $sp, 8
    li $v0, 0
    jr $ra
