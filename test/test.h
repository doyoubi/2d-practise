#ifndef TEST
#define TEST

#include<stdlib.h>
#include<fstream>
#include<iostream>
using std::cout;
using std::endl;

namespace
{
    using std::endl;
    using std::ios;
    std::ofstream fout("error_message.txt", ios::out|ios::app);

    #include<time.h>
}

inline void validate(bool to_be_validated, const char * const error_message)
{
    if( ! to_be_validated )
    {
        time_t now;
        time( &now );
        cout<< endl << error_message << endl << endl;
        fout<< asctime( gmtime(&now) )
            << error_message <<endl<<endl;
        fout.close();
        exit(1);
    }
}

#endif
