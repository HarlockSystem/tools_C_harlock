#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "hunintarray.h"
#include "tools.h"

void hunintarray_alloc_more(hunintarray T , int new_alloc);

void hunintarray_print (hunintarray T)
{
  int i;
  for (i= 0; i< T->len; i++)
    {
      printf(" %u ", T->data[i]);
    }
	RC;
}

void hunintarray_debug (hunintarray T)
{
  int i;
  printf("hunintarray, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      printf (" %u ", T->data[i]);
    }
  RC;
}

/*hunintarray hunintarray_create (int len)
{
  hunintarray A = malloc (sizeof (struct _hunintarray));
  A->len = len;
  A->alloc = len;
  A->data = malloc (sizeof (int) * len);
  return A;
  }*/

hunintarray hunintarray_create(int len)
{
  /* hunintarray T = ext_hunintarray_create(len, len);
  return T;*/
  return ext_hunintarray_create(len, len);
}

hunintarray ext_hunintarray_create (int len, int alloc)
{
  assert ((len >=0) && (alloc > 0) && (len <=alloc));
  {
  hunintarray A = tools_malloc (sizeof (struct _hunintarray));
  A->len = len;
  A->alloc = alloc;
  A->data = tools_malloc (sizeof (unintdata) * alloc);
  return A;
  }
}

hunintarray empty_hunintarray_create(int alloc)
{
  return ext_hunintarray_create(0 , alloc);
}
/* hunintarray T = hunintarray_create (1000); */
/* hunintarray_set (T , x , y); */

void hunintarray_alloc_more(hunintarray T , int new_alloc)
{
  unsigned int * tmp = tools_malloc (sizeof (unintdata) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
    tmp[i] = T->data[i];
    }		       
  tools_free (T->data, sizeof (unsigned int) * T->alloc);
      T->data = tmp;
      T->alloc = new_alloc;
}		    

hunintarray standard_empty_hunintarray_create (void)
{
  return ext_hunintarray_create ( 0, HUNINTARRAY_DEFAULT_ALLOC);
}

void hunintarray_destroy (hunintarray T)
{
  tools_free (T->data, sizeof (unsigned int) * T->alloc );
  tools_free (T, sizeof (struct _unintarray);
}

unintdata hunintarray_get (hunintarray T , int i)
{
  assert (i >= 0);
  assert (i < T->len);
  return T->data[i];
 }

void hunintarray_set ( hunintarray T, int i, unintdata n)
{
  assert (i >=0 );
  assert (i < T->len);
  T->data[i] = n;
}

 void hunintarray_set_2D(hunitarray    )

void ext_hunintarray_set ( hunintarray T, int i, intdata n)
{
  if (i >= T->alloc)
    hunintarray_alloc_more (T,i *2);
  if (i >=T->len)
    T->len = i+1;
  hunintarray_set(T, i, n);
}



int hunintarray_length (hunintarray T)
{
  return T->len;
}

void hunintarray_add(hunintarray T, unintdata n)
{
  ext_hunintarray_set(T, T->len , n);    
}

void hunintarray_delete(hunintarray T, int loc)/*modifie l'ordre du tableau*/
{
  assert (T->len > 0);
  assert (loc < T->len);
  T->data[loc] = T->data[T->len-1];
  T->len--;
} 
 



unintdata hunintarray_get_min(hunintarray T)
{
  int n;
  intdata m;
  m = hunintarray_get (T,0);
  
  for(n = 1; n < hunintarray_length (T) ; n++)
      {
	intdata T_i = hunintarray_get (T , n);
	if (T_i<m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

hunintarray hunintarray_concat(hunintarray T1, hunintarray T2)
{
  hunintarray T = hunintarray_create (hunintarray_length (T1) + hunintarray_length (T2));
  int i,j;
  j = hunintarray_length(T1);
  for(i=0 ; i < hunintarray_length (T1); i++)
    {
      /*EXPL: T->data[i] = T1->data[i]; */
      /*EXPL: T->data[i] = hunintarray_get (T1 ;i);*/
      hunintarray_set (T, i, hunintarray_get (T1 ,i));
    }
  for(i=0; i < hunintarray_length (T2); i++)
    {
      hunintarray_set (T , (j+i) , hunintarray_get (T2, i));
    }
  return T;
}


void D_hunintarray_concat(hunintarray T1 , hunintarray T2)
{
 int n;
  for (n = 0; n < hunintarray_length(T2); n++)
    hunintarray_add(T1 , hunintarray_get(T2 ,n));
		   
 }		 



int hunintarray_seek_min_index (hunintarray T ,int start)
{
  int i, index_min;
  unintdata m = T->data[start];
  index_min = start;
    
  for (i = start +1 ; i < hunintarray_length (T) ; i++)
      {
	if  (T->data[i] <  m)
	  {
	  m = T->data[i];
	  index_min = i;
	  }
      }
  return index_min;
}

void hunintarray_sort1 (hunintarray T)/* tri par selection du minimum)*/
{
  int i;
  for(i = 0 ; i < hunintarray_length( T ) ; i++)
    {
      int_swap (T->data + i, T->data + hunintarray_seek_min_index(T , i));
    }
}
/*
void hunintarray_sort2 (hunintarray T)
{
int i, index_min;
for (i = 0; i <= hunintarray_length(T) - 2; i++)
{
index_min = hunintarray_seek_min_index (T , i);
int_swap (T->data + i , T->data + index_min);
}
}
*/


unintdata hunintarray_sum(hunintarray T)/* somme de tt les entiers*/
{
  int i;
  intdata sum = 0;
  for (i = 0; i < T->len ; i++)
    {
      sum += hunintarray_get(T, i);
    }
  return sum;
}



float hunintarray_average (hunintarray T)/* renvoi la moyenne*/
{
 
  float s = hunintarray_sum(T);
  return (s /T->len);
}


float hunintarray_median (hunintarray T)/* renvoi la mediane du tableau */ 
{
  hunintarray T2 = hunintarray_clone (T);
  hunintarray_sort1(T2);
  float med;
  if(T->len % 2 == 1)
    {
  int j = T->len / 2;
  med =hunintarray_get(T , j);
    }
  else
    {
      unsigned int i = T2->data[(T2,(T->len - 1) / 2)];
      unsigned int n = T2->data[(T2,(T->len + 1) / 2)];
      med = ((i + n) / 2.0);
    }
  hunintarray_destroy(T2);
  return med;
}

unintdata hunintarray_get_max (hunintarray T)/* cherche le chiffre le plus grand*/
{
  int n;
  unintdata m = hunintarray_get (T,0);
  
  for(n = 1; n < hunintarray_length (T) ; n++)
      {
	intdata T_i = hunintarray_get (T , n);
	if (T_i > m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

int hunintarray_num_occur(hunintarray T, unintdata n)
{
  int i;
  int o ;
  for(i=0 ; i<T->len ; i++)
    {
      if(T->data[i]==n)
	{
	  o += 1;
	}
    }  
    
  return o;
 }

hunintarray hunintarray_clone (hunintarray T)
{
  hunintarray U = hunintarray_create (T->len);
  int i;
  for (i = 0 ; i < T->len ; i++)
    {
      U->data[i] = T->data[i];
    }
  return U;
}


void hunintarray_arg(int a, char* c[]) 
{
  if(  a >= 2 )
  {
  int taille = a - 1;
  hunintarray T = empty_hunintarray_create(2);
  int i;
  for (i = 0 ; i < taille ; i++)
    {
      hunintarray_add(T, unchar_to_unint ( c[i + 1]));
    }
  {
    unintdata mn = hunintarray_get_min (T);
    unintdata mx = hunintarray_get_max (T);
    float ave = hunintarray_average (T);
    float med = hunintarray_median (T);
    printf("vous avez entré %d nombre(s).\n", taille);
    printf("Le plus petit est %u , le plus grand est %u .\n", mn , mx);
    printf("L'etendue est de %u\n" , mx - mn);
    printf("La moyenne arithmetique s'eleve a %f .\n",ave);
    printf("La mediane est egale a %f .\n",med);
    printf("Vous avez entre les valeurs suivantes :\n");
    hunintarray_debug (T); RC;
    printf("Soit , par ordre croissant :\n");
    hunintarray_sort1 (T);
    hunintarray_debug(T);
  }
  hunintarray_destroy(T);
 }
 }
 
 void scanf_pos_float (float *n)
{
	scanf("%f", n);
	while ((*n) <= 0.0)
	{
		printf("Entrez un nombre strictement positif->\n");
		scanf("%f",n);
	}
}

 void scanf_un_int (unsigned int *n)
{
  scanf("%u", n);
while ((*n) <= 0)
	{
		printf("Entrez un nombre strictement positif.\n");
		scanf("%u",n);
	}
  }

 unsigned int factorielle (unsigned int n)
{
  unsigned int a =1 ,i;
  assert ( (n >= 0)&&(n <= 13) );
  for(i= 1; i <= n; i++)
    {
      a *= i;
    }
  return a;
}
 
 
 int recherche_nombre(hunintarray T, unintdata n)
{
  int i;
  for(i=0;i<T->len;i++)
    {
      if(T->data[i]=n)
	{
	  printf("je retourne 1");
	  return 1;
	    }
    }
  return 0;
}

unsigned int unchar_to_unint(unsigned char * ch)/*ne traite que les positifs*/
{
  int r = 0;
  int i;
  for(i=0; ch[i] != 0 ;i++)
    {
      assert ((ch[i] >= '0') && (ch[i] <= '9'));
      r *=10;
      r += (((int) ch[i] - 48));
    }
  return r;
}

 
 void unint_swap (unsigned int *m,unsigned int *n)
{
  unsigned int tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

hunintarray hunintarray_index_sorted (hunintarray T)
{
  unsigned int min;int index_min = T->len, i , n;
  hunintarray sorted_index = hunintarray_create(T->len); 

  for (i = 0; i < T->len; i++)

    {
      min = (T->len+1);

	for(n = 0; n < T->len; n++)
      {
      if (T->data[n] < min)
	{
	index_min = n;
	min = T->data[index_min];
	}
      
      }
    sorted_index->data[i] = index_min;
    T->data[index_min] = T->len+1;
    }

  return sorted_index;
}


hunintarray diviseur(unintdata n)
{
  
int i;
hunintarray T = standard_empty_hunintarray_create();
i = 1;
while (i <= n)
{
	if( n%i == 0)
	{
	  hunintarray_add(T,i);

	}
i++;
}
 return T;
 
}


void print_premier(hunintarray I,unsigned int n)
{
  if (I->len == 2)
    printf("%u\n", n);
}


int premier_1(int m)
{
  hunintarray T = diviseur(m);
  int len = hunintarray_length(T);
  hunintarray_destroy(T);
  if ( len == 2)
    return 1;
  else
    return 0;
}

int premier_2(unintdata m)
{
  if (m == 1)
    return 0;
  else
    {
      int i;
      for (i = 2 ; i < m ; i++)
	{
	  if (m % i == 0)
	    return 0;
	}
      return 1;
    }
}


int premier_3(unintdata m)
{
  if (m == 1)
    return 0;
  else if( m ==2 )
    return 1;
  else
    {
      int i;
      for (i = 2 ; i < square (m) + 1 ; i++)
	{
	  if (m % i == 0)
	    return 0;
	}
      return 1;
    }
}




/* T must be sorted  */
int hunintarray_dicho_search (hunintarray T, unintdata value)
{
  int D, F, M;
  D = 0; F = T->len - 1;
  do /* repeat */
    {
      M = (F + D) / 2;
      if (T->data[M] == value)
	return M;
      else if (T->data[M] < value)
	D = M + 1;
      else
	F = M - 1;
    }
  while (F >= D); /* until F < D */
  return -1;
}

int hunintarray_search (hunintarray T, unintdata value)
{
  int i = 0;
  while ((i < T->len) && (T->data[i] != value))
    i++;

  if (i == T->len)
    return -1;
  else
    return i;
}

void hunintarray_set_length (hunintarray A, int new_size)
{
  if (new_size >= A->alloc)
    hunintarray_alloc_more (A, new_size);

  A->len = new_size;
}
