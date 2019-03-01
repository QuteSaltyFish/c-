#include <iostream>
#include "closeHashTable.h"
#include "HashFunction.h"
#include <string>
#include <ctime>
#include <cstdlib>
class NameList
{
public:
    string *list;
    int size;
    NameList();
    NameList(int size);
    ~NameList(){delete []list;}
    int getSize(){return size;}
    void show()
    {
        for (int i=0; i<size; ++i)
            cout<<"The "<<i+1<<"th name is: "<<list[i]<<endl;
    }
};

NameList::NameList()
{
    size = 30;
    list = new string[30];
    list[0]="chenbingyang";
    list[1]="dengxialing";
    list[2]="fangyimian";
    list[3]="lvyi";
    list[4]="shiyunnan";
    list[5]="sunzixuan";
    list[6]="wangyukun";
    list[7]="wangyulong";
    list[8]="wubolun";
    list[9]="gaodeshen";
    list[10]="guoyi";
    list[11]="jinshouchen";
    list[12]="lihonglu";
    list[13]="lizixuna";
    list[14]="lixinyi";
    list[15]="lixinyi";
    list[16]="liaoyusheng";
    list[17]="maze";
    list[18]="qianrui";
    list[19]="shaomingzheng";
    list[20]="tongzhengyan";
    list[21]="weisizhe";
    list[22]="wangmingke";
    list[23]="wangxiaohang";
    list[24]="xiehaozhe";
    list[25]="yankunlin";
    list[26]="yuanshenchao";
    list[27]="yejiaxun";
    list[28]="yujialing";
    list[29]="yuzhuowen";
}

NameList::NameList(int num)
{
    size = num;
    list = new string[num];
    for (int i=0; i<size; ++i)
    {
        int length = rand()%12+3;
        for (int j=0; j<length; ++j)
            list[i]+=(char)(97+rand()%26);
    }
}
int main()
{
    srand((unsigned int)time(NULL));
    NameList a, b(10);
    unsigned long (*f[5])(const string &)={stupidHash, BKDRHash, APHash, SDBMHash, JSHash};
    for (int i=0; i<5; ++i)
    {
        cout<<"The "<<i+1<<" th method's result is:\n";
        closeHashTable<string, int> HashTable(a.getSize(), f[i]);
    
        for (int j=0; j<a.getSize(); ++j)
            HashTable.insert(SET<string, int>{a.list[j], j});
        HashTable.show();
    //a.show();
    //b.show();
    }
    return 0;
}

