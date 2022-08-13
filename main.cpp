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
    // TODO: no input bigger than ull max.
    // https://m.cplusplus.com/reference/limits/numeric_limits/

    /*
    Factorer f(70534908);
    std::vector<ull> factors = f.prime_factors(&Factorer::pollard);
    for (auto& fac : factors)
        cout << fac << endl;
    */

    // TODO: test is_prime.
    mpz_class min_val = mpz_class (0);
    mpz_class max_val = mpz_class (1);
    mpz_class ret = Factorer::rand_range(min_val, max_val);

    cout << ret << endl;

    return 0;
}
