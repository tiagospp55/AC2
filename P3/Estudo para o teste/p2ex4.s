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
    
    addiu $sp, $sp, -12
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)


    lui $s0, SFR_Bruh

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFF0
    sw $t1, TRISE($t0)

    lw $ $t1, TRISB
    ori $t1, $t1, 0x000F
    sw $t1, TRISB($t0)
    # s0 é o counter
    li $s1, 0

loop:
    
    lw $t0, PORTB($s0)
    andi $t0, $t0, 0x0002

    if: 
        beq $t0, 0x0002, else
        srl $s1, $s1, 1
        j endif
    else:
        sll $s1, $s1, 1
endif:

if2: 
    bne $s1, 0x0010, endif2
    li $s1, 1
endif2: 
    lw $t2, LATE($t0)
    andi $t2, $t2, 0xFFF0
    or $t2, $t2, $s1
    sw $t2, TRISE($t0)

    


    
    
 


