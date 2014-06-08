#include "test.hpp"

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template < typename INPUT >
std::string utils::test<INPUT>::case_names[case_count] = { "Best Case", "Average Case", "Worst Case" };

template < typename INPUT >
utils::test<INPUT>::test( const std::string& name,
                          case_func& best_case,
                          case_func& average_case,
                          case_func& worst_case,
                          check_func& correctness_check ) :
    m_name { name },
    m_correctness_check { correctness_check }
{
    m_cases[0] = best_case;
    m_cases[1] = average_case;
    m_cases[2] = worst_case;
}

template < typename INPUT >
void utils::test<INPUT>::run()
{
    cout << "Begin: " << m_name << endl;

    for(size_t i = 0; i < case_count; ++i){
        // run and time the best case
        cout << case_names[i] << endl;
        cout << "    Start ... ";
 
        auto start = high_resolution_clock::now();
        auto output = m_cases[i]();
        auto end = high_resolution_clock::now();

        cout << "Stop "
             << duration_cast<nanoseconds>(end - start).count()
             << " nanoseconds" << endl;

        // check correctness
        if( !m_correctness_check( output ) ){
            cout << "    Correctness Check Failed!" << endl;
        }
    }
    cout << "End " << m_name << endl;

}
