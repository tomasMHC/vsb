#include <stdio.h>
int a = 14;
int b = 6;
int modulo() {
    printf("Modulo %d // %d = %d\n", a,b, a % b);
    return 0;
}
int main() {
int a = 1;
int b = a = 5;
printf("%d\n", a);
printf("%d\n", b);

modulo();
return 0;
}