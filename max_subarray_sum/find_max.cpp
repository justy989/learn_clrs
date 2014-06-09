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

template < typename T >
find::answer<T> find::impl_dac_find_max_crossing_subarray( const std::vector<T>& input,
                                                           size_t left,
                                                           size_t mid,
                                                           size_t right )
{
    answer<T> ans { left, right, T{} };
    T left_sum = input[mid];
    T right_sum = input[mid+1];

    T sum {};

    for(size_t i = mid; i > left; --i){
        sum += input[i];
        if( sum > left_sum ){
            left_sum = sum;
            ans.left = i;
        }
    }

    sum = {};

    for(size_t i = mid + 1; i <= right; ++i){
        sum += input[i];
        if( sum > right_sum ){
            right_sum = sum;
            ans.right = i;
        }
    }

    ans.sum = right_sum + left_sum;

    return ans;
}

template < typename T >
find::answer<T> find::impl_dac_find_max_subarray( const std::vector<T>& input,
                                                  size_t left,
                                                  size_t right )
{
    // our base case
    if( left == right ){
        return answer<T>{ left, right, input[0] };
    }

    // calc mid and recurs on the left and right sides
    size_t mid = ( left + right ) / 2;

    auto left_ans = impl_dac_find_max_subarray( input,
                                                left,
                                                mid );

    auto right_ans = impl_dac_find_max_subarray( input,
                                                mid + 1,
                                                right );

    // find the cross section's max
    auto cross_ans = impl_dac_find_max_crossing_subarray( input,
                                                          left,
                                                          mid,
                                                          right );

    // determine which sum to return
    if( left_ans.sum >= right_ans.sum &&
        left_ans.sum >= cross_ans.sum ){
        return left_ans;
    }else if( right_ans.sum >= left_ans.sum &&
              right_ans.sum >= cross_ans.sum ){
        return right_ans;
    }

    return cross_ans;
}

template < typename T >
find::answer<T> find::dac_find_max_subarray( const std::vector<T>& input )
{
    // handle erroneous input
    if( !input.size() ){
        return answer<T>{ 0, 0, T{} };
    }

    // begin!
    return impl_dac_find_max_subarray( input,
                                       0,
                                       input.size() - 1 );
}

