#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace mat{
    using matrix = std::vector< std::vector< double > >;

    matrix bf_multiply( const matrix& a, const matrix& b );
    matrix strassen_multiply( const matrix& a, const matrix& b );
};

#endif
