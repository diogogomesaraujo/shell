#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shell.h"

void calc(char *value1, char *op, char *value2) {
    float v1 = atof(value1);
    float v2 = atof(value2);
    float result = 0.0; // Initialize result to avoid uninitialized use

    switch (*op) {
        case '+':
            result = v1 + v2;
            break;
        case '-':
            result = v1 - v2;
            break;
        case '*':
            result = v1 * v2;
            break;
        case '/':
            if (v2 == 0) {
                printf("Erro: Divisão por zero\n");
                return;
            }
            result = v1 / v2;
            break;
        case '^':
            result = powf(v1, v2);
            break;
        default:
            printf("Operador inválido, use: +,-,*,/,^\n");
            // No need to set result here since we're printing an error message
            return;
    }

    printf("Resultado calc %.5f\n", result);
}

void bitcalc(char *value1, char *op, char *value2) {
    int v1 = atoi(value1);
    int v2 = atoi(value2);
    int result = 0;

    if (strcmp(op, "AND") == 0) {
        result = v1 & v2;
    } else if (strcmp(op, "OR") == 0) {
        result = v1 | v2;
    } else if (strcmp(op, "XOR") == 0) {
        result = v1 ^ v2;
    } else if (strcmp(op, "LSHIFT") == 0) {
        result = v1 << v2;
    } else if (strcmp(op, "RSHIFT") == 0) {
        result = v1 >> v2;
    } else {
        printf("Operador inválido, use: AND, OR, XOR, LSHIFT, RSHIFT\n");
        return;
    }

    printf("Resultado bitcalc %d\n", result);
}

