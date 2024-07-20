
// PIC16F884 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 20000000
int count =0;

void UART_Init(void) {
    // Set baud rate to 9600 for 20MHz oscillator, high-speed baud rate
    TXSTAbits.BRGH = 1;    // High-speed baud rate
    unsigned int spbrg_value = ((_XTAL_FREQ / 16) / 9600) - 1;
    SPBRG = spbrg_value;

    TXSTAbits.SYNC = 0;    // Asynchronous mode
    RCSTAbits.SPEN = 1;    // Enable serial port (configures RX and TX pins as serial port pins)
    TXSTAbits.TXEN = 1;    // Enable transmission
    RCSTAbits.CREN = 0;    // Disable continuous reception
    TXSTAbits.TX9 = 0;     // Disable 9-bit transmission

    TRISCbits.TRISC6 = 0;  // Set RC6/TX pin as output
    TRISCbits.TRISC4 = 0;  // Set RC4 as output to enable MAX3485
    PORTCbits.RC4 = 1;     // Set RC4 to high
}

void UART_send_char(unsigned char data)  
{
    while(!TXIF);  // hold the program till TX buffer is free
    TXREG = data; //Load the transmitter buffer with the received value
    while(!TRMT);
}


void main(void) {
    UART_Init(); // Initialize UART

    while(1) {
        UART_send_char('A');
        __delay_ms(400);
        count++; 
    }
}