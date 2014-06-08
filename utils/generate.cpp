#include "generate.hpp"

#include <random>

template < typename T >
std::vector<T> utils::generate_unique( uint32_t seed, size_t n, T increment )
{
    std::vector<T> gen( n );
    std::mt19937 mt( seed );
    std::uniform_int_distribution<> dist( 0, n - 1 );

    T value {};

    // setup the array with incrementing values
    for( size_t i = 0; i < n; ++i ){
        gen[ i ] = value;
        value += increment;
    }

    // swap random elements
    for( size_t i = 0; i < n; ++i ){
        auto swap_index = dist( mt );

        T hold = gen[ i ];
        gen[ i ]  = gen[ swap_index ];
        gen[ swap_index ] = hold;
    }

    return gen;
}

