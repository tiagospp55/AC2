#void delay(unsigned int ms)
#{
#   resetCoreTimer();
#   while(readCoreTimer() < K * ms);
#}

.equ K, 20000



delay: 
        li $v0, resetCoreTimer
        syscall
while:  li $v0, readCoreTimer
        syscall
        mul $t1, K, ms

        bge $v0, K*ms, endwhile
        j while
endwhile:

