#ifndef __LIFEGAME_H__
#define __LIFEGAME_H__

#include <stdlib.h>
#include <stdio.h>


#include "../tools0_50/tools.h"
#include "../tools0_50/jstr.h"
#include "../tools0_50/hcharpix.h"
#include "../tools0_50/mfile.h"

typedef struct _lifegame *lifegame;
typedef unsigned int imgcolor;

//with hcharpix



//game of life
/* RULES
Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by over-population.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

struct _lifegame {
   
  hcharpix cell;
  int w;
  int h;
  char ccolor;
  char bg;
  intarray dead_rules; //0 = valeur min 1 = valeur max
  intarray alive_rules; //0 = underpop 1 = valeur min 2 = valeur max 3 overpop
  //bool *alive 9 booleen 2 | 3 a true
  //bool *dead 9 booleen 3 a true
};


extern int lifegame_menu(void);
extern int input_game_size(void);
extern void life_game_size(int gamesize, int *x, int *y); 

extern lifegame lifegame_create (int w, int h, char bg , char ccolor);
extern void lifegame_destroy (lifegame* L);
extern void lifegame_display (lifegame L);
extern int neighbor_count(lifegame L,int x,int y);
extern void get_level_size(lifegame L, int *x ,int *y);
extern bool is_cell_alive(lifegame L,int x ,int y);
extern void set_cell(lifegame L, int x, int y , bool alive);
extern void set_cell_debug(lifegame L, int x, int y ,int n, bool alive);
//copy a lifegame in a new lifegame
extern lifegame lifegame_clone(lifegame L);
extern void lifegame_next_gen(lifegame src, lifegame dst);
//a faire 31/10/16
//destroy : integral copy of src by erasing dst but dont create a new
extern void D_lifegame_clone(lifegame src, lifegame dst);
//my slip :) display nber of gen & nber of cell(s) alive
extern void lifegame_next_gen_til_N(lifegame L, int N, int pause);
//stop if gen dont evolve
extern void lifegame_next_gen_til_N_or_same_gen(lifegame L, int N, int pause);
// how many cells for a dead to be alive
extern intarray lg_dead_rules(void);
extern void set_dead_rules(lifegame L, int bmin, int bmax);

//how many cell underpop ,stay alive , overpopulation
extern intarray lg_alive_rules(void);
extern void set_alive_rules(lifegame L, int upop, int bmin, int bmax, int opop);
//check neighbor rules for dead cells & alive cells
extern bool lifegame_dead(lifegame L,int neighbor);
extern bool lifegame_alive(lifegame L,int neighbor);
//gestion jstr ?
extern void lifegame_write(lifegame A, mfile file);
extern void lifegame_save(lifegame A, char* filename);

extern lifegame lifegame_read(mfile file);
extern lifegame lifegame_load(char* filename);
//lifegame load aux ? 
#endif
