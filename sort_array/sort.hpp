#ifndef SORTS_H
#define SORTS_H

#include <vector>

namespace sort{
    template < typename T > 
    void insertion_sort( std::vector<T>& input );

    template < typename T >
    void impl_merge( std::vector<T>& input,
                     std::size_t start,
                     std::size_t mid,
                     std::size_t end );

    template < typename T >
    void impl_merge_sort( std::vector<T>& input,
                          std::size_t start,
                          std::size_t end );

    template < typename T >
    void merge_sort( std::vector<T>& input );
}

#include "sort.cpp"

#endif
