/*************************************************************************
	> File Name: algithem_test.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 07:22:24 AM PST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    int a[]={2,4,7,8,10,12,13,15,16,19,20};
    vector<int> v;
    vector<int>::iterator itr;
    for (int i=0; i<11; ++i)
    {
        v.push_back(a[i]);
    }
    if (binary_search(v.begin(), v.end(), 13))
        cout<<"13 exist\n";
    else
        cout<<"13 nonexist\n";
    itr = find(v.begin(), v.end(), 13);
    cout<< *itr<<endl;
    return 0;
}
