#pragma once
#include <iostream>
#include <vector>
#include "department.h"
#include "group_tasks.h"
#include "person.h"
#include "dinic.h"
using namespace std;

bool unique(vector<int> vector, int num);
int mod(int a);

class Plague
{
    class data_index
    {
    public:
        int data;
        int index;
        int day;
        data_index(int data, int index, int day)
        {
            this->data = data;
            this->index = index;
            this->day = day;
        }
    };
    int mode;
    int output_mode;

public:
    int departments_count;

private:
    vector<Department> departments;
    int gr_tasks_count;
    vector<Group_tasks> gr_tasks;
    vector<int> days;
    vector<int> hours;
    int empl_count;
    int task_count;
    vector<Person> best; // best emplyees to choose to have min sum, under said conditions
    int best_points;
    vector<Person> possibly_best;

public:
    Plague(int mode, int output_mode, int departments_count, vector<Department> departments, int gr_tasks_count, vector<Group_tasks> gr_tasks, int empl_count, int task_count)
    {
        this->mode = mode;
        this->output_mode = output_mode;
        this->departments_count = departments_count;
        this->departments = departments;
        this->gr_tasks_count = gr_tasks_count;
        this->gr_tasks = gr_tasks;
        this->days = *(new vector<int>);
        this->hours = *(new vector<int>);
        this->empl_count = empl_count;
        this->task_count = task_count;
        this->best = *(new vector<Person>);
        this->best_points = 1000000; // just an unrealistic number
        for (int i = 0; i < gr_tasks_count; i++)
        {
            for (int j = 0; j < gr_tasks[i].task_count; j++)
            {
                // add only unique days
                if (unique(days, gr_tasks[i].tasks[j].day))
                    days.push_back(gr_tasks[i].tasks[j].day);
                // add only unique hours
                if (unique(hours, gr_tasks[i].tasks[j].time))
                    hours.push_back(gr_tasks[i].tasks[j].time);
            }
        }
    }

    int calculate_nodes_num(vector<Person> empl)
    {
        return 2 + int(empl.size()) + (int(empl.size()) * int(days.size())) + (int(empl.size()) * int(days.size()) * int(hours.size())) + task_count + gr_tasks_count;
    }

    Graph calculate_max_flow(vector<Person> empl)
    {
        int total_nodes = calculate_nodes_num(empl) - 1;
        Graph graph(total_nodes + 1);
        int current = 1;
        vector<data_index> pdt; // person date time
        int curr_emp, curr_day;
        for (int emp = 0; emp < empl.size(); emp++)
        {
            graph.addEdge(0, current++, empl[emp].total_hours);
            curr_emp = current - 1;
            for (int day = 0; day < days.size(); day++)
            {
                graph.addEdge(curr_emp, current++, empl[emp].hours_pday);
                curr_day = current - 1;
                for (int h = 0; h < hours.size(); h++)
                {
                    graph.addEdge(curr_day, current++, 1);
                    pdt.push_back(data_index(hours[h], current - 1, days[day]));
                }
            }
        }
        int curr_group, temp_cap;
        for (int gr = 0; gr < gr_tasks_count; gr++)
        {
            temp_cap = gr_tasks[gr].total_phours - gr_tasks[gr].total_min_hours;
            // group --- end
            graph.addEdge(current++, total_nodes, temp_cap);
            curr_group = current - 1;
            for (int task = 0; task < gr_tasks[gr].task_count; task++)
            {
                temp_cap = gr_tasks[gr].tasks[task].max_humhours - gr_tasks[gr].tasks[task].min_humhours;
                // task --- group
                graph.addEdge(current++, curr_group, temp_cap);
                // task --- end
                graph.addEdge(current - 1, total_nodes, gr_tasks[gr].tasks[task].min_humhours);
                for (int p_dt = 0; p_dt < pdt.size(); p_dt++)
                {
                    // time --- task
                    if (pdt[p_dt].data == gr_tasks[gr].tasks[task].time && pdt[p_dt].day == gr_tasks[gr].tasks[task].day)
                        graph.addEdge(pdt[p_dt].index, current - 1, 1);
                }
            }
        }
        graph.DinicMaxflow(0, total_nodes);
        return graph;
    }

    bool verify(Graph graph)
    {
        int iterator = graph.V - 2;

        for (int gr = gr_tasks_count - 1; gr >= 0; gr--)
        {
            for (int tsk = gr_tasks[gr].task_count - 1; tsk >= 0; tsk--)
            {
                if (graph.adj[iterator][1].flow - graph.adj[iterator][1].C != 0)
                    return false;
                iterator--;
            }
            if (graph.adj[iterator][0].flow - graph.adj[iterator][0].C != 0)
                return false;
            iterator--;
        }
        return true;
    }

    void mode_one(int *temp, int which)
    {
        for (int i = 0; i <= departments[which].num_empl; i++)
        {
            temp[which] = i;
            if (which == departments_count - 1)
            {
                int sum = 0;
                for (int j = 0; j < departments_count; j++)
                {
                    for (int k = 0; k < temp[j]; k++)
                    {
                        possibly_best.push_back(departments[j].empl[k]);
                        sum += departments[j].empl[k].points;
                    }
                }
                if (sum < best_points)
                {
                    if (verify(calculate_max_flow(possibly_best)))
                    {
                        best = possibly_best;
                        best_points = sum;
                    }
                }
                /*
                for (int i = 0; i < possibly_best.size(); i++)
                    cout << possibly_best[i].points << " ";
                cout << endl;*/
                possibly_best.clear();
            }
            else
                mode_one(temp, which + 1);
        }
    }

    void run()
    {
        if (mode == 1)
            mode_one(new int[departments_count], 0);
        else if (mode == 2)
        {
            cout << "not yet ready\n";
        }
        else
        {
            cout << "not yet ready\n";
        }

        if (output_mode == 1)
        {
            cout << best_points << endl;
            for (int i = 0; i < best.size(); i++)
                departments[best[i].department].add_working();
            for (int i = 0; i < departments_count; i++)
                if (departments[i].empl_working > 0)
                    cout << departments[i].name << " " << departments[i].empl_working << endl;
        }
        else if (output_mode == 2)
        {
            cout << best_points << endl;
            for (int i = 0; i < best.size(); i++)
                departments[best[i].department].add_working();
            for (int i = 0; i < departments_count; i++)
            {
                if (departments[i].empl_working > 0)
                    cout << departments[i].name << " " << departments[i].empl_working << endl;
                for (int j = 0; j < best.size(); j++)
                {
                    if (best[j].department == i)
                    {
                        cout << best[j].name << " " << best[j].total_hours << endl;
                        for (int x = 0; x < gr_tasks_count; x++)
                        {
                            for (int y = 0; y < best[j].total_hours; y++)
                                cout << gr_tasks[x].name << " " << gr_tasks[x].tasks[y].day << " " << gr_tasks[x].tasks[y].time << endl;
                        }
                    }
                }
            }
        }
    }
};

int mod(int a)
{
    if (a < 0)
        return -a;
    return a;
}

bool unique(vector<int> vector, int num)
{
    for (int i = 0; i < vector.size(); i++)
        if (vector[i] == num)
            return false;
    return true;
}

Plague input_plague()
{
    int mode, output, dep_c, gr_c, empl_count = 0, task_count = 0;
    scanf(" %d", &mode);
    scanf(" %d", &output);
    scanf(" %d", &dep_c);

    vector<Department> depar;
    for (int i = 0; i < dep_c; i++)
    {
        depar.push_back(input_department(i));
        empl_count += depar[i].num_empl;
    }
    scanf(" %d", &gr_c);

    vector<Group_tasks> gr_tasks;
    for (int i = 0; i < gr_c; i++)
    {
        gr_tasks.push_back(input_group_tasks());
        task_count += gr_tasks[i].task_count;
    }

    return Plague(mode, output, dep_c, depar, gr_c, gr_tasks, empl_count, task_count);
}