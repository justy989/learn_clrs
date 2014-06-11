#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace mat{
    using matrix = std::vector< std::vector< double > >;

    matrix add(const matrix& a, const matrix& b, size_t i, size_t j, size_t n);
    matrix subtract(const matrix& a, const matrix& b, size_t i, size_t j, size_t n);

    matrix bf_multiply( const matrix& a, const matrix& b );
    matrix strassen_multiply( const matrix& a, const matrix& b );
};

#endif
