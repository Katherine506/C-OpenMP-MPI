#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NANOSEC  1000000000L;
/*Estime el tiempo que toma el sistema en crear y destruir un thread. Escriba un programa en C que reciba un número entero T en los argumentos de línea de comandos, el cual indica la cantidad de pruebas a realizar. Si el usuario no especifica este número, asuma T = 1. Seguidamente su programa realiza T pruebas secuenciales. En cada prueba, el thread principal crea un thread secundario, espera a que este termine, y mide la duración que tardan estas dos acciones juntas con resolución de nanosegundos. El thread secundario simplemente ejecuta una función cuyo cuerpo es vacío. Note que las pruebas no se realizan concurrente si no secuencialmente. El thread principal debe reportar una estadística en la salida estándar, que es la duración en segundos de la prueba que tardó menos tiempo. Este dato permite a un programador tener un estimado del tiempo en que tarda el sistema en crear y destruir un hilo de ejecución. La salida podría tener el formato:
Minimum thread creation and destruction time was 0.123456789s among 12345 trials
Sugerencia: Utilice la función clock_gettime para obtener el tiempo inicial y final y calcular la duración.
*/

void* get_thread_time(){
    
    return NULL;
}

int main(int argc, char* arg[]) {

    int thread_count = 1;
    struct timespec start, stop;
    double accum;


    if(argc == 2){
       thread_count = (size_t)strtoul(arg[1], NULL, 10);
      //  printf("argc: %i\n", argc);
    }

    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

   double min_time = 0;
   
    for (size_t i = 0; i < thread_count; ++i) {
        clock_gettime( CLOCK_REALTIME, &start);
        pthread_create(&threads[i], NULL, get_thread_time, NULL);
        clock_gettime( CLOCK_REALTIME, &stop);
    
        accum = stop.tv_nsec - start.tv_nsec;

        if((min_time == 0) || (accum < min_time)){
            min_time  = accum;
        }
        accum = accum/NANOSEC;
       
        
        //printf( "\ntiempo %f\n", accum );
    }

    min_time = min_time/NANOSEC;

    printf( "\nMinimum thread creation and destruction time was %lf among %i trials\n", min_time, thread_count);

    for (size_t i = 0; i < thread_count; ++i) {
        pthread_join(threads[i], NULL);
    }

    free(threads);

    return 0;
}

