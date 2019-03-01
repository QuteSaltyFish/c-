#pragma once
#include<assert.h>
#include<iostream>
#include<cstdlib>
using namespace std;
void show()
{
    cout<<"This is the score.h"<<endl;
}

struct person
{
    int score[7];
    person()
    {
        for (int i=1; i<7; ++i)
        {
            score[i]=rand()%101;
            score[0]+=score[i];
        }
    }
    int getScore(int subject) const 
    {
        return score[subject];
    }
    void show()
    {
        for (int i=0; i<7; ++i)
            cout<<"score "<<i<<" is : "<<score[i]<<'\n';
    }
};
class score
{
public:
    score(int num = 6);
    ~score() {delete []data;}
    void sort();
    void showscore();
private:
    person *data;  //store all person score;
    int sample;     //the number of student;
    int order[7];
    void quicksort(person *array, int left, int right);
    int partsort(person *array, int left, int right);
    bool isBigger(person &a, person &b);
};

score::score(int num)
{
    sample = num;
    data = new person[num];
    for (int i=1; i<7; ++i)
    {
        cout<<"pls input the "<<i<<"th order:";
        cin>>order[i];
    }
    order[0]=0;
}

//calculate the relationshop of size of the person node
//return true if a>b
bool score::isBigger(person &a, person &b)
{
    for(int i=0; i<7; ++i)
    {
        if ( a.getScore(order[i]) > b.getScore(order[i]) )
            return true;
        else if ( a.getScore(order[i]) < b.getScore(order[i]) )
            return false;
    }
    return false;
}

void score::showscore()
{
    for (int i=0; i<sample; ++i)
    {
        cout<<"The "<<i+1<<"th person:\n";
        data[i].show();
        cout<<endl;
    }       
}

void score::quicksort(person *array, int left, int right)
{
    assert(array);
    if (left >= right)
        return;
    int index=partsort(array, left, right);

    quicksort(array, left, index-1);
    quicksort(array, index+1, right);
}

int score::partsort(person *array, int left, int right)
{
    person &key=array[right];
    while ( left < right )
    {
        while ( left < right && !isBigger(key, array[left]))
            left++;
        while (left<right && !isBigger(array[right],key))
            right--;
        swap(array[right], array[left]);
    }
    swap(array[right], key);
    return left;
}

void score::sort()
{
    quicksort(data, 0, sample-1);
}
