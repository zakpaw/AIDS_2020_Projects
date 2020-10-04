#pragma once
#include <iostream>
#include <queue>
using namespace std;

const int MAXINT = 2147483647;

bool EdmundMaxFlow(int **C, int max)
{
    queue<int> Q;
    int **F = new int *[max];
    int *P, *CFP;
    int s = 0, t = max - 1, fmax = 0, cp, x, y, i, j;
    bool esc;

    for (i = 0; i < max; i++)
        F[i] = new int[max];

    P = new int[max];
    CFP = new int[max];

    for (i = 0; i < max; i++)
        for (j = 0; j < max; j++)
            F[i][j] = 0;

    while (true)
    {
        for (i = 0; i < max; i++)
            P[i] = -1;
        P[s] = -2;
        CFP[s] = MAXINT;

        while (!Q.empty())
            Q.pop();
        Q.push(s);

        esc = false;
        while (!Q.empty())
        {
            x = Q.front();
            Q.pop();
            for (y = 0; y < max; y++)
            {
                cp = C[x][y] - F[x][y];
                if (cp && (P[y] == -1))
                {
                    P[y] = x;
                    CFP[y] = CFP[x] > cp ? cp : CFP[x];
                    if (y == t)
                    {
                        fmax += CFP[t];
                        i = y;
                        while (i != s)
                        {
                            x = P[i];
                            F[x][i] += CFP[t];
                            F[i][x] -= CFP[t];
                            i = x;
                        }
                        esc = true;
                        break;
                    }
                    Q.push(y);
                }
            }
            if (esc)
                break;
        }
        if (!esc)
            break;
    }

    bool valid = true;
    for (x = 0; x < max; x++)
    {
        for (y = 0; y < max; y++)
        {
            if (y == max - 1)
            {
                //cout << C[x][y] << " - " << F[x][y] << endl;
                if (F[x][y] - C[x][y] != 0)
                {
                    valid = false;
                    for (i = 0; i < max; i++)
                        delete[] F[i];

                    delete[] F;
                    delete[] P;
                    delete[] CFP;
                    return valid;
                }
            }
        }
    }

    for (i = 0; i < max; i++)
        delete[] F[i];

    delete[] F;
    delete[] P;
    delete[] CFP;

    return valid;
}
