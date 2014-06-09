#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "find_max.hpp"

#include <iostream>

using namespace utils;
using namespace std;

int main()
{
    uint32_t seed = 1337;
    size_t n = 5000;

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
    test_case_fn dac_fn = [](const input& input){ return find::dac_find_max_subarray(input); };

    test_check_fn check_correctness = [](const input& input,
                                         const output& output){
        auto correct_ans = find::dac_find_max_subarray( input );
        return ( correct_ans.sum == output.sum &&
                 correct_ans.left == output.left &&
                 correct_ans.right == output.right );
    };

    using case_info = std::vector< test<input, output>::case_info >;

    // create cases
    case_info dac_cases {
        { "Average Case: n lg n", deltas }
    };

    // construct and run tests
    test<input, output> dac_test { "DAC Find Max SubArray"s,
                                   dac_fn,
                                   check_correctness,
                                   std::move(dac_cases) };

    dac_test.run();

    cout << endl;

    return 0;
}
