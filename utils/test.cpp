#include "test.hpp"

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template < typename INPUT >
utils::test<INPUT>::test( const std::string& name,
                          case_func& best_case,
                          case_func& average_case,
                          case_func& worst_case,
                          check_func& correctness_check ) :
    m_name { name },
    m_best_case { best_case },
    m_average_case { average_case },
    m_worst_case { worst_case },
    m_correctness_check { correctness_check }
{

}

template < typename INPUT >
void utils::test<INPUT>::run()
{
    cout << "Begin: " << m_name << endl;

    // run and time the best case
    cout << "  Best Case:" << endl;
    cout << "    Start ... ";
 
    auto start = high_resolution_clock::now();
    auto output = m_best_case();
    auto end = high_resolution_clock::now();

    cout << "Stop "
         << duration_cast<nanoseconds>(end - start).count()
         << " nanoseconds" << endl;

    // check correctness
    if( !m_correctness_check( output ) ){
        cout << "    Correctness Check Failed!" << endl;
    }


    // run and time the average case
    cout << "  Average Case:" << endl;
    cout << "    Start ... ";
 
    start = high_resolution_clock::now();
    output = m_average_case();
    end = high_resolution_clock::now();

    cout << "Stop "
         << duration_cast<nanoseconds>(end - start).count()
         << " nanoseconds" << endl;

    // check correctness
    if( !m_correctness_check( output ) ){
        cout << "    Correctness Check Failed!" << endl;
    }


    // run and time the worst case
    cout << "  Worst Case:" << endl;
    cout << "    Start ... ";
 
    start = high_resolution_clock::now();
    output = m_worst_case();
    end = high_resolution_clock::now();

    cout << "Stop "
         << duration_cast<nanoseconds>(end - start).count()
         << " nanoseconds" << endl;

    // check correctness
    if( !m_correctness_check( output ) ){
        cout << "    Correctness Check Failed!" << endl;
    }

    cout << "End " << m_name << endl;
}
