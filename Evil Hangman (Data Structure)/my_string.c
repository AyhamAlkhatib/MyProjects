#include <stdio.h> // include directive
#include <stdlib.h> // include directive
#include <ctype.h> // include directive
#include "my_string.h" // include header

struct my_string // declare known type of structure
{
  int size; // the number of characters currently in the object
  int capacity; // total capacity of the object
  char* data; // pointer to the object -malloc starts here
};
typedef struct my_string My_string; // define type

Boolean check_if_used( MY_STRING guess_list, char c ) {

    My_string* pMy_string = (My_string*)guess_list;
    int i ;

    for ( i = 0; i < my_string_get_size( guess_list ); i++ ) {

        if ( pMy_string -> data[i] == c ) {

            printf( "You have already guessed that letter! Try again...\n" ) ;
            return TRUE ;

        }

    }

    return FALSE ;

}

MY_STRING my_string_init_default(void)
{
  My_string* pString; // declare pointer to object
  pString = (My_string*)malloc(sizeof(My_string)); // allocate space for object
  if(pString != NULL) // if allocation was successful
  {
    pString->size = 0; // initalise size
    pString->capacity = 7; // initalise capacity
    pString->data = (char*)malloc(sizeof(char)*pString->capacity);
    // allocate space for capacity number of characters
  }
  else // if allocation was not successful
  {
    free(pString); // release the pointer
    pString = NULL; // and set it to NULL
  }
  return (MY_STRING)pString; // cast to handle type void* and return
}

void my_string_destroy(Item* pItem)
{
  My_string* pMy_string = (My_string*) *pItem; // cast to the known type
  free(pMy_string->data); // release the data pointer within the object
  free(pMy_string); // release the pointer to the object itself
  *pItem = NULL; // and set it to NULL
  return; // return
}


MY_STRING my_string_init_c_string(const char* c_string)
{
  int i = 0; // declare counter variable
  int capacity = 0; // declare holder variable
  int size = 0; // declare holder variable
  char c = 'd'; // declare holder variable

  for( i = 0; c != '\0'; i++) // measure the size of the given c-string
    {
      c = c_string[i];
    }
  size = i - 1;
  capacity = size;
  
  My_string* pString;
  pString = (My_string*)malloc(sizeof(My_string));
  if(pString != NULL)
  {
    pString->size = size;
    pString->capacity = capacity;
    pString->data = (char*)malloc(sizeof(char)*pString->capacity);
    
  }
  else // if allocation was not successful
  {
    free(pString);
    pString = NULL;
  }

  for (i = 0; i < capacity; i++)
  {
    pString->data[i] = c_string[i];
  }

  return (MY_STRING)pString;
}


int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string;
  return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  return pString->size; // return the size
}


int my_string_compare( MY_STRING hLeft_string, MY_STRING hRight_string ) {

    My_string *pLeft_string = ( My_string * ) hLeft_string ;
    My_string *pRight_string = ( My_string * ) hRight_string ;
    int i ;

    for ( i = 0; i < pLeft_string -> size && i < pRight_string -> size; i++ )    {
        
        if ( pLeft_string -> data[i] < pRight_string -> data[i] )
    {
            return -1 ;
            //break;
        } else if ( pLeft_string -> data[i] > pRight_string -> data[i] ) {
            
            return 1 ;
            // break
        }

    }
    return 0;
}


Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string* pString = (My_string*)hMy_string;
  char c = 'd';
  int i = 0;
  c = fgetc(fp);
  while(isspace(c))
    {
        c = fgetc(fp);
    if(c == EOF)
      {
        return FAILURE;
      }
    }
  pString->size = 0;
  for(i = 0;!isspace(c); i++)
    {
      if (pString->capacity > i+ 1)
    {
      pString->data[i] = c;
      pString->size = i + 1;
    }
      else
    {
     
      pString->data = (char*)realloc(pString->data, pString->capacity * 2);
      if(pString->data == NULL)
        {
          return FAILURE;
        }
      pString->capacity *= 2;
      pString->data[i] = c;
      pString->size = i + 1;
    }
      c = fgetc(fp);
      if(c == EOF)
     {
       return FAILURE;
     }
    }
  ungetc(c, fp);
  return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* pString = (My_string*)hMy_string;
  char c = 'd';
  int i = 0;
  if(pString == NULL)
    {
      return FAILURE;
    }
  else
    {
      for (i = 0; i < pString->size; i++)
    {
      c = pString->data[i];
      fprintf(fp, "%c", c);
    }
      return SUCCESS;
    }
}



Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  if (pString->capacity > pString->size + 1) // if there is room in pString
    {
      pString->data[pString->size] = item; // insert character into pString
      pString->size = pString->size + 1; // increment size
    }
  else // if there is not enough room for another character
    {
      // reallocate twice the capacity as before resizing
      pString->data = (char*)realloc(pString->data, pString->capacity * 2);
      if(pString->data == NULL) // if reallocation failed
    {
      return FAILURE; // return failure
    }
      else // if reallocation succeeded
    {
      pString->capacity *= 2; // re-set capacity
      pString->data[pString->size] = item; // insert character into pString
      pString->size = pString->size + 1; // increment size
    }
    }
  return SUCCESS; // return sucess
}

Status my_string_pop_back(MY_STRING hMy_string)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type
   if (pString->size > 0) // if pString is not empty
     {
       pString->size = pString->size - 1; // reduce size of pString
       return SUCCESS; // return sucess
     }
   else // if pString is empty
     {
       return FAILURE; // return failure
     }
}


char* my_string_at(MY_STRING hMy_string, int index)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type

   if (index < pString->size && index >= 0) // if the index is within bounds
     {
       return (char*)&pString->data[index]; // return address
     }
   else // if the index is not within bounds
     {
       return NULL; // return NULL
     }
}


char* my_string_c_str(MY_STRING hMy_string)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type
   my_string_push_back(hMy_string, '\0'); // insert a NULL character
   pString->size = pString->size - 1; // correct size increment
   return (char*)&(pString->data[0]); // return address
}


Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*)hResult; // cast to the known type
  My_string* pAppend = (My_string*)hAppend; // cast to the known type
  int needed_size = (int)pResult->size + (int)pAppend->size; // find needed size
  int i= 0; // declare counter variable
  int continued_i = 0; // declare counter variable
  char* c = NULL; // declare character pointer
  char* pTemp = NULL; // declare temporary holder variable

  pTemp = (char*)malloc(sizeof(char) * needed_size); // allocate memory
  if (pTemp == NULL) // if allocation failed
    {
      return FAILURE; // return failure
    }
  
  c = my_string_c_str(hResult); // initialize character pointer
  for( i = 0; i < pResult->size; i++) // loop through first string
    {
      pTemp[i] = *(c + i); // insert one character at a time
    }

  continued_i = i; // maintain counter by saving its current value
  
  c = my_string_c_str(hAppend); // initialize character pointer
  for( i = 0; i < pAppend->size; i++) // loop through the second string
    {
      pTemp[continued_i] = *(c + i); // insert one character at a time
      continued_i++; // continue to increment the counter used above
    }

  free(pResult->data); // free old data handle
  pResult->data = pTemp; // insert new data handle
  pResult->size = needed_size; // adjust size
  pResult->capacity = needed_size; // adjust capacity
  
  return SUCCESS; // return success
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  if (pString->size <= 0) // if pString size is 0 (strong condition)
    {
      return TRUE; // return true (pString is empty)
    }
  else // if pString size is greater than 0
    {
      return FALSE; // return false (pString is not empty)
    }
}

void my_string_assignment(Item* pLeft, Item Right)
{
  My_string* pLeft_string = (My_string*)*pLeft;
  My_string* pRight_string = (My_string*)Right;
  int i;
  char* temp;
  temp = my_string_c_str((MY_STRING)Right);
  if(pLeft_string == NULL)
    {
      pLeft_string = my_string_init_c_string(temp);
    }
  else
    {
      pLeft_string->size = 0;
      for(i=0; i<pRight_string->size+1; i++)
    {
      my_string_push_back(pLeft_string, pRight_string->data[i]);
    }
    }
  *pLeft = pLeft_string;
}

Status get_word_key_value( MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess ) {
    int i;
    while(!my_string_empty(new_key))
        my_string_pop_back(new_key);
    for(i = 0; i < my_string_get_size(word); i++)
        if(!my_string_push_back(new_key, *my_string_at(word, i) == guess ? guess : *my_string_at(current_word_family, i)))
            return FAILURE;
    return SUCCESS;
}
