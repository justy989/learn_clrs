#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "find_max.hpp"

#include <iostream>

using namespace utils;
using namespace std;

int main()
{
    uint32_t seed = 1337;
    size_t n = 1000;

    cout << "Generating list of " << n << " random unique values with seed " << seed << endl << endl;

    // generate 50 ints, copy them for best and worst input
    auto values = generate_unique<int>( seed, n );
    
    using input = decltype(values);
    using output = find::answer<int>;

    input deltas ( values.size() - 1, 0 );

    // calculate the deltas between values. use these for input
    for( size_t i = 0; i < deltas.size(); i++){
        deltas[i] = values[ i + 1 ] - values[ i ];
    }

    using test_case_fn = test< input, output >::case_func;
    using test_check_fn = test< input, output >::check_func;

    // create lambdas for test use
    test_case_fn k_fn = [](const input& input){ return find::kadane_find_max_subarray(input); };
    test_case_fn dac_fn = [](const input& input){ return find::dac_find_max_subarray(input); };
    test_case_fn bf_fn = [](const input& input){ return find::bf_find_max_subarray(input); };

    test_check_fn check_correctness = [](const input& input,
                                         const output& output){
        auto correct_ans = find::kadane_find_max_subarray( input );
        return ( correct_ans.sum == output.sum &&
                 correct_ans.left == output.left &&
                 correct_ans.right == output.right );
    };

    using case_info = std::vector< test<input, output>::case_info >;

    // create cases
    case_info dac_cases {
        { "Average Case: n lg n", deltas }
    };

    case_info kadane_cases {
        { "Average Case: n", deltas }
    };

    case_info bf_cases {
        { "Average Case: n^3", deltas }
    };

    // construct and run tests
    test<input, output> k_test { "Kadane Find Max SubArray"s,
                                 k_fn,
                                 check_correctness,
                                 std::move(kadane_cases) };

    test<input, output> dac_test { "DAC Find Max SubArray"s,
                                   dac_fn,
                                   check_correctness,
                                   std::move(dac_cases) };

    test<input, output> bf_test { "Brute Force Find Max SubArray"s,
                                  bf_fn,
                                  check_correctness,
                                  std::move(bf_cases) };

    k_test.run();
    dac_test.run();
    bf_test.run();

    cout << endl;

    return 0;
}
