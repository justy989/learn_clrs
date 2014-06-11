#include "matrix.hpp"

using namespace mat;

void mat::add( const matrix a, 
               const matrix b, 
               matrix c,
               uint n )
{
    for(uint i = 0; i < n; ++i){
        for(uint j = 0; j < n; ++j){
            set( c, n, i, j,
                 element(a, n, i, j) + element(b, n, i, j) );
        }
    }
}

void mat::subtract( const matrix a, 
                    const matrix b, 
                    matrix c,
                    uint n )
{
    for(uint i = 0; i < n; ++i){
        for(uint j = 0; j < n; ++j){
            set( c, n, i, j,
                 element(a, n, i, j) + element(b, n, i, j) );
        }
    }
}

void mat::bf_multiply( const matrix a,
                       const matrix b,
                       matrix c,
                       uint n )
{
    for(uint i = 0; i < n; ++i){
        for(uint j = 0; j < n; ++j){

            set( c, n, i, j, element_type{} );

            for(uint k = 0; k < n; ++k){
                set( c, n, i, j,
                     element(c, n, i, j) +
                     ( element(a, n, i, k) * element(b, n, k, j) ) );
            }
        }
    }
}

void mat::strassen_multiply( const matrix a, 
                             const matrix b,
                             matrix c,
                             uint n )
{
    if(n == 1){
        c[0] = a[0] * b[0];
        return;
    }

    return;
        
    // // calc the next size down
    // uint next_n = n / 2;
        
    // // allocate 2x2 matrices that represent partitioned versions of the ones passed in
    // underlying pa[0][0][next_n][next_n];
    // underlying pb[2][2][next_n][next_n];
    // underlying pc[2][2][next_n][next_n];
        
    // // copy in a and b into the matrix partitions
    // for(uint i = 0; i < next_n; ++i){
    //     for(uint j = 0; j < next_n; ++j){
                
    //         uint next_i = i + next_n;
    //         uint next_j = j + next_n;
                
    //         pa[0][0][i][j] = a[i][j];
    //         pb[0][0][i][j] = b[i][j];
                
    //         pa[1][0][i][j] = a[next_i][j];
    //         pb[1][0][i][j] = b[next_i][j];
                
    //         pa[0][1][i][j] = a[i][next_j];
    //         pb[0][1][i][j] = b[i][next_j];
                
    //         pa[1][1][i][j] = a[next_i][next_j];
    //         pb[1][1][i][j] = b[next_i][next_j];
    //     }
    // }
        
    // matrix params[10];
    // matrix s[7];
        
    // // build the 10 unique parameters
    // subtract( pa[0][1], pa[1][1], params[0], next_n );
    // add( pb[1][0], pb[1][1], params[1], next_n );
    // add( pa[0][0], pa[1][1], params[2], next_n );
    // add( pb[0][0], pb[1][1], params[3], next_n );
    // subtract( pa[0][0], pa[1][0], params[4], next_n );
    // add( pb[0][0], pb[0][1], params[5], next_n );
    // add( pa[0][0], pa[0][1], params[6], next_n );
    // subtract( pb[0][1], pb[1][1], params[7], next_n );
    // subtract( pb[1][0], pb[0][0], params[8], next_n );
    // add( pa[1][0], pa[1][1], params[9], next_n );

    // // calculate the 7 strassen values 
    // strassen_multiply( params[0], params[1], s[0], next_n );
    // strassen_multiply( params[2], params[3], s[1], next_n );
    // strassen_multiply( params[4], params[5], s[2], next_n );
    // strassen_multiply( params[6], pb[1][1],  s[3], next_n );
    // strassen_multiply( pa[0][0],  params[7], s[4], next_n );
    // strassen_multiply( pa[1][1],  params[8], s[5], next_n );
    // strassen_multiply( params[9], pb[0][0],  s[6], next_n );
        
    // // use the params to store answers
    // // pc[0][0]
    // add( s[0], s[1], params[0], next_n );
    // subtract( params[0], s[3], params[1], next_n );
    // add( params[1], s[5], pc[0][0], next_n );
        
    // // pc[1][0]
    // add( s[3], s[4], pc[1][0], next_n );
        
    // // pc[0][1]
    // add( s[5], s[4], pc[0][1], next_n );

    // // pc[1][1]
    // subtract( s[1], s[2], params[0], next_n );
    // add( params[0], s[4], params[1], next_n );
    // subtract( params[1], s[6], pc[1][1], next_n );
        
    // // copy them into the big matrix
    // for(uint i = 0; i < next_n; ++i){
    //     for(uint j = 0; j < next_n; ++j){
    //         uint next_i = next_n + i;
    //         uint next_j = next_n + j;
                
    //         c[i][j]           = pc[0][0][i][j];
    //         c[next_i][j]      = pc[1][0][i][j];
    //         c[i][next_j]      = pc[0][1][i][j];
    //         c[next_i][next_j] = pc[1][1][i][j];
    //     }
    // }
}

