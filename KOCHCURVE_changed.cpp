#include <iostream>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
using namespace std;

#define RADIAN (3.14 / 180)
#define XMAX 1400
#define YMAX 900

int n; // Declare 'n' as a global variable

void Initialize();
void draw();
void draw_koch(float, float, float, float, int);
void display();

void Initialize()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    gluOrtho2D(0.0, XMAX, 0.0, YMAX);
}

void draw(int n)
{
    glBegin(GL_LINES);
    draw_koch(600, 100, 800, 400, n);
    draw_koch(800, 400, 400, 400, n);
    draw_koch(400, 400, 600, 100, n);
    glEnd();
    glFlush();
}

void draw_koch(float xa, float ya, float xb, float yb, int n)
{
    float xc, xd, yc, yd, midx, midy;

    xc = (2 * xa + xb) / 3;
    yc = (2 * ya + yb) / 3;
    xd = (2 * xb + xa) / 3;
    yd = (2 * yb + ya) / 3;

    midx = xc + ((xd - xc) * cos(60 * RADIAN)) + ((yd - yc) * sin(60 * RADIAN));
    midy = yc - ((xd - xc) * sin(60 * RADIAN)) + ((yd - yc) * cos(60 * RADIAN));

    if (n > 0)
    {
        draw_koch(xa, ya, xc, yc, n - 1);
        draw_koch(xc, yc, midx, midy, n - 1);
        draw_koch(midx, midy, xd, yd, n - 1);
        draw_koch(xd, yd, xb, yb, n - 1);
    }
    else
    {
        glVertex2f(xa, ya);
        glVertex2f(xc, yc);

        glVertex2f(xc, yc);
        glVertex2f(midx, midy);

        glVertex2f(midx, midy);
        glVertex2f(xd, yd);

        glVertex2f(xd, yd);
        glVertex2f(xb, yb);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw(n);
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "\nEnter For How Many Iterations You Want to Draw?: ";
    cin >> n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(XMAX, YMAX);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("KOCH CURVE");

    Initialize();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}


/*

Certainly! Here's a detailed explanation of the provided code:

1. The code includes necessary header files such as `<iostream>`, `<GL/glut.h>`, `<GL/freeglut.h>`, and `<math.h>`.

2. `RADIAN` is defined as a constant value to convert degrees to radians.

3. `XMAX` and `YMAX` are defined as the maximum values for the X and Y coordinates of the window.

4. The code declares a global variable `n` to store the number of iterations.

5. Function prototypes are declared for `Initialize()`, `draw()`, `draw_koch()`, and `display()`.

6. The `Initialize()` function is defined to set up the OpenGL environment. It clears the color buffer, sets the clear color to black, sets the drawing color to white, and defines the orthographic projection using `gluOrtho2D`.

7. The `draw()` function is called by `display()` to draw the Koch curve. It uses `glBegin(GL_LINES)` to begin drawing line segments and then calls `draw_koch()` three times to draw the three segments of the Koch curve. Finally, `glEnd()` and `glFlush()` are called to end the drawing and flush the drawing commands.

8. The `draw_koch()` function is a recursive function that draws a segment of the Koch curve between two given points. It calculates the coordinates of the four intermediate points using the Koch curve algorithm. If `n` (number of iterations) is greater than zero, the function calls itself recursively to draw the four smaller segments of the Koch curve. If `n` is zero, it uses `glVertex2f()` to draw the four line segments directly.

9. The `display()` function is the main drawing function. It clears the color buffer, calls `draw()` to draw the Koch curve, and then flushes the drawing commands.

10. In the `main()` function, the user is prompted to enter the number of iterations for drawing the Koch curve, and the value is stored in the variable `n`.

11. GLUT is initialized using `glutInit()`, and the display mode is set to `GLUT_SINGLE | GLUT_RGB`.

12. The window size and position are set using `glutInitWindowSize()` and `glutInitWindowPosition()`.

13. A window with the title "KOCH CURVE" is created using `glutCreateWindow()`.

14. `Initialize()` is called to set up the OpenGL environment.

15. The `display()` function is registered as the display callback using `glutDisplayFunc()`.

16. The main event loop is started using `glutMainLoop()`.

Overall, the code uses OpenGL and GLUT functions to draw a Koch curve based on the number of iterations specified by the user. The Koch curve is drawn recursively using line segments, and the resulting curve is displayed in an OpenGL window.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */
