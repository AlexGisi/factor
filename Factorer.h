//
// Created by Alex Gisi on 5/17/22.
//

#include <gmpxx.h>
#include <vector>

#ifndef FACTOR_FACTORER_H
#define FACTOR_FACTORER_H

using ull = unsigned long long;


class Factorer {
typedef mpz_class (Factorer::*FactorizerFn)() const;

public:
    explicit Factorer(mpz_class num);

    static mpz_class gcd(mpz_class a, mpz_class b);
    [[nodiscard]] bool is_prime(int n = 5) const;

    static mpz_class rand_range(const mpz_class& min, const mpz_class& max);
    static ull rand_range(ull min, ull max);

    static mpz_class fast_exp(const mpz_class& a, unsigned long x, const mpz_class& m);
    static mpz_class fast_exp_mpz(const mpz_class& a, const mpz_class& x, const mpz_class& m);

    [[nodiscard]] std::vector<mpz_class> prime_factors(FactorizerFn f) const;

    // Factoring methods return a factor of num.
    [[nodiscard]] mpz_class naive() const;
    [[nodiscard]] mpz_class pollard() const;

private:
    mpz_class num;

    static std::vector<mpz_class> factors(FactorizerFn f, const mpz_class& n);
    static mpz_class big_power(unsigned long base, unsigned long exp);
};


#endif //FACTOR_FACTORER_H
