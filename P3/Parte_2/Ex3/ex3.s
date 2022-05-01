        .equ    RESET_CORE_TIMER, 12
        .equ    READ_CORE_TIMER, 11
        .equ    SFR_BASE_HI, 0xBF88
        .equ    TRISE, 0x6100
	    .equ    PORTE, 0x6110
	    .equ    LATE, 0x6120
        .equ    TRISB, 0x6040
	    .equ    PORTB, 0x6050
        .data
        .text
        .globl main



main:

        addiu   $sp, $sp, -12           #       abrir espaco na stack
        sw      $ra, 0($sp)             #       salvaguardar $ra
        sw      $s0, 4($sp)             #       salvaguardar $s0
        sw      $s1, 8($sp)             #       salvaguardar $s1

        lui $s0, SFR_BASE_HI

        lw $t1, TRISB($s0)
        andi $t1, $t1, 0xFFF0
        sw $t1, TRISB($s0)

        lw $t1, TRISE($s0)
        ori $t1, $t1, 0x000F
        sw $t1, TRISE($s0)

        li $s1, 0
    
loop:

if:

        

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