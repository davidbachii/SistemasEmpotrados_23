#include "../include/leon3_uart.h"

//Estructura de datos que permite acceder a los registros de la //UART de LEON3

struct UART_regs
{
	/** \brief UART  Data Register */
	volatile uint32_t Data;   	/* 0x80000100 */
	/** \brief UART  Status Register */
	volatile uint32_t Status; 	/* 0x80000104 */
	/** \brief UART  Control Register */
	volatile uint32_t Ctrl; 	/* 0x80000108 */
	/** \brief UART  Scaler Register */
	volatile uint32_t Scaler; 	/* 0x8000010C */
};

//!  LEON3 UART A Transmit FIFO is FULL
#define LEON3_UART_TFF (0x200)

//!  LEON3 UART A Transmit FIFO is EMPTY
#define LEON3_UART_TFE (0x004)

struct   UART_regs * pLEON3_UART_REGS= (struct   UART_regs *) 0x80000100;



int8_t leon3_putchar(char c)
{

	uint32_t write_timeout=0;

	while((LEON3_UART_TFF & pLEON3_UART_REGS->Status)
			&&(write_timeout < 0xAAAAA))

	{
			write_timeout++;

	}//Esperar hasta que TFF es 0

	if(write_timeout <  0xAAAAA)
		pLEON3_UART_REGS->Data=c;

	return (write_timeout ==  0xAAAAA);
}
