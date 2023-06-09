#include <GL/glut.h>

 GLfloat xRotated, yRotated, zRotated;
void init(void)
{
glClearColor(0,0,0,0);
 
}

void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube
glFlush();
}


void animation(void)
{
 
     yRotated += 0.01;
     xRotated += 0.02;
    DrawCube();
}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
     
    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

int main(int argc, char** argv){

glutInit(&argc, argv);
//we initizlilze the glut. functions
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(DrawCube);
glutReshapeFunc(reshape);
//Set the function for the animation.
glutIdleFunc(animation);
glutMainLoop();
return 0;
}
									

/*

This code is a basic example of using OpenGL to create a rotating 3D cube. Let's go through it step by step:

1. The code starts by including the necessary header file `GL/glut.h`, which provides the functions and constants required for OpenGL programming.

2. Next, the code defines three global variables `xRotated`, `yRotated`, and `zRotated` of type `GLfloat`, which will be used to control the rotation of the cube.

3. The `init` function is defined to initialize the OpenGL environment. It sets the clear color to black using `glClearColor`.

4. The `DrawCube` function is where the cube is drawn and rendered. It begins by setting the matrix mode to `GL_MODELVIEW` and clearing the drawing buffer using `glClear`.

5. The function then sets up the transformation matrix using `glLoadIdentity` to load the identity matrix, followed by translations and rotations based on the values of `xRotated`, `yRotated`, and `zRotated`. These transformations allow the cube to rotate around the X, Y, and Z axes.

6. The cube is drawn using `glBegin(GL_QUADS)` and `glEnd()` functions to define the vertices of each face and their corresponding colors using `glColor3f`.

7. The `animation` function is called in each frame to update the rotation angles `xRotated` and `yRotated` and then call `DrawCube` to redraw the cube with the updated rotation.

8. The `reshape` function is responsible for handling the window resizing. It adjusts the projection matrix using `gluPerspective` to maintain the correct aspect ratio and sets the viewport to the full size of the window.

9. Finally, in the `main` function, the GLUT library is initialized using `glutInit` and the display mode is set to single-buffered and RGB color using `glutInitDisplayMode`. A window is created with the specified position and name using `glutCreateWindow`.

10. The `init` function is called to initialize the OpenGL environment, and the `DrawCube` function is set as the display callback using `glutDisplayFunc`.

11. The `reshape` function is set as the reshape callback using `glutReshapeFunc`, and the `animation` function is set as the idle callback using `glutIdleFunc`.

12. Finally, the main event loop is started with `glutMainLoop`, which handles the rendering and user input events.

In summary, this code sets up a basic OpenGL window and uses transformations to rotate a cube around the X and Y axes. The cube is continuously redrawn in each frame to create a rotating animation effect.

*/

/*
// This is extra explanation if you need read

In the given code, the `glVertex3f` function is used to specify the vertices of the cube's faces. It is part of the fixed-function pipeline of OpenGL and is used to define points in 3D space.

The `glVertex3f` function takes three arguments: `x`, `y`, and `z`, representing the coordinates of the vertex. These arguments are of type `GLfloat`, which is a single-precision floating-point number.

For example, let's take a look at one of the `glVertex3f` calls in the code:
```cpp
glVertex3f(1.0f, 1.0f, -1.0f);    // Top Right Of The Quad (Top)
```
This call specifies a vertex with coordinates `(1.0f, 1.0f, -1.0f)` in 3D space. It represents the top right corner of the top face of the cube.

The `glBegin(GL_QUADS)` and `glEnd()` functions are used to delimit a block of code that defines a set of vertices forming a specific primitive, in this case, a quad (a four-sided polygon).

Between `glBegin(GL_QUADS)` and `glEnd()`, multiple `glVertex3f` calls are made to specify the vertices of the quad's corners. Each consecutive set of four vertices forms one face of the cube.

It's important to note that the order in which the vertices are specified determines the direction of the surface normal and, consequently, the front and back faces of the quad. In this code, counter-clockwise winding is used for the quads, which is the default winding order for front-facing polygons in OpenGL.

By specifying the vertices of the cube's faces using `glVertex3f`, the code defines the geometry of the cube, which is then transformed and rendered based on the applied transformations and the viewing parameters set up in the code.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */
