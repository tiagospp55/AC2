# int main(void){
#  char c;
#  do {
#   c = inkey();
#   if( c != 0 )
#   putChar( c );
#  else
#   putChar('.');
#  } while( c != '\n' );
#  return 0;
# }

.data
.equ inkey, 1
.equ putChar, 3
.text
.globl main

main:
do:		li	$v0, inkey
		syscall
		move $a0, $v0
while1:	beq	$a0, 0, do			#while((c = inkey()) == 0)
		beq $a0, '\n', while2	#if(c != '\n')
		li $v0, putChar
		 syscall
while2:	bne $a0,'\n', do		#while(c != '\n')
		jr $ra



