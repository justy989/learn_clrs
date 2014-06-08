#ifndef GENERATE_H
#define GENERATE_H

#include <vector>
#include <cstdint>

namespace utils{

    template < typename T >
    std::vector<T> generate_unique( uint32_t seed, std::size_t n, T increment = 1 );

}

#include "generate.cpp"

#endif
