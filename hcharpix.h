#ifndef __HCHARPIX_H__
#define __HCHARPIX_H__

/* public : C->w = width ; C->h = height */
//hcharpix harlock
#include "jstr.h"
#include "hcharpix.h"
#include "tools.h"
#include "mfile.h"

typedef struct _hcharpix *hcharpix;

struct _hcharpix
{
  jstr * data;
  int h;
  int w;
  char init;
  int x;
  int y;
};


/* le curseur est placé en position (0,0) */
extern hcharpix hcharpix_create (int width, int height, char bg);
extern void hcharpix_destroy (hcharpix C);

/* getter et setter de la position (x, y)*/
extern char hcharpix_get_bg(hcharpix C);
extern char hcharpix_get_xy (hcharpix C, int x, int y);
extern void hcharpix_set_xy (hcharpix C, int x, int y, char c);
extern void hcharpix_revert_xy (hcharpix C, int x, int y);
/* revert remet la valeur bg de hcharpix_create à la position (x, y) */

/* getter et setters de la position du curseur */
extern char hcharpix_get (hcharpix C);
extern void hcharpix_set (hcharpix C, char c);
extern void hcharpix_revert (hcharpix C);

/* réinitialisation de tout le hcharpix */
extern void hcharpix_revert_all (hcharpix C);


extern void hcharpix_display (hcharpix C);
extern void hcharpix_add( hcharpix C, int i, jstr j);
/* place le curseur au début de la ligne y */
extern inline void hcharpix_goto_line (hcharpix C, int y);

/* déplacements du curseur */
extern inline void hcharpix_goto_next (hcharpix C);
/* si le curseur est à une fin de ligne, goto_next le place
   au début de la ligne suivante. */
extern inline void hcharpix_goto_previous (hcharpix C);
/* si le curseur est à un début de ligne, goto_previous le place
   à la fin de la ligne précédente */
extern inline void hcharpix_step_up (hcharpix C);
extern inline void hcharpix_step_down (hcharpix C);
extern inline void hcharpix_rmright(hcharpix C);//reste sur la meme row
extern inline void hcharpix_rmleft(hcharpix C);//row move left
extern inline void hcharpix_cmup(hcharpix C);//reste sur la meme column column move up
extern inline void hcharpix_cmdown(hcharpix C); 


extern void hcharpix_add( hcharpix C, int i, jstr j);
extern char * char2string(int strsize, char bg);

extern void hcharpix_bound(hcharpix O,int* x, int* y ,int* x2, int* y2);
extern void hcharpix_draw_horline (hcharpix C, int y, int x1, int x2, char c);//trace des lignes horizontales


extern void hcharpix_draw_verline (hcharpix C, int x, int y1, int y2, char c);//trace des lignes verticales


extern inline void hcharpix_goto_xy (hcharpix C, int x, int y);//place le curseur a xy

extern hcharpix hcharpix_clone (hcharpix C);
extern void hcharpix_copy (hcharpix O, int ox, int oy, int ox2, int oy2, hcharpix TG, int tgx, int tgy);

// a ecrire 31/10/16 cour 57
extern int hcharpix_diffcount(hcharpix C1, hcharpix C2);

extern bool hcharpix_equal(hcharpix C1, hcharpix C2); 

//extern void hcharpix_copy_alpha (hcharpix O, int ox, int oy, int ox2, int oy2, hcharpix TG, int tgx, int tgy);

extern int get_xy_neighbor(hcharpix C, int x, int y);
extern void hcharpix_full_box(hcharpix C, int x1, int x2, int y1, int y2, char c);
extern void hcharpix_circlesym8(hcharpix C, int xcenter, int ycenter, int radius, char e);
extern void hcharpix_full_circlesym8(hcharpix C, int xcenter, int ycenter, int radius, char e);

//charpix fonction mfile

extern void hcharpix_write(hcharpix A, mfile file);
extern void hcharpix_save( hcharpix C, char* filename);

extern hcharpix hcharpix_read(mfile file);
extern hcharpix hcharpix_load(char * filename);
extern void hcharpix_coordonates(hcharpix H, int *x, int *y);
#endif
