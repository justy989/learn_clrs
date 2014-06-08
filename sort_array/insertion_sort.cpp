#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "sorts.hpp"

#include <iostream>
#include <algorithm>

int main()
{
    uint32_t seed = 1337;
    size_t n = 500;

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

    // create our lambdas for each case
    test_case_lambda best_case = [&best_input](){ sorts::insertion_sort(best_input); return std::ref(best_input); };
    test_case_lambda average_case = [&average_input](){ sorts::insertion_sort(average_input); return std::ref(average_input); };
    test_case_lambda worst_case = [&worst_input](){ sorts::insertion_sort(worst_input); return std::ref(worst_input); };

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

    // print generated input
    cout << "Generated input:" << endl;

    for( auto elem : average_input ){
        cout << elem << " ";
    }

    cout << endl;
    
    // create the test and run it
    utils::test<decltype(average_input)> is ( "Insertion Sort"s,
                                              best_case,
                                              average_case,
                                              worst_case,
                                              check_correctness );

    is.run();

    return 0;
}
