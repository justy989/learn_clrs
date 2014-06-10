#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "matrix.hpp"

#include <iostream>

using namespace std;

struct input{

    input(size_t n) :
        a(n, std::vector<double>(n, 0.0)),
        b(n, std::vector<double>(n, 0.0)) {}

    mat::matrix a;
    mat::matrix b;
};

int main()
{
    uint32_t seed = 1337;
    size_t n = 32;

    cout << "NxN Matrix Multiplication" << endl;
    cout << "Generating 2 " << n << "x" << n << " matricies with seed " << seed << endl << endl;

    // allocate and fill matricies
    input in {n};

    for(size_t i = 0; i < n; ++i){
        in.a[i] = utils::generate_unique<double>( seed, n ); seed++;
        in.b[i] = utils::generate_unique<double>( seed, n ); seed++;
    }


    // aliases
    using output = mat::matrix;
    using test = utils::test< input, output >;
    using case_info = std::vector< test::case_info >;


    // create lambdas for test use
    test::case_func bf_fn = [](const input& in){ return mat::bf_multiply(in.a, in.b); };

    // create lambda for checking correctness
    test::check_func check_correctness = [](const input& input,
                                            const output& output){
        return input.a.size() == output.size(); // lol
    };


    // create cases
    case_info bf_cases {
        { "Average Case: n^3", in }
    };


    // construct and run tests
    test bf_test { "Brute Force"s,
                   bf_fn,
                   check_correctness,
                   std::move(bf_cases) };

    bf_test.run();

    cout << endl;

    return 0;
}
