#include <iostream>
#include <limits>
#include "Factorer.h"

using namespace std;

int main() {
    // TODO: no input bigger than ull max.
    // https://m.cplusplus.com/reference/limits/numeric_limits/

    Factorer f(67503901);
    cout << f.is_prime() << endl;

    return 0;
}
