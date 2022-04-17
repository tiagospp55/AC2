# int main(void)
# {
# int value;
# while(1)
# { 
# printStr("\nIntroduza um inteiro (sinal e módulo): ");
# value = readInt10();
# printStr("\nValor em base 10 (signed): ");
# printInt10(value);
# printStr("\nValor em base 2: ");
# printInt(value, 2);
# printStr("\nValor em base 16: ");
# printInt(value, 16);
# printStr("\nValor em base 10 (unsigned): ");
# printInt(value, 10);
# printStr("\nValor em base 10 (unsigned), formatado: ");
# printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
# }
# return 0;
# }

	.data

		.equ printStr,8
		.equ readInt10,5
		.equ printInt,6
		.equ printInt10,7

ler:		.asciiz "\nIntorduza um numero (sinal e módulo): \n"
lidob2:		.asciiz "\nValor lido, em base 2: \n"
lidob16:	.asciiz "\nValor lido, em base 16: \n"
lidob10u:	.asciiz "\nValor lido, em base 10 unsigned: \n"
lidob10s:	.asciiz "\nValor lido, em base 10 signed: \n"

		.text
		.globl main
main:	
while:	la		$a0, ler
		li  	$v0, printStr
		syscall
		li  	$v0, readInt10
		syscall					#"\nIntorduza um numero (sinal e módulo): \n"
		move 	$t0, $v0

		la		$a0, lidob2
		li  	$v0, printStr
		syscall					#"\nValor lido, em base 2: \n"
		move	$a0, $t0		
		li 		$a1, 2			#conversão para binário
		li 		$v0, printInt 
		syscall

		la		$a0, lidob16
		li 		$v0, printStr
		syscall					#"\nValor lido, em base 16: \n"
		move	$a0, $t0
		li 		$a1, 16			#conversão para HEX
		li 		$v0, printInt
		syscall

		la		$a0, lidob10u
		li 		$v0, printStr
		syscall					#"\nValor lido, em base 10 unsigned: \n"
		move	$a0, $t0
		li 		$a1, 10			#conversão para decimal unsigned
		li 		$v0, printInt
		syscall

		la		$a0, lidob10s
		li 		$v0, printStr
		syscall					#"\nValor lido, em base 10 signed: \n"
		move	$a0, $t0
								#não há conversão porque o numero int pelo utilizador já vem sinalizado
		li 		$v0, printInt10
		syscall

		j while
		jr	$ra
