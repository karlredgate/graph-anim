
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char **argv ) {
    int v;
    int array[1024];

    int i = 0;
    while ( scanf("%d", &v) != EOF ) {
        array[i++] = v;
        if ( i > 1023 ) break;
    }

    print_array( array, i );
    printf( "------------\n" );
    quicksort( array, i );
    print_array( array, i );
}

/* vim: set autoindent expandtab sw=4 : */
