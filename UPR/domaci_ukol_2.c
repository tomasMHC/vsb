#include <stdio.h>

int main() {
    int obrazec = 0;
    int a = 0;
    int b = 0;

    scanf("%d%d%d", &obrazec, &a, &b);

    // Zde můžete pracovat s proměnnými `obrazec`, `a`, `b`, které byly načteny ze vstupu programu

    if (obrazec == 0) {
        for (int i = 0; i < b; i++) {
            for (int j = 0; j < a; j++) {
                printf("x");
            }
            printf("\n");
        }
    }

    if (obrazec == 1) {
        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");

        for (int i = 0; i < b-2; i++) {
            for (int j = 0; j < a; j++) {
                if (j == 0 || j == a-1) {
                    printf("x");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");
    }
    
    if (obrazec == 2) {
        int x = 0;

        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");

        for (int i = 0; i < b-2; i++) {
            for (int j = 0; j < a; j++) {
                if (j == 0 || j == a-1) {
                    printf("x");
                } else {
                    if (x<10){
                        printf("%d", x);
                        x++;} 
                    else {
                        x=0;
                        printf("%d", x);
                        x++;
                    }
                }
            }
            printf("\n");
        }

        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");
    }

    if (obrazec == 3) {
        int c = 0;
        for (int i = 0; i < a; i++) {            
            for (int j = 0; j <= c; j++) {
                if (j == c) {
                    printf("x");
                } 
                else {
                    printf(" ");
                }
            }
            c++;
            printf("\n");
        }
    }

    if (obrazec == 4) {
        int c = a-1;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < a; j++) {
                if (j == c) {
                    printf("x");
                } 
                else {
                    printf(" ");
                }
            }
        printf("\n");
        c=c-1;
        }
    }

    if (obrazec == 5) {
        int c = a;
        for (int i = 0; i < a-1; i++) {

            for (int j = 0; j<a*2-1; j++) {
                if (j == c-1 || j == a-i-1 || j== a+i-1) {
                    printf("x");
                } 
                else {
                    printf(" ");
                } 
            }
            printf("\n");
            c=c-1;
        }  
        for (int k = 0; k<a*2-1; k++) {
            printf("x");
        }
    printf("\n");
    }
        
    if (obrazec == 6) {
        int c = a/2;
        for (int i = 0; i<b; i++) { 
            if (i == 0) {
                for (int i = 0; i<a; i++) {
                    printf("x");
                }
                printf("\n");
            }
            if (i>0) {
                for (int i =0; i<=c; i++) {
                    if (i == c) {
                        printf("x");
                    } 
                    else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }

    if (obrazec == 7) {
        for (int j=0; j<b;j++) {
            if (j == 0 || j==b/2-1) {
                for (int i = 0; i<a; i++) {
                    printf("x");
                }
                printf("\n");
            }
            if ((b/2-1)>j) {
                for (int i = 0; i<a; i++) {
                    if (i == 0 || i == a-1) {
                        printf("x");
                    } 
                    else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
            if (j>=b/2+1) {
                for (int i = 0; i<a; i++) {
                    if (i == 0 ) {
                        printf("x");
                    } 
                    else {
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    }

    if (obrazec == 9) {
        int x = 0;

        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");

        for (int i = 0; i < b-2; i++) {
            x=i;
            for (int j = 0; j < a; j++) {
                if (j == 0 || j == a-1) {
                    printf("x");
                } 
                else {
                    x=x%10;
                    printf("%d", x);
                    x=x+(b-2);
                    if (x>9){
                        x=x-10;
                    }
                }
            }
            printf("\n");
        }

        for (int i = 0; i < a; i++) {
                printf("x");
            }
            printf("\n");
    }

    if (obrazec == 8 ||  obrazec < 0 || obrazec > 9) {
        printf("Neznamy obrazec\n");
    }
    return 0;
}