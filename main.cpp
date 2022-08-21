/*
 * Notes
 * Non-primes:
 *  - 6750399
 */

#include <iostream>
#include <limits>
#include "Factorer.h"

using namespace std;

int main() {
    /*
    Factorer f(70534908);
    std::vector<mpz_class> factors = f.prime_factors(&Factorer::pollard);
    for (auto& fac : factors)
        cout << fac << endl;
    */
    Factorer f(6);
    mpz_class ret = f.pollard();
    cout << ret << endl;

    return 0;
}
