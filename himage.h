#ifndef __HIMAGE_H__
#define __HIMAGE_H__

/* public : C->w = width ; C->h = height */
//himage harlock
#include "himage.h"
#include "tools.h"
#include "mfile.h"

typedef struct _himage S_image; 
typedef struct _himage *himage;
typedef unsigned char imgcompo;
typedef unsigned int imgcolor;

			  
struct _himage
{
  
  imgcolor * pixel;
  int h;
  int w;
  imgcolor color;
  imgcolor init;
  int x;
  int y;
};


/* le curseur est placé en position (0,0) */
extern himage himage_create_skel (int width, int height, imgcolor bg);
void himage_alloc_mem(himage C);
extern void himage_destroy_ligth (himage C);
extern himage himage_create_and_alloc(int width, int height, imgcolor bg );
extern void himage_destroy_full (himage* C);


/* getter et setter de la position (x, y)*/
extern imgcolor himage_get_xy (himage C, int x, int y);
extern void himage_set_xy (himage C, int x, int y, imgcolor c);
extern void himage_revert_xy (himage C, int x, int y);
/* revert remet la valeur bg de himage_create à la position (x, y) */

/* getter et setters de la position du curseur */
extern imgcolor himage_get (himage C);
extern void himage_set (himage C, imgcolor c);
extern void himage_revert (himage C);

/* réinitialisation de tout le himage */
extern void himage_fill_all (himage C, imgcolor i);


extern void himage_display (himage C);

/* place le curseur au début de la ligne y */
extern inline void himage_goto_line (himage C, int y);

/* déplacements du curseur */
extern inline void himage_goto_next (himage C);
/* si le curseur est à une fin de ligne, goto_next le place
   au début de la ligne suivante. */
extern inline void himage_goto_previous (himage C);
/* si le curseur est à un début de ligne, goto_previous le place
   à la fin de la ligne précédente */
extern inline void himage_step_up (himage C);
extern inline void himage_step_down (himage C);

//extern void himage_add( himage C, int i, imgcolor j);


extern void himage_bound(himage O,int* x, int* y ,int* x2, int* y2);
extern void himage_draw_horline (himage C, int y, int x1, int x2, imgcolor c);//trace des lignes horizontales


extern void himage_draw_verline (himage C, int x, int y1, int y2, imgcolor c);//trace des lignes verticales


extern inline void himage_goto_xy (himage C, int x, int y);//place le curseur a xy

extern himage himage_clone (himage C);
extern void himage_copy (himage O, int ox, int oy, int ox2, int oy2, himage TG, int tgx, int tgy);
//extern void himage_copy_alpha (himage O, int ox, int oy, int ox2, int oy2, himage TG, int tgx, int tgy);


extern void himage_full_box(himage C, int x1, int x2, int y1, int y2, imgcolor c);
extern void himage_circlesym8(himage C, int xcenter, int ycenter, int radius, imgcolor e);
extern void himage_full_circlesym8(himage C, int xcenter, int ycenter, int radius, imgcolor e);

//image fonction mfile


extern himage himage_read(mfile file);
extern himage himage_load(char * filename);

//cours 62
extern imgcolor image_make_color(imgcompo r, imgcompo g ,imgcompo b);
extern void img_get_color_compo(imgcolor c, imgcompo* r, imgcompo* g ,imgcompo* b);
extern void img_color_debug(imgcolor c);
extern void himage_write(himage A, mfile file);
extern void himage_save( himage C, char* filename);
extern void himage_rd_or_ignor_sharp_comments(mfile file, bool comments);


#endif
