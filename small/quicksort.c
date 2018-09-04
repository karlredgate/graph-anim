
#include <stdlib.h>
#include <stdio.h>

static void
print_array( int *array, int length ) {
    for ( int i = 0 ; i < length ; i++ ) {
        printf( "%d ", array[i] );
    }
    printf( "\n" );
}

static void
swap( int *array, int left, int right ) {
    int tmp = array[left];
    array[left] = array[right];
    array[right] = tmp;
}

static int
partition( int *array, int left, int right, int pivot ) {
    while ( left <= right ) {
        while ( array[left]  < pivot ) left++;
        while ( array[right] > pivot ) right--;
        if ( left <= right )  swap( array, left++, right-- );
    }
    return left;
}

static void
sort_partition( int *array, int left, int right ) {
    if ( left >= right ) return;
    int middle = (left + right) / 2;
    int pivot = array[ middle ];
    int boundary = partition( array, left, right, pivot );
    sort_partition( array, left, boundary - 1 );
    sort_partition( array, boundary, right );
}

void
quicksort( int *array, int length ) {
    sort_partition( array, 0, length-1 );
}

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
