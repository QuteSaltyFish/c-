#pragma once
#include<string>
class Display
{
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();
private:
    Display() {}
};

