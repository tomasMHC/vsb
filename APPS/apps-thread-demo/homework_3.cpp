#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <random>
#include <time.h>
#include <sys/time.h>

#define rand_min -100000000
#define rand_max 100000000
#define LENGTH_LIMIT 1000

#define TYPE int

int rand_range( int min, int max ) {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( min, max );
    return dis( gen );
}

// Time interval between two measurements converted to ms
int timeval_diff_to_ms( timeval *t_before, timeval *t_after )
{
    timeval l_res;
    timersub( t_after, t_before, &l_res );
    return 1000 * l_res.tv_sec + l_res.tv_usec / 1000;
}

void swap_values( TYPE &a, TYPE &b ) {
    TYPE temp = a;
    a = b;
    b = temp;
}
class TaskPart
{
public:
    int m_id;                 // user thread identification
    int m_from, m_length;     // data range
    TYPE *m_data;             // array
    TaskPart( int t_myid, int t_from, int t_length, TYPE *t_data ) :
        m_id( t_myid ), m_from( t_from ), m_length( t_length ), m_data( t_data ) {}
    
    void selection_sort() {
        int start = m_from;
        int end = m_from + m_length;
        for ( int i = start; i < end - 1; i++ ) {
            int min_idx = i;
            for ( int j = i + 1; j < end; j++ )
                if ( m_data[ j ] < m_data[ min_idx ] )
                    min_idx = j;
            swap_values( m_data[ min_idx ], m_data[ i ] );
        }
        return;
    }
};

TYPE *merge( TYPE *arr1, TYPE *arr2, int length ) {
    TYPE *result = new TYPE [ length ];
    int i = 0, j = 0, k = 0;
    while ( i < length / 2 && j < length - length / 2 ) {
        if ( arr1[ i ] < arr2[ j ] )
            result[ k++ ] = arr1[ i++ ];
        else
            result[ k++ ] = arr2[ j++ ];
    }
    while ( i < length / 2 )
        result[ k++ ] = arr1[ i++ ];
    while ( j < length - length / 2 )
        result[ k++ ] = arr2[ j++ ];
    return result;
}

void *my_thread( void *t_void_arg )
    {
        TaskPart *lp_task = ( TaskPart * ) t_void_arg;

        printf( "Thread %d started from %d with length %d...\n",
            lp_task->m_id, lp_task->m_from, lp_task->m_length );

        lp_task->selection_sort();

        printf( "Sorting in thread %d is done.\n", lp_task->m_id );

        return NULL;
    }


int main(int argc, char **argv) {
        // The number of elements must be used as program argument
    if ( argc != 2 ) 
    { 
        printf( "Specify number of elements, at least %d.\n", LENGTH_LIMIT ); 
        return 0; 
    }
    int l_my_length = atoi( argv[ 1 ] );
    if ( l_my_length < LENGTH_LIMIT ) 
    { 
        printf( "The number of elements must be at least %d.\n", LENGTH_LIMIT ); 
        return 0; 
    }

    // array allocation
    TYPE *l_my_array = new TYPE [ l_my_length ];
    if ( !l_my_array ) 
    {
        printf( "Not enought memory for array!\n" );
        return 1;
    }

    // Initialization of random number generator
    // srand( ( int ) time( NULL ) );
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(rand_min, rand_max);

    printf( "Random numbers generetion started..." );
    for ( int i = 0; i < l_my_length; i++ )
    {
        l_my_array[ i ] = dis(gen);
       if ( !( i % LENGTH_LIMIT ) ) 
        {
            printf( "." ); 
            fflush( stdout );
        }    
    }
    printf("\n");
    
    pthread_t pth1, pth2;
    TaskPart task1( 1, 0, l_my_length / 2, l_my_array );
    TaskPart task2( 2, l_my_length / 2, l_my_length - l_my_length / 2, l_my_array );

    timeval t_before, t_after;
    gettimeofday( &t_before, NULL );

    pthread_create( &pth1, nullptr, my_thread, ( void * ) &task1 );
    pthread_create( &pth2, nullptr, my_thread, ( void * ) &task2 );
    pthread_join( pth1, nullptr );
    pthread_join( pth2, nullptr );

    gettimeofday( &t_after, NULL );

    printf( "Sorting is done in %d ms.\n", timeval_diff_to_ms( &t_before, &t_after ) );

    gettimeofday( &t_before, NULL );
    TYPE *result = merge( task1.m_data + task1.m_from, task2.m_data + task2.m_from, l_my_length );
    gettimeofday( &t_after, NULL );

    printf( "Merging is done in %d ms.\n", timeval_diff_to_ms( &t_before, &t_after ) );

    for ( int i =0 ; i < l_my_length; i++) {
        printf( "%d ", result[ i ] );
    }
    printf("\n");

    // data_vlakna dv1 = { "pat", 5};
    // data_vlakna dv2 = { "mat", 10};

    // pthread_create(&pth1, nullptr, vlakno, ( void *) &dv1);
    // strcpy( dv1.jmeno, "karel");
    // pthread_create(&pth2, nullptr, vlakno, ( void *) &dv2);
    // // std::thread v2( vlakno, &dv2 );
    // pthread_join( pth1, nullptr);
    // // v2.join();

    // printf( "main konci\n");
    delete[] l_my_array;
    delete[] result;
    return 0;
}
