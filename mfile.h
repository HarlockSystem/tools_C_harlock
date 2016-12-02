#ifndef __MFILE_H__
#define __MFILE_H__

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



#include "tools.h"

#define FILE_BUFFER_SIZE 8192
#define FILE_READ_ONLY 0
#define FILE_WRITE_ONLY 1


#define FILE_EOF 254


typedef struct _mfile* mfile;

struct _mfile  {

  char* filename;
  int handler;
  int mode;
  char* buffer;
  int len; // 0 <= len <= FILE_BUFFER_SIZE
  int cursor; // 0 <= cursor <= len -1


};


extern void  mfile_close (mfile* F);
extern mfile mfile_open( char* filename, int mode);

//return the number of octet readed
extern int mfile_read(mfile file,void* bufferb, int nb_read);

//write a nber of octet
extern void mfile_write(mfile file,void* bufferb, int nb_write);

extern int mfile_read_char(mfile F);
extern int mfile_read_char_aux(mfile file,bool nxt);
extern int mfile_read_char_stop(mfile file);

//reg char is NOT space char & NOT line return (ASCII 13, 10)
extern int mfile_read_next_reg_char(mfile file);
extern int mfile_read_next_ignore_cr(mfile file);
extern void mfile_goto_nxt_char(mfile file);
extern void mfile_goto_nxtline(mfile file);

extern void mfile_write_char(mfile F, char c);
extern void mfile_write_string(mfile file, char* str);
extern void mfile_write_str(mfile file, char* str);
extern void mfile_write_int(mfile, int n);

extern void mfile_write_text_int (mfile file, int n);
//modify?
extern void mfile_read_next_text_int (mfile file,int *nn,bool* integer,bool* eof);

extern void mfile_read_next_text_str(mfile file, char** str, bool* eof);
void mfile_read_string_to(mfile file, char** str, bool* eof);
extern void mfile_read_text_int(mfile file, int* nn, bool* integer,bool* eof);

extern void mfile_read_str_len(mfile file, int len, char** strb, bool* eof);
extern void mfile_write_binary_int32 (mfile file, unsigned int n);
extern void mfile_read_binary_int32 (mfile file, int* n, bool* eof);
extern int mfile_read_binary2_int32(mfile file);
extern void mfile_write_binary_int64 (mfile file, long n);
extern long mfile_read_binary_int64 (mfile file);
//create a f() of read & write jstr or intarray
#endif
