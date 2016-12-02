#ifndef __TOOLS_H__
#define __TOOLS_H__
#include "tools_config.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define RC printf ("\n")

/*
  TOOLS, a part of the Cfuns modules.
  (C) Jacques-Olivier Lapeyre 2012-2016
*/

/* MEMORY TOOLS */

typedef unsigned int bool;
typedef void (*fun_memory_shrink) (void* global_data, bool verbose); /* vérifier si ceci sert encore... normalement, oui, dans memiro */

/* ajouter une étoile ici et modifier le reste du module en conséquence */
/* a priori, petite accélération ainsi obtenue */

/* le verbose du memory_skrink peut être factorisé, et n'a pas besoin
   d'être passé en paramètre à la fun_memory_shrink. Arranger cela. */

typedef struct _tools_memory_infos tools_memory_infos;

struct _tools_memory_infos {
  int allocated_memory;
  int nb_alloc;
  int max_memory;

  /* memory shrink section */
  fun_memory_shrink memory_shrinker;
  void* global_data_for_memory_shrinker;
  bool verbose_when_call_memory_shrinker;
  int max_alloc; /* when <= 0, ignored */
};

/** GLOBAL VARIABLE **/
tools_memory_infos GLOBAL_MEMORY;

/**********************/

typedef unsigned char* pointer;

typedef unsigned int file_handler;

#define GTRUE ((bool) 255)
#define TRUE ((bool) 1)
#define FALSE ((bool) 0) 

unsigned int tools_int_invert (unsigned int n);

typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned int uint;
#define NULLBYTE ((byte) 0)
#define NULLCHAR ((char) 0)

typedef char chardata;
typedef int intdata;
typedef void* data;
typedef double doubledata;
typedef char* regstr;
typedef char* buffer;

typedef int symbType;

/* une fonction qui prend en paramètre implicite la variable GLOBAL */
typedef void (*global_fun) (void); 
/* et qui ne vaut que pour ses effets de bord. */

typedef bool (*predicate) (data);

typedef int (*fun_cmp) (data, data); 
/* 
   type de fonction : comparaison de deux éléments du conteneur
   return : -n si data1 < data2
            0 si data1 == data 2
	    +n si data1 > data2
	    (n étant positif, et donc -n est négatif)
*/

typedef bool (*fun_equal) (data, data);

typedef void (*destructor) (data*); 
/*
  Destructeur d'un élément du conteneur.
  Il est passé par pointeur pour que le destructeur puisse le remettre à NULL.
*/

typedef void (*fun_print) (data);
/*
  fonction d'affichage d'un élément du conteneur.
  plutôt vers stdout.
*/

typedef void (*fun_debug) (data);
/*
  fonction d'affichage d'un élément du conteneur.
  plutôt vers stderr.
*/

typedef void (*fun_write) (data, FILE*);
/*
  écriture dans un FILE*
  ce FILE* peut être stdout ou stderr.
*/

typedef data (*fun_clone) (data);
/*
  fonction clonant un élément du conteneur.
 */

typedef void (*fun_void) (void);
/*
  fonction de type void -> void
*/

typedef void (*fun_zero) (void* ptr, destructor des);
typedef void (*fun_init) (void* ptr, destructor des);
typedef void (*fun_move) (void* src, void* target, destructor des);
typedef void (*fun_copy) (void* src, void* target, fun_clone clone);

typedef void (*fun_side_effect) (void* any_data);

extern bool tools_big_endian ();

/**************** fonctions de gestion de la mémoire ********/
extern void tools_app_init (void);
extern void tools_memory_init (void);
extern void tools_memory_init_with_memory_shrinker (fun_memory_shrink shrinker, void* global_data, bool verbose);
extern void tools_memory_shrink (void);
extern void* tools_malloc (size_t len);
extern void tools_free (void* mem, size_t len);
extern void tools_memory_debug (void);
extern void tools_memory_verbose (void);
extern void tools_memory_check_at_end_of_app (void);
/**************** fin de gestion de la mémoire **************/


/*
  retourne l'indice de la première occurence trouvée 
  retourne -1 si aucune occurence.
*/
extern int intstar_linear_search (int* tab, int len, int n);

/* 
   un peu comme atan2 mais en mieux...
   résultat retourné en radians 
   et rayon précalculé pour la suite, si on veut.
*/
extern float tools_rect_to_pol (float x, float y, float* radius);

typedef struct _APP_about* APP_about;
typedef struct _APP_about S_APP_about;

struct _APP_about {
  char* author;   /* always cloned */
  char* website;  /* always cloned */
  char* progname; /* always cloned */
  char* version;  /* always cloned */
};

extern APP_about APP_about_constructor (char* author, char* website,
					char* progname, char* version);

extern S_APP_about S_APP_about_constructor (char* author, char* website,
					    char* progname, char* version);

extern void APP_about_destructor (APP_about* about);

extern void S_APP_about_destructor (S_APP_about* about);

/* transforme un octet en chaîne de 8 caractères, chacun étant un 0 ou un 1 */
extern char* byte_explode (byte b);

extern void integ4_to_4bytes (integ4 n, byte *a, byte *b, byte *c, byte *d); 
extern integ4 bytes_to_integ4 (byte a, byte b, byte c, byte d);

extern void UNSAFE_buffer_copy (char* src, char* dst, int len);

extern char tools_hexdigit (int digit);

/* regstr section */

typedef struct _regstr_cursor* regstr_cursor;

struct _regstr_cursor {
  regstr str;
  int len;
  int index;
};

extern regstr_cursor regstr_cursor_create (regstr str);
extern void regstr_cursor_destroy (regstr_cursor* cur);
extern bool regstr_cursor_at_end (regstr_cursor cur);
extern regstr regstr_cursor_get_word (regstr_cursor cur);
extern regstr regstr_cursor_get_word_and_go_to_next (regstr_cursor cur);
extern regstr regstr_downcase (regstr str);
extern void regstr_filter_downcase (regstr str);

extern regstr regstr_sub_extract (regstr str, int d, int f);

extern char* regstr_clone (char* S);
extern char* regstr_clone_even_when_null (char* S);
extern char* regstr_clone_with_len (char* S, int len);
extern int regstr_compare (char* S, char *T);
extern bool regstr_equals (char* S, char *T);
extern void regstr_destroy (data* S);
extern void regstr_destroy_raw (char** pstr);
extern void regular_regstr_destroy (char** S); /* warns if S == NULL */
extern void regstr_debug (char* S);
extern void generic_regstr_debug (void* S);
extern char* regstr_concat (char* S1, char* S2);
extern void D_regstr_concat (char** S, char* S2);
extern char* regstr_add_int_suffix (char* S, int n);
extern void D_regstr_add_int_suffix (char** S, int n);

/* retourne un clone de S sans les occurences de c */
extern char* tools_regstr_filter_subtract1 (char* S, char c);
/*
  fonction ajoutée juste pour les besoins de gll_ihm
  Une fois qu'un filtrage plus puissant aura été mis en place,
  voir s'il est nécessaire de garder la filter_subtract1.
*/

/* Lire le commentaire présent dans tools.c sur la fonction regstr_destroy_of_size */
extern void regstr_destroy_of_size (char** S, int len);

extern data generic_regstr_clone (data S);
extern int generic_regstr_compare (data S, data T);
extern void generic_regstr_destroy (void** S);
extern char* empty_regstr_create (void);
extern bool is_empty_regstr (char* S);

extern int regstr_char_count (char* S, char c);
extern int regstr_get_number_of_lines (char* S);

extern bool regstr_equal(char* str1, char* str2);
extern void regstr_destroy_len(char ** sstr, int len);

/* end of regstr section */

extern void tools_error (char *msg);

/* échange de deux caractères, de deux entiers ou de deux doubles passés par pointeur */
extern void char_swap (char *m, char *n);
extern void int_swap (int *m, int *n);
extern void double_swap (double *m, double *n);
extern void ptr_swap(void **p1, void **p2 );

/* Conversion d'une chaîne de type "123" en int 123 */
extern int string_to_int (char* ch);
extern bool string_is_int_value (char* ch);

/* Saisie d'un décimal positif */
extern void scanf_posfloat (float *n);
/* Saisie d'un entier positif */
extern void scanf_posint (int *n);

/* Saisie d'un entier entre a et b */
extern void scanf_ABint (char* msg, int *n, int a, int b);

/* o or n */
extern char input_yes_or_no (void);

extern char* not_empty_regstr_read (void);

extern int tool_random_int (int vmin, int vmax);
extern double tool_random_double (double vmin, double vmax);
extern float tool_random_float (float vmin, float vmax);

/* Code importé de mon logiciel de traitement d'image */

#define _WARNING_LEVEL_ 1

extern void tools_warn (char* msg);

extern void tool_send_warning (char* w);
extern void tool_send_error (char* e);
extern int tools_pseudolog_bin (double n);
extern void int_set_minival (int *i, int vmin);
extern void int_set_minival_and_warn (int *i, int vmin);
extern void int_normalize (int *i, int vmin, int vmax);
extern void int_normalize_oob (int *i, int vmin, int vmax, bool* out);
extern void int_normalize_and_warn (int *i, int vmin, int vmax);
/* warns if (*i < vmin or *i > vmax) and #ifdef DEBUG */
extern void float_normalize (float* i, float vmin, float vmax);
extern void float_normalize_and_warn (float* i, float vmin, float vmax);
extern void double_normalize (double* i, double vmin, double vmax);
extern void double_normalize_and_warn (double* i, double vmin, double vmax);

extern void doublestar_cpy (double *dst, double *src, int dsti, int srci, int len);

/* fin du code importé du logiciel de traitement d'image */

extern int generic_regstr_compare (data A, data B);
extern void generic_regstr_print (data S);
extern void generic_regstr_print_to_stderr (data S);
extern void generic_regstr_destroy (data *S);
extern data generic_regstr_clone (data S);

extern int regstr_try_to_extract_number (char* str, int start, bool* is_an_int, int* end);
extern void regstr_debug_from (char* str, int start);

extern char* F_regstr_trim (regstr s); /* pas stable */ /* corriger quand on a le temps */

/* caractères actuellement autorisés : alphanumériques non accentués, ., - et _ */
extern bool tools_is_regular_file_name (char* filename);

/*
  type de donnée utilisé par exemple dans gll_file pour donner les positions
  de début (offset_first) et de fin (offset_last) des fichiers "encapsulés"
  dans un .pack.
*/
typedef struct _gll_index S_gll_index;
typedef struct _gll_index*  gll_index;

struct _gll_index {
  int offset_first;
  int offset_last;
};

extern gll_index gll_index_create (int offset_first, int offset_last);
extern gll_index gll_index_create_len (int offset_first, int len);
extern void gll_index_destroy (gll_index* ind);
extern void generic_gll_index_destroy (void** ind);
extern void* generic_gll_index_clone (void* ind);
extern gll_index gll_index_clone (gll_index ind);
extern void generic_gll_index_print (void* ind);
extern int generic_gll_index_compare (void* ind1, void *ind2); /* cmp based of offset_first first */
extern int gll_index_compare (gll_index ind1, gll_index ind2); /* cmp based of offset_first first */
extern void gll_index_debug (gll_index ind);

extern void gll_index_get (gll_index ind, int* offset_first, int *offset_last, int *len);

extern int gll_index_length (gll_index ind);

#ifdef DEBUG
extern bool is_regular_gll_index (gll_index ind);
#endif

/* GLL_ARRAY section */
/* un gll_array est un array simplifié */

typedef struct _gll_array *gll_array;

struct _gll_array {
  int len;
  int alloc;
  int data_type;
  void** data;
  destructor del;
};

/* 
   Pour vérification des types de données stockées dans des gll_array 
   dans les modules GLL.
*/

#define GLL_UNKNOWN_DATA_TYPE -1
#define GLL_COLOUR_DATA_TYPE 0
#define GLL_DISPLAY_RECT_AREA_DATA_TYPE 1
/* gll_display_rect_area = zones clickables pour gll_draw */
#define CHAR_DATA_TYPE 2
#define GLL_IMAGE_ICON_DATA_TYPE 3
/* image_icon : image + Surface servant d'icône dans une interface graphique à la gll_draw */
#define GLL_TREELINEDATA_DATA_TYPE 4
/* données caractérisant un segment d'arbre de gll_fractree : x1, y1, x2, y2, couleur et "rayon" */

#define GLL_SPRITE_FRAME_DATA_TYPE 5
#define GLL_SPRITE_ANIM_DATA_TYPE 6
#define GLL_SPRITE_DATA_TYPE 7
/* gll_sprites*/

#define GLL_TILE_DATA_TYPE 8
/* gll_levpart version du 8 juillet 2014 => code sans doute jetable */

#define GLL_FONT_SURFACE_DATA_TYPE 9
/* gll_font version du 20 juillet 2014 */

#define GLL_ITEM_DATA_TYPE 10
/* gll_item version du 16 août 2014 */

#define GLL_INT_DATA_TYPE 11

#define GTREE_CELL_DATA_TYPE 12
/* module gtree ajouté dans Cfuns le 19 août 2014 */

#define REGSTR_DATA_TYPE 13
/* ajouté le 4 mars 2015 pour le module gll_gfx */

#define GLL_ARRAY_DATA_TYPE 14
/*
 ajouté le 11 août 2015 pour gll_ihm.c :
 les frames ont un tableau de tableau
 de childrens.
*/

extern gll_array empty_gll_array_create (destructor F, int alloc, int data_type);
extern void gll_array_destroy (gll_array* A);

/* when you have a gll_array of gll_arrays */
extern void gll_array_generic_destructor (void** A);

/* set function 'element_clone' to NULL for "pointer copy" */
extern gll_array gll_array_clone (gll_array A, fun_clone element_clone);

extern void* gll_array_get (gll_array A, int i);
extern void gll_array_set (gll_array A, int i, void* d);
extern void gll_array_add (gll_array A, void* d);

extern void gll_array_zero (gll_array A); /* vide A sans modifier son occupation en mémoire */
extern void gll_array_shrink (gll_array A); /* réduit l'occupation mémoire de A autant que possible */

extern void gll_array_write (gll_array A, fun_write write, FILE* file);

extern void UNSORTED_gll_array_remove (gll_array A, int i, bool must_destroy);

/* pointer based comparison */
extern bool is_in_gll_array (gll_array A, void* d);
extern void gll_array_find (gll_array A, void* d, bool* found, int* index);

/* fun_equal based comparison */
extern bool is_in_gll_array_equal (gll_array A, void* d, fun_equal equal);

#ifdef DEBUG /* maintenue pour compatibilité ascendante */
extern void gll_array_check_data_type (gll_array A, int data_type);
#endif       /* utilisez plutôt la v2 qui retourne un booléen */
/* et exploitez la valeur de ce booléen dans vos zones #DEBUG */

#ifdef DEBUG
extern bool gll_array_check_data_type_v2 (gll_array A, int data_type);
#endif

/* End of GLL_ARRAY section */



/* Beginning of gll_charray section */ 

typedef struct _gll_charray* gll_charray;

struct _gll_charray {
  int w;
  int h;
  bool has_alpha;
  unsigned char alpha;
  unsigned char* data;
};

extern gll_charray gll_charray_alloc (int w, int h);
extern gll_charray gll_charray_constructor (int w, int h, unsigned char initvalue);
extern void gll_charray_set_alpha (gll_charray cha, bool has_alpha, unsigned char alpha);
extern void gll_charray_destructor (gll_charray* cha);
extern void generic_gll_charray_destructor (void** cha);

extern gll_charray gll_charray_clone (gll_charray cha);

extern unsigned char* gll_charray_get_all (gll_charray cha, int* w, int *h, bool* has_alpha, unsigned char* alpha);

extern unsigned char* gll_charray_get_location (gll_charray cha, int x, int y);

/* End of gll_charray section */ 



/* Beginning of tools_rect section */

typedef struct _tools_rect S_tools_rect;
typedef struct _tools_rect *tools_rect;

struct _tools_rect {
  int x1;
  int y1;
  int x2;
  int y2;
};

extern S_tools_rect S_tools_rect_create (int x1, int y1, int x2, int y2);

extern tools_rect tools_rect_create (int x1, int y1, int x2, int y2);

extern bool tools_is_inside_rect (tools_rect R, int x, int y); 

extern tools_rect tools_rect_clone (tools_rect R);

extern tools_rect tools_rect_create_wh (int x1, int y1, int w, int h);

extern void tools_rect_destroy (tools_rect* R);

extern void tools_rect_get_xxyy (tools_rect R, int *x1, int *y1, int *x2, int *y2);
extern void tools_rect_get_xywh (tools_rect R, int *x1, int *y1, int *w, int *h);
extern void tools_rect_get_wh (tools_rect R, int *w, int *h);
extern void tools_rect_get_xxyywh (tools_rect R, int *x1, int *y1, int *x2, int *y2, int *w, int *h);

extern void tools_rect_set_xxyy (tools_rect R, int x1, int y1, int x2, int y2);

extern void tools_rect_zero (tools_rect R);

extern void tools_rect_debug (tools_rect R);
extern void tools_rect_debug_wh (tools_rect R);

#ifdef DEBUG
extern bool is_regular_tools_rect (tools_rect R);
extern bool is_regular_not_empty_tools_rect (tools_rect R);
#endif

/* End of tools_rect section */


/* Beginning of tools_rectf section */
typedef struct _tools_rectf S_tools_rectf;
typedef struct _tools_rectf *tools_rectf;

struct _tools_rectf {
  float x1;
  float y1;
  float x2;
  float y2;
};

extern S_tools_rectf S_tools_rectf_create (float x1, float y1, float x2, float y2);

extern tools_rectf tools_rectf_create (float x1, float y1, float x2, float y2);

extern bool tools_is_inside_rectf (tools_rectf R, float x, float y); 

extern tools_rectf tools_rectf_clone (tools_rectf R);

extern tools_rectf tools_rectf_create_wh (float x1, float y1, float w, float h);

extern void tools_rectf_destroy (tools_rectf* R);

extern void tools_rectf_get_xxyy (tools_rectf R, float *x1, float *y1, float *x2, float *y2);

extern void tools_rectf_clip (tools_rectf R, float minx, float miny, float maxx, float maxy);
/* End of tools_rectf section */

/* Allocateurs simples mais astucieux */
extern void tools_bialloc (void** ptr1, size_t size1, void** ptr2, size_t size2);
extern void tools_bifree (void* ptr1, void* ptr2, size_t size);


/* section sur les fast_array */

typedef struct _fast_array *fast_array;

struct _fast_array {
  pointer data;
  int elem_size;
  int len;
  int w;
  int alloc;
  bool resizable;
  /*bool locked; locked n'est plus utilisé. Vérifier ? Et Virer ?*/
};

extern fast_array fast_array_constructor (int elem_size, int initial_alloc, bool resizable);
extern void fast_array_destructor (fast_array* A);
extern void generic_fast_array_destructor (void** A);
extern fast_array fast_array_clone (fast_array A);

/* return NULL when not found */
extern void* fast_array_linear_search (fast_array A, void* value, fun_equal equal);

extern pointer fast_array_get_pointer_to_nth (fast_array A, int n);
extern pointer fast_array_get_pointer_to_last (fast_array A);
extern pointer fast_array_get_pointer_to_end (fast_array A);

extern fast_array fast_array_2D_constructor (int elem_size, int w, int h,
					     bool resizable);

extern pointer fast_array_2D_get_pointer_to_xy (fast_array A,
						int x, int y);

extern void fast_array_2D_resize (fast_array A, int neww, int newh,
				  fun_init init, fun_move move, destructor des);

extern pointer fast_array_get_at_and_clone (fast_array A, int n);

extern void fast_array_clone_and_set_to (fast_array A, int n, pointer obj);

extern void fast_array_add (fast_array A, pointer obj);

extern void fast_array_shrink (fast_array A);

extern void fast_array_zero (fast_array A);
extern void fast_array_zero_and_shrink (fast_array A);

extern void generic_int_zero (void* intptr);

/*
  zeroes the elements of A 
  len is not updated.
*/
extern void fast_array_zero_elements (fast_array A, fun_zero Z, destructor des);
extern void fast_array_copy (fast_array A, int from, int to, int size, fun_copy F, fun_clone clone);
extern void fast_array_move (fast_array A, int from, int to, int size, fun_move F, destructor des);

extern void fast_array_debug (fast_array A, fun_print printer, char* sep);

extern void fast_array_reverse (fast_array A);

/*
  fonction hyper spécifique conçue pour utiliser 
  un fast_array comme une fifo, fifo qui sert elle-même à simuler
  la récursivité.
*/
extern void fast_array_fifosim_delete_head (fast_array A);

/* fin de la section sur les fast_array */


/* 
   code sur les nombres complexes ; utilisé à ce jour (27 mai 2015) uniquement 
   dans mon cours sur Mandelbrot... voir si c'est nécessaire de garder cela.
*/

typedef struct _complex complex;

struct _complex {
  double a; /* Re; */
  double b; /* Im; */
};

/* pas 'constructor' car pas de pointeur */
extern complex make_complex (double a, double b);

/* Z1 += Z2; */
extern void D_complex_plus (complex* Z1, complex Z2);

/* Z *= Z */
extern void D_complex_square (complex* Z);

extern double complex_mod (complex Z);



//tools add by harlock

void my_sleep(int n);
void endian_check(void);


#endif
