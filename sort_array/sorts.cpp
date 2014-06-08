#include "sorts.hpp"

template < typename T > 
void sorts::insertion_sort( std::vector<T>& input )
{
    auto n = input.size();

    // handle simple cases
    if( n <= 1 ){
        return;
    }

    // loop over the input
    for( std::size_t j = 1; j < n; ++j ){

        // save the key and start at the end of the sorted input
        auto key = input[ j ];
        std::size_t i = j - 1;

        // loop while the values are greater than our key
        for( ; 
             i >= 0 && input[ i ] > key;
             --i ){
            // shift over each element
            input[ i + 1 ] = input[ i ];
        }

        // put our key in place
        input[ i + 1 ] = key;
    }
}
