/******************************************************
 Project : 
 Author  :D.ZIG
 File    :
 Subject : fichier header 
 Version	:3.0
******************************************************/
#ifndef _base_517_h
#define _base_517_h

#include <reg517a.h>                                                              

/*-----------------------LES CONSTANTES-----------------------*/
#define NB_CHAR	60 // tampon de reception de la ligne série
#define CR 0x0D // Carriage return 
#define LF 0x0A // Line feed 
#define SPACE ' '
#define TAB '\t'
#define CMD_OK ">" // Commande OK
#define CMD_NOT_OK "!>" // Problême sur commande

#define ON						1
#define OFF						0

#define OK						0
#define CMD_UNKNOW			1
#define ERR_PARAM 			2
#define ERR_TIMOUT			3
#define ERR_SYNTAXE 			4
#define CMD_NODISP         5 // commande indisponible
#define NO_CONNECT         6 // moteur non connecté
#define ERR_FDCPLUS        7 // moteur en fin de course +
#define ERR_FDCMOINS       8 // moteur en fin de course origine
#define ERR_ENABLE         9 // moteur non alimenté
#define ERR_CALCUL         10 // Erreur dans un calcul
#define ERR_GRAVE           11 // Grosse erreur
/*------------------definition des structures--------------- */
typedef struct
{
  char code *chaine;  
  int (*fonc)();
  int prompt; // indique si on renvoie le prompt sur la ligne serie ou non
} Code_cmd;

typedef struct
{
  char erreur;
  char code *chaine;
}Code_err;

typedef unsigned long Ulong;
/*------------------------------------------------------------*/


/*---------------------Prototypes des fonctions de base-------*/
int init_mot(); // initialisation du moteur
void init_hard();
void write_rs232( int c );
void write_float_rs232( double var );
int extract_int_param(int *param);
int extract_long_param( long *param);
int extract_float_param(double *param);
#endif  // _base_517_h 
