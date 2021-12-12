/* 
 * File: Core_Driver.c
 * Copy: Copyright (c) 2021 Chattada Viriyaphap
 * BlazerID: chattada
 * 
 * Vers: 1.0.0 12/10/2021 GCM - Original Coding
 * Desc: Driver for testing concepts in Core_Demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Core.h"

void help(void);
int file_read_fgetc( char file_name[], char contents[] );
int file_read_fscanf( char file_name[], char contents[] );
int string_demo( int argc, char** argv );

/* Name: int main(int argc, char** argv)
 * Desc: Drives other functions
 */
int main(int argc, char** argv) {
    int index;
    int results;
    char file_name[20];
    char contents[chunk_length_max]; // from core.h
    int locations[n_max];
    char chunks[chunk_count_max][chunk_length_max];
    
    printf("argc: %d\n", argc);
    for (index = 0; index < argc; index++) {
        printf("argv[ %d ]: %s\n", index, argv[index]);
    }
    
    if ((argc == 2) && (strcmpi(argv[ 1 ], "/string_demo") == 0)) {
        string_demo( argc, argv );
    } else if ((argc == 3) && (strcmpi(argv[ 1 ], "/file_read_fgetc") == 0)) {
        strcpy( file_name, argv[ 2 ] );
        results = file_read_fgetc( file_name, contents );
        // loop through all the chars in contents
/*
        for (index = 0; index < results; index++) {
            printf("%d: %c\n", index, contents[index]);
        }
*/
        printf("%s\n", contents);
    } else if ((argc == 3) && (strcmpi(argv[ 1 ], "/file_read_fscanf") == 0)) {
        strcpy( file_name, argv[ 2 ] );
        results = file_read_fscanf( file_name, contents );
        // loop through all the chars in contents
/*
        for (index = 0; index < results; index++) {
            printf("%d: %c\n", index, contents[index]);
        }
*/
        printf("%s\n", contents);
    } else if ((argc == 4) && (strcmpi(argv[ 1 ], "/string_find") == 0)) {
        results = string_find( argv[ 2 ], argv[ 3 ], locations);
        printf("Count: %d\n", results);
        for (index = 0; index < results; index++) {
            printf("%d: %d\n", index, locations[index]);
        }
    } else if ((argc == 5) && (strcmpi(argv[ 1 ], "/string_compare") == 0)) {
        if (strcmpi(argv[ 4 ], "case_sensitive") == 0) {
            results = string_compare(argv[ 2 ], argv [ 3 ], case_sensitive);
            printf("Results: %d\n", results);
        } else if (strcmpi(argv[ 4 ], "case_insensitive") == 0) {
            results = string_compare(argv[ 2 ], argv [ 3 ], case_insensitive);
            printf("Results: %d\n", results);            
        } else {
            help();
        }        
    } else if ((argc == 4) && (strcmpi(argv[ 1 ], "/string_split") == 0)) {
        results = string_split(argv[ 2 ], argv[ 3 ][ 0 ], chunks);
        printf("Results: %d\n", results);
        for (index = 0; index < results; index++) {
            printf("chunks[ %d ] is %s\n", index, chunks[index]);
        }
    } else {
        help();
    } 
    return (EXIT_SUCCESS);
}

/* 
 * Name: help(void)
 * Desc: Help menu
 * Args: void input
 */
void help(void) {
    printf("==================================================\n");
    printf("File: Core_Driver.c\n");
    printf("Copy: Copyright (c) 2021 Chattada Viriyaphap\n");
    printf("vERS: 1.0.0 12/10/2021 CV - Initial version\n");
    printf("Desc: Core_Demo\n");
    printf("==================================================\n");   
    printf("Usage:\n");
    printf("    /string_demo\n");
    printf("    /file_read_fgetc Sample_Wiki.txt\n");
    printf("    /file_read_fscanf Sample_Wiki.txt\n");
    printf("    /string_find banana na\n");
    printf("    /string_compare Hamster hamster case_sensitive\n");
    printf("    /string_compare Hamster hamster case_insensitive\n");
    printf("    /string_split Viriyaphap,Chattada,C,chattada ,\n");
}

/* Name: file_read_fgetc
 * Desc: uses fgetc to return a character from a file
 * 
 */
int file_read_fgetc( char file_name[], char contents[] ) {
    int current;
    int count;
    FILE *input;

    count = 0;    
    input = fopen( file_name, "r");
    
    if (input != NULL) {
        // file exists
        while ((( current = fgetc( input ) ) > 0 ) && ( count < chunk_length_max - 1) ){
            contents[count] = current;
            count++;
            printf("%d: %c\n", count, current);
        }          
        contents[count] = '\0'; // end of string character
        fclose(input);
    } else {
        // files does not exist
        printf("Error: %s does not exist!\n", file_name);   
    }
    return( count ); // return count if file exists and return 0 if file does not exist
}

/* Name: file_read_fscanf
 * Desc: uses fscanf to return a character from a file
 * 
 */
int file_read_fscanf( char file_name[], char contents[] ) {
    char current;
    int count;
    FILE *input;
    
    count = 0;    
    input = fopen(file_name, "r");
    
    if (input != NULL) {
        // file exists
        while (( fscanf( input, "%c", &current ) != EOF ) && ( count < chunk_length_max - 1)) {
            contents[count] = current;            
            count++;
            printf("%d: %c\n", count, current);
        }
        contents[count] = '\0'; // end of string character
        fclose(input);
    } else {
        // file does not exist
        printf("Error: %s does not exist!\n", file_name);
    }    
    return( count ); // return count if file exists and return 0 if file does not exist}
}

/* 
 * Name: string_demo( int argc, char** argv )
 * Desc: Demonstration of string and character indexing
 * Args: input - argc, argv
 */
int string_demo( int argc, char** argv ) {
    char sample_01[10] = "something";
    char sample_02[10];
    char sample_03[10];
    char sample_04[10];
    
    int n;
    int index;
    int results;
    int done; // flag to exit the application
    
    n = 10;
    index = 0;
    
/*
    // strcpy(sample_02, "Something too long");
    printf("Treated as a string:\n");
    while (sample_01[index] != '\0') { // \0 means end of string
        printf("sample_01[ %d ]: %c\n", index, sample_01[index]);
        index++;
    }
    printf("\n");
    
    index = 0;
    printf("Treated as a string with a fallback plan:\n");
    while ((sample_01[index] != '\0') && (index < n)) { // \0 means end of string
        printf("sample_01[ %d ]: %c\n", index, sample_01[index]);
        index++;
    }
    printf("\n");
    
    printf("Treated as character vector:\n");
    for (index = 0; index < n; index++) {
        printf("sample_01[ %d ]: %c\n", index, sample_01[index]);
    }
*/
    
    done = 0; // initial flag
    
    while (done == 0) {
        printf("Enter a string less than 10 characters (or 'exit'):\n");
        scanf("%s", &sample_03);
        
        if (strcmpi(sample_03, "exit") == 0) {
            done = 1; // exit application
        } else { // continue application
        results = string_upper(sample_04, sample_03);
        printf("%s converts to %s by changing %d characters\n", sample_03, sample_04, results);
        
        results = string_lower(sample_04, sample_03);
        printf("%s converts to %s by changing %d characters\n", sample_03, sample_04, results);
        }
    }    
    return (EXIT_SUCCESS);
}

