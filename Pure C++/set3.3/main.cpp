#include <iostream>
#include "closeHashTable.h"
#include <string>
#include <ctime>
#include <cstdlib>
#include "HashFunction.h"

class NameList
{
public:
    SET<string, int> *list;
    int size;
    NameList();
    NameList(int size);
    ~NameList(){delete []list;}
    int getSize(){return size;}
    void show()
    {
        for (int i=0; i<size; ++i)
            cout<<"The "<<i+1<<"th name is: "<<list[i].key<<'\t'<<list[i].other<<endl;
    }
};

NameList::NameList()
{
    size = 30;
    list = new SET<string, int>[30];
    for (int i=0; i<size; ++i)
        list[i].other=i;
    list[0].key="chenbingyang";
    list[1].key="dengxialing";
    list[2].key="fangyimian";
    list[3].key="lvyi";
    list[4].key="shiyunnan";
    list[5].key="sunzixuan";
    list[6].key="wangyukun";
    list[7].key="wangyulong";
    list[8].key="wubolun";
    list[9].key="gaodeshen";
    list[10].key="guoyi";
    list[11].key="jinshouchen";
    list[12].key="lihonglu";
    list[13].key="lizixuna";
    list[14].key="lixinyi";
    list[15].key="lixinyi";
    list[16].key="liaoyusheng";
    list[17].key="maze";
    list[18].key="qianrui";
    list[19].key="shaomingzheng";
    list[20].key="tongzhengyan";
    list[21].key="weisizhe";
    list[22].key="wangmingke";
    list[23].key="wangxiaohang";
    list[24].key="xiehaozhe";
    list[25].key="yankunlin";
    list[26].key="yuanshenchao";
    list[27].key="yejiaxun";
    list[28].key="yujialing";
    list[29].key="yuzhuowen";
}

NameList::NameList(int num)
{
    size = num;
    list = new SET<string, int>[num];
    for (int i=0; i<size; ++i)
    {
        int length = rand()%12+3;
        list[i].other = i;
        for (int j=0; j<length; ++j)
            list[i].key+=(char)(97+rand()%26);
    }
}
int main()
{
    srand((unsigned int)time(NULL));
    NameList a, b(10);
    closeHashTable<string, int> HashTable(a.getSize(), JSHash);
    for (int i=0; i<a.getSize(); ++i)
        HashTable.insert(a.list[i]);
    HashTable.show();
    //a.show();
    //b.show();
    SET<string,int> c{"asv", 1};
    cout<<endl;
    
    cout<<SET<string,int>{"asv", 1}.key<<"  "<<SET<string,int>{"asv", 1}.other;
    std::cout << "Hello world" << std::endl;
    return 0;
}

