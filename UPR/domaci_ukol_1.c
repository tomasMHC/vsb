#include <stdio.h>

int main() {
    int a=9420;

    printf("Bankovka 5000: %dx\n", a/5000);
    a=a%5000;
    printf("Bankovka 2000: %dx\n", a/2000);
    a=a%2000;
    printf("Bankovka 1000: %dx\n", a/1000);
    a=a%1000;
    printf("Bankovka 500: %dx\n", a/500);
    a=a%500;
    printf("Bankovka 200: %dx\n", a/200);
    a=a%200;
    printf("Bankovka 100: %dx\n", a/100);
    return 0;
}

