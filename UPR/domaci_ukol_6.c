#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int nacteni_poctu_riadkov(int* pocet_radku){
    char buf[51];
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("Nacteni dat nevyslo. Ukoncuji program\n");
        return 1;
    }
    else {
        *pocet_radku = atoi(buf);
    }
    return 0;
}

int checkForUppercase(char* slovo) {
    int asci_num = 0, i = 0;
    int bool = 0;
    while (slovo[i] != '\0') {
        asci_num = (int) slovo[i];
        if (asci_num >= 65 && asci_num <= 90){
            bool = 1;
        }
        i++;
    }
    return bool;
}

int uppercaseCount(char* slovo) {
    int i = 0;
    int uppercase_letters = 0;
    while (slovo[i] != '\0') {
        if ((int) slovo[i] >=65 && (int) slovo[i] <=90) {
            uppercase_letters++;
        }
        i++;
    }
    return uppercase_letters;
}

int lowercaseCount(char* slovo) {
    int i = 0;
    int lowercase_letters = 0;
    while (slovo[i] != '\0') {
        if ((int) slovo[i] >=97 && (int) slovo[i] <=122) {
            lowercase_letters++;
        }
        i++;
    }
    return lowercase_letters;
}

void normalizace1(char* slovo) {         // xBc -> Xbc, ABC -> Abc
    int bool = checkForUppercase(slovo);
    if ( bool == 1 ) {              // bool = 1 ak je v slove aspon jeden uppercase znak. V tomto prípade sa nastaví prvy znak slova na uppercase, zbytok lowercase
        if (slovo[0] > 90) {
            slovo[0] = (int) slovo[0] - 32;
        }
        int i=1;
        while (slovo[i] != '\0' ) {
            if ( (int) slovo[i] <= 90 && (int) slovo[i] >= 65 ){
                slovo[i] = (int) slovo[i] + 32;
            }
            i++;
        }
    }
    else if ( bool==0 ) {           // Pripad ked slovo neobsahuje UPPERCASE --> vssetky znaky do UPPERCASE
        int i=0;
        while (slovo[i] != '\0' ) {
            if (slovo[i] >= 'a' && slovo[i] <= 'z') {
                slovo[i] = (int) slovo[i] - 32;
            }
            i++;
        }
    }
}

void normalizace2(const char* slovo, char* new_slovo){
    int i = 0, j = 1;
    new_slovo[0]=slovo[0];
    while (slovo[i] != '\0' ) {
        if (slovo[i+1] != slovo[i]) {
            new_slovo[j] = slovo[i+1] ;
            i++,j++;
        }
        else {
            i++;
        } 
    }

}

void slovo(char* radek) {
    int i = 0, j = 0 , spaces = 0, pocet_slov=0, delka_slova = 0;
    int velke_po = 0, male_po = 0;
    int velke_pred = 0, male_pred = 0; int konec =0;
    male_pred = lowercaseCount(radek);
    velke_pred = uppercaseCount(radek);

    while (radek[i] != '\0' ) {        
        while (radek[i] == ' ') {           // zbavit sa medzier na zaciatku radku
            i++;
            spaces++;
        }
        
        j = 0 ; delka_slova = 0; char slovo[51]={'\0'};
        while (radek[i] != '\0' && radek[i] != ' ') {
            if (radek[i] == '\n') {
                i++;
                }
            else {
                // int ch = (int) radek[i];
                // printf("char: %d\n", ch);
                slovo[j] = radek[i];
                j++,i++;
                delka_slova++;
            } 
        }
        if (delka_slova > 0) {
            slovo[j]= '\0';
            pocet_slov++;

            char modified[51] ={'\0'};
            normalizace1(slovo); 
            normalizace2(slovo,modified);
            
            printf("%s ", modified);
           
            velke_po = velke_po + uppercaseCount(modified);
            male_po = male_po + lowercaseCount(modified);
        }
    }
    int spaces_po = 0;
    if (pocet_slov > 0) {
        spaces_po = pocet_slov -1;
    }

    printf("\n");
    printf("lowercase: %d -> %d\n", male_pred, male_po);
    printf("uppercase: %d -> %d\n", velke_pred, velke_po);
    printf("spaces: %d -> %d\n", spaces, spaces_po);
    printf("\n");
}

int nacteni_textu(int radky){
    char buf[51]={'\0'};
    int size = sizeof(buf) / sizeof(buf[0]);
    for (int i = 0; i < radky; i++) {
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("Nacteni dat nevyslo. Ukoncuji program\n");
            return 1;
        }
        else {
            slovo(buf);
        }
    }
    return 0;
}

int main() {
    int radky = 0;
    nacteni_poctu_riadkov(&radky);
    nacteni_textu(radky);
    return 0;
}