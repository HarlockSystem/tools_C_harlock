/*.h = header */
/* < repertoire biblio standard > */
/* " repertoire perso " */
/* int argc taille de la chaine de commande du main 
   char * argv[] chaine enregistrer par le main pour entrer des lignes de commandes */
//jol algorithme facon Jacque Olivier Lapeyre
#ifndef __STRINGARRAY_H__
#define __STRINGARRAY_H__


#define RC printf ("\n")
#define STRINGARRAY_DEFAULT_ALLOC 10
#include "intarray.h"
#include "jstr.h"

typedef struct _stringarray *stringarray;
typedef char* regstr;
typedef char chardata;




struct _stringarray
{
  jstr* data;
  int len;
  int alloc;
};




extern void stringarray_debug (stringarray S);
extern void ext_stringarray_debug (stringarray tab);
extern void stringarray_debug_bound (stringarray T,char * bound);
extern void stringarray_print (stringarray S, char * c);
extern stringarray stringarray_create (int len);
extern stringarray ext_stringarray_create (int len, int alloc);
extern stringarray empty_stringarray_create(int alloc);
extern stringarray standard_empty_stringarray_create (void);
extern void stringarray_create_aux (stringarray tab);
extern void stringarray_destroy (stringarray S);
extern void stringarray_and_jstr_destroy(stringarray S);
extern jstr stringarray_get (stringarray S , int i);
extern void stringarray_set (stringarray S , int i , jstr n);
extern void ext_stringarray_set ( stringarray S, int i, jstr n);
extern int stringarray_length (stringarray S);
extern void stringarray_add(stringarray S, jstr j);
extern void stringarray_delete(stringarray S, int loc);
extern stringarray stringarray_concat_aux (stringarray S1, stringarray T2, int clone);
extern stringarray stringarray_concat(stringarray T1,stringarray T2);
extern stringarray stringarray_concat_jstr_clone (stringarray T1, stringarray T2);
extern void D_stringarray_concat(stringarray T1, stringarray T2);
extern void stringarray_sort1 (stringarray S);/*tri par ordre lexicographique*/
extern stringarray stringarray_clone (stringarray S);
extern stringarray stringarray_clone_aux (stringarray T, int clone);

extern stringarray stringarray_clone_jstr(stringarray S);

extern int stringarray_equal(stringarray j1, stringarray j2);
extern void UNSORTED_stringarray_delete (stringarray tab, int index);
extern void stringarray_sort_jol (stringarray T);
extern void stringarray_resize (stringarray tab, int newalloc);
extern void ext_stringarray_set (stringarray tab, int index, jstr value);
extern jstr stringarray_get_max (stringarray tab);
extern int stringarray_get_index_of_max (stringarray tab);
extern int stringarray_get_index_of_max_from (stringarray tab, int index);
extern jstr stringarray_get_min ( stringarray tab);
extern int stringarray_get_index_of_min (stringarray tab);
extern int stringarray_get_index_of_min_from (stringarray tab, int index);
extern int stringarray_nb_occurences (stringarray tab, jstr n);
#endif
