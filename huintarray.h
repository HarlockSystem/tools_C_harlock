/*.h = header */
/* < repertoire biblio standard > */
/* " repertoire perso " */
/* int argc taille de la chaine de commande du main 
   char * argv[] chaine enregistrer par le main pour entrer des lignes de commandes */
#ifndef __UNINTARRAY_H__
#define __UNINTARRAY_H__




#define RC printf ("\n")
#define HUNINTARRAY_DEFAULT_ALLOC 10


typedef unsigned int unintdata;

typedef struct _hununsigned intarray *hunintarray;

struct _hunintarray
{
  unsigned int* data;
  int len;
  int alloc;
};




extern void hunintarray_debug (hunintarray T);

extern hunintarray hunintarray_create (int len);
extern hunintarray ext_hunintarray_create (int len, int alloc);
extern hunintarray empty_hunintarray_create(int alloc);
extern hunintarray standard_empty_hunintarray_create (void);
extern void hunintarray_destroy (hunintarray T);
extern unintdata hunintarray_get (hunintarray T, int i);
/* unsigned int a = T.data[i] */
/* unsigned int a = hunintarray_get (T, i); */
extern void hunintarray_set (hunintarray T, int i , unintdata n);
extern void ext_hunintarray_set ( hunintarray T, int i, unintdata n);
/* T.data(i) = n; */
/* hunintarray_set (T, i, n); */
extern int hunintarray_length (hunintarray T);
/* int a = T.len; */
/* int a = hunintarray_length (T); */
extern void hunintarray_add(hunintarray T, unintdata n);
extern void hunintarray_delete(hunintarray T, int loc);

extern unintdata hunintarray_get_min (hunintarray T);
extern hunintarray hunintarray_concat (hunintarray T1, hunintarray T2);
extern void D_hunintarray_concat(hunintarray T1, hunintarray T2);
extern int hunintarray_seek_min_index (hunintarray T ,int start);
extern void hunintarray_sort1 (hunintarray T);/* tri par selection du minimum)*/
extern int hunintarray_num_occur(hunintarray T, unintdata n);
extern int hunintarray_recherche(hunintarray T, unintdata n);
extern unintdata  hunintarray_sum (hunintarray T);
extern float hunintarray_average (hunintarray T);
extern float hunintarray_median (hunintarray T);
extern unintdata hunintarray_get_max (hunintarray T);
extern hunintarray hunintarray_clone (hunintarray T);
extern void hunintarray_arg(int a, char* c[]); 


extern void scanf_pos_float (float *n);
extern void scanf_un_int (unsigned int *n);
extern unsigned int factorielle (unsigned int n);
extern unsigned int unchar_to_unint(unsigned char * ch);
extern void unint_swap (unsigned int *m, unsigned int *n);
extern hunintarray hunintarray_index_sorted(hunintarray T);
extern hunintarray diviseur(int i);
extern void print_premier(hunintarray I,int n);
extern unsigned int premier_1(unsigned int m);
extern unsigned int premier_2(unsigned int m);
extern unsigned int premier_3(unsigned int m);

/* T must be sorted  */
extern unsigned int hunintarray_dicho_search (hunintarray T,unsigned int value);
extern unsigned int hunintarray_search (hunintarray T,unsigned int value);
extern void hunintarray_set_length (hunintarray A, int new_size);
#endif
