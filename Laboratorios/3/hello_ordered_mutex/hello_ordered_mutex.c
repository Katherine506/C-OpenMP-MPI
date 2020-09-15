/*Ejercicio 2 [hello_ordered_mutex]
Modifique la solución del ejemplo de Hello World con espera activa visto en clase para obligar a los hilos de ejecución a saludar en orden en la salida estándar. Use una colección de mutexes, uno por cada thread. Haga que únicamente el thread 0 tenga su mutex habilitado. Cuando el thread 0 ha saludado, habilita el mutex del siguiente thread y así sucesivamente. Corra su solución y mida el tiempo de ejecución. ¿Permite este mecanismo de control de concurrencia resolver este problema de manera predecible?*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, finish;  

typedef struct {
    size_t message;
    size_t position; //chose_thread
    size_t next_thread;
    pthread_mutex_t mutex_position;
} shared_message_t;

typedef struct {
    size_t thread_num;
    shared_message_t *shared_message;

} thread_data_t;


void* hello_world(void* args){

    thread_data_t* data = (thread_data_t*) args;

    size_t thread_num = data->thread_num;
    shared_message_t* shared_message = data->shared_message;

    //bloqueo el mutex
    pthread_mutex_lock(&shared_message->mutex_position);

    if (thread_num == shared_message->position) {
        shared_message->message = 2021;
    }
    printf("Hello world from thread number # %zu. The message is: %zu\n", thread_num, shared_message->message);

    ++shared_message->position;
    
    //desbloqueo el mutex
    pthread_mutex_unlock(&shared_message -> mutex_position);

    return NULL;    
    
}


int main(int argc, char* arg[]) {
    clock_gettime(CLOCK_REALTIME, &start);
    size_t thread_count = (size_t)strtoul(arg[1], NULL, 10);
    //Array de mutex
    pthread_mutex_t* mutex_array = malloc((size_t)(thread_count * sizeof(pthread_mutex_t)));

    size_t chosen_thread  = 0;

    if (argc >= 3) {
        thread_count = (size_t)strtoul(arg[1], NULL, 10);
        chosen_thread = (size_t)strtoul(arg[2], NULL, 10);

        if (chosen_thread < 0 || chosen_thread>= thread_count) {
            fprintf(stderr, "Error, invalid parameters\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Error, invalid number of parameters\n");
        return 1;
    }
    
    pthread_t* threads = malloc((size_t)(thread_count * sizeof(pthread_t)));

    shared_message_t* shared_message = (shared_message_t*)calloc(1, sizeof(shared_message_t));

    shared_message->message = 2020;
    shared_message->position= chosen_thread;
    shared_message->next_thread = 0;

    thread_data_t* thread_data_list = malloc((size_t)(thread_count * sizeof(thread_data_t)));
    
    //pthread_mutex_init(&mutex_array[0], /*attr*/ NULL);

    for (size_t i = 0; i < thread_count; i++)
    {
        //if (i == 0)
        //{
           // pthread_mutex_init(&mutex_array[i], NULL);
        //}
        //else
       // {
            pthread_mutex_init(&mutex_array[i], NULL);
        //}
    }

     //crea el thread
    for (size_t i = 0; i < thread_count; ++i) {
	pthread_create(&threads[i], NULL, hello_world, (void*) &shared_message);  
     
    }

    //Join
    for (size_t i = 0; i < thread_count; ++i) 
    {
        pthread_join(threads[i], NULL);
    }

    printf("Hello world from main thread\n");

    //Liberar memoria
    
    free(threads);
    free(shared_message);
    free(thread_data_list);
    free(mutex_array);
    for(size_t i = 0; i< thread_count; ++i){
        pthread_mutex_destroy(&shared_message->mutex_position);
    }

    clock_gettime(CLOCK_REALTIME, &finish);
    unsigned int time_taken = finish.tv_nsec - start.tv_nsec;
    double total_time = (double) time_taken/1000000000;
    printf("Time taken: %fs\n", total_time);
    return 0;


    return 0;
}