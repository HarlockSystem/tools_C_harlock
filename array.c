#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "array.h"
#include "jstr.h"

void array_alloc_more(array T , int new_alloc);

void array_print (array T)
{
  int i;
  for (i= 0; i< T->len; i++)
    {
      printf(" %d ", T->data[i]);
    }
	RC;
}

void array_debug (array T)
{
  int i;
  printf("array, Memoire allouee : %d\nMemoire utilisee : %d\n", T->alloc, T->len);
  for(i=0 ; i<T->len; i++)
    {
      printf (" %d ", T->data[i]);
    }
  RC;
}

/*array array_create (int len)
{
  array A = malloc (sizeof (struct _array));
  A->len = len;
  A->alloc = len;
  A->data = malloc (sizeof (int) * len);
  return A;
  }*/

array array_create(int len)
{
  return ext_array_create(len, len);
}

array ext_array_create (int len, int alloc)
{
  assert ((len >=0) && (alloc > 0) && (len <=alloc));
  {
  array A = malloc (sizeof (struct _array));
  A->len = len;
  A->alloc = alloc;
  A->data = malloc (sizeof (data) * alloc);
  return A;
  }
}

array empty_array_create(int alloc)
{
  return ext_array_create(0 , alloc);
}
/* array T = array_create (1000); */
/* array_set (T , x , y); */

void array_alloc_more(array T , int new_alloc)
{
  data * tmp = malloc (sizeof (data) * new_alloc);
  int i;
  for ( i = 0 ; i < T->len ; i++)
    {
    tmp[i] = T->data[i];
    }		       
      free (T->data);
      T->data = tmp;
      T->alloc = new_alloc;
}		    

array standard_empty_array_create (void)
{
  return ext_array_create ( 0, ARRAY_DEFAULT_ALLOC);
}

void array_destroy (array T)
{
  free (T->data);
  free (T);
}

data array_get (array T , int i)
{
  assert (i >= 0);
  assert (i < T->len);
  return T->data[i];
 }

void array_set ( array T, int i, data n)
{
  assert (i >=0 );
  assert (i < T->len);
  T->data[i] = n;
}

void ext_array_set ( array T, int i, data n)
{
  if (i >= T->alloc)
    array_alloc_more (T,i *2);
  if (i >=T->len)
    T->len = i+1;
  array_set(T, i, n);
}



int array_length (array T)
{
  return T->len;
}

void array_add(array T, data n)
{
  ext_array_set(T, T->len , n);    
}

void array_delete(array T, int loc)/*modifie l'ordre du tableau*/
{
  assert (T->len > 0);
  assert (loc < T->len);
  T->data[loc] = T->data[T->len-1];
  T->len--;
} 
 



data array_get_min(array T)
{
  int n;
  data m;
  m = array_get (T,0);
  
  for(n = 1; n < array_length (T) ; n++)
      {
	data T_i = array_get (T , n);
	if (T_i<m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

array array_concat(array T1, array T2)
{
  array T = array_create (array_length (T1) + array_length (T2));
  int i,j;
  j = array_length(T1);
  for(i=0 ; i < array_length (T1); i++)
    {
      /*EXPL: T->data[i] = T1->data[i]; */
      /*EXPL: T->data[i] = array_get (T1 ;i);*/
      array_set (T, i, array_get (T1 ,i));
    }
  for(i=0; i < array_length (T2); i++)
    {
      array_set (T , (j+i) , array_get (T2, i));
    }
  return T;
}


void D_array_concat(array T1 , array T2)
{
  data n;
  for (n = 0; n < array_length(T2); n++)
    array_add(T1 , array_get(T2 ,n));
		   
 }		 



int array_seek_min_index (array T ,int start)
{
  int i, index_min;
  data m = T->data[start];
  index_min = start;
    
  for (i = start +1 ; i < array_length (T) ; i++)
      {
	if  (T->data[i] <  m)
	  {
	  m = T->data[i];
	  index_min = i;
	  }
      }
  return index_min;
}

void array_sort1 (array T)/* tri par selection du minimum)*/
{
  int i;
  for(i = 0 ; i < array_length( T ) ; i++)
    {
      int_swap (T->data + i, T->data + array_seek_min_index(T , i));
    }
}
/*
void array_sort2 (array T)
{
int i, index_min;
for (i = 0; i <= array_length(T) - 2; i++)
{
index_min = array_seek_min_index (T , i);
int_swap (T->data + i , T->data + index_min);
}
}
*/






data array_get_max (array T)/* cherche le chiffre le plus grand*/
{
  int n;
  data m = array_get (T,0);
  
  for(n = 1; n < array_length (T) ; n++)
      {
	data T_i = array_get (T , n);
	if (T_i > m)
	  {
	    m = T_i; 
	  }
      }
  return m;
}

int array_num_occur(array T, data n)
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

array array_clone (array T)
{
  array U = array_create (T->len);
  int i;
  for (i = 0 ; i < T->len ; i++)
    {
      U->data[i] = T->data[i];
    }
  return U;
}


void array_arg(int a, char* c[]) 
{
  if(  a >= 2 )
  {
  int taille = a - 1;
  array T = empty_array_create(2);
  int i;
  for (i = 0 ; i < taille ; i++)
    {
      array_add(T, string_to_int ( c[i + 1]));
    }
  {
    int mn = array_get_min (T);
    int mx = array_get_max (T);
    float ave = array_average (T);
    float med = array_median (T);
    printf("vous avez entre %d nombre(s).\n", taille);
    printf("Le plus petit est %d , le plus grand est %d .\n", mn , mx);
    printf("L'etendue est de %d\n" , mx - mn);
    printf("La moyenne arithmetique s'eleve a %f .\n",ave);
    printf("La mediane est egale a %f .\n",med);
    printf("Vous avez entre les valeurs suivantes :\n");
    array_debug (T); RC;
    printf("Soit , par ordre croissant :\n");
    array_sort1 (T);
    array_debug(T);
  }
  array_destroy(T);
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

 void scanf_pos_int (int *n)
{
  scanf("%d", n);
while ((*n) <= 0)
	{
		printf("Entrez un nombre strictement positif.\n");
		scanf("%d",n);
	}
  }

 int factorielle (int n)
{
  int a =1 ,i;
  assert ( (n >= 0)&&(n <= 13) );
  for(i= 1; i <= n; i++)
    {
      a *= i;
    }
  return a;
}
 
 
 int recherche_nombre(array T, data n)
{
  int i;
  for(i=0;i<T->len;i++)
    {
      if(T->data[i]=n)
	{
	  return 1;
	}
    }
  return 0;
}

int string_to_int(char * ch)/*ne traite que les positifs*/
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

 
 void int_swap (int *m, int *n)
{
  int tmp = (*m);
  (*m) = (*n);
  (*n) = tmp;
}

array array_index_sorted (array T)
{
  int min, index_min = T->len, i , n;
  array sorted_index = array_create(T->len); 

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


array diviseur(int n)
{
  
int i;
array T = standard_empty_array_create();
i = 1;
while (i <= n)
{
	if( n%i == 0)
	{
	  array_add(T,i);

	}
i++;
}
 return T;
 
}


void print_premier(array I,int n)
{
  if (I->len == 2)
    printf("%i\n", n);
}


int premier_1(int m)
{
  array T = diviseur(m);
  int len = array_length(T);
  array_destroy(T);
  if ( len == 2)
    return 1;
  else
    return 0;
}

int premier_2(int m)
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


int premier_3(int m)
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

int square(int n)
{
  return n*n;
}


array random_array(int len)
{
  array I = array_create(len);
  int i;
  for (i = 0; i < len; i++)
    {
      array_set(I, i, rand() % 10000);
    }
  return I;
}

array args_to_array(int nb , char **args)
{
  array I = empty_array_create(nb -1);
  int i;
  for (i = 1; i < nb ; i++)
    {
      array_add(I, atoi(args[i]));
    }
  return I;
}

array array_clone_heap_sort_by_min(array I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error array_clone_heap_sort_by_min array is empty");
      return NULL;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  
  heap_sort_by_min(heap_sort, I);
  
  
  array J = empty_array_create(I->len);
  for(i = 0; i < I->len; i++)
    {
      array_add(J, heap_get_head_value(heap_sort));
      heap_del_head_val_by_min(heap_sort);
    }
  
  heap_destroy(&heap_sort);
  return J;
}

void array_D_heap_sort_by_min(array I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error array_D_heap_sort_by_min array is empty");
      return;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  heap_sort_by_min(heap_sort, I);
  
  for(i = 0; i < I->len; i++)
    {
      I->data[i] = heap_get_head_value(heap_sort);
      heap_del_head_val_by_min(heap_sort);
    }
  heap_destroy(&heap_sort);
}


array array_clone_heap_sort_by_max(array I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error array_clone_heap_sort_by_max array is empty");
      return NULL;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  
  heap_sort_by_max(heap_sort, I);
  
 
  array J = empty_array_create(I->len);
  for(i = 0; i < I->len; i++)
    {
      array_add(J, heap_get_head_value(heap_sort));
      heap_del_head_val_by_max(heap_sort);
      
    }
  heap_destroy(&heap_sort);
  return J;
}

void array_D_heap_sort_by_max(array I)
{
  if(I->len == 0)
    {
      fprintf(stderr,"error array_D_heap_sort_by_max array is empty");
      return;
    }
  int i;
  heap heap_sort = heap_create_empty(I->len);
  heap_sort_by_max(heap_sort, I);
  
  for(i = 0; i < I->len; i++)
    {
      I->data[i] = heap_get_head_value(heap_sort);
      
      heap_del_head_val_by_max(heap_sort);
      
    }
  heap_destroy(&heap_sort);
}

heap heap_create_empty(int alloc)
{
  array I = empty_array_create(alloc);
  return I;
}
 
heap heap_ext_create(int len)
{
  array j = ext_array_create(len, len);
  return j;
}

heap heap_destroy(heap* H)
{
  array_destroy(*H);
  (*H) = NULL;
}

bool heap_is_empty( heap H)
{
  return (H->len == 0);
}

int heap_count_children(heap H, int i)
{
  int lc = (i*2)+1;
  if (lc >= H->len)
    return 0;
  else if( (lc + 1) >= H->len)
    return 1;
  else
    return 2;
}
 
void heap_sort_by_min(heap H, array I)
{
  int i;
  for (i = 0; i < I->len; i++)
    {
      array_add(H, I->data[i]);
      int index = H->len -1;
      
      while(heap_has_parent(H, index))
	{
	  int parent_index = heap_parent_index(index);
	  if (H->data[index] < H->data[heap_parent_index(index)])
	    {
	      int_swaph(H->data + index, H->data + heap_parent_index(index));
	      index = parent_index;
	     }
	  else
	    break;
	}	
    }
}

void heap_sort_by_max(heap H, array I)
{
  int i;
  
  for (i = 0; i < I->len; i++)
    {
      
      
      array_add(H, I->data[i]);
      int index = H->len - 1;
      while(heap_has_parent(H, index))
	{
	  int parent_index = heap_parent_index(index);
	  if (H->data[index] > H->data[parent_index])
	    {
	      int_swaph(H->data + index, H->data + parent_index);
	      index = parent_index;
	    }
	  else
	    break;
	}	
    }
}

int heap_parent_index(int x)
{
// impair (n-1)/2 pair (n/2)-1
  return (x -1)/2;
}

int heap_left_child_index(int x)
{
// (nx2)+1 impair
  
  return (2  * x + 1);
}
int heap_right_child_index(int x)
{
// (n+1)x2 pair
  return (2 * x + 2) ;
}
data heap_get_parent(heap H, int x)
{
  return array_get(H, heap_parent_index(x));
}

data heap_get_head_value(heap H)
{
      return array_get(H, 0);
}

void heap_del_head_val_by_min(heap H)
{
if (H->len ==  1)
    {
      H->len = 0;
    }
 else
   {
     int last = H->len -1;
     int index;
     H->data[0] = H->data[last];
     index = 0;
     H->len--;
     while(heap_count_children( H, index) > 0)
       {
	 int smallest_child_index = heap_get_small_child_index(H, index);
	 if (H->data[index] > H->data[heap_get_small_child_index(H,index)])
	   {
	     int_swaph(H->data + index, H->data + smallest_child_index);
	     index = smallest_child_index;
	   }
	 else
	   break;
       }

    }
 
}

void heap_del_head_val_by_max(heap H)
{

 if (H->len ==  1)
    {
      H->len = 0;
    }
 else
   {
     int last = H->len -1;
     int index;
     H->data[0] = H->data[last];
     index = 0;
     H->len--;
     while(heap_count_children( H, index) > 0)
       {
	 int biggest_child_index = heap_get_big_child_index(H, index);
	 if (H->data[index] < H->data[biggest_child_index])
	   {
	     int_swaph(H->data + index, H->data + biggest_child_index);
	     index = biggest_child_index;
	   }
	 else
	   break;
       }

    }
 
}

int heap_get_small_child_index(heap H,int x)
{
  if (heap_count_children(H, x) == 1)
    return heap_left_child_index(x);
  else
    {
      if (array_get(H,heap_left_child_index(x)) > (array_get(H,heap_right_child_index(x))))
	return heap_right_child_index(x);
  
      if (array_get(H,heap_left_child_index(x)) <= (array_get(H,heap_right_child_index(x))))
	{
	  return heap_left_child_index(x);
	}
    }
 }

int heap_get_big_child_index(heap H,int x)
{
  if (heap_count_children(H, x) == 1)
    return heap_left_child_index(x);
  else
    {
      if (array_get(H,heap_left_child_index(x)) < (array_get(H,heap_right_child_index(x))))
	return heap_right_child_index(x);
  
      if (array_get(H,heap_left_child_index(x)) >= (array_get(H,heap_right_child_index(x))))
	{
	  return heap_left_child_index(x);
	}
    }
 }

bool heap_is_parent_smaller(heap H, int x)
{
  return ( array_get(H, x) > array_get(H , heap_parent_index( x)));
}
 
bool heap_is_parent_bigger(heap H, int x)
{
  return ( array_get(H, x) < array_get(H , heap_parent_index( x)));   
}

bool heap_has_parent(heap H, int x)
{
  return (x > 0);
} 
