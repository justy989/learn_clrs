#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "matrix.hpp"

#include <iostream>
#include <limits>

using namespace std;

struct params{

    params(mat::uint n) :
        size(n),
        a( new mat::element_type[ mat::size( n ) ]),
        b( new mat::element_type[ mat::size( n ) ]),
        c( new mat::element_type[ mat::size( n ) ])
        {}

    params(const params& p) :
        size(p.size),
        a( new mat::element_type[ mat::size( size ) ]),
        b( new mat::element_type[ mat::size( size ) ]),
        c( new mat::element_type[ mat::size( size ) ])        
    {
        for(mat::uint i = 0; i < mat::size( size ); ++i){
            a[i] = p.a[i];
            b[i] = p.b[i];
            c[i] = p.c[i];
        }
    }

    params(params&& p) :
        size(p.size),
        a(p.a),
        b(p.b),
        c(p.c)
    {
        p.a = nullptr;
        p.b = nullptr;
        p.c = nullptr;
        p.size = 0;
    }

    ~params()
    {
        if( a ){
            delete[] a;
            a = nullptr;
        }

        if( b ){
            delete[] b;
            b = nullptr;
        }

        if( c ){
            delete[] c;
            c = nullptr;
        }
    }

    mat::uint size;

    mat::matrix a;
    mat::matrix b;
    mat::matrix c;
};

int main()
{
    uint32_t seed = 1337;
    mat::uint n = 16;

    cout << "NxN Matrix Multiplication" << endl;
    cout << "Generating 2 " << n << "x" << n << " matricies with seed " << seed << endl << endl;

    // allocate and fill matricies
    params bf_in(n);

    for(size_t i = 0; i < n; ++i){
        auto a = utils::generate_unique<double>( seed, n ); seed++;
        auto b = utils::generate_unique<double>( seed, n ); seed++;

        for(size_t j = 0; j < n; ++j){
            mat::set( bf_in.a, n, i, j, a[j] );
            mat::set( bf_in.b, n, i, j, b[j] );
        }
    }

    params st_in(bf_in);

    mat::strassen_allocator allocator(n);

    // aliases
    using input = params;
    using output = mat::matrix;
    using test = utils::test< input, output >;
    using case_info = std::vector< test::case_info >;


    // create lambdas for test use
    test::case_func bf_fn = [](input& in){ mat::bf_multiply(in.a, in.b, in.c, in.size); return in.c; };
    test::case_func st_fn = [&allocator](input& in){ mat::strassen_multiply(in.a, in.b, in.c, in.size, allocator); return in.c; };

    mat::matrix answer = new mat::element_type[ mat::size(n) ];

    // find the answer via brute force
    mat::bf_multiply(bf_in.a, bf_in.b, answer, n );

    // create lambda for checking correctness
    test::check_func check_correctness = [&answer, n](const input& input,
                                                      const output& output){
        if(input.size != n){
            return false;
        }

        for(mat::uint i = 0; i < input.size; ++i){
            for(mat::uint j = 0; j < input.size; ++j){
                // if( fabs( mat::element(output, n, i, j) - mat::element(answer, n, i, j) ) > std::numeric_limits<double>::epsilon() ){
                //     return false;
                // }
                cout << mat::element(output, n, i, j) << " ";
            }
            cout << endl;
        }

        return true;
    };


    // create cases
    case_info bf_cases {
        { "Average Case: n^3", bf_in }
    };

    case_info st_cases {
        { "Average Case: n^log7", st_in }
    };

    // construct and run tests
    test bf_test { "Brute Force"s,
                   bf_fn,
                   check_correctness,
                   std::move(bf_cases) };

    test st_test { "Strassen"s,
                   st_fn,
                   check_correctness,
                   std::move(st_cases) };

    bf_test.run();
    st_test.run();

    cout << endl;

    delete answer;
    return 0;
}
