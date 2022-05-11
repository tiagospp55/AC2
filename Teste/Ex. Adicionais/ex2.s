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
        jr      $ra          

main: 
    lui $s0, SFR_Bruh

    lw $t0, TRISE($s0)
    andi $t0, $t0, 0xFFF0
    sw $t0, TRISE($s0)

    lw $t0, LATE($s0)
    andi $t0, $t0, 0xFFF0
    sw $t0, TRISE($s0)

loop:
        li $v0, putChar
        syscall
        move $s1, $v0

if:
        beq $s0, '0', else
        lw $t1, LATE($0)
        ori $t1, 0x000F
        sw $t1, LATE($s0)
        j endif
else:
        beq $s0, '1', else1
        lw $t1, LATE($0)
        ori $t1, 0x0001
        sw $t1, LATE($s0)
        j endif
else1:
        beq $s0, '2', else2
        lw $t1, LATE($0)
        ori $t1, 0x0002
        sw $t1, LATE($s0)
        j endif
else2:
        beq $s0, '3', nothing
        lw $t1, LATE($0)
        ori $t1, 0x0003
        sw $t1, LATE($s0)
        j elsif
nothing:
        lw $t1, LATE($0)
        ori $t1, 0x000F
        sw $t1, LATE($s0)
        li $a0, 1000
        jal delay
endif:
        
        lw $t1, LATE($0)
        andi $t1, 0xFFF0
        sw $t1, LATE($s0)

        j loop

endloop:
        li $v0, 0
        jr $ra
    