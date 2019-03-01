#include "fun1.hpp"
#include "fun2.h"
#include <iostream>
using namespace std;
int main()
{
    int a = 1, b = 2;
    car c(3);
    cout << isBigger(a, b) << endl;
    c.show();
    return 0;
}