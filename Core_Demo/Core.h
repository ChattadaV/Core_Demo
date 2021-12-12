/* 
 * File: Core.c
 * Copy: Copyright (c) 2021 Chattada Viriyaphap
 * BlazerID: chattada
 * 
 * Vers: 1.0.0 12/10/2021 GCM - Original Coding
 * Desc: Header file for aggregating core functions 
 */

#if !defined core_defined

#define char_count_max 20
#define chunk_count_max 20
#define chunk_length_max 1000
#define line_length_max 1000
#define n_max 100
#define m_max 100

typedef enum 
    { ascending, descending }
order_type;

typedef enum
    { case_sensitive, case_insensitive }
case_sensitivity_type;

typedef enum
    { data, count }
column_name_type;

int file_read( char file_name[], char contents[] );
int file_read_line( FILE *input, char line[] );

int char_find( char contents[], int contents_length, char search, int locations[]);

int string_find( char contents[], char search[], int locations[]);
int string_split( char contents[], char delimiter, char chunks[][chunk_length_max]);
int string_compare( char const first[], char const second[], case_sensitivity_type sensitivity );
int string_length( char const source[] );
int string_upper( char destination[], char const source[] );
int string_lower( char destination[], char const source[] );

int export_int2Darray(int array[n_max][m_max], int n, int m, char *filename, char *delimiter);
int export_double2Darray(double array[n_max][m_max], int n, int m, char *filename, char *delimiter);
int export_char2Darray(char array[n_max][m_max], int n, int m, char *filename, char *delimiter);
int export_string2Darray(char array[n_max][m_max][chunk_length_max], int n, int m, char *filename, char *delimiter);

#define core_defined

#endif
