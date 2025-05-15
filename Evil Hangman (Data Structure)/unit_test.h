#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"


Status test_aalkhati_init_default_returns_nonNULL(char* buffer, int length); // 1
Status test_aalkhati_get_size_on_init_default_returns_0(char* buffer, int length); //2
Status test_aalkhati_get_capacity_on_init_default_returns_7(char* buffer, int length);//3
Status test_aalkhati_init_c_string_returns_nonNULL(char* buffer, int length);//4
Status test_aalkhati_get_size_returns_0(char* buffer, int length); //5
Status test_aalkhati_compare_works_with_non_alphanumeric_characters(char* buffer, int length);//6
Status test_aalkhati_my_string_pop_back_reduces_size(char* buffer, int length); // 7
Status test_aalkhati_my_string_empty_confirms_on_popped_back_string(char* buffer, int length); // 8
Status test_aalkhati_check_string_concat_properly_calculates_size(char* buffer, int length); // 9
Status test_aalkhati_check_if_my_string_c_string_changes_size(char* buffer, int length); // 10

Status test_aalkhati_my_string_at_correctly_returns_address(char* buffer, int length); // 11
Status test_aalkhati_extraction_returns_correct_size(char* buffer, int length); // 12
Status test_aalkhati_insertion_prints_c_string_correctly(char* buffer, int length); // 13
Status test_aalkhati_extraction_copies_correctly_from_file(char* buffer, int length); // 14
Status test_aalkhati_my_string_compare_returns_0(char* buffer, int length); // 15
Status test_aalkhati_compare_returns_greater_than_0( char *buffer, int length ); // 16

Status test_aalkhati_compare_returns_less_than_0( char *buffer, int length ); // 17
Status test_aalkhati_concat_allocates_additional_memory( char *buffer, int length ); // 18
Status test_aalkhati_concat_returns_success(char* buffer, int length); // 19
Status test_aalkhati_concat_returns_success_with_empty_string( char *buffer, int length); // 20
Status test_aalkhati_string_empty_returns_false_on_a_nonempty_string(char *buffer, int length); // 21
Status test_aalkhati_string_empty_returns_true_on_an_empty_string( char *buffer, int length ); // 22
Status test_aalkhati_init_c_str_resize(char* buffer, int length);// 23
Status test_aalkhati_push_back_allocates_additional_memory(char *buffer, int length); // 24
Status test_aalkhati_returns_NULL_at_out_of_bounds_index(char* buffer, int length); // 25
#endif
