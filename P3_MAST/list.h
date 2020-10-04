#pragma once
#include <iostream>
#include "node.h"

struct ListNode
{
    node *tree_node;
    struct ListNode *next = NULL;
};


void free_structure(ListNode *head)
{
    ListNode* tmp = NULL;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        delete(tmp);
    }
}

void push(ListNode **head, node *tree_node)
{
    ListNode *newhead = new ListNode;
    newhead->tree_node = tree_node;
    newhead->next = *head;
    *head = newhead;
}
void append(ListNode **head, node *tree_node)
{
    ListNode *current = **(&head);
    static ListNode *last = NULL;
    if (*head != NULL)
    {
        current = *(&last);
        current->next = new ListNode;
        current->next->tree_node = tree_node;
        current->next->next = NULL;
        last = current->next;
        return;
    }
    ListNode *temp = new ListNode;
    temp->tree_node = tree_node;
    temp->next = *head;
    *head = temp;
    last = *head;
}
