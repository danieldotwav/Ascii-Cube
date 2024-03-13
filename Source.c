#define _CRT_SECURE_NO_WARNINGS /* Disable Windows Warnings */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Constants.h"

float calculateX(int i, int j, int k);
float calculateY(int i, int j, int k);
float calculateZ(int i, int j, int k);
void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch);

int main(void) {
    printf("\x1b[2J");
    while (1) {
        memset(asciiRenderBuffer, backgroundASCIICode, width * height);
        memset(depthBuffer, 0, width * height * 4);
        cubeWidth = 20;
        horizontalOffset = -2 * cubeWidth;
        
        /* Create large cube */ 
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }
        cubeWidth = 10;
        horizontalOffset = 1 * cubeWidth;
        
        /* Create medium cube */
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }
        cubeWidth = 5;
        horizontalOffset = 8 * cubeWidth;
        
        /* Create small cube */
        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth;
                cubeY += incrementSpeed) {
                calculateForSurface(cubeX, cubeY, -cubeWidth, '@');
                calculateForSurface(cubeWidth, cubeY, cubeX, '$');
                calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
                calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
                calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
                calculateForSurface(cubeX, cubeWidth, cubeY, '+');
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? asciiRenderBuffer[k] : 10);
        }

        A += 0.05;
        B += 0.05;
        C += 0.01;
        usleep(4000 * 2);
    }
    return 0;
}

float calculateX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
        j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
        j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
        i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) {
    x = calculateX(cubeX, cubeY, cubeZ);
    y = calculateY(cubeX, cubeY, cubeZ);
    z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

    inverseDepth = 1 / z;

    screenX = (int)(width / 2 + horizontalOffset + viewScale * inverseDepth * x * 2);
    screenY = (int)(height / 2 + viewScale * inverseDepth * y);

    bufferIndex = screenX + screenY * width;
    if (bufferIndex >= 0 && bufferIndex < width * height) {
        if (inverseDepth > depthBuffer[bufferIndex]) {
            depthBuffer[bufferIndex] = inverseDepth;
            asciiRenderBuffer[bufferIndex] = ch;
        }
    }
}