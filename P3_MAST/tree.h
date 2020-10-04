#pragma once
#include <iostream>
#include "node.h"
#include "list.h"

typedef struct tempList
{
    struct ListNode *leafs = NULL;
    struct ListNode *branches = NULL;
}temp_list;

typedef struct Tree
{
    struct node *root;
    node *arr_of_ptrs;
    int num_leafs = 0;
    int num_branches = 1;
} tree_t;

void delete_node (node *root)
{
    if (root->child)
        delete_node(root->child);
    if (root->brother) 
        delete_node(root->brother);
    delete root;
}

void delete_tree (tree_t *tree)
{
    if (tree->arr_of_ptrs)
        delete[] tree->arr_of_ptrs;
    delete_node(tree->root);
}

node *conv_lists_to_arr(temp_list *lists, int sizeleafs, int sizebranches)
{
    ListNode *leafs = lists->leafs;
    ListNode *branches = lists->branches;
    node *arr = new node[sizeleafs + sizebranches];
    for (int i = 0; i < sizeleafs; i++)
    {
        arr[i] = *(leafs->tree_node);
        leafs = leafs->next;
    }
    free_structure(lists->leafs);
    for (int i = 0; i < sizebranches; i++)
    {
        branches->tree_node->index = i + sizeleafs;
        arr[i + sizeleafs] = *(branches->tree_node);
        branches = branches->next;
    }
    free_structure(lists->branches);
    return arr;
}

void read_from_newick(node **root, tree_t *tree, temp_list *lists, int *identifier, int *index)
{
    char c ='o';
    int num = 0;
    if (scanf("%d", &num)) {}
    else
        scanf("%c", &c);
        
    if (c == ';')
        return;
    else if (c == '(')
    {
        (tree->num_branches)++;
        (*identifier)--;
        add_child(root, *identifier);
        read_from_newick(&(*root)->child, tree, lists, identifier, index);
        push(&lists->branches, (*root));
    }
    else if (c == ',')
    {
        (tree->num_branches)++;
        add_brother(root, *identifier);
        read_from_newick(&(*root)->brother, tree, lists, identifier, index);
    }
    else if (c == ')')
        read_from_newick(&(*root)->father, tree, lists, identifier, index);
    else
    {
        append(&lists->leafs, (*root));
        (tree->num_leafs)++;
        (tree->num_branches)--;
        (*root)->data = num;
        (*root)->index = *index;
        (*index)++;
        read_from_newick(root, tree, lists, identifier, index);
    }
}

tree_t *create_forest(const int howmany)
{
    tree_t *forest = new tree_t[howmany];
    for (int t = 0; t < howmany; t++)
    {
        int identifier = 0, index = 0;
        node *root = new node;
        temp_list templist;
        read_from_newick(&root, &forest[t], &templist, &identifier, &index);
        forest[t].root = root;
        forest[t].arr_of_ptrs = conv_lists_to_arr(&templist, forest[t].num_leafs, forest[t].num_branches);
    }
    return forest;
}