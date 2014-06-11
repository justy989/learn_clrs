#include "matrix.hpp"

using namespace mat;

matrix mat::add( const matrix& a, const matrix& b )
{
    std::size_t n = a.size();

    matrix c(n, std::vector<double>(n, 0.0));

    for(std::size_t i = 0; i < n; ++i){
        for(std::size_t j = 0; j < n; ++j){
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    return c;
}

matrix mat::subtract( const matrix& a, const matrix& b )
{
    std::size_t n = a.size();

    matrix c(n, std::vector<double>(n, 0.0));

    for(std::size_t i = 0; i < n; ++i){
        for(std::size_t j = 0; j < n; ++j){
            c[i][j] = a[i][j] - b[i][j];
        }
    }

    return c;
}

matrix mat::bf_multiply( const matrix& a,
                         const matrix& b )
{
    std::size_t n = a.size();
    matrix c(n, std::vector<double>(n, 0.0));

    for(std::size_t i = 0; i < n; ++i){
        for(std::size_t j = 0; j < n; ++j){

            c[i][j] = 0.0;

            for(std::size_t k = 0; k < n; ++k){
                c[i][j] = c[i][j] + ( a[i][k] * b[k][j] );
            }
        }
    }

    return c;
}

matrix mat::strassen_multiply( const matrix& a, const matrix& b )
{
    std::size_t n = a.size();

    if(n == 1){
        return matrix(n, std::vector<double>(n, a[0][0] * b[0][0]));
    }

    // calc the next size down
    std::size_t next_n = n / 2;

    // allocate 2x2 matrices that represent partitioned versions of the ones passed in
    matrix pa[2][2] { { matrix( next_n, std::vector<double>(next_n)), matrix( next_n, std::vector<double>(next_n)) },
                      { matrix( next_n, std::vector<double>(next_n)), matrix( next_n, std::vector<double>(next_n)) } };
    matrix pb[2][2] { { matrix( next_n, std::vector<double>(next_n)), matrix( next_n, std::vector<double>(next_n)) },
                      { matrix( next_n, std::vector<double>(next_n)), matrix( next_n, std::vector<double>(next_n)) } };

    // copy in a and b into the matrix partitions
    for(std::size_t i = 0; i < next_n; ++i){
        for(std::size_t j = 0; j < next_n; ++j){

            std::size_t next_i = i + next_n;
            std::size_t next_j = j + next_n;

            pa[0][0][i][j] = a[i][j];
            pb[0][0][i][j] = b[i][j];

            pa[1][0][i][j] = a[next_i][j];
            pb[1][0][i][j] = b[next_i][j];

            pa[0][1][i][j] = a[i][next_j];
            pb[0][1][i][j] = b[i][next_j];

            pa[1][1][i][j] = a[next_i][next_j];
            pb[1][1][i][j] = b[next_i][next_j];
        }
    }

    // calculate the 7 values
    matrix s[7] {
        strassen_multiply( subtract( pa[0][1], pa[1][1] ), add( pb[1][0], pb[1][1] ) ),
        strassen_multiply( add( pa[0][0], pa[1][1] ),      add( pb[0][0], pb[1][1] ) ),
        strassen_multiply( subtract( pa[0][0], pa[1][0] ), add( pb[0][0], pb[0][1] ) ),
        strassen_multiply( add( pa[0][0], pa[0][1] ),      pb[1][1] ),
        strassen_multiply( pa[0][0],                       subtract( pb[0][1], pb[1][1] ) ),
        strassen_multiply( pa[1][1],                       subtract( pb[1][0], pb[0][0] ) ),
        strassen_multiply( add( pa[1][0], pa[1][1] ),      pb[0][0] )
    };

    // build the answers
    matrix pc[2][2] {
        { add( subtract( add( s[0], s[1] ), s[3] ), s[5] ), add( s[3], s[4] ) },
        { add( s[5], s[4] ), subtract( add( subtract( s[1], s[2] ), s[4] ), s[6] ) }
    };

    // copy them into the big matrix
    matrix c(n, std::vector<double>(n, 0.0));

    for(std::size_t i = 0; i < next_n; ++i){
        for(std::size_t j = 0; j < next_n; ++j){
            std::size_t next_i = next_n + i;
            std::size_t next_j = next_n + j;

            c[i][j]           = pc[0][0][i][j];
            c[next_i][j]      = pc[1][0][i][j];
            c[i][next_j]      = pc[0][1][i][j];
            c[next_i][next_j] = pc[1][1][i][j];
        }
    }

    return c;
}

