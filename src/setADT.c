/***************************************
Group No 35
 2018A7PS0238P Name: Hritwik Goklaney		         
 2018A7PS0262P Name: Yash Gupta 
 2018A7PS0161P Name: Chaitanya Kulkarni		         
 2018A7PS0004P Name: Aashay Garg	
***************************************/
#include "setADT.h"

void set_init(set s) 
{
  for (int i = 0; i < SET_SIZE; i++) 
  {
    s[i] = 0;
  }
}

bool set_find_elem(set s, int num) 
{
  return ( (s[num / ULL_NUM_BITS] & (((1ULL << (ULL_NUM_BITS - 1)) >> (num % ULL_NUM_BITS)))) != 0 );
}

void set_remove_elem(set s, int num) 
{
  s[num / ULL_NUM_BITS] &= (~((1ULL << (ULL_NUM_BITS - 1)) >> (num % ULL_NUM_BITS)));
}

void set_add_elem(set s, int num) 
{
  s[num / ULL_NUM_BITS] |= ((1ULL << (ULL_NUM_BITS - 1)) >> (num % ULL_NUM_BITS));
}

void set_union(set dest, set first, set second) {
  for (int j = 0; j < SET_SIZE; j++) 
  {
    dest[j] = first[j] | second[j];
  }
}

void set_intersection(set dest, set first, set second) {
  for (int j = 0; j < SET_SIZE; j++) {
    dest[j] = first[j] & second[j];
  }
}

bool is_superset(set first, set second) 
{
  for (int j = 0; j < SET_SIZE; j++) {
    if ((first[j] & second[j]) != second[j]) {
      return false;
    }
  }
  return true;
}