
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_SIZE 1024

typedef int (*heap_comparator)( void *, void * );

typedef struct heap heap;
struct heap {
    int capacity;
    int size;
    int *items;
};

static int
last_index( heap *this ) {
    return this->size - 1;
}

#define LEFT_CHILD_INDEX(parent)   ((parent*2)+1)
#define RIGHT_CHILD_INDEX(parent)  ((parent*2)+2)
#define PARENT_INDEX(child)        ((child-1)>>1)

static int
left_child( heap *this, int parent ) {
    return this->items[ LEFT_CHILD_INDEX(parent) ];
}

static int
right_child( heap *this, int parent ) {
    return this->items[ RIGHT_CHILD_INDEX(parent) ];
}

static int
parent( heap *this, int child ) {
    return this->items[ PARENT_INDEX(child) ];
}

static int
has_left_child( heap *this, int parent ) {
    return LEFT_CHILD_INDEX(parent) < this->size;
}

static int
has_right_child( heap *this, int parent ) {
    return RIGHT_CHILD_INDEX(parent) < this->size;
}

static int
has_parent( heap *this, int child ) {
    // PARENT_IDEX(child) >= 0
    return child > 0;
}

void
print_heap( heap *this, char *prefix ) {
    printf( "%02d> ", this->size );
    int line = 0;
    int increment = 2;
    for ( int i = 0 ; i < this->size ; i++ ) {
        printf( "%d ", this->items[i] );
        if ( i == line ) {
            printf( "\n    " );
            line += increment;
            increment *= 2;
        }
    }
    printf( " < %s\n", prefix );
}

heap *
heap_create() {
    heap *this = malloc( sizeof (heap) );
    this->capacity = INITIAL_SIZE;
    this->items = calloc( INITIAL_SIZE, sizeof (int) );
    this->size = 0;
    return this;
}

int
heap_not_empty( heap *this ) {
    return this->size > 0;
}

static void
swap( heap *this, int i, int j ) {
    int *items  = this->items;
    int tmp  = items[i];
    items[i] = items[j];
    items[j] = tmp;
}

static void
sift( heap *this ) {
    int *items = this->items;
    int index = 0;

    while ( has_left_child(this, index) ) {
        int child = LEFT_CHILD_INDEX(index);
        if ( has_right_child(this, index) ) {
            int right = RIGHT_CHILD_INDEX(index);
            if ( items[right] < items[child] )  child = right;
        }
        if ( items[index] < items[child] ) return;
        swap( this, index, child );
        index = child;
    }
}

static void
bubble( heap *this ) {
    int *items = this->items;
    int index = last_index(this);

    while ( has_parent(this, index) ) {
        int parent = PARENT_INDEX(index);
        if ( items[parent] <= items[index] ) return;
        swap( this, parent, index );
        index = parent;
    }
}

int
heap_deletemin( heap *this ) {
    if ( this->size == 0 ) return -1;
    int value = this->items[0];
    this->items[0] = this->items[ this->size - 1 ];
    this->size--;
    sift( this );
    return value;
}

void
heap_add( heap *this, int value ) {
    // error check - size and copy
    printf( " ===> ADD : %d\n", value );
    this->items[ this->size ] = value;
    this->size++;
    bubble( this );
}

int main( int argc, char **argv ) {
    int v;
    heap *h = heap_create();

    while ( scanf("%d", &v) != EOF ) {
        heap_add( h, v );
    }

    int previous = 0;
    while ( heap_not_empty(h) ) {
        v = heap_deletemin( h );
        printf( "[ %d ]\n", v );
        if ( v < previous ) printf( "error\n" );
        // print_heap( h, "DEL" );
        previous = v;
    }
}

/* vim: set autoindent expandtab sw=4 : */
