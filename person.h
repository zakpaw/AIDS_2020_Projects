#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person
{
    string name;
    int points;
    int total_hours;
    int hours_pday;
    int department;

    friend class Department;
    friend class Plague;

public:
    Person(string name, int points, int total_hours, int hours_pday, int department)
    {
        this->name = name;
        this->points = points;
        this->total_hours = total_hours;
        this->hours_pday = hours_pday;
        this->department = department;
    }
};

Person input_person(int department)
{
    string name;
    int points, total_hours, hours_pday;
    cin >> name;
    scanf(" %d", &points);
    scanf(" %d", &total_hours);
    scanf(" %d", &hours_pday);

    return Person(name, points, total_hours, hours_pday, department);
}
