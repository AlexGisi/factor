//
// Created by Alex Gisi on 5/17/22.
//

#include <stdexcept>
#include <random>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
#include <functional>
#include <queue>
#include "Factorer.h"

Factorer::Factorer(mpz_class num) : num(std::move(num)) { }

/*
 * Use the Euclidean algorithm to find the GCD.
 * b should be bigger than a.
 */
mpz_class Factorer::gcd(mpz_class a, mpz_class b) {
    if (b < a) {
        mpz_class temp;
        temp = b;
        b = a;
        a = temp;
    }

    mpz_class r = 0, old_r;
    do {
        old_r = r;
        r = b % a;
        b = a;
        a = r;
    } while (r != 0);

    return old_r;
}

/*
 * Probabilistically check if num prime using the Miller-Rabin test.
 * n: number of potential witnesses to test.
 */
bool Factorer::is_prime(int n) const {
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    int m = 0;
    mpz_class q = num-1;
    do {
        q = q / 2;
        m++;
    } while (q % 2 == 0);

    if(!q.fits_uint_p())
        throw std::runtime_error("q did not fit uint");

    // Choose witnesses uniformly from (1, n).
    mpz_class* pot_witnesses = new mpz_class [n];
    bool* is_witness = new bool[n];
    for(int i = 0; i < n; i++) {
        pot_witnesses[i] = rand_range(2, num-1);
        is_witness[i] = true;
    }

    // Test potential witnesses.
    for(int i = 0; i < n; i++) {
        if(fast_exp(pot_witnesses[i], q.get_ui(), num) == 1) {
            is_witness[i] = false;
        }
    }

    for(int i = 0; i < m; i++) {
        mpz_class n_i = (big_power(2, i) * q ) % num;
        for(int j = 0; j < n; j++)
            if( fast_exp_mpz(pot_witnesses[j], n_i, num) == num-1)
                is_witness[j] = false;
    }

    for(int i=0; i < n; i++)
        if(is_witness[i])
            return false;

    return true;  // Most likely prime.
}

// Ref:
// https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range/20136256#20136256
ull Factorer::rand_range(ull min, ull max) {
    std::random_device r_dev;
    std::mt19937_64 generator(r_dev());
    std::uniform_int_distribution<ull> distr(min, max);

    return distr(generator);
}

/*
 * Uniform random generation on [min, max].
 * TODO: Consider re-using the random device.
 */
mpz_class Factorer::rand_range(const mpz_class& min, const mpz_class& max) {
    mpz_t ret;
    mpz_class ret_class;
    mpz_init(ret);
    gmp_randstate_t randstate;
    std::random_device r_dev;
    mpz_class f_max;

    gmp_randinit_mt(randstate);
    gmp_randseed_ui(randstate, r_dev());

    f_max = max-min+1;

    mpz_urandomm(ret, randstate, f_max.get_mpz_t());

    ret_class = mpz_class (ret);
    ret_class += min;

    mpz_clear(ret);

    return ret_class;
}

/*
 * Efficiently exponentiate modulo some integer n. GMP can do this for us.
 */
mpz_class Factorer::fast_exp(const mpz_class& a, const unsigned long x, const mpz_class& m) {
    mpz_t ret;
    mpz_class ret_class;

    mpz_init(ret);
    mpz_powm_ui(ret, a.get_mpz_t(), x, m.get_mpz_t());

    ret_class = mpz_class (ret);

    mpz_clear(ret);
    return ret_class;
}

/*
 * Efficiently exponentiate modulo some integer n. GMP can do this for us.
 */
mpz_class Factorer::fast_exp_mpz(const mpz_class& a, const mpz_class& x, const mpz_class& m) {
    mpz_t ret;
    mpz_class ret_class;

    mpz_init(ret);

    mpz_powm(ret, a.get_mpz_t(), x.get_mpz_t(), m.get_mpz_t());

    ret_class = mpz_class (ret);

    mpz_clear(ret);
    return ret_class;
}

/*
 * The most naive way to find a factor.
 */
mpz_class Factorer::naive() const {
    mpz_class i = mpz_class (2);
    mpz_class max_factor = sqrt(i);
    for(i=2; i <= max_factor; i++) {
        if(num % i == 0)
            return i;
    }
    throw std::runtime_error("No factor found.");
}

/*
 * Breadth-first search the tree of factors, finding factors at each fork with the member function f
 * which returns a factor.
 */
std::vector<mpz_class> Factorer::prime_factors(FactorizerFn f) const {
    std::vector<mpz_class> prime_factors;
    std::queue<mpz_class> q;

    q.push(num);
    while (!q.empty()) {
        Factorer factorer(q.front());
        if (factorer.is_prime()) {
            prime_factors.push_back(q.front());
        } else {
            std::vector<mpz_class> decomp = factors(f, q.front());
            q.push(decomp[0]);
            q.push(decomp[1]);
        }
        q.pop();
    }

    return prime_factors;
}

/*
 * Find two factors of a number n using the factorizing function f, which returns
 * a mpz_class.
 */
std::vector<mpz_class> Factorer::factors(Factorer::FactorizerFn f, const mpz_class& n) {
    std::vector<mpz_class> factors;

    mpz_class fac = std::invoke(f, Factorer(n));
    mpz_class other = n / fac;
    factors.push_back(fac);
    factors.push_back(other);

    return factors;
}

/*
 * Pollard's p-1 algorithm.
 */
mpz_class Factorer::pollard() const {
    mpz_class a;
    unsigned long i;

    // Choose a in range (1, num).
    a = rand_range(2, num);
    std::cout << a << std::endl;

    // We could get *very* lucky.
    if (gcd(a, num) != 1) return gcd(a, num);

    mpz_class last_a = a;
    for (i = 1; ; i++) {
        mpz_class a_i = fast_exp(last_a, i, num);
        std::cout << a_i << std::endl;

        mpz_class g = gcd(a_i - 1, num);
        if (g != 1 && g != num)
            return g;
        else if (g == 1 || g == num)
            throw std::runtime_error("No factor found");
    }
}

mpz_class Factorer::big_power(unsigned long base, unsigned long exp) {
    mpz_t mpz_base;
    mpz_t ret;
    mpz_class ret_class;

    mpz_init(ret);
    mpz_pow_ui(ret, mpz_base, exp);
    ret_class = mpz_class (ret);

    mpz_clear(ret);

    return ret_class;
}
