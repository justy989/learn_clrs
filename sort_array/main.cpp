#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "sort.hpp"

#include <iostream>
#include <algorithm>

using namespace utils;
using namespace sort;

int main()
{
    uint32_t seed = 1337;
    size_t n = 5000;

    cout << "Generating list of " << n << " random unique values with seed " << seed << endl << endl;

    // generate 50 ints, copy them for best and worst input
    auto average_input = generate_unique<int>( seed, n );
    decltype(average_input) best_input ( average_input );
    decltype(average_input) worst_input ( average_input );

    // best input is already sorted
    std::sort( best_input.begin(), best_input.end() );

    // worst input is reverese-sorted
    std::sort( worst_input.begin(), worst_input.end(),
               [](int i, int j){return i > j;} );


    using test_case_lambda = test< decltype(average_input) >::case_func;
    using test_check_lambda = test< decltype(average_input) >::check_func;

    // create our lambdas for each case, capture vectors by copying
    test_case_lambda is_fn = [](decltype(average_input) input){ insertion_sort(input); return std::move(input); };
    test_case_lambda ms_fn = [](decltype(average_input) input){ merge_sort(input); return std::move(input); };

    // create our lambda to check correctness
    test_check_lambda check_correctness = []( const std::vector<int>& input )
    {
        for(size_t i = 1; i < input.size(); ++i){
            if( input[i - 1] > input[i] ){
                return false;
            } 
        }

        return true;
    };

    using case_info = std::vector< test<decltype(average_input)>::case_info >;

    // setup case info. Match Case id to input
    case_info is_cases {
        { "Best Case: O(n)", best_input },
        { "Average Case: O((n/2)^2)", average_input },
        { "Worst Case: O(n^2)", worst_input },            
    };

    case_info ms_cases {
        { "Average Case: O(n lg n)", average_input },
    };
    
    // create the tests and run them
    test<decltype(average_input)> is_test ( "Insertion Sort"s,
                                            is_fn,
                                            check_correctness,
                                            std::move(is_cases) );

    test<decltype(average_input)> ms_test ( "Merge Sort"s,
                                            ms_fn,
                                            check_correctness,
                                            std::move(ms_cases) );

    is_test.run();
    ms_test.run();

    return 0;
}
