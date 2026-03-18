#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_STACK 100

typedef struct {
    double items[MAX_STACK];
    int top;
} Stack;

void push(Stack *s, double val) {
    if (s->top < MAX_STACK - 1) {
        s->items[++s->top] = val;
    }
}

double pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[s->top--];
    }
    else {
        return (NAN);
    }
}

double evaluate(const char *expr) {
    Stack s = {.top = -1};
    char *token = strtok((char *)expr, " ");
    
    while (token) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&s, atof(token));
        } else {
            double b = pop(&s);
            double a = pop(&s);
            if (isnan(a) || isnan(b)) {
                printf("!!! Potrebne zadat druhy operand !!!\n");
                return NAN;
            }
            
            switch (token[0]) {
                case '+': push(&s, a + b); break;
                case '-': push(&s, a - b); break;
                case '*': push(&s, a * b); break;
                case '/': push(&s, a / b); break;
            }
        }
        token = strtok(NULL, " ");
    }
    if (s.top == 0) {
        return s.items[s.top];
    }
    else {
        printf("!!! Prilis mnoho operandu !!!\n");
        return NAN;
    }
    
}

int main() {
    char expr[256];
    int run = 1;
    while (run == 1) {
        printf("Enter RPN expression: ");
        fgets(expr, sizeof(expr), stdin);
        if (strcmp(expr, "quit\n") == 0) {
            run = 0;
        }
        else {
            printf("Result: %.2f\n", evaluate(expr));
        }
    }
    return 0;
}