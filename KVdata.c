#include <stdlib.h>
#include <stdio.h>

#include "jstr.h"
#include "mfile.h"
#include "stringarray.h"
#include "tools.h"
#include "KVdata.h"
//K -> key V -> value

KVdata KV_data_alloc(void)
{
  KVdata KV = ((KVdata) tools_malloc(sizeof(struct _KVdata)));
    KV->KEYS = standard_empty_stringarray_create();
    KV->VALUES =  standard_empty_stringarray_create();
    return KV;
}
  
KVdata KV_data_load(char* filename, bool verbose)
  {
    KVdata KV = KV_data_alloc();
    mfile file = mfile_open (filename, FILE_READ_ONLY);
    char* key; char* value;
    bool eof = FALSE;
    if (file == NULL)
      {
	fprintf(stderr, "KVdata_load error while opening file"); 
	KV_data_destroy(&KV);
	return NULL;
      }
    while(!eof)
      {
	mfile_read_next_text_str(file, &key, &eof);
	if (!eof)
	  {
	    mfile_read_next_text_str(file, &value, &eof);
	    if (eof)
	      fprintf(stderr,"\nno value found for key: %s\n",key);

	    
	    else 
	      {
		stringarray_add(KV->KEYS, regstr_to_jstr(key));
		stringarray_add(KV->VALUES, regstr_to_jstr(value));
		if(verbose)
		  {
		    fprintf(stderr,"Key : %s ; Value : %s \n",key, value);}

		regstr_destroy(&key);
	    regstr_destroy(&value);
	      }
	    
	  }
      }

    
    mfile_close(&file);
    return KV;
  }

void KV_data_destroy(KVdata* KVX )
{
  KVdata KV = *KVX;
  
  stringarray_destroy_using_jstr_destroy (KV->KEYS);
  stringarray_destroy_using_jstr_destroy (KV->VALUES);
  tools_free( KV , sizeof(struct _KVdata));
  *KVX = NULL;
  
}

char* KV_data_get_string(KVdata KV, char* key)
{
  int i;
  for (i =0; i < KV->KEYS->len; i++)
    {
      jstr j = stringarray_get(KV->KEYS, i);
      char* key2 = jstr_to_regstr(j);
      if (regstr_equal(key, key2))
	{
	  regstr_destroy(&key2);
	  return jstr_to_regstr(stringarray_get(KV->VALUES,i ));
	}
      regstr_destroy(&key2);
    }
  return NULL;
  
}

void KV_data_get_int (KVdata KV,char* key, int* n, bool* found)
{
  char* str = KV_data_get_string (KV ,key);
  if (str == NULL)
    {
      *n = -1;
      *found = FALSE;
      return;
    }
  int ok;
  
  *n =  string_to_int (str);

  if (n = 0)
    {
      *n= -1;
      *found = FALSE;
    }

  else
    *found = TRUE;
  
  regstr_destroy(& str);
}
