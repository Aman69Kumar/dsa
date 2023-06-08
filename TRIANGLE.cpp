#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void display() {
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POLYGON);


    glColor3f(1,0,1);glVertex3f(0,-0.5,0);
    glColor3f(0,1,1);glVertex3f(0.5,0.5,0);
    glColor3f(1,0,1);glVertex3f(-0.5,0.5,0);
    /*
    glColor3f(1,0,1);glVertex3f(-0.25,0.75,0);
    glColor3f(1,0,1);glVertex3f(0.0,0.5,0);
    glColor3f(1,0,1);glVertex3f(0.25,0.75,0);
    glColor3f(1,0,1);glVertex3f(0.37,0.62,0);
    glColor3f(1,0,1);glVertex3f(0.5,0.5,0);
    */


  glEnd();

  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(600, 600);
  glutCreateWindow("A Simple Triangle");
  glutDisplayFunc(display);
  glutMainLoop();
}

/*
This program uses the OpenGL library to create a simple triangle and display it on the screen. The triangle consists of three vertices specified in 3D space, and each vertex is assigned a color. The program sets up a window using GLUT (OpenGL Utility Toolkit) and handles the rendering of the triangle in the `display()` function.

Let's go through the program step by step:

1. The program includes the necessary header file `<GL/glut.h>`. Depending on the platform, it includes either `<GLUT/glut.h>` or `<GL/glut.h>`.

2. The `display()` function is defined, which is responsible for rendering the triangle on the screen. It starts by clearing the color buffer using `glClear(GL_COLOR_BUFFER_BIT)`.

3. Inside the `display()` function, the `glBegin(GL_POLYGON)` function is called to indicate the start of a polygon (in this case, a triangle).

4. The `glColor3f()` function is used to set the color of each vertex. The first argument specifies the red component, the second argument specifies the green component, and the third argument specifies the blue component. In this program, each vertex is assigned a different color, creating a gradient effect.

5. The `glVertex3f()` function is called three times to specify the three vertices of the triangle. Each vertex is specified with three coordinates (x, y, z) in 3D space. In this program, the triangle is positioned in the xy-plane with z=0. The vertices are specified in counterclockwise order to define the front face of the triangle.

6. The `glEnd()` function is called to mark the end of the polygon.

7. The `glFlush()` function is called to ensure that all the OpenGL commands are executed and the triangle is rendered on the screen.

8. The `main()` function is the entry point of the program. It initializes GLUT using `glutInit()`, passing the command line arguments.

9. The display mode is set using `glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)`. `GLUT_SINGLE` indicates that a single buffer is used for rendering, and `GLUT_RGB` indicates that the color model is RGB.

10. The window position and size are set using `glutInitWindowPosition()` and `glutInitWindowSize()`.

11. The window is created using `glutCreateWindow()`, and the title of the window is set to "A Simple Triangle".

12. The `glutDisplayFunc()` function is called to register the `display()` function as the callback function for rendering the window contents.

13. Finally, the `glutMainLoop()` function is called to enter the event processing loop and handle user interactions.

In summary, this program sets up an OpenGL window using GLUT, defines a `display()` function to render a triangle, and enters the main event processing loop to display the triangle on the screen. The triangle is defined by three vertices with assigned colors, and the program uses the OpenGL pipeline to render the triangle on the screen.
*/