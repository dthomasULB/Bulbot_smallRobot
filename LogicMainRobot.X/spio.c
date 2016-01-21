/**
 * @file SPIO.c
 * @author bULBot 2011-2012
 * @author Olivier Desenfans
 * @brief Assigne les fonctions spéciales aux pattes d'I/O. 
 * @details Configuration des registres d'assignation des fonctions spéciales (UART, CAN) 
 * aux pattes d'entrées sorties (Special Purpose I/O).
 */

#include "spio.h"
#include "../libdspic/pps.h"
#include <xc.h>

//! Fonction d'assignation des I/O. 
void assignSPIO(void) {

    // bouton choix d'équipe
    TRISCbits.TRISC2 = 1;
    AD1PCFGLbits.PCFG8 = 1;

    // goupille de démarrage
    TRISCbits.TRISC3 = 1;

    //Denis 2015-2016 sortie ElectroAimant
    TRISCbits.TRISC1=0;
    AD1PCFGLbits.PCFG7 = 1;

    //UART Bluetooth
    ppsInConfig(PPS_U1RX,22);  //U1RX
    ppsInConfig(PPS_U1CTS,12); //U1CTS
    ppsOutConfig(0b00011,23);//U1TX
    ppsOutConfig(0b00100,13);//RTS

    // Codé équivalent
    //	_U1RXR = 22;       U1RX -> RP22
    //	_U1CTSR = 12;      U1CTS -> RP12
    //	_RP23R = 3;        RP23 -> U1Tx
    //	_RP13R = 4;        RP13 -> U1RTS

    // CAN
    ppsOutConfig(PPS_C1TX, 11);
    ppsInConfig(PPS_IN_C1RX, 10);
    // Sortie pour le servo    
    ppsOutConfig(PPS_OC1, 7);
;
}

