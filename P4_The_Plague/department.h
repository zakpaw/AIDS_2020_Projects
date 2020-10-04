#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "person.h"

using namespace std;

class Department
{
public:
    string name;
    int num_empl;
    int sum;
    vector<Person> empl;
    int empl_working;

    friend class Plague;

    Department(string name, int num_empl, int num)
    {
        this->name = name;
        this->num_empl = num_empl;
        this->empl_working = 0;
        int sum = 0;
        for (int i = 0; i < num_empl; i++)
        {
            empl.push_back(input_person(num));
            sum += empl[i].points;
        }
        this->sum = sum;
    }

    void add_working()
    {
        this->empl_working += 1;
    }
};

Department input_department(int num)
{
    string name;
    int num_empl;
    cin >> name;
    scanf(" %d", &num_empl);

    return Department(name, num_empl, num);
}
