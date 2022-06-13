.data
.text
.globl main


delay:
        move $t0, $a0
for:    
        ble $t0, 0, endfor
        li $v0, resetCoreTimer
        syscall
read:
        li $v0, readCoreTimer
        syscall
        blt $v0, 40000, read
        addi $t0, $t0, -1
        j for
endfor:
        jr $ra


main:   
        addiu $sp, $sp, -12
        sw $ra, 0($sp)
        sw $s0, 4($sp)
        sw $s1, 8($sp)

        lui $s0, SFR_BASE_HI

        lw $t0, TRISB($s0)
        ori $t0, $t0, 0x000F
        sw $t0, TRISB($s0)
        
        lw $t0, TRISE($s0)
        andi $t0, $t0, 0xFF7F
        sw $t0, TRISE($s0)

        
        lw $t0, LATE($s0)
        ori $t0, $t0, 0x0080
        sw $t0, LATE($s0)
loop:
        
        lw $s1, PORTB($s0)
        xori $s1, $s1, 0xFFFF
        andi $s1, $s1, 0x000F
        
if:     bgt $s1, 0x09, else
        addi $s1, $s1, 0x30
        j endif

else:   addi $s1, $s1, 0x37
endif:  move $a0, $t0
        li $v0, putChar
        syscall

        lw $t3, LATE($s0)
        xori $t3, $t3, 0x0080
        sw $t3, LATE($s0)

        li $a0, 125 
        jal delay
        j loop
endloop:
        
        lw $ra, 0($sp)
        lw $s0, 4($sp)
        lw $s1, 8($sp)
        addiu $sp, $sp, 12
        li $v0, 0
        jr $ra
        


        





        
