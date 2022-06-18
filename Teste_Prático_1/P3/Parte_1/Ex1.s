.equ SFR_BASE_HI, 0xBF88
.equ TRISE, 0x6100
.equ PORTE, 0x6110
.equ LATE, 0x6120
.equ TRISB, 0x6040
.equ PORTB, 0x6050
.equ LATB, 0x6060
.data
.text
.globl main

main:   
        lui     $t0, SFR_BASE_HI
        lw      $t1, TRISE($t0)
        andi    $t1, $t1, 0xFFFE 
        sw      $t1, TRISE($t0)   #Saida se estiver a 0

        
        lw       $t1, TRISB($t0)
        ori     $t1, $t1, 0x0001 
        sw       $t1, TRISB($t0)   #Entrada se tiver a 1

        # O TRIS diz ao processador se aquele porto é uma entrada ou saida
        # O registo LAT é usado para escrever no controlador valores
        # O registo PORT é usado para ler no controlador os valores

loop:
        lw      $t1, PORTB($t0)
        andi    $t1, $t1, 1
        lw      $t2, LATE($t0)
        andi    $t2, $t2, 0xFFFE
        or      $t2, $t2, $t1
        sw      $t2, $t2, $t1
        j loop
        li $v0, 0
        jr $ra
        