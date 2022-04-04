#int main(void)
#{
#   int counter = 0;
#   while(1)
#   {
#       resetCoreTimer();
#       while(readCoreTimer() < 200000);
#       printInt(counter++, 10 | 4 << 16); // Ver nota1
#       putChar('\r'); // cursor regressa ao inicio da linha
#   }
#return 0;
#}

.data
.text
.globl main

main:
li $t0, 0 

while:
    li $v0, resetCoreTimer
    syscall
    while2: 
        li $v0, readCoreTimer
        syscall
        bge $v0, 200000, endwhile2
        j while2
endwhile2:
    li $v0, printInt
    li $a0, $t0
    addi $t0, $t0, 1
    li      $a1, 0x0004000A         #               $a1 = 10 | 4 << 16
    syscall

    li      $v0, printInt           #               $v0 = 6;
    syscall                         #               printInt(++counter, 10 | 4 << 16)
    li $v0, putChar
    li $a0, '\r'
    syscall


endwhile:
    j while

    li $v0, 0
    jr $ra