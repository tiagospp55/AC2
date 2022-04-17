.equ SFR_BASE_HI, 0xBF88	# 16 MSbits of SFR area
.equ TRISE, 0x6100			# TRISE address is 0xBF886100
.equ PORTE, 0x6110			# PORTE address is 0xBF886110
.equ LATE, 0x6120			# LATE address is 0xBF886120

.data
.text
.globl main

main:
		lui 	$t1, SFR_BASE_HI		#

		lw		$t2, TRISE($t1)			# READ
		andi	$t2, $t2, 0xFFF0		# MODIFY RE0 - Saída QUando se coloca algo a 0, significa saida no microcontrolador
		sw		$t2, TRISE($t1)			# WRITE

		lw		$t2, TRISB($t1)			# READ
		ori		$t2, $t2, 0x0001		# MODIFY RB0 - Quandos se coloca o bit a 1 significa entrada no microcontrolador
		sw		$t2, TRISB($t1)			# WRITE

loop:
		
		
		j loop;

end:	
		jr $ra