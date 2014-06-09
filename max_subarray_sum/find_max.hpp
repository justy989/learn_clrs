#ifndef FIND_MAX_H
#define FIND_MAX_H

#include <utility>
#include <vector>

namespace find{

    template < typename T >
    struct answer{
        std::size_t left;
        std::size_t right;
        T sum;
    };

    template < typename T >
    answer<T> bf_find_max_subarray( const std::vector<T>& input );

    template < typename T >
    answer<T> kadane_find_max_subarray( const std::vector<T>& input );

    template < typename T >
    answer<T> impl_dac_find_max_crossing_subarray( const std::vector<T>& input,
                                                   size_t left,
                                                   size_t mid,
                                                   size_t right );

    template < typename T >
    answer<T> impl_dac_find_max_subarray( const std::vector<T>& input,
                                          size_t left,
                                          size_t right );

    template < typename T >
    answer<T> dac_find_max_subarray( const std::vector<T>& input );

}

#include "find_max.cpp"

#endif
