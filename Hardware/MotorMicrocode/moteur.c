/******************************************************
 Project : Platine d'injection OHANA
 Author  :D.ZIG
 File    :moteur.c
 Subject : commande des moteurs pas a pas
 Version	:3.0
******************************************************/ 
#include "ohana.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*------------TABLES ET VARIABLES GLOBALES EXTERNES--------------*/
extern  xdata unsigned int tab_vmax[];     // vitesse maxi
extern  xdata unsigned int tab_vmin[];     // vitesse mini
extern  xdata unsigned int tab_acc[];      // acceleration
extern  xdata unsigned int tab_adresse[];  // adresse physique
extern  xdata unsigned int tab_intensite[];// intensite moteur
extern  xdata unsigned int tab_micropas[]; // µpas/pas
extern  xdata         long tab_position[]; // position
extern  xdata          int tab_phase[];    // phase à l'origine
extern  xdata          int tab_jeu[]; // valeur du rattrapage de jeu
extern xdata unsigned char tab_etat[]; // table d'etat des moteurs

extern code char correspondance_micropas[];
extern char num_moteur;
extern bit move_on; // flag de mouvement en cours défini dans timer.c
extern bit end_move;
extern bit init_on;
/*-------------------------VARIABLES GLOBALES DU FICHIER----------*/
data long nb_pas; // sert à rafraichir la position dans tab_position
data unsigned int x_acc; // déplacement pendant l'accélération
data int t_acc; // temps d'accélération en secondes
bit rattrapage; // flag du rattrapage de jeu
bit autre = 0;
/*------------------------------FONCTIONS-------------------*/

/*--------------------------SELECTION DU MOTEUR--------------------*/
// durée totale de la fonction = dépend du rattrage de jeu. 
// Ca peut atteindre 500ms
// durée de l'extract_int_param = 16ms
int select_mot()
{
 int code_fct,param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // si un mouvement est en cours, la commande est indisponible
   if (move_on || init_on) return CMD_NODISP;
   // si le moteur n'existe pas, erreur de paramètres 
   if ( (param < 0) || (param > NB_MOT) ) return ERR_PARAM; 
   //printf("Num moteur:%d\n\r",param);
   num_moteur = param;
   code_fct = selection_moteur(param);   
 }
 return code_fct;
}
int selection_moteur(int numero)
{
 data char val;
 data int nb_rattrapage,rattrapage_max;
 data unsigned char i;
 //printf("Entree select\n\r");
 ENABLE = ALIM_OFF; // alimentation moteur inactive  
 //attente mini pour que les relais commutent
 wait(3);
 // positionnement des paramètres mpas et intensite sur le port P6
 P6 = ~(tab_micropas[numero] <<4 | tab_intensite[numero]);
 //rattrapage de phase 
 // positionnement de l'adresse 0 sur P4
 P4 = (P4 &0x7)| 0xF8;
 // reste de la division
 rattrapage_max = 4 *correspondance_micropas[tab_micropas[numero]];
 nb_rattrapage = (tab_phase[numero] + tab_position[numero]) % rattrapage_max; 
 //printf("Entree rattrapage: %d \n\r",nb_rattrapage);
 if (nb_rattrapage >= rattrapage_max) return ERR_GRAVE;
 ENABLE = ALIM_ON; // alim active
 SENS = SENS_PLUS;
 
 // génération de n pulses de rattrapage sur le moteur 0
 if (nb_rattrapage)
 {
  VAL_EEPROM = ON; // inhibition de l'EEPROM (par securite)
  // il est important d'attendre au moins 0,3s sinon la carte moteur n'enregistrera 
  // pas les pulses de rattrapage
  wait(30); 
  for(i=0;i<nb_rattrapage;i++)
  {
   HORLOGE = ON;
   wait(1);
   HORLOGE = OFF;
   wait(1);
  }  
  VAL_EEPROM = OFF; // reactivation de l'EEPROM
 }
 //printf("Sortie rattrapage\n\r");
 // fin du rattrapage de phase
 // positionnement de l'adresse moteur sur P4
 P4 =  (P4 &0x7) | (~numero << 3);
 // attente de 30 ms, pour permettre au relais de commuter
 //printf("Adressage moteur\n\r");
 wait(3);
 //printf("Entree read_fdc\n\r");
 val = read_fdc();
 //printf("Code fdc:%d\n\r",val);
 if (val == (FDC_MOINS + FDC_PLUS)) return NO_CONNECT;
 if (val == FDC_PLUS) return ERR_FDCPLUS;
 if (val == FDC_MOINS) return ERR_FDCMOINS;
 //printf("Sortie select\n\r");
 return OK;;
}


/*-------------------------DEPLACEMENT MOTEUR DE N PAS-----------------*/
// durée totale de la fonction  = 53ms 
// durée de l'extract_long_param = 18ms
int bouge_moteur()
{
 int code_fct;
 long param;
 if ((num_moteur == 0) || init_on ) return CMD_NODISP;// si moteur 0, on quitte
 code_fct = extract_long_param(&param);
 if ( code_fct == OK)
 { 
   if (param ==0) code_fct = ERR_PARAM;
   else code_fct = move_mot(tab_vmin[num_moteur], param); 
 }
 return code_fct;
}

int move_mot( unsigned int vitesse,long value)
{
 data int val,nb_mpas;
 data long nbr_pulse,jeu;
 // si deplacement nul, c'est pas la peine d'aller plus loin
 if (value == 0) return OK;
 // si un mouvement est deja en cours, la commande est indisponible
 if (move_on) return CMD_NODISP;
 // si le moteur n'est pas alimenté ni connecté, on sort aussi
 if (ENABLE==ALIM_OFF) return ERR_ENABLE;
 val = read_fdc();
 if (val == (FDC_MOINS + FDC_PLUS)) return NO_CONNECT; 
 if ( value < 0 ) SENS = SENS_MOINS;
 else SENS = SENS_PLUS;
 // si on veut aller SENSPLUS en étant sur le fin de course+ , c'est pas bon
 if((val == FDC_PLUS) && (SENS == SENS_PLUS)) return ERR_FDCPLUS;
 // si on veut aller SENS_MOINS en étant sur le fin de course- ,pas bon non plus
 if((val == FDC_MOINS) && (SENS == SENS_MOINS)) return ERR_FDCMOINS;
 nb_pas = value;
 // si rattrapage de jeu
 rattrapage = 0;
 jeu = (long)tab_jeu[num_moteur];
 if((jeu>0)&&(SENS==SENS_MOINS)&&!init_on)
 {
  nb_pas -= jeu;
  rattrapage = 1;
 }
 nbr_pulse = labs(nb_pas);
 nb_mpas = correspondance_micropas[tab_micropas[num_moteur]]; 
 IEX3 = 0; // on remet à zero les flags d'it sur les fins de courses
 IEX4 = 0;
 move_on = 1; // flag de mouvement en cours
 start_horloge(vitesse *nb_mpas,nbr_pulse);
 EX3 = 1; // autorisation de l'it sur FDC-
 EX4 = 1; // autorisation de l'it sur FDC+
 write_tab_etat(MASQUE_MVT_ON,1); // bit move_on à 1
 return OK;
}
/*--------------------------LECTURE DES FINS DE COURSES-------------------*/
int read_fdc()
{
 return (P1 & 0x3);
}



/*-------------------LECTURE DES ETATS DYNAMIQUES DU SYSTEME-----------------*/
// durée de la fonction = 3.5ms
int read_status()
{
 /* comme la plupart des infos sont des bits, il faut passer par des variables char
    intermédiaires avant de faire des décalages
 */
 data unsigned char val0,val1,val2,val3,val4;
 data int val,val5;
 val = 0;
 val0 = move_on;
 val1 = end_move;
 val2 = init_on;
 val3 = autre;
 val4 = read_fdc();
 val5 = num_moteur;
 val = ( val0 | (val1<<1) | (val2<<2) | (val3<<5) | (val4<<6) | (val5<<8));
 return val;
}

int read_etats()
{
 write_rs232(read_status());
 return OK;
}
/*--------------------------CALCUL DE LA RAMPE D'ACCELERATION----------------*/
// durée de la fonction = 185ms
// Extarction de la racine carrée = 120ms
// si calcul en double = 460ms
// Le calcul s'arrete à la seconde immédiatement en dessous
// pour un déplacement inférieur ou égal à la moitié de la course
int calcul_rampe(unsigned int course)
{
 data long delta;
 data int t1,t2,t3,vmini,acc,vmaxi;
 data int racine_delta;
 t_acc = 0;
 x_acc = 0;
 vmini =tab_vmin[num_moteur];
 vmaxi =tab_vmax[num_moteur];
 acc = tab_acc[num_moteur];
 t3 = (vmaxi-vmini)/acc;
 // si vmin > vmax y a une erreur
 if (vmini > vmaxi ) return ERR_CALCUL;
 delta = (long)vmini*vmini + (long)acc*course;
 racine_delta = (int)sqrt((double)delta);
 t1 =(-vmini + racine_delta)/acc;
 t2 =(-vmini - racine_delta)/acc;
 if(t1 > 0) t_acc = t1;
 if(t2 > 0) t_acc = t2;
 if( (t3<t_acc) || (t3==0) )t_acc = t3;
 x_acc = acc*t_acc*t_acc/2 + vmini*t_acc;
 //printf("t1:%d, t2:%d, t3:%d ,t:%d, x:%d\n\r",t1,t2,t3,t_acc,x_acc);
 return OK; 
}

int read_rampe()
{
 printf("t:%d, x:%d\n\r",t_acc,x_acc);
 return OK;
}
