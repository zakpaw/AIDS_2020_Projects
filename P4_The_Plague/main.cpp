#include "Plague.h"
#include <iostream>
#include <ctime>

int main()
{
    freopen("sample_input.txt", "r", stdin);
    Plague plague = input_plague();
    plague.run();
    return 0;
}
