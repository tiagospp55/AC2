#include <detpic32.h>

int main(void){


    UxSTAbits.UTXISEL = 0; // quando se pede interrupção do lado tx (ver manual)
    UxSTAbits.URXISEL = 0; // quando se pede interrupção do lado rx (ver manual)
    IPCybits.UxIP = 1; // prioridade da interrupção (1 a 6)
    IFSybits.UxTXIF = 0; // limpar pedido de interrupção do lado tx
    IFSybits.UxRXIF = 0; // limpar pedido de interrupção do lado rx
    IFSybits.UxEIF = 0; // limpar pedido de interrupção por causa de erros
    IECybits.UxTXIE = 0; // desativa pedidos de interrupção na transmissão
    IECybits.UxRXIE = 1; // ativa pedidos de interrupção na receção
    IECybits.UxEIE = 0; // desativa pedidos de interrupção em caso de erro
    if (use_interrupts != 0){
            U2STAbits.UTXISEL = 0;
            U2STAbits.urxisel = 0;

    }
}


{
    int c;
    if(U2STAbits.OEER !0){
        u2staBITS.oerr = 0;   
    }
    while( U2STAbits.URXDA == 0); // Espera até que o buffer de receção deixe de estar vvazio
    c = U2XREG;
    return (c & 0xFF);
}

