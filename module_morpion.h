#ifndef __MODULE_MORPION_H__
#define __MODULE_MORPION_H__

#include "char_key_tools.h"
#include "intarray.h"

typedef struct _morpion_grid morpion_grid; 

struct _morpion_grid
{
int num_jetons;
int num_p1;
int num_p2;
int stat_player1;
int stat_player2;
int game_status;
int num_game;
int ia;
int IA_play;
int player_1;
int player_2;
};



extern morpion_grid morpion_grid_create(void);
extern void print_tab_morp(char_table T);
extern void print_stat(morpion_grid m);
extern void morp_tab_init(intarray T);
extern char_table character_set(void);
extern void get_player_1(intarray T);
extern void get_player_2(intarray T);
extern void get_ia(intarray T);
extern void print_resultat (int n);
extern int num_played_game(int n);
extern void intarray_to_char_table (intarray T, char_table Charac, char_table prin_grid);
extern void intarray_to_m_grid (int mor_t[3][3], intarray T);
extern int game_status(int mor_t[3][3], morpion_grid m);
extern void morpion_debug(intarray T, int mor_t[3][3]);
extern int c_jetons(int mor_t[3][3]);

#endif
