#include <iostream>
#include <math.h>

using namespace std;

bool is_prime(int number)
{
  if ( number < 2 ) return false;
	if ( number == 2 ) return true;
	if ( number % 2 == 0 ) return false;

	for ( size_t i = 3, last = (size_t)(double)sqrt(number); i <= last; i += 2 )
		if ( number % i == 0 )
			return false;

	return true;
}

int main()
{
    int number;
    int aux = 0;

    cout << "Write the upper limit number" << endl;
    cin >> number;

    for (int i = 2; i < number; i++)
        if (is_prime(i))
        {
            ++aux;
        }
    cout <<"Total of prime numbers: " << aux << endl;

    is_prime(number);

    return 0;
}