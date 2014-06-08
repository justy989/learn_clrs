#ifndef TEST_H
#define TEST_H

#include <string>
#include <functional>
#include <vector>

namespace utils{

    template < typename INPUT >
    class test{
    public:
        using case_func = std::function< INPUT(INPUT) >;
        using check_func = std::function< bool(const INPUT&) >;

        struct case_info{
            std::string id;
            INPUT input;
        };

        test( const std::string& name,
              case_func& fn,
              check_func& correctness_check,
              std::vector<case_info>&& cases );

        void run();

    private:
        std::string m_name;

        case_func& m_case_func;
        check_func& m_correctness_check;
        std::vector<case_info> m_cases;
    };
}

#include "test.cpp"

#endif
