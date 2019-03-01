#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int> s;
    int a[21] = { 0, 4, 7, 10, 2, 9, 8, 12, 13, 17, 3, 18, 1, 15, 5, 6, 11, 14, 16, 20, 19 };
    set<int>::iterator p;

    for (int i = 0; i < 21; ++i)
        s.insert(a[i]);
    cout << "The content of s: ";
    for (p = s.begin(); p != s.end(); ++p)
        cout << *p << '\t';

    cout << "\nfind(18):" << *(s.find(18)) << endl;

    s.erase(17);
    cout << "after erase(17), the content of s:";
    for (p = s.begin(); p != s.end(); ++p)
        cout << *p << '\t';
    cout << endl;

    return 0;
}
