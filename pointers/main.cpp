#include <iostream>

int main()
{
    int *pointerInt = nullptr; // an int pointer
    int exampleInt = 10;
    pointerInt = &exampleInt;
    
    std::cout << "example value" << exampleInt << std::endl;
    std::cout << "example memory address" << pointerInt << std::endl;
}