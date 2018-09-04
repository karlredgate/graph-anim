
#include <stdlib.h>

#include "darray.h"

darray *
darray_create( unsigned int entries ) {
    darray * array = malloc( sizeof darray );
    if ( array == NULL ) {
        return NULL;
    }
    array->used = 0;

    if ( entries == 0 ) {
        array->data = NULL;
        array->entries = 0;
        return array;
    }

    array->data = malloc( sizeof (void *) * entries );
    if ( array->data == NULL ) {
        free( array );
        return NULL;
    }

    array->entries = entries;
    return array;
}

void
darray_delete( darray *array ) {
    if ( array == NULL ) return;
    if ( array->data != NULL )  free( array->data );
    free( array );
}

static void
darray_resize( darray *array, int shift ) {
    int entries = array->entries * 2;
    if ( shift > entries ) {
        // should make the multiplier larger
    }
    int size = entries * sizeof (void *);

    // malloc does not zero
    void **buffer = malloc( size );
    if ( buffer == NULL ) {
        // error
    }
    memcpy( buffer + shift, array->data, array->used * sizeof (void *) );
    free( array->data );
    array->data = buffer;
    array->entries = entries;
}

/* vim: set autoindent expandtab sw=4 : */
