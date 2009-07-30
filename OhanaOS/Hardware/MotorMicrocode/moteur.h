 /******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :moteur.h
 Subject : fichier header 
 Version	:0.1
******************************************************/
#ifndef _moteur_h
#define _moteur_h

#define SENS_PLUS  0
#define SENS_MOINS 1
#define ALIM_ON 0
#define ALIM_OFF 1

#define FDC_MOINS  1 // code du fin de course origine
#define FDC_PLUS   2 // code du fin de course plus

/* les masques pour isoler les infos d'états */
#define MASQUE_MVT_ON     0x01
#define MASQUE_END_MOVE   0x02
#define MASQUE_INIT_ON    0x04
#define MASQUE_PARAM_OK   0x08
#define MASQUE_INIT_OK    0x10
#define MASQUE_TIMOUT     0x20
#define MASQUE_FDCMOINS   0x40
#define MASQUE_FDCPLUS    0x80 

/*-----------------DECLARATIONS DES FONCTIONS-------------*/
void init_cpt_pulse(unsigned int valeur);
int select_mot(); // selection du moteur à paramétrer 
int selection_moteur(int numero);
int bouge_moteur(); // deplacement moteur
int move_mot( unsigned int vitesse, long value); 
int read_fdc(); // lecture des fins de course
int read_status(); // lecture des etats dynamiques du système
int read_etats(); // idem sur la ligne rs232
int calcul_rampe(unsigned int course); // calcul de la rampe d'acceleration
int read_rampe(); // pour afficher les valeurs de t et x de la rampe
#endif //_moteur_h
