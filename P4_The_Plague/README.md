#### The Plague
Imagine that we are a dean of a university faculty.
Due to plague plaguing our city we were obliged to provide help to local hospital by “volunteering” a few persons to work as nurses.
The local hospital sent the list of tasks and time slots and number of volunteers needed in each time slot.
Precisely, a particular slot has minimum requirement, which has to be fulfilled and maximum possible, due to the fact that some tasks may be performed in given time slot but do not have to. The upper limit is caused by considerations like space constraint for maximal number of nurses working at the same room. Moreover the tasks are grouped and each of the groups may have additional requirement of person-hours [for example “cleaning” may consists of two tasks and some work can be done during the time slot of either task].
The few departments of our faculty prepared lists of researchers, given by names, “value” of the researcher, number of hours the persons can work, and number of hours per day the person can work. We can decide how many researchers we take from each department.  
Due to the labour law a researcher cannot work more than x hours per day and y hours in total. The data is provided per researcher, it may depend on the contract.
Due to the laws of nature a researcher cannot work on two tasks in the same time
We consider 3 options: 
1. To take the researchers ordered by the lists [to avoid any suspicion of favoritism between the persons];
2. To take the researchers ordered by the lists and in addition take the staff equitably between departments [i.e. that there will be at most difference of one person between the departments, if some department has less take all from it];
 
#### GOAL:  
We would like to find the number of researchers taken from each department, which minimizes the value spent, satisfying manpower requirements of hospitals. 
Important assumption – you may assume that the number of the departments is a small constant number, like 2 or 5. 
Important requirement – the scheduling modes 1, 2 have to be solved by polynomial exact algorithms. Scheduling mode 2 has to be have “much better” complexity than for mode 1, the difference has to such like between O(n^k) and O(2^kn), where k is the number of the departments. Simply disallowing some cases is not enough.

#### Input:  
[Mode of Scheduling]  
1: Take any number of persons from any department, but in the same order as in the lists, i.e. we can only take second person if we took first from a department.  
2: The same as before (the list order is still a restriction), but in addition the number of persons between departments are to be "equitable", i.e. if we take x persons from some department. It means that we may take x or x-1, and if some department has less than x-1 we have to take all.  
3: Choose persons from the departments at will, ignoring the order on the lists, ignoring personal limits of hours worked per day and setting general limit per day of x for all the scientists. The total limit of hours per person is still present (!) and has to be fulfilled.  
[Mode of Output]  
0: Show number of points.  
1: Show number of points and number of persons chosen from each department.  
2: Show number of points, number of persons chosen from each department and schedule.  
[Number of departments d]  
[Name of the department, number of workers in the department]  
(Name of the researcher, number of points, number of hours, number of hours per day)  
 ...  
(Name of the researcher, number of points, number of hours, number of hours per day)  
 ...  
[Name of Department d, number of persons in department]  
(Name of the researcher, number of points, number of hours, number of hours per day)  
...  
(Name of the researcher, number of points, number of hours, number of hours per day)  
[Number of groups of tasks t]  
[Name of the group 1, number of tasks in the group 1, total needed number of hours required]  
(day, time, min hours required, max hours required)  
...  
(day, time, min hours required, max hours required)  
[Name of a group, number of tasks in the group t, total needed number of hours required]  
(day, time, min hours required, max hours required)  
...  
(day, time, min hours required, max hours required)  

#### Output:
If there is no feasible schedule return NO  
If there is a schedule and option 1 was chosen  
Minimum number of points required  
Name of the department 1, number of persons chosen  
...  
Name of the department d, number of persons chosen  
If there is a schedule and option 2 was chosen  
Minimum number of points required  
Name of the department 1, number of persons chosen x,  
Name of the person chosen, number of hours the person works  
Task to do, day, time,  
...  
Name of the person chosen, number of hours the person works  
Task to do, day, time,  
...  
etc  

#### Sample input:  
1 1  
1  
A 2  
AAAXXX   100 50 8  
BBBYYY   200 20 4  
1  
X 2 4  
1 1 2 5  
1 3 2 2  
#### output:  
300  
A 2  
