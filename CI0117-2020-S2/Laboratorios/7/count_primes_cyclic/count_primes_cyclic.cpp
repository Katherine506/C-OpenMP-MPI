#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <math.h>

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
    omp_set_num_threads(4);
    int number;
    int aux = 0;

    cout << "Write the upper limit number" << endl;
    cin >> number;

#pragma omp parallel for default(shared) schedule(runtime) reduction(+: aux) 
    for (int i = 2; i < number; i++)
    {
        if (is_prime(i))
        {
            ++aux;
        }
    }
    cout << "Total of prime numbers: " << aux << endl;

    is_prime(number);

    return 0;
}