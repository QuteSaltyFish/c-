#include"display.h"
#include<iostream>

Display::Display(int width, int height, const std::string& title)
{
    std::cout<<"Constructor!\n";
}

Display::~Display()
{
    std::cout<<"Destructor!\n";
}
