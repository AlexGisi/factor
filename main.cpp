/*
 * Notes
 * Non-primes:
 *  - 6750399
 */

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include "Factorer.h"

using namespace std;
using namespace chrono;

/*
 * Generate random numbers that have from digit_min to digit_max
 * digits, one number per digit-class. Filter prime numbers and those
 * divisible by two.
 */
std::vector<mpz_class> gen_number_set() {
    vector<mpz_class> set;
    int digit_min = 5;
    int digit_max = 50;

    for (int i = digit_min; i <= digit_max; ) {
        mpz_class candidate = Factorer::rand_digits(i);
        if (!Factorer(candidate).is_prime() && !(candidate % 2 == 0)) {
            set.push_back(candidate);
            i++;
        }
    }

    return set;
}

void print_number_set() {
    std::vector<mpz_class> nums = gen_number_set();

    for(auto& n : nums)
        cout << n << ' ';
}

void time_fac_func(Factorer& factorer, mpz_class (Factorer::*function)() const) {
    auto start = high_resolution_clock::now();
    cout << (factorer.*function)();
    cout << '\t';

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << duration.count() << '\t';
}

void profile(const vector<mpz_class>& nums) {
    cout << "Number\tNaive Factor\tNaive microseconds\tPollard Factor\tPollard microseconds" << endl;
    for(const mpz_class& n : nums) {
        cout << n << '\t';
        Factorer fac(n);
        time_fac_func(fac, &Factorer::naive);
        time_fac_func(fac, &Factorer::pollard);
        cout << endl;
    }
}

std::vector<mpz_class> load_nums() {
    mpz_class to_add;
    string read;
    std::vector<mpz_class> ret;
    ifstream infile("list2.txt");
    if(!infile.is_open())
        throw std::runtime_error("Could not open file.");

    while (infile >> read) {
        to_add.set_str(read, 10);
        ret.push_back(to_add);
    }

    return ret;
}

int main() {
    vector<mpz_class> nums = load_nums();
    profile(nums);

    // print_number_set();

    return 0;
}
