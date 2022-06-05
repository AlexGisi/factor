//
// Created by Alex Gisi on 5/17/22.
//

#include <vector>

#ifndef FACTOR_FACTORER_H
#define FACTOR_FACTORER_H

using ull = unsigned long long;


class Factorer {
typedef ull (Factorer::*FactorizerFn)() const;

public:
    explicit Factorer(ull num);

    static ull gcd(ull a, ull b);
    [[nodiscard]] bool is_prime(ull n = 5) const;

    static ull rand_range(ull min, ull max);
    static ull fast_exp(ull a, ull x, ull n);

    [[nodiscard]] std::vector<ull> prime_factors(FactorizerFn f) const;

    // Factoring methods return a factor of num.
    [[nodiscard]] ull naive() const;

private:
    ull num;

    static std::vector<ull> factors(FactorizerFn f, ull n);
};


#endif //FACTOR_FACTORER_H
