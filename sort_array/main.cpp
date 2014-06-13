#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "sort.hpp"

#include <iostream>
#include <algorithm>

using namespace sort;

int main()
{
    uint32_t seed = 1337;
    size_t n = 5000;

    cout << "Generating list of " << n << " random unique values with seed " << seed << endl << endl;

    // generate 50 ints, copy them for best and worst input
    auto average_input = utils::generate_unique<int>( seed, n );

    using input = decltype(average_input);
    using output = input;
    using test = utils::test< input, output >;
    using case_info = std::vector< test::case_info >;


    input best_input { average_input };
    input worst_input { average_input };

    // best input is already sorted
    std::sort( best_input.begin(), best_input.end() );

    // worst input is reverese-sorted
    std::sort( worst_input.begin(), worst_input.end(),
               [](int i, int j){return i > j;} );


    // create our lambdas for each case, capture vectors by copying
    test::case_func b_fn = [](input input){ bubble_sort(input); return std::move(input); };
    test::case_func is_fn = [](input input){ insertion_sort(input); return std::move(input); };
    test::case_func ms_fn = [](input input){ merge_sort(input); return std::move(input); };

    // create our lambda to check correctness
    test::check_func check_correctness = []( const input& input, const output& output )
    {
        if( input.size() != output.size() ){
            return false;
        }

        for(size_t i = 1; i < output.size(); ++i){
            if( output[i - 1] > output[i] ){
                return false;
            } 
        }

        return true;
    };


    // setup case info. Match Case id to input
    case_info b_cases {
        { "Best Case: n", best_input },
        { "Average Case: (n/2)^2", average_input },
        { "Worst Case: n^2", worst_input },            
    };

    case_info is_cases {
        { "Best Case: n", best_input },
        { "Average Case: (n/2)^2", average_input },
        { "Worst Case: n^2", worst_input },            
    };

    case_info ms_cases {
        { "Average Case: n lg n", average_input },
    };

    
    // create the tests and run them
    test b_test { "Bubble Sort"s,
                   b_fn,
                   check_correctness,
                   std::move(b_cases) };

    test is_test { "Insertion Sort"s,
                   is_fn,
                   check_correctness,
                   std::move(is_cases) };

    test ms_test { "Merge Sort"s,
                   ms_fn,
                   check_correctness,
                   std::move(ms_cases) };

    b_test.run();
    is_test.run();
    ms_test.run();

    return 0;
}
