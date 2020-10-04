#pragma once
#include <iostream>
#include "tree.h"
#include "largest_sum.h"


int leaf_leaf(node first, node second)
{
    if (first.data == second.data)
        return 1;
    return 0;
}

bool branch_leaf(node* root, int num) 
{ 
    if (root == NULL) 
        return false;
    if (root->data == num) 
        return true; 
    bool res1 = branch_leaf(root->child, num); 
    if(res1) 
        return true;
    bool res2 = branch_leaf(root->brother, num); 
    return res2; 
}

int branch_branch(int **arr, node *first_ptr, node *second_ptr)
{
    node *first = first_ptr;
    node *second = second_ptr;
    int width = 0, height = 0;
    while (first)
    {
        first = first->brother;
        width++;
    }
    while (second)
    {
        second = second->brother;
        height++;
    }
    first = first_ptr;
    second = second_ptr;

    int **mini_arr = new int *[height];
    for (int i = 0; i < height; i++)
    {
        first = first_ptr;
        mini_arr[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            mini_arr[i][j] = arr[second->index][first->index];
            first = first->brother;
        }
        second = second->brother;
    }

    int max = 0;
    max = largest_sum(mini_arr, width, height);

    first = first_ptr;
    second = second_ptr;
    for (int i = 0; i < width + height; i++)
    {
        if(i < width)
        {
            if (arr[second->father->index][first->index] > max)
                max = arr[second->father->index][first->index];
            first = first->brother;
            if (i == width - 1)
                first = first_ptr;
        }
        else
        {
            if (arr[second->index][first->father->index] > max)
                max = arr[second->index][first->father->index];
            second = second->brother;
        }
    }
    //for (int i = 0; i < height; i++)
    //    delete[] mini_arr[i];
    delete[] mini_arr;
    return max;
}

void fill_hashtable(tree_t first, tree_t second)
{
    int height = second.num_branches + second.num_leafs;
    int width = first.num_branches + first.num_leafs;
    node *first_arr = first.arr_of_ptrs;
    node *second_arr = second.arr_of_ptrs;
    int **arr = new int *[height];

    for (int i = 0; i < height; i++)
    {
        arr[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            if (i < second.num_leafs && j < first.num_leafs)
                arr[i][j] = leaf_leaf(first_arr[j], second_arr[i]);
            else if(i >= second.num_leafs && j >= first.num_leafs)
                arr[i][j] = -1;
            else
            {
                if(j >= second.num_leafs)
                    arr[i][j] = branch_leaf(first_arr[j].child, second_arr[i].data);
                else
                    arr[i][j] = branch_leaf(second_arr[i].child, first_arr[j].data);
            }
        }
    }
    
    for (int i = height - 1; i >= second.num_branches; i--)
        for (int j = width - 1; j >= first.num_branches; j--)
            if (arr[i][j] == -1)
                arr[i][j] = branch_branch(arr, first_arr[j].child, second_arr[i].child);

    printf("%d", (first.num_leafs - arr[second.num_leafs][first.num_leafs]));
    printf("\n");
    for (int i = 0; i < height; i++)
        delete[] arr[i];
    delete[] arr;
}
