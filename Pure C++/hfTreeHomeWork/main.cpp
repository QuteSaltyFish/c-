#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include "hfTree.h"
using namespace std;


void showInstruction()
{
    cout<<"Pls choose which mode do you want:\n";
    cout<<"I:Initialization\tE:Encoding\tD:Decoding\tP:code Printing\tT:Tree printing";
}
void initializeTree(hfTree<char> *tree)
{
    //declaration
    int n=0, *weight;
    char *v;
    //消除原来存储的树
    if (tree== nullptr)
        delete tree;

    //键入新的树
    cout<<"PLS input the scale of the text";
    cin>>n;
    v = new char[n];
    weight = new int[n];
    for (int i=0 ; i<n; ++i)
    {
        cout<<"Pls input the char and the weight of the "<<i<<"th item:";
        cin>>v[i];
        cin.get();
        cin>>weight[i];
        cout<<endl;
    }
    tree = new hfTree<char>(v, weight, n);


    delete v;
    delete weight;
}
int main() {
    //declaration
    int n=0, *weight;
    char inputSwitch=' ';
    char *v;
    ifstream inFile("plainFile.in"), DataFile("DataFile.txt");
    fstream CodeFile;
    ofstream textFile, codePrint, treePrint;
    char command='\0';      //用户选择的指令
    hfTree<char>::hfCode *result=nullptr;   //用于存储处理得到的哈夫曼码
    hfTree<char> *hfmtree= nullptr;  //存储整个树
    char** treeMap = nullptr;
    if (!DataFile.is_open())
    {
        cout<<"Open DataFile error!";
        return -1;
    }
    if (!inFile.is_open())
    {
        cout<<"open plainFile error!";
        return -1;
    }
    //开始读取用户的指令
    do
    {
        showInstruction();
        cin>>command;
        switch (command)
        {
            case 'd':
                if (hfmtree==nullptr)
                {
                    cout<<"The Tree Has Not Been initiated!\n";
                    break;
                }
                CodeFile.open("CodeFile.txt");
                if(!CodeFile.is_open())
                {
                    cout<<"open CodeFile error";
                    return -1;
                }
                textFile.open("textFile.out");
                if(!textFile.is_open())
                {
                    cout<<"open textFile error";
                    return -1;
                }

                while(!CodeFile.eof())
                {
                    string x="";
                    CodeFile>>x;
                    for (int i=0; i<n; ++i)
                    {
                        if (result[i].code == x)
                        {
                            textFile<<result[i].data;
                            break;
                        }
                    }
                }

                textFile.close();
                CodeFile.close();
                break;
            case 'e':
                CodeFile.open("CodeFile.txt");

                if(!CodeFile.is_open())
                {
                    cout<<"open CodeFile error";
                    return -1;
                }
                if (hfmtree==nullptr)
                {
                    cout<<"The Tree Has Not Been initiated!\n";
                    break;
                }

                while(!inFile.eof())
                {
                    char letter=' ';
                    inFile.get(letter);
                    cout<<letter;
                    for (int i=0; i<n; ++i)
                    {
                        if (result[i].data == letter)
                        {
                            CodeFile<<result[i].code;
                            break;
                        }
                    }
                    CodeFile<<' ';
                }
                cout<<endl;
                CodeFile.close();
                break;
            case 'i':
                //消除原来存储的树和原来的结果
                if (hfmtree != nullptr)
                {
                    delete hfmtree;
                    hfmtree = nullptr;
                }
                if (result !=nullptr)
                {
                    delete [] result;
                    result = nullptr;
                }

                cout<<"Do U want to use the data from the file?(y for yes, n for no)";
                cin>>inputSwitch;
                while(true)
                {
                    if (inputSwitch=='n')
                    {
                        //键入新的树
                        cout<<"PLS input the scale of the text";
                        cin>>n;
                        v = new char[n];
                        weight = new int[n];
                        for (int i=0 ; i<n; ++i)
                        {
                            cout<<"Pls input the char and the weight of the "<<i<<"th item:";
                            cin>>v[i];
                            cin.get();
                            cin>>weight[i];
                            cout<<endl;
                        }
                        break;
                    }
                    else if (inputSwitch=='y')
                    {
                        map<char,int> storage;
                        char letter;
                        while(DataFile.get(letter))
                        {
                            storage[letter]+=1;
                        }
                        v= new char[storage.size()];
                        weight = new int[storage.size()];
                        int i=0;
                        for (map<char, int>::iterator pt=storage.begin(); pt!=storage.end(); ++pt)
                        {
                            cout<<pt->first<<' '<<pt->second<<endl;
                            v[i] = pt->first;
                            weight[i] = pt->second;
                            ++i;
                        }
                        n = storage.size();
                        break;
                    }
                }



                hfmtree = new hfTree<char>(v, weight, n);


                delete v;
                delete weight;

                result = new hfTree<char>::hfCode[n];
                hfmtree->getCode(result);
                for (int i=0;i<n; ++i) {
                    cout<< result[i].data<<' '<< result[i].code<<endl;
                }
                break;
            case 'p':
                CodeFile.open("codeFile.txt",ios::in);
                codePrint.open("codePrint.out");
                while(!CodeFile.eof())
                {
                    static int time=0;
                    char x;
                    CodeFile.get(x);
                    cout<<x;
                    codePrint<<x;
                    if (time!=0 && time%50==0)
                    {
                        cout<<'\n';
                        codePrint<<'\n';
                    }
                    time++;
                }

                codePrint.close();
                CodeFile.close();
                break;
            case 't':
                if (hfmtree== nullptr)
                {
                    cout<<"hfTree has not been initiated!\n";
                    break;
                }
                treePrint.open("treePrint.out");
                if (!treePrint.is_open())
                {
                    cout<<"Open TreePrint error!";
                    return -1;
                }
                treeMap = hfmtree->getTreeMap(treeMap);
                for (int i=0; i<hfmtree->getDepth(); ++i)
                {
                    for (int j=0; j<pow(2,hfmtree->getDepth())-1; ++j)
                    {
                        cout<<treeMap[i][j]<<' ';
                        treePrint<<treeMap[i][j]<<' ';
                    }
                    cout<<endl;
                    treePrint<<endl;
                }
                delete treeMap;
                treeMap= nullptr;
                treePrint.close();
                break;
            default:
                break;
        }
    }while (command != 'q');
    std::cout << "Hello, World!" << std::endl;
    inFile.close();
    return 0;
}

