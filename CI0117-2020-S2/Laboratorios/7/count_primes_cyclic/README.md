
Scheduling guiado (guided):

El tipo de scheduling guiado es similar al tipo de scheduling dinámico. OpenMP nuevamente divide las iteraciones en chunks . Cada hilo ejecuta un fragmento de iteraciones y luego solicita otro fragmento hasta que no haya más fragmentos disponibles.

El tipo de scheduling guiado es apropiado cuando las iteraciones están mal equilibradas entre sí. Los chunks iniciales son más grandes porque reducen los gastos generales. Los fragmentos más pequeños llenan el programa hacia el final del cálculo y mejoran el equilibrio de carga. Este tipo de scheduling es especialmente apropiado cuando se produce un equilibrio de carga deficiente hacia el final del cálculo.

Ejemplo de un programa que utiliza directivas OpenMP con Scheduling guiado:

    #include <unistd.h>
    #include <stdlib.h>
    #include <omp.h>
    #include <stdio.h>
    #define THREADS 4
    #define N 16

    int main ( ) {
 
        int i;
    #pragma omp parallel for schedule(guided) num_threads(THREADS)
    for (i = 0; i < N; i++) {
        /* wait for i seconds */
        sleep(i);

        printf("Thread %d has completed iteration %d.\n",
    omp_get_thread_num( ), i);
        }

    /* all threads done */
    printf("All done!\n");
    return 0;
    }

Tabla comparativa de sheduling:

| Cantidad de Numeros | Cantidad de hilos | static,1       | static,N/2      | static,N        | dynamic,1      | dynamic, N/2   | dynamic,N      | guided,1       | guided, N/2    | guided,N       |
|---------------------|-------------------|----------------|-----------------|-----------------|----------------|----------------|----------------|----------------|----------------|----------------|
| 100                 | 4                 | 29,83 msec     | 27,48 msec      | 29,89 msec      | 35,62 msec     | 43,82 msec     | 34,75 msec     | 28,23 msec     | 17,28 msec     | 5,86 msec      |
| 1000                | 4                 | 2,21 msec      | 34,25 msec      | 10,04 msec      | 19,75 msec     | 7,20 msec      | 2,42 msec      | 15,16 msec     | 13,22 msec     | 4,23 msec      |
| 10000               | 4                 | 8,52 msec      | 15,95 msec      | 3,40 msec       | 15,26 msec     | 3,39 msec      | 30,08 msec     | 32,63 msec     | 33,61 msec     | 25,66 msec     |
| 100000              | 4                 | 19,03 msec     | 36,85 msec      | 25,77 msec      | 34,58 msec     | 15,72 msec     | 73,22 msec     | 43,73 msec     | 14,36 msec     | 18,01 msec     |
| 1000000             | 4                 | 191,96 msec    | 235,65 msec     | 208,26 msec     | 216,03 msec    | 169,36 msec    | 186,22 msec    | 170,11 msec    | 168,49 msec    | 186,12 msec    |
| 10000000            | 4                 | 3 549,97 msec  | 3 896,71 msec   | 3 749,54 msec   | 3 339,35 msec  | 3 170,01 msec  | 3 185,79 msec  | 3 251,89 msec  | 3 133,42 msec  | 3 585,01 msec  |
| 100000000           | 4                 | 95 555,61 msec | 120 577,43 msec | 121 167,86 msec | 75 842,71 msec | 74 848,55 msec | 77 555,25 msec | 76 819,33 msec | 76 373,93 msec | 78 791,72 msec |msec | 76 819,33 msec | 76 373,93 msec | 78 791,72 msec |119 175,24 msec | 116 869,03 msec |

Comentario:

El objetivo de la scheduling dinámico / guiado es mejorar la distribución del trabajo en el caso de que no cada iteración del ciclo contenga la misma cantidad de trabajo.

Segun esta estadística, podemos concluir que el mejor resultado de tiempos obtenidos es para scheduling guided. Esto puede ser porque la diferencia con el tipo de scheduling dinámico en el tamaño de los fragmentos. El tamaño de un fragmento es proporcional al número de iteraciones no asignadas dividido por el número de subprocesos. Por tanto, el tamaño de los chunks disminuye.

Haciendo un conteo de la cantidad de veces de mejor tiempo se obtiene que:

Static obtiene 4 veces mejores tiempos.

Dynamic obtiene 7 veces mejores tiempo.

Guided obtiene 10 veces mejores tiempo.



