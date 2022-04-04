#int main(void)
#{
#char c;
#do {
#   c = inkey();
#   if( c != 0 )
#       putChar( c );
#   else
#       putChar('.');
#} while( c != '\n' );
#return 0;
#}

.data
.text
.equ inkey, 1
.equ putChar, 3
.globl main

main: 
do:
    li $v0, inkey
    syscall
    move $a0, $v0

if: beq $a0, 0, else
    li $v0, putChar
    syscall
    j while 
else:
    li $a0, '.'
    li $v0, putChar
    syscall
while:
    beq $a, '\n' ,do
    li $v0, 0
    jr $ra