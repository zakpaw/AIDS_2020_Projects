#include "Plague.h"
#include <iostream>
#include <ctime>

int main()
{
    //clock_t time = clock();
    freopen("t2.txt", "r", stdin);
    Plague plague = input_plague();
    //time = clock() - time;
    plague.run();
    //cout << "run: " << double(clock() - time) / CLOCKS_PER_SEC << endl;

    return 0;
}
