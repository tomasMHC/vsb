#include "stdio.h"

int nacitani_vstupu(char* orientace, int* pocet, int* zacatek) {
    int number1=0, number2=0;
    char hist_orientation=' ';
    // printf("Zadaj orientaciu histogramu (v/h): ");
    

    scanf("%c", &hist_orientation);
    if (hist_orientation == 'h') {
        // printf("Orientacia histogramu: %c\n", hist_orientation);
    }
    else {
        // printf("Zadaj spravnu orientaciu (v/h): ");
        printf("Neplatny mod vykresleni"); printf("\n");
        return 1;
    }
    
    // printf("Zadaj pocet cisel a zacatek histogramu: ");
    scanf("%d %d", &number1, &number2);
    // printf("Cisla %d a %d\n", number1, number2);
    *orientace = hist_orientation;
    *pocet = number1;
    *zacatek = number2;

    return 0;
}

void read_histogram(int* hist_pole, int number1) {
    // printf("Zadaj hodnoty: ");
    for (int i = 0; i < number1; i++) {
            scanf("%d", &hist_pole[i]);
        }
    }

void fill_array(int* arr, int size, int start_value, int increment) {
    for (int i = 0; i < size; i++) {
        arr[i] = start_value + i * increment;
    }
}
void vypis_pole(int* pole, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", pole[i]);
    }
    printf("\n");
}

void hashprint(int i) {
    if (i >0) {
        printf(" ");
    }
    for (int j = 0; j < i; j++) {
        printf("#");
    }
}

void countif(int* nums_array, int* hist_array, int size, int hist_size, int* counted_array) {
    for (int i = 0; i < hist_size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (hist_array[i] == nums_array[j]) {
                count++;
                counted_array[j] = counted_array[j] + 1;
            }
        }
    }
}

int max_delka_cisla(int* arr, int size) {
    int delka = 0;
    for (int i = 0; i < size; i++) {
        int number = arr[i];
        int delka_i = 0;
        while (number >= 10) {
            number /= 10;
            delka_i++;
        }
        if (delka_i> delka) {
            delka = delka_i;
        }
    } 
    return delka;
}

int delka_cisla(int number) {
    int delka = 0;
    while (number >= 10) {
        number /= 10;
        delka++;
    }
    return delka;
}

void print_histogram(int* nums_array, int* counted_array, int size, int hist_size) {
    int count_defined=0;
    int max_delka = max_delka_cisla(nums_array, size);

    for (int i = 0; i < size; i++) {
        int whitespaces = 0;
        int count = counted_array[i];
        int delka_i = delka_cisla(nums_array[i]);
        count_defined=count_defined+count;
        whitespaces = (max_delka - delka_i);
        for (int j = 0; j < whitespaces; j++) {
            printf(" ");
        }
        printf("%d", nums_array[i]); hashprint(count); printf("\n");
    }
    
    if ((hist_size - count_defined) >0) {
        printf("invalid:"); hashprint(hist_size - count_defined);
        printf("\n");
    }
    
}

int main() {
    // Keep this line here
    
    char orientation;
    int count = 0, start_= 0;
    int numbers_array[9]= {0};
    int counted_array[9] = {0};
    int chyba = 0;
    chyba = nacitani_vstupu(&orientation, &count, &start_);
    if (chyba != 0) {
        return 1;
    }
    // nacitani_vstupu(&orientation, &count, &start_);
    int hist_array[1000]= {0};
    read_histogram(hist_array, count);

    int size = sizeof(numbers_array) / sizeof(numbers_array[0]);
    fill_array(numbers_array, size, start_, 1);
    
    // vypis_pole(pole,size);
    // int hist_size = sizeof(hist_array) / sizeof(hist_array[0]);
    // vypis_pole(numbers_array, size);
    // vypis_pole(hist_array, count);

    countif(numbers_array, hist_array, size, count, counted_array);
    // vypis_pole(counted_array, size);

    print_histogram(numbers_array, counted_array, size, count);
    return 0;
}