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
        lui $t0, SFR_BASE_HI #
# A configuração de cada um dos bits de um porto como entrada
# ou saida é efetuado pelo TRIS, sendo que se o seu bit estiver a 1, é uma entrada e se estiver a 0 é uma saida

# TRIS = 0 => saida
# TRIS = 1 => entrada

# O registo LAT é utilizado para escrever um valor no porto configurado como saida
# O registo PORT é para ler um valor do porto configurado como entrada

        lw $t1, TRISE($t0)   # Saida - 0
        andi $t1, $t1, 0xFFFE
        sw $t1, TRISE($t0)

        lw $t1, TRISB($t0)   # Entrada - 1
        ori $t1, $t1, 0x0001
        sw $t1, TRISB($t0)
        
loop: 
        lw $t1, PORTB($t0)
        andi $t1, $t1, 0x0001
        xori $t1, $t1, 0x0001 #  Negar o valor da entrada
        lw $t2, LATE($t0)
        andi $t2, $t2, 0xFFFE
        
        or $t2, $t2, $t1
        sw $t2, LATE($t0)
        
        j loop

        li $v0, 0
        jr $ra
