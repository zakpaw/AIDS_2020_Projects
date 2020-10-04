#include <stdio.h>
#include <stdlib.h>

//#include "LList1.c"
#define CHUNK 18


typedef struct 
{
    long long i, j, k;
    int minus;
} param_t;

typedef struct 
{
        char char_num;
        long long int int_num;
}Number_t;

typedef struct node 
{
        int minus;
        Number_t num;
        struct node* next;
}llist_t;

int Smal_Larg_Eq(llist_t *nums, int length[], int a, int b);
void print_all(llist_t *nums,int howmany);
int chunk_num(int lenght);
void dev_to_chunks(llist_t* numbers, llist_t *nums, int length[],int howmany);
void sum(llist_t *nums, int length[], int where, int a, int b);
void diff(llist_t *nums, int length[], int where, int a, int b);
void max(llist_t *nums, int length[], int howmany);
void min(llist_t *nums, int length[], int howmany);
void read_command(llist_t* nums, int length[], int n);
void evaluate(llist_t* nums, param_t* EQ, int length[]);




long long int mypow(int base, int exp)
{
    long long int result = 1;
    while(exp!=0)
    {
        result *=base;
        --exp;
    }
    return result;
}


int len_of_int(long long int x) 
{
        int counter = 0;
    if( x < 0)
        x *= -1;
        while(x > 9)
        {
                x = x / 10;
                counter++;
        }
        return counter + 1;
}


void free_list(llist_t* head) 
{
    llist_t* tmp = NULL;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}


void llist_push(llist_t** head, Number_t element, int minus) 
{
        llist_t* temp = (llist_t*)malloc(sizeof(llist_t));
        temp->num = element;
        temp->next = *head;
        if(minus == 1)
                temp->minus = 1;
        else
                temp->minus = 0;
        *head = temp;
}


void llist_print(llist_t* head) 
{
        llist_t* begin = head;
        while (head != NULL) 
        {
                if(head->minus == 1 && head == begin)
                        printf("-");
                if(head->num.int_num < mypow(10,CHUNK - 1) && head != begin)
                        for(int i = 0; i < (CHUNK - len_of_int(head->num.int_num)); i++)
                                printf("%d", 0);
        printf("%lld", head->num.int_num);
                head = head->next;
        }
}


llist_t *reverse(llist_t *head) 
{
    llist_t *rev = NULL;
    while(head != NULL)
    {
        llist_push(&rev, head->num, head->minus);
        head = head->next;
    }
    return rev;
}
/*
3
437234243
-928734987234
234543
0=1-2
?
*/
int main()
{
    int  howmany = 0;
    Number_t character;
    character.char_num = 'a';
    character.int_num = 0;
    scanf("%d", &howmany);
    while(getchar()!='\n'); //clean buffer
    int* length = (int*)malloc(howmany);
    llist_t* numbers = (llist_t*)malloc(sizeof(llist_t)*howmany);

    for(int i = 0; i < howmany; i++) 
    {
        llist_t *start = NULL;
        length[i] = 0;
        int minus = 0;
        while (scanf("%c", &character.char_num)) 
        {
            if (character.char_num == '\n') break;
            if (character.char_num == '-') minus = 1;
            else 
            {
                llist_push(&start, character, minus);
                length[i]++;
            }
        }
        numbers[i] = *start;
    }
    llist_t* numbers1 = (llist_t*)malloc(sizeof(llist_t)*howmany);
    dev_to_chunks(numbers1, numbers, length, howmany);
    read_command(numbers1, length, howmany);

    free_list(numbers);
    free_list(numbers1);
    return 0;
}


void read_command(llist_t* nums, int length[], int n) 
{
    param_t* param = (param_t*)malloc(sizeof(param_t));
    char* CMD = (char*)malloc(30*sizeof(char));
    int exit = 0;
    char character;
    int cmd_id = 0;
   
    while (!exit) {
        while (scanf("%c",&character)) 
        {
            CMD[cmd_id] = character;
            if (character == '\n' || character == '\0') 
            {
                cmd_id = 0;
                if (sscanf(CMD, "%lld = %lld - %lld", &param->i, &param->j, &param->k) == 3) 
                {
                    param->minus = 1;
                    evaluate(nums, param, length);
                }
                else if (sscanf(CMD, "%lld = %lld + %lld", &param->i, &param->j, &param->k) == 3) 
                {
                    param->minus = 0;
                    evaluate(nums, param, length);
                }
                for (int i=0; i<30; i++) CMD[i] = 0;
                break;
            }
            cmd_id++;
            if (character == 'm') 
            {
                scanf("%c",&character);
                scanf("%c",&character);
                if (character == 'n') min(nums, length, n);
                if (character == 'x') max(nums, length, n);
            }
            if (character == '?') print_all(nums, n);
            if (character == 'q') exit = 1;
        }
    }
    free(CMD);
}
 
void evaluate(llist_t* nums, param_t* EQ, int length[]) 
{
    if(EQ->minus == 1)
        diff(nums,length, EQ->i, EQ->j, EQ->k);
    else
        sum(nums,length, EQ->i, EQ->j, EQ->k);
}


void diff(llist_t *nums, int length[], int where, int a, int b)
{
    if(nums[a].minus == 0 && nums[b].minus == 1)
    {
        sum(nums, length, where, a ,b);
        return;
    }
    if(nums[a].minus == 1 && nums[b].minus == 0)
    {
        nums[a].minus = 0;
        sum(nums, length, where, a ,b);
        nums[a].minus = 1;
        nums[where].minus = 1;
        return;
    }
    if(nums[a].minus == 1 && nums[b].minus == 1)
    {
        sum(nums, length, where, a, b);
        return;
    }
    

    llist_t* result = NULL;
    if(Smal_Larg_Eq(nums, length, a, b) == 2)
    {
        Number_t x;
        x.char_num = 'a';
        x.int_num = 0;
        llist_push(&result, x, 0);
        nums[where] = *result;
        return;
    }
    int carry = 0;
    int temp, minus = 0;
    if(Smal_Larg_Eq(nums, length, a , b) == 1)
    {
        temp = a;
        a = b;
        b = temp;
        minus = 1;
    }

    int lenA = chunk_num(length[a]);
    int lenB = chunk_num(length[b]);
    int dif = len_of_int(nums[a].num.int_num) - len_of_int(nums[b].num.int_num);
    nums[a] = *reverse(&nums[a]);
    nums[b] = *reverse(&nums[b]);
    llist_t numA = nums[a];
    llist_t numB = nums[b];

    for(int i = 0; i < lenB; i++)
    {
        Number_t sub;
        sub.char_num = 'a';
        sub.int_num = numA.num.int_num - numB.num.int_num - carry;
        if(sub.int_num < 0)
        {
            sub.int_num = sub.int_num + mypow(10 ,len_of_int(sub.int_num));
            carry = 1;
        }
        else 
            carry = 0;
        llist_push(&result, sub, minus);
        if(numB.next !=NULL)
            numB = *numB.next;       
        if(numA.next != NULL)
            numA = *numA.next;
    }

    for(int i = 0; i < dif; i++)
    {
        if(numA.num.int_num == 0 && carry)
        {
            Number_t sub;
            sub.char_num = 'a';
            sub.int_num = numA.num.int_num - carry;
            llist_push(&result, sub, minus);
        }
        if(carry == 0 && &numA != NULL)
            llist_push(&result, numA.num, minus);
        carry = 0;
        if(numA.next !=NULL)
            numA = *numA.next;
        else 
            break;
    }
    while(result->num.int_num == 0)
    {
        llist_t* final = NULL;
        final = result->next;
        result = final;
        free_list(final);
    }
    if(where != a)
        nums[a] = *reverse(&nums[a]);
    if(where != b)
        nums[b] = *reverse(&nums[b]);
    nums[where] = *result;
}


void sum(llist_t *nums, int length[], int where, int a, int b)
{
    if(nums[a].minus == 1 && nums[b].minus == 0)
    {
        nums[a].minus = 0;
        diff(nums,length, where, a, b);
        nums[a].minus = 1;
        nums[where].minus = 0;
        return;
    }
    if(nums[a].minus == 0 && nums[b].minus == 1)
    {
        diff(nums,length, where, b, a);
        return;
    }


    llist_t *result= NULL;
    int carry = 0;
    int temp;
    if(length[a] > length[b])
    {
        temp = a;
        a = b;
        b = temp;
    }
    int lenA = chunk_num(length[a]);
    int lenB = chunk_num(length[b]);
    int dif = len_of_int(nums[b].num.int_num) - len_of_int(nums[a].num.int_num);
    nums[a] = *reverse(&nums[a]);
    nums[b] = *reverse(&nums[b]);
    llist_t numA = nums[a];
    llist_t numB = nums[b];

    for(int i = 0; i < lenA; i++)
    {
        Number_t sum, x;
        x.char_num = 'a';
        sum.int_num = numA.num.int_num + numB.num.int_num + carry;
        x.int_num = sum.int_num % mypow(10 ,CHUNK);

        llist_push(&result, x, numA.minus);
        carry = sum.int_num / mypow(10 ,CHUNK);
        if(numA.next != NULL)
            numA = *numA.next;
        if(numB.next !=NULL)
            numB = *numB.next;
    }   
    
    for(int i = 0; i < dif; i++)
    {
        if(&numB == NULL || carry == 0)
            break;
        Number_t sum, x;
        x.char_num = 'a';
        sum.int_num = numB.num.int_num + carry;
        x.int_num = sum.int_num % mypow(10 ,CHUNK);
        llist_push(&result, x, numA.minus);
        carry = sum.int_num / mypow(10 ,CHUNK);
        if(numB.next !=NULL)
            numB = *numB.next;
    }
    
    if(carry) 
    {
    Number_t x;
    x.char_num = 'a';
    x.int_num = carry;
    llist_push(&result, x, numA.minus);
    }
    if(where != a)
        nums[a] = *reverse(&nums[a]);
    if(where != b)
        nums[b] = *reverse(&nums[b]);
    nums[where] = *result;
}


int Smal_Larg_Eq(llist_t *nums, int length[], int a, int b)
{
    /*
    0 -> 1st number is larger
    1 -> 2nd number is larger
    2 -> numbers are equal
    */
    llist_t numA = nums[a];
    llist_t numB = nums[b];

    int lenA = length[a];
    int lenB = length[b];
    if(numA.minus == 1 && numB.minus == 0)
        return 1;
    if(numA.minus == 0 && numB.minus == 1)
        return 0;
    if(lenA > lenB)
    {
        if(numA.minus == 0)
            return 0;
        else
            return 1;
    }
    if(lenB > lenA)
    {
        if(numA.minus == 0)
            return 1;
        else
            return 0;        
    }

    while(&numA != NULL && &numB != NULL)
    {
        if(numA.num.int_num < numB.num.int_num)
            return 1;
        else if(numA.num.int_num > numB.num.int_num)
            return 0;
        if(numA.next != NULL)
            numA = *numA.next;
        else 
            break;
        if(numB.next != NULL)
            numB = *numB.next;
        else
            break;
    }
    numA = nums[a];
    numB = nums[b];
    return 2;
}


void dev_to_chunks(llist_t* numbers, llist_t *nums, int length[],int howmany)
{
    for(int i = 0; i < howmany; i++)
    {
        llist_t *start = NULL;
        Number_t temp;
        temp.char_num = 'a';
        temp.int_num = 0;
        int minus = 0;
        for(int j = 0; j < length[i]; j++)
        {
            int test = j % CHUNK;
            temp.int_num += ((int)nums[i].num.char_num - (int)('0')) * mypow(10, j % CHUNK);
                
            if((j > 0 && test == CHUNK -1) || j == length[i] - 1)
            {
                llist_push(&start, temp, nums[i].minus);
                temp.int_num = 0;
                if (j != length[i] - 1)
                    nums[i] = *nums[i].next;
            }
            else 
                nums[i] = *nums[i].next;
        }
        numbers[i] = *start;
    }
}


void max(llist_t *nums, int length[], int howmany)
{
    int max = 0;
    for(int i = 1; i < howmany; i++)
        if(Smal_Larg_Eq(nums, length, max, i) == 1)
            max = i;
    llist_print(&nums[max]);
    printf("\n");
}


void min(llist_t *nums, int length[], int howmany)
{
    int min = 0;
    for(int i = 1; i < howmany; i++)
        if(Smal_Larg_Eq(nums,length, min, i) == 0)
            min = i;
    llist_print(&nums[min]);   
    printf("\n");
}


void print_all(llist_t *nums,int howmany)
{
    for(int i = 0; i < howmany; i++)
    {
        llist_print(&nums[i]);
        printf("\n");
    }
}


int chunk_num(int lenght)
{
    int result = 0;
    for(int i=0;i<=lenght;i++)
        if (i % CHUNK == 1)
            result++;
    return result;
}
