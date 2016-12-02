#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "tools.h"
#include "mfile.h"
#include "jstr.h"


#define FILE_BUFFER_SIZE 8192
#define FILE_READ_ONLY 0
#define FILE_WRITE_ONLY 1
#define FILE_EOF 254

mfile mfile_open( char* filename, int mode)
{
	mfile F = (mfile) tools_malloc (sizeof (struct _mfile));
	if (mode == FILE_READ_ONLY)
	  {
	    F->cursor = FILE_BUFFER_SIZE;
	    F->len =  FILE_BUFFER_SIZE;
	    F->handler = open (filename, O_RDONLY);
	   
	  }
	else
	  {
	    F->cursor = 0;
	    F->len = 0;
	    F->handler = open (filename, O_WRONLY | O_CREAT | O_TRUNC  , 00600);
	  }

	if (F->handler == -1)
	  {
	    tools_free (F, sizeof (struct _mfile));
	    fprintf(stderr, "unable to open file %s", filename);
	    return NULL;
	  }

	F->filename = regstr_clone (filename);
	F->mode = mode;
	F->buffer = (char*) tools_malloc ( sizeof (char) * FILE_BUFFER_SIZE);

	return F;
}

void  mfile_close (mfile* F)
{
	mfile F2 = *F;
	if ((F2->mode = FILE_WRITE_ONLY) && (F2->cursor != 0) && (F2->cursor != 4096))
		{
		  write (F2->handler, F2->buffer, F2->cursor);
		}
	close (F2->handler);
	regstr_destroy_raw(&(F2->filename));
	tools_free(F2->buffer, sizeof (char) * FILE_BUFFER_SIZE);
	tools_free(F2 ,sizeof (struct _mfile));
	*F = NULL;
} 

 int mfile_read(mfile file,void* bufferb, int nb_toread)
 {
   char* buffer = (char*) bufferb;
   int i = 0;
   int c = mfile_read_char(file);
   while(c!= FILE_EOF && i < nb_toread)
     {
       buffer[i] = c;
       i++;
       c = mfile_read_char(file);
     }
   return i;
 }





void mfile_write(mfile file,void* bufferb, int nb_towrite)
{
  char* buffer = (char*) bufferb;
  int i;
  for (i=0; i < nb_towrite; i++)
    mfile_write_char(file, buffer[i]);
  
}



/*
int mfile_read_char (mfile F, bool nxt)
{
  if (F->mode == 1)
    {
      fprintf(stderr," file %s in not open in read mode.", F->filename);
      return EOF;

    }
  if (F->cursor < F->len)
    {
      char c = F->buffer[F->cursor];
      F->cursor++;
      return (int) c;
    }
  if  (F->cursor > F->len)
    {
      fprintf ( stderr,"mfile_read_char : erreur");
      return FILE_EOF;
    }
  if (F->cursor == F->len)
    {
      F->len = read (F->handler,F->buffer,FILE_BUFFER_SIZE);
      if (F->len == 0)
	return FILE_EOF;
      else
	{
	  F->cursor = 1;
	  return  (int) F->buffer[0];
	}
    } 
}
*/



int mfile_read_char_aux (mfile F, bool nxt)
{
  if (F->mode == 1)
    {
      fprintf(stderr," file %s in not open in read mode.", F->filename);
      return EOF;
    }
  
  if (F->cursor < F->len)
    {
      
      char c = F->buffer[F->cursor];
      
      
      if(nxt)
	{
	  F->cursor++;
	}
      
      return (int) c;
    }

  if  (F->cursor > F->len)
    {
      fprintf ( stderr,"mfile_read_char :cursor_error");
	return FILE_EOF;
    }
  
  if (F->cursor == F->len)
    {
      
      F->len = read (F->handler,F->buffer,FILE_BUFFER_SIZE);
      if (F->len == 0)
	return FILE_EOF;
      
      else
	{
	  if (nxt)
	    F->cursor = 1;
	  else
	    {
	      F->cursor = 0;
	    }
	  return  (int) F->buffer[0];
	}
    } 
}

void mfile_write_char (mfile F, char c)
{
  if (F->mode == 0)
    {
      fprintf(stderr," file %s in not open in write mode.", F->filename);
      return;

    }
  if (F->cursor > FILE_BUFFER_SIZE)
    {
      fprintf(stderr,"\nmfile_write_char : error");
      return;
    }

  if (F->cursor < FILE_BUFFER_SIZE)
    {
      F->buffer[F->cursor] = c;
      F->cursor++;
    }

  if (F->cursor == FILE_BUFFER_SIZE)
    {
      write (F->handler, F->buffer, FILE_BUFFER_SIZE);
      F->cursor = 0;
    }
}

int mfile_read_char (mfile file)
{
 return mfile_read_char_aux(file, 1);
}

int mfile_read_char_stop(mfile file)
{
 return mfile_read_char_aux(file, 0);
}

// ignore space & cr
int mfile_read_next_reg_char(mfile file)
{
  int c;

  do
    {
      c = mfile_read_char (file);
    }

  while ((c == ' ') || (c == ((char) 13)) || (c == ((char) 10)));
  return (char) c;
}

int mfile_read_next_ignore_cr(mfile file)
{
  int c = mfile_read_char_stop(file);
  
  
  while ((c == '\n') || (c == ((char) 10)) || (c == ((char) 13)))
      {
	mfile_goto_nxt_char(file);
	c = mfile_read_char_stop(file);
      }
  mfile_goto_nxt_char(file);
  return c;
}

void mfile_goto_nxt_char(mfile file)
{
  file->cursor ++;
}


void mfile_goto_nxtline(mfile file)
{
  int c = mfile_read_char_stop(file);
  while ((c != '\n') && (c != 10) && (c != 13))
    {
      mfile_goto_nxt_char(file);
      c = mfile_read_char_stop(file);
    }

  
  while((c == 13) || (c == 10) || ( c == '\n'))
    {
      mfile_goto_nxt_char(file);
      c = mfile_read_char_stop(file);
    }
}


void mfile_write_string(mfile file, char* str)
{
  int i;
  for (i = 0; str[i] != '\0'; i++)
    mfile_write_char(file, str[i]);
}

void mfile_write_str(mfile file, char* str)
{
  int i;
  for (i=0; str[i] !='\0'; i++)
    mfile_write_char( file, str[i]);
      
}

void mfile_write_text_int (mfile file, int n)
{
    char* str = int_to_regstr_2(n);
    mfile_write_string (file, str);
    regstr_destroy_raw(&str);
}




void mfile_read_text_int (mfile file, int * nn, bool* integer,bool* eof)
{
  int n = 0;
  int c  = mfile_read_char (file);
  
 
  if (c == FILE_EOF)
    {
      *nn = -1;
      *integer = FALSE;
      *eof = TRUE;
      return;
    }
  
  else if( ( c < '0') || ( c > '9'))
    {
      
      *nn = -1;
      *integer = FALSE;
      *eof = FALSE;
      return;
    }

  
  while ((c != FILE_EOF) && (c >= '0') && (c <= '9'))
    {
      n *= 10;
      n += ((char) c) - '0';
      c  = mfile_read_char_stop (file);
      if ((c != FILE_EOF) && (c >= '0') && (c <= '9'))
         {
	   mfile_goto_nxt_char(file);
         }
    }
  
  *eof = FALSE;
  *integer = TRUE;
  *nn = n;
  
}



void mfile_read_next_text_int(mfile file, int* nn,bool* integer, bool* eof)
{
  
  int c  = mfile_read_char_stop (file);
  
  while ((c != FILE_EOF) && ((c == ' ') || (c == '\n') || (c == 13) || (c == 10)))
    {
      mfile_goto_nxt_char(file);
      c = mfile_read_char_stop (file);
    }

  
  if (c == FILE_EOF)
    {
      *nn = -1;
      *integer = FALSE;
      *eof = TRUE;
      return;
    }
  
  mfile_read_text_int(file, nn, integer, eof);
}

void mfile_read_string_to(mfile file, char** str, bool* eof)
{
  
  int c = mfile_read_char_stop (file);
  jstr j = NULL;



  if (c == FILE_EOF)
    {
     
      *str = NULL;
      *eof = TRUE;
      return;
    }
  j = standard_empty_jstr_create();

  
  while ((c != FILE_EOF) && ((c != ' ') && (c != '\n') && (c != 13) && (c != 10)))
    {
      jstr_add(j,(char) c);
       mfile_goto_nxt_char(file);
      c = mfile_read_char_stop (file);
    }

  {
    char* sstr = jstr_to_regstr(j);
    *str = sstr;
    jstr_destroy(j);
  }
 

  
}


void mfile_read_next_text_str(mfile file, char** str, bool* eof)
{

  int c  = mfile_read_char_stop (file);

  while ((c != FILE_EOF) && ((c == ' ') || (c == '\n') || (c == 13) || (c == 10)))
    {
      mfile_goto_nxt_char(file);
      c = mfile_read_char_stop (file);
      
    }

  
  if (c == FILE_EOF)
    {
     
      *str = NULL;
      *eof = TRUE;
      return;
    }
  mfile_read_string_to(file, str, eof);
}


void mfile_read_str_len(mfile file, int len, char** strb, bool* eof )
{
  char* str = (char*) tools_malloc (sizeof (char) * (len + 1));
  int i;
  for (i = 0; i < len; i++)
    {
      int c = mfile_read_char(file);
      if(c == FILE_EOF)
	{
	  str[len]= '\0';
	  *eof = TRUE;
	  *strb = str;
	  return;
	}
      str[i] = (char) c;
    }
  str[len] = '\0';
  *eof = FALSE;
  *strb = str;
}

void mfile_write_int(mfile file, int n)
{
  mfile_write(file, &n, 4);
}


// positif
void mfile_write_binary_int32 (mfile file, unsigned int n)
{
  mfile_write_char(file,(n >> 24));
  mfile_write_char(file,(n >> 16) & 0xFF);
  mfile_write_char(file,(n >> 8) & 0xFF);
   mfile_write_char(file,((n >> 0)& 0xFF));

  
}

//fonctionne jusqua 536870911
int mfile_read_binary2_int32(mfile file)
{
   int n;
  unsigned char a = mfile_read_char(file);//unsigned char pour 8bits
  unsigned char b = mfile_read_char(file);
  unsigned char c = mfile_read_char(file);
  unsigned char d = mfile_read_char(file);
  if ((a == FILE_EOF) ||(b == FILE_EOF) ||(c == FILE_EOF) ||(d == FILE_EOF))
    {
      fprintf(stderr,"end of file");
      return -1;
    }
  n = ((a << 24) | (b << 16) | (c << 8) | d );
  return n;
}


void mfile_read_binary_int32(mfile file,int* n, bool* eof)
{
 unsigned char a = mfile_read_char(file);
 unsigned char b = mfile_read_char(file);
 unsigned char c = mfile_read_char(file);
 unsigned char d = mfile_read_char(file);
  
  
  if ((a == FILE_EOF) ||(b == FILE_EOF) ||(c == FILE_EOF) ||(d == FILE_EOF))
    {
      *eof = TRUE;
      *n = -1;
    }
  
  *eof = FALSE;
  *n = (a << 24 | b << 16 | c << 8 | d );
}

void mfile_write_binary_int64 (mfile file, long n)
{
  mfile_write_char(file,n >> 56);
  mfile_write_char(file, (n >> 48) & 0xFF);
  mfile_write_char(file, (n >> 40) & 0xFF);
  mfile_write_char(file, (n >> 32) & 0xFF);
  mfile_write_char(file, (n >> 24) & 0xFF);
  mfile_write_char(file, (n >> 16) & 0xFF);
  mfile_write_char(file, (n>> 8) & 0xFF);
  mfile_write_char(file, n & 0xFF);   
}

long mfile_read_binary_int64 (mfile file)
{
  long a = mfile_read_char(file);
  long b = mfile_read_char(file);
  long c = mfile_read_char(file);
  long d = mfile_read_char(file);
  long e = mfile_read_char(file);
  long f = mfile_read_char(file);
  long g = mfile_read_char(file);
  long h = mfile_read_char(file);
  if ((a == FILE_EOF) ||(b == FILE_EOF) ||(c == FILE_EOF) ||(d == FILE_EOF)||(e == FILE_EOF) ||(f == FILE_EOF) ||(g == FILE_EOF) ||(h == FILE_EOF))
    {
      fprintf(stderr,"binary int read error EOF");
      return -1;
    }
  return (a << 56 | b << 48 | c << 40 | d  << 32 | e << 24 | e << 16 | f << 8 | g);

}



		       
