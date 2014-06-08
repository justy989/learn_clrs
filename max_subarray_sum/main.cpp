//#include "../utils/test.hpp"
#include "../utils/generate.hpp"
#include "find_max.hpp"

#include <iostream>

using namespace utils;
using namespace std;

int main()
{
    uint32_t seed = 1337;
    size_t n = 15;

    cout << "Generating list of " << n << " random unique values with seed " << seed << endl << endl;

    // generate 50 ints, copy them for best and worst input
    auto values = generate_unique<int>( seed, n );
    
    using input = decltype(values);

    input deltas ( values.size() - 1, 0 );

    for( size_t i = 0; i < deltas.size(); i++){
        deltas[i] = values[ i + 1 ] - values[ i ];
    }

    for( auto elem : deltas ){
        cout << elem << " ";
    }

    cout << endl;

    auto ans = find::kadane_find_max_subarray( deltas );

    cout << "Left:  " << ans.left << endl;
    cout << "Right: " << ans.right << endl;
    cout << "Sum:   " << ans.sum << endl;

    cout << endl;

    return 0;
}
