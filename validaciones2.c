#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

// Limpia el exceso de caracteres acumulados en el búfer del teclado (stdin)
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Implementación: Verifica rangos enteros
int validarEntero(int valor, int min, int max) {
    return (valor >= min && valor <= max);
}

// Implementación: Verifica rangos decimales (Límites abiertos según examen UDLA)
int validarDecimal(float valor, float min, float max) {
    return (valor > min && valor < max);
}

// Implementación: Filtra para que solo existan letras y espacios
int validarTexto(const char *cadena) {
    if (strlen(cadena) == 0) return 0;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isalpha((unsigned char)cadena[i]) && !isspace((unsigned char)cadena[i])) {
            return 0; // Se detectó un número, símbolo o carácter extraño
        }
    }
    return 1;
}

// Lee enteros de forma segura impidiendo bucles infinitos por letras
void leerEnteroValidado(const char *mensaje, int min, int max, int *resultado) {
    int valor;
    int asignado;
    while (1) {
        printf("%s", mensaje);
        asignado = scanf("%d", &valor);
        
        if (asignado != 1) {
            printf(">> Error: Entrada no válida (no se permiten letras ni símbolos)\n");
            limpiarBuffer();
        } else {
            limpiarBuffer(); 
            if (validarEntero(valor, min, max)) {
                *resultado = valor; // Modifica directo la variable del otro archivo
                break;
            } else {
                printf(">> Error: dato fuera de rango, intente de nuevo\n");
            }
        }
    }
}

// Lee decimales (float) de forma segura protegiendo el flujo de entrada
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
                *resultado = valor; // Modifica directo la variable del otro archivo
                break;
            } else {
                printf(">> Error: dato fuera de rango, intente de nuevo\n");
            }
        }
    }
}

// Lee cadenas de texto controlando límites de desbordamiento (caracteres infinitos)
void leerTextoValidado(const char *mensaje, char *resultado, int tamano_max) {
    char buffer[200]; // Búfer temporal amplio para absorber excesos del teclado
    while (1) {
        printf("%s", mensaje);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Remueve el salto de línea '\n' que mete fgets de forma automática
            buffer[strcspn(buffer, "\n")] = '\0';
            
            // Valida que la longitud ingresada no rompa el tamaño de la variable destino
            if (strlen(buffer) >= (size_t)tamano_max) {
                printf(">> Error: Texto demasiado largo (máximo %d caracteres)\n", tamano_max - 1);
                continue;
            }
            
            // Valida que el texto sea puramente alfabético
            if (validarTexto(buffer)) {
                strcpy(resultado, buffer);
                break;
            } else {
                printf(">> Error: El nombre no debe contener números ni símbolos\n");
            }
        }
    }
}