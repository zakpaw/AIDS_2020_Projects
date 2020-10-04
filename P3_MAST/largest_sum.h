#pragma once
#include <iostream>

void find_max(int *arr, bool* banned, int width, int height, int prev_depth, int prev_sum, int *max_sum)
{
    int sum, depth = prev_depth + 1;
    
    for (int i = 0; i < width; i++)
    {
        if (banned[i])
            continue;
        banned[i] = true;
        
        sum = prev_sum + arr[(depth - 1)*width+i];
        
        if (depth != height)
            find_max(arr, banned, width, height, depth, sum, max_sum);
        
        else if (sum > *max_sum)
            *max_sum = sum;

        banned[i] = false;
    }
}

int largest_sum(int** values, int l, int h) {
    int max_sum;
    int width = l >= h ? l : h;
    int height = l <= h ? l : h;
    bool *banned = new bool[height];
    int* arr = new int [height * width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (l < h)
                arr[i * width + j] = values[j][i];
            else
                arr[i * width + j] = values[i][j];
            if (i == 0)
                banned[j] = false;
        }
    }
    find_max(arr, banned, width, height, 0, 0, &max_sum);
    delete[] banned;
    delete[] arr;
    return max_sum;
}