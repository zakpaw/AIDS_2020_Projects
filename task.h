#pragma once
#include <iostream>
using namespace std;
class Task
{
    int day;
    int time;
    int min_humhours;
    int max_humhours;

    friend class Group_tasks;
    friend class Plague;

public:
    Task(int day, int time, int min_humhours, int max_humhours)
    {
        this->day = day;
        this->time = time;
        this->min_humhours = min_humhours;
        this->max_humhours = max_humhours;
    }

    void print()
    {
        std::cout << day << time << min_humhours << max_humhours << std::endl;
    }
};

Task input_task()
{
    int day, time, min_humh, max_humh;
    scanf(" %d", &day);
    scanf(" %d", &time);
    scanf(" %d", &min_humh);
    scanf(" %d", &max_humh);

    return Task(day, time, min_humh, max_humh);
}
