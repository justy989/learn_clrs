#ifndef MATRIX_H
#define MATRIX_H

#include <cstdint>

namespace mat{
    using uint = uint32_t;
    using element_type = double;
    using matrix = element_type*;

    inline constexpr uint size( uint n ) { return n * n; }

    inline element_type element(const matrix m,
                                uint n,
                                uint i,
                                uint j )
    {
        return m[ (j * n) + i ];
    }

    inline void set( matrix m,
                     uint n,
                     uint i,
                     uint j,
                     element_type value )
    {
        m[ (j * n) + i ] = value;
    }
    
    void add( const matrix a, const matrix b, matrix c, uint n );
    void subtract( const matrix a, const matrix b, matrix c, uint n );

    void bf_multiply( const matrix a, const matrix b, matrix c, uint n );

    void strassen_multiply( const matrix a, const matrix b, matrix c, uint n );
};

#endif
