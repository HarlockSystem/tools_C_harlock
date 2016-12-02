#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "module_morpion.h"
/* la table s'initialise avec morpion_grid qui va pointer vers un intarray et je passerais d'un intarray a un char table pour afficher les info les donner seront traiter via un intarray facilitant la manipulation des donnee, et l'ia sera gerer via morpion_grid pour une lecture facilite du tableau de jeux je peux deja finir l'exercice demander uniquement en char table et implemter l'ia plus tard*/




void morpion_debug(intarray T, int mor_t[3][3])
{
  int i,j,k;
  for (i = 0; i<3; i++)
    {
      for (j = 0; j<3 ; j++)
	printf("morpion grid [%d][%d] : %d\n" ,i , j ,mor_t[i][j]);
    }

  
for (k = 0; k < 9;k++)
  {

    printf("morpion.data[%d] : %d\n" ,k , T->data[k]);
  }
}


morpion_grid morpion_grid_create(void)
{
  morpion_grid m;
  m.num_jetons = 0;
  m.num_p1 = 0;
  m.num_p2 = 0;
  m.stat_player1 = 0;
  m.stat_player2 = 0;
  m.game_status = 0;
  m.num_game = 0;
  m.ia = 2;
  m.IA_play = 0;
  m.player_1 = 1;
  m.player_2 = 2;
  return m;
}
  
void print_tab_morp(char_table T)
{
 
  printf("\n    | %c | %c | %c |        | %d | %d | %d |\n",T.data[0], T.data[1], T.data[2] ,1 ,2 ,3 );
  printf("    _____________        ____________\n");
  printf("    | %c | %c | %c |        | %d | %d | %d |\n",T.data[3], T.data[4], T.data[5] ,4 ,5 ,6);
  printf("    _____________        ____________\n");
  printf("    | %c | %c | %c |        | %d | %d | %d |\n\n",T.data[6], T.data[7], T.data[8] ,7 ,8 ,9);
}

void print_stat(morpion_grid m)
{
  printf("\n\n%d victoire(s) joueur 1\n%d victoire(s) joueur 2\n%d partie(s) jouee(s)\n\n",m.stat_player1 ,m.stat_player2 ,m.num_game);
}


void morp_tab_init(intarray T)
{
  int i;
  for (i = 0; i < 9; i++)
    {
      T->data[i] = 0;
    }
}

char_table character_set(void)
{
  char_table K = key_table_create(3);
  char* charc = ".XO";
  K.data = charc; 
  return K;
}

void get_player_1(intarray T)
{
  int i;
  printf("\njoueur 1 X a vous de jouer : "); 
  scanf("%d", &i);

 if (i < 1 || i > 9)
    {
      printf("\nentrez un chiffre entre 1 et 9 : "); 
      scanf("%d", &i);
    }
  if (T->data[i -1] > 0)
    {
      printf("\ncette case est deja prise choisissez une autre case : "); 
      scanf("%d", &i);
    }

  else
    T->data[i -1] = 1;
}

void get_player_2(intarray T)
{
  int i;
  printf("\njoueur 2 O a vous de jouer : "); 
  scanf("%d", &i);

 if (i < 1 || i > 9)
    {
      printf("\nentrez un chiffre entre 1 et 9"); 
     scanf("%d", &i);
    }
  if (T->data[i -1] > 0)
    {
      printf("\ncette case est deja prise choisissez une autre case"); 
      scanf("%d", &i);
    }
  else
    T->data[i - 1] = 2;
}

void get_ia(intarray T)
{
  int i;
  printf("joueur 2 O a vous de jouer : "); 
  scanf("%d", &i);
  
  if (i < 1 || i > 9)
    {
      printf("entrez un chiffre entre 1 et 9"); 
  scanf("%d", &i);
    }
  if (T->data[i] > 0)
    {
      printf("cette case est deja prise choisissez une autre case"); 
      scanf("%d", &i);
    }
  else
    T->data[i] = 2;
}


void print_resultat (int n)
{
  if (n == 1)
    {
      printf("\n\njoueur 1 X a gagne !\n\n"); 
    }
  else if (n == 2)
    {
      printf("\n\njoueur 2 O a gagne !\n\n");
    }

  else if (n == 3)
    {
      printf("\n\nDraw Game !\n\n");
    }

}
 

int num_played_game(int n)
{
  n++;
  return n;
} 


void intarray_to_char_table (intarray T, char_table Charac, char_table print_grid)

{
  int i;
  for(i = 0 ; i< 9; i++)
    {
      print_grid.data[i] =  Charac.data[T->data[i]];
    }
}

				
void intarray_to_m_grid (int mor_t[3][3], intarray T)
{
  int j, k,i = 0;
      for (j = 0; j < 3 ; j++)
	{
	  for( k = 0; k < 3; k++)
	    {
	      mor_t[j][k] = T->data[i];
	    i++;
	    }

	}
}


int game_status(int mor_t[3][3], morpion_grid m)
 {
   int a = 0, b = 1 ,c = 2, res;

   if ( (mor_t[a][a]==b && mor_t[a][b]==b && mor_t[a][c]== b) || (mor_t[b][a]==b && mor_t[b][b]==b && mor_t[b][c] == b) || (mor_t[c][a]==b && mor_t[c][b]==b && mor_t[c][c] == b) || (mor_t[a][a]==b && mor_t[b][a]==b && mor_t[c][a] == b) || (mor_t[a][b]==b && mor_t[b][b]==b && mor_t[c][b] == b) || (mor_t[a][c]==b && mor_t[b][c]==b && mor_t[c][c] == b) || (mor_t[a][a]==b && mor_t[b][b]==b && mor_t[c][c] == b) || (mor_t[a][c]==b && mor_t[b][b]==b && mor_t[c][a] == b))
     res = 1;

   else if ( (mor_t[a][a]==c && mor_t[a][b]==c && mor_t[a][c] == c) || (mor_t[b][a]==c && mor_t[b][b]==c && mor_t[b][c] == c) || (mor_t[c][a]==c && mor_t[c][b]==c && mor_t[c][c] == c) || (mor_t[a][a]==c && mor_t[b][a]==c && mor_t[c][a] == c) || (mor_t[a][b]==c && mor_t[b][b]==c && mor_t[c][b] == c) || (mor_t[a][c]==c && mor_t[b][c]==c && mor_t[c][c] == c) || (mor_t[a][a]==c && mor_t[b][b]==c && mor_t[c][c] == c) || (mor_t[a][c]==c && mor_t[b][b]==c && mor_t[c][a] == c) )
      res = 2;

   else if (m.num_jetons == 9)
      res = 3 ;

   else if (m.num_jetons < 9)
      res = 0;

 
    return res;
    }



int c_jetons(int mor_t[3][3])
{
  int i ,j, jetons = 0 ;
  for (i = 0 ; i < 3 ; i++)
    {
      for(j = 0 ; j < 3 ; j++)
	{
	  if (mor_t[i][j] != 0)
	    {
	    jetons++;
	    }
	}
    }
  return jetons;
}
  
  
