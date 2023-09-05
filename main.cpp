#include "mbed.h"
#include <iostream>
#include <cmath>
#include <cstdio>

PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

void setRGBColor(float red, float green, float blue) {
    ledR = red;
    ledG = green;
    ledB = blue;
}

const int numRows = 4;
const int numCols = 4;

char keyMap[numRows][numCols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};

// Función para calcular las raíces de un polinomio de grado 2
void calculateRoots() {
    char inputBuffer[32];
    int bufferIndex = 0;
    unsigned int coeficientes[3];
    int numeroActual = 0;

    while (numeroActual < 3) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    char keyPressed = keyMap[i][j];

                    if (keyPressed == '*') {
                        inputBuffer[bufferIndex] = '\0';

                        sscanf(inputBuffer, "%u", &coeficientes[numeroActual]);
                        printf("Coeficiente %d ingresado: %u\n", numeroActual + 1, coeficientes[numeroActual]);

                        memset(inputBuffer, 0, sizeof(inputBuffer));
                        bufferIndex = 0;

                        numeroActual++;

                        if (numeroActual >= 3) {
                            break;
                        }
                    } else {
                        inputBuffer[bufferIndex] = keyPressed;
                        bufferIndex++;
                    }

                    ThisThread::sleep_for(500ms);
                }
            }

            if (numeroActual >= 3) {
                break;
            }

            rowPins[i] = 1;
        }
    }

    double discriminante = coeficientes[1] * coeficientes[1] - 4 * coeficientes[0] * coeficientes[2];

    if (discriminante > 0) {
        double x1 = (-coeficientes[1] + std::sqrt(discriminante)) / (2 * coeficientes[0]);
        double x2 = (-coeficientes[1] - std::sqrt(discriminante)) / (2 * coeficientes[0]);
        printf("Las raíces son: x1 = %lf y x2 = %lf\n", x1, x2);
    } else if (discriminante == 0) {
        double x = -coeficientes[1] / (2 * coeficientes[0]);
        printf("La raíz doble es: x = %lf\n", x);
    } else {
        double realPart = -coeficientes[1] / (2 * coeficientes[0]);
        double imaginaryPart = std::sqrt(-discriminante) / (2 * coeficientes[0]);
        printf("Las raíces son imaginarias: x1 = %lf + %lfi y x2 = %lf - %lfi\n", realPart, imaginaryPart, realPart, imaginaryPart);
    }
}

char inputBuffer[50];
int bufferIndex = 0;
bool recording = false;

char convertToGrade(float N) {
    char nota;
    
    if (N >= 0 && N <= 3) {
        nota = 'A';
    } else if (N > 3 && N <= 4) {
        nota = 'B';
    } else if (N > 4 && N <= 5) {
        nota = 'C';
    } else if (N > 5 && N <= 7) {
        nota = 'D';
    } else if (N > 7 && N < 9) {
        nota = 'E';
    } else if (N >= 9 && N <= 10) {
        nota = 'F';
    } else {
        nota = '?';  // Valor fuera de rango
    }
    
    return nota;
}

void processKey(char key) {
    if (key == '*' && !recording) {
        recording = true; // Iniciar la grabación del número
    } else if (key == '*' && recording) {
        if (bufferIndex > 0) {
            inputBuffer[bufferIndex] = '\0';  // Null-terminate the string
            printf("Número ingresado: %s\n", inputBuffer);
            
            // Convertir la entrada a un número
            float N = atof(inputBuffer);
            
            if (N >= 0 && N <= 10) {
                char nota = convertToGrade(N);
                printf("Nota alfanumérica: %c\n", nota);
            } else {
                printf("Valor de nota no válido: %s\n", inputBuffer);
            }
            
            bufferIndex = 0;
        }
        recording = false; // Detener la grabación después de la conversión
    } else if (recording) {
        inputBuffer[bufferIndex++] = key;
    }
}

// Función para mostrar colores
void showColors() {
    char inputBuffer[32];
    int bufferIndex = 0;
    unsigned int numerosDecimales[3];
    int numeroActual = 0;

    while (numeroActual < 3) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    char keyPressed = keyMap[i][j];

                    if (keyPressed == '*') {
                        inputBuffer[bufferIndex] = '\0';

                        sscanf(inputBuffer, "%u", &numerosDecimales[numeroActual]);
                        printf("Número %d ingresado: %u\n", numeroActual + 1, numerosDecimales[numeroActual]);

                        memset(inputBuffer, 0, sizeof(inputBuffer));
                        bufferIndex = 0;

                        numeroActual++;

                        if (numeroActual >= 3) {
                            break;
                        }
                    } else {
                        inputBuffer[bufferIndex] = keyPressed;
                        bufferIndex++;
                    }

                    ThisThread::sleep_for(500ms);
                }
            }

            if (numeroActual >= 3) {
                break;
            }

            rowPins[i] = 1;
        }
    }

    float red = 1 - (float)(numerosDecimales[0] / 255.0f);
    float green = 1 - (float)(numerosDecimales[1] / 255.0f);
    float blue = 1 - (float)(numerosDecimales[2] / 255.0f);

    setRGBColor(red, green, blue);
}

int main() {
    printf("Por favor, elija una opción y presione * para confirmar:\n");
    printf("1. Calcular raíces de un polinomio de grado 2\n");
    printf("2. Mostrar colores\n");

    printf("Elija una opción: ");

    int eleccion = -1;

    // Leer la elección del usuario desde el teclado de membrana
    while (eleccion < 0 || eleccion > 3) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    char keyPressed = keyMap[i][j];

                    if (keyPressed >= '0' && keyPressed <= '3') {
                        eleccion = keyPressed - '0';
                    } else if (keyPressed == '*') {
                        break;
                    }

                    ThisThread::sleep_for(500ms);
                }
            }

            if (eleccion >= 0 && eleccion <= 3) {
                break;
            }

            rowPins[i] = 1;
        }
    }

    if (eleccion == 1) {
        calculateRoots();
    } else if (eleccion == 2) {
        showColors();
    } else if (eleecion == 3) {
        while (true) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    processKey(keyMap[i][j]);
                    ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                }
            }

            rowPins[i] = 1;
        }
    }
    }

    printf("Programa terminado.\n");
    
    return 0;
}
