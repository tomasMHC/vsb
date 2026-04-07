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

// Time interval between two measurements converted to ms
int timeval_diff_to_ms( timeval *t_before, timeval *t_after )
{
    timeval l_res;
    timersub( t_after, t_before, &l_res );
    return 1000 * l_res.tv_sec + l_res.tv_usec / 1000;
}

TYPE *merge( TYPE *arr1, TYPE *arr2, int lenA, int lenB ) {
    TYPE *result = new TYPE [ lenA + lenB ];
    int i = 0, j = 0, k = 0;
    while ( i<lenA && j<lenB ) {
        if ( arr1[ i ] < arr2[ j ] )
            result[ k++ ] = arr1[ i++ ];
        else
            result[ k++ ] = arr2[ j++ ];
    }
    while ( i < lenA )
        result[ k++ ] = arr1[ i++ ];
    while ( j < lenB )
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

TYPE* sort_and_merge(int threads_cnt, TYPE* l_my_array, int l_my_length) {
    std::vector<pthread_t>threads(threads_cnt);
    std::vector<TaskPart>tasks;
    tasks.reserve(threads_cnt);

    int base_length = l_my_length / threads_cnt;
    int extra_length = l_my_length % threads_cnt;
    int current_from = 0;
    for ( int i = 0; i < threads_cnt; i++ ) {
        int current_length = base_length + ( i < extra_length ? 1 : 0 );
        tasks.emplace_back( i , current_from, current_length, l_my_array );
        current_from += current_length;
    }
    timeval t_before, t_after;
    gettimeofday( &t_before, NULL );

    for (int i = 0; i < threads_cnt; i++) {
        pthread_create(&threads[i], nullptr, my_thread, (void*)&tasks[i]);
    }

    for (int i = 0; i < threads_cnt; i++) {
        pthread_join(threads[i], nullptr);
    }
    gettimeofday( &t_after, NULL );

    printf( "-*-*-*-* Sorting with %d threads is done in %d ms. *-*-*-*-*-\n", threads_cnt, timeval_diff_to_ms( &t_before, &t_after ) );

    // Merging sorted arrays (chunks)
    TYPE* result = nullptr;
    int result_len = 0;
    gettimeofday( &t_before, NULL );

    for (int i = 0; i < threads_cnt; i++) {
        TYPE* chunk = tasks[i].m_data + tasks[i].m_from;
        int len = tasks[i].m_length;

        if (result == nullptr) {
            // first chunk becomes the initial result
            result = new TYPE[len];
            memcpy(result, chunk, len * sizeof(TYPE));
            result_len = len;
        } else {
            TYPE* merged = merge(result, chunk, result_len, len);
            delete[] result;
            result = merged;
            result_len += len;
        }
    }
    gettimeofday( &t_after, NULL );
    printf( "Merging is done in %d ms.\n", timeval_diff_to_ms( &t_before, &t_after ) );
    
    return result;
}

void print_array(TYPE* arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void check_arrays_equal(TYPE* arr1, TYPE* arr2, int length) {
    for (int i = 0; i < length; i++) {
        if (arr1[i] != arr2[i]) {
            printf("!!! Arrays differ at index %d: %d != %d !!!\n", i, arr1[i], arr2[i]);
            return;
        }
    }
    printf("-*-*-*-* Arrays are equal. *-*-*-*-*\n");
} 
bool check_sorting(TYPE* arr, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (arr[i+1] < arr[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    int process_1_threads = 1;
    int process_2_threads = 4;
    
    // The number of elements must be used as program argument
    if ( argc != 3 ) 
    { 
        printf( "Specify number of elements and thread count.\n" );
        return 0; 
    }

    int l_my_length = atoi( argv[ 1 ] );
    if ( l_my_length < LENGTH_LIMIT ) 
    { 
        printf( "The number of elements must be at least %d.\n", LENGTH_LIMIT ); 
        return 0; 
    }
    int thread_cnt = atoi( argv[ 2 ]);
    if (thread_cnt < 1) {
        printf("Thread count must be >0\n");
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

    // Sort and merge with different thread counts
    TYPE* result1 = sort_and_merge(1, l_my_array, l_my_length);
    TYPE* result2 = sort_and_merge(thread_cnt, l_my_array, l_my_length);
    // print_array(result1, l_my_length);
    // print_array(result2, l_my_length);
    printf("Array 1: %s\n", check_sorting(result1, l_my_length) ? "sorted" : "not sorted");
    printf("Array 2: %s\n", check_sorting(result2, l_my_length) ? "sorted" : "not sorted");

    check_arrays_equal(result1, result2, l_my_length);
    delete[] l_my_array;
    delete[] result1;
    delete[] result2;
    return 0;
}
