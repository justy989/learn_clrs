#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "find_max.hpp"

#include <iostream>

using namespace std;

int main()
{
    uint32_t seed = 1337;
    size_t n = 1000;

    cout << "Find Max Sub Array" << endl;
    cout << "Generating list of " << n << " random unique values with seed " << seed << endl << endl;

    // generate 50 ints, copy them for best and worst input
    auto values = utils::generate_unique<int>( seed, n );
    
    using input = decltype(values);
    using output = find::answer<int>;
    using test = utils::test< input, output >;
    using case_info = std::vector< test::case_info >;


    input deltas ( values.size() - 1, 0 );

    // calculate the deltas between values. use these for input
    for( size_t i = 0; i < deltas.size(); i++){
        deltas[i] = values[ i + 1 ] - values[ i ];
    }


    // create lambdas for test use
    test::case_func k_fn = find::kadane_find_max_subarray<int>;
    test::case_func dac_fn = find::dac_find_max_subarray<int>;
    test::case_func bf_fn = find::bf_find_max_subarray<int>;

    // create lambda for checking correctness
    test::check_func check_correctness = [](const input& input,
                                            const output& output){
        // use quickest algorithm
        auto correct_ans = find::kadane_find_max_subarray( input );
        return ( correct_ans.sum == output.sum &&
                 correct_ans.left == output.left &&
                 correct_ans.right == output.right );
    };


    // create cases
    case_info kadane_cases {
        { "Average Case: n", deltas }
    };

    case_info dac_cases {
        { "Average Case: n lg n", deltas }
    };

    case_info bf_cases {
        { "Average Case: n^3", deltas }
    };


    // construct and run tests
    test k_test { "Kadane"s,
                  k_fn,
                  check_correctness,
                  std::move(kadane_cases) };

    test dac_test { "Divide And Conquer"s,
                    dac_fn,
                    check_correctness,
                    std::move(dac_cases) };

    test bf_test { "Brute Force"s,
                   bf_fn,
                   check_correctness,
                   std::move(bf_cases) };

    k_test.run();
    dac_test.run();
    bf_test.run();

    cout << endl;

    return 0;
}
