ter#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
using namespace std;
double x,y,len,angle;
int it;
void init(){ glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,640,0,480);
glClear(GL_COLOR_BUFFER_BIT);
}
void line1(int x1, int y11, int x2,int y2){
glColor3f(0,1,0);
glBegin(GL_LINES);
glVertex2i(x1,y11);
glVertex2i(x2,y2);
glEnd();
glFlush();
}
void k_curve(double x, double y, double len, double angle, int it){ if(it>0){
len /=3;
k_curve(x,y,len,angle,(it-1));
x += (len * cosl(angle * (M_PI)/180));
y += (len * sinl(angle * (M_PI)/180));
k_curve(x,y, len, angle+60,(it-1));
x += (len * cosl((angle + 60) * (M_PI)/180));
y += (len * sinl((angle + 60) * (M_PI)/180));
k_curve(x,y, len, angle-60,(it-1));
x += (len * cosl((angle - 60) * (M_PI)/180));
y += (len * sinl((angle - 60) * (M_PI)/180));
k_curve(x,y,len,angle,(it-1));
}
else
{
line1(x,y,(int)(x + len * cosl(angle * (M_PI)/180) + 0.5),(int)(y + len * sinl(angle * (M_PI)/180) + 0.5));
}
}
void Algorithm(){ k_curve(x,y,len,angle,it);
}
int main(int argc, char** argv){
cout<<"\n Enter Starting Point x space y ";
cin>>x>>y;
cout <<"\n Lenght of line and space angle of line";

cin>>len>>angle;
cout<<"\n No. of ittration ";
cin>>it;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(200,200);
glutCreateWindow("Koch");
init();
glutDisplayFunc(Algorithm);
glutMainLoop();
return 0;
}


/*

Sure! Here's a detailed explanation of the provided code:

1. The code includes necessary header files such as `<iostream>`, `<math.h>`, `<time.h>`, and `<GL/glut.h>`.

2. Global variables `x`, `y`, `len`, `angle`, and `it` are declared.

3. The `init()` function is defined to set up the OpenGL environment. It sets the clear color to white, sets the projection matrix using `gluOrtho2D`, and clears the color buffer.

4. The `line1()` function is defined to draw a line segment between two given points. It sets the drawing color to green using `glColor3f()`, begins drawing lines with `glBegin(GL_LINES)`, specifies the two vertices of the line using `glVertex2i()`, and ends the drawing with `glEnd()` and `glFlush()`.

5. The `k_curve()` function is a recursive function that draws a Koch curve based on the given parameters. It uses an iterative approach to draw the Koch curve by dividing the line segment into three parts and recursively drawing smaller Koch curves for each part. If the recursion depth (`it`) is greater than zero, the function calls itself recursively for the four line segments of the Koch curve. If the recursion depth is zero, it calls `line1()` to draw the line segment directly.

6. The `Algorithm()` function is defined to invoke the `k_curve()` function with the initial parameters (`x`, `y`, `len`, `angle`, `it`).

7. In the `main()` function, the user is prompted to enter the starting point (`x` and `y`), the length of the line segment (`len`), the angle of the line segment (`angle`), and the number of iterations (`it`).

8. GLUT is initialized using `glutInit()`.

9. The display mode is set to `GLUT_SINGLE | GLUT_RGB` using `glutInitDisplayMode()`.

10. The window size and position are set using `glutInitWindowSize()` and `glutInitWindowPosition()`.

11. A window with the title "Koch" is created using `glutCreateWindow()`.

12. The `init()` function is called to set up the OpenGL environment.

13. The `Algorithm()` function is registered as the display callback using `glutDisplayFunc()`.

14. The main event loop is started using `glutMainLoop()`.

Overall, the code uses OpenGL and GLUT functions to draw a Koch curve based on the user-provided parameters. The Koch curve is drawn recursively by dividing the line segment into smaller segments and drawing them iteratively. The resulting Koch curve is displayed in an OpenGL window.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */