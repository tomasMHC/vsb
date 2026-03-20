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

int testpar( int a, int b, int c) {
    printf( "%d %d %d\n", a, b, c);
}

// int obvod_troj( int a, int b, int c);
int max_prvocislo(int *pole, int N);
int longest_number(char * pole);

// void some_asm_function();

// Variables


// type g_some_c_variable;


int main()
{
    int pole[] = { 999, 541, 611, 571, 517, 643, 509, 647, 591, 500 };
    printf("Max prvocislo v poli je: %d\n", max_prvocislo(pole, 8));

    char str[] = "Nejtepleji bylo 20 srpna 2012 kdy byla teplot 40 stupnu.";
    printf("Nejdelsi cislo: %d\n", longest_number(str));
    
}
