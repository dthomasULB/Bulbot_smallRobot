/*
// Definition of the clock frequency (in Hz), needed for __delay32()
#define FCY 40000000UL


#include "xc.h"
//  This file contains the prototype of __delay32()
#include <libpic30.h>
#include <uart.h>
#include "Communication.h"


#define LMX9830_STX						(0x02)
#define LMX9830_IND						(0x69)
#define LMX9830_READY					(0x25)
// SPP_INCOMMING_LINK_ESTABLISHED
#define LMX9830_LINK_ESTABLISHED		(0x0C)
#define LMX9830_ETX						(0x03)
#define LMX9830_SPP_TRANSPARENT_MODE               (0x11)
#define LMX9830_SPP_LINK_RELEASED		(0x0E)


#define RADIO_RX_DATA_SIZE		255
#define RADIO_TX_DATA_SIZE		255
#define RADIO_TIME_OUT			5000	// en ms
// LMX9830 frame detection, int timer ticks (Prescaler = 1:8)
// PR3 = timeout/(8*Tcy) - 1 = 2ms/200ns - 1 = 10E3 - 1
#define TMR3_TIMEOUT			9999

char radioRxData[RADIO_RX_DATA_SIZE];
int radioRxDataNb;
int radioRxDataStartPtr;
int radioRxDataEndPtr;

char radioTxData[RADIO_TX_DATA_SIZE];
int radioTxDataNb;
int radioTxDataStartPtr;
int radioTxDataEndPtr;

int radioLinkStatus;
#define RADIO_NO_LINK			0
#define RADIO_AMB2300_READY		1
#define RADIO_HOST_CONNECTED	2

int radioIsrFrameState = 0;
char radioIsrChecksum = 0;
int radioIsrLength = 0;
int radioIsrDataNb = 0;



// This function is used to know the available space in the Tx buffer.
// 2 cases can happen:
//	- if a host is connected, the function returns the available space in the
//	  Tx buffer
//	- if no host is connected, the function returns RADIO_HOST_NOT_CONNECTED_ERR
int RadioGetTxBufferSpace(void)
{
	if (radioLinkStatus == RADIO_HOST_CONNECTED)
	{
		return(radioTxDataNb);
	}
	else
	{
		return(RADIO_HOST_NOT_CONNECTED_ERR);
	}
}




// This function is used to send data to the host.
// 3 cases can happen:
//	- no host is connected: the function does nothing and returns
//	  RADIO_HOST_NOT_CONNECTED_ERR
//	- a host is connected, but there is not enough space in the Tx buffer:
//	  the function does nothing and returns RADIO_TX_BUFFER_FULL
//	- a host is connected and there is enough space in the Tx buffer ("normal"
//	  case): the function copies nb bytes in the Tx buffer to be send and
//	  returns RADIO_NO_ERR.
int RadioSendData( char* data, int nb)
{
	int i;


	// if no host is connected, RADIO_HOST_NOT_CONNECTED_ERR is returned
	if (radioLinkStatus != RADIO_HOST_CONNECTED)
	{
		return(RADIO_HOST_NOT_CONNECTED_ERR);
	}
	// if there is not enough space in the Tx buffer, RADIO_TX_BUFFER_FULL is returned
	else if (radioTxDataNb < nb)
	{
		return(RADIO_TX_BUFFER_FULL);
	}
	else
	{
		// radioTxDataNb is updated
		radioTxDataNb -= nb;
		// data are written in the output buffer
		for (i=0; i<nb; i++)
		{
			radioTxData[radioTxDataEndPtr] = data[i];
			// the end pointer must now point to the next byte to transmit,
			// that is the next in the vector ...
			radioTxDataEndPtr++;
			// ... unless the end of the vector is reached. If so, the next byte
			// to transmit is at the beginning of the vector (even if the vector
			// is empty: the next byte will be written there)
			if (radioTxDataEndPtr > RADIO_TX_DATA_SIZE)
			{
				radioTxDataEndPtr = 0;
			}
		}
		// if the UART Tx buffer is not full (that is, last transimssion is
		// complete), interrupt flag is activated to start the transmission
		if ( U1STAbits.UTXBF == 0 )
		{
			IFS0bits.U1TXIF = 1;
		}
		return(RADIO_NO_ERR);
	}
}




// This function is used to know the number of bytes waiting in the Rx buffer.
// 2 cases can happen:
//	- if a host is connected, the function returns the number of bytes in the
//	  Rx buffer
//	- if no host is connected, the function returns RADIO_HOST_NOT_CONNECTED_ERR
int RadioGetRxBufferSpace(void)
{
	if (radioLinkStatus == RADIO_HOST_CONNECTED)
	{
		return(radioRxDataNb);
	}
	else
	{
		return(RADIO_HOST_NOT_CONNECTED_ERR);
	}
}




// This function is used to get data sent by the host.
// 3 cases can happen:
//	- no host is connected: the function does nothing and returns
//	  RADIO_HOST_NOT_CONNECTED_ERR
//	- a host is connected, but there is not enough bytes in the Rx buffer:
//	  the function does nothing and returns RADIO_RX_BUFFER_EMPTY
//	- a host is connected and there is enough bytes in the Rx buffer ("normal"
//	  case): the function copies nb bytes from the Rx buffer in the bytes vector
//	  pointed by data and returns RADIO_NO_ERR.
int RadioGetData(char *data, int nb)
{
	int i;


	// if no host is connected, RADIO_HOST_NOT_CONNECTED_ERR is returned
	if (radioLinkStatus != RADIO_HOST_CONNECTED)
	{
		return(RADIO_HOST_NOT_CONNECTED_ERR);
	}
	// if there is not enough bytes in the Rx buffer,
	// RADIO_RX_BUFFER_EMPTY is returned
	else if (radioRxDataNb < nb)
	{
		return(RADIO_RX_BUFFER_EMPTY);
	}
	else
	{
		// radioRxDataNb is updated
		radioRxDataNb -= nb;
		// data are read from the input buffer
		for (i=0; i<nb; i++)
		{
			data[i] = radioRxData[radioRxDataStartPtr];
			// start pointer must now point to the "new" oldest byte, that is the
			// next one ...
			radioRxDataStartPtr++;
			// ... unless the end of the vector is reached. If so, the oldest byte
			// is the first of the vector
			if (radioRxDataStartPtr == RADIO_RX_DATA_SIZE)
			{
				radioRxDataStartPtr = 0;
			}
		}
		return(RADIO_NO_ERR);
	}
}


int RadioInit(void) {
	unsigned int baudvalue;		// Holds the value of baud register
	unsigned int U1MODEvalue;	// Holds the value of uart config reg
	unsigned int U1STAvalue;	// Holds the information regarding uart TX & RX interrupt modes
	int frameState;
	int err;
	char data;
	int length;
	char checksum;


	radioRxDataNb = 0;
	radioRxDataStartPtr = 0;
	radioRxDataEndPtr = 0;
	radioTxDataNb =  RADIO_TX_DATA_SIZE;
	radioTxDataStartPtr = 0;
	radioTxDataEndPtr = 0;
	radioLinkStatus = RADIO_NO_LINK;

	// Turn off UART1module to be in a defined state
	CloseUART1();
	// Configure uart1 receive and transmit interrupt
    ConfigIntUART1(UART_RX_INT_EN & UART_RX_INT_PR6 & UART_TX_INT_EN & UART_TX_INT_PR2);

	// Configure UART1 module to transmit 8 bit data with one stopbit. Also Enable loopback mode
    U1MODEvalue =	UART_EN				&	// enables the UART
    				UART_IDLE_CON		&	// UART continues to operate in idle mode
    				UART_IrDA_DISABLE	&	// IrDA encoder not used
					UART_MODE_FLOW		&	// AMB2300 is a DTE => we have to use the flow control mode
					UART_UEN_10			&	// we use U1Rx, U1Tx, U1CTS# and U1RTS# pins
					UART_EN_WAKE		&	// the CPU wakes up from sleep mode if a start bit is received
					UART_DIS_LOOPBACK	&	// internal loopback is disabled
					UART_DIS_ABAUD		&	// automatic baud rate detection disabled
					UART_UXRX_IDLE_ONE	&	// normal polarity for Rx
					UART_BRGH_SIXTEEN	&	// BRG uses a prescaler of 16
					UART_NO_PAR_8BIT	&	// 8 bits, no parity
					UART_1STOPBIT;			// 1 stop bit

	baudvalue = 21;	// with prescaler of 16

    U1STAvalue  =	UART_INT_TX_BUF_EMPTY  &
					UART_IrDA_POL_INV_ZERO &
					UART_TX_ENABLE &
					UART_SYNC_BREAK_DISABLED &
					UART_INT_RX_CHAR &
					UART_ADR_DETECT_DIS &
					UART_RX_OVERRUN_CLEAR;

    OpenUART1(U1MODEvalue, U1STAvalue, baudvalue);
/*
	// Configures timer3 to generate a timeout interrupt for LMX9830 frame detection
	T3CONbits.TON = 0;		// stop Timer3
	TMR3 = 0;				// clear timer3
	PR3 = TMR3_TIMEOUT;		// Set timeout value
	T3CONbits.TCS = 0; 		// Timer3 uses internal clock (Fcy = Fosc/2 = 40MHz)
	T3CONbits.TCKPS = 1;	// prescaler = 1:8
	T3CONbits.TGATE = 0;	// we don't use external enable signal
	_T3IF = 0;		// clear the interrupt flag, before ...
	_T3IE = 0;		// disable the interrupt


	LAT_AMB2300_RESET = 0;
	TRIS_AMB2300_RESET = 0;
	__delay32(1000);
	LAT_AMB2300_RESET = 1;
	__delay32(500000);

	frameState = 0;
	err = RADIO_NO_ERR;
	checksum = 0;
//	T3CONbits.TON = 1;		// start Timer3 as timeout counter
	// The AMB2300 should send a valid start-up frame. Otherwise, Timer3 will
	// overflow, and the function will end waiting for the frame
	while ((_T3IF == 0) && (radioLinkStatus == RADIO_NO_LINK) && (err == RADIO_NO_ERR))
	{
		// if there is data available in the input buffer
		if (radioRxDataNb > 0) {
			data = radioRxData[radioRxDataStartPtr];
			// we read one data, so radioRxDataNb msut be decremented
			radioRxDataNb--;
			// start pointer must now point to the "new" oldest byte, that is the
			// next one ...
			radioRxDataStartPtr++;
			// ... unless the end of the vector is reached. If so, the oldest byte
			// is the first of the vector (it should'nt happen here)
			if (radioRxDataStartPtr == RADIO_RX_DATA_SIZE)   radioRxDataStartPtr = 0;

			switch (frameState) {
				case 0:
					// the data must match the start-up frame
					if (data == LMX9830_STX) {
						frameState = 1;
						TMR3 = 0;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
				case 1:
					// the data must match the start-up frame
					if (data == LMX9830_IND) {
						frameState = 2;
						TMR3 = 0;
						checksum += data;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
				case 2:
					// the data must match the start-up frame
					if (data == LMX9830_READY) {
						frameState = 3;
						TMR3 = 0;
						checksum += data;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
				case 3:
					length = data;
					checksum += data;
					TMR3 = 0;
					frameState = 4;
				break;
				case 4:
					length += (((int)data) << 8);
					checksum += data;
					if (length > 0) {
						frameState = 5;
						TMR3 = 0;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
				case 5:
					if (data == checksum){
						frameState = 6;
						TMR3 = 0;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
				case 6:
					length--;
					TMR3 = 0;
					if (length <= 0) frameState = 7;
				break;
				case 7:
					if (data == LMX9830_ETX) {
						radioLinkStatus =  RADIO_AMB2300_READY;
						TMR3 = 0;
					} else {
						err = RADIO_HARDWARE_ERR;
					}
				break;
			}
		}
	}
	T3CONbits.TON = 0;
	TMR3 = 0;
	if (_T3IF == 1){
		_T3IF = 0;		// clear the interrupt flag
		err = RADIO_HARDWARE_ERR;
	}
	_T3IE = 1;		// enable the interrupt
	return(err);
}



//	INTERRUPTS
//////////////////////////////////////////////////////////////////////////////

/* This is TIMER3 ISR */
/*
void __attribute__((__interrupt__, no_auto_psv)) _T3Interrupt(void)
{
	// interrupt flag is reset
	_T3IF = 0;
	// Timer3 is stopped
	T3CONbits.TON = 0;
	// Timer3 is reset
	TMR3 = 0;
	// radioRxDataNb is updated
	radioRxDataNb += (radioIsrFrameState + 1);
	radioIsrDataNb = 0;
	// frameState is reset
	radioIsrFrameState = 0;
	radioIsrChecksum = 0;
}


/* This is UART1 transmit ISR */
/*
void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void)
{
	// reset the interrupt flag
	IFS0bits.U1TXIF = 0;
	// if there are bytes to send in our output buffer and the UART Tx buffer
	// is not full, we copy the next byte to send in the Tx buffer.
	while ( ( radioTxDataNb <  RADIO_TX_DATA_SIZE ) && ( U1STAbits.UTXBF == 0 ) )
	{
		// first byte of the output buffer is written in the UART Tx buffer
		U1TXREG = radioTxData[radioTxDataStartPtr];
		// the start pointer must now point to the next byte to transmit,
		// that is the next in the vector ...
		radioTxDataStartPtr++;
		// ... unless the end of the vector is reached. If so, the next byte
		// to transmit is at the beginning of the vector (even if the vector
		// is empty: the next byte will be written there)
		if (radioTxDataStartPtr > RADIO_TX_DATA_SIZE)
		{
			radioTxDataStartPtr = 0;
		}
		// data counter is decremented
		radioTxDataNb++;
	}
}




/* This is UART1 receive ISR 
void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void)
{
	char data;

    IFS0bits.U1RXIF = 0;
	while (U1STAbits.URXDA)
	{
		// First, if there was a framing error, we discard the byte.
		// It should never happen
		if (U1STAbits.FERR == 1)   data = U1RXREG;

		// if input buffer is not full
		else if (radioRxDataNb < RADIO_RX_DATA_SIZE)
		{
			// new byte is written in the buffer
			data = U1RXREG;
			radioRxData[radioRxDataEndPtr] = data;
			// the end pointer must now point to where the next byte received
			// has to be put, that is after this one in the vector ...
			radioRxDataEndPtr++;
			// ... unless the end of the vector is reached. If so, we put the
			// new byte at the beginning of the vector (as buffer is not full,
			// its first byte has to be empty)
			if (radioRxDataEndPtr == RADIO_RX_DATA_SIZE)
			{
				radioRxDataEndPtr = 0;
			}



			if (radioLinkStatus == RADIO_NO_LINK)
				radioRxDataNb++;

			if (radioLinkStatus == RADIO_AMB2300_READY)
			{
				radioIsrDataNb++;
				switch (radioIsrFrameState) {
					case 0:
						// the data must match the host connection frame
						if (data == LMX9830_STX) {
							radioIsrFrameState = 1;
							TMR3 = 0;
							T3CONbits.TON = 1;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 1:
						// the data must match the host connection frame
						if (data == LMX9830_IND) {
							radioIsrFrameState = 2;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 2:
						// the data must match the host connection frame
						if (data == LMX9830_LINK_ESTABLISHED) {
							radioIsrFrameState = 3;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 3:
						radioIsrLength = data;
						radioIsrChecksum += data;
						TMR3 = 0;
						radioIsrFrameState = 4;
					break;
					case 4:
						radioIsrLength += (((int)data) << 8);
						radioIsrChecksum += data;
						if (radioIsrLength > 0) {
							radioIsrFrameState = 5;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 5:
						if (data == radioIsrChecksum){
							radioIsrFrameState = 6;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 6:
						radioIsrLength--;
						TMR3 = 0;
						if (radioIsrLength <= 0) radioIsrFrameState = 7;
					break;
					case 7:
						if (data == LMX9830_ETX) {
							radioLinkStatus =  RADIO_HOST_CONNECTED;
							T3CONbits.TON = 0;		// stop Timer3
							TMR3 = 0;
							radioIsrFrameState = 0;
							radioIsrChecksum = 0;
							radioRxDataStartPtr += radioIsrDataNb;
							radioIsrDataNb = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
				}

			}
			else if (radioLinkStatus == RADIO_HOST_CONNECTED)	// if host PC is connected
			{
				radioIsrDataNb++;
				// Verify if we are receiving a LMX9830 frame, indicating the
				// deconnection of the remote device (SPP_TRANSPARENT_MODE)
				switch (radioIsrFrameState) {
					case 0:
						// the data must match the host connection frame
						if (data == LMX9830_STX) {
							radioIsrFrameState = 1;
							TMR3 = 0;
							T3CONbits.TON = 1;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 1:
						// the data must match the host connection frame
						if (data == LMX9830_IND) {
							radioIsrFrameState = 2;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 2:
						// the data must match the host connection frame
						if (data == LMX9830_SPP_TRANSPARENT_MODE) {
							radioIsrFrameState = 3;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 3:
						radioIsrLength = data;
						radioIsrChecksum += data;
						TMR3 = 0;
						radioIsrFrameState = 4;
					break;
					case 4:
						radioIsrLength += (((int)data) << 8);
						radioIsrChecksum += data;
						if (radioIsrLength > 0) {
							radioIsrFrameState = 5;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 5:
						if (data == radioIsrChecksum){
							radioIsrFrameState = 6;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 6:
						radioIsrLength--;
						TMR3 = 0;
						if (radioIsrLength <= 0) radioIsrFrameState = 7;
					break;
					case 7:
						if (data == LMX9830_ETX) {
							TMR3 = 0;
							radioIsrFrameState = 8;
							radioIsrChecksum = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;

					case 8:
						// the data must match the host connection frame
						if (data == LMX9830_STX) {
							radioIsrFrameState = 9;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 9:
						// the data must match the host connection frame
						if (data == LMX9830_IND) {
							radioIsrFrameState = 10;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 10:
						// the data must match the host connection frame
						if (data == LMX9830_SPP_LINK_RELEASED) {
							radioIsrFrameState = 11;
							TMR3 = 0;
							radioIsrChecksum += data;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 11:
						radioIsrLength = data;
						radioIsrChecksum += data;
						TMR3 = 0;
						radioIsrFrameState = 12;
					break;
					case 12:
						radioIsrLength += (((int)data) << 8);
						radioIsrChecksum += data;
						if (radioIsrLength > 0) {
							radioIsrFrameState = 13;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 13:
						if (data == radioIsrChecksum){
							radioIsrFrameState = 14;
							TMR3 = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
					case 14:
						radioIsrLength--;
						TMR3 = 0;
						if (radioIsrLength <= 0) radioIsrFrameState = 15;
					break;
					case 15:
						if (data == LMX9830_ETX) {
							radioLinkStatus =  RADIO_AMB2300_READY;
							T3CONbits.TON = 0;		// stop Timer3
							TMR3 = 0;
							radioIsrFrameState = 0;
							radioIsrChecksum = 0;
							radioRxDataStartPtr += radioIsrDataNb;
							radioIsrDataNb = 0;
						} else {
							_T3IF = 1;	// call Timer3 ISR
						}
					break;
				}
			}
		}
	}
}


inline void radioSendChar(char data) {
	int test = 1;

	while(test) {
		uart1TxIsrDisable();								// on désactive l'interruption de réception pour manipuler les variables de l'ISR
		if (radioTxDataNb > 0) {							// on attend qu'on puisse écrire au moins un octet dans le buffer d'émission)
			radioTxDataNb--;									// on met à jour radioTxDataNb
			radioTxData[radioTxDataEndPtr] = data;				// on écrit l'octet à la fin du buffer d'émission
			if (++radioTxDataEndPtr >= RADIO_TX_DATA_SIZE) {	// on met à jour le pointeur vers la fin du buffer
				radioTxDataEndPtr = 0;
			}
			test = 0;
		}
		uart1TxIsrEnable();									// on réactive l'interruption
	}
	if (U1STAbits.UTXBF == 0) {							// Si l'UART n'est pas en train d'envoyer un octet (le buffer d'émission était vide)
		IFS0bits.U1TXIF = 1;							// on active "manuellement" l'ISR pour démarrer l'envoi
	}
}



void radioSendString(char* data) {
	int i = 0;

	while (*(data+i) != 0) {
		radioSendChar(*(data+i));
		i++;
	}
}
inline void uart1RxIsrEnable() {
	IEC0bits.U1RXIE = 1;

}

inline void uart1RxIsrDisable() {
	IEC0bits.U1RXIE = 0;
}


inline void uart1TxIsrDisable() {
	IEC0bits.U1TXIE = 0;
}

inline void uart1TxIsrEnable() {
	IFS0bits.U1TXIF = 0;
	IEC0bits.U1TXIE = 1;
}




inline char radioGetChar(void) {
	char data;
	int test = 1;

	while(test) {
		uart1RxIsrDisable();								// on désactive l'interruption de réception pour manipuler les variables de l'ISR
		if(radioRxDataNb > 0) {							// on attend qu'il y ait au moins un octet à lire dans le buffer de réception
			radioRxDataNb--;									// on met à jour radioRxDataNb
			data = radioRxData[radioRxDataStartPtr];			// on lit l'octet le plus ancien du buffer de réception
			if (++radioRxDataStartPtr >= RADIO_RX_DATA_SIZE) {	// on met à jour le pointeur vers l'octet le plus ancien du buffer
				radioRxDataStartPtr = 0;
			}
			test = 0;
		}
		uart1RxIsrEnable();									// on réactive l'interruption
	}
	return(data);
}
*/