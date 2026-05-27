#include "drawing.h"
void left(int pocet_kroku) {
    for (int i =0; i<pocet_kroku; i++) {
        move_left();
    }
}
void right(int pocet_kroku) {
    for (int i =0; i<pocet_kroku; i++) {
        move_right();
    }
}
void up(int pocet_kroku) {
    for (int i =0; i<pocet_kroku; i++) {
        move_up();
    }
}

void cara(int delka) {
        for (int i = 0; i< delka; i++) {
            draw_pixel();
            right(2);
        }
    }

void plna_cara_vertikalna(int delka) {
        for (int i = 0; i< delka; i++) {
            draw_pixel();move_down();
        }
    }
void plna_cara_vertikalna_up(int delka) {
        for (int i = 0; i< delka; i++) {
            draw_pixel();move_up();
        }
    }
void plna_cara(int delka) {
        for (int i = 0; i< delka; i++) {
            draw_pixel();move_right();
        }
    }

void ctverec(int delka_strany) {
    set_blue_color();
    plna_cara(delka_strany);move_left();
    move_down();
    plna_cara_vertikalna(delka_strany);
    left(delka_strany);up(delka_strany);
    plna_cara_vertikalna(delka_strany);
    plna_cara(delka_strany);
    }

void schody(int pocet) {
    plna_cara(5);
    for (int i = 0; i < pocet; i++) {
        move_left();move_down();draw_pixel();move_down();
        plna_cara(5);
    }
}

void kvetina(int sirka, int vyska) {
    move_to(vyska+3,sirka/2+1); set_green_color();
    for (int i = 0; i < (vyska-2*((sirka/4))); i++) {
        draw_pixel();
        move_up();
    }

    // for (int i = 0; i < vyska/2; i++) {
    //     set_red_color();
    //     draw_pixel(); move_up();move_left();
    //     }
    for (int k = 0; k<((sirka/4)); k++) {
            move_left();
        }
    for (int i = -(sirka/4); i <= (sirka/4); i++) {
        set_red_color();
        
        if (i < 0) {
            int delka_cary = ((2*i)+sirka);
            plna_cara(delka_cary);
            for (int j = 0; j < 2*i+sirka+1; j++) {
                move_left();
            }
            move_up();  
        }
        else if (i>=0) {
            int delka_cary = (-2)*i+sirka;
            plna_cara(-i*2+sirka);
            left(-i*2+sirka-1);
            if (i==0) {
                right(delka_cary/2-2);
                set_white_color();
                plna_cara(2);
                left(delka_cary/2);
            }
            move_up(); 
        }
            
    }

    }

void kvet(int sirka, int vyska) {
    int stonka = 0;
    int vyska_kvetu = vyska/2+1;
    int dodatok = sirka/3 + sirka%3;
    for (int y=0; y<vyska_kvetu;y++) {
        if ((y>=vyska_kvetu/3) && (y<(vyska_kvetu-(vyska_kvetu/3))) && (vyska_kvetu>2)) {
            set_red_color(); plna_cara((sirka-dodatok)/2);
            set_yellow_color(); plna_cara(dodatok);
            set_red_color(); plna_cara((sirka-dodatok)/2);
        }
        else {
            set_red_color(); plna_cara(sirka);      
        }
        move_down();left(sirka);
    }
    if (sirka %2==0) {
        stonka = 1;

    }
    else {
        stonka = 0;
    }
    right(sirka/2-stonka);
    for (int z=0; z<(vyska-(vyska/2+1)); z++) {
        set_green_color(); plna_cara(dodatok/2);left(dodatok/2);
        move_down();
    }
}

void louka(int radky, int sloupce) {
        int vyska = 7;
        int sirka = 10;
        
        for (int y=0; y < radky; y++) {
            for (int x=1; x <= sloupce; x++) {
                if (y==0) {
                    move_to(1, x * (sirka + 1));
                    kvet(sirka, vyska);
                }
                else {
                    move_to(1+y*(vyska+1), x * (sirka + 1));
                    kvet(sirka, vyska);
                }
            }
        }
    }

void animovana_louka(int radky, int sloupce) {
    int vyska = 7;
    int sirka = 7;
        
    for (int y=0; y < radky; y++) {
        for (int x=1; x <= sloupce; x++) {
            if (y==0) {
                move_to(1, x * (sirka + 1));
                kvet(sirka, vyska);
                animate_ms(200);
            }
            else {
                move_to(1+y*(vyska+1), x * (sirka + 1));
                kvet(sirka, vyska);
                animate_ms(200);
            }
        }
    }
}

void snake() {
    int sirka = 20;
    int y = 15;
    int x = 4;
    int round = 0;
    int delka_hada=5;
    int z=1;
    int ms=150;

    for (round = 0; round < 3; round++) {
        if (round<1) {
            for (int i = 0; i < 14; i++) {
                if (x + delka_hada == sirka) {     // prejeti za okraj vpravo
                    x = 1;
                    for (int j = 0; j < delka_hada; j++) {
                        clear_screen();
                        move_to(1,1);  
                        ctverec(sirka);
                        move_to(y,x+1);set_green_color(); plna_cara(j); set_red_color(); plna_cara(1);
                        move_to(y,(sirka-delka_hada+j));set_green_color(); plna_cara(delka_hada-j);
                        animate_ms(ms);
                    }
                }
                else {
                    clear_screen();
                    move_to(1,1);  
                    ctverec(sirka);
                    move_to(y,x+1);set_green_color();plna_cara(delka_hada);set_red_color();plna_cara(1);
                    animate_ms(ms);
                    x++;
                }   
            }
        }

        if (round>1) {
            
            for (int i = 0; i < 20; i++) {
                int x_coord = x+delka_hada;
                if (y - delka_hada == 1) {
                    y=20;
                    for (int j = 0; j < delka_hada; j++) {  // prejeti za okraj
                        clear_screen();
                        move_to(1,1);  
                        ctverec(sirka);
                        move_to(y+1,x_coord);set_green_color(); plna_cara_vertikalna_up(j); set_red_color(); plna_cara_vertikalna_up(1);
                        move_to(delka_hada-j+1,x_coord); set_green_color(); plna_cara_vertikalna_up(delka_hada-j);
                        animate_ms(ms);
                    }
                }
                else {
                    if (z==1) {         // zahnuti doleva
                        for (int k = 0; k< delka_hada; k++) {
                            clear_screen();
                            move_to(1,1);ctverec(sirka);
                            move_to(y,x_coord-delka_hada+k);set_green_color();plna_cara(delka_hada-k);set_red_color();plna_cara(1-k);
                            move_to(y,x_coord);set_green_color();plna_cara_vertikalna_up(k);set_red_color();plna_cara_vertikalna_up(1);
                            animate_ms(ms);
                            x_coord=x_coord++;
                        }
                        z++;
                        y--;
                    }
                    clear_screen();
                    move_to(1,1);ctverec(sirka);
                    move_to(y+1,x_coord);set_green_color();plna_cara_vertikalna_up(delka_hada);set_red_color();plna_cara_vertikalna_up(1);
                    animate_ms(ms); 
                    y--;
                } 
            }
        }
    }

    
}

int main() {
    // Keep this line here
    clear_screen();

    // Load the input - what should be drawn.
    int drawing = 0;
    scanf("%d", &drawing);
    if (drawing == 0) {
        set_green_color();
        cara(20);move_right();move_down();
        cara(15);move_right();move_down();
        cara(10);
        move_to(3,2);
        set_red_color();
        cara(20);move_right();move_down();
        cara(15);move_right();move_down();
        cara(10);
        set_blue_color();
        move_to(4,3);
        cara(20);move_right();move_down();
        cara(15);move_right();move_down();
        cara(10);   
    }
    else if (drawing == 1) {
        set_red_color();
        schody(10);
        move_to(3,10);
        set_green_color();
        schody(7);
        move_to(4,20);
        set_blue_color();
        schody(5);
    }
    else if (drawing == 2) {
        kvet(8,8);
        move_to(3,25);kvet(7,3);
        move_to(1,13);kvet(10,7);
        move_to(10,3);kvet(8,5);
        move_to(9,12);kvet(7,10);
        move_to(8,20);kvet(12,9);
    }
    else if (drawing == 3) {
        louka(2,3);
    }
    else if (drawing == 4) {
        // animovana_louka(3,7);
        snake();
    }
    // Put your drawing code here

    // Keep this line here
    end_drawing();

    return 0;
}