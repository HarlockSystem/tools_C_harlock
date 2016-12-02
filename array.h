/*.h = header */
/* < repertoire biblio standard > */
/* " repertoire perso " */
/* int argc taille de la chaine de commande du main 
   char * argv[] chaine enregistrer par le main pour entrer des lignes de commandes */
#ifndef __ARRAY_H__
#define __ARRAY_H__


#define RC printf ("\n")
#define ARRAY_DEFAULT_ALLOC 1024

#include "tools.h"

typedef void* data;
typedef struct _array *array;
typedef array heap;

struct _array
{
  void** data;
  int len;
  int alloc;
};


extern void array_debug (array T);
extern array array_create (int len);
extern array ext_array_create (int len, int alloc);
extern array empty_array_create(int alloc);
extern array standard_empty_array_create (void);
extern void array_destroy (array T);
extern data array_get (array T , int i);
/* int a = T.data[i] */
/* int a = array_get (T, i); */
extern void array_set (array T , int i , data n);
extern void ext_array_set ( array T, int i, data n);
/* T.data(i) = n; */
/* array_set (T, i, n); */
extern int array_length (array T);
/* int a = T.len; */
/* int a = array_length (T); */
extern void array_add(array T, data n);
extern void array_delete(array T, int loc);

extern data array_get_min (array T);
extern array array_concat (array T1, array T2);
extern void D_array_concat(array T1, array T2);
extern int array_seek_min_index (array T ,int start);
extern void array_sort1 (array T);/* tri par selection du minimum)*/
extern int array_num_occur(array T, data n);
extern int array_recherche(array T, data n);
extern int array_sum (array T);
extern float array_average (array T);
extern float array_median (array T);
extern data array_get_max (array T);
extern array array_clone (array T);
extern void array_arg(int a, char* c[]); 

extern int square (int n);
extern void scanf_pos_int (int *n);
extern void scanf_pos_int (int *n);
extern int factorielle (int n);
extern int string_to_int(char * ch);
extern void int_swap (int *m, int *n);
extern array array_index_sorted(array T);
extern array diviseur(int i);
extern void print_premier(array I,int n);
extern int premier_1(int m);
extern int premier_2(int m);
extern int premier_3(int m);

extern array args_to_array(int nb , char **args);
extern array random_array(int len);

//heap sort
extern array array_clone_heap_sort_by_min(array I);
extern void array_D_heap_sort_by_min(array I);
extern array array_clone_heap_sort_by_max(array I);
extern void array_D_heap_sort_by_max(array I);

extern heap heap_create_empty(int alloc);
extern heap heap_ext_create(int len);
extern heap heap_destroy(heap* H);
extern bool heap_is_empty( heap H);
extern int heap_count_children(heap H, int i);
extern void heap_sort_by_min(heap H, array I);
extern void heap_sort_by_max(heap H, array I);
extern int heap_parent_index(int x);
extern int heap_left_child_index(int x);
extern int heap_right_child_index(int x);
extern data heap_get_parent(heap H, int x);
extern data heap_get_head_value(heap H);
extern bool heap_is_parent_smaller(heap H, int x);
extern bool heap_is_parent_bigger(heap H, int x);
extern bool heap_has_parent(heap H, int x);
extern void heap_del_head_val_by_min(heap H);
extern void heap_del_head_val_by_max(heap H);
extern int heap_get_small_child_index(heap H,int x);
extern int heap_get_big_child_index(heap H,int x);

#endif
