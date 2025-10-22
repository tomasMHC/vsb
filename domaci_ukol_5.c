#include "stdio.h"
#include "stdlib.h"

void fill_array(char* arr, int radky, int sloupce) {
    for (int i = 0; i < radky*sloupce; i++) {
        arr[i] = '.';
    }
}
void print_matrix(char* matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void doprava(int* direction_x, int* direction_y) {
    
    if (*direction_x == 1 && *direction_y == 0) { //pravo
        *direction_x = 0;
        *direction_y = 1;
    }
    else if (*direction_x == 0 && *direction_y == 1) { //dolu
        *direction_x = -1;
        *direction_y = 0;
    }
    else if (*direction_x == -1 && *direction_y == 0) { //levo
        *direction_x = 0;
        *direction_y = -1;
    }
    else if (*direction_x == 0 && *direction_y == -1) { //nahoru
        *direction_x = 1;
        *direction_y = 0;
    }
}

void doleva(int* direction_x, int* direction_y) {
    
    if (*direction_x == 1 && *direction_y == 0) { //pravo
        *direction_x = 0;
        *direction_y = -1;
    }
    else if (*direction_x == 0 && *direction_y == 1) { //dolu
        *direction_x = 1;
        *direction_y = 0;
    }
    else if (*direction_x == -1 && *direction_y == 0) { //levo
        *direction_x = 0;
        *direction_y = 1;
    }
    else if (*direction_x == 0 && *direction_y == -1) { //nahoru
        *direction_x = -1;
        *direction_y = 0;
    }
}

int index_2d_na_1d(int y, int x, int sloupce) {
    return y * (sloupce) + x;
}

int main() {
    // Keep this line here
    int radky, sloupce;
    scanf("%d %d", &radky, &sloupce);
    char* matrix = (char*) malloc(radky * sloupce * sizeof(char));
    fill_array(matrix, radky, sloupce);
    // print_matrix(matrix, radky, sloupce);

    char ch = ' ';
    int direction_x = 1;
    int direction_y = 0;
    int x = 0;
    int y = 0;
    int pocet_zelvicek = 1;
    int k=0; int l = 0; int direction_k = 1; int direction_l = 0;
    int p=0; int q=0; int direction_p = 1; int direction_q = 0;

    scanf("%c", &ch);
    while (ch != 'x') {
        scanf(" %c", &ch);
        if (ch == 'r') {
            doprava(&direction_x, &direction_y);
            if (pocet_zelvicek == 2) {
                doprava(&direction_k, &direction_l); 
            }
            else if (pocet_zelvicek == 3) {
                doprava(&direction_k, &direction_l);
                doprava(&direction_p, &direction_q);
            }
        }
        else if (ch == 'l') {
            doleva(&direction_x, &direction_y);
            if (pocet_zelvicek == 2) {
                doleva(&direction_k, &direction_l);
            }
            else if (pocet_zelvicek == 3) {
                doleva(&direction_k, &direction_l);
                doleva(&direction_p, &direction_q);
            }
        }
        else if (ch == 'o') {
            int index = index_2d_na_1d(y, x, sloupce);
            int index2=0;
            int index3=0;
            matrix[index] = 'o';
            if (pocet_zelvicek == 2) {
                index2 = index_2d_na_1d(l, k, sloupce);
                if (matrix[index2]== 'o') {
                    matrix[index2] = '.';
                }
                else {
                    matrix[index2] = 'o';
                }
            }
            else if (pocet_zelvicek == 3) {
                index2= index_2d_na_1d(l,k,sloupce);
                index3 = index_2d_na_1d(q,p,sloupce);
                if (matrix[index2] == 'o') {
                    matrix[index2] = '.';
                }
                else {
                    matrix[index2] = 'o';
                }
                if (matrix[index3] == 'o') {
                    matrix[index3] = '.';
                }
                else {
                    matrix[index3] = 'o';
                }
            }
        }
        else if(ch == 'm') {
            x = x+direction_x;
            y = y+direction_y;
            if (x < 0) {
                x = sloupce - 1;
            }
            else if (x > sloupce-1) {
                x = 0;
            }
            if (y < 0) {
                y = radky - 1;
            }
            else if (y > radky-1) {
                y = 0;
            }

            if (pocet_zelvicek == 2) {
                k = k+direction_k;
                l = l+direction_l;
                if (k < 0) {
                    k = sloupce - 1;
                }
                else if (k > sloupce-1) {
                    k = 0;
                }
                if (l < 0) {
                    l = radky - 1;
                }
                else if (l > radky-1) {
                    l = 0;
                }
            }
            else if (pocet_zelvicek == 3) {
                p = p+direction_p;
                q = q+direction_q;
                if (p < 0) {
                    p = sloupce - 1;
                }
                else if (p > sloupce-1) {
                    p = 0;
                }
                if (q < 0) {
                    q = radky - 1;
                }
                else if (q > radky-1) {
                    q = 0;
                }

                k = k+direction_k;
                l = l+direction_l;
                if (k < 0) {
                    k = sloupce - 1;
                }
                else if (k > sloupce-1) {
                    k = 0;
                }
                if (l < 0) {
                    l = radky - 1;
                }
                else if (l > radky-1) {
                    l = 0;
                }
            }

        }
        else if (ch == 'f') {
            pocet_zelvicek = pocet_zelvicek + 1;
            if (pocet_zelvicek > 3) {
                pocet_zelvicek = 3 ;
            }
        }
        // print_matrix(matrix, radky, sloupce); printf("\n");
    }
    print_matrix(matrix, radky, sloupce);
    free(matrix);
    return 0;
}