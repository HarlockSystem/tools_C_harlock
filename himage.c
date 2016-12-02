#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "himage.h" //add -lm


himage himage_create_skel (int width, int height, imgcolor bg)//quadratique
{
  imgcolor color = image_make_color(0, 0, 0);
  assert ((height > 0) && (width > 0));
  himage C = tools_malloc (sizeof (struct _himage));
  C->h = height;
  C->w = width;
  C->x = 0;
  C->y = 0;
  C->color =  color;
  C->init = bg;
  return C;
}


himage himage_create_and_alloc(int width, int height, imgcolor bg )
{
  himage C = himage_create_skel(width,height,bg );
  himage_alloc_mem(C);
  return C;
}


void himage_alloc_mem(himage C)
{
  C->pixel = tools_malloc (sizeof (imgcolor)*  (C->w * C->h));
}


void himage_destroy_light(himage *C)
{
  himage C2 =*C;
  tools_free(&C2, sizeof(struct _himage));
  *C = NULL;
}


void himage_destroy_full (himage* C)
{
  himage C2 = *C;
  tools_free (C2->pixel,(sizeof (unsigned int)*  (C2->w * C2->h)));
  tools_free (C2 ,sizeof(struct _himage));
  *C = NULL;
}


imgcolor himage_get_xy (himage C, int x, int y)
{
  imgcolor c = C->pixel[y * C->w + x];
  return c;
}


void himage_set_xy (himage C, int x, int y, imgcolor c)
{
  C->pixel[y * C->w + x] =  c;
}


void himage_revert_xy(himage C, int x, int y)
{ 
 C->pixel[y * C->w + x] = C->init;
}


imgcolor himage_get (himage C)
{
  imgcolor c = C->pixel[C->y * C->w + C->x];
  return c;
}


void himage_set (himage C, imgcolor c)
{
  C->pixel[C->y * C->w + C->x] =  c;
}


void himage_revert(himage C)
{
  C->pixel[C->y * C->w + C->x] =  C->init;
}

void himage_fill_all(himage C, imgcolor i)
{
  int j;
  for (j = 0; j < (C->h * C->w);j++)
    {
      C->pixel[j] = i;
    }
}


/*void himage_fill_all(himage C)
{
  int i;
  imgcolor* ptr = C->pixel;
    for(i = 0; i < (C->h * C->w); i++)
    {
       *ptr = C->init;
       ptr++;
    }
}
*/


void himage_display (himage C) //quadratique
{
  int i;
  fprintf(stdout,"\n");
  for (i = 0; i< (C->h * C->w); i++)
    {
      fprintf(stdout,"%u",C->pixel[i]);
      if ( i % C->w == 0)
	RC;
    }
  fprintf(stdout,"\n");
}


inline
void himage_goto_line (himage C, int y)//constant
{
  if ((y < C->h) && (y >= 0)) 
    {
      C->y = y;
    }
  else
    {
      fprintf(stderr,"entrez un chiffre entre 0 et %d",C->y); 
    }
}
  
inline
void himage_goto_next(himage C)//constant
{
  C->x++;
  if (C->x > (C->w-1))
    {
      C->x = 0;
      himage_step_down(C);
    }
}

inline
void himage_goto_previous(himage C)//constant
{
  C->x--;
  if (C->x < 0)
    {
      C->x = (C->w-1);
      himage_step_up(C);
    }
}

inline
void himage_step_up(himage C)//constant
{
  C->y--;
  if (C->y < 0)
    {
      C->y = (C->h-1);
    }
}

inline void himage_step_down(himage C)//constant
{
  C->y++;
  if (C->y > (C->h-1))
    {
      C->y = 0;
    }
}





void himage_draw_horline (himage C, int y, int x1, int x2, imgcolor c)//trace des lignes horizontales, linéaire
{
  int i;
  if (y < 0)
    {
      fprintf(stderr," y out of bound set y to 0");
      y = 0;
    }
  if (x1 < 0)
    {
      fprintf(stderr, " x out of bound set x to 0");
      x1 = 0;
    }
  if (y > (C->h -1))
    {
      fprintf(stderr," y out of bound set y to %d",(C->h -1));
      y = (C->h -1);
    }
  if (x1 > (C->w -1))
    {
      fprintf(stderr," x1 out of bound set x1 to %d",(C->w -1));
      x1 = (C->w -1);
    }
  if(x2 > (C->w -1))
    {
      fprintf(stderr," x2 out of bound set x2 to %d",(C->w -1));
      x2 = (C->w -1);
    }
   if (x2 < 0)
    {
      fprintf(stderr, " x out of bound set x to 0");
      x2 = 0;
    }
   C->y = y;
   C->x = x1;
   
   if ((x2 - x1) < 0)
	{
	  for (i = 0; i > (x2 - x1); i--)
	    {
	      himage_set(C, c);
	      himage_goto_previous(C);
	    }
	}
      if ((x2 - x1) > 0)
	{
	  for(i =0; i < (x2 - x1); i++)
	    {
	      himage_set(C, c);
	      himage_goto_next(C);
	    }
	}
      if ((x2 - x1) == 0)
	himage_set(C,c);    
}


void himage_draw_verline (himage C, int x, int y1, int y2, imgcolor c)//trace des lignes verticales, linéaire
{
 int i;
  if (x < 0)
    {
      fprintf(stderr," x out of bound set x to 0");
      x = 0;
    }
  if (x > (C->w -1))
    {
      fprintf(stderr," x out of bound set x to %d",(C->w -1));
      x = (C->w -1);
    }
  if (y1 < 0)
    {
      fprintf(stderr, " y out of bound set y to 0");
      y1 = 0;
    }
  if (y1 > (C->h -1))
    {
      fprintf(stderr," y out of bound set y to %d",(C->h -1));
      y1 = (C->h -1);
    }
  if (y1 > (C->h -1))
    {
      fprintf(stderr," y1 out of bound set y1 to %d",(C->w -1));
      y1 = (C->h -1);
    }
  if (y2 > (C->h -1))
    {
      fprintf(stderr," y2 out of bound set y2 to %d",(C->w -1));
      y2 = (C->h -1);
    }
      if (y2 < 0)
    {
      fprintf(stderr, " y2 out of bound set y2 to 0");
      y2 = 0;
    }

      C->x = x;
      C->y = y1;
   
      if ((y2 - y1) < 0)
	{
	  for (i = 0; i > (y2 - y1); i--)
	    {
	      himage_set(C, c);
	      himage_step_up(C);
	    }
	}
      if ((y2 - y1) > 0)
	{
	  for(i =0; i < (y2 - y1); i++)
	    {
	      himage_set(C, c);
	      himage_step_down(C);
	    }
	}
      if ((y2 - y1) == 0)
	himage_set(C,c);    
}


inline void himage_goto_xy (himage C, int tgx, int tgy)//place le curseur a xy, constant
{
if (tgx < 0)
  {
    fprintf(stderr, "x out of bound set x to 0");
      C->x = 0;
  }
if (tgx > (C->w -1))
  {
    fprintf(stderr,"x out of bound set x to %d", (C->w -1));
    C->x = (C->w -1);
  }

if (tgy < 0)
  {
    fprintf(stderr, "y out of bound set y to 0");
    C->y = 0;
  }
if (tgy > (C->h -1))
  {
    fprintf(stderr, "y out of bound set y to %d", (C->h -1));
    C->y = (C->h -1);
  }
if (tgx > 0 && tgx < (C->w -1))
 C->x = tgx;
if (tgy > 0 && tgy < (C->h -1))
C->y = tgy;
}

himage himage_clone (himage C)
{
   int i;
   himage CP = himage_create_and_alloc(C->w, C->h, C->init);
   
   for (i=0; i < C->h; i++)
     {
       CP->pixel[i] = C->pixel[i];
     }
   return CP;
 }

void himage_bound(himage O,int* x, int* y ,int* x2, int* y2)
{
  int ox = *x;
  int oy = *y;
  int ox2 = *x2;
  int oy2 = *y2;
  
  if(ox < 0)				   
    {
     ox = 0;
    }
  if(oy < 0)
    {
      oy = 0;
    }
  if(oy > (O->h -1))
    {
      oy = (O->h -1);
    }
  if(ox > (O->w -1))
    {
      ox = (O->w -1);
    }
  if(ox2 < 0)
    {
      ox = 0;
    }
   if(ox2 > (O->w -1))
    {
      ox2 = (O->w -1);
    }
  if(oy2 < 0)
    {
      oy2 = 0;
    }
  if(oy2 > (O->h -1))
    {
      oy2 = (O->h -1);
    }
  
  *x = ox;
  *y = oy;
  *x2 = ox2;
  *y2 = oy2;
}


void himage_copy (himage O, int ox, int oy, int ox2, int oy2, himage TG, int tgx, int tgy)
 {
   int i; int j;int tgx2 = tgx;
   if(ox < 0)
    {
      fprintf(stderr," ox out of bound set ox to 0");
      ox = 0;
    }
  if(oy < 0)
    {
      fprintf(stderr, " oy out of bound set oy to 0");
      oy = 0;
    }
  if(oy > (O->h -1))
    {
      fprintf(stderr," oy out of bound set oy to %d",(O->h -1));
      oy = (O->h -1);
    }
  if(ox > (O->w -1))
    {
      fprintf(stderr," ox out of bound set ox to %d",(O->w -1));
      ox = (O->w -1);
    }
 if(ox2 < 0)
    {
      fprintf(stderr," ox2 out of bound set ox2 to 0");
      ox = 0;
    }
  if(oy2 < 0)
    {
      fprintf(stderr, " oy2 out of bound set oy2 to 0");
      oy2 = 0;
    }
  if(oy2 > (O->h -1))
    {
      fprintf(stderr," oy2 out of bound set oy2 to %d",(O->h -1));
      oy2 = (O->h -1);
    }
  if(ox2 > (O->w -1))
    {
      fprintf(stderr,"ox2 out of bound set ox2 to %d",(O->w -1));
      ox2 = (O->w -1);
    }
  if (tgx < 0)
    {
      fprintf(stderr," tgx out of bound set tgx to 0");
      tgx = 0;
    }
  if (tgy < 0)
    {
      fprintf(stderr, " oy2 out of bound set oy2 to 0");
      tgy = 0;
    }
  if (tgx > (TG->w -1))
    {
      fprintf(stderr," oy2 out of bound set oy2 to %d",(TG->w -1));
      tgx = (TG->w -1);
    }
  if (tgy > (TG->h -1))
    {
      fprintf(stderr,"ox2 out of bound set ox2 to %d",(TG->h -1));
      tgy = (TG->h -1);
    }			       

  printf("\n");
    
      for (i = oy; i < (oy2+1) ; i++)
	{
	for (j = ox; j < (ox2+1) ;j++)
	  {
	    himage_set_xy (TG,tgx2,tgy,himage_get_xy(O, j,i));
	    tgx2++;
	    if (tgx2 > (TG->w-1))
		break;
	  }
	tgy++;
	tgx2 = tgx;
	if(tgy > (TG->h -1))
	   break;
	}
    
 }


void himage_full_box(himage C, int ox1, int ox2, int oy1, int oy2, imgcolor c)
{
  int i,j;
  if ( ox1 > ox2)//check and swap
    {
    int swapx = ox1;
    ox1 = ox2;
    ox2 = swapx;
    }
  
  if( oy1 > oy2)
    {
      int swapy = oy1;
      oy1 = oy2;
      oy2 = swapy;
    }
  int x1, y1,x2, y2;//give coord to f() check and correct value
  x1 = ox1;
  x2 = ox2;
  y1 = oy1;
  y2 = oy2;
  himage_bound(C, &x1, &y1, &x2,&y2);
  for (i = y1; i < (y1 + 1 + (y2 - y1)); i++)
	 for (j = x1; j < (x1 + 1 + (x2 - x1)); j++)
	{
	  himage_set_xy(C, j, i, c);
	}
}




void himage_circlesym8(himage C, int xcenter, int ycenter, int radius, imgcolor e)//lineaire
{
  int x, y, r2;
  r2  = radius*radius;
  himage_set_xy(C, xcenter, ycenter + (radius), e);
  himage_set_xy(C, xcenter, ycenter - (radius), e);
  himage_set_xy(C, xcenter + radius, ycenter, e);
  himage_set_xy(C, xcenter - radius, ycenter, e);

  y = radius;
  x = 1;
  y =(int) (sqrt(r2 - 1) + 0.5);
  while (x < y )
    {
      himage_set_xy(C, xcenter + x, ycenter + (y), e);
      himage_set_xy(C, xcenter + x, ycenter - (y), e);
      himage_set_xy(C, xcenter - x, ycenter + (y), e);
      himage_set_xy(C, xcenter - x, ycenter - (y), e);
      himage_set_xy(C, xcenter + y, ycenter + (x), e);
      himage_set_xy(C, xcenter + y, ycenter - (x), e);
      himage_set_xy(C, xcenter - y, ycenter + (x), e);
      himage_set_xy(C, xcenter - y, ycenter - (x), e);
      x += 1;
      y =(int) (sqrt(r2 - (x * x)) + 0.5);
    }
  if (x == y)
    {
      himage_set_xy(C, xcenter + x, ycenter + (y), e);
      himage_set_xy(C, xcenter + x, ycenter - (y), e);
      himage_set_xy(C, xcenter - x, ycenter + (y), e);
      himage_set_xy(C, xcenter - x, ycenter - (y), e);
    }
}

void himage_full_circlesym8(himage C, int xcenter, int ycenter, int radius, imgcolor e)
{
  int x, y, r2;
  int i;
  himage_set_xy(C, xcenter, ycenter,e);
  y = radius;
  himage_set_xy(C, xcenter, ycenter + (radius), e);
  for (i = ycenter ; i < (ycenter + (radius)); i ++)
    himage_set_xy(C, xcenter, i, e);
  
  himage_set_xy(C, xcenter, ycenter - (radius), e);
   for (i = ycenter ; i > (ycenter - (radius)); i --)
    himage_set_xy(C, xcenter, i, e);
   
  himage_set_xy(C, xcenter + radius, ycenter, e);
   for (i = xcenter ; i < (xcenter + radius); i ++)
    himage_set_xy(C, i, ycenter, e);
   
  himage_set_xy(C, xcenter - radius, ycenter, e);
   for (i = xcenter ; i > (xcenter - radius); i --)
    himage_set_xy(C, i, ycenter, e);
   
  r2 = radius*radius;
  
  x = 1;
  y =(int) (sqrt(r2 - 1) + 0.5);
  
  while (x < y )
    {
  
      himage_set_xy(C, xcenter + x, ycenter + (y), e);
      for (i = ycenter ; i < (ycenter + (y)); i ++)
	himage_set_xy(C, xcenter + x, i, e);
      
      himage_set_xy(C, xcenter + x, ycenter - (y), e);
      for (i = ycenter ; i > (ycenter - (y)); i --)
	himage_set_xy(C, xcenter + x, i, e);
      
      himage_set_xy(C, xcenter - x, ycenter + (y), e);
      for (i = ycenter ; i < (ycenter + (y)); i ++)
	himage_set_xy(C, xcenter - x, i, e);
      
      himage_set_xy(C, xcenter - x, ycenter - (y), e);
      for (i = ycenter ; i > (ycenter - (y)); i --)
	himage_set_xy(C, xcenter - x, i, e);
      
      himage_set_xy(C, xcenter + y, ycenter + (x), e);
       for (i = ycenter ; i < (ycenter + (x)); i ++)
	himage_set_xy(C, xcenter + y, i, e);
       
      himage_set_xy(C, xcenter + y, ycenter - (x), e);
      for (i = ycenter ; i > (ycenter - (x)); i --)
	himage_set_xy(C, xcenter + y, i, e);
      
      himage_set_xy(C, xcenter - y, ycenter + (x), e);
      for (i = ycenter ; i < (ycenter + (x)); i ++)
	himage_set_xy(C, xcenter - y, i, e);
      
      himage_set_xy(C, xcenter - y, ycenter - (x), e);
      for (i = ycenter ; i > (ycenter - x); i --)
	himage_set_xy(C, xcenter - y, i, e);
      
      x += 1;
      y =(int) (sqrt(r2 - (x * x)) + 0.5);	
    }
  if (x == y)
    {
      himage_set_xy(C, xcenter + x, ycenter + (y), e);
      for (i = ycenter; i < (ycenter + (y)); i++)
	himage_set_xy(C ,xcenter + x, i, e);
      himage_set_xy(C, xcenter + x, ycenter - (y), e);
       for (i = ycenter; i > (ycenter - (y)); i --)
	himage_set_xy(C, xcenter + x, i, e);
      himage_set_xy(C, xcenter - x, ycenter + (y), e);
      for (i = ycenter ; i < (ycenter + (y)); i ++)
	himage_set_xy(C, xcenter - x, i, e);
      himage_set_xy(C, xcenter - x, ycenter - (y), e);
      for (i = ycenter ; i > (ycenter - (y)); i --)
	himage_set_xy(C, xcenter - x, i, e);
    }
    
}

 //chaine d'identification ".himage01"
  // int 32 largeur w
  // int 32 hauteur h

/* format ppm
P5 // entete
640 500  // dimensions
255 // 
#ceci est un commentaire ppm
octetrgbrgbrgb //couleur




 */
void himage_write(himage A, mfile file)
{
  imgcompo r,g,b;
  img_get_color_compo(A->init, &r, &g, &b);
  
  int x;
  mfile_write_str(file, "P6\n");
  mfile_write_text_int (file,A->w);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->h);
  mfile_write_char(file, '\n');
  mfile_write_str(file, "255\n");
  fprintf(stderr,"\nhimage write : width : %d | height : %d | total pixel : %d\n ", A->w , A->h, (A->w * A->h));
   for(x = 0; x < (A->h * A->w); x++)
    {
      img_get_color_compo(A->pixel[x], &r, &g, &b);
     
      mfile_write_char (file,(char) r);
      mfile_write_char (file,(char) g);
      mfile_write_char (file,(char) b);
    }

}

void himage_save( himage C, char* filename)
{
  mfile file = mfile_open(filename, 1);
  
  himage_write(C, file);
  
  mfile_close(&file);
}

//retourne NULL if unable to read
himage himage_read(mfile file)
{
 
  int w, h,crange;
  bool is_int, eof;
  char P = mfile_read_char(file);
  char six = mfile_read_char(file);
  
  if((P != 'P') || (six != '6'))
    {
      fprintf(stderr,"himage_read error : not P6 ?");
      return NULL;
    }
  
  himage_rd_or_ignor_sharp_comments(file, 1);
  
  mfile_read_next_text_int(file, &w, &is_int, &eof);
   
  if (eof || (!is_int))
    {
      fprintf(stderr, "himage_read error looking for width\n");
      return NULL;
    }
  
 
  
  mfile_read_next_text_int(file, &h, &is_int, &eof);
 
 if (eof || (!is_int))
    {
      fprintf(stderr, "himage_read error looking for height\n");
      return NULL;
    }

 
 himage_rd_or_ignor_sharp_comments(file, 1);

 mfile_read_next_text_int(file, &crange, &is_int, &eof);
 
  if (crange!=255)
    {
      fprintf(stderr, "himage_read error looking for color range\n");
      return NULL;
    }
  {
    char sep =  mfile_read_char(file);
    
    if (sep != '\n')
      {
	
	fprintf(stderr,"error beginning separator not found : %d\n",sep );

	return NULL;
      }
  }

  
  fprintf(stderr, "himage read :width : %d | height :%d | crange : %d\n ",w,h,crange );
    {
      himage img =  himage_create_and_alloc(w, h,  image_make_color(0,0,0));
      int i;
      for(i = 0; i < w * h; i++)
	{
	  int r, g, b;
	  
	  r = mfile_read_char (file);
	  g = mfile_read_char (file);
	  b = mfile_read_char (file);


	  
	  if ((r == FILE_EOF) || (g == FILE_EOF) || (b == FILE_EOF) )
	    {
	       fprintf(stderr, "himage end of file");
	       himage_destroy_full (&img);
	       return NULL;
	    }
	  {
	    imgcompo rr = (imgcompo) r;
	    imgcompo gg = (imgcompo) g;
	    imgcompo bb = (imgcompo) b;
	    img->pixel[i] = image_make_color(rr , gg ,bb);
	  }
	}
      return img;
    }
    
}


himage himage_load(char* filename)
{
  mfile F = mfile_open (filename, FILE_READ_ONLY);
  himage A = himage_read(F);
  mfile_close(&F);
  return A;
}

//cours 62
imgcolor image_make_color(imgcompo r, imgcompo g ,imgcompo b)
{
  return ((r << 16) | (g << 8) | b);
}


void img_get_color_compo(imgcolor c, imgcompo* r, imgcompo* g ,imgcompo* b)
{
   *r = c >> 16; 
   *g = (c >> 8) & 0xFF;
   *b = c & 0xFF;
}


void img_color_debug(imgcolor c)
{
  imgcompo r, g ,b;
  img_get_color_compo(c, &r, &g, &b);
  fprintf(stderr,"RGB : %u | %u | %u" ,r,g,b);
}


void himage_rd_or_ignor_sharp_comments(mfile file, bool comments)
{
  while(1)
    {
      int c = mfile_read_char_stop(file);
      if( c == '\n')
	{
	  mfile_goto_nxt_char(file);
	  c = mfile_read_char_stop(file);
	  if (c != '#')
	    return;
	}	
      if (c != '#')
	{
	  return;
	}
      
      if (comments)
	fprintf(stderr,"\ncomments : ") ;
      
      while ((c!='\n')&&(c!=10)&&(c!='\n')&&(c != FILE_EOF))
	{
	  mfile_goto_nxt_char(file );
	  c = mfile_read_char_stop(file);
	  if (comments)
	    fprintf(stderr,"%c",c) ; 
	}
    }
}
