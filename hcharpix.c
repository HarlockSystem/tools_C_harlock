#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "hcharpix.h" //add -lm


hcharpix hcharpix_create (int width, int height, char bg)//quadratique
{
  assert ((height > 0) && (width > 0));
  int i;
  hcharpix C = malloc (sizeof (struct _hcharpix));
  C->h = height;
  C->w = width;
  C->x = 0;
  C->y = 0;
  C->init = bg;
  C->data = malloc (sizeof ( jstr) * height);
  
  for (i = 0; i < height; i ++)
    {
      hcharpix_add(C, i, regstr_to_jstr(char2string(C->w, bg))); 
    } 
  return C;
}

void hcharpix_add( hcharpix C, int i, jstr j)//lineaire
{
  C->data[i] = j;
}

void hcharpix_destroy (hcharpix C)//lineaire
{
  int i;
  for (i = 0; i < C->h; i++)
    {
      jstr_destroy (C->data[i]);
    }
  free (C->data);
  free (C);
}

char hcharpix_get_bg(hcharpix C)
{
  return C->init;
}

char hcharpix_get_xy (hcharpix C, int x, int y)//constant
{
  char c = jstr_get(C->data[y],x);
  return c;
}

void hcharpix_set_xy (hcharpix C, int x, int y, char c)//constant
{
  jstr_set(C->data[y], x, c);
}

void hcharpix_revert_xy(hcharpix C, int x, int y)//linéaire
{ 
 jstr_set( C->data[y], x, C->init);
}

char hcharpix_get (hcharpix C)//constant
{
  char c = jstr_get(C->data[(C->y)],C->x);
  return c;
}

void hcharpix_set (hcharpix C, char c)//constant
{
  jstr_set(C->data[C->y], C->x, c);
}

void hcharpix_revert(hcharpix C)
{
  jstr_set( C->data[C->y], C->x, C->init);//constant
}

void hcharpix_revert_all(hcharpix C)//linéaire
{
  int i, n;
  for(i = 0; i < C->h; i++)
    {
      for(n = 0; n < C->w; n++)
	{
	  jstr_set( C->data[i], n, C->init);
	}
    }
}

void hcharpix_display (hcharpix C) //quadratique
{
  int i;
  fprintf(stdout,"\n");
  for (i = 0; i< C->h; i++)
    {
      jstr_print(C->data[i]);
      fprintf(stdout,"\n");
    }
  fprintf(stdout,"\n");
}


inline
void hcharpix_goto_line (hcharpix C, int y)//constant
{
  if ((y < C->h) && (y >= 0)) 
    {
      C->y = y;
    }
  else
    {
      printf("entrez un chiffre entre 0 et %d",C->y); 
    }
}
  
inline
void hcharpix_goto_next(hcharpix C)//constant
{
  C->x++;
  if (C->x > (C->w-1))
    {
      C->x = 0;
      hcharpix_step_down(C);
    }
}

inline
void hcharpix_goto_previous(hcharpix C)//constant
{
  C->x--;
  if (C->x < 0)
    {
      C->x = (C->w-1);
      hcharpix_step_up(C);
    }
}

inline
void hcharpix_step_up(hcharpix C)//constant
{
  C->y--;
  if (C->y < 0)
    {
      C->y = (C->h-1);
    }
}

inline void hcharpix_step_down(hcharpix C)//constant
{
  C->y++;
  if (C->y > (C->h-1))
    {
      C->y = 0;
    }
}


inline
void hcharpix_cmup(hcharpix C)//constant
{
  C->y--;
  if (C->y < 0)
    {
      C->y = (C->h - 1);
    }
}

inline void hcharpix_cmdown(hcharpix C)//constant
{
  C->y++;
  if (C->y > (C->h-1))
    {
      C->y = 0;
    }
}

void hcharpix_rmright(hcharpix C)//constant
{
  C->x++;
  if (C->x > (C->w -1))
    {
      C->x = 0;
    }
}

inline
void hcharpix_rmleft(hcharpix C)//constant
{
  C->x--;
  if (C->x < 0)
    {
      C->x = (C->w-1);
    }
}




char* char2string(int strsize, char bg)//linéaire !fuite memoire a changer!
{
  int i;
  char * str = malloc ((strsize+1)*sizeof(char));
  if(str == NULL)
    {
      return NULL;
    }
  for (i = 0; i < strsize; i++)
    {
      str[i] = bg;
    }
  str[strsize]='\0';
  return str;
}

void hcharpix_draw_horline (hcharpix C, int y, int x1, int x2, char c)//trace des lignes horizontales, linéaire
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
	  for (i = 0; i > (x2 - x1)-1; i--)
	    {
	      hcharpix_set(C, c);
	      hcharpix_rmleft(C);
	    }
	}
      if ((x2 - x1) > 0)
	{
	  for(i =0; i < (x2 - x1)+1; i++)
	    {
	      hcharpix_set(C, c);
	      hcharpix_rmright(C);
	    }
	}
      if ((x2 - x1) == 0)
	hcharpix_set(C,c);    
}

void hcharpix_draw_verline (hcharpix C, int x, int y1, int y2, char c)//trace des lignes verticales, linéaire
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
      fprintf(stderr," y1 out of bound set y1 to %d",(C->h -1));
      y1 = (C->h -1);
    }
  if (y2 > (C->h -1))
    {
      fprintf(stderr," y2 out of bound set y2 to %d",(C->h -1));
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
	  for (i = 0; i < (y2 - y1)-1; i--)
	    {
	      hcharpix_set(C, c);
	      hcharpix_cmup(C);
	    }
	}
      if ((y2 - y1) > 0)
	{
	  for(i =0; i < (y2 - y1)+1; i++)
	    {
	      hcharpix_set(C, c);
	      hcharpix_cmdown(C);
	    }
	}
      if ((y2 - y1) == 0)
	hcharpix_set(C,c);    
}


inline void hcharpix_goto_xy (hcharpix C, int tgx, int tgy)//place le curseur a xy, constant
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
 
 C->x = tgx;
 C->y = tgy;
}

hcharpix hcharpix_clone (hcharpix C)//quadratique
 {
   int i;
   hcharpix CP = hcharpix_create(C->w, C->h, C->init);
   
   for (i=0; i < C->h; i++)
     {
       CP->data[i] = jstr_clone(C->data[i]);
     }
   return CP;
 }

void hcharpix_bound(hcharpix O,int* x, int* y ,int* x2, int* y2)
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


void hcharpix_copy (hcharpix O, int ox, int oy, int ox2, int oy2, hcharpix TG, int tgx, int tgy)//quadratique
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
      fprintf(stderr, " tgy out of bound set tgy to 0");
      tgy = 0;
    }
  if (tgx > (TG->w -1))
    {
      fprintf(stderr," tgx out of bound set tgx to %d",(TG->w -1));
      tgx = (TG->w -1);
    }
  if (tgy > (TG->h -1))
    {
      fprintf(stderr,"tgy out of bound set tgy to %d",(TG->h -1));
      tgy = (TG->h -1);
    }			       

  printf("\n");
    
      for (i = oy; i < oy2 +1 ; i++)
	{
	for (j = ox; j < ox2 +1 ;j++)
	  {
	    hcharpix_set_xy (TG,tgx2,tgy,hcharpix_get_xy(O, j,i));
	    tgx2++;
	    //if (tgx2 > (TG->w-1))
	    //break;
	  }
	tgy++;
	tgx2 = tgx;
	//if(tgy > (TG->h -1))
	// break;
	}
    
 }



int get_xy_neighbor(hcharpix C, int x, int y)
{
  int nb = 0;
  char c;
  hcharpix_goto_xy(C, x, y);
  
  hcharpix_cmup(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_rmright(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_cmdown(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_cmdown(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_rmleft(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_rmleft(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_cmup(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
  hcharpix_cmup(C);
  c = jstr_get(C->data[C->y], C->x);
  if (c != C->init)
    nb ++;
 
  return nb;
}

void hcharpix_full_box(hcharpix C, int ox1, int ox2, int oy1, int oy2, char c)
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
 
  hcharpix_bound(C, &x1, &y1, &x2,&y2);
  
  for (i = y1; i < (y1 + 1 + (y2 - y1)); i++)
	 for (j = x1; j < (x1 + 1 + (x2 - x1)); j++)
	{
	  hcharpix_set_xy(C, j, i, c);
	}
}




void hcharpix_circlesym8(hcharpix C, int xcenter, int ycenter, int radius, char e)//lineaire
{
  int x, y, r2;
  r2  = radius*radius;
  hcharpix_set_xy(C, xcenter, ycenter + (radius/2), e);
  hcharpix_set_xy(C, xcenter, ycenter - (radius/2), e);
  hcharpix_set_xy(C, xcenter + radius, ycenter, e);
  hcharpix_set_xy(C, xcenter - radius, ycenter, e);

  y = radius;
  x = 1;
  y =(int) (sqrt(r2 - 1) + 0.5);
  while (x < y )
    {
      hcharpix_set_xy(C, xcenter + x, ycenter + (y/2), e);
      hcharpix_set_xy(C, xcenter + x, ycenter - (y/2), e);
      hcharpix_set_xy(C, xcenter - x, ycenter + (y/2), e);
      hcharpix_set_xy(C, xcenter - x, ycenter - (y/2), e);
      hcharpix_set_xy(C, xcenter + y, ycenter + (x/2), e);
      hcharpix_set_xy(C, xcenter + y, ycenter - (x/2), e);
      hcharpix_set_xy(C, xcenter - y, ycenter + (x/2), e);
      hcharpix_set_xy(C, xcenter - y, ycenter - (x/2), e);
      x += 1;
      y =(int) (sqrt(r2 - (x * x)) + 0.5);
    }
  if (x == y)
    {
      hcharpix_set_xy(C, xcenter + x, ycenter + (y/2), e);
      hcharpix_set_xy(C, xcenter + x, ycenter - (y/2), e);
      hcharpix_set_xy(C, xcenter - x, ycenter + (y/2), e);
      hcharpix_set_xy(C, xcenter - x, ycenter - (y/2), e);
    }
}

void hcharpix_full_circlesym8(hcharpix C, int xcenter, int ycenter, int radius, char e)//quadratique
{
  int x, y, r2;
  int i;
  hcharpix_set_xy(C, xcenter, ycenter,e);
  y = radius;
  hcharpix_set_xy(C, xcenter, ycenter + (radius/2), e);
  for (i = ycenter ; i < (ycenter + (radius/2)); i ++)
    hcharpix_set_xy(C, xcenter, i, e);
  
  hcharpix_set_xy(C, xcenter, ycenter - (radius/2), e);
   for (i = ycenter ; i > (ycenter - (radius/2)); i --)
    hcharpix_set_xy(C, xcenter, i, e);
   
  hcharpix_set_xy(C, xcenter + radius, ycenter, e);
   for (i = xcenter ; i < (xcenter + radius); i ++)
    hcharpix_set_xy(C, i, ycenter, e);
   
  hcharpix_set_xy(C, xcenter - radius, ycenter, e);
   for (i = xcenter ; i > (xcenter - radius); i --)
    hcharpix_set_xy(C, i, ycenter, e);
   
  r2 = radius*radius;
  
  x = 1;
  y =(int) (sqrt(r2 - 1) + 0.5);
  
  while (x < y )
    {
  
      hcharpix_set_xy(C, xcenter + x, ycenter + (y/2), e);
      for (i = ycenter ; i < (ycenter + (y/2)); i ++)
	hcharpix_set_xy(C, xcenter + x, i, e);
      
      hcharpix_set_xy(C, xcenter + x, ycenter - (y/2), e);
      for (i = ycenter ; i > (ycenter - (y/2)); i --)
	hcharpix_set_xy(C, xcenter + x, i, e);
      
      hcharpix_set_xy(C, xcenter - x, ycenter + (y/2), e);
      for (i = ycenter ; i < (ycenter + (y/2)); i ++)
	hcharpix_set_xy(C, xcenter - x, i, e);
      
      hcharpix_set_xy(C, xcenter - x, ycenter - (y/2), e);
      for (i = ycenter ; i > (ycenter - (y/2)); i --)
	hcharpix_set_xy(C, xcenter - x, i, e);
      
      hcharpix_set_xy(C, xcenter + y, ycenter + (x/2), e);
       for (i = ycenter ; i < (ycenter + (x/2)); i ++)
	hcharpix_set_xy(C, xcenter + y, i, e);
       
      hcharpix_set_xy(C, xcenter + y, ycenter - (x/2), e);
      for (i = ycenter ; i > (ycenter - (x/2)); i --)
	hcharpix_set_xy(C, xcenter + y, i, e);
      
      hcharpix_set_xy(C, xcenter - y, ycenter + (x/2), e);
      for (i = ycenter ; i < (ycenter + (x/2)); i ++)
	hcharpix_set_xy(C, xcenter - y, i, e);
      
      hcharpix_set_xy(C, xcenter - y, ycenter - (x/2), e);
      for (i = ycenter ; i > (ycenter - (x/2)); i --)
	hcharpix_set_xy(C, xcenter - y, i, e);
      
      x += 1;
      y =(int) (sqrt(r2 - (x * x)) + 0.5);	
    }
  if (x == y)
    {
      hcharpix_set_xy(C, xcenter + x, ycenter + (y/2), e);
      for (i = ycenter; i < (ycenter + (y/2)); i++)
	hcharpix_set_xy(C ,xcenter + x, i, e);
      hcharpix_set_xy(C, xcenter + x, ycenter - (y/2), e);
       for (i = ycenter; i > (ycenter - (y/2)); i --)
	hcharpix_set_xy(C, xcenter + x, i, e);
      hcharpix_set_xy(C, xcenter - x, ycenter + (y/2), e);
      for (i = ycenter ; i < (ycenter + (y/2)); i ++)
	hcharpix_set_xy(C, xcenter - x, i, e);
      hcharpix_set_xy(C, xcenter - x, ycenter - (y/2), e);
      for (i = ycenter ; i > (ycenter - (y/2)); i --)
	hcharpix_set_xy(C, xcenter - x, i, e);
    }
    
}

 //chaine d'identification ".hcharpix01"
  // int 32 largeur w
  // int 32 hauteur h

void hcharpix_write(hcharpix A, mfile file)
{
 
  int x,y;
  mfile_write_str(file, ".hcharpix01");
  mfile_write_binary_int32(file, A->w);
  mfile_write_binary_int32(file, A->h);
  mfile_write_char (file, A->init);
 for(y = 0; y < A->h; y++)
    {
      for(x = 0; x < A->w; x++)
	{
	  mfile_write_char (file, hcharpix_get_xy(A, x, y));		  
	}
    }
}

void hcharpix_save( hcharpix C, char* filename)
{
  mfile file = mfile_open( filename, 1);
  hcharpix_write(C, file);
  mfile_close(&file);
}

//retourne NULL if unable to read
hcharpix hcharpix_read(mfile file)
{
  char* format_str = NULL;bool eof = FALSE;
  mfile_read_str_len(file, 11 , &format_str, &eof);
  
  
  if (eof)
    {
      fprintf(stderr, "hcharpix_read error\n");
      regstr_destroy_len(&format_str, 11);
      return NULL;
    }

  
   
    if (!regstr_equal( ".hcharpix01", format_str))
    {
      fprintf( stderr,"%s\n", format_str);
      fprintf( stderr, "hcharpix_read file seem not a hcharpix");
      regstr_destroy_len(&format_str, 11);
      return NULL;
      }
  

  regstr_destroy_len(&format_str, 11);
  {
    int w,h,x,y; hcharpix C = NULL; bool eof;
    mfile_read_binary_int32(file, &w, &eof);
    
    if(eof)
      {
	fprintf(stderr,"hcharpix_read unable to read width");
	regstr_destroy_len(&format_str, 11);
	return NULL;
      }
    
    mfile_read_binary_int32(file, &h, &eof);
    if(eof)
      {
	fprintf(stderr,"hcharpix_read unable to read height");
	regstr_destroy_len(&format_str, 11);
	return NULL;
      }


    
         C = hcharpix_create (w , h, ' ');
	 int c = mfile_read_char(file);
	 if (c == FILE_EOF)
	   {
	     fprintf( stderr,"error end of file");
	     return NULL;
	   }

	 C->init = (char) c;
    for(y = 0; y < C->h; y++)
      {
	for(x = 0; x < C->w; x++)
	  {
	    c = mfile_read_char (file);
	    if (eof)
	      {
		hcharpix_destroy(C);
		fprintf(stderr,"hcharpix_read unable to reach end");
		return NULL;
	      }
	    hcharpix_set_xy(C, x, y,(char) c);
	  }
      }
    return C;
  }
}

hcharpix hcharpix_load(char* filename)
{
  mfile F = mfile_open (filename, FILE_READ_ONLY);
  hcharpix A = hcharpix_read(F);
  mfile_close(&F);
  return A;
}

      
int hcharpix_diffcount(hcharpix C1, hcharpix C2)
{
  int counter, h,w,x,y;
  if (C1->w > C2->w)
    w = C2->w;
  if (C2->w >= C1->w)
    w = C1->w;
  if (C1->h > C2->h)
    h = C2->h;
  if (C2->h >= C1->h)
    h = C1->h;
  
  counter = 0;
  
  
  
  for(y = 0; y < h; y++)
    {
      for(x = 0; x < w; x++)
	{
	  if (jstr_get(C1->data[(C1->y)],C1->x) != jstr_get(C2->data[(C2->y)],C2->x))
	    {
	      counter++;
	    }
	}
	 
    }
  return counter;
}

bool hcharpix_equal(hcharpix C1, hcharpix C2)
{
  int x,y;
  if (C1 == C2)
    return TRUE;

  if (C1->w != C2->w || C1->h != C2->h)
      return FALSE;
    
  
  for(y = 0; y < C1->h; y++)
    {
      for(x = 0; x < C1->w; x++)
	{
	  if (jstr_get(C1->data[y],x) != jstr_get(C2->data[y],x))
	    {
	      //fprintf(stderr,"debug| %c|%c |", jstr_get (C1->data[y],x), jstr_get(C2->data[y],x));
	      //fprintf(stderr,"not same data");
	      return FALSE;
	    }
	}
    }
  
  return TRUE;
}

void hcharpix_coordonates(hcharpix H, int *x, int *y)
{
  *x = H->x;
  *y = H->y;
}
