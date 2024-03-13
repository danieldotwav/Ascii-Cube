#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <windows.h>
void usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec); 

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

float A, B, C;
float x, y, z;

float cubeWidth = 20; /* Width of the cube */
int width = 160, height = 44; /* Width and height of the screen */
float depthBuffer[160 * 44]; /* Stores the inverse of the z - coordinate(depth) for each pixel on the screen, to manage which object is closer to the viewer and should therefore be visible */
char asciiRenderBuffer[160 * 44]; /* Stores the ASCII character to be rendered on the screen */
int backgroundASCIICode = '-'; /* ASCII code for the background */
int distanceFromCam = 100; /* Distance of the camera from the origin */
float viewScale = 40; /* Scale factor used in the perspective projection calculation to adjust the size of the rendered objects */

float incrementSpeed = 0.6; /* Increment speed used to calculate the position of the cubes */
float horizontalOffset; /* Used to position the cubes on the screen */
float inverseDepth; /* Reciprocal depth used to adjust size of objects based on their distance from the viewer */
int screenX, screenY; /* Screen coordinates of the pixel to be rendered */
int bufferIndex; /* Used to index into the depthBuffer and asciiRenderBuffer */

#endif