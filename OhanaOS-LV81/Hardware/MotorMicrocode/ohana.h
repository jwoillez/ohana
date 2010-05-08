/******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :ohana.h
 Subject : fichier header 
 Version	:3.0
******************************************************/
/* changements par rapport à la version 2:
   tout le port P5 affecté en sortie libre d'utilisation
   P32 (0xb2) = VAL_EEPROM
   P33 (0xb3) = VAL_RAQ
*/ 
#ifndef _ohana_h
#define _ohana_h 


#include "base_517.h" 
#include "afficheur.h"
#include "timer.h"
#include "param.h"
#include "moteur.h"
 
/*------------------------LES CONSTANTES-----------------------*/

/*-----------DEFINITIONS DES PORTS E/S "BIT ADRESSABLE"-------*/
/*  PORT 1 */ 
at 0x90	sbit	ORIGINE;			// fin de course origine					
at 0x91	sbit	FIN_DE_COURSE;	// fin de course aller		
at 0x92	sbit	DEFAUT;			// defaut moteur		
at 0x93	sbit 	HOME;				// home moteur				

/*  PORT 4  */
at 0xe8	sbit	HORLOGE; 	//horloge moteur
at 0xe9	sbit	ENABLE;		// alimentation moteur
at	0xea	sbit	SENS;			// sens de rotation moteur
at 0xeb	sbit	M0;			// adressage moteur LSB
at	0xec	sbit	M1;
at 0xed	sbit	M2;
at 0xee	sbit	M3;
at 0xef	sbit 	M4;			// adressage moteur MSB



/* compilation conditionnelle selon la version de la carte micro */
#ifdef VERSION_2
 at 0xf9 sbit VAL_RAQ; // validation raquette de commande des moteurs sur P5
 at 0xfa sbit VAL_EEPROM; // validation d'acces a l'eeprom (actif 0) sur P5
 /* PORT P5 */
 at 0xfb sbit L1;
 at 0xfc sbit L2;
 at 0xfd sbit L3;
#else
 at 0xb2  sbit  VAL_EEPROM;   // validation d'acces a l'eeprom (actif 0) sur P3
 at 0xb3  sbit  VAL_RAQ;      // validation raquette de commande des moteurs sur P3
 /*  PORT 5  */
 /* tout le port en sortie libre d'utilisation */
 at 0xf8 sbit  L0;
 at 0xf9 sbit  L1;		
 at 0xfa	sbit	L2;		
 at 0xfb	sbit	L3; 
 at 0xfc	sbit	L4;
 at 0xfd	sbit	L5;
 at 0xfe sbit  L6;
 at 0xff sbit  L7;
#endif
/*--------------------------PROTOTYPES DES FONCTIONS UTILISEES------------------*/
/* fonctions de tests */


#endif  // _ohana_h 
