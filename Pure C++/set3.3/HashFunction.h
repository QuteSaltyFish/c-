//
// Created by Mingke Wang on 2018-12-18.
//

#ifndef SET3_3_HASHFUNCTION_H
#define SET3_3_HASHFUNCTION_H
#include <string>
using namespace std;
unsigned long stupidHash(const string &str)
{
    unsigned long i, Hash=0;
    for (i=0; i<str.length(); ++i)
        Hash+=str[i];
    return Hash;
}
unsigned long BKDRHash(const string &str)
{
    int seed=131;
    unsigned long hash=0;
    unsigned long i=0;
    unsigned long len=str.length();

    for (i=0; i<len; ++i)
        hash = (hash * seed) + (str[i]);

    return hash;
}

unsigned long APHash(const string &str)
{
    unsigned long hash=0;
    unsigned long i;
    for (i=0; i<str.length(); i++)
    {
        if ((i&1)==0)
            hash^=((hash<<7)^(str[i])^(hash>>3));
        else
            hash^=(~((hash<<11)^(str[i])^(hash>>5)));
    }   
    return hash;
}

unsigned long DJBHash(const string &str)
{
    unsigned long hash=5381;
    for (unsigned long  i=0; i<str.length(); ++i)
    {
        hash+=(hash<<5)+(str[i]);
    }
    return hash;
}

unsigned long SDBMHash(const string &str)
{
    unsigned long hash=0;
    for (unsigned long i=0; i<str.length(); ++i)
    {
        hash=(str[i])+(hash<<6)+(hash<<16)-hash;
    }
    return hash;
}

unsigned long JSHash(const string &str)
{
    unsigned long hash=1315423911;
    for(unsigned long i=0; i<str.length(); ++i)
    {
        hash^=((hash<<5)+str[i]+(hash>>2));
    }
    return hash;
}
#endif //SET3_3_HASHFUNCTION_H
