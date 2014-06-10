#include "matrix.hpp"

using namespace mat;

matrix mat::bf_multiply( const matrix& a,
                         const matrix& b )
{
    std::size_t n = a.size();
    matrix c(n, std::vector<double>(n, 0.0));

    for(std::size_t i = 0; i < n; ++i){
        for(std::size_t j = 0; j < n; ++j){

            c[i][j] = 0.0;

            for(std::size_t k = 0; k < n; ++k){
                c[i][j] += c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

matrix mat::strassen_multiply( const matrix& a, const matrix& b )
{
    std::size_t n = a.size();

    matrix c(n, std::vector<double>(n, 0.0));

    c[0][0] = a[0][0] + b[0][0];

    return c;
}

