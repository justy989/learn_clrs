#include "test.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <chrono>

using namespace std;
using namespace std::chrono;

template < typename INPUT, typename OUTPUT >
utils::test<INPUT, OUTPUT>::test( const std::string& name,
                                  case_func& func,
                                  check_func& correctness_check,
                                  std::vector<case_info>&& cases ) :
    m_name { name },
    m_case_func { func },
    m_correctness_check { correctness_check },
    m_cases { std::move(cases) }
{

}

template < typename T >
std::string format_ns_with_commas(T count)
{
    std::stringstream ss;
    ss.imbue(std::locale("en_US"));
    ss << std::fixed << count;
    return ss.str();
}

template < typename INPUT, typename OUTPUT >
void utils::test<INPUT, OUTPUT>::run()
{
    cout << "Begin: " << m_name << endl;

    for(size_t i = 0; i < m_cases.size(); ++i){
        // run and time the best case
        cout << "  " << m_cases[i].id << endl;
        cout << "    Start ... ";
 
        auto start = high_resolution_clock::now();

        auto output = m_case_func( m_cases[i].input );

        auto end = high_resolution_clock::now();

        cout << "Stop "
             << format_ns_with_commas( 
                 duration_cast<nanoseconds>(end - start).count() )
             << " ns" << endl;

        // check correctness
        if( !m_correctness_check( m_cases[i].input, output ) ){
            cout << "    Correctness Check Failed!" << endl;
        }
    }

    cout << "End " << m_name << endl << endl;
}

