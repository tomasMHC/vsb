#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct data_vlakna
    {
        char jmeno[ 128 ];
        int tout;
    };

    void *vlakno( void *t_arg) {
        data_vlakna *data = ( data_vlakna * ) t_arg;
        for ( int i = 0; i < data -> tout; i++){
            printf( "Ja som vlakno %i %s\n", i, data->jmeno );
            sleep( 1 );
        }
        return 0;
    }

int main() {
    pthread_t pth1, pth2;
    data_vlakna dv1 = { "pat", 5};
    data_vlakna dv2 = { "mat", 10};

    pthread_create(&pth1, nullptr, vlakno, ( void *) &dv1);
    strcpy( dv1.jmeno, "karel");
    pthread_create(&pth2, nullptr, vlakno, ( void *) &dv2);
    // std::thread v2( vlakno, &dv2 );
    pthread_join( pth1, nullptr);
    // v2.join();

    printf( "main konci\n");

}
