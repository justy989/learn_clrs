#ifndef SORTS_H
#define SORTS_H

#include <vector>

namespace sorts{
    template < typename T > 
    void insertion_sort( std::vector<T>& input );
}

#include "sorts.cpp"

#endif
