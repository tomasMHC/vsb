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
int sude_max( int *pole, int N);
int pocet_cislic( char *str);
long faktorial( long n);
void deleni_pole( long *pole, int N, int delitel);

// void some_asm_function();

// Variables


// type g_some_c_variable;


int main()
{
    int i = 13;
    testpar(i++, i++, i++);
    // printf("Obvod %d\n", obvod_troj(3,5,10));

    int pole[] = {1,2,3,4,5,6,7,8,90,10};
    printf("sude max: %d\n", sude_max(pole,10));

    printf("Pocet cislic: %d\n", pocet_cislic("AH0J PR0GR4M4T03"));

    printf("Faktorial %ld\n", faktorial(5));

    long lpole[] = {10,-20,30,-40,50,-60,70,-80,90,-100};
    deleni_pole(lpole,10, 7);
    for (int i = 0; i<10; i++) {
        printf("%ld ", lpole[i]);
    }
}
