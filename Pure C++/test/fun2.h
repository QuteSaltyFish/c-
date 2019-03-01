#ifndef FUN2_H
#define FUN2_H
#include <iostream>
using namespace std;
class car {
private:
    int num;

public:
    car(int x = 0) { num = x; }
    void show() { cout << num; }
};

#endif // FUN2_H