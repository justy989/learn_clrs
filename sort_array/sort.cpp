#include "sort.hpp"

template < typename T >
void sort::bubble_sort( std::vector<T>& input )
{
    auto end = input.size() - 1;
    size_t swap_count = 0;
    
    do{
        swap_count = 0;
        for(std::size_t i = 0; i < end; ++i){
            auto next_i = i + 1;
            if( input[i] > input[next_i] ){
                std::swap( input[i], input[next_i]);
                ++swap_count;
            }
        }
    } while( swap_count );
}

template < typename T > 
void sort::insertion_sort( std::vector<T>& input )
{
    auto n = input.size();

    // handle simple cases
    if( n <= 1 ){
        return;
    }

    // loop over the input
    for( std::size_t j = 1; j < n; ++j ){

        // save the key and start at the end of the sorted input
        auto key = input[ j ];
        std::size_t i = j - 1;

        // loop while the values are greater than our key
        for( ; 
             i >= 0 && input[ i ] > key;
             --i ){
            // shift over each element
            input[ i + 1 ] = input[ i ];
        }

        // put our key in place
        input[ i + 1 ] = key;
    }
}

template < typename T >
void sort::impl_merge( std::vector<T>& input,
                       std::size_t start,
                       std::size_t mid,
                       std::size_t end )
{
    size_t left_size { (mid - start) + 1 };
    size_t right_size { end - mid };

    // gcc vlas
    T left[ left_size ];
    T right[ right_size ];

    std::size_t i { 0 };
    std::size_t j { 0 };

    // copy the elements into left and right arrays
    // the algorithm assumes these sub-arrays are sorted
    for(; i < left_size; ++i){
        left[i] = input[ start + i ];
    }

    for(; j < right_size; ++j){
        right[j] = input[ mid + j + 1 ];
    }

    i = 0;
    j = 0;

    // time to merge!
    for(std::size_t k = start; k <= end; ++k){

        // if either list is empty, add the rest of the other
        if( i >= left_size ){
            input[k] = right[j];
            ++j;
            continue;
        }

        if( j >= right_size ){
            input[k] = left[i];
            ++i;
            continue;
        }

        // based on which side is less,
        // add it back into the input list
        // and move the pointer to the next elem
        // in the lower side
        if( left[i] <= right[j] ){
            input[k] = left[i];
            ++i;
        }else{
            input[k] = right[j];
            ++j;
        }
    }
}

template < typename T >
void sort::impl_merge_sort( std::vector<T>& input,
                            std::size_t start,
                            std::size_t end )
{
    // if start isn't < end, there is only 1 element, so it is sorted
    if( start >= end ){
        return;
    }

    // calculate the mid point
    std::size_t mid = ( start + end ) / 2;
    
    // recursively merge sort the left and right halfs
    impl_merge_sort( input,
                     start,
                     mid );
    
    impl_merge_sort( input,
                     mid + 1,
                     end );
    
    // merge the two halves together
    impl_merge( input,
                start,
                mid,
                end );
}

template < typename T >
void sort::merge_sort( std::vector<T>& input )
{
    impl_merge_sort( input,
                     0,
                     input.size() - 1 );
}

