#pragma once
#include <iostream>

struct node
{
    int data;
    int index;
    node *father = NULL;
    node *child = NULL;
    node *brother = NULL;
};

void add_child(node **father, int data)
{
    if (father == NULL)
        return;
    node *newchild = new node;
    newchild->father = *father;
    newchild->data = data;
    (*father)->child = newchild;
}

void add_brother(node **level, int data)
{
    if (*level == NULL)
        return;
    while ((*level)->brother != NULL)
        *level = (*level)->brother;
    node *newbrother = new node;
    newbrother->father = (*level)->father;
    newbrother->data = data;
    (*level)->brother = newbrother;
}

void free_node()
{
    return;
}