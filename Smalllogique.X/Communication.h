/*
 * File:   Radio.h
 * Author: M. Osee
 *
 * Created on 13 janvier 2013, 13:58
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H
	// defines wireless module reset pin
	#define LAT_AMB2300_RESET	_LATB14
	#define TRIS_AMB2300_RESET	_TRISB14

	#define RADIO_NO_ERR						 0
	#define RADIO_HOST_NOT_CONNECTED_ERR		-1
	#define RADIO_TX_BUFFER_FULL				-2
	#define RADIO_RX_BUFFER_EMPTY				-3
	#define RADIO_HARDWARE_ERR					-4

void uart1TxIsrEnable(void);
void uart1TxIsrDisable(void);

void uart1RxIsrEnable(void);
void uart1RxIsrDisable(void);

	int RadioGetTxBufferSpace(void);

	// This function is used to send data to the host.
	// 3 cases can happen:
	//	- no host is connected: the function does nothing and returns
	//	  RADIO_HOST_NOT_CONNECTED_ERR
	//	- a host is connected, but there is not enough space in the Tx buffer:
	//	  the function does nothing and returns RADIO_TX_BUFFER_FULL
	//	- a host is connected and there is enough space in the Tx buffer ("normal"
	//	  case): the function copies nb bytes in the Tx buffer to be send and
	//	  returns RADIO_NO_ERR.
	int RadioSendData( char* data, int nb);

	// This function is used to know the number of bytes waiting in the Rx buffer.
	// 2 cases can happen:
	//	- if a host is connected, the function returns the number of bytes in the
	//	  Rx buffer
	//	- if no host is connected, the function returns RADIO_HOST_NOT_CONNECTED_ERR
	int RadioGetRxBufferSpace(void);

	// This function is used to get data sent by the host.
	// 3 cases can happen:
	//	- no host is connected: the function does nothing and returns
	//	  RADIO_HOST_NOT_CONNECTED_ERR
	//	- a host is connected, but there is not enough bytes in the Rx buffer:
	//	  the function does nothing and returns RADIO_RX_BUFFER_EMPTY
	//	- a host is connected and there is enough bytes in the Rx buffer ("normal"
	//	  case): the function copies nb bytes from the Rx buffer in the bytes vector
	//	  pointed by data and returns RADIO_NO_ERR.
	int RadioGetData(char *data, int nb);

	int RadioInit(void);

#endif
