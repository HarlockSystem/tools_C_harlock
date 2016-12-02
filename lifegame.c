#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lifegame.h"


int lifegame_menu(void)
{
  int n;
  char i;
  char input [10];
 menu:
  fprintf(stdout,
	  "--GAME-OF-LIFE--\nConway 1970\nBY HARLOCK\n\n--MENU--\n[1]NEW GAME\n[2]LOAD GAME\n[3]QUIT\nYour Selection: ");
  
fscanf(stdin,"%10s",input);
i = input[0];

	  
  switch(i)
    {
    case '1':
      {
	n = 1;
	break;
      }
    case '2':
      {
	n = 2;
	break;
      }
    case '3':
      {
	n = 3;
	break;
      }
    default:
      goto menu;
      
     
    }

  return n;
}


int input_game_size(void)
{
  int n;
  char i;
  char input [10];
 menu:
  fprintf(stdout,"--NEW GAME--\nSELECT SIZE THE SIZE OF THE MAP\n[1] 10 x 5\n[2] 20 x 10\n[3] 40 x 20\n[4] 80 x 40\n[5] 160 x 54\n[6]test only\nYour Selection: ");
fscanf(stdin,"%10s",input);
 
  i = input[0];
  
  switch(i)
    {
    case '1':
      {
	n = 1;
	break;
      }
    case '2':
      {
	n = 2;
	break;
      }
    case '3':
      {
	n = 3;
	break;
      }
    case '4':
      {
	n = 4;
	break;
      }
    case '5':
      {
	n = 5;
	break;
      }
    case '6':
      {
	n = 6;
	break;
      }

    default:
      goto menu;
    }
  return n;
}

void input_game_rules(lifegame L)
{
  //standard game rules
  set_alive_rules(L, 2, 2, 3, 3);
  set_dead_rules(L, 3, 3);
}


void life_game_size(int gamesize, int *x , int *y)
{
  if (gamesize < 1)
    gamesize = 1;
  if (gamesize > 6)
    gamesize = 6;

  /*
[1] 10 x 5\n
[2] 20 x 10\n
[3] 40 x 20\n
[4] 80 x 40\n
[5] 160 x 54\n
   */
     
  switch(gamesize)
   {
    case 1:
      {
	*x = 10;
	*y = 5;
	break;
      }
    case 2:
      {
	*x = 20;
	*y = 10;
	break;
      }
    case 3:
      {
	*x = 40;
	*y = 20;
	break;
      }
    case 4:
      {
	*x = 80;
	*y = 40;
	break;
      }
    case 5:
      {
	*x = 160;
	*y = 54;
	break;
      }
   case 6:
     {
       *x = 1000000;
       *y = 1000000;
       break;
     }
      break;
    }
}

void get_level_size(lifegame L, int* x, int* y)
{
  *x = L->w;
  *y = L->h;
}


lifegame lifegame_create (int w, int h, char bg, char ccolour)
{
  
  lifegame L = tools_malloc(sizeof (struct _lifegame));
  L->cell = hcharpix_create (w, h, bg);
  L->ccolor = ccolour;
  L->bg = bg;
  L->h = h;
  L->w = w;
  L->alive_rules = lg_alive_rules();
  L->dead_rules = lg_dead_rules();
  input_game_rules(L);
  
  return L;
}


void lifegame_destroy(lifegame* L)
{
  lifegame L2 = *L;
  hcharpix_destroy (L2->cell);
  intarray_destroy (L2->dead_rules);
  intarray_destroy (L2->alive_rules);
  tools_free(L2, sizeof( struct _lifegame));
  
  *L = NULL;
}


int neighbor_count(lifegame L, int x, int y)
{
  int i;
  i = get_xy_neighbor(L->cell, x, y);
  return i;
}

void lifegame_display(lifegame L)
{
  hcharpix_display(L->cell);
}

bool is_cell_alive(lifegame L,int x ,int y)
{
  if (hcharpix_get_xy(L->cell, x,y) != hcharpix_get_bg(L->cell))
    {
      return TRUE;
    }
  
  else
    {
      return FALSE;
    }
}

void set_cell(lifegame L, int x, int y , bool alive)
{
  //tri de Graham : si alors sinon
  //alive ? hcharpix_set_xy (L->cell, x, y,L->ccolor ) : hcharpix_set_xy (L->cell,x, y, L->bg); 
  if (alive)
    {
      //fprintf(stderr,"set:%d|%d ",x,y);
      hcharpix_set_xy (L->cell, x, y,L->ccolor );
    }

  else
    {
      //fprintf(stderr,"unset:%d|%d ",x,y);
      hcharpix_set_xy (L->cell,x, y, L->bg);
    }
}



void set_cell_debug(lifegame L, int x, int y ,int n, bool alive)
{
  //tri de Graham : si alors sinon
  //alive ? hcharpix_set_xy (L->cell, x, y,L->ccolor ) : hcharpix_set_xy (L->cell,x, y, L->bg); 
  if (alive)
    {
      //fprintf(stderr,"set:%d|%d ",x,y);
      
      hcharpix_set_xy (L->cell, x, y, (char)(n+48) );
    }

  else
    {
      //fprintf(stderr,"unset:%d|%d ",x,y);
      hcharpix_set_xy (L->cell,x, y, L->bg);
    }
}

lifegame lifegame_clone(lifegame L)
{
  lifegame L2 = lifegame_create(L->w , L->h, L->bg, L->ccolor);
   hcharpix_copy (L->cell, 0, 0, L->w-1  , L->h-1,L2->cell , 0, 0);

   
fprintf(stderr,"width:%d | height:%d | bg:%c | ccolor:%c\n", L->w , L->h, L->bg, L->ccolor);
L2->dead_rules = lg_dead_rules();
L2->alive_rules = lg_alive_rules();

  input_game_rules(L2);
     fprintf(stderr,"rules dead:%d|%d  alive:%d|%d|%d|%d\n",L2->dead_rules->data[0], L2->dead_rules->data[1], L2->alive_rules->data[0], L2->alive_rules->data[1], L2->alive_rules->data[2], L2->alive_rules->data[3]);
     
 
  return L2;
}


void D_lifegame_clone(lifegame L, lifegame L2)
{
  
   hcharpix_copy (L->cell, 0, 0, L->w-1  , L->h-1,L2->cell , 0, 0);
   L2->alive_rules->data[0] = L->alive_rules->data[0];
   L2->alive_rules->data[1] = L->alive_rules->data[1];
   L2->alive_rules->data[2] = L->alive_rules->data[2];
   L2->alive_rules->data[3] = L->alive_rules->data[3];
   L2->dead_rules->data[0] = L->dead_rules->data[0];
   L2->dead_rules->data[1] = L->dead_rules->data[1];
   L2->bg = L->bg;
   L2->ccolor =  L->ccolor;
     
}

void lifegame_next_gen(lifegame src, lifegame tgt)
{
  int n;
  int x, y;
  int count = 0;
  int count_alive = 0;
  int total = 0;
  hcharpix_copy (src->cell, 0, 0, (src->w-1 ) , (src->h-1),tgt->cell , 0, 0);
 
  for( y = 0; y < (src->h); y++)
    {
      for (x = 0; x < (src->w); x++)
	{
	  n =  neighbor_count(src, x, y);
	  
	  if(is_cell_alive(src,x ,y))
	    {
	      //fprintf(stderr, "alive : %d|%d ",x,y);
	      //lifegame_alive(src, n) ? set_cell(tgt, x, y, TRUE) : set_cell(tgt, x, y, FALSE);
	      if (lifegame_alive (src, n))
		{
		  count_alive ++;
		  set_cell(tgt, x, y, TRUE);
		}
	      else
		{
		  set_cell(tgt, x, y, FALSE);
		    
		}
		  
	    }
	  
	  if(!is_cell_alive(src,x ,y))
	    {
	      if(lifegame_dead(src, n))
		{
		  //fprintf(stderr ,"birth:%d|%d ",x , y);
		  count ++;
		  set_cell(tgt, x, y , TRUE);
		}
	      }
	  
	}
    }
  total = count + count_alive;
  fprintf(stdout,"new life:%d | already living:%d | total life:%d\n",count, count_alive, total);
}



intarray lg_dead_rules(void)
{
  intarray i = intarray_create(2);
  return i;
}

intarray lg_alive_rules(void)
{
  intarray i = intarray_create(4);
  return i;
}

void set_alive_rules(lifegame L, int upop, int bmin, int bmax, int opop)
{
  L->alive_rules->data[0] = upop;
  L->alive_rules->data[1] = bmin;
  L->alive_rules->data[2] = bmax;
  L->alive_rules->data[3] = opop;
}

void set_dead_rules(lifegame L, int bmin, int bmax)
{
  L->dead_rules->data[0] = bmin;
  L->dead_rules->data[1] = bmax;
}

//dont check if the cell is dead or alive true the cell birth
bool lifegame_dead(lifegame L,int neighbor)
{
  //si vrai return true
  return ((neighbor >= L->dead_rules->data[0]) && (neighbor <= L->dead_rules->data[1]));
}
//TRUE the cell survive
bool lifegame_alive(lifegame L,int neighbor)
{
  
  if((neighbor <  L->alive_rules->data[0]) || (neighbor > L->alive_rules->data[3]))
    {
      return FALSE;
    }
  if((neighbor >= L->alive_rules->data[1]) && (neighbor <= L->alive_rules->data[2]))
    {
      return TRUE;
    }
  
}
//pause in second
void lifegame_next_gen_til_N(lifegame L, int N, int pause)
{
  int i;
  int tc = 0;
   lifegame_display(L);
 lifegame L2 = lifegame_clone(L);

 for (i = 0; i < N; i++)
   {
     tc++;
     fprintf(stdout,"time:%d\n",tc);
     lifegame_next_gen(L, L2);
     ptr_swap((void **) &L,(void **) &L2);
     lifegame_display(L);
     sleep(pause);
   }
 if (i%2 != 0)
   ptr_swap((void **) &L,(void **) &L2);
 lifegame_destroy (&L2);
}

//stop if no more cell state evolving
void lifegame_next_gen_til_N_or_same_gen(lifegame L, int N, int pause)
{
  int i;
  int tc= 0;
   lifegame_display(L);
lifegame L2 = lifegame_clone(L);
  for (i = 0; i < N; i++)
    {
       tc++;
       fprintf(stdout,"time:%d\n",tc);
      lifegame_next_gen(L, L2);
      if( hcharpix_equal(L->cell, L2->cell))
	{
	  fprintf(stdout,"\n -------final stage-------- \n"); 
	  break;
	}
      ptr_swap((void **) &L,(void **) &L2);
      lifegame_display(L);
      sleep(pause);
     
    }

   if (i%2 != 0)
     ptr_swap((void **) &L,(void **) &L2);
  
  lifegame_destroy (&L2);
}

// writing same order as struct
void lifegame_write(lifegame A, mfile file)
{
  char c;
  int x,y ;
  //lg1 -> filetype
  //size width height : int int
  //ccolor bg ->char char
  //dead rules: int int alive rules: int int int int 
  //data...
  mfile_write_str(file, "lg1\n");
  mfile_write_text_int (file,A->w);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->h);
  mfile_write_char(file, '\n');
  mfile_write_char(file, A->ccolor);
  mfile_write_char(file, ' ');
  mfile_write_char(file, A->bg);
  mfile_write_char(file, '\n');
  mfile_write_text_int (file,A->dead_rules->data[0]);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->dead_rules->data[1]);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->alive_rules->data[0]);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->alive_rules->data[1]);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->alive_rules->data[2]);
  mfile_write_char(file, ' ');
  mfile_write_text_int (file,A->alive_rules->data[3]);
  mfile_write_char(file, '\n');

 fprintf(stderr,"filegame write : width : %d | height : %d |\n", A->w , A->h);

 for(y = 0; y < A->h; y++)
   {
     for(x = 0; x < A->w; x++)
       {
	 c =  hcharpix_get_xy (A->cell, x, y);
	 mfile_write_char (file,c);
	 
       }
   }
}

void lifegame_save( lifegame C, char* filename)
{
  mfile file = mfile_open(filename, 1);
  
  lifegame_write(C, file);
  
  mfile_close(&file);
}


lifegame lifegame_read(mfile file)
{

  //lg1 -> filetype
  //size width height : int int
  //bg
  //ccolor
  //dead rules: int int alive rules: int int int int 
  //data..
  
  int w, h;
  int drmin, drmax,arup, armin, armax, arop;
  bool is_int, eof;
  char l = mfile_read_char(file);
  char g = mfile_read_char(file);
  char one = mfile_read_char(file);
  char bg, ccolor;
  
  if((l != 'l') ||(g != 'g')||(one != '1'))
    {
      fprintf(stderr,"filegame_read error : invalid filetype ?");
      return NULL;
    }
  
  himage_rd_or_ignor_sharp_comments(file, 1);


  //read width & height
  mfile_read_next_text_int(file, &w, &is_int, &eof);
   
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for width\n");
      return NULL;
    }
  
 
  
  mfile_read_next_text_int(file, &h, &is_int, &eof);
 
 if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }

 
 himage_rd_or_ignor_sharp_comments(file, 1);

 //read cell color & background char 

 ccolor = mfile_read_char(file);
 //skipping space char
 mfile_read_char(file);
 bg = mfile_read_char(file);

 himage_rd_or_ignor_sharp_comments(file, 1);
 
 //drmin, drmax,arup, armin, armax, arop;
 mfile_read_next_text_int(file, &drmin, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }



mfile_read_next_text_int(file, &drmax, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }

mfile_read_next_text_int(file, &arup, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }

mfile_read_next_text_int(file, &armin, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }

mfile_read_next_text_int(file, &armax, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
      return NULL;
    }


mfile_read_next_text_int(file, &arop, &is_int, &eof);
 
 
  if (eof || (!is_int))
    {
      fprintf(stderr, "filegame_read error looking for height\n");
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
 
  
  fprintf(stderr, "filegame read -> width : %d | height :%d | dead rules : %d %d | alive rules : %d %d %d %d\n",w,h,drmin, drmax,arup, armin, armax, arop);
  {
    lifegame L =  lifegame_create(w, h, bg, ccolor) ;
    int i,j,x,y;
    for(i = 0; i < h; i++)
      {
	for (j = 0; j < w; j++)
	  {
	    hcharpix_goto_xy(L->cell, j, i);
	    hcharpix_coordonates(L->cell, &x, &y);
	    fprintf(stdout ,"| x:%d |j:%d | y:%d | i:%d |\n",x , j, y, i);
	    int c =  mfile_read_next_ignore_cr(file);
     
	    if (c == FILE_EOF)
	      {
		fprintf(stderr, "lifegame_read end of file error\n");
		lifegame_destroy(&L);
		return NULL;
	      }
	    hcharpix_set (L->cell, (char) c);
	  }
      }
    return L;
  }
  
}
    



lifegame lifegame_load(char* filename)
{
  mfile F = mfile_open (filename, FILE_READ_ONLY);
  lifegame L = lifegame_read(F);
  mfile_close(&F);
  return L;
}
