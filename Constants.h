#ifndef CONSTANTS_H
#define CONSTANTS_H

/* A custom implementation of a delay function tailored for Windows environments, where the Unix usleep function is not available */
#include <windows.h>
void usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER filetime;

    filetime.QuadPart = -(10 * usec); /* Convert to 100 nanosecond interval, negative value indicates relative time */

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &filetime, 0, NULL, NULL, 0); /* Set the timer to expire after the specified number of 100-nanosecond intervals */
    WaitForSingleObject(timer, INFINITE); /* Calling thread to wait for timer object to signal */
    CloseHandle(timer); /* Clean up */
}

/* Calculation Constants */

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


/* ASCII Characters for the cube faces */

#define FACE1 '/'
#define FACE2 '$'
#define FACE3 '~'
#define FACE4 '#'
#define FACE5 ';'
#define FACE6 '+'

#endif