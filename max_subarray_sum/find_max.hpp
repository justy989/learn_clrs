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
    answer<T> kadane_find_max_subarray( const std::vector<T>& input );

}

#include "find_max.cpp"

#endif
