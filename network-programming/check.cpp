#include <iostream>
#include <gmp.h>
using namespace std;

int main()
{

    int i;
    int size;

    //cout << "Enter the size of the array: ";
    //cin >> size;
    if (!cin || (size <= 0)) {
        //cout << "Invalid entry. It must be a positive integer." << endl;
    }


    mpz_t *q = new mpz_t[size];

    // Initial array elements to 1
    for (i = 0; i < size; i++) {
        mpz_init_set_str(q[i], "1", 10);
    }

    // Multiply the value by i (So the product will be i)
    for (i = 0; i < size; i++) {
        mpz_mul_ui(q[i], q[i], i);
    }

    // Print them out
    for (i = 0; i < size; i++) {
        //cout << q[i] << endl; 
    }

    delete [] q ;

    return 0;

}
