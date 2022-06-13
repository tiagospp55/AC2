#include <detpic32.h>

int main(void){
    int ovs_factor[2] = { 16,4 };
    int PBLK = 20*10^6;
    int ovs = 0; // 0 (x16, standard speed) ou 1 (x4, high speed)
    U2MODEbits.ON = 0; // desativa a UART
    U2MODEbits.BRGH = ovs; // configura fator de sobre amostragem (0 ou 1)
    U2BRG = round_div(PBCLK,ovs_factor[ovs] * baud_rate) – 1;
    U2MODEbits.PDSEL = 3; // 0 (8N), 1 (8E), 2 (8O), 3 (9N) --- ver manual
    U2MODEbits.STSEL = 0; // 0 (1 stop bits), 1 (2 stop bits) --- ver manual
    U2STAbits.UTXEN = 1; // ativa transmissão (ver nota abaixo)
    U2STAbits.URXEN = 1; // ativa receção (ver nota abaixo)
    U2MODEbits.ON = 1; // ativa UART

    

    EnableInterrupts();
    
}
