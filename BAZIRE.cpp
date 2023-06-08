#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
using namespace std;
int x[4],y[4];
void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
    glClear(GL_COLOR_BUFFER_BIT);
}
void putpixel(double xt,double yt )
{
glColor3f(1,0,0);
glBegin(GL_POINTS);
glVertex2d(xt,yt);
glEnd();
glFlush();
}
void Algorithm(){
glColor3f(0,1,0);
glBegin(GL_LINES);
glVertex2i(x[0],y[0]);
glVertex2i(x[1],y[1]);
glVertex2i(x[1],y[1]);
glVertex2i(x[2],y[2]);
glVertex2i(x[2],y[2]);
glVertex2i(x[3],y[3]);
glEnd();
glFlush();
double t;
for (t = 0.0; t < 1.0; t += 0.0005)
{
double xt = pow(1-t, 3) * x[0] + 3 * t * pow(1-t, 2) * x[1] + 3 * pow(t, 2) * (1-t) * x[2] + pow(t, 3) * x[3];
double yt = pow(1-t, 3) * y[0] + 3 * t * pow(1-t, 2) * y[1] + 3 * pow(t, 2) * (1-t) * y[2] + pow(t, 3) * y[3];
putpixel(xt, yt);
}
}
int main(int argc, char** argv){
cout<<"\n \t Enter The Four Points x space y ";
for(int i=0;i<4;i++){
cout<<"\n \t Enter x and y for "<<i<<" = ";
cin>>x[i]>>y[i];
}
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(200,200);
glutCreateWindow("Bezier 4 point");
init();
glutDisplayFunc(Algorithm);
glutMainLoop();
return 0;
}

/*

Certainly! Let's break down the code and explain each function and its purpose:

```cpp
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
using namespace std;
```
This section includes the necessary header files for the program, including `iostream` for input/output operations, `math.h` for mathematical functions, `time.h` for time-related functions, and `GL/glut.h` for OpenGL and GLUT functions. The `using namespace std;` statement allows using standard library functions and objects without explicitly specifying the namespace.

```cpp
int x[4],y[4];
```
This declares two arrays `x` and `y`, which will store the x and y coordinates of the four control points for the Bezier curve.

```cpp
void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
    glClear(GL_COLOR_BUFFER_BIT);
}
```
The `init` function is used to set up the OpenGL environment. It sets the clear color to white using `glClearColor`, sets the current matrix mode to `GL_PROJECTION` using `glMatrixMode`, defines a 2D orthographic projection using `gluOrtho2D`, and clears the color buffer using `glClear`.

```cpp
void putpixel(double xt,double yt )
{
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    glVertex2d(xt,yt);
    glEnd();
    glFlush();
}
```
The `putpixel` function is used to draw a single pixel on the screen. It takes the x and y coordinates as parameters. It sets the color to red using `glColor3f`, starts drawing points using `glBegin(GL_POINTS)`, specifies the vertex using `glVertex2d`, ends drawing using `glEnd`, and flushes the drawing commands to the screen using `glFlush`.

```cpp
void Algorithm()
{
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2i(x[0],y[0]);
    glVertex2i(x[1],y[1]);
    glVertex2i(x[1],y[1]);
    glVertex2i(x[2],y[2]);
    glVertex2i(x[2],y[2]);
    glVertex2i(x[3],y[3]);
    glEnd();
    glFlush();

    double t;
    for (t = 0.0; t < 1.0; t += 0.0005)
    {
        double xt = pow(1-t, 3) * x[0] + 3 * t * pow(1-t, 2) * x[1] + 3 * pow(t, 2) * (1-t) * x[2] + pow(t, 3) * x[3];
        double yt = pow(1-t, 3) * y[0] + 3 * t * pow(1-t, 2) * y[1] + 3 * pow(t, 2) * (1-t) * y[2] + pow(t, 3) * y[3];
        putpixel(xt, yt);
    }
}
```
The `Algorithm` function is the heart of the program. It draws the Bezier curve on the screen. It begins by setting the color to green using `glColor3f`. It then starts drawing lines using `glBegin(GL_LINES)` and specifies the vertices for each line using `glVertex2i`. These lines connect

 the four control points of the curve.

After drawing the lines, the function enters a loop that iterates from 0.0 to 0.9995 (less than 1.0) with a step of 0.0005. In each iteration, it calculates the x and y coordinates of the curve point using the Bezier curve formula.

The Bezier curve formula calculates the position of a point on the curve based on the control points and the parameter `t`. It uses the Bernstein polynomial basis to determine the contribution of each control point to the curve point.

For example, to calculate the x coordinate of the curve point, it uses the formula:
```
xt = pow(1-t, 3) * x[0] + 3 * t * pow(1-t, 2) * x[1] + 3 * pow(t, 2) * (1-t) * x[2] + pow(t, 3) * x[3]
```

Similarly, it calculates the y coordinate of the curve point using the same formula.

Finally, it calls the `putpixel` function with the calculated x and y coordinates to draw the point on the screen.

```cpp
int main(int argc, char** argv)
{
    cout << "\n \t Enter The Four Points x space y ";
    for(int i=0;i<4;i++)
    {
        cout << "\n \t Enter x and y for " << i << " = ";
        cin >> x[i] >> y[i];
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Bezier 4 point");

    init();
    glutDisplayFunc(Algorithm);
    glutMainLoop();

    return 0;
}
```
The `main` function is the entry point of the program. It prompts the user to enter the x and y coordinates of the four control points for the Bezier curve.

Then, it initializes the GLUT library using `glutInit`, sets the display mode to use a single buffer and RGB mode using `glutInitDisplayMode`, sets the window size and position using `glutInitWindowSize` and `glutInitWindowPosition`, and creates a window with the specified title using `glutCreateWindow`.

The `init` function is called to set up the OpenGL environment.

The `glutDisplayFunc` function is used to specify the callback function that will be called to display the content of the window. In this case, it is set to `Algorithm`, which draws the Bezier curve.

Finally, the `glutMainLoop` function is called to start the event processing loop of GLUT.

That's the detailed explanation of the complete code. It takes the user-specified control points, calculates the Bezier curve points, and displays the curve using OpenGL and GLUT functions.

*/