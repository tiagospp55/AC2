  .equ    RESET_CORE_TIMER, 12
        .equ    READ_CORE_TIMER, 11
        .equ putChar, 3
        .equ printInt, 6
        .data
        .text
        .globl main


main:                                   
        addiu   $sp, $sp, -16           
        sw      $ra, 0($sp)            
        sw      $s0, 4($sp)            
        sw      $s1, 8($sp)          
        sw      $s2, 12($sp)      
        li      $s0, 0          
        li      $s1, 0                  
        li      $s2, 0                 


while:  li $a0, 100
        jal delay

        li $a0, '\r'
        li $v0, putChar
        syscall

        addi $$s0, $s0, 1
        move $a0, $s0
        li $a1, 0x0005000A  
        li $v0, printInt
        syscall

if:     rem $t0, $s0,2
        bne $t0, 0, endif           
        addi $s1, $s1, 1   
endif:

if2:  
        rem $t0, $s0, 10
        bne $t0, 0, endif
        addi $s2,$s2, 1
endif2:
                                        
        li      $a0, ' '                
        li      $v0, putChar            
        syscall                         
        move    $a0, $s1                
        li      $a1, 0x0005000A        
        li      $v0, printInt          
        syscall                       
                                       
        li      $a0, ' '               
        li      $v0, putChar           
        syscall                        
        move    $a0, $s2               
        li      $a1, 0x0005000A        
        li      $v0, printInt           
        syscall                                  
                                        
        j       while                   
        li      $v0, 0                  
        lw      $ra, 0($sp)                  
        lw      $s0, 4($sp)              
        lw      $s1, 8($sp)             
        lw      $s2, 12($sp)            
        addiu   $sp, $sp, 16            
        jr      $ra                     

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