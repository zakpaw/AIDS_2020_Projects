#include <iostream>

struct Node
{
    bool click;
    int returning;
    int data;
    struct Node *next = NULL;
    struct Node *start = NULL;
};

void free_structure(struct Node* head) 
{
    struct Node* tmp = NULL;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        delete(tmp);
    }
}

void append(struct Node** head, int num) 
{
    struct Node *current = **(&head);
    static struct Node *last = NULL;
    static struct Node *start = NULL;
    if (*head != NULL)
    {
        current = *(&last);
        current->next = new Node;
        current->next->data = num;
        current->next->click = false;
        current->next->returning = 0;
        current->next->next = NULL;
        current->next->start = start;
        last = current->next;
        return;
    }
    struct Node *temp = new Node;
    temp->data = num;
    temp->next = *head;
    temp->click = false;
    temp->returning = 0;
    *head = temp;
    start = *head;
    last = *head;
    temp->start = start;
}

typedef struct Task
{
    int num_of_instructions;
    int *instruction;
}Task_t;

int rotate(bool click, struct Node **rotor, int num)
{
    if (click == true)
    {
        if ((*rotor)->next != NULL)
            (*rotor) = (*rotor)->next;
        else
            (*rotor) = (*rotor)->start;
    }
    struct Node *temp = *rotor;
    for (int i = 1; i < num; i++)
    {
        if (temp->next != NULL)
            temp = temp->next;
        else
            temp = temp->start;
    }
    return num + temp->data;
}

int reflect(int *reflector, int number, int num_of_letters)
{
    if(number > num_of_letters)
        number = number % num_of_letters;
    number = number - 1;
    if (number < 0)
        return reflector[num_of_letters+number];
    return reflector[number];
}


void encode(struct Node **rotorsOG, Task_t *task, int **reflectors, int num_of_letters, int* to_number)
{
    struct Node **rotors = new Node*[(task->num_of_instructions - 1) / 2];
    for(int i = 0; i < (task->num_of_instructions - 1) / 2; i++)
    {
        rotors[i] = rotorsOG[task->instruction[2 * i]];
        for (int j = 0; j < task->instruction[2 * i + 1] - 1; j++) //set position
            rotors[i] = rotors[i]->next;
    }
    int click1 = 0;
    bool click2 = false, click2_done = false, click = false;
    int num = 0;
    while (true)
    {
        scanf(" %d", &num);
        if (num < 1)
            break;

        for (int i = 0; i < (task->num_of_instructions - 1) / 2; i++)
        {
            if (i == 0)
            {
                num = rotate(true, &rotors[0], num);
                num = reflect(to_number, num, num_of_letters);
                click1++;
            }
            else if(i == 1 && rotors[0]->click && click1 > 1)
            {
                num = rotate(true, &rotors[1], num);
                num = reflect(to_number, num, num_of_letters);
                click = rotors[1]->click;
                click2 = true;
            }
            else if(i == 2 && click && click2_done == true)
            {
                if (click2 = false)
                    rotate(true, &rotors[1], 0);
                num = rotate(true, &rotors[2], num);
                num = reflect(to_number, num, num_of_letters);
                click = false;
            }
            else
            {
                num = rotate(false, &rotors[i], num);
                num = reflect(to_number, num, num_of_letters);
            }
        }
        if (click2 == true)
            click2_done = true;
        click2 = false;
        num = reflect(reflectors[task->instruction[task->num_of_instructions - 1]], num, num_of_letters);
        for (int j = (task->num_of_instructions - 1) / 2 - 1; j >= 0; j--)
        {
            struct Node *temp = rotors[j];
            for (int i = 1; i < num; i++)
            {
                if (temp->next != NULL)
                    temp = temp->next;
                else
                    temp = temp->start;
                    
            }
            num = num + temp->returning;
            num = reflect(to_number, num, num_of_letters);
        }
        printf("%d ", num);
    }
    while(getchar()=='0');
    printf("\n");
    delete[] rotors;
}

void set_returning(struct Node **rotor, int num_of_letters)
{
    struct Node *rot = NULL;
    for (int i = 0; i <= num_of_letters; i++)
    {
        rot = (*rotor);
        int how = rot->data;
        if ((*rotor)->data < 0)
            how = num_of_letters + rot->data;
        for (int j = 0; j < how; j++)
        {
            if (rot->next != NULL)
                rot = rot->next;
            else
                rot = rot->start;
        }
        rot->returning = (*rotor)->data * -1;
        if ((*rotor)->next != NULL)
            (*rotor) = (*rotor)->next;
            
        else
            (*rotor) = (*rotor)->start;
    }
    (*rotor) = rot;
    (*rotor) = (*rotor)->start;
}



int **input_reflectors(int num_of_reflectors, int num_of_letters)
{
    int **reflectors = new int *[num_of_reflectors];
    for (int i = 0; i < num_of_reflectors; i++)
    {
        int *reflect = new int[num_of_letters];
        for (int j = 0; j < num_of_letters; j++)
        {
            int num;
            scanf("%d", &num);
            reflect[j] = num;
        }
        reflectors[i] = reflect;
    }
    return reflectors;
}


struct Node **input_rotors(int num_of_rotors, int num_of_letters)
{
    struct Node **rotors = new struct Node*[num_of_rotors];
    int num;
    int num_of_click = 0;
    for (int i = 0; i < num_of_rotors; i++)
    {
        struct Node *rotor = NULL;
        for (int j = 0; j < num_of_letters; j++)
        {
            scanf("%d", &num);
            num = num - (j + 1);
            append(&rotor, num);
        }
        scanf("%d", &num_of_click);
        for (int j = 0; j < num_of_click; j++)
        {
            scanf("%d", &num);
            for (int k = 1; k < num; k++)
                rotor = rotor->next;
            rotor->click = true;
            rotor = rotor->start;
        }
        rotor = rotor->start;
        rotors[i] = rotor;
    }
    return rotors;
}

Task_t *input_task()
{
    int howmany_rotors;
    scanf("%d", &howmany_rotors);
    Task_t *task = new Task_t[(howmany_rotors * 2) + 1];
    int instruction_size = (howmany_rotors * 2) + 1;
    task->instruction = new int[instruction_size];
    for (int i = 0; i < instruction_size; i++)
    {
        int input;
        scanf("%d", &input);
        task->instruction[i] = input;
    }
    task->num_of_instructions = howmany_rotors * 2 + 1;
    return task;
}

int main()
{
    int num_of_letters = 0, num_of_rotors = 0, num_of_reflectors = 0;
    int howmany = 0;
    scanf("%d", &num_of_letters);
    scanf("%d", &num_of_rotors);
    struct Node **rotors = input_rotors(num_of_rotors, num_of_letters);
    for (int i = 0; i < num_of_rotors; i++)
        set_returning(&rotors[i], num_of_letters);
    scanf("%d", &num_of_reflectors);
    int **reflectors = input_reflectors(num_of_reflectors, num_of_letters);
    int *to_number = new int[num_of_letters];
    for (int i = 0; i < num_of_letters; i++)
        to_number[i] = i + 1;
    scanf("%d", &howmany);
    for (int i = 0; i < howmany; i++)
    {
        Task_t *task = input_task();
        encode(rotors, task, reflectors, num_of_letters, to_number);
        delete[] task->instruction;
        delete task;
    }
    delete[] to_number;
    for (int i = 0; i < num_of_rotors; i++)
        free_structure(rotors[i]);
    delete[] rotors;
    for (int i = 0; i < num_of_reflectors; i++)
        delete[] reflectors[i];
    delete[] reflectors;
    return 0;
}
