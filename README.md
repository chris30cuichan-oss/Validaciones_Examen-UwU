#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Funciones auxiliares de validación pura
int validarEntero(int valor, int min, int max);
int validarDecimal(float valor, float min, float max);
int validarTexto(const char *cadena);

// Funciones de lectura obligatorias usando punteros (Paso por referencia)
void leerEnteroValidado(const char *mensaje, int min, int max, int *resultado);
void leerDecimalValidado(const char *mensaje, float min, float max, float *resultado);
void leerTextoValidado(const char *mensaje, char *resultado, int tamano_max);

#endif
-----------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

// Limpia el exceso de caracteres en el búfer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarEntero(int valor, int min, int max) {
    return (valor >= min && valor <= max);
}

int validarDecimal(float valor, float min, float max) {
    return (valor > min && valor < max); // Rangos del examen: > 0.0 y < 300.0 / > 0.30 y < 2.50
}

// Verifica que el nombre solo tenga letras y espacios
int validarTexto(const char *cadena) {
    if (strlen(cadena) == 0) return 0;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha((unsigned char)cadena[i]) && !isspace((unsigned char)cadena[i])) {
            return 0; // Contiene un número o símbolo
        }
    }
    return 1;
}

// Implementación con punteros sin usar return
void leerEnteroValidado(const char *mensaje, int min, int max, int *resultado) {
    int valor;
    int asignado;
    while (1) {
        printf("%s", mensaje);
        asignado = scanf("%d", &valor);
        
        if (asignado != 1) {
            // Si el usuario ingresó letras o símbolos
            printf(">> Error: Entrada no válida (no se permiten letras ni símbolos)\n");
            limpiarBuffer();
        } else {
            limpiarBuffer(); // Limpia el salto de línea sobrante
            if (validarEntero(valor, min, max)) {
                *resultado = valor; // Modificación vía desreferenciación
                break;
            } else {
                printf(">> Error: dato fuera de rango, intente de nuevo\n");
            }
        }
    }
}

// Implementación con punteros sin usar return
void leerDecimalValidado(const char *mensaje, float min, float max, float *resultado) {
    float valor;
    int asignado;
    while (1) {
        printf("%s", mensaje);
        asignado = scanf("%f", &valor);
        
        if (asignado != 1) {
            printf(">> Error: Entrada no válida (no se permiten letras ni símbolos)\n");
            limpiarBuffer();
        } else {
            limpiarBuffer();
            if (validarDecimal(valor, min, max)) {
                *resultado = valor;
                break;
            } else {
                printf(">> Error: dato fuera de rango, intente de nuevo\n");
            }
        }
    }
}

// Evita caracteres infinitos usando el tamaño máximo y valida que solo sean letras
void leerTextoValidado(const char *mensaje, char *resultado, int tamano_max) {
    char buffer[200]; // Búfer temporal amplio para capturar excesos
    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Quitar el salto de línea que agrega fgets
            buffer[strcspn(buffer, "\n")] = '\0';
            
            // Validar longitud para evitar desbordamiento ("caracteres infinitos")
            if (strlen(buffer) >= (size_t)tamano_max) {
                printf(">> Error: Texto demasiado largo (máximo %d caracteres)\n", tamano_max - 1);
                continue;
            }
            
            // Validar que no tenga números ni símbolos
            if (validarTexto(buffer)) {
                strcpy(resultado, buffer);
                break;
            } else {
                printf(">> Error: El nombre no debe contener números ni símbolos\n");
            }
        }
    }
}
