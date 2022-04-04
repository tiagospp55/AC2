#int main(void)
#{
#int value;
#while(1)
#{
#printStr("\nIntroduza um inteiro (sinal e módulo): ");
#value = readInt10();
#printStr("\nValor em base 10 (signed): ");
#printInt10(value);
#printStr("\nValor em base 2: ");
#printInt(value, 2);
#printStr("\nValor em base 16: ");
#printInt(value, 16);
#printStr("\nValor em base 10 (unsigned): ");
#printInt(value, 10);
#printStr("\nValor em base 10 (unsigned), formatado: ");
#printInt(value, 10 | 5 << 16); // ver nota de rodapé 3
#}
#return 0;
#}


.data
.text
.equ printStr, 1
.equ putChar, 3
.equ printInt, 6
.equ readInt10, 5

.ascizz texto1, "Escolhe um número"  #Não sei se é assim que se faz uma string
.globl main

main: 

while:
    la $a0, texto1
    li $v0, printStr
    syscall

    li $v0, readInt10
    syscall

    move $a0, $v0
    li $v0, printInt
    syscall

    j while

    li $v0, 0 
    jr $ra
