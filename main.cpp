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

    Factorer f(70534908);
    std::vector<ull> factors = f.prime_factors(&Factorer::naive);
    for (auto& fac : factors)
        cout << fac << endl;

    /*
    Factorer f(29);
    cout << f.is_prime() << endl;
     */

    return 0;
}
