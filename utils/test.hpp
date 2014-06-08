#ifndef TEST_H
#define TEST_H

#include <string>
#include <functional>

namespace utils{

    template < typename INPUT >
    class test{
    public:
        using case_func = std::function< INPUT(INPUT) >;
        using check_func = std::function< bool(const INPUT&) >;

        test( const std::string& name,
              case_func& fn,
              const INPUT& best_input,
              const INPUT& average_input,
              const INPUT& worst_input,
              check_func& correctness_check );

        void run();

    private:

        std::string m_name;

        static constexpr size_t case_count {3};
        static std::string case_names[case_count];

        const case_func& m_case_func;
        const INPUT m_case_inputs[case_count];
        check_func& m_correctness_check;
    };
}

#include "test.cpp"

#endif
