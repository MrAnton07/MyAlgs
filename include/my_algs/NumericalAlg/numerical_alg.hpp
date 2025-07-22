#pragma once

#include <bitset>
#include <utility>

namespace num_alg::number{

    class Hash_table;
    class RSA_Protocol;
    
    int Multiply(int& x, int& y);
    int* Divide(int& x, int& y, int* buff);
    int ModExp(int& x, int&y, int& N);
    int Euclid(int& a, int& b);
    int* ExtendedEuclid(int& a, int& b, int* buff);
    bool Primality(int& N);
    bool Primality2(int& N);

}
