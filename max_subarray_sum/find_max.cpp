#include "find_max.hpp"

template < typename T >
find::answer<T> find::bf_find_max_subarray( const std::vector<T>& input )
{
    if(input.size() <= 0){
        return answer<T>{ 0, 0, T{} };
    }

    answer<T> ans { 0, 0, input[0] };

    // brute force approach
    for(size_t i = 0; i < input.size(); ++i){
        for(size_t j = i + 1; j <= input.size(); ++j){

            // start with an empty sum
            T sum {};

            // loop over every possible range
            for(size_t k = i; k <= j; ++k){
                sum += input[k];
            }

            // if we found a new greater sum, save it
            if( sum > ans.sum ){
                ans.sum = sum;
                ans.left = i;
                ans.right = j;
            }
        }
    }
    
    return ans;
}

template < typename T >
find::answer<T> find::kadane_find_max_subarray( const std::vector<T>& input )
{
    if(input.size() <= 0){
        return answer<T>{ 0, 0, T{} };
    }

    answer<T> ans { 0, 0, input[0] };

    T check_sum = ans.sum;
    size_t check_left = 0;

    // loop over the input
    for(size_t i = 1; i < input.size(); ++i){

        // if the value is positive save it's starting location
        // and set it as a potential candidate
        if(check_sum < 0){
            check_sum = input[i];
            check_left = i;
        }else{ // otherwise continue adding
            check_sum += input[i];
        }

        // if the sum gets larger than what we have found
        // so far, then save it
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

    // find the max sum of the left side
    for(size_t i = mid; i > left; --i){
        sum += input[i];
        if( sum > left_sum ){
            left_sum = sum;
            ans.left = i;
        }
    }

    sum = {};

    // find the sum of the right side
    for(size_t i = mid + 1; i <= right; ++i){
        sum += input[i];
        if( sum > right_sum ){
            right_sum = sum;
            ans.right = i;
        }
    }

    // add them together for the crossing
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

