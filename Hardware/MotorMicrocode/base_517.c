/******************************************************
 Project :  OHANA
 Author  : D.ZIG
 File    : base_517
 Subject : Programme principal
 Version	: 3.0
******************************************************/

#include "ohana.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*---------DECLARATIONS DES FONCTIONS UTILISEES---------*/
void init_rs232();
int print_erreur();
int last_command();
int version();

/*---------LE TABLEAU DES MNEMONIQUES ET DES COMMANDES---------*/
Code_cmd code tab_cmd[]= 
{
  {"MVT", bouge_moteur,1},
  {"SEL", select_mot,1}, 
  {"??", last_command,1},
  {"?ST", read_etats,1},
  {"?POS", affiche_position,1},
  {"?ETAT",read_tab_etat,1},
  {"STOP",stop,1},
  {"HALT",halt,1},
  {"INIT", init_mot,1},
  {"?INFO",read_info,1}, //lecture des infos de FDC et position pour tous les moteurs
  {"?SEL", read_select,1},
  {"START", start,1}, 
  {"?FDC", read_fin_course,1},
  {"VMIN", write_vmin,1},
  {"?VMIN", read_vmin,1},
  {"VMAX", write_vmax,1},
  {"?VMAX", read_vmax,1},
  {"INT", write_intensite,1},
  {"?INT", read_intensite,1},
  {"ACC", write_acceleration,1},
  {"?ACC", read_acceleration,1},
  {"MPAS", write_mpas,1},
  {"?MPAS", read_mpas,1},
  //{"ADR", write_adresse,1},
  //{"?ADR", read_adresse,1},
  {"POS", write_position,1},
  {"PHAS", write_phase,1},
  {"?PHAS",read_phase,1},
  {"JEU", write_jeu,1},
  {"?JEU", read_jeu,1},
  {"OFFSET", write_offset,1},
  {"?OFFSET", read_offset,1},
  {"?PARAM", affiche_param,1},
  {"L", luminosite,1},
  {"B", clignote,1},
  {"?ERR", print_erreur,1},
  {"?VER", version ,1},
  {"TAB",init_tab,1},
  {"?RAMPE", read_rampe,1},
  /* suite  */
};

int code nb_cmd = sizeof( tab_cmd )/sizeof(Code_cmd);

Code_err code tab_err[] =
{
  {OK,"OK"},
  {ERR_PARAM,"Erreur de parametre"},
  {ERR_TIMOUT,"Erreur de Timout"},
  {ERR_SYNTAXE,"Erreur de syntaxe"},
  {CMD_UNKNOW,"Commande inconnue"},
  {CMD_NODISP,"Commande indisponible"},
  {NO_CONNECT,"Moteur non connecté"},
  {ERR_FDCPLUS,"Fin de course aller actif"},
  {ERR_FDCMOINS,"Fin de course origine actif"},
  {ERR_ENABLE,"Moteur non alimenté"},
  {ERR_CALCUL," Erreur dans un calcul"},
  {ERR_GRAVE,"Grosse erreur interne"},
  /* suite */
};

int code nb_err = sizeof( tab_err )/sizeof( Code_err );

char xdata tamp_rs232[ NB_CHAR+1 ]; // le tampon de réception sur la ligne RS232
#ifdef VERSION_2
 code char annonce[] ="Ver:2.01 (Copyright:D.ZIG CNRS-LESIA/2003)\n\r"; 
#else
 code char annonce[] ="Ver:3.01 (Copyright:D.ZIG CNRS-LESIA/2003)\n\r";
#endif 
static int data code_fonc,index;
static code char delimiteur[] = {SPACE,TAB};
static code int nb_delimiteur = sizeof(delimiteur)/sizeof(char);
static char tampon_aff[NB_AFF+1];
static data char step_init =0; // compteur de sequence d'initialisation

bit cmd_recu; // flag de commande recue sur ligne série
bit init_on = 0; // flag d'initialisation en cours

/*--------------------------VARIABLES EXTERNES----------------------*/
extern bit rattrapage; // flag du rattrapage de jeu
extern bit move_on; // flag de mouvement en cours
extern bit end_move; // flag de fin de mouvement
extern bit autre;
extern char num_moteur; // numero du moteur selectionné
extern  xdata  long tab_position[]; // position
extern xdata unsigned int tab_vmin[];// vitesse
extern xdata          int tab_jeu[]; // valeur du rattrapage de jeu
extern data long nb_pulse; // défini dans timer.c
extern data long nb_pas;   // défini dans moteur .c
/* ---------------------------PROG PRINCIPAL-------------------*/

void main(void)
{
   long pos_zero;
	char data i,val, sequence_init;
	data int old_status, new_status;
	unsigned int course;
	init_hard(); // Initialisation de base 
	init_rs232(); // Initialisation du port RS232 
	pos_zero=0;
	sequence_init = 0;
	num_moteur = MOT_DEFAUT;
	old_status = read_status();
	brightness(4); // luminosité moyenne sur l'afficheur
	sprintf(tampon_aff,"OHANA V3");
	display(tampon_aff);
	/*-------------------------------BOUCLE PRINCIPALE--------------------------------*/
	while(1) 
	{
	  L1 = !L1; // pour tester la frequence de la boucle
	  // le flag cmd_recu est positionne par le routine d'IT 
	  if ( cmd_recu == ON )
	  {
	    cmd_recu = OFF; //flag a zero
	    for (i = 0;i < nb_cmd; i++) 
		 {
			val = strncmp (tamp_rs232 ,tab_cmd[i].chaine ,
			               strlen(tab_cmd[i].chaine));
			if ( val == 0 )
			{
			  code_fonc = (*tab_cmd[i].fonc)(); // on lance la fonction
			  break; // et on sort de la boucle for
			}
		 }// fin de boucle for
		 if (val) code_fonc = CMD_UNKNOW;
		 // envoi du caractère de fin d'execution sur la ligne série 
		 if (code_fonc != OK) printf(CMD_NOT_OK); 
		 else if (tab_cmd[i].prompt) printf(CMD_OK);
	  }// fin de if ( cmd_recu == ON )
	  /*----------------------------------------------------------------------------*/
	  /*---------------------------RAFRAICHISSEMENT DE L'AFFICHAGE------------------------------*/
	  new_status = read_status();
	  if	(new_status != old_status) // on ne rafraichit que si quelque chose change
	  {
		 if (!init_on && !rattrapage)
		 {
		  //printf("%d\n\r",new_status);
		  old_status = new_status;
		  if (!move_on && end_move)
		  {
		   //printf("end of move\n\r");
		   end_move = 0;// flag à zero
		   refresh_pos();
		   write_tab_etat(MASQUE_MVT_ON,0); // raz du bit move_on
		  }
		  if (!move_on)
		  { 
		    autre = OFF;
		    if (num_moteur)// on affiche la position du moteur
		    {
		      sprintf(tampon_aff,"%1d:%06ld",num_moteur, tab_position[num_moteur]);
		    }
		    else
		      sprintf(tampon_aff,"%1d:XXXXXX",num_moteur);
		  }
		  // si les deux fins de courses sont actifs, c'est qu'on est pas connecté
		  if ((new_status & MASQUE_FDCMOINS) && (new_status & MASQUE_FDCPLUS))
		    sprintf(tampon_aff,"%1d: NOT C",num_moteur);
		  else 
		  {
		   if (new_status & MASQUE_FDCMOINS) // sur le fin de course-
		      sprintf(tampon_aff,"%1d:  FDC-",num_moteur);
		   else if (new_status & MASQUE_FDCPLUS) // sur le fin de course+
		      sprintf(tampon_aff,"%1d:  FDC+",num_moteur);
		  }  		     		 
		}// fin de if (!init_on && !rattrapage)
		/*---------------------------SEQUENCE D'INITIALISATION------------------------*/
		if (init_on)
		{
		 sprintf(tampon_aff,"%1d:  INIT",num_moteur);
		 switch (step_init)
		 {
		  // STEP 1: debut de l'init, on remet a zero la phase et
		  //         on va chercher le fin de course origine
		  case 1: reset_phase();// raz phase à l'origine
		          //printf("STEP1\n\r");
		          write_tab_etat(MASQUE_INIT_ON,1); // on positionne le bit init_on à 1
		          write_tab_etat(MASQUE_INIT_OK,0); // on remet à zero le bit init_ok
		          move_mot(tab_vmin[num_moteur],COURSE_INIT);
		          step_init++;
		          break;
		  // STEP 2: on repart gentiment de l'offset defini dans tab_offset
		  case 2: 
		          if (!move_on)
		          {
		           //printf("STEP2\n\r");
		           wait(ATTENTE_MINI);
		           if (lect_offset()!=0) 
		           		move_mot(V_INIT,lect_offset());
		           step_init++;
		           wait(ATTENTE_MINI);
		          }
		          break;
		  // STEP 3: on met le compteur à zero, on coupe l'alim, on la remet
		  // et on repart vers le fin de course
		  case 3: 
		          if(!move_on)
		          {
		           //printf("STEP3\n\r");
		           pos_zero=0;
		           // mise a zero de la position
		           write_eeprom((char *)&tab_position[num_moteur],(char *)&pos_zero,sizeof(pos_zero));
		           selection_moteur(0);
		           wait(ATTENTE_MINI);
		           selection_moteur(num_moteur);
		           wait(ATTENTE_MINI);
		           move_mot(V_INIT,COURSE_INIT);
		           step_init++;
		          }
		          break;
		  //STEP 4:On repart de ce qu'il faut
		  case 4: 
		          if(!move_on)
		          { 
		           //printf("STEP4\n\r");
		           wait(ATTENTE_MINI);
		           refresh_pos(); // on note  où est le fin de course
		           course = abs(tab_position[num_moteur]);
		           move_mot(V_INIT,course);
		           step_init++;
		          }
		          break;
		  //STEP 5: on met le compteur position à zero, calcul de la phase à l'origine
		  // et c'est fini !!!! 
		  case 5: 
		          if(!move_on)
		          {
		           //printf("STEP5\n\r");
		           pos_zero=0;
		           nb_pas = 0; // on remet a zero avant refresh_pos (comprend qui peut)
		           calcul_phase_org(course);
		           write_eeprom((char *)&tab_position[num_moteur],(char *)&pos_zero,sizeof(pos_zero));
		           init_on = 0;
		           step_init = 0;
		           write_tab_etat(MASQUE_INIT_ON,0);// raz du bit init_on
		           write_tab_etat(MASQUE_INIT_OK,1);// init_ok à 1
		          }
		          break;             
		 }	 
		}// fin de if (init_on)
		
		/*---------------------------RATTRAPAGE DE JEU--------------------------------------------*/
		if(rattrapage)
	   {
		 if(!move_on)
		 {
		  refresh_pos(); //rafraichissement de la position dans la table
		  // on avance de la valeur du rattrapage de jeu
		  wait(1);
		  move_mot(tab_vmin[num_moteur],tab_jeu[num_moteur]);
		 }
	   }// fin de if (rattrapage)
	   
	   // affichage des infos
	   display(tampon_aff);
	  }// fin de if	(new_status != old_status)
	  
	  // si on bouge on rafraichit periodiquement l'affichage
	  if (!init_on && move_on)
	  {
	   visu_boucle();//pour voir la frequence de la boucle de scrutation
		// fonction speciale rapide pour afficher la position instantanée
		refresh_display(lect_pos());
	  }
	  
   }// FIN DE LA GRANDE BOUCLE WHILE
}// FIN DU MAIN
/*--------------------------FIN DE LA BOUCLE PRINCIPALE-------------------------*/

/*--------------------------INITIALISATION DU MOTEUR--------------*/
int init_mot()
{
 data int code_fct;
 data char val;
 val=read_fdc();
 if(val != (FDC_MOINS + FDC_PLUS))
 {
  if (num_moteur &&!move_on && !init_on)
  {
   init_on = 1;
   step_init = 1;
   code_fct = OK;
  }
 }
 else code_fct = CMD_NODISP;
 return code_fct;
}


/*-----------------------INIT DE LA COMMUNICATION SERIE----------------*/
/*       Mode 1 sur RX0, 9600Bds,8 bits,no parity, 1 bit stop
         sans controle de flux ( pas de XON/XOFF) IT autorisee          
 */

void init_rs232()
{
 SM1 = 1; // Mode 1
 BD = 1;  //Generateur de frequence interne
 PCON |= 0x80 ; // forcage du bit 7(SMOD) de PCON a 1 
 RI0 = 0 ; //flag de reception a zero
 REN0 = 1; // Autorisation de reception
 ES0 = 1; // Autorisation de l'IT sur le port RX0
}

/*------------------------ROUTINE D'IT SUR LIGNE RX0-----------------*/
void it_rs232( void ) interrupt  4
{
  data char c;
  if ( RI0 == 1 ) //Si l'IT vient de la reception on la traite
  {
    c = S0BUF;
    RI0 = 0; // Raz du flag de reception
    // le retour chariot est detecté
    if (c == CR) 
    {
      tamp_rs232[index] = 0;
      index =0;
      cmd_recu = ON; 
      return;
    }
    /* LF  est ignoré */
    if ( c == LF ) return;
    if (index == NB_CHAR) return; // pour eviter de deborder le buffer
    if ( isascii(c) )
    {
      tamp_rs232[index] = toupper(c);
      index++;
    }
  }  
}

/*------------------------------INITIALISATION TRES HARD-----------------------------*/
void init_hard()
{
 SYSCON &= 0xFE ; // Validation de l'usage de la XRAM interne ( Adr 0xF800 )
 // priorité sur les interruptions
 IP0 = 0x2C;
 IP1 = 0x22;
 I3FR = 1; // it de fdc- sur front montant
 EAL = ON; // Validation générale des IT
 HORLOGE = OFF;
 VAL_EEPROM = OFF; // validation des ecritures sur l'EEPROM
}

/*-----------------------EXTRACTION DU PARAMETRE ENTIER---------------*/
int extract_int_param(int *param)
{
 char * pt;
 int i;
 for ( i=0; i< nb_delimiteur; i++)
 {
   pt = (char *)strchr( tamp_rs232,delimiteur[i] );
   if ( pt != NULL )
   {
     pt++;
     if( strlen(pt) == 0 ) return ERR_PARAM; 
     *param = atoi( pt );
     return OK ;
   }
 }
 return ERR_SYNTAXE;
}

/*-----------------------EXTRACTION DU PARAMETRE LONG-------------------*/
int extract_long_param(long *param)
{
 char * xdata pt;
 int i;
 for ( i=0; i< nb_delimiteur; i++)
 {
   pt = (char *)strchr( tamp_rs232,delimiteur[i] );
   if ( pt != NULL )
   {
     pt++;
     if( strlen(pt) == 0 ) return ERR_PARAM;
     *param = atol( pt );
     return OK ;
   }
 }
 return ERR_SYNTAXE;
}

/*-----------------------EXTRACTION DU PARAMETRE FLOTTANT---------------*/
int extract_float_param(double *param)
{
 char *pt;
 int i;
 for ( i=0; i< nb_delimiteur; i++)
 {
   pt = (char *)strchr( tamp_rs232,delimiteur[i] );
   if ( pt != NULL )
   {
     pt++;
     if( strlen(pt) == 0 ) return ERR_PARAM;
     *param = atof( pt );
     return OK ;
   }
 }
 return ERR_SYNTAXE;
}
/*-------------------------ECRITURE SUR LIGNE SERIE------------*/
void write_rs232(int c)
{
 printf("%d\n\r",c);
}

void write_float_rs232( double var )
{
 printf("%.2f\n\r",var);
}

/* -------LECTURE DU CODE DE RETOUR DE LA DERNIERE FONCTION APPELEE--*/
int last_command()
{
 write_rs232(code_fonc);
 return OK;
}

/*-----------------LECTURE DE LA SIGNIFICATION DU CODE DE RETOUR--*/
int print_erreur()
{
 data unsigned char i;
 int param,code_fct;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
    for ( i=0 ; i< nb_err ; i++ )
    {
       if ( tab_err[i].erreur == param )
       {
         puts(tab_err[i].chaine );
         return OK;
       }
    }
    puts("Erreur non repertoriee\n\r");
    code_fct = OK;
 }
 return code_fct;
}

/*-----------------------LECTURE DU MESSAGE D'ANNONCE----------*/
int version()
{
 puts(annonce);
 return OK;
}














