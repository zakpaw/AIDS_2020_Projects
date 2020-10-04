#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "task.h"
using namespace std;

class Group_tasks
{
    string name;
    int total_phours;
    vector<Task> tasks;
    int total_min_hours; // sum min hours of all tasks

    friend class Plague;

public:
    int task_count;

    Group_tasks(string name, int task_count, int total_phours)
    {
        this->name = name;
        this->task_count = task_count;
        this->total_phours = total_phours;
        int temp = 0;
        for (int i = 0; i < task_count; i++)
        {
            tasks.push_back(input_task());
            temp += tasks[i].min_humhours;
        }
        this->total_min_hours = temp;
    }
};

Group_tasks input_group_tasks()
{
    string name;
    int task_count, total_phours;
    //scanf(" %s", &name);
    cin >> name;
    scanf(" %d", &task_count);
    scanf(" %d", &total_phours);

    return Group_tasks(name, task_count, total_phours);
}
