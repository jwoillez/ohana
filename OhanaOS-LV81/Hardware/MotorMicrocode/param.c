/******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :param.c
 Subject : gestion des parametres moteurs
 Version	:3.01
******************************************************/ 
#include "ohana.h"
#include <stdio.h>
#include <stdlib.h>
/*-------------------------TABLES EN EEPROM----------*/
at 0x000  xdata unsigned int tab_vmax[NB_MOT+1];     // vitesse maxi
at 0x040  xdata unsigned int tab_vmin[NB_MOT+1];     // vitesse mini
at 0x080  xdata unsigned int tab_acc[NB_MOT+1];      // acceleration
at 0x0c0  xdata unsigned int tab_adresse[NB_MOT+1];  // adresse physique
at 0x100  xdata unsigned int tab_intensite[NB_MOT+1];// intensite moteur
at 0x140  xdata unsigned int tab_micropas[NB_MOT+1]; // µpas/pas
at 0x180  xdata         long tab_position[NB_MOT+1]; // position
at 0x200  xdata unsigned int tab_phase[NB_MOT+1];    // phase à l'origine
at 0x240  xdata unsigned int tab_etat[NB_MOT+1];     // etats 
at 0x280  xdata unsigned int tab_jeu[NB_MOT+1];      // valeur de rattrapage de jeu
at 0x2c0  xdata unsigned int tab_offset[NB_MOT+1];    // offset de position zero
// tableau de correspondance entre les codes micropas et le nombre de micropas/pas
code char correspondance_micropas[] ={0,1,2,4,5,8,10,16,20,32,40,64};
// tableau de correspondance entre les codes intensite et l'intensite du moteur
code float correspondance_intensite[]={0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00};

/*-------------------------VARIABLES GLOBALES-------------*/
char num_moteur;
extern data long nb_pulse; // compteur d'impulsions défini dans timer.c
extern data long nb_pas; // defini dans moteur.c
extern bit move_on;
extern bit autre;
/*-------------------------FONCTIONS D'ACCES AUX PARAMETRES----------*/
/*---------------------------ECRITURE EN EEPROM---------------------*/
/* Ecriture de la valeur octet par octet avec attente d'au moins
   5 millisecondes entre chaque cycle d'ecriture
   Attention!! en utilisant cette fonction, le paramètre val doit avoir
   une adresse. Donc ne pas la prendre dans l'espace interne data ni idata
*/
void write_eeprom(char * eeprom, char *val, char nb_octet)
{
 data char i;
 for( i = 0; i < nb_octet; i++)
 {
  eeprom[i] = val[i];
  //printf("at %p val= %x\n\r",&eeprom[i],val[i]);
  wait(1);// attente d'un tick d'horloge
 }
}

/*-----RAFRAICHISSEMENT DE LA POSITION DU MOTEUR DANS LA TABLE TAB_POSITION--*/
// duree de la fonction = 15ms
void refresh_pos()
{
 long new_val;
 long val;
 new_val = labs(nb_pas) - (nb_pulse >> 1);
 if (SENS == SENS_PLUS)
 	val = tab_position[num_moteur] + new_val;
 else
 	val = tab_position[num_moteur] - new_val;
 write_eeprom((char *)&tab_position[num_moteur],(char *)&val,sizeof(val));
}
/*---------------------LECTURE DE LA POSITION INSTANTANEE DU MOTEUR--------------*/
long lect_pos()
{
 long val, pulse ;
 pulse = nb_pulse >>1;
 val = labs(nb_pas) - pulse;
  if (SENS == SENS_PLUS)
 	val = tab_position[num_moteur] + val;
 else
 	val = tab_position[num_moteur] - val; 
 return val;
}
/* Lecture du moteur selectionné */
int read_select()
{
 write_rs232(num_moteur); 
 return OK;
}
/*--------------------------CALCUL DE LA PHASE A L'ORIGINE-----------------------*/
void calcul_phase_org(int course)
{
 int val;
 val = course % (4*correspondance_micropas[tab_micropas[num_moteur]]);
 write_eeprom((char *)&tab_phase[num_moteur],(char *)&val,sizeof(val));
}
/*-----------------------------RAZ DE LA PHASE A L'ORIGINE-----------------------*/
void reset_phase(void)
{
 unsigned int val;
 val = 0;
 write_eeprom((char *)&tab_phase[num_moteur],(char *)&val,sizeof(val));
}

/* Ecriture de VMIN dans le tableau tab_vmin */
int write_vmin()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < VMIN1) || (param > VMIN2) ) return ERR_PARAM;
   write_eeprom((char *)&tab_vmin[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de VMIN dans le tableau tab_vmin */
int read_vmin()
{
 write_rs232(tab_vmin[num_moteur]);
 return OK;
}

/* Ecriture de VMAX dans le tableau tab_vmax */
int write_vmax()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < VMAX1) || (param > VMAX2) ) return ERR_PARAM;
   write_eeprom((char *)&tab_vmax[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de VMAX dans le tableau tab_vmax */
int read_vmax()
{
 write_rs232(tab_vmax[num_moteur]);
 return OK;
}

/* Ecriture de INT dans le tableau tab_intensite */
int write_intensite()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < IMIN) || (param > IMAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_intensite[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de INT dans le tableau tab_intensite */
int read_intensite()
{
 write_rs232(tab_intensite[num_moteur]);
 return OK;
}

/* Ecriture de ACC dans le tableau tab_acc */
int write_acceleration()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < AMIN) || (param > AMAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_acc[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de ACC dans le tableau tab_acc */
int read_acceleration()
{
 write_rs232(tab_acc[num_moteur]);
 return OK;
}

/* Ecriture de ADR dans le tableau tab_adresse */
int write_adresse()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < ADRMIN) || (param > ADRMAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_adresse[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de ADR dans le tableau tab_adresse */
int read_adresse()
{
 write_rs232(tab_adresse[num_moteur]);
 return OK;
}

/* Ecriture de MPAS dans le tableau tab_micropas */
int write_mpas()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < MPMIN) || (param > MPMAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_micropas[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* Lecture de MPAS dans le tableau tab_micropas */
int read_mpas()
{
 write_rs232(tab_micropas[num_moteur]);
 return OK;
}
/* lecture de la position moteur instantanée */
int affiche_position()
{ 
 if (move_on) printf("%ld\n\r",lect_pos());
 else printf("%ld\n\r",tab_position[num_moteur]);
 return OK;
}
/*  Ecriture de la position dans tab_position  */
int write_position()
{
 int code_fct;
 long param;
 code_fct = extract_long_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < POSMIN) || (param > POSMAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_position[num_moteur],(char *)&param,sizeof(param));
   // ruse grossière pour reactualiser l'affichage de la position
   autre = ON; 
   code_fct = OK;
 }
 return code_fct;
}

/* lecture des fins de courses   */
int read_fin_course()
{
 write_rs232(read_fdc());
 return OK;
}

/*  Ecriture de la phase dans tab_phase  */
int write_phase()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( param < 0 ) return ERR_PARAM;
   write_eeprom((char *)&tab_phase[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}

/*  Lecture de la phase dans tab_phase  */
int read_phase()
{
 write_rs232(tab_phase[num_moteur]);
 return OK;
} 

/* Ecriture de la valeur de rattrapage de jeu */
int write_jeu()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < JEU_MIN) || (param >= JEU_MAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_jeu[num_moteur],(char *)&param,sizeof(param));
   code_fct = OK;
 }
 return code_fct;
}
/* lecture de la valeur de rattrapage de jeu */
int read_jeu()
{
 write_rs232(tab_jeu[num_moteur]);
 return OK;
}
 
/* offset de decalage entre la position zero et le fdc origine */
int write_offset()
{
 int code_fct,valeur;
 code_fct = extract_int_param(&valeur);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (valeur <OFFSET_MIN) || (valeur > OFFSET_MAX) ) return ERR_PARAM;
   write_eeprom((char *)&tab_offset[num_moteur],(char *)&valeur, sizeof(valeur));
   code_fct = OK;
 }
 return code_fct;
}
/* lecture de l'offset */
int read_offset()
{
 write_rs232(tab_offset[num_moteur]);
 return OK;
}
 
unsigned int lect_offset()
{
 return tab_offset[num_moteur];
}
/* remise a zero du bit d'init_ok dans la table en EEPROM */

/*----------------Ecriture d'un bit dans la table d'états---------------------*/
void write_tab_etat(unsigned int masque, unsigned char value)
{
 unsigned int param;
 param = tab_etat[num_moteur];
 if (value) param |= masque;
 else param &= ~masque;
 write_eeprom((char *)&tab_etat[num_moteur],(char *)&param,sizeof(param));
}

/*-------------------Lecture de la table d'état-------------------------------*/
int read_tab_etat()
{
 write_rs232(tab_etat[num_moteur]);
 return OK;
}
/* Lecture de tous les paramètres moteurs sur la console */
int affiche_param()
{
 if (num_moteur <= NB_MOT)
 {
  printf("MOT   : %d\n\r",num_moteur);
  printf("VMIN  : %d pas/sec\n\r",tab_vmin[num_moteur]);
  printf("VMAX  : %d pas/sec\n\r",tab_vmax[num_moteur]);
  printf("ACC   : %d \n\r",tab_acc[num_moteur]);
  printf("INT   : %.2fA\n\r",correspondance_intensite[tab_intensite[num_moteur]]);
  printf("MPAS  : %d µpas/pas\n\r",correspondance_micropas[tab_micropas[num_moteur]]);
  //printf("ADR   : %u\n\r",tab_adresse[num_moteur]);
  printf("POS   : %ld\n\r",tab_position[num_moteur]);
  printf("PHASE : %u\n\r",tab_phase[num_moteur]);
  printf("OFFSET: %u\n\r",tab_offset[num_moteur]);
  printf("JEU   : %u\n\r",tab_jeu[num_moteur]);
  printf("ETAT  : %u\n\r",tab_etat[num_moteur]);
  printf("FDC+  : %d\n\r",read_fdc() >> 1); // etat du fin de course +
  printf("ORG   : %d\n\r", read_fdc() & 0x1);       // etat du fin de course -
 }
 return OK;
}

int init_tab()
{
 unsigned int param;
 unsigned char i;
 for(i=0;i<=NB_MOT;i++)
 {
  param = VMIN_DEFAUT;
  write_eeprom((char *)&tab_vmin[i],(char *)&param,sizeof(param));
  param = VMAX_DEFAUT;
  write_eeprom((char *)&tab_vmax[i],(char *)&param,sizeof(param));
  param = A_DEFAUT;
  write_eeprom((char *)&tab_acc[i],(char *)&param,sizeof(param));
  param = I_DEFAUT;
  write_eeprom((char *)&tab_intensite[i],(char *)&param,sizeof(param));
  param = MP_DEFAUT;
  write_eeprom((char *)&tab_micropas[i],(char *)&param,sizeof(param));
  param = JEU_DEFAUT;
  write_eeprom((char *)&tab_jeu[i],(char *)&param,sizeof(param));
  //if (i>=0 && i<=6) param =i;
  //if (i>=7 && i<=12) param = i+2;
  //if (i>=13 && i<=18) param = i+4;
  //write_eeprom((char *)&tab_adresse[i],(char *)&param,sizeof(param));
  param = OFFSET_DEFAUT;
  write_eeprom((char *)&tab_offset[i],(char *)&param,sizeof(param));
  param = PHASE_DEFAUT;
  write_eeprom((char *)&tab_phase[i],(char *)&param,sizeof(param));
  param =0;
  write_eeprom((char *)&tab_etat[i],(char *)&param,sizeof(param));
 }
 return OK;
}
/* Lecture des parametres  pour tous les moteurs */
int read_info()
{
 char i;
 for(i=1; i<=NB_MOT; i++)
 {
  printf("%d\t",tab_vmin[i]);
  printf("%d\t",tab_vmax[i]);
  printf("%d\t",tab_acc[i]);
  printf("%.2f\t",correspondance_intensite[tab_intensite[i]]);
  printf("%d\t",correspondance_micropas[tab_micropas[i]]);
  printf("%ld\t",tab_position[i]);
  printf("%u\t",tab_offset[i]);
  printf("%u\t",tab_jeu[i]);
  printf("\n\r");
 }
 return OK;
}

