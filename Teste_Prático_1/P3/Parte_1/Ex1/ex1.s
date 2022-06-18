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
        lui $t1, SFR_BASE_HI #
# A configuração de cada um dos bits de um porto como entrada
# ou saida é efetuado pelo TRIS, sendo que se o seu bit estiver a 1, é uma entrada e se estiver a 0 é uma saida

# TRIS = 0 => saida
# TRIS = 1 => entrada

# O registo LAT é utilizado para escrever um valor no porto configurado como saida
# O registo PORT é para ler um valor do porto configurado como entrada


        lw $t2, TRISE($t1) # READ (Mem_addr = 0xBF880000 + 0x6100)
        andi $t2, $t2, 0xFFFE # MODIFY (bit0=0 (0 means OUTPUT))
        sw $t2, TRISE($t1) # WRITE (Write TRISE register)


        lw $t2, TRISB($t1) # READ (Mem_addr = 0xBF880000 + 0x6100)
        li $t4, 0x0001
        or $t2, $t2, $t4 # MODIFY (bit0=1 (1 means Input))
        sw $t2, TRISB($t1) # WRITE (Write TRISE register)

loop: 
        lw $t2, PORTB($t1)
        andi $t2, $t2, 0x0001   # Coloca a 0 todos os bits excepto o bit 0, para preservar o seu valor
    
        lw $t3, LATE($t1)
        andi $t3, $t3, 0xFFFE # Colocar o ultimo bit a 0
        or $t2, $t2, $t3

        sw $t2, LATE($t1)
        j loop

        li $v0, 0
        jr $ra


