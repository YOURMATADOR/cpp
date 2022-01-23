#include <iostream>

void print_piramid(int height)
{
    for (int i = height; i > 0; i--)
    {
        for (int row = 0; row < i; row++)
        {
            std::cout << "& ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    print_piramid(5);
    return 0;
}