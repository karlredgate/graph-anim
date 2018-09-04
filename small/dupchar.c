
#include <stdlib.h>
#include <stdio.h>

static void
record( uint32_t *seen, unsigned char c ) {
    int bit = c & 0x1F; // (1<<6)-1
    int element = c >> 5;
    seen[element] |= (1 << bit);
}

static int
char_seen( uint32_t *seen, unsigned char c ) {
    printf( "record %c\n", c );
    int bit = c & 0x1F; // (1<<6)-1
    int element = c >> 5;
    return ( seen[element] & (1 << bit) ) != 0;
}

unsigned char
firstdup( unsigned char *s ) {
    uint32_t seen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };;
    while ( *s != '\0' ) {
        if ( char_seen(seen, *s) ) return *s;
        record( seen, *s++ );
    }
    return '\0';
}

int main( int argc, char **argv ) {
    unsigned char string[1024];
    if ( scanf("%[^\n]", string) == 0 ) {
        printf( "error\n" );
        exit( 1 );
    }

    printf( "dup is '%c'\n", firstdup(string) );
}

/* vim: set autoindent expandtab sw=4 : */
