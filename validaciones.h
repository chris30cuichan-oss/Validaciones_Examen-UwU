#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <stddef.h> // Necesario para reconocer el tipo de dato size_t

// Funciones auxiliares de validación pura (Retornan 1 si es correcto, 0 si no)
int validarEntero(int valor, int min, int max);
int validarDecimal(float valor, float min, float max);
int validarTexto(const char *cadena);

// Funciones principales de lectura obligatorias usando punteros (Paso por referencia sin return)
void leerEnteroValidado(const char *mensaje, int min, int max, int *resultado);
void leerDecimalValidado(const char *mensaje, float min, float max, float *resultado);
void leerTextoValidado(const char *mensaje, char *resultado, int tamano_max);

#endif