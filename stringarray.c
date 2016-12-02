#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "stringarray.h"

typedef char chardata;
typedef char* regstr;
// module a verifier !

int stringarray_equal(stringarray j1, stringarray j2)
{
  int i,lgth = j1->len;
  int equal = 0;
  
   if( j1->len == j2->len)
    {
      for (i = 0; i < lgth; i++)
	{
	
	  if (jstr_equal(j1->data[i], j2->data[i]) == 1)
	    {
	      equal++;
	    }
	}
  
      if(equal == (lgth))
	{
      	  return 1;
	}
      else
	{
	  return 0;
	}
    }

  else
    return 0;
}



void stringarray_print (stringarray T, char * c)
{
  int i;
  for (i = 0; i< T->len; i++)
    {
      jstr_print(T->data[i]);
      printf("%s", c);
    }
}
	   

void stringarray_debug_bound (stringarray T,char * bound)
{
  int i;
  printf("stringarray, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      jstr_debug(T->data[i]);
      printf(bound);
    }
}

void stringarray_debug (stringarray T)
{
  int i;
  printf("stringarray, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      jstr_debug(T->data[i]);
      printf(bound);
    }
}
stringarray stringarray_create(int len)
{
  return ext_stringarray_create(len, len);
}

stringarray ext_stringarray_create (int len, int alloc)
{
  assert ((len >= 0) && (alloc > 0) && (len <= alloc));
  {
  stringarray A = malloc (sizeof (struct _stringarray));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc (sizeof (jstr) * alloc);
  {
    int i;
    for (i = 0; i < alloc; i++)
      {
	A->data[i] = NULL;
      }
  }
  return A;
  }
}

stringarray empty_stringarray_create(int alloc)
{
  return ext_stringarray_create(0 , alloc);
}

void stringarray_create_aux (stringarray tab)
{
  int i;
  if (tab->alloc <= 0)
    {
      tab->alloc = 4;
      printf("stringarray_create_aux : taille alloué <= 0.\n");
      printf("nous allouons %d à la place.\n", tab->alloc);
    }
  tab->data = malloc * sizeof (jdtr));
for (i = 0; i < tab->alloc; i++)
  tab->data[i] = NULL;

  
}


void stringarray_alloc_more(stringarray T , int new_alloc)
{
  jstr * tmp = malloc (sizeof (jstr) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
    tmp[i] = T->data[i];
    }
  for( i =T->len; i < new_alloc; i++)
    {
      tmp[i] = NULL;
    }
    
      free (T->data);
      T->data = tmp;
      T->alloc = new_alloc;
}		    

stringarray standard_empty_stringarray_create (void)
{
  return ext_stringarray_create ( 0, STRINGARRAY_DEFAULT_ALLOC);
}

void stringarray_destroy (stringarray T)
{
  free (T->data);
  free (T);
}

void stringarray_and_jstr_destroy (stringarray T)
{
  int i;
  for (i = 0; i < T->len; i++)
    {
      jstr_destroy (T->data[i]);
    }
  free (T->data);
  free (T);
}


jstr stringarray_get (stringarray T , int i)
{
  if (( i < 0 ) || (index >= tab->len))
    {
      printf("stringarray_get : l'index %d est invalide.\n",index);
      printf("les valeurs valides sont entre 0 et %d.\n", tab->len -1);
      return NULL;
    }
    
  return T->data[i];
 }

void stringarray_set ( stringarray T, int i, jstr j)
{

  if (( i < 0 ) || (index >= tab->len))
    {
      printf("stringarray_set : l'index %d est invalide.\n",index);
      printf("les valeurs valides sont entre 0 et %d.\n", tab->len -1);
      return;
    }
  if (T->data[i] != NULL)
    {
      jstr_destroy ( T->data[i]);
    } 
  T->data[i] = j;
}

void ext_stringarray_set ( stringarray T, int i, jstr n)
{
  if (i >= T->alloc)
    stringarray_alloc_more (T,i *2);
  if (i >= T->len)
    T->len = i+1;
  stringarray_set(T, i, n);
}



int stringarray_length (stringarray T)
{
  return T->len;
}

void stringarray_add(stringarray T, jstr j)
{
  ext_stringarray_set(T, T->len , j);    
}

void stringarray_delete(stringarray T, int loc)/*modifie l'ordre du tableau*/
{
  int i;
  if ((loc < 0) || ( loc >= T->len))
    {
      printf ("stringarray_delete : index invalide %d.\n", loc);
      return;
    }
  jstr_destroy (T->data[loc]);

  for (i = loc + 1; i < T->len; i++)
        T->data[i - 1] = T->data[i];
  
  T->len--;
} 
 
stringarray stringarray_concat(stringarray T1,stringarray T2)
{
  return stringarray_concat_aux (T1, T2, 0);
}

stringarray stringarray_concat_jstr_clone (stringarray T1, stringarray T2)
{
  return stringarray_concat_aux (T1, T2, 1);
}

stringarray stringarray_concat_aux(stringarray T1, stringarray T2, int clone)
{
  stringarray T = stringarray_create (stringarray_length (T1) + stringarray_length (T2));
  int i,j;
  j = stringarray_length(T1);
  for(i=0 ; i < stringarray_length (T1); i++)
    {
      if (clone)
	T->data[i] = jstr_clone (T1->data[i]);
      else
      stringarray_set (T, i, stringarray_get (T1 ,i));
    }
  for(i=0; i < stringarray_length (T2); i++)
    {
      if (clone)
	T->data[j+i] = jstr_clone (T2->data[i]);
      else
      stringarray_set (T , (j+i) , stringarray_get (T2, i));
    }
  return T;
}


void D_stringarray_concat(stringarray T1 , stringarray T2)
{
  int n;
  for (n = 0; n < (stringarray_length( T2 )); n++)
    {
      stringarray_add(T1 , T2->data[n]);
    }		   
 }

stringarray stringarray_clone_aux (stringarray T, int clone)
{
  stringarray U = stringarray_create (T->len);
  int i;
  for (i = 0 ; i < T->len ; i++)
    {
      if (clone)
	U->data[i] = jstr_clone(T->data[i]);
      else
      U->data[i] = T->data[i];
    }
  return U;
}

stringarray stringarray_clone_jstsr (stringarray T)
{
  stringarray_clone_aux (stringarray T, 1);
}
stringarray stringarray_clone (stringarray T)
{
  stringarray_clone_aux (stringarray T, 0);
}
 
void stringarray_sort1 (stringarray T)
{
int i, l, n, c = 0, k;
if (T->len > 1);
{
  

  intarray C = intarray_create(T->len);
  intarray sorted =intarray_create(T->len);
  
  stringarray tmp = stringarray_create(T->len);
  
  for(i = 0; i < T->len; i++)
      {
        c = 0;
        for(n = 0; n < T->len; n++)
	       {
	          c += jstr_compare(T->data[i], T->data[n]);
	        }
        C->data[i] = c;
    }
  sorted = intarray_index_sorted(C);
    
  for (k = 0; k < T->len; k++)
    {
      stringarray_set(tmp, k , T->data[sorted->data[k]]);
    }

  for (l = 0; l< T->len; l++)
	{	
	stringarray_set(T, l,tmp->data[l]);
	}
stringarray_destroy(tmp);  
intarray_destroy(C);
  intarray_destroy(sorted);
 }
}

void stringarray_sort_jol (stringarray T)
{
  int i, index_min;
  for (i = 0; i <= stringarray_length (T) - 2; i++)
    {
      index_min = stringarray_get_min_index (T, i);
      {
	jstr tmp = T->data[i];
	T->data[i] = T->data[index_min];
	T->data[index_min] = tmp;
      }
    }
}


void stringarray_resize (stringarray tab, int newalloc)
{
  jstr* newdata = malloc (sizeof (jstr) * newalloc);
  int i;
  for (i = 0; i < tab->len; i++)
    newdata[i] = tab->data[i];

  free (tab->data);

  tab->data = newdata;
  tab->alloc = newalloc;
}

void ext_stringarray_set (stringarray tab, int index, jstr value)
{
  int i;

  if (index < 0)
    {
      printf ("ext_stringarray_set : impossible d'écrire en case %d.\n", index);
      return;
    }
  if (index < tab->len)
    {
      tab->data[index] = value;
      return;
    }
  if (index >= tab->alloc)
    stringarray_resize (tab, 1 + 2 * index);

  for (i = tab->len; i < index; i++)
    tab->data[i] = empty_jstr_create(1);

  tab->data[index] = value;

  if (index >= tab->len)
    tab->len = index + 1;
}


void UNSORTED_stringarray_delete (stringarray tab, int index)
{
  if ((index < 0) || (index >= tab->len))
    {
      printf ("stringarray_delete : index invalide %d.\n", index);
      return;
    }
  jstr_destroy (tab->data[index]);
  tab->data[index] = tab->data[tab->len -1];
  tab->len--;
}





jstr stringarray_get_max (stringarray tab)
{
  int index_maxi = stringarray_get_index_of_max (tab);
  return tab->data[index_maxi];
}

int stringarray_get_index_of_max (stringarray tab)
{
  return stringarray_get_index_of_max_from (tab, 0);
}

int stringarray_get_index_of_max_from (stringarray tab, int index)
{
  if ((index < 0) || (index >= tab->len))
    {
      printf("stringarray_get_index_of_max_from : l'index %d est invalide.\n", index);
      printf("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
      return 0;
    }
  jstr maxi = tab->data[index];
  int index_maxi = index;
  int i;
  for (i = index + 1; i < tab->len; i++)
    {
      if (jstr_compare (tab->data[i], maxi) == 1)
	{
	  maxi = tab->data[i];
	  index_maxi = i;
	}
    }
  return index_maxi;
}

jstr stringarray_get_min ( stringarray tab)
{
  int index_mini = stringarray_get_index_of_min (tab);
  return tab->data[index_mini];
}

int stringarray_get_index_of_min (stringarray tab)
{
  return stringarray_get_index_of_min_from (tab, 0);
}
			     
int stringarray_get_index_of_min_from (stringarray tab, int index)
{
if ((index < 0) || (index >= tab->len))
    {
      printf("stringarray_get_index_of_min_from : l'index %d est invalide.\n", index);
      printf("les valeurs valides sont entre 0 et %d.\n", tab->len - 1);
      return 0;
    }
  jstr mini = tab->data[index];
  int index_mini = index;
  int i;
  for (i = index + 1; i < tab->len; i++)
    {
      if (jstr_compare (tab->data[i], mini) == -1)
	{
	  mini = tab->data[i];
	  index_mini = i;
	}
    }
  return index_mini;
}

int stringarray_nb_occurences (stringarray tab, jstr n)
{
  int nb_occurences = 0;
  int i;
  for (i = 0; i < tab->len; i++)
    {
      if (jstr_equal(tab->data[i],n))
	nb_occurrences++;

    }
  return nb_occurences;
}

int stingarray_search (stringarray tab, jstr n)
{
  int i;
  for (i = 0; i< tab->len; i++)
    {
      if (jstr_equal(tab->data[i],n))
	return 1;
    }
  return 0;
}

void ext_stringarray_debug (stringarray tab)
{
  printf("Tab. alloc = %d ; len = %d\n",tab->alloc, tab->len);
  stringarray_debug(tab);
}

int stringarray_equal(stringarray j1, stringarray j2)
{
  if (j1->len != j2->len)
    return 0;

  {
    int i;
    for(i = 0; i < j1->len; i++)
      {
	if (!(jstr_equal (j1->data[i], j2->data[i])))
	  return 0;
      }
    return 1;
  }
}
	   
