#include "matrix.hpp"

#include <stdexcept>
#include <cmath>

using namespace mat;

void mat::add( const matrix a, 
               const matrix b, 
               matrix c,
               uint n )
{
    for(uint i = 0; i < n; ++i){
        for(uint j = 0; j < n; ++j){
            set( c, n, i, j,
                 element( a, n, i, j ) + element( b, n, i, j ) );
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
                 element( a, n, i, j ) - element( b, n, i, j ) );
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

mat::strassen_allocator::strassen_allocator(uint matrix_dimension) :
    m_next{0}
{
    uint matrix_size = matrix_dimension * matrix_dimension;
    uint levels = log( static_cast<double>(matrix_dimension) ) / log(2.0);
    uint partitioned_and_temp_matrices = 8 * matrix_size;

    m_size = partitioned_and_temp_matrices * matrix_dimension * levels;

    m_memory = new element_type[m_size];
}

mat::strassen_allocator::~strassen_allocator()
{
    if(m_memory){
        delete[] m_memory;
    }
}

mat::matrix mat::strassen_allocator::alloc(uint n)
{
    uint save = m_next;
    m_next += mat::size(n);

    if( m_next > m_size ){
        throw std::runtime_error("Hit allocator max");
    }

    return m_memory + save;
}

void mat::strassen_multiply( const matrix a, 
                             const matrix b,
                             matrix c,
                             uint n,
                             strassen_allocator& allocator )
{
    if(n == 1){
        c[0] = a[0] * b[0];
        return;
    }
        
    // calc the next size down
    uint next_n = n / 2;

    // allocate 2x2 matrices that represent partitioned versions of the ones passed in
    matrix pa[2][2] { { allocator.alloc(next_n), allocator.alloc(next_n) },
                      { allocator.alloc(next_n), allocator.alloc(next_n) } };
    matrix pb[2][2] { { allocator.alloc(next_n), allocator.alloc(next_n) },
                      { allocator.alloc(next_n), allocator.alloc(next_n) } };
    matrix pc[2][2] { { allocator.alloc(next_n), allocator.alloc(next_n) },
                      { allocator.alloc(next_n), allocator.alloc(next_n) } };
        
    // copy in a and b into the matrix partitions
    for(uint i = 0; i < next_n; ++i){
        for(uint j = 0; j < next_n; ++j){                
            uint next_i = i + next_n;
            uint next_j = j + next_n;
                
            set( pa[0][0], next_n, i, j, element( a, n, i, j ) );
            set( pb[0][0], next_n, i, j, element( b, n, i, j ) );
                
            set( pa[1][0], next_n, i, j, element( a, n, next_i, j ) );
            set( pb[1][0], next_n, i, j, element( b, n, next_i, j ) );
                
            set( pa[0][1], next_n, i, j, element( a, n, i, next_j ) );
            set( pb[0][1], next_n, i, j, element( b, n, i, next_j ) );
                
            set( pa[1][1], next_n, i, j, element( a, n, next_i, next_j ) );
            set( pb[1][1], next_n, i, j, element( b, n, next_i, next_j ) );
        }
    }

    // build our temporary matrices
    matrix params[10] {
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n)
    };

    matrix s[7] {
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
        allocator.alloc(next_n),
    };

    // build the 10 unique parameters
    subtract( pa[0][1], pa[1][1], params[0], next_n );
    add(      pb[1][0], pb[1][1], params[1], next_n );
    add(      pa[0][0], pa[1][1], params[2], next_n );
    add(      pb[0][0], pb[1][1], params[3], next_n );
    subtract( pa[0][0], pa[1][0], params[4], next_n );
    add(      pb[0][0], pb[0][1], params[5], next_n );
    add(      pa[0][0], pa[0][1], params[6], next_n );
    subtract( pb[0][1], pb[1][1], params[7], next_n );
    subtract( pb[1][0], pb[0][0], params[8], next_n );
    add(      pa[1][0], pa[1][1], params[9], next_n );

    // calculate the 7 strassen values 
    strassen_multiply( params[0], params[1], s[0], next_n, allocator );
    strassen_multiply( params[2], params[3], s[1], next_n, allocator );
    strassen_multiply( params[4], params[5], s[2], next_n, allocator );
    strassen_multiply( params[6], pb[1][1],  s[3], next_n, allocator );
    strassen_multiply( pa[0][0],  params[7], s[4], next_n, allocator );
    strassen_multiply( pa[1][1],  params[8], s[5], next_n, allocator );
    strassen_multiply( params[9], pb[0][0],  s[6], next_n, allocator );
        
    // use the params to store pc answers
    add(      s[0],      s[1], params[0], next_n );
    subtract( params[0], s[3], params[1], next_n );
    add(      params[1], s[5], pc[0][0],  next_n );
        
    add( s[3], s[4], pc[1][0], next_n );
    add( s[5], s[6], pc[0][1], next_n );

    subtract( s[1],      s[2], params[0], next_n );
    add(      params[0], s[4], params[1], next_n );
    subtract( params[1], s[6], pc[1][1],  next_n );
        
    // copy them into the big matrix
    for(uint i = 0; i < next_n; ++i){
        for(uint j = 0; j < next_n; ++j){
            uint next_i = next_n + i;
            uint next_j = next_n + j;
                
            set( c, n, i,      j,      element( pc[0][0], next_n, i, j ) );
            set( c, n, next_i, j,      element( pc[1][0], next_n, i, j ) );
            set( c, n, i,      next_j, element( pc[0][1], next_n, i, j ) );
            set( c, n, next_i, next_j, element( pc[1][1], next_n, i, j ) );
        }
    }
}

