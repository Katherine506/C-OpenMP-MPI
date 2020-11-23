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
    int under_limit = 2;
    int upper_limit = 0;

 if (argc >= 2) {
    upper_limit = (size_t)strtoul(argv[1], NULL, 10);
} 
    int aux = 0;
    int my_id, num_processes;
    double start, end, time = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);

    start = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

  if (my_id == 0) //proceso root
    {
       for(int i=1; i<num_processes; i++){
        MPI_Send(&under_limit, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&upper_limit, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
       }
    }

    if (my_id != 0)
    {
        MPI_Recv(/*buf*/&under_limit, /*count*/1 , /*datatype */MPI_INT, /*source*/0,  /*tag*/ 0 , /*comm*/ MPI_COMM_WORLD, /*status*/&status);
        MPI_Recv(/*buf*/&upper_limit, /*count*/1 , /*datatype */MPI_INT, /*source*/0,  /*tag*/ 0 , /*comm*/ MPI_COMM_WORLD, /*status*/&status);

    }

    int origin = under_limit + (upper_limit - under_limit)*my_id/num_processes;
    int destine = under_limit + (upper_limit - under_limit)*(my_id+1)/num_processes;

    start = MPI_Wtime();// inicia el conteo

    for (int i = origin; i < destine; i++)
    {
        if (is_prime(i))
        {
            ++aux;
        }
    } 

    if (my_id != 0)
    {
        MPI_Send(&aux, /*count*/ 1 , /*dest*/ MPI_INT, 0, 0 , MPI_COMM_WORLD);
    }

     if (my_id == 0){
        int total = aux;
        for(int i = 1; i < num_processes; i++){
            MPI_Recv(/*buf*/&aux, /*count*/1 , /*datatype */MPI_INT, /*source*/i,  /*tag*/ 0 , /*comm*/ MPI_COMM_WORLD, /*status*/&status);
            total += aux;
        }
         
    end = MPI_Wtime();
    time = end - start;

    cout << "\n" << total << " primes found in range " << "[ " << under_limit << ", " << upper_limit << "] " << "in " << time << "s with " << num_processes << " processess "<< endl;
     
    }
    
    MPI_Finalize();

    return 0;
}