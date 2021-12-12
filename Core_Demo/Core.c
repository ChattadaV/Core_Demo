/* 
 * File: Core.c
 * Copy: Copyright (c) 2021 Chattada Viriyaphap
 * BlazerID: chattada
 * 
 * Vers: 1.0.0 12/10/2021 GCM - Original Coding
 * Desc: Code for implementing prototypes found in betalib.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Core.h"

/* Name: int file_read( char file_name[], char contents[] )
 * Desc: contents[] will be a string with a \0.
 */
int file_read( char file_name[], char contents[] ) { 
    FILE *input;
    int count;
    char chunk;
    
    input = fopen( file_name, "r");
    
    if (input != NULL) {
        // file exists
        while ((fscanf(input, "%c", &chunk) != EOF) && (count < chunk_length_max - 1)) { // EOF means End of File // chunk_length_max - 1 to reserve last argument for contents[count] = '\0'
            contents[count] = chunk;
            count++;
        }
        fclose(input);
    } else {
        // file does not exist
        printf("Error: %s does not exist!\n", file_name);
    }    
    contents[count] = '\0'; // guarantees a valid string
    return( 0 );
}

/* Name: int read_line( FILE *input, char line[] )
 * Desc: reads one line at a time from a file based on \n.  line[] will be a 
 * string with a \0.
 */
int file_read_line( FILE *input, char line[] ) {     
    // stop at EOF (End of File) or \n (new line) or when we have read too many chars
    // instead of a file_name, we are passing a file pointer
    char chunk;
    int count;
    
    if (input != NULL) {
        // file exists
        while ((fscanf(input, "%c", &chunk) != EOF) && (chunk != '\n') && (count < chunk_length_max -1)) {
            line[count] = chunk;
            count++;
            // leave the file open so no fclose
        }
    } else {
        // file does not exist
        printf("Error: Invalid file pointer!\n");
    }
    line[count] = '\0';
    return( count );
}

/* Name: int char_find( char contents[], int contents_length, char search, int locations[])
 * Desc: 
 */
int char_find( char contents[], int contents_length, char search, int locations[]) {

    
    return( 0 );
}

/* Name: int string_find( char contents[], char search[], int locations[])
 * Desc: 
 */
int string_find( char contents[], char search[], int locations[]) {
    // content is the string to search in
    // search is the string to search for
    // must have '\0' (end of string)
    //Ex: contents = "banana", search = "na" -> 2 (first n) and 4 (second n) 
    // Ex: contents = "IEEE MEETING", search = "EE" -> 1 (first E) 6 (second E)
    // case sensitive for now
    int contents_length;
    int search_length;
    int contents_index;
    int search_index;
    int match; // flag
    int count;
    
    contents_length = string_length(contents);
    search_length = string_length(search);
    contents_index = 0;
    search_index = 0;
    match = 1; // initial flag
    count = 0;
    
    if (contents_length <= 0) {
        printf("Error: No valid contents string!\n");
    } else if (search_length <= 0) {
        printf("Error: No valid search string!\n");
    } else if (contents_length < search_length) {
        printf("Error: contents string is shorter than your search string!\n");
    } else {
        while ((contents_index < contents_length - search_length + 1) && (count < n_max)) { // only loop through what is needed
            match = 1; // assume true
            search_index = 0;
            while ((match == 1) && (search_index < search_length)) {
                // compare characters
                if (contents[contents_index + search_index] == search[search_index]) {
                    // have a match
                    search_index++;
                } else {
                    // different -> no match
                    match = 0;
                }
            }
            if (match ==1) {
                // found a match and need to store it
                locations[count] = contents_index;
                count++;
                contents_index = contents_index + search_index;
            } else {
                contents_index++;
            }
        }
    }    
    return( count );
}

/* Name: int string_split( char contents[], char delimiter, char chunks[][chunk_length])
 * Desc: 
 */
int string_split( char contents[], char delimiter, char chunks[][chunk_length_max]) {
    int contents_index;
    int results;
    int chunks_index; // "word" or string index
    int chunk_index; // "character" index of a particular word or string
    
    // results = 0; // number of chunks found
    contents_index = 0;
    chunks_index = 0;
    chunk_index = 0;
    
    while ((contents[contents_index] != '\0') && (chunks_index < chunk_count_max)) {
        // look for delimiter
        if (contents[contents_index] == delimiter) {
            // found a new chunk
            chunks[chunks_index][chunk_index] = '\0'; // make sure we use strings
            chunks_index++; // move on to the next word
            chunk_index = 0; // first char of the next word
        } else {
            if (chunks_index < (chunk_length_max - 1)) {
                // append to the old/existing chunk
                chunks[chunks_index][chunk_index] = contents[contents_index];
                chunk_index++; // move on to the next character                
            } else {
                // do nothing
            }
        }
        contents_index++;
    }
    chunks[chunks_index][chunk_index] = '\0'; // make sure last string is terminated
    
    return( chunks_index + 1 );
}

/* Name: int string_compare( char const first[], char const second[], case_sensitivity_type sensitivity )
 * Desc: 
 */
int string_compare( char const first[], char const second[], case_sensitivity_type sensitivity ) {
    // first and second must be strings
    int first_length;
    int second_length;
    int shortest_length;
    int index;
    int results;
    char first_char;
    char second_char;
    
    first_length = string_length(first);
    second_length = string_length(second);
    
    index = 0;
    results = 0;
    
    if (first_length < second_length) {
        shortest_length = first_length;
    } else {
        shortest_length = second_length;
    }
    
    if (sensitivity == case_sensitive) {
        while ((index < shortest_length) && (results == 0)) {
            if (first[index] < second[index]) {
                // first word (shorter) comes before second word
                results = -1;
            } else if (first[index] > second[index]) {
                // first word (longer) comes after second word                
                results = 1;
            } else {
                // keep on matching
                results = 0;
            }
            index++;
        }
        // check again because Ex: Ham is not the same as Hamster even though they both have 'ham' in their names
        if (results == 0) {
            if (first_length < second_length) {
                // first (shorter) comes before second
                results = -1;
            } else if (first[index] > second[index]) {
                // first word (longer) comes after second word                
                results = 1;
            } else {
                // guarantees that the two strings are equal
                results = 0;
            }
        }
    } else if (sensitivity == case_insensitive) {
        while ((index < shortest_length) && (results == 0)) {
            first_char = first[index];
            second_char = second[index];
            
            if ((first_char >= 65) && (first_char <= 90)) {
                // first_char is upper-case (refer to ASCII character code)
                first_char = first_char + 32; // convert from upper to lower case
            } 
            if ((second_char >= 65) && (second_char <= 90)) {
                // second_char is upper-case (refer to ASCII character code)
                second_char = second_char + 32; // convert from upper to lower case
            }
            if (first_char < second_char) {
                // first (shorter) comes before second
                results = -1;
            } else if (first_char > second_char) {
                // first word (longer) comes after second word                
                results = 1;
            } else {
                // keep on matching
                results = 0;
            }
            index++;
        }  
        if (results == 0) {
            if (first_length < second_length) {
                // first (shorter) comes before second
                results = -1;
            } else if (first_length > second_length) {
                // first word (longer) comes after second word
                results = 1;
            } else {
                // guarantees that the two strings are equal
                results = 0;
            }
        }
    } else {
        printf("Error: Should not reach this! Unhandled case_sensitivity!\n");
    }
    
    return( results );
}

/* Name: string_length( char const source[] )
 * Desc: Find the length of the string
 */
int string_length( char const source[] ) {
    int results;
    
    results = 0;
    
    while (source[results] != '\0') { // \0 means end of string
        results++;
    }
    
    return( results );    
}

/* Name: string_upper( char destination[], char const source[] )
 * Desc: Convert lower case characters to upper case
 */
int string_upper( char destination[], char const source[] ) {
    // convert from lower to upper case -> -32 (refer to ASCII character code)
    int results;
    int index;
    
    results = 0;
    index = 0;
    
    while (source[index] != '\0') {
        if ((source[index] >= 97) && (source[index] <= 122)) {
            // the character is lower-case (refer to ASCII character code)
            // convert to upper-case
            destination[index] = source[index] - 32;
            results++;
        } else {
            // the character is upper-case (refer to ASCII character code)
            // no need to convert (the character is already upper-case)
            destination[index] = source[index]; // no change
        }
        index++;
    }
    destination[index] = '\0'; // last character (not included in the loop)
    return( results );    
}

/* Name: string_lower( char destination[], char const source[] )
 * Desc: Convert upper case characters to lower case
 */
int string_lower( char destination[], char const source[] ) {
    // convert from upper to lower case -> +32 (refer to ASCII character code)
    int results;
    int index;
    
    results = 0;
    index = 0;
    
    while (source[index] != '\0') {
        if ((source[index] >= 65) && (source[index] <= 90)) {
            // the character is upper-case (refer to ASCII character code)
            // convert to lower-case
            destination[index] = source[index] + 32;
            results++;
        } else {
            // the character is lower-case (refer to ASCII character code)
            // no need to convert (the character is already lower-case)
            destination[index] = source[index]; // no change
        }
        index++;
    }
    destination[index] = '\0'; // last character (not included in the loop)
    return( results );    
}


/* Name: int export_int2Darray(int array[n_max][m_max], int n, int m, char *filename, char *delimiter)
 * Desc: 
 */
int export_int2Darray(int array[n_max][m_max], int n, int m, char *filename, char *delimiter) {
   return( 0 );    
}

/* Name: int export_double2Darray(double array[n_max][m_max], int n, int m, char *filename, char *delimiter)
 * Desc: 
 */
int export_double2Darray(double array[n_max][m_max], int n, int m, char *filename, char *delimiter) {
   return( 0 );    
}

/* Name: int export_char2Darray(char array[n_max][m_max], int n, int m, char *filename, char *delimiter)
 * Desc: 
 */
int export_char2Darray(char array[n_max][m_max], int n, int m, char *filename, char *delimiter) {
    return( 0 );    
}

/* Name: int export_string2Darray(char array[n_max][m_max], int n, int m, char *filename, char *delimiter)
 * Desc: 
 */
int export_string2Darray(char array[n_max][m_max][chunk_length_max], int n, int m, char *filename, char *delimiter) {
    return( 0 );    
}