#include "find_max.hpp"

template < typename T >
find::answer<T> find::kadane_find_max_subarray( const std::vector<T>& input )
{
    if(input.size() <= 0){
        return answer<T>{ 0, 0, T{} };
    }

    answer<T> ans { 0, 0, input[0] };

    T check_sum = ans.sum;
    size_t check_left = 0;

    for(size_t i = 0; i < input.size(); ++i){
        if(check_sum < 0){
            check_sum = input[i];
            check_left = i;
        }else{
            check_sum += input[i];
        }

        if( check_sum > ans.sum ){
            ans.sum = check_sum;
            ans.left = check_left;
            ans.right = i;
        }
    }

    return ans;
}
