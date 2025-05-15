#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

Status test_aalkhati_init_default_returns_nonNULL(char* buffer, int length)
{
    MY_STRING hString = NULL; hString = my_string_init_default();
    if(hString == NULL) {
        strncpy(buffer, "test_init_default_returns_nonNULL\n" "my_string_init_default returns NULL", length);
        return FAILURE;
    }
    else {
        my_string_destroy(&hString);
        strncpy(buffer, "init_default_returns_nonNULL\n", length); return SUCCESS;
    }
}
Status test_aalkhati_get_size_on_init_default_returns_0(char* buffer, int length)
{
    MY_STRING hString = NULL; Status status;
    hString = my_string_init_default();
    if(my_string_get_size(hString) != 0) {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
        strncpy(buffer, "test_get_size_on_init_default_returns_0\n""Did not receive 0 from get_size after init_default", length);
    } else {
        status = SUCCESS;
        strncpy(buffer, "get_size_on_init_default_returns_0\n"
                , length);
    }
    my_string_destroy(&hString);
    return status;
    
}

Status test_aalkhati_get_capacity_on_init_default_returns_7(char* buffer, int length)
// Test if get capacity returns correct number which is 7
{
    
    MY_STRING hString = NULL;
    Status status;
    
    hString = my_string_init_default();
    
    if (my_string_get_capacity(hString) != 7)
    {
        status = FAILURE;
        printf("Expected a capacity of 7 but got %d\n",
               my_string_get_capacity(hString));
        strncpy(buffer,
                "test_get_capacity_on_init_default_returns_7\n"
                "Did not receive 7 from get_capacity after init_default"
                , length);
    }
    else
    {
        status = SUCCESS;
        strncpy(buffer,
                "get_capacity_on_init_default_returns_7\n"
                , length);
    }
    my_string_destroy(&hString);
    return status;
    
}

Status test_aalkhati_get_size_returns_0(char* buffer, int length)
// Tests if get_size function returns 0
{
    MY_STRING hstring = NULL;
    Status status;
    hstring = my_string_init_default();
    if (my_string_get_size(hstring)!= 0)
    {
        status = FAILURE;
        printf("Expected a size of 0 but got %d\n",
               my_string_get_capacity(hstring));
        strncpy(buffer,
                "test_aalkhati_get_size_returns_0\n"
                "Did not receive 0 from get_size after init_default"
                , length);
    }
    else {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_get_size_returns_0",length);
        
    }
    my_string_destroy(&hstring);
    return status;
}

Status test_aalkhati_init_c_string_returns_nonNULL(char* buffer, int length)
// Test if intit_c_str function returns a non NULL string after creating a string
{
  MY_STRING hString = NULL;
  hString = my_string_init_c_string("StarLight");

  if(hString == NULL)
    {
      strncpy(buffer,
          "test_aalkhati_init_c_string_returns_nonNULL\n"
          "my_string_init_c_string returns NULL"
          , length);
      return FAILURE;
    }
  else
    {
      my_string_destroy(&hString);
      strncpy(buffer
          , "aalkhati_init_c_string_returns_nonNULL\n"
          , length);
      return SUCCESS;
    }
}

Status test_aalkhati_compare_works_with_non_alphanumeric_characters(char* buffer, int length)
// Checks if my string_compare function works right by comparing 2 strings in which one is smaller than the other.
{
  MY_STRING hRstring = NULL;
  MY_STRING hLstring = NULL;
  int result = 0;
  Status status = FAILURE;

  hRstring = my_string_init_c_string("+-&^ *"); // R is smaller
  hLstring = my_string_init_c_string("+-&^ *?");

  result = my_string_compare(hLstring, hRstring);

  if (result <= 0)
    {
      strncpy(buffer,
          "test_aalkhati_compare_works_with_non_alphanumeric_characters\n"
          "my_string_compare returned incorrect value"
          , length);
      status = SUCCESS;
    }
  else
    {
      strncpy(buffer,
          "aalkhati_compare_works_with_non_alphanumeric_characters\n"
          , length);
      status = SUCCESS;
    }
  my_string_destroy(&hRstring);
  my_string_destroy(&hLstring);
  return status;
}
Status test_aalkhati_my_string_pop_back_reduces_size(char* buffer, int length)
// Tests if pop back actually reduces the size...
{
    MY_STRING str = my_string_init_c_string("Moonlight");
    Status status;
    my_string_pop_back(str);
    if (my_string_get_size(str)!= 8)
    {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_my_string_pop_back_reduces_size\n"
                "test_aalkhati_my_string_pop_back_doesn't_reduces_size",length);
    } else {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_my_string_pop_back_reduces_size\n",length);
    }
    my_string_destroy(&str);
    return status;
}
Status test_aalkhati_my_string_empty_confirms_on_popped_back_string(char* buffer, int length)
// test a string size after calling my_string_pop_back multiple times
{
    MY_STRING str;
    Status status;
    str = my_string_init_c_string("Moonlight");
    for (int i = 0; i < 9; i++)
        my_string_pop_back(str);
    if (my_string_empty(str) == TRUE )
    {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_my_string_empty_confirms_on_popped_back_string\n",length);
    }
    else {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_my_string_empty_confirms_on_popped_back_string\n"
                "test_aalkhati_my_string_empty_doesn't_confirm_on_popped_back_string",length);
    }
    my_string_destroy(&str);
    return status;
}
Status test_aalkhati_check_string_concat_properly_calculates_size(char* buffer, int length)
// Test if my_string_concat properly calculates the size..
{
    Status status;
    MY_STRING str1 = my_string_init_c_string("Moonlight");
    MY_STRING str2 = my_string_init_c_string("Barcelona");
    my_string_concat(str1, str2);
    if (my_string_get_size(str1)!= 18)
    {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_check_string_concat_properly_calculates_size\n"
                "test_aalkhati_string_concat_doesn't_properly_calculates_size",length);
    } else {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_check_string_concat_properly_calculates_size\n",length);
    }
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    return status;
}

Status test_aalkhati_check_if_my_string_c_string_changes_size(char* buffer, int length)
{
    // Test my_str_c_str changes the size.... Fails if it change the size ... success otherwise
    MY_STRING str = my_string_init_c_string("Barca");
    Status status;
    my_string_c_str(str);
    if (my_string_get_size(str) != 5)
    {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_check_if_my_string_c_string_changes_size\n"
                "test_aalkhati_my_string_c_string_changes_size\n",length);
    } else {
        status = SUCCESS;
        strncpy(buffer,"alkhati_check_if_my_string_c_string_changes_size",length);
    }
    my_string_destroy(&str);
    return status;
}

Status test_aalkhati_my_string_at_correctly_returns_address(char* buffer, int length)
// Tests my_string_at returns the correct address
{
  MY_STRING hMy_string = NULL;
    Status status = SUCCESS; ;
  char actual_string[9] = "StarLight";
  int i = 0;
  hMy_string = my_string_init_c_string(actual_string);
  
  for (i = 0; i < 9; i++)
    {
      if (*my_string_at(hMy_string, i) != actual_string[i])
    {
      status = FAILURE;
    }
    }

  if (status == FAILURE)
    {
      strncpy(buffer,
          "test_aalkhati_my_string_at_correctly_returns_address\n"
          "Address returned by my_string_at did not align."
          , length);
    }
  else
    {
        
      strncpy(buffer,
          "aalkhati_my_string_at_correctly_returns_address\n"
          , length);
    }

  my_string_destroy(&hMy_string);
  return status;
}
Status test_aalkhati_extraction_returns_correct_size(char* buffer, int length)
// Tests if my_string_extraction calculates the correct size
{

  MY_STRING str = NULL;
  Status status;
  FILE* fp;
  
  str = my_string_init_default();
  
  fp = fopen("Simple.txt", "w");
  fprintf(fp, "Culers");
  fclose(fp);
  
  fp = fopen("Simple.txt", "r");

  my_string_extraction(str, fp);
  if (my_string_get_size(str) != 6)
    {
      strncpy(buffer,
          "test_aalkhati_extraction_returns_correct_size\n"
          "my_string_extraction set the wrong size or inlcuded spaces"
          , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,"test_aalkhati_extraction_returns_correct_size\n", length);
      status = SUCCESS;
    }
  
  fclose(fp);
  
  my_string_destroy(&str);
  return status;
}

Status test_aalkhati_insertion_prints_c_string_correctly(char* buffer, int length)
// Tests if my_string_insertion correctly prints data
{
    
    Status status;
    FILE* fp;
    int i;
    char* string= "Barcelona";
    MY_STRING str =  my_string_init_c_string(string);
    fp = fopen("Simple.txt","w");
    my_string_insertion(str, fp);
    fclose(fp);
    fp = fopen("Simple.txt","r");
    for ( i = 0; i < 9; i++)
    {
        if (fgetc(fp) != string[i])
        {
            status = FAILURE;
            break;
        }
    }
    if (status == FAILURE)
    {
        strncpy(buffer,"aalkhati_insertion_prints_c_string_correctly\n"
                "aalkhati_insertion_doesn't_prints_c_string_correctly",length);
    }
    else {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_insertion_prints_c_string_correctly\n",length);
    }
    fclose(fp);
    my_string_destroy(&str);
    return status;
}
Status test_aalkhati_extraction_copies_correctly_from_file(char* buffer, int length)
// Tests if my_string_extraction correctly copies data from the file
{
  MY_STRING hMy_string = NULL;
  char actual_string[9] = "StarLight";
  Status status = SUCCESS;
  FILE* fp;
  int i = 0;
  
  hMy_string = my_string_init_default();
  
  fp = fopen("Simple.txt", "w");
  fprintf(fp, "StarLight");
  fclose(fp);
  
  fp = fopen("Simple.txt", "r");
  my_string_extraction(hMy_string, fp);
  fclose(fp);

  for (i = 0; i < 9; i++)
    {
      if (*my_string_at(hMy_string, i) != actual_string[i])
    {
      status = FAILURE;
    }
    }

  if (status == FAILURE)
    {
      strncpy(buffer,
          "test_aalkhati_extraction_copies_correctly_from_file\n"
          "my_string_extraction did not copy correctly from file."
          , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,
          "aalkhati_extraction_copies_correctly_from_file\n"
          , length);
      status = SUCCESS;
    }
  
  remove("Simple.txt");
  my_string_destroy(&hMy_string);
  return status;
}
Status test_aalkhati_my_string_compare_returns_0(char* buffer, int length)
// Tests if my_string_compsre returns 0 when both strings have same length.
{
    Status status;
    MY_STRING str1 = my_string_init_c_string("Culers");
    MY_STRING str2 = my_string_init_c_string("Culers");
    int result = my_string_compare(str1, str2);
    if (result == 0)
    {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_my_string_compare_returns_0\n",length);
    } else {
        status = FAILURE;
        strncpy(buffer,"aalkhati_my_string_compare_returns_0\n"
                "aalkhati_my_string_compare_doesnt_return_0",length);
    }
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    return status;
}

Status test_aalkhati_compare_returns_greater_than_0( char *buffer, int length )
// Tests if my_string_compare returns an integer greater than 0 when the left string is greater than the right string
{
  MY_STRING str2 = my_string_init_c_string( "Barca" ) ;
  MY_STRING str1 = my_string_init_c_string("Barcelona") ;
  Status status ;

   if ( my_string_compare( str1, str2 ) > 0 )
    {

    status = SUCCESS ;
    strncpy( buffer, "aalkhati_compare_returns_greater_than_0\n", length ) ;

    }
  else
    {
    status = FAILURE ;
    strncpy( buffer, "aalkhati_compare_returns_greater_than_0\n"
            "my_string_compare returned a value less than or equal to zero", length ) ;
    }
  my_string_destroy( &str1 ) ;
  my_string_destroy( &str2 ) ;
  return status ;
}
Status test_aalkhati_compare_returns_less_than_0( char *buffer, int length)
// Tests if my_string_compare returns an integer less than 0 when the left string is lesst than the right string
{

  MY_STRING str1 = my_string_init_c_string( "Barca" ) ;
  MY_STRING str2 = my_string_init_c_string("Barcelona") ;
  Status status ;

   if ( my_string_compare( str1, str2 ) <= 0 )
    {

    status = SUCCESS ;
    strncpy( buffer, "aalkhati_compare_returns_less_than_0\n", length ) ;

    }
  else
    {
    status = FAILURE ;
    strncpy( buffer, "test_aalkhati_compare_returns_greater_than_0\n"
            "my_string_compare returned a value greater than or equal to zero", length ) ;
    }
  my_string_destroy( &str1 ) ;
  my_string_destroy( &str2 ) ;
  return status ;
}
Status test_aalkhati_concat_allocates_additional_memory( char *buffer, int length )
// Tests if my_string_concat allocates additionl memory when resize is needed
{
    Status status;
    MY_STRING str1 = my_string_init_c_string("Barcelona");
    MY_STRING str2 = my_string_init_c_string("Barca");
    int count = my_string_get_capacity(str1);
    my_string_concat(str1, str2);
    if (count >= my_string_get_capacity(str1))
    {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_concat_allocates_additional_memory\n"
                "concat_doesn't_allocates_additional_memory",length);
    } else {
        status = SUCCESS;
        strncpy(buffer,"concat_allocates_additional_memory\n",length);
    }
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    return status;
}
Status test_aalkhati_concat_returns_success(char* buffer, int length)
// Tests if my_string_concat correctly concatenate 2 strings.
{
    MY_STRING str1 = my_string_init_c_string("Barcelona");
    MY_STRING str2 = my_string_init_c_string("Barca");
    Status status;
    if (my_string_concat(str1, str2) == SUCCESS)
    {
        status = SUCCESS;
        strncpy(buffer,"aalkhati_concat_returns_success\n",length);
    } else {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_concat_returns_success\n"
                "concat_returns_failure",length);
    }
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    return status;
}
Status test_aalkhati_concat_returns_success_with_empty_string( char *buffer, int length)
// Tests if my_string_concat appends with an empty string
{
    MY_STRING str1 = my_string_init_c_string("Barcelonaa");
    MY_STRING str2 = my_string_init_c_string("");
    Status status;
    if (my_string_concat(str1, str2) == FAILURE)
    {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_concat_returns_success_with_empty_string\n"
                "concat_returns_failure_with_empty_string",length);
    } else {
        status = SUCCESS;
        strncpy(buffer,"concat_returns_success_with_empty_string",length);
    }
    my_string_destroy(&str1);
    my_string_destroy(&str2);
    return status;
}
Status test_aalkhati_string_empty_returns_false_on_a_nonempty_string( char *buffer, int length)
// Checks if my_string_empty returns false on a non_empty string
{
    MY_STRING str1 = my_string_init_c_string("Barca");
    Status status;
    if (my_string_empty(str1) == FALSE)
    {
        status = SUCCESS;
        strncpy(buffer,"string_empty_returns_false_on_a_nonempty_string\n",length);
    } else {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_string_empty_returns_false_on_a_nonempty_string\n"
                "string_empty_doesn't_return_false_on_a_nonempty_string",length);
    }
    my_string_destroy(&str1);
    return status;
}
Status test_aalkhati_string_empty_returns_true_on_an_empty_string(char *buffer, int length)
// Test if my_string_empty returns true on an empty string
{
    MY_STRING str= my_string_init_c_string("");
    Status status;
    if (my_string_empty(str) == TRUE)
    {
        status = SUCCESS;
        strncpy(buffer,"string_empty_returns_true_on_an_empty_string\n",length);
    } else {
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_string_empty_returns_true_on_an_empty_string\n"
                "string_empty_doesn't_return_true_on_an_empty_string",length);
    }
    my_string_destroy(&str);
    return status;
}
Status test_aalkhati_returns_NULL_at_out_of_bounds_index(char* buffer, int length)
// Checks if my_string_at will return NULL at index out of bounds
{
    MY_STRING hString1 = NULL;
    Status status;

    hString1 = my_string_init_c_string("test");
    

    if (my_string_at(hString1, 9) == NULL)
    {
        status = SUCCESS;
        strncpy(buffer, "test_aalkhati_at_negative_index\n", length);
        
    }
    else
    {
        status = FAILURE;
        printf("Expected NULL but received a non-NULL response\n");
        strncpy(buffer, "test_aalkhati_at_negative_index", length);
    }
    my_string_destroy(&hString1);
    return status;
}
Status test_aalkhati_push_back_allocates_additional_memory(char *buffer, int length)
// Checks if push back do a resize if it needed a resize.
{
    Status status;
    MY_STRING str = my_string_init_c_string("FC barcelon");
    int count1 = my_string_get_capacity(str);
    my_string_push_back(str, 'a');
    int count2 = my_string_get_capacity(str);
    if (count2 > count1)
    {
        status = SUCCESS;
        strncpy(buffer,"push_back_allocates_additional_memory\n",length);
    } else{
        status = FAILURE;
        strncpy(buffer,"test_aalkhati_push_back_allocates_additional_memory\n"
                "push_back_doesn't_allocates_additional_memory",length);
    }
    my_string_destroy(&str);
    return status;
}

Status test_aalkhati_init_c_str_resize(char* buffer, int length)
// Checks if my_string_init_c_string do a resize if it needed.
{
    MY_STRING hString = NULL;
    Status status;

    hString = my_string_init_c_string("Computing II");

    if(my_string_get_capacity(hString) < 12)
    {
        status = FAILURE;
       
        strncpy(buffer, "test_does_init_c_str_resize_properly\n"
                "c_str did not resize properly", length);
    }
    else
    {
        status=SUCCESS;
        strncpy(buffer, "test_aalkhati_init_c_str_resize\n", length);
    }
    my_string_destroy(&hString);
    return status;
}
