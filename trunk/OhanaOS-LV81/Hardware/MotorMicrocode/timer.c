/******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :timer.c
 Subject : gestion des timers, des it et autres trucs très hard
 Version	:3.0
******************************************************/
/*
  On utilise le timer 2 en mode auto-reload pour générer la fréquence d'horloge.
  Le comptage des impulsions est placé directement dans la routine d'interruption. 
*/
#include "ohana.h"
/*-------------------------VARIABLES GLOBALES-------------*/
static data unsigned int tick_periode = 65536 - (1000000L/TICKDEFAUT); // -periode par defaut en µs
static data unsigned int h_periode = 65536 - (1000000L/HDEFAUT); // -periode timer0 par defaut
static data unsigned char msb_base, lsb_base, msb_h, lsb_h;
data long nb_pulse;
static data unsigned long time; // compteur de temps pour le timer0

/*----------------------------FLAGS-----------------------*/
bit move_on = 0; // flag de mouvement en cours
bit end_move = 0; // flag de fin de mouvement
extern bit rattrapage; // flag de rattrapage de jeu
/*--------------GENERATION DE L'HORlOGE MOTEUR---------------*/
// Utilisation du timer 2 en mode auto-reload
int start_horloge(unsigned int frequence, long pulse)
{ 
 data unsigned int reload, compare;
 // en fait on travaille à 2 fois la fréquence d'horloge, donc 2 fois plus de pulses
 nb_pulse = pulse << 1;
 CTCON |= 0x80 ; //fosc/96 (125kHz)
 T2PS = 1; //fosc/96 (125kHz)
 T2R1 = 1; // mode auto-reload
 T2R0 = 0; // mode auto-reload
 T2I1 = 0; // fonction timer
 T2I0 = 1; // fonction timer
 reload = -62500/frequence;
 compare = 65534;  // compare à une valeur fixe (2 coup d'horloge )
  // pour un démarrage propre, il faut charger aussi directement TH2 et TL2
 // parce que le contenu de CRC sera visiblement pris au coup d'horloge suivant
 TH2 = reload >> 8; 
 TL2 = reload & 0xFF;
 CM0 = compare; // chargement de la valeur de comparaison
 CRC = reload ; // chargement de la periode et démarrage
 TF2 = 0; // raz du flag d'overflow
 ET2 = 1; // validation de l'it
 CMEN = 1; // Validation sur sortie
 //HORLOGE = ON;
 return OK;
}

// routine d'it du timer 2
// Genere le signal carré d'horloge et compte les impulsions et arrete le moteur quand y faut
// Durée de traitement de cette routine 80µs
void it_timer2(void) interrupt 5
{
 TF2 = 0;// flag d'overflow à zero
 nb_pulse --; // decompte les impulsions
 HORLOGE = !HORLOGE;
 if ( nb_pulse <= 0)// quand c'est fini, on arrete
 {
  ET2=0;// inhibition des it
  HORLOGE = OFF;//stop horloge
  move_on = 0; // c'est fini
  end_move = 1; // fin de mouvement 
 }
}

// arret propre du moteur sur une position "home" du moteur
int stop_horloge()
{
 // ça n'a de sens que si on est déjà en mouvement
 if ( move_on == 1)
 {
   while(HOME != 1); // on attend d'être sur un pas entier
	ET2 = 0;
	CMEN = 0; // Inhibition de la sortie
	HORLOGE = OFF;
 	move_on = 0;
	end_move = 1;
 }
 return OK;
}

// arret pas propre du moteur n'importe ou
int halt_horloge()
{
 // ça n'a de sens que si on est déjà en mouvement
 if ( move_on == 1)
 {
	ET2 = 0;
	CMEN = 0; // Inhibition de la sortie
	HORLOGE = OFF;
 	move_on = 0;
	end_move = 1;
 }
 return OK;
}
// pour tests
int start()
{
  int code_fct;
  long param;
  code_fct = extract_long_param(&param);
  if (code_fct == OK)
    code_fct = calcul_rampe((unsigned int)param);
 return code_fct;
}

int stop()
{ 
 int code_fct;
 code_fct = stop_horloge();
 return code_fct;
}

int halt()
{ 
 int code_fct;
 code_fct = halt_horloge();
 return code_fct;
}
/***********************BASE DE TEMPS  SUR TIMER 1**************/
// Mode 1 compteur 16bits, genere un IT toutes les tick_periode ms 
// Durée de la fonction 670µs
void start_tick(void)
{
 msb_base =tick_periode >> 8;
 lsb_base = tick_periode & 0xff;
 TF1 = OFF; //raz du flag d'overflow
 TH1 = msb_base;  // Chargement du compteur MSB
 TL1 = lsb_base; // LSB
 TMOD = (TMOD & 0x0F) | 0x10; // Mode 1 sur timer 1
 ET1 = ON; //autorisation de l'IT
 TR1 = ON; //Mise en route du compteur
}

void stop_tick( void)
{
 TR1 = OFF; // arret du compteur
 ET1 = OFF; // inhibition de l'IT
}

/* 
   Routine d'interruption du timer 1
*/
void	it_tick(void) interrupt 3
{
 TH1 = msb_base;  // Chargement du compteur
 TL1 = lsb_base;
 TR1 = ON; // On redemarre
}



/***********************BASE DE TEMPS  SUR TIMER 0**************/
// Mode 1 compteur 16bits, genere un IT toutes les tick_periode ms 
// Durée de la fonction 670µs
void start_t0(void)
{
 time = 0;
 msb_h =h_periode >> 8;
 lsb_h = h_periode & 0xff;
 TF0 = OFF; //raz du flag d'overflow
 TH0 = msb_h;  // Chargement du compteur MSB
 TL0 = lsb_h; // LSB
 TMOD = (TMOD & 0xF0) | 0x1; // Mode 1 sur timer 0
 ET0 = ON; //autorisation de l'IT
 TR0 = ON; //Mise en route du compteur
}

void stop_t0( void)
{
 TR0 = OFF; // arret du compteur
 ET0 = OFF; // inhibition de l'IT
}
unsigned long read_t0(void)
{
 return time;
}

/* 
   Routine d'interruption du timer 0
*/
void	it_t0(void) interrupt 1
{
 TH0 = msb_h;  // Chargement du compteur
 TL0 = lsb_h;
 TR0 = ON; // On redemarre
 time++;
}

// Fonction de delai d'attente de n période de timer0
void wait(unsigned int tps_attente)
{
 start_t0();
 while ( time < tps_attente);
 stop_t0();
}

/*---------------------Routines d'interruption sur les fins de courses-----------------*/
// fin de course moins , IEX3 sur front montant 
void it_fdcmoins(void) interrupt 10
{
 // si on bouge dans le sens moins, on arrete l'horloge du moteur
 // tester à nouveau l'etat du fin de course permet de s'affranchir des parasites
 if (move_on && (SENS==SENS_MOINS)&&ORIGINE)
 {
   rattrapage = 0;// si on tape le fin de course, on inhibe le rattrapage
   EX3 = 0; // on inhibe l'it
  	ET2 = 0;
	CMEN = 0; // Inhibition de la sortie
	HORLOGE = OFF;
 	move_on = 0;
	end_move = 1;
 }
}

// fin de course plus , IEX4 sur front montant 
void it_fdcplus(void) interrupt 11
{
 // si on bouge dans le sens moins, on arrete l'horloge du moteur 
 // tester à nouveau l'etat du fin de course permet de s'affranchir des parasites
 if (move_on &&(SENS==SENS_PLUS)&&FIN_DE_COURSE)
 {
   EX4 = 0; // on inhibe l'it
  	ET2 = 0;
	CMEN = 0; // Inhibition de la sortie
	HORLOGE = OFF;
 	move_on = 0;
	end_move = 1;
 }
}
