//
// Created by Alex Gisi on 5/17/22.
//

#ifndef FACTOR_FACTORER_H
#define FACTOR_FACTORER_H

using ull = unsigned long long;


class Factorer {
public:
    explicit Factorer(ull num);

    static ull gcd(ull a, ull b);
    [[nodiscard]] bool is_prime(int n = 5) const;

    static ull rand_range(ull min, ull max);
    static ull fast_exp(ull a, ull x, ull n);

private:
    ull num;
};


#endif //FACTOR_FACTORER_H
