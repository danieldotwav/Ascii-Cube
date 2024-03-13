#define _CRT_SECURE_NO_WARNINGS /* Disable Windows Warnings */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Constants.h"

float A, B, C;
float x, y, z;

float cubeWidth = 20; /* Width of the cube */
int width = 160, height = 44; /* Width and height of the screen */
float depthBuffer[160 * 44]; /* Stores the inverse of the z - coordinate(depth) for each pixel on the screen, to manage which object is closer to the viewer and should therefore be visible */
char asciiRenderBuffer[160 * 44]; /* Stores the ASCII character to be rendered on the screen */
int backgroundASCIICode = '-'; /* ASCII code for the background */
int distanceFromCam = 100; /* Distance of the camera from the origin */
float viewScale = 40; /* Scale factor used in the perspective projection calculation to adjust the size of the rendered objects */

float incrementSpeed = 0.6; 
float horizontalOffset; /* Used to position the cubes on the screen */
float inverseDepth; /* Reciprocal depth used to adjust size of objects based on their distance from the viewer */
int screenX, screenY; /* Screen coordinates of the pixel to be rendered */
int bufferIndex; /* Used to index into the depthBuffer and asciiRenderBuffer */

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

int main() {
    printf("\x1b[2J");
    while (1) {
        memset(asciiRenderBuffer, backgroundASCIICode, width * height);
        memset(depthBuffer, 0, width * height * 4);
        cubeWidth = 20;
        horizontalOffset = -2 * cubeWidth;
        
        // Create large cube
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
        
        // Create medium cube
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
        
        // Create small cube
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