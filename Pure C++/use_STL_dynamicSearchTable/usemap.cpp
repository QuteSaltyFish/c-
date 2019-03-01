#include <iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
    map<string, string> s;
    string name[6] = {"钱一", "孙二", "张三", "李四", "王五", "赵六"};
    string addr[6] = {"上海", "南京", "杭州", "南京", "南京", "杭州"};
    map<string, string>::iterator p;

    //insert the imformation of thes 6 people and display them
    for (int i=0; i<6; ++i)
        s.insert(pair<string, string>(name[i], addr[i]));
    cout<<"the content of s:"<<endl;
    for (p=s.begin(); p!=s.end(); ++p)
        cout<<p->first<<p->second<<endl;

    p=s.find("张三");
    cout<<"\nfind(\"张三\"):"<<p->first<<'\t'<<p->second<<endl;
    p->second="hhh";    //after find the iterator, U can change the and value of the iterator(but U cannot change the key of it!)
    for (p=s.begin(); p!=s.end(); ++p)
        cout<<p->first<<p->second<<endl;

    s.erase("张三");
    cout<<"\nafter erase(\"张三\"), the content of s:"<<endl;
    for (p=s.begin(); p!=s.end(); ++p)
        cout<<p->first<<p->second<<endl;

    std::cout << "Hello world" << std::endl;
    return 0;
}

