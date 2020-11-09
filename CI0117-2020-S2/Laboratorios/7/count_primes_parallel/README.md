Tiempos de ejecucion usando perf stat para el programa paralelo.

| Cantidad de Numeros | Cantidad de hilos | Tiempo Serial   | Tiempo Paralelo |
|---------------------|-------------------|-----------------|-----------------|
| 100                 | 4                 | 1,53 msec       | 39,18 msec      |
| 1000                | 4                 | 1,26 msec       | 36,18 msec      |
| 10000               | 4                 | 1,68 msec       | 30,95 msec      |
| 100000              | 4                 | 12,76 msec      | 40,85 msec      |
| 1000000             | 4                 | 244,15 msec     | 160,56 msec     |
| 10000000            | 4                 | 6 239,47 msec   | 2 925,34 msec   |
| 100000000           | 4                 | 157 847,12 msec | 72 554,64 msec  |