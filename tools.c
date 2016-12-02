#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "tools.h"
#include "jstr.h"

int intstar_linear_search (int* tab, int len, int n)
{
  int i;
  for (i = 0; i < len; i++)
    {
      if (tab[i] == n)
	return i;
    }

  return -1;
}

void fast_array_reverse (fast_array A)
{
  int mid = (A->len - 2) / 2;
  int i, j;
  if (A->len <= 1)
    return;

  for (i = 0, j = A->len - 1; i <= mid; i++, j--)
    {
      int ii = i * A->elem_size;
      int jj = j * A->elem_size;
      int k;      
      for (k = 0; k < A->elem_size; k++)
	{
	  char tmp = A->data[ii + k];
	  A->data[ii + k] = A->data[jj + k];
	  A->data[jj + k] = tmp;
	}
    }
}

void gll_array_write (gll_array A, fun_write write, FILE* file)
{
  int i;
  
  if (write == NULL)
    return;
  
  for (i = 0; i < A->len; i++)
    {
      (*write) (A->data[i], file);
      fprintf (file, "\n");
    }
}

void regstr_filter_downcase (regstr str)
{
  int i;
  for (i = 0; str[i] != '\0'; i++)
    {
      if ((str[i] >= 'A') && (str[i] <= 'Z'))
	str[i] += ('a' - 'A');
    }
}

regstr regstr_downcase (regstr str)
{
  int len = regstr_len (str);
  regstr down = (regstr) tools_malloc (sizeof (char) * (len + 1));
  int i;
  for (i = 0; i < len; i++)
    {
      char c = str[i];
      if ((c >= 'A') && (c <= 'Z'))
	down[i] = c + 'a' - 'A';
      else
	down[i] = c;
    }
  down[i] = NULLCHAR;
  return down;
}

/* return NULL when not found */
void* fast_array_linear_search (fast_array A, void* value, fun_equal equal)
{
  int i;
  for (i = 0; i < A->len; i++)
    {
      void* elem = A->data + i * A->elem_size;
      if ((*equal) (elem, value))
	return elem;
    }

  return NULL;
}


void fast_array_zero (fast_array A)
{
  A->len = 0;
}

void fast_array_zero_elements (fast_array A, fun_zero Z, destructor des)
{
  int i;

  if (Z == NULL)
    {
#ifdef DEBUG
      fprintf (stderr, "fast_array_zero_elements : fun_zero is null.\n");
#endif
      return;
    }
    
  for (i = 0; i < A->alloc; i++)
    (*Z) (A->data + i * A->elem_size, des);
}

void fast_array_copy (fast_array A, int from, int to, int size, fun_copy F, fun_clone clone)
{
  int i;
  if (F == NULL)
    {
#ifdef DEBUG
      fprintf (stderr, "fast_array_copy : fun_copy is null.\n");
#endif      
      return;
    }

  for (i = 0; i < size; i++)
    {
      void* target = fast_array_get_pointer_to_nth (A, to + i);
      void* src = A->data + (from + i) * A->elem_size;
      (*F) (src, target, clone);
    }
}

void fast_array_move (fast_array A, int from, int to, int size, fun_move F, destructor des)
{
  int i;
  if (F == NULL)
    {
#ifdef DEBUG
      fprintf (stderr, "fast_array_move : fun_move is null.\n");
#endif      
      return;
    }

  for (i = 0; i < size; i++)
    {
      void* target = fast_array_get_pointer_to_nth (A, to + i);
      void* src = A->data + (from + i) * A->elem_size;
      (*F) (src, target, des);
    }
}

fast_array fast_array_2D_constructor (int elem_size, int w, int h,
				      bool resizable)
{
  int alloc = w * h;
  fast_array A = fast_array_constructor (elem_size, alloc, resizable);
  A->w = w;
  return A;
}

pointer fast_array_2D_get_pointer_to_xy (fast_array A,
					 int x, int y)
{
  if (A->w == -1)
    {
#ifdef DEBUG
      fprintf (stderr, "fast_array_2D_get_pointer_to_xy : array is flat.\n");
      fprintf (stderr, "assume y == 1.\n");
#endif
      return fast_array_get_pointer_to_nth (A, x);
    }

  return  A->data + A->elem_size * (y * A->w + x);
}

void fast_array_debug (fast_array A, fun_print printer, char* sep)
{
  pointer p = A->data;
  int i;
  for (i = 0; i < A->len; i++, p += A->elem_size)
    {
      (*printer) (p);
      fprintf (stderr, sep);
    }
}

void tools_rect_set_xxyy (tools_rect R, int x1, int y1, int x2, int y2)
{
  R->x1 = x1; R->y1 = y1; R->x2 = x2; R->y2 = y2;
}

void tools_rect_zero (tools_rect R)
{
  R->x1 = R->y1 = R->x2 = R->y2 = 0;
}

APP_about APP_about_constructor (char* author, char* website,
				 char* progname, char* version)
{
  APP_about about = (APP_about) tools_malloc (sizeof (struct _APP_about));
  about->author = regstr_clone ((author == NULL)
				? "Jacques-Olivier Lapeyre"
				: author);
  about->website = regstr_clone ((website == NULL)
				 ? "http://www.multiparadigme.org"
				 : website);
  about->progname = regstr_clone ((progname == NULL)
				  ? "Foo bar"
				  : progname);
  about->version = regstr_clone ((version == NULL)
				 ? "zero"
				 : version);
  return about;
}

S_APP_about S_APP_about_constructor (char* author, char* website,
				     char* progname, char* version)
{
  S_APP_about about;
  about.author = regstr_clone ((author == NULL)
				? "Jacques-Olivier Lapeyre"
			       : author);
  about.website = regstr_clone ((website == NULL)
				? "http://www.multiparadigme.org"
				: website);
  about.progname = regstr_clone ((progname == NULL)
				 ? "Foo bar"
				 : progname);
  about.version = regstr_clone ((version == NULL)
				? "zero"
				: version);
  return about;  
}

void APP_about_destructor (APP_about* aabout)
{
  APP_about about = *aabout;
  if (about->author != NULL)
    regular_regstr_destroy (&(about->author));
  if (about->website != NULL)
    regular_regstr_destroy (&(about->website));
  if (about->progname != NULL)
    regular_regstr_destroy (&(about->progname));
  if (about->version != NULL)
    regular_regstr_destroy (&(about->version));
  tools_free (about, sizeof (struct _APP_about));
  *aabout = NULL;
}

void S_APP_about_destructor (S_APP_about* about)
{
  if (about->author != NULL)
    regular_regstr_destroy (&(about->author));
  if (about->website != NULL)
    regular_regstr_destroy (&(about->website));
  if (about->progname != NULL)
    regular_regstr_destroy (&(about->progname));
  if (about->version != NULL)
    regular_regstr_destroy (&(about->version));
}

int regstr_char_count (char* S, char c)
{
  int i, cpt = 0;
  for (i = 0; S[i] != NULLCHAR; i++)
    {
      if (S[i] == c)
	cpt++;
    }
  return cpt;
}

int regstr_get_number_of_lines (char* S)
{
  if (S[0] == NULLCHAR)
    return 0;
  else
    {
      int i, cpt = 0;
      for (i = 0; S[i] != NULLCHAR; i++)
	{
	  if (S[i] == '\n')
	    cpt++;
	}

      
      if ((i >= 2) && (S[i - 1] == '\n'))
	  cpt--;
	  
      return cpt + 1; 
    }
}

void tools_rect_debug (tools_rect R)
{
  fprintf (stderr, "(%d ; %d ; %d ; %d)", R->x1, R->y1, R->x2, R->y2); 
}

void tools_rect_debug_wh (tools_rect R)
{
  int w = R->x2 - R->x1 + 1;
  int h = R->y2 - R->y1 + 1;
  fprintf (stderr, "(%d ; %d) and size (%d ; %d)", R->x1, R->y1, w, h);
}

/* retourne un clone de S sans les occurences de c */
char* tools_regstr_filter_subtract1 (char* S, char c)
{
  int i, j = 0, lenT = 0;
  char* T = NULL;
  for (i = 0; S[i] != NULLCHAR; i++)
    {
      if (S[i] != c)
	lenT++;
    }

  T = (char*) tools_malloc (sizeof(char) * (lenT + 1));
  for (i = 0; S[i] != NULLCHAR; i++)
    {
      if (S[i] != c)
	{
	  T[j] = S[i];
	  j++;
	}
    }
  
  T[lenT] = NULLCHAR;
  return T;
}
  
/*
  fonction ajoutée juste pour les besoins de gll_ihm
  Une fois qu'un filtrage plus puissant aura été mis en place,
  voir s'il est nécessaire de garder la filter_subtract1.
*/

void int_set_minival (int *i, int vmin)
{
  if (*i < vmin) *i = vmin;
}

void int_set_minival_and_warn (int *i, int vmin)
{
  if (*i < vmin)
    {
#ifdef DEBUG
      fprintf (stderr, "FUNCTION int_set_minival_and_warn :\n");
      fprintf (stderr, "Value %d should be greater or equal to %d. I set it to %d.\n", *i, vmin, vmin); 
#endif
      *i = vmin;
    }
}

unsigned int tools_int_invert (unsigned int n)
{
  unsigned int m = n;
  unsigned char* cPtr = (unsigned char*) (&m);
  unsigned char a = cPtr[0];
  cPtr[0] = cPtr[3];
  cPtr[3] = a;
  a = cPtr[1];
  cPtr[1] = cPtr[2];
  cPtr[2] = a;
  return m;
}

bool tools_big_endian ()
{
  unsigned int n = 0xFF000000;
  unsigned char* cPtr = (unsigned char*) (&n);
  if ((*cPtr) == 0xFF)
    return TRUE;
  else
    return FALSE;
}

/* section sur les fast_array */

/* private prototypes */
void fast_array_resize (fast_array A, int new_alloc);
/* */

fast_array fast_array_constructor (int elem_size, int initial_alloc, bool resizable)
{
  fast_array A = (fast_array) tools_malloc (sizeof (struct _fast_array));
  if (initial_alloc < 1)
    {
#ifdef DEBUG
      fprintf (stderr, "FUNCTION fast_array_constructor :\n");
      fprintf (stderr, "initial alloc value < 1. I set it to 1.\n");

#endif
      initial_alloc = 1;
    }
  A->elem_size = elem_size;
  A->len = 0;
  A->w = -1;
  A->alloc = initial_alloc;
  A->resizable = resizable;
  /* A->locked = FALSE; */
  A->data = (pointer) tools_malloc (elem_size * initial_alloc);
  return A;
}

fast_array fast_array_clone (fast_array A)
{
  fast_array B = (fast_array) tools_malloc (sizeof (struct _fast_array));
  int size = sizeof (char) * A->elem_size * A->len;
  B->elem_size = A->elem_size; B->len = A->len;
  B->alloc = A->len; /* ce n'est pas une erreur */
  B->resizable = A->resizable;
  /* B->locked = A->locked; */
  B->data = (pointer) tools_malloc (size);
  UNSAFE_buffer_copy ((char*) A->data, (char*) B->data, size);
  return B;
}

void fast_array_destructor (fast_array* AA)
{
  {
    fast_array A = *AA;
    if (A == NULL)
      fprintf (stderr, "A NULL\n");
    else if (A->data == NULL)
      fprintf (stderr, "A->data NULL\n");
    tools_free (A->data, A->elem_size * A->alloc);
    tools_free (A, sizeof (struct _fast_array));
    *AA = NULL;
  }
}

void generic_int_zero (void* intptr)
{
  int* ptr = (int*) intptr;
  *ptr = 0;
}
  
void generic_fast_array_destructor (void** AA)
{
  fast_array* A = (fast_array*) AA;
  fast_array_destructor (A);
  *AA = NULL;
}

/*
void fast_array_lock (fast_array A)
{
  A->locked = TRUE;
}
  
void fast_array_unlock (fast_array A)
{
  A->locked = FALSE;
  }*/

pointer fast_array_get_pointer_to_nth (fast_array A, int n)
{
  if (n < 0) return NULL;
  if ((n >= A->len) && (!A->resizable)) return NULL;
  if (n >= A->alloc)
    fast_array_resize (A, 1 + 2 * n);
    
  if (n >= A->len)
    A->len = n + 1;
  return A->data + n * A->elem_size;
}

pointer fast_array_get_pointer_to_last (fast_array A)
{
  return fast_array_get_pointer_to_nth (A, A->len - 1);
}

pointer fast_array_get_pointer_to_end (fast_array A)
{
  return fast_array_get_pointer_to_nth (A, A->len);
}
  
pointer fast_array_get_at_and_clone (fast_array A, int n)
{
  pointer ptr = NULL;
  if (n < 0) return NULL;
  if (n >= A->len) return NULL;

  ptr = (pointer) tools_malloc (A->elem_size);
  UNSAFE_buffer_copy ((char *) (A->data + n * A->elem_size),
		      (char*) ptr, A->elem_size);
  return ptr;
}


/* private function */
void fast_array_resize (fast_array A, int new_alloc)
{
  int index_of_last = ((new_alloc <= A->len) ? new_alloc - 1 : A->len - 1);
  pointer new_data = (pointer) tools_malloc (new_alloc * A->elem_size);
  
  UNSAFE_buffer_copy ((char*) A->data, (char*) new_data, A->elem_size * (index_of_last + 1));
  
  tools_free (A->data, A->alloc * A->elem_size);
  A->data = new_data;
  A->alloc = new_alloc;
  A->len = index_of_last + 1;
}

void fast_array_clone_and_set_to (fast_array A, int n, pointer obj)
{
  if (n < 0) return;
  if ((n >= A->len) && (!A->resizable)) /* || A->locked)) */
    return;
  if (n >= A->len)
    {
      if (n >= A->alloc)
	fast_array_resize (A, 1 + 2 * n);

      if (A->len <= n)
	A->len = n + 1;
    }
  
  UNSAFE_buffer_copy ((char *) obj,
		      (char*) (A->data + n * A->elem_size), A->elem_size);
}

void fast_array_add (fast_array A, pointer obj)
{
  fast_array_clone_and_set_to (A, A->len, obj);
}

void fast_array_zero_and_shrink (fast_array A)
{
  A->len = 0;
  fast_array_resize (A, 1);
}

void fast_array_shrink (fast_array A)
{
  fast_array_resize (A, A->len);
}

void fast_array_fifosim_delete_head (fast_array A)
{
  UNSAFE_buffer_copy ((char*)
		      (A->data + (A->len - 1) * A->elem_size),
		      (char*) A->data, A->elem_size);
  /* 
     remplacer par l'occasion par un appel à memcpy ;
     trouver les autres appels à UNSAFE...
     les remplacer aussi, et en parler pendant un cours.
  */

  (A->len)--;
}

/* fin de la section sur les fast_array */


/* caractères actuellement autorisés : alphanumériques non accentués, ., - et _ */
bool tools_is_regular_file_name (char* s)
{
  int i;
  for (i = 0; s[i] != NULLCHAR; i++)
    {
      bool succeed = FALSE;
      if ((s[i] >= 'a') && (s[i] <= 'z'))
	succeed = TRUE;
      else if ((s[i] >= 'A') && (s[i] <= 'Z'))
	succeed = TRUE;
      else if ((s[i] >= '0') && (s[i] <= '9'))
	succeed = TRUE;
      else if ((s[i] == '-') || (s[i] == '_'))
	succeed = TRUE;
      if (succeed == FALSE)
	return FALSE;
    }

  return TRUE;
}


/* Beginning of gll_charray section */ 

gll_charray gll_charray_alloc (int w, int h)
{
  gll_charray cha = (gll_charray) tools_malloc (sizeof (struct _gll_charray));
  cha->w = w; cha->h = h; cha->has_alpha = FALSE; cha->alpha = ((char) 0);
  cha->data = (unsigned char*) tools_malloc (sizeof (unsigned char) * w * h);
  return cha;
}

gll_charray gll_charray_constructor (int w, int h, unsigned char initvalue)
{
  gll_charray cha = gll_charray_alloc (w, h);
  int i;
  for (i = 0; i < cha->w * cha->h; i++)
    cha->data[i] = initvalue;
  return cha;
}

void gll_charray_set_alpha (gll_charray cha, bool has_alpha, unsigned char alpha)
{
  cha->has_alpha = has_alpha;
  cha->alpha = alpha;
}

void gll_charray_destructor (gll_charray* ccha)
{
  gll_charray cha = *ccha;
  tools_free (cha->data, sizeof (char) * cha->w * cha->h);
  tools_free (cha, sizeof (struct _gll_charray));
  *ccha = NULL;
}

void generic_gll_charray_destructor (void** ccha)
{
  gll_charray* cha = (gll_charray*) ccha;
  gll_charray_destructor (cha);
  *ccha = NULL;
}

gll_charray gll_charray_clone (gll_charray cha)
{
  gll_charray clone = gll_charray_alloc (cha->w, cha->h);
  int i;
  gll_charray_set_alpha (clone, cha->has_alpha, cha->alpha);
  for (i = 0; i < cha->w * cha->h; i++)
    clone->data[i] = cha->data[i];
  return clone;
}

unsigned char* gll_charray_get_all (gll_charray cha, int* w, int *h, bool* has_alpha, unsigned char* alpha)
{
  *w = cha->w; *h = cha->h; *has_alpha = cha->has_alpha; *alpha = cha->alpha;
  return cha->data;
}

unsigned char* gll_charray_get_location (gll_charray cha, int x, int y)
{
#ifdef DEBUG
  if ((x < 0) || (y < 0) || (x >= cha->w) || (y >= cha->h))
    {
      fprintf (stderr, "FUNCTION gll_charray_get_location :\n");
      fprintf (stderr, "out of bounds error.\n");
    }
#endif
  return cha->data + y * cha->w + x;
}

/* End of gll_charray section */ 


bool regstr_equals (char* S, char *T)
{
  int i = 0;
  while ((S[i] == T[i]) && (S[i] != NULLCHAR) && T[i] != NULLCHAR)
    {
      i++;
    }
  return (T[i] == S[i]);
}

void regstr_debug_from (char* str, int i)
{
  while (str[i] != NULLCHAR)
    {
      fprintf (stderr, "%c", str[i]);
      i++;
    }
}

int regstr_try_to_extract_number (char* str, int start, bool* is_an_int, int* end)
{
  int i = start; bool negative = FALSE;
  int value = 0;
  *is_an_int = TRUE;

  if (str[i] == '-')
    {
      negative = TRUE;
      i++;
    }
  while ((str[i] != ' ') && (str[i] != '\n') && (str[i] != NULLCHAR))
    {
      if ((str[i] < '0') || (str[i] > '9'))
	{
	  *is_an_int = FALSE;
	  break;
	}
      value *= 10;
      value += (str[i] - '0');
    }

  if (negative)
    value = -value;

  if (*is_an_int)
    {
      *end = i - 1;
      return value;
    }
  else
    {
      *end = start;
      return -1;
    }
}

char tools_hexdigit (int digit)
{
  if ((digit < 0) || (digit > 15))
    {
#ifdef DEBUG
      fprintf (stderr, "tools_hexdigit : digit = %d. Must be in [[0 ; 15]]. Assume digit == .\n", digit);
#endif
      return '0';
    }
  else if ((digit >= 0) && (digit <= 9))
    return '0' + digit;
  else /* assume digit in [[10;15]] */
    return 'A' + digit - 10;
}

regstr_cursor regstr_cursor_create (regstr str)
{
  regstr_cursor cur = (regstr_cursor) tools_malloc (sizeof (struct _regstr_cursor));
  cur->str = str;
  cur->len = regstr_len (str);
  cur->index = 0;
  return cur;
}

void regstr_cursor_destroy (regstr_cursor* cur)
{
  tools_free (*cur, sizeof (struct _regstr_cursor));
  *cur = NULL;
}

bool regstr_cursor_at_end (regstr_cursor cur)
{
  return (cur->index >= cur->len);
}

regstr regstr_cursor_get_word (regstr_cursor cur)
{
  int d = cur->index;
  int f;
  for (f = d; ((cur->str[f] != NULLCHAR) && (cur->str[f] != ' ')); f++);
  return regstr_sub_extract (cur->str, cur->index, f - 1);
}

regstr regstr_sub_extract (regstr str, int d, int f)
{
  /* amélioration future : code de DEBUG */
  int len = f - d + 1;
  regstr sub = (regstr) tools_malloc (sizeof (char) * (len + 1));
  int i;
  sub[len] = NULLCHAR;
  for (i = 0; i < len; i++)
    sub[i] = str[d + i];
  return sub;
}

regstr regstr_cursor_get_word_and_go_to_next (regstr_cursor cur)
{
  regstr str = NULL;
  int d = cur->index;
  int f;
  for (f = d; ((cur->str[f] != NULLCHAR) && (cur->str[f] != ' ')); f++);
  for (d = f; ((cur->str[d] != NULLCHAR) && (cur->str[d] == ' ')); d++);
  str =  regstr_sub_extract (cur->str, cur->index, f - 1);
  cur->index = d;
  return str;
}

/* set function 'element_clone' to NULL for "pointer copy" */
gll_array gll_array_clone (gll_array A, fun_clone element_clone)
{
  gll_array B = empty_gll_array_create (A->del, A->len, A->data_type);
  int i;
  for (i = 0; i < A->len; i++)
    B->data[i] = ((element_clone == NULL) ? A->data[i] : (*element_clone) (A->data[i]));

  return B;
}

void gll_array_zero (gll_array A)
{
  if (A->len == 0)
    return;
  
  if (A->del != NULL)
  {
    int i;
    
    for (i = 0; i < A->len; i++)
      (*(A->del)) (&(A->data[i]));
  }

  A->len = 0;
}

bool tools_is_inside_rect (tools_rect R, int x, int y)
{
  return ((x >= R->x1) && (x <= R->x2) && (y >= R->y1)
	  && (y <= R->y2));
}

bool tools_is_inside_rectf (tools_rectf R, float x, float y)
{
  return ((x >= R->x1) && (x <= R->x2) && (y >= R->y1) && (y <= R->y2));
}


tools_rect tools_rect_alloc (int x1, int y1)
{
  tools_rect R = (tools_rect) tools_malloc (sizeof (struct _tools_rect));
  R->x1 = x1;
  R->y1 = y1;
  return R;
}

tools_rectf tools_rectf_alloc (float x1, float y1)
{
  tools_rectf R = (tools_rectf) tools_malloc (sizeof (struct _tools_rectf));
  R->x1 = x1;
  R->y1 = y1;
  return R;
}

S_tools_rectf S_tools_rectf_create (float x1, float y1, float x2, float y2)
{
  S_tools_rectf R;
  R.x1 = x1; R.y1 = y1; R.x2 = x2; R.y2 = y2;
  return R;
}

tools_rectf tools_rectf_create (float x1, float y1, float x2, float y2)
{
  tools_rectf R = tools_rectf_alloc (x1, y1);
  R->x2 = x2; R->y2 = y2;
  return R;
}

tools_rect tools_rect_create (int x1, int y1, int x2, int y2)
{
  tools_rect R = tools_rect_alloc (x1, y1);
  R->x2 = x2; R->y2 = y2;
  return R;
}

tools_rectf tools_rectf_clone (tools_rectf R)
{
  return tools_rectf_create (R->x1, R->y1, R->x2, R->y2);
}

tools_rect tools_rect_clone (tools_rect R)
{
  return tools_rect_create (R->x1, R->y1, R->x2, R->y2);
}

tools_rectf tools_rectf_create_wh (float x1, float y1, float w, float h)
{
  tools_rectf R = tools_rectf_alloc (x1, y1);
  R->x2 = x1 + w - 1;
  R->y2 = y1 + h - 1;
  return R;
}

tools_rect tools_rect_create_wh (int x1, int y1, int w, int h)
{
  tools_rect R = tools_rect_alloc (x1, y1);
  R->x2 = x1 + w - 1;
  R->y2 = y1 + h - 1;
  return R;
}

void tools_rectf_destroy (tools_rectf* R)
{
  tools_free (*R, sizeof (struct _tools_rectf));
  *R = NULL;
}

void tools_rect_destroy (tools_rect* R)
{
  tools_free (*R, sizeof (struct _tools_rect));
  *R = NULL;
}

void tools_rectf_get_xxyy (tools_rectf R, float *x1, float *y1, float *x2, float *y2)
{
  *x1 = R->x1; *x2 = R->x2; *y1 = R->y1; *y2 = R->y2;
}

void tools_rect_get_xxyy (tools_rect R, int *x1, int *y1, int *x2, int *y2)
{
  *x1 = R->x1; *x2 = R->x2; *y1 = R->y1; *y2 = R->y2;
}

void tools_rect_get_xywh (tools_rect R, int *x1, int *y1, int *w, int *h)
{
  *x1 = R->x1; *y1 = R->y1;
  *h = R->y2 - *y1 + 1;
  *w = R->x2 - *x1 + 1;
}

void tools_rect_get_wh (tools_rect R, int *w, int *h)
{
  *h = R->y2 - R->y1 + 1;
  *w = R->x2 - R->x1 + 1;
}

void tools_rect_get_xxyywh (tools_rect R, int *x1, int *y1, int *x2, int *y2, int *w, int *h)
{
    *x1 = R->x1; *x2 = R->x2; *y1 = R->y1; *y2 = R->y2;
    *h = R->y2 - R->y1 + 1;
    *w = R->x2 - R->x1 + 1;
}

#ifdef DEBUG
bool is_regular_tools_rect (tools_rect R)
{
  return ((R->x1 <= R->x2) && (R->y1 <= R->y2));
}

bool is_regular_not_empty_tools_rect (tools_rect R)
{
  return ((R->x1 < R->x2) && (R->y1 < R->y2));
}
#endif


char* regstr_add_int_suffix (char* S, int n)
{
  char* N = int_to_regstr (n);
  char* R = regstr_concat (S, N);
  regular_regstr_destroy (&N);
  return R;
}

void D_regstr_add_int_suffix (char** S, int n)
{
  char* N = int_to_regstr (n);
  D_regstr_concat (S, N);
  regular_regstr_destroy (&N);
}

char* regstr_concat (char* S1, char* S2)
{
  int len1 = regstr_len (S1);
  int len2 = regstr_len (S2);
  char* S = (char*) tools_malloc (sizeof (char) * (len1 + len2 + 1));
  int i;

  S[len1 + len2] = ((char) 0);
  for (i = 0; i < len1; i++)
    S[i] = S1[i];
  for (i = 0; i < len2; i++)
    S[len1 + i] = S2[i];

  return S;
}

void D_regstr_concat (char** S, char* S2)
{
  char* newS = regstr_concat (*S, S2);
  regular_regstr_destroy (S);
  *S = newS;
}

void regstr_debug (char* S)
{
  int i = 0;
  while (S[i] != ((char) 0))
    {
      fprintf (stderr, "(char %d) = %c ;  ", i, S[i]); 
      i++;
    }
  fprintf (stderr, "\nstrlen = %d.\n", i);
}

void generic_regstr_debug (void* SS)
{
  char* S = (char*) SS;
  regstr_debug (S);
}

char* F_regstr_trim (regstr s)
{
  int d = 0;
  int f = regstr_len (s) - 1;
  while ((s[d] != ((char) 0)) && (s[d]==' '))
    d++;
  while ((f >= 0) && ((s[f] == ' ') || (s[f] == '\n') || (s[f] == ((char) 10))))
    f--;

  {
    int len = f - d + 1;
    char* tr = (char*) tools_malloc (sizeof (char) * (len + 1));
    int i;
    tr[len] = ((char) 0);
    for (i = 0; i < len; i++)
      tr[i] = s[d + i];
    return tr;
  }
}

char* byte_explode (byte b)
{
  char* bits = (char*) tools_malloc (sizeof (char) * 8);
  int i;
  for (i = 0; i < 8; i++)
    {
      bits[i] = (b & 1);
      b >>= 1;
    }
  return bits;
}

char* empty_regstr_create (void)
{
  char* S = (char*) tools_malloc (sizeof (char) * 1);
  S[0] = NULLCHAR;
  return S;
}

char* not_empty_regstr_read (void)
{
  char* S = regstr_standard_read ();
  while (S[0] == ((char) 0))
    {
      printf ("\nVous devez entrer au moins un caractere.\n");
      printf ("Re-essayez : ");
      S = regstr_standard_read ();
    }
  printf ("\n");
  return S;
}

void regular_regstr_destroy (char** S) /* warns if S == NULL */
{
#ifdef DEBUG
  if ((S == NULL) || (*S == NULL))
    {
      fprintf (stderr, "regular_regstr_destroy : null pointer.\n");
      return;
    }
#endif
  {
    int len = regstr_len (*S);
    tools_free (*S, sizeof (char) * (len + 1)); /* NULLCHAR at the end of regstr */
    (*S) = NULL;
  }
}

/*
  Destructeur à appeler quand on veut forcer la valeur de len 
  Ceci peut par exemple etre necessaire pour une chaîne se terminant par plusieurs
  octets nuls, si on souhaite éviter que le tools_free basé sur regstr_len
  ne compte mal les octets libérés.
*/
void regstr_destroy_of_size (char** S, int len)
{
#ifdef DEBUG
  if ((S == NULL) || (*S == NULL))
    {
      fprintf (stderr, "regular_regstr_destroy : null pointer.\n");
      return;
    }
#endif
  tools_free (*S, sizeof (char) * (len + 1)); /* len + 1 à cause du (dernier) NULLCHAR */
  (*S) = NULL;
  
}

void regstr_destroy_raw (char** pstr)
{
  char * str = *pstr;
tools_free (str, sizeof (char) * (regstr_len (str) + 1));
 (*pstr)= NULL;
}

void regstr_destroy (data *_S)
{
  char* S = ((char*) (*_S));
  tools_free (S, sizeof (char) * (regstr_len (S) + 1));
  (*_S) = NULL;
}

data generic_regstr_clone (data S)
{
  return ((data) (regstr_clone ((char*) S)));;
}

void generic_regstr_destroy (data *_S)
{
  char** S = (char**) _S;
  regular_regstr_destroy (S);
  *_S = NULL;
}

bool is_empty_regstr (char* S)
{
  return ((S != NULL) && (S[0] == NULLCHAR)); 
}

char input_yes_or_no (void)
{
  char* answer = regstr_standard_read ();
  char c;
  while ((answer[0] == ((char) 0)) || ((answer[1] != ((char) 0)) ||
				       ((answer[0] != 'o') && (answer[0] != 'n'))))
    {
      printf ("\nVous devez choisir entre o et n : ");
      tools_free (answer, sizeof (char) * (1 + regstr_len (answer)));
      answer = regstr_standard_read ();
    }
  c = answer[0];
  tools_free (answer, sizeof (char) * (1 + regstr_len (answer)));
  return c;
}

void generic_regstr_print (data S)
{
  printf ((char*) S);
}

void generic_regstr_print_to_stderr (data S)
{
  fprintf (stderr, (char*) S);
}

int generic_regstr_compare (data A, data B)
{
  char* C = (char*) A;
  char* D = (char*) B;
  return regstr_compare (C, D);
}

int tool_random_int (int vmin, int vmax)
{
  int amp = vmax - vmin + 1;
  double _alea = (1.0 * rand () / INT_MAX) * amp;
  int alea = (int) (vmin + _alea);
  int_normalize (&alea, vmin, vmax);
  return alea;
}

double tool_random_double (double vmin, double vmax)
{
  double amp = vmax - vmin;
  double alea = (1.0 * rand () / INT_MAX) * amp;
  return vmin + alea;
}

float tool_random_float (float vmin, float vmax)
{
  float amp = vmax - vmin;
  float alea = (1.0 * rand () / INT_MAX) * amp;
  return vmin + alea;
}

void int_normalize_and_warn (int *_i, int vmin, int vmax)
{
  int i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      int tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "int_normalize_and_warn : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : integer %d 'normalized' to %d\n", i, vmin);
#endif
      (*_i) = vmin;
    }
  else if (i > vmax)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : integer %d 'normalized' to %d\n", i, vmax);
#endif
      (*_i) = vmax;
    }
}

void double_normalize_and_warn (double *_i, double vmin, double vmax)
{
  double i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      double tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "double_normalize_and_warn : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : double %f 'normalized' to %f\n", i, vmin);
#endif
      (*_i) = vmin;
    }
  else if (i > vmax)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : double %f 'normalized' to %f\n", i, vmax);
#endif
      (*_i) = vmax;
    }
}

void float_normalize_and_warn (float *_i, float vmin, float vmax)
{
  float i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      float tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "float_normalize_and_warn : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : float %f 'normalized' to %f\n", i, vmin);
#endif
      (*_i) = vmin;
    }
  else if (i > vmax)
    {
#ifdef DEBUG
      fprintf (stderr, "WARNING : float %f 'normalized' to %f\n", i, vmax);
#endif
      (*_i) = vmax;
    }
}

void int_normalize_oob (int *_i, int vmin, int vmax, bool* out)
{
  int i = (*_i);
  *out = FALSE;
#ifdef DEBUG
  if (vmin > vmax)
    {
      int tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "int_normalize : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    {
      (*_i) = vmin;
      *out = TRUE;
    }
  else if (i > vmax)
    {
      (*_i) = vmax;
      *out = TRUE;
    }
}

void int_normalize (int *_i, int vmin, int vmax)
{
  int i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      int tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "int_normalize : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    (*_i) = vmin;
  else if (i > vmax)
    (*_i) = vmax;
}

void float_normalize (float* _i, float vmin, float vmax)
{
  float i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      float tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "float_normalize : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    (*_i) = vmin;
  else if (i > vmax)
    (*_i) = vmax;
}

void double_normalize (double* _i, double vmin, double vmax)
{
  double i = (*_i);
#ifdef DEBUG
  if (vmin > vmax)
    {
      double tmp = vmin;
      vmin = vmax;
      vmax = tmp;
      fprintf (stderr, "float_normalize : vmin > vmax (anomaly). I swap vmin and vmax and I try to continue.\n");
    }
#endif
  if (i < vmin)
    (*_i) = vmin;
  else if (i > vmax)
    (*_i) = vmax;
}

int regstr_compare (char* S, char *T)
{
  int i = 0;
  while ((S[i] != ((char) 0)) && (T[i] != ((char) 0)) && (S[i] == T[i]))
    i++;

  if ((S[i] == ((char) 0)) && (T[i] == ((char) 0))) return 0;
  else if (S[i] == ((char) 0)) return -1;
  else if (T[i] == ((char) 0)) return +1;
  else if (S[i] < T[i]) return -1;
  else /* if (S[i] > T[i]) */ return +1;
}

char* regstr_clone (char* S)
{
#ifdef DEBUG
  if (S == NULL)
    {
      fprintf (stderr, "regstr_clone : null pointer. Use regstr_clone_even_when_null_instead.\n");
      return NULL;
    }
#endif
  {
    char* T;
    int i, len = 0;
    while(S[len] != NULLCHAR) len++;
    T = (char*) tools_malloc (sizeof (char) * (len + 1));
    for (i = 0; i < len; i++)
      T[i] = S[i];
    T[len] = NULLCHAR;
    return T;
  }
}

char* regstr_clone_with_len (char* S, int len)
{
  char* T = (char*) tools_malloc (sizeof (char) * (len + 1));
  int i;
    for (i = 0; i < len; i++)
      T[i] = S[i];
    T[len] = NULLCHAR;
    return T;
}

char* regstr_clone_even_when_null (char* S)
{
  if (S == NULL)
    return NULL;
  else
    return regstr_clone (S);
}

void tools_error (char *msg)
{
  fprintf (stderr, msg);
  fprintf (stderr, "\n");
}


void UNSAFE_buffer_copy (char* src, char* dst, int len)
{
  int i;
  for (i = 0; i < len; i++)
    {
      (*dst) = (*src);
      src++;
      dst++;
    }
}


integ4 bytes_to_integ4 (byte a, byte b, byte c, byte d)
{
  integ4 n = (a << 24) | (b << 16) | (c << 8) | d;
  return n;
}


void integ4_to_4bytes (integ4 n, byte *a, byte *b, byte *c, byte *d)
{
  (*d) = n & 255;
  (*c) = (n >> 8) & 255;
  (*b) = (n >> 16) & 255;
  (*a) = (n >> 24);
}

void char_swap (char *m, char *n)
{
  char tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

void int_swap (int *m, int *n)
{
  int tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

void double_swap (double *m, double *n)
{
  double tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

void ptr_swap(void **p1, void **p2 )
{
  void *tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
  tmp = NULL;
  
}

bool string_is_int_value (char* ch)
{
  if ((ch[0] == ((char) 0)) || ((ch[0] != '-') && ((ch[0] < '0') || (ch[0] > '9')))) 
    return FALSE;

  {
    int i = 1;
    while (ch[i] != ((char) 0))
      {
	if ((ch[i] < '0') || (ch[i] > '9'))
	  return FALSE;
	i++;
      }
  }
  return TRUE;
}

int string_to_int (char* ch)
{
#ifdef DEBUG
  if (!string_is_int_value (ch))
    {
      fprintf (stderr, "string_to_int : string is not an int value. Return 0.\n");
      return 0;
    }
#endif
  {
    if (ch[0] == '-')
      {
	/* ch + 1 est l'adresse du deuxième char de la chaîne */
	/* donc le début de la valeur absolue.*/
	int vabs = string_to_int (ch + 1);
	return -vabs;
      }
    else
      {
	int r = 0;
	int i;
	for (i = 0; ch[i] != 0; i++)
	  {
	    r *= 10;
	    r += (((int) ch[i]) - 48);
	  }
	return r;
      }
  }
}

void scanf_posfloat (float *n)
{
  scanf ("%f", n);
  while ((*n) <= 0.0)
    {
      printf ("Entrez un nombre strictement positif.\n");
      scanf ("%f", n);
    }
}


void scanf_posint (int *n)
{
  (*n) = int_standard_read ();
  while ((*n) <= 0.0)
    {
      printf ("Entrez un nombre strictement positif.\n");
      (*n) = int_standard_read ();
    }
}

void scanf_ABint (char *msg, int *n, int a, int b)
{
  printf (msg);
  (*n) = int_standard_read ();
  while ((*n < a) || (*n > b))
    {
      fprintf (stderr, "\nentrez un entier entre %d et %d : ", a, b);
      (*n) = int_standard_read ();
    }
  printf ("\n");
}

/* Code importé de mon logiciel de traitement d'image */

void tool_send_warning (char* w)
{
  switch (_WARNING_LEVEL_)
    {	
    case 2:
      tool_send_error (w);
    case 1:
      fprintf (stderr, "WARNING: %s.\n", w);
    }
}

void tool_send_error (char* e)
{
  fprintf (stderr, "ERROR : %s!\n", e);
  exit (EXIT_FAILURE);
}


int tools_pseudolog_bin (double n)
{
  double p = 1.0;
  int log = 0;

  do
    {
      if (n == p)
	return log;
      p *= 2;
      log++;
    }
  while ((p >= 0) && (p < n));

  return -1;
}

void doublestar_cpy (double *dst, double *src, int dsti, int srci, int len)
{
  int i;
  for (i = 0; i < len; i++)
    dst[i + dsti] = src[i + srci];
}

/* fin du code importé du logiciel de traitement d'image */


void tools_memory_init (void)
{
  GLOBAL_MEMORY.allocated_memory = 0;
  GLOBAL_MEMORY.nb_alloc = 0;
  GLOBAL_MEMORY.max_memory = 0;

  /* memory shrink section */
  GLOBAL_MEMORY.memory_shrinker = NULL;
  GLOBAL_MEMORY.global_data_for_memory_shrinker = NULL;
  GLOBAL_MEMORY.verbose_when_call_memory_shrinker = FALSE;
  GLOBAL_MEMORY.max_alloc = 0;
}

void tools_memory_init_with_memory_shrinker (fun_memory_shrink shrinker,
					     void* global_data,
					     bool verbose)
{
  GLOBAL_MEMORY.allocated_memory = 0;
  GLOBAL_MEMORY.nb_alloc = 0;
  GLOBAL_MEMORY.max_memory = 0;

  /* memory shrink section */
  GLOBAL_MEMORY.memory_shrinker = shrinker;
  GLOBAL_MEMORY.global_data_for_memory_shrinker = global_data;
  GLOBAL_MEMORY.verbose_when_call_memory_shrinker = verbose;
  GLOBAL_MEMORY.max_alloc = 0;
}

void tools_warn (char* msg)
{
  fprintf (stderr, msg);
  fprintf (stderr, ".\n");
}

void tools_memory_shrink (void)
{
  if (GLOBAL_MEMORY.memory_shrinker == NULL)
    return;

  if ((GLOBAL_MEMORY.max_alloc != 0) && (GLOBAL_MEMORY.allocated_memory > GLOBAL_MEMORY.max_alloc))
    (*(GLOBAL_MEMORY.memory_shrinker)) (GLOBAL_MEMORY.global_data_for_memory_shrinker, GLOBAL_MEMORY.verbose_when_call_memory_shrinker);
}

void* tools_malloc (size_t len)
{
  void* mem;
  bool am_i_waiting = FALSE;
#ifndef DEBUG
  if (len < 1)
    {
      fprintf (stderr, "tools_malloc : memsize < 1. Assume memsize = 1");
      len = 1;
    }
#endif
	 
  do
    {
      mem = malloc (len);
      if ((!am_i_waiting) && (mem == NULL))
	{
	  fprintf (stderr, "L'application attend de pouvoir allouer ");
	  fprintf (stderr, "%ld octets de memoire...\n", (long) len);
	  fprintf (stderr, "ceci elevera l'allocation totale a %ld octets.\n", (long) (GLOBAL_MEMORY.allocated_memory + len));
	  fprintf (stderr, "Si la situation reste bloquee trop longtemps, ");
	  fprintf (stderr, "essayez de fermer une autre application pour ");
	  fprintf (stderr, "liberer de la memoire.\n");
	  am_i_waiting = TRUE;
	} 
    }
  while (mem == NULL);

  GLOBAL_MEMORY.allocated_memory += len;
  if (am_i_waiting)
    fprintf (stderr, "L'allocation de %ld octets s'est bien passee.\n", (long) len);

  GLOBAL_MEMORY.nb_alloc++;

  if (GLOBAL_MEMORY.allocated_memory > GLOBAL_MEMORY.max_memory)
    GLOBAL_MEMORY.max_memory = GLOBAL_MEMORY.allocated_memory;
  
  return mem;
}

void tools_memory_verbose (void)
{
  fprintf (stderr, "\nNB OF MALLOC CALLS : %d\n", GLOBAL_MEMORY.nb_alloc);
  fprintf (stderr, "MAX ALLOCATED MEMORY : %d bytes\n\n", GLOBAL_MEMORY.max_memory);
}

void tools_free (void* mem, size_t len)
{
#ifdef DEBUG
  if (mem == NULL)
    {
      tools_warn ("tools_free : mem is a null pointer");
      return;
    }
#endif
  GLOBAL_MEMORY.allocated_memory -= len;
  free (mem);
}

void tools_memory_debug (void)
{
#ifdef DEBUG
  fprintf (stderr, "%d bytes allocated.\n", GLOBAL_MEMORY.allocated_memory);
#endif
}

void tools_memory_check_at_end_of_app (void)
{
  if (GLOBAL_MEMORY.allocated_memory > 0)
    fprintf (stderr, "This application has memory leaks.\n%d bytes have not been freed.\n", GLOBAL_MEMORY.allocated_memory);
  else if (GLOBAL_MEMORY.allocated_memory < 0)
    fprintf (stderr, "This application has freed too much memory !!!\n%d bytes have not been freed.\n", GLOBAL_MEMORY.allocated_memory);
}

gll_array empty_gll_array_create (destructor F, int alloc, int data_type)
{
  gll_array A = (gll_array) tools_malloc (sizeof (struct _gll_array));
  int i;
  A->len = 0; A->alloc = alloc; A->del = F; A->data_type = data_type;
  A->data = (void**) tools_malloc (sizeof (void*) * alloc);
  for (i = 0; i < alloc; i++)
    A->data[i] = NULL;
  return A;
}

void gll_array_generic_destructor (void** AA)
{
  gll_array* A = (gll_array*) AA;
  gll_array_destroy (A);
  *AA = NULL;
}

void gll_array_destroy (gll_array* _A)
{
  if (_A == NULL)
    {
#ifdef DEBUG
      tools_warn ("gll_array_destroy : _A is a null pointer (1)");
#endif
      return;
    }

  {
    gll_array A = (*_A);
    if (A == NULL)
      {
#ifdef DEBUG
	tools_warn ("gll_array_destroy : A is a null pointer (2)");
#endif
	return;
      }

    if (A->data == NULL)
      {
#ifdef DEBUG
	tools_warn ("gll_array_destroy : A->data is a null pointer (3)");
#endif
      }
    else
      {
	if (A->del != NULL)
	  {
	    int i;
	    for (i = 0; i < A->len; i++)
	      {
		void* value = A->data[i];
		if (value != NULL)
		  (*A->del) (&value);
	      }
	  }
	tools_free (A->data, A->alloc * sizeof (void*));
      }
    
    tools_free (A, sizeof (struct _gll_array));
    
    (*_A) = NULL;
  }
}

void* gll_array_get (gll_array A, int i)
{
  if (A == NULL)
    {
#ifdef DEBUG
      tools_warn ("gll_array_get : A is a null pointer");
#endif
      return NULL;
    }

  if ((i < 0) || (i >= A->len))
    {
#ifdef DEBUG
      fprintf (stderr, "gll_array_get : Index %d out of bounds.\n", i);
#endif
      return NULL;
    }

  return A->data[i];
}

/* private */
void gll_array_realloc (gll_array A, int newalloc)
{
  if (A == NULL)
    {
#ifdef DEBUG
      tools_warn ("(private) gll_array_realloc : A is a null pointer");
#endif
      return;
    }

  {
    void** newdata = (void**) tools_malloc (sizeof (void*) * newalloc);
    int i; int last = ((A->len <= newalloc) ? A->len : newalloc) - 1;
    for (i = 0; i <= last; i++)
      newdata[i] = A->data[i]; /* copie de la zone à garder */
    if (A->del != NULL) /* suppression de ce qui est au-delà de la zone à garder */
      {
	for (i = last + 1; i < A->alloc; i++)
	  {
	    if ((A->del != NULL) && (A->data[i] != NULL))
	      (*(A->del)) (A->data[i]);
	  }
      }
    tools_free (A->data, sizeof (void*) * A->alloc);
    for (i = last + 1; i < newalloc; i++) /* NULL dans la zone réallouée partout après... */
      newdata[i] = NULL; /* ...le dernier élément recopié */
    A->data = newdata;
    A->alloc = newalloc;
    if (A->len > A->alloc)
      A->len = A->alloc;
  }
}

void gll_array_shrink (gll_array A)
{
  if (A->len > 0)
    gll_array_realloc (A, A->len);
  else
    gll_array_realloc (A, 1);
}

void gll_array_set (gll_array A, int i, void* d)
{
  if (A == NULL)
    {
#ifdef DEBUG
      tools_warn ("gll_array_set : A is a null pointer");
#endif
      return;
    }
  
  if (i < 0)
    {
#ifdef DEBUG
      tools_warn ("gll_array_set : negative index in an ext. array");
#endif
      return;
    }

  if (i >= A->alloc)
    gll_array_realloc (A, i * 2);
  
  if (i >= A->len)
    A->len = i + 1;

  if ((A->del != NULL) && (A->data[i] != NULL))
    (*(A->del)) (&(A->data[i]));

  A->data[i] = d;  
}

void gll_array_add (gll_array A, void* d)
{
  gll_array_set (A, A->len, d);
}

#ifdef DEBUG
void gll_array_check_data_type (gll_array A, int data_type)
{
  bool ignored = gll_array_check_data_type_v2 (A, data_type);
  if ((ignored != TRUE) && (ignored != FALSE))
    ignored = FALSE; /* 'no compiler warning' bidouille */
}
#endif

#ifdef DEBUG
bool gll_array_check_data_type_v2 (gll_array A, int data_type)
{
  if (A == NULL)
    {
#ifdef DEBUG
      fprintf (stderr, "FUNCTION gll_array_check_data_type : \n");
      fprintf (stderr, "Warning : gll_array is a NULL pointer. \n");
#endif
      return FALSE;
    }
  if (A->data_type != data_type)
    {
      tools_warn ("gll_array_check_data_type : incorrect data_type in a generic array");
      return FALSE;
    }
  else
    return TRUE;
}
#endif


/* pointer based comparison */
bool is_in_gll_array (gll_array A, void* d)
{
  int i;
  for (i = 0; i < A->len; i++)
    {
      void* dd = A->data[i];
      if (d == dd)
	return TRUE;
    }
  return FALSE;
}

/* pointer based comparison */
void gll_array_find (gll_array A, void* d, bool* _found, int* _index)
{
  bool found = FALSE;
  int index = 0;

  while ((index < A->len) && (!found))
    {
      if (A->data[index] == d)
	found = TRUE;
      else
	index++;
    }

  *_found = found;
  *_index = index;
}

/* fun_equal based comparison */
bool is_in_gll_array_equal (gll_array A, void* d, fun_equal equal)
{
  int i;
  for (i = 0; i < A->len; i++)
    {
      void* dd = A->data[i];
      if ((*(equal)) (d, dd))
	return TRUE;
    }
  return FALSE;
}

void UNSORTED_gll_array_remove (gll_array A, int i, bool must_destroy)
{
#ifdef DEBUG
  if ((i < 0) || (i >= A->len))
    {
      fprintf (stderr, "(unsorted) gll_array_remove : index %d out of bounds.\n", i);
      return;
    }
#endif

  {
    void* value = A->data[i];
    
    if (must_destroy && (A->del != NULL))
      {
	(*(A->del)) (&value);
	A->data[i] = NULL;
      }

    if (i < A->len - 1)
      A->data[i] = A->data[A->len - 1];
    
    (A->len)--;
  }
}

/* End of GLL_ARRAY section */

/* GLL_INDEX SECTION */

gll_index gll_index_create (int offset_first, int offset_last)
{
  gll_index ind = (gll_index) tools_malloc (sizeof (struct _gll_index));
  ind->offset_first = offset_first;
  ind->offset_last = offset_last;
  return ind;
}

gll_index gll_index_create_len (int offset_first, int len)
{
  int last = offset_first + len - 1;
  return gll_index_create (offset_first, last);
}

void gll_index_destroy (gll_index* _ind)
{
  gll_index ind = *_ind;
  tools_free (ind, sizeof (struct _gll_index));
  *_ind = NULL;
}

void generic_gll_index_destroy (void** _ind)
{
  gll_index* ind = (gll_index*) _ind;
  gll_index_destroy (ind);
  *_ind = NULL;
}

void* generic_gll_index_clone (void* _ind)
{
  gll_index ind = (gll_index) _ind;
  return ((void*) gll_index_clone (ind));
}

gll_index gll_index_clone (gll_index ind)
{
  return gll_index_create (ind->offset_first, ind->offset_last);
}

void generic_gll_index_print (void* _ind)
{
  gll_index ind = (gll_index) _ind;
  gll_index_debug (ind);
}

int generic_gll_index_compare (void* _ind1, void* _ind2) 
{
  gll_index ind1 = (gll_index) _ind1;
  gll_index ind2 = (gll_index) _ind2;
  return gll_index_compare (ind1, ind2);
}

int gll_index_compare (gll_index ind1, gll_index ind2)
{
  if (ind1->offset_first < ind2->offset_first)
    return -1;
  else if (ind1->offset_first > ind2->offset_first)
    return 1;
  else if (ind1->offset_last < ind2->offset_last)
    return -1;
  else if (ind1->offset_last > ind2->offset_last)
    return 1;
  else
    return 0;
}

void gll_index_debug (gll_index ind)
{
  fprintf (stderr, "index(%d;%d;%d) ", ind->offset_first, ind->offset_last, gll_index_length (ind));
}

void gll_index_get (gll_index ind, int* offset_first, int *offset_last, int *len)
{
  *offset_first = ind->offset_first;
  *offset_last = ind->offset_last;
  *len = gll_index_length (ind);
}

int gll_index_length (gll_index ind)
{
  return ind->offset_last - ind->offset_first + 1;
}

#ifdef DEBUG
bool is_regular_gll_index (gll_index ind)
{
  return ((ind->offset_first >= 0) && (ind->offset_last >= ind->offset_first));
}
#endif

void tools_bialloc (void** ptr1, size_t size1, void** ptr2, size_t size2)
{
  size_t size = size1 + size2;
  *ptr1 = tools_malloc (size);
  *ptr2 = (void*) ((char*) (*ptr1) + size1);
}

void tools_bifree (void* ptr1, void* ptr2, size_t size)
{
  if (ptr2 != NULL) ptr2 = NULL; /* no warning */
  tools_free (ptr1, size);
}

/* pas 'constructor' car pas de pointeur */
complex make_complex (double a, double b)
{
  complex Z; /* complex Z = malloc (sizeof (struct _complex)); */
  Z.a = a;   /* Z->a = a; */
  Z.b = b;   /* Z->b = b; */
  return Z;  /* return Z; */
}

/* Z1 += Z2; */
void D_complex_plus (complex* Z1, complex Z2)
{
  Z1->a += Z2.a;
  Z1->b += Z2.b;
}

/* Z *= Z */
void D_complex_square (complex* Z)
{
  double a = Z->a * Z->a - Z->b * Z->b;
  double b = 2 * Z->a * Z->b;
  Z->a = a;
  Z->b = b;
}

double complex_mod (complex Z)
{
  return sqrtf (Z.a * Z.a + Z.b * Z.b);
}

float tools_rect_to_pol (float x, float y, float* r)
{
  float radius = sqrtf (x * x + y * y);
  *r = radius;
  if (radius == 0.0)
    return 0.0;
  else
    {
      float cocos = x / radius;
      float sisin = y / radius;
  
      if ((cocos >= 0.0) && (sisin >= 0.0))
	return asin (sisin);
  
      if ((cocos >= 0.0) && (sisin < 0.0))
	return asin (sisin); 

      if ((cocos < 0.0) && (sisin >= 0.0))
	return acos (cocos);

      if ((cocos < 0.0) && (sisin < 0.0))
	return -acos (cocos);
  
#ifdef DEBUG
      fprintf (stderr, "FUNCTION tools_rect_to_pol : unknown case.\n");
#endif
      return 0.0;
    }
}

void tools_rectf_clip (tools_rectf R, float minx, float miny, float maxx, float maxy)
{
  /* 
     éventuellement ajouter code de debug pour les cas où x1 > x2, etc 
   */
  if (R->x1 < minx) R->x1 = minx;
  if (R->x2 > maxx) R->x2 = maxx;
  if (R->y1 < miny) R->y1 = miny;
  if (R->y2 > maxy) R->y2 = maxy;
} 

void fast_array_2D_resize (fast_array A, int neww, int newh,
			   fun_init init, fun_move move, destructor des)
{
  if (!(A->resizable))
    {
#ifdef DEBUG
      fprintf (stderr, "fast_array_2D_resize : array is not resizable.\n");
#endif
      return;
    }

  {
    int actualw = A->w;
    int actualh = A->alloc / A->w;
    pointer newdata, ptr, target;
    int i, x, y;
  
    newdata = tools_malloc (neww * newh * A->elem_size);
    ptr = newdata;
    for (i = 0; i < neww * newh; i++)
      {
	(*init) (ptr, NULL);
	ptr += A->elem_size;
      }

    for (y = 0; y < actualw; y++)
      {
	ptr = A->data + y * actualw * A->elem_size;
	target = newdata + y * neww * A->elem_size;
	for (x = 0; x < actualh; x++)
	  {
	    (*move) (ptr, target, des);
	    ptr += A->elem_size;
	    target += A->elem_size;
	  }
      }
  
    tools_free (A->data, actualw * actualh * A->elem_size);
    A->data = newdata;
    A->w = neww;
    A->len = neww * newh;
    A->alloc = neww * newh;
  }
}





// added by Harlock cour 60
void regstr_destroy_len(char ** sstr, int len)
{
  char* str = *sstr;
  tools_free(str, sizeof(char) * (len+1));
  *sstr = NULL;
}

bool regstr_equal (char* str1, char* str2)
{
 
  int i = 0;
  while ((str1[i] != '\0') && (str2[i] != '\0'))
    {
   
      if (str1[i] != str2[i])
	{
	  return FALSE;

	}
      i++;
    }
  return (str1[i] == str2[i]);
}

void my_sleep(int n)
{
  time_t T = time(NULL);
  time_t TT = T;
  while( TT -T < n)
    TT = time(NULL);
}

void endian_check(void)
{
   int x = 1;

  char *y = (char*)&x;

  printf("%c\n",*y+48);
  fprintf(stdout, "if little endian 1 if big endian 0");

}

//heap sort harlock

