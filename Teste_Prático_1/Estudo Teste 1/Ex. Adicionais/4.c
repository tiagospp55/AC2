#include <detipic32.h>

void delay(int ms);

int main(void){
    TRISE = TRISE & 0xFFF0
    LATE = LATE $ 0xFFF0
    char = c;
    while(1){
        c = getChar();
        switch(c){
            case '0':{
                LATE = LATE | 0x0001;    
                sendtodisplays(c);
                break;
            }
            case '1':
            {
                LATE = LATE | 0x0002;
                sendtodisplays(c);
                break;
            }
            case '2'{
                LATE = LATE | 0x0003;
                sendtodisplays(c);
                break;
            }
            case '3'{
                    LATE = LATE | 0x0004;
                    sendtodisplays(c);
                break;
            }
            default: {
                
                sendtodisplays(c);
                break;
            }
        }
        
    }
    
}