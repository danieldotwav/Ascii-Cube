# ASCII Cube

This program is a simple yet fascinating exploration into the realm of computer graphics using ASCII art. It renders 3D objects (cubes, in this case) in real-time, projecting them onto a 2D screen using ASCII characters. This renderer showcases the fundamental concepts of 3D graphics such as perspective projection, depth buffering, and basic animation.

## Features

- **Real-time 3D to 2D projection**: Converts 3D coordinates of cubes into 2D screen coordinates.
- **Depth buffering**: Implements a depth buffer to correctly render the visibility of objects based on their distance from the viewer.
- **Dynamic viewing**: The cubes rotate, providing a dynamic view of the objects from different angles.
- **Scalable rendering**: Adjusts the scale of projection to fit the screen size.

## Usage

After compilation, run the program. It will automatically start rendering the rotating cubes. The rendering window is set to a width of 160 characters and a height of 44 lines by default. You can adjust the `width` and `height` variables in the code to match your console or terminal window size for optimal viewing.

## Code Overview

- **Main Variables**:
  - `A`, `B`, `C`: Rotation angles around the x, y, and z axes.
  - `x`, `y`, `z`: 3D coordinates after rotation.
  - `cubeWidth`: The size of the cubes.
  - `width`, `height`: The dimensions of the rendering window.
  - `depthBuffer`: An array used for depth testing, ensuring proper object overlap.
  - `asciiRenderBuffer`: An array to hold the ASCII characters for rendering.
  - `backgroundASCIICode`: The ASCII code for rendering the background.
  - `distanceFromCam`: How far away the camera is from the origin.
  - `viewScale`: A scaling factor for adjusting the projection size.
  - `incrementSpeed`: How fast the cubes rotate.
  - `horizontalOffset`: Horizontal displacement of the cubes on the screen.
  - `inverseDepth`: Used for scaling objects based on their distance.
  - `screenX`, `screenY`: The screen coordinates for rendering.
  - `bufferIndex`: Index for writing to the buffer arrays.

- **Functions**:
  - `calculateX`, `calculateY`, `calculateZ`: Compute the rotated coordinates.
  - `calculateForSurface`: Calculates screen position and updates buffers for rendering surfaces of the cubes.

## Customization

You can customize various parameters such as `cubeWidth`, `backgroundASCIICode`, and `viewScale` to modify the appearance of the rendered scene. You can also experiment with different objects by changing the `calculateForSurface` function.