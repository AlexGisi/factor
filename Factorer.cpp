//
// Created by Alex Gisi on 5/17/22.
//

#include <stdexcept>
#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <functional>
#include <queue>
#include "Factorer.h"

Factorer::Factorer(ull num) : num(num) { }

/*
 * Use the Euclidean algorithm to find the GCD.
 * b should be bigger than a.
 */
ull Factorer::gcd(ull a, ull b) {
    if (b < a) throw std::invalid_argument("Argument b should be greater than a");

    ull r = 0, old_r;
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
bool Factorer::is_prime(ull n) const {
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    ull m = 0, q = num-1;
    do {
        q = q / 2;
        m++;
    } while (q % 2 == 0);

    // Choose witnesses uniformly from (1, n).
    ull* pot_witnesses = new ull[n];
    bool* is_witness = new bool[n];
    for(int i = 0; i < n; i++) {
        pot_witnesses[i] = rand_range(2, num-1);
        is_witness[i] = true;
    }

    // Test potential witnesses.
    for(int i = 0; i < n; i++) {
        if(fast_exp(pot_witnesses[i], q, num) == 1) {
            is_witness[i] = false;
        }
    }

    for(int i = 0; i < m; i++) {
        ull n_i = ( (ull) pow(2, i) * q ) % num;
        for(int j = 0; j < n; j++)
            if( fast_exp(pot_witnesses[j], n_i, num) == num-1)
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

ull Factorer::fast_exp(ull a, ull x, ull n) {
    ull res = a;
    for(int i = 0; i < x-1; i++) {
        res = (res * a) % n;
    }
    return res;
}

ull Factorer::naive() const {
    for(ull i=2; i <= (ull) sqrt(num); i++) {
        if(num % i == 0)
            return i;
    }
    throw std::runtime_error("No factor found.");
}

std::vector<ull> Factorer::prime_factors(FactorizerFn f) const {
    std::vector<ull> prime_factors;
    std::queue<ull> q;

    q.push(num);
    while (!q.empty()) {
        Factorer factorer(q.front());
        if (factorer.is_prime()) {
            prime_factors.push_back(q.front());
        } else {
            std::vector<ull> decomp = factors(f, q.front());
            q.push(decomp[0]);
            q.push(decomp[1]);
        }
        q.pop();
    }

    return prime_factors;
}

std::vector<ull> Factorer::factors(Factorer::FactorizerFn f, ull n) {
    std::vector<ull> factors;

    ull fac = std::invoke(f, Factorer(n));
    ull other = n / fac;
    factors.push_back(fac);
    factors.push_back(other);

    return factors;
}
