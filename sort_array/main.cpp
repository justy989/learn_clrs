#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "sorts.hpp"

#include <iostream>
#include <algorithm>

int main()
{
    uint32_t seed = 1337;
    size_t n = 5000;

    cout << "Generating list of " << n << " random unique values with seed " << seed << endl;

    // generate 50 ints, copy them for best and worst input
    auto average_input = utils::generate_unique<int>( seed, n );
    decltype(average_input) best_input ( average_input );
    decltype(average_input) worst_input ( average_input );

    // best input is already sorted
    std::sort( best_input.begin(), best_input.end() );

    // worst input is reverese-sorted
    std::sort( worst_input.begin(), worst_input.end(),
               [](int i, int j){return i > j;} );


    using test_case_lambda = utils::test< decltype(average_input) >::case_func;
    using test_check_lambda = utils::test< decltype(average_input) >::check_func;

    // create our lambdas for each case, capture vectors by copying
    test_case_lambda is = [](decltype(average_input) input){ sorts::insertion_sort(input); return std::ref(input); };
    test_case_lambda ms = [](decltype(average_input) input){ sorts::merge_sort(input); return std::ref(input); };

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
    
    // create the tests and run them
    utils::test<decltype(average_input)> is_test ( "Insertion Sort"s,
                                                   is,
                                                   best_input,
                                                   average_input,
                                                   worst_input,
                                                   check_correctness );

    utils::test<decltype(average_input)> ms_test ( "Merge Sort"s,
                                                   ms,
                                                   best_input,
                                                   average_input,
                                                   worst_input,
                                                   check_correctness );

    is_test.run();
    ms_test.run();

    return 0;
}
