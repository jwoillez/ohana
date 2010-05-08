/******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :afficheur.h
 Subject : fichier header 
 Version	:3.0
******************************************************/ 
#ifndef _afficheur_h
#define _afficheur_h


#define NB_AFF 8  // 8 digits sur l'afficheur



/*--------------------------PROTOTYPES DES FONCTIONS UTILISEES------------------*/
int display( char *message); // envoi d'une chaine de caractères vers l'afficheur
int reset_display( void); // reset de l'afficheur
void refresh_display(long val);
int brightness( int val); // controle de la luminosite de l'afficheur
int luminosite();
int blink( char val ); // clignotement de l'afficheur
int clignote();
void visu_boucle(void); //pour visualiser la frequence de boucle de scrutation


#endif //_afficheur_h
