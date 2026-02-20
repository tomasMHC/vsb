//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// petr.olivka@vsb.cz, Department of Computer Science, VSB-TUO
//
// Empty project
//
//***************************************************************************

#include <stdio.h>
#include <string.h>

// Functions

void my_asm_function();
void my_max();
void my_suma();
void my_strlen();

// void some_asm_function();

// Variables

int g_int_a = 333, g_int_b=111111;
int g_int_max;
char g_str[]="Zabit nelze,pustit!";
int g_str_len;
long g_long_pole[]= { 1 ,2,3,4,5,6,7,8,9,10};
long g_suma;

// type g_some_c_variable;



int main()
{
    printf("a=%d b= %d\n", g_int_a, g_int_b);
    printf("str = %s\n",  g_str);
    my_asm_function();
    printf("a=%d b= %d\n", g_int_a, g_int_b);
    printf("str = %s\n",  g_str);

    my_max();
    printf("max=%d\n", g_int_max);

    my_suma();
    printf("suma=%ld\n", g_suma);

    my_strlen();
    printf("len = %ld\n", strlen(g_str));

}
