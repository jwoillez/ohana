 /******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :param.h
 Subject : fichier header 
 Version	:3.0
******************************************************/
#ifndef _param_h
#define _param_h

#define NB_MOT 6 //6 moteurs 
#define MOT_DEFAUT 0 // moteur pas defaut à la mise sous tension

#define V_INIT 30 // vitesse d'approche du fin de course
#define V_RATTRAPAGE 50 // frequence d'horloge pour le rattrapage de phase
#define COURSE_INIT -999999L
#define DELTA_N  100
#define ATTENTE_MINI 20 // 0.2 secondes

#define VMIN1 1 // fourchette de definition des vitesses mini
#define VMIN_DEFAUT 300
#define VMIN2 600
#define VMAX1	50 // fourchette de definition des vitesses maxi
#define VMAX_DEFAUT 600
#define VMAX2 800
#define IMIN 0 // fourchette de definition d'intensite moteur
#define I_DEFAUT 0 // tous les moteurs à 0.25A
#define IMAX 7
#define AMIN 10 // fourchette de definition des accelerations
#define A_DEFAUT 20
#define AMAX 100
#define MPMIN 1 // fourchette de definition des micropas/pas
#define MP_DEFAUT 5
#define MPMAX 6
#define ADRMIN 0 // fourchette des adresses physiques moteur
#define ADRMAX 31
#define POSMIN 0
#define POSMAX 999999L
#define JEU_MIN 0 // rattrapage de jeu
#define JEU_DEFAUT 0
#define JEU_MAX 200
#define OFFSET_DEFAUT 100 // position du zero par rapport au fdc origine
#define OFFSET_MIN 0
#define OFFSET_MAX 1000
#define PHASE_DEFAUT 0 // phase a l'origine par defaut

/*-----------------DECLARATIONS DES FONCTIONS-------------*/
void write_eeprom(char * eeprom, char *val, char nb_octet);
void refresh_pos(); // ecriture de la nouvelle position dans la table EEPROM
long lect_pos(); // lecture instantanée de la position 
void calcul_phase_org(int course); // calcul de la phase a l'origine
void reset_phase(void); // remise a zero de la phase à l'origine
int read_select(); // lecture du moteur selectionné
int write_vmin(); // ecriture de VMIN dans la table tab_vmin
int read_vmin();  // lecture
int write_vmax(); // ecriture de VMAX dans la table tab_vmax
int read_vmax();  // lecture
int write_intensite();
int read_intensite();
int write_acceleration();
int read_acceleration();
int write_adresse();
int read_adresse();
int write_mpas();
int read_mpas();
int write_position();
int affiche_position();
int read_fin_course(); // lecture des fin de courses et etats moteur
int write_phase();
int read_phase();
int read_jeu();
int write_jeu();
int write_offset();
int read_offset();
int read_info(); // lecture des fin de course et position pour tous les moteurs
unsigned int lect_offset();
void write_tab_etat(unsigned int masque, unsigned char value);
int read_tab_etat();
int affiche_param(); // envoi de tous les paramètres d'un moteur sur la console
int init_tab(); // initialisation par defaut des tables en EEPROM

#endif //_param_h
