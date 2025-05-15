/*#include <stdio.h>
#include "unit_test.h"
int main(int argc, char* argv[]) {
Status (*tests[])(char*, int) = {
    test_aalkhati_init_default_returns_nonNULL,
    test_aalkhati_get_size_on_init_default_returns_0,
    test_aalkhati_get_capacity_on_init_default_returns_7,
    test_aalkhati_init_c_string_returns_nonNULL,
    test_aalkhati_get_size_returns_0,
    test_aalkhati_compare_works_with_non_alphanumeric_characters,
    test_aalkhati_my_string_pop_back_reduces_size,
    test_aalkhati_my_string_empty_confirms_on_popped_back_string,
    test_aalkhati_check_string_concat_properly_calculates_size,
    test_aalkhati_check_if_my_string_c_string_changes_size,
    test_aalkhati_my_string_at_correctly_returns_address,
    test_aalkhati_extraction_returns_correct_size,
    test_aalkhati_insertion_prints_c_string_correctly,
    test_aalkhati_extraction_copies_correctly_from_file,
    test_aalkhati_my_string_compare_returns_0,
    test_aalkhati_compare_returns_greater_than_0,
    test_aalkhati_compare_returns_less_than_0,
    test_aalkhati_concat_allocates_additional_memory,
    test_aalkhati_concat_returns_success,
    test_aalkhati_concat_returns_success_with_empty_string,
    test_aalkhati_string_empty_returns_false_on_a_nonempty_string,
    test_aalkhati_string_empty_returns_true_on_an_empty_string,
    test_aalkhati_init_c_str_resize,
    test_aalkhati_push_back_allocates_additional_memory,
    test_aalkhati_returns_NULL_at_out_of_bounds_index
    
};
int number_of_functions = sizeof(tests) / sizeof(tests[0]); int i;
char buffer[500];
int success_count = 0;
int failure_count = 0;
for(i=0; i<number_of_functions; i++) {
if(tests[i](buffer, 500) == FAILURE) {
printf("FAILED: Test %d failed miserably\n", i); printf("\t%s\n", buffer);
failure_count++;
} else {
 printf("\t%s\n", buffer); success_count++;
} }
printf("Total number of tests: %d\n", number_of_functions); printf("%d/%d Pass, %d/%d Failure\n", success_count,
number_of_functions, failure_count, number_of_functions); return 0;
}
*/
