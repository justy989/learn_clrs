#include <iostream>

using namespace std;

double same_birthday_pct( int n )
{
    if( n <= 1){
        return 0.0;
    }

    double percent = 1.0;

    for( int i = 0; i < n; i++ ){
        percent *= ( 1.0 - (static_cast<double>(i) / 365.0) );
    }

    return ( 1.0 - percent ) * 100.0;
}

int main(int argc, char** argv)
{
    if( argc !=  2){
        cerr << "This program requires 1 argument signifying the number of people in the room." << endl;
        return 1;
    }

    int n = atoi( argv[1] );
    auto percent = same_birthday_pct( n );

    cout << "The chance that 2 of " << n 
         << " people have the same birthday is: " 
         << percent << " %" << endl;

    return 0;
}
