/*H**********************************************************************
* FILENAME :        main.c             DESIGN REF: 
*
* DESCRIPTION :
*       UART module example for RexPIC-8 (PIC16F1517) 
*
* PUBLIC FUNCTIONS :
*
* NOTES :
*      
*
*       Copyright Swiss TI Lab 2017
* 
* LICENSE:
*       CC-BY-SA  
* 
* AUTHOR :    Kevin Ceresa        START DATE :    09 Oct 2017
*
* CHANGES :
*
* REF NO    VERSION     DATE        WHO     DETAIL
* 1         V1I1        09Oct17     K.C.    Released
*
*H*/

//DEFINE
#define _XTAL_FREQ 8000000 //8MHz clock
//INCLUDE
#include <xc.h>
#include <stdio.h>

/*------------------------------------------------- UART_Init ------
|  Function UART_Init
|
|  Purpose:  Initialize the internal UART module 
|
|  Parameters:
|      -
|
|  Returns:  -
*-------------------------------------------------------------------*/
void UART_Init()
{
    //RC6 output
    TRISCbits.TRISC6 = 0;
    ANSELC = 0;
    //RC7 input
    TRISCbits.TRISC7 = 1;
        
    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUDCON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TXSTA = 0x24;

    // Baud Rate = 9600; SPBRGL 207; 
    SPBRGL = 0xCF;

    // Baud Rate = 9600; SPBRGH 0; 
    SPBRGH = 0x00;
}


/*------------------------------------------------- UART_Write ------
|  Function UART_Write
|
|  Purpose:  Send a character over the UART internal module 
|
|  Parameters:
|      txData:  -- IN --    Char input
|      
|  Returns:  -
*-------------------------------------------------------------------*/
void UART_Write(char txData)
{
    while(!TRMT)

    TXREG = txData;    // Write the data byte to the USART.
}

//Variable
const char buffer1[20] = "Swiss TI LAB ";
char buffer2[20];
const int data = 2017;
char read;

/*------------------------------------------------------- main -----
|  Function main
|
|  Purpose:  main function -> send some data
|
|  Parameters: -   
|
|  Returns: -
*-------------------------------------------------------------------*/
void main()
{
    UART_Init();
    
    __delay_ms(1000);
    //Send some character
    UART_Write('\n');
    UART_Write('S');
    UART_Write('T');
    UART_Write('L');
    UART_Write('\n');
        
    //Send a string
    for (int a=0; buffer1[a] != '\0'; a++)
    {
        UART_Write(buffer1[a]);
    }
        
    //Send a number (int)
    sprintf(buffer2,"%d",data);
    
    for (int a=0; buffer2[a] != '\0'; a++)
    {
        UART_Write(buffer2[a]);
    }
        
    while(1)
    {
        if (RCIF == 1)
        {
            read = RCREG;
            //Send back the data
            UART_Write(read);
            UART_Write('\n');
        }
            
    }
        
}
