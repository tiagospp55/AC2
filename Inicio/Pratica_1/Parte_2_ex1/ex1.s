# int main(void)
# {
# char c;
# do
# {
# c = getChar();
# putChar( c );
# } while( c != '\n' );
# return 0;
# }

.data
.equ GetChar,2
.equ putChar, 3
.text
.globl main
main:
do:     li $v0, GetChar
        syscall
        move $a0, $v0
        syscall
        beq $a0, '\n', while
		li	$v0, putChar
while:  bne $a0,'\n', do
        li $v0, 0
        jr $ra