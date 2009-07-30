 /******************************************************
 Project :  
 Author  : D.ZIG
 File    : afficheur.c
 Subject : Controle de l'afficheur HDSP-210X
 Version	: 3.0
******************************************************/
#include "ohana.h"
#include <string.h>

/*---------------------ADRESSE DE L'AFFICHEUR------------*/
at 0x838 xdata unsigned char AFFICHEUR[NB_AFF]; // les 8 digits de l'afficheur
at 0x830 xdata unsigned char CWR_AFF; // control word register de l'afficheur
at 0x839 xdata unsigned char P_TEST; // 2ieme caractere de l'afficheur

/*-------------------------P'TITES FONCTIONS---------------*/
// envoi d'une chaine de caracteres vers l'afficheur
int  display(char *message)
{
  data char i,val;
  val =strlen(message);
  // si la longueur du message dépasse l'affichage, on tronque 
  if (val > NB_AFF) val = NB_AFF;
  for(i=0;i<val;i++) AFFICHEUR[i] = message[i];
  // Si besoin, on remplit avec des espaces
  if (val < NB_AFF)
  {
   for(i = val;i <NB_AFF ;i++) AFFICHEUR[i] = SPACE;
  }
  return OK;
}

/* 
   pour afficher la position courante sur l'afficheur sans passer par le sprintf qui bouffe du temps
   pour l'instant, on ne sait traiter que des valeurs positives
   durée de la fonction 190ms 
*/
void refresh_display(long val)
{
 data int reste,i;
 data long res;
 res = val;
 i=NB_AFF-1;
 while(res!=0)
 {
  reste = (res % 10) + 0x30;// reste est convertie en caractère ASCII
  res =res / 10;
  AFFICHEUR[i]=reste;
  i--;
 }
 while(i>=2)
 {
  AFFICHEUR[i]=0x30;// caractère  0 en ASCII
  i--;
 }
}

// reset de l'afficheur
int reset_display( void)
{
  return OK;
}

// controle de la luminosite de l'afficheur
// 0 -> eteint , 7 -> maximum
int brightness( int val)
{
 CWR_AFF = (CWR_AFF & 0xF8) | (~val & 0x7); // masques
 return OK;
}

// appel de brightness via la ligne serie
int luminosite( )
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < 0) || (param > 7) ) return ERR_PARAM;
   code_fct = brightness( param );
 }
 return code_fct;
}

// clignotement de l'afficheur
int blink( char val )
{
  unsigned int masque;
  if (val) masque = 0x10;
  else masque = 0;
  CWR_AFF = (CWR_AFF & 0xEF) | masque;
  return OK;
 }
 
int clignote()
{
 int code_fct, param;
 code_fct = extract_int_param(&param);
 if (code_fct == OK)
 {
   // c'est la qu'on execute la commande 
   if ( (param < 0) || (param > 1) ) return ERR_PARAM;
   code_fct = blink( param );
 }
 return code_fct;
}

/* tite fonction pour visualiser la fréquence de la boucle de scrutation */
void visu_boucle(void)
{
 if (P_TEST == 0x3A) P_TEST = 0x20;// on affichage les caracteres ":" ou espace
 else P_TEST = 0x3A;
}

