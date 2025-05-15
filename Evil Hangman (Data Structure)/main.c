#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "my_string.h"
#include "generic_vector.h"
#include "AVL_tree.h"

#define MAX_WORD 30

GENERIC_VECTOR *func_dictionary( void ) ;
Boolean resume_game( void ) ;
Boolean running_total( void ) ;
char get_ch( void ) ;
void clear_keyboard_buffer( void ) ;
void hangman_game( void ) ;

int main( int argc, char *argv[] )
{

    do {
        GENERIC_VECTOR *dictionary = func_dictionary() ; // Allocating 30 generic vector's and put each word length in the correct generic vector
        GENERIC_VECTOR largest_family = NULL ;
        TREE hTree = avl_tree_init_default() ;
        MY_STRING word_key = my_string_init_default() ;
        MY_STRING guess_list = my_string_init_c_string( " " ) ;
        MY_STRING word_family = my_string_init_default() ;
        int word_length, number_of_guesses, bool_running_total, i ;
        char current_guess ;

        do {

            printf( "How many letters in the words yo want? " ) ; // Prompt word-length
            scanf( "%d", &word_length ) ;
            clear_keyboard_buffer() ;

        } while ( word_length <= 2 || word_length >= MAX_WORD ) ;
        
        do {

            printf( "How many guesses do you want to guess? " ) ; // Prompt for the user how many guesses they he/she want
            scanf( "%d", &number_of_guesses ) ;
            clear_keyboard_buffer() ;

        } while (  number_of_guesses<= 0 || number_of_guesses > 26 ) ;
        
        bool_running_total = running_total() ;


        for ( i = 0; i < word_length; i++ )
            my_string_push_back( word_key, '-' ) ; // Outputting word keys the same number of the word-length

        

        do {

            printf( "You have %d guess(es) remaining\nLetters used: ", number_of_guesses ) ;
            my_string_insertion( guess_list, stdout ) ;

            printf( "\nCurrent word: ") ;
            my_string_insertion( word_key, stdout ) ;

            do {

                current_guess = get_ch() ;

            } while ( check_if_used( guess_list, current_guess ) ) ;

            my_string_push_back( guess_list, current_guess) ;
            my_string_push_back( guess_list, ',' ) ;
            my_string_push_back( guess_list, ' ' ) ;

           
        

            if ( bool_running_total )
                printf( "Running total of the number of words remaining:\n" ) ;

            for ( i = 0; i < generic_vector_get_size( dictionary[word_length] ); i++ ) {

                get_word_key_value( word_key, word_family, generic_vector_at( dictionary[word_length], i ), current_guess ) ;
                avl_tree_push( hTree, word_family, generic_vector_at( dictionary[word_length], i ) ) ;

            }

            largest_family = avl_tree_get_largest_family( hTree, bool_running_total ) ;
            generic_vector_destroy( &( dictionary[word_length] ) ) ;
            dictionary[word_length] = generic_vector_init_default( my_string_assignment, my_string_destroy ) ;

            for ( i = 0; i < generic_vector_get_size( largest_family ); i++ ) {

                generic_vector_push_back( dictionary[word_length], generic_vector_at( largest_family, i ) ) ;

            }

            get_word_key_value( word_key, word_family, generic_vector_at( dictionary[word_length], 0 ), current_guess ) ;

            if ( my_string_compare( word_key, word_family ) == 0 ) {

                printf( "\nIncorrect. The word does not include any %c's\n\n", current_guess ) ;
                number_of_guesses-- ;

            }

            my_string_assignment( &word_key, word_family ) ;

            generic_vector_destroy( &largest_family ) ;
            avl_tree_destroy( &hTree ) ;
            my_string_destroy( &word_family ) ;
            word_family = my_string_init_default();
            hTree = avl_tree_init_default() ;

            if ( number_of_guesses == 0 ) {

                printf( "You lose!\nThe word was: " ) ;
                my_string_insertion( generic_vector_at( dictionary[word_length], 0), stdout ) ;
                printf( "\n\n" ) ;
                break ;

            }

            if ( my_string_compare( generic_vector_at( dictionary[word_length], 0 ), word_key ) == 0 ) {

                if ( generic_vector_get_size( dictionary[word_length] ) == 1) {

                    printf( "You win!\nThe word was: ");
                    my_string_insertion( generic_vector_at( dictionary[word_length], 0), stdout ) ;
                    printf( "\n\n" ) ;
                    break ;

                }

            }

        } while ( number_of_guesses > 0 ) ;


        avl_tree_destroy( &hTree ) ;
        my_string_destroy( &word_key ) ;
        my_string_destroy( &guess_list ) ;
        my_string_destroy( &word_family ) ;
        for ( i = 0; i < MAX_WORD; i++ ) generic_vector_destroy( &dictionary[i] ) ;
        free( dictionary ) ;


    } while ( resume_game() ) ;

    return 0 ;

}

GENERIC_VECTOR *func_dictionary( void )
{
    GENERIC_VECTOR *hgVector = ( GENERIC_VECTOR * ) malloc( MAX_WORD * sizeof( GENERIC_VECTOR ) ) ;
    MY_STRING hString = NULL ;
    FILE *fp ;
    int i ;

    fp = fopen( "dictionary.txt", "r" ) ;

    if ( fp == NULL )
        exit( 1 ) ;

    for ( i = 0; i < MAX_WORD; i++ )
    { // Allocating space for every word length

        hgVector[i] = generic_vector_init_default( my_string_assignment, my_string_destroy ) ;

        if ( hgVector[i] == NULL )
            exit( 1 ) ;

    }

    hString = my_string_init_default() ;

    if ( hString == NULL )
        exit( 1 ) ;

    while ( my_string_extraction( hString, fp ) ) {

        if ( my_string_get_size( hString ) < 30 ) {

            if ( !generic_vector_push_back( hgVector[my_string_get_size( hString )], ( Item ) hString ) ) // Putting every word length in the correct generic vector
                exit( 1 ) ;

        }

    }

    my_string_destroy( &hString ) ;
    fclose( fp ) ;

    return hgVector ;
}

Boolean resume_game( void ) {
    // Prompt the user to play again

    char c ;

    printf( "Would you like to play again? (y for yes) (n for no)" ) ;
    scanf( "%c", &c ) ;
    clear_keyboard_buffer() ;

    c = tolower( c ) ;

    if ( !isalpha( c ) || ( isalpha( c ) && c != 121 && c != 110 ) ) {

        return resume_game() ;

    }

    return FALSE ;

}

Boolean running_total( void ) {

    char ch ;

    printf( "Would you like a running total of the number of words remaining? (y/n) " ) ;
    scanf( "%c", &ch ) ;
    clear_keyboard_buffer() ;

    ch = tolower( ch ) ;

    

        return ch ;

    }








char get_ch( void ) {
    // Prompt the user to guess a character
    char c ;

    printf( "\nGuess a character: " ) ;
    scanf( "%c", &c ) ;
    clear_keyboard_buffer() ;

    if ( isalpha( c ) ) {

        c = tolower( c ) ;

    } else {

        return get_ch() ;

    }

    return c ;

}

void clear_keyboard_buffer( void ) {

    char c ;

    do {

        scanf( "%c", &c) ;

    } while ( c != '\n' ) ;

    return ;
}






