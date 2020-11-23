#include <iostream>
#include <cstdio>
#include <cstring>
#include <math.h>
#include "mpi.h"

using namespace std;

bool is_prime(int number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;
    for (int i = 3, last = (int)(double)sqrt(number); i <= last; i += 2)
    {
        if (number % i == 0)
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    int bcast_under_limit = 2;
    int bcast_upper_limit = 0;
    int aux = 0; 
    int result = 0;
    int my_id, num_processes;
    double start, end, time = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  if (my_id == 0) //proceso root
    {
        cout << "Write the upper limit number" << endl;
        cin >> bcast_upper_limit;        
    }

    MPI_Bcast(&bcast_under_limit, 1, MPI_INT, /*root*/ 0, MPI_COMM_WORLD); 
    MPI_Bcast(&bcast_upper_limit, 1, MPI_INT, /*root*/ 0, MPI_COMM_WORLD); 

    int origin = bcast_under_limit + (bcast_upper_limit - bcast_under_limit)* my_id/num_processes;
    int destine = bcast_under_limit + (bcast_upper_limit - bcast_under_limit)* (my_id+1)/num_processes;

    start = MPI_Wtime(); 
    for (int i = origin; i < destine; i++)
    {
        if (is_prime(i))
        {
            ++aux;
        }
    } 

    int total = aux;
    MPI_Reduce(/*buf envio*/&aux , /*buf recibido*/&result, /*count*/1 , /*datatype */MPI_INT, /*Operacion*/ MPI_SUM,  /*Root*/ 0 , /*comm*/ MPI_COMM_WORLD);
    total += aux;

    end = MPI_Wtime();
    time = end - start;

    if (my_id == 0)
    {
        cout << "\n\n" << result << " primes found in range " << "[ " << bcast_under_limit << ", " << bcast_upper_limit << "] " << "in "  << time << "s " << " with " << num_processes << " processess "<< endl;
    }

    MPI_Finalize();

    return 0;
}