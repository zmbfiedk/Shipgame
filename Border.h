#pragma once
#include <iostream>

class Border
{
private:
    int width;
    int height;

public:
    Border(int width, int height);

    void Draw() const;

    int GetMinX() const;
    int GetMaxX() const;
    int GetMinY() const;
    int GetMaxY() const;
};
