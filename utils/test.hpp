#ifndef TEST_H
#define TEST_H

#include <string>
#include <functional>

namespace utils{

    template < typename INPUT >
    class test{
    public:
        using case_func = std::function< INPUT(void) >;
        using check_func = std::function< bool(const INPUT&) >;

        test( const std::string& name,
              case_func& best_case,
              case_func& average_case,
              case_func& worst_case,
              check_func& correctness_check );

        void run();

    private:

        std::string m_name;

        case_func& m_best_case;
        case_func& m_average_case;
        case_func& m_worst_case;
        check_func& m_correctness_check;
    };
}

#include "test.cpp"

#endif
