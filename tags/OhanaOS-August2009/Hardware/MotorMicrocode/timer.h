 /******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :timer.h
 Subject : fichier header 
 Version	:3.0
******************************************************/
#ifndef _timer_h
#define _timer_h

#define F_MAX 8000 // frequence maxi moteur en pas/sec
#define TICKDEFAUT 20 // fr�quence (Hz) pour g�n�ration des rampes d'acc�l�ration
#define HDEFAUT 100 // fr�quence (Hz) timer de d�lai et timout

/*-----------------DECLARATIONS DES FONCTIONS-------------*/
int start_horloge(unsigned int frequence, long pulse);
int stop_horloge();// arret propre
int halt_horloge();// arret moins propre
int start();// pour tests
int stop();
int halt();
void start_tick( void ); // base de temps sur timer1
void stop_tick( void);
void start_t0( void ); // base de temps sur timer0
unsigned long read_t0(void); // lecture du temps ecoule sur timer 0
void stop_t0( void );
void wait(unsigned int tps_attente); 

#endif 
