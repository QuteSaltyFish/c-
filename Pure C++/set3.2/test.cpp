#include <iostream>
#include"score.h"
#include<ctime>
int main()
{
    srand((unsigned int)time(NULL));
    cout<<"pls input the number of the sample:";
    int num;
    cin>>num;
    score a(num);
    a.showscore();
    cout<<endl<<endl<<endl<<"After sorting:\n";
    a.sort();
    a.showscore();
    std::cout << "Hello world" << std::endl;
    return 0;
}

