#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
using namespace std;
int x=0;
int flag=0;
void init(){
 glClearColor(1.0,1.0,1.0,0.0);
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,640,0,480);
}
void object1(){
 glClear(GL_COLOR_BUFFER_BIT);

 glColor3f(1,0,0);
 glBegin(GL_POLYGON);
 glVertex2i(x,220);
 glVertex2i(x+40,220);
 glVertex2i(x+40,260);
 glVertex2i(x,260);
 glEnd();

 glutSwapBuffers();

}
void timer(int){
 glutPostRedisplay();
 glutTimerFunc(1000/60,timer,0);

 if(flag == 0){
 x = x+3;
 }
 if(flag == 1){
 x = x-3;
 }
 if(x==600){
 flag = 1;
}
 if(x == 0){
 flag = 0;
 }
}
int main(int argc, char** argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(640,480);
 glutInitWindowPosition(200,200);
 glutCreateWindow("Animation");
 init();
 glutDisplayFunc(object1);
 glutTimerFunc(1000,timer,0);
 glutMainLoop();
 return 0;
}


/*

This code is a simple animation program using OpenGL and GLUT (OpenGL Utility Toolkit) library. It creates a window and displays a rectangle that moves horizontally back and forth.

Let's go through the code step by step:

The necessary header files are included:
cpp
Copy code
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
The code uses the std namespace:
cpp
Copy code
using namespace std;
Global variables are declared:
cpp
Copy code
int x = 0;
int flag = 0;
x represents the x-coordinate of the rectangle, and flag is used to control the direction of the animation.

The init function is defined to set up the initial environment settings:
cpp
Copy code
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set the clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);  // Set the orthographic projection
}
It sets the clear color to white and sets up the 2D orthographic projection for the window.

The object1 function is defined to draw the rectangle:
cpp
Copy code
void object1() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    glColor3f(1, 0, 0);  // Set the drawing color to red

    glBegin(GL_POLYGON);  // Begin drawing a polygon (rectangle)
    glVertex2i(x, 220);
    glVertex2i(x + 40, 220);
    glVertex2i(x + 40, 260);
    glVertex2i(x, 260);
    glEnd();  // End drawing the polygon

    glutSwapBuffers();  // Swap the front and back buffers to display the drawn rectangle
}
It clears the color buffer, sets the drawing color to red, and then uses glBegin(GL_POLYGON) and glEnd() to define the vertices of the rectangle. The rectangle's position is determined by the x coordinate. Finally, glutSwapBuffers() is used to swap the front and back buffers to display the drawn rectangle.

The timer function is defined to control the animation:
cpp
Copy code
void timer(int) {
    glutPostRedisplay();  // Mark the current window as needing to be redisplayed
    glutTimerFunc(1000 / 60, timer, 0);  // Set the timer function to be called after 1/60th of a second

    if (flag == 0) {
        x = x + 3;  // Move the rectangle to the right
    }
    if (flag == 1) {
        x = x - 3;  // Move the rectangle to the left
    }
    if (x == 600) {
        flag = 1;  // Reverse the direction when the rectangle reaches the right edge
    }
    if (x == 0) {
        flag = 0;  // Reverse the direction when the rectangle reaches the left edge
    }
}
The function uses glutPostRedisplay() to mark the current window as needing to be redrawn. glutTimerFunc() is called to set the timer function to be called after 1/60th of a second. Inside the timer function, the x coordinate is updated to move the rectangle either to the right or left, depending on the value of flag. When the rectangle reaches the right edge (x = 600), flag is set to 1 to reverse the direction. Similarly, when the rectangle reaches the left edge (x = 0), flag is set to 0 to reverse the direction again.

The main function:
cpp
Copy code
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Set the display mode to double-buffered and RGB color
    glutInitWindowSize(640, 480);  // Set the window size
    glutInitWindowPosition(200, 200);  // Set the window position
    glutCreateWindow("Animation");  // Create a window with the specified title
    init();  // Call the init function to set up the environment
    glutDisplayFunc(object1);  // Set the display function
    glutTimerFunc(1000, timer, 0);  // Set the timer function
    glutMainLoop();  // Enter the GLUT event-processing loop
    return 0;
}
The main function initializes GLUT, sets the display mode, window size, and position, creates a window with the specified title, calls the init function to set up the environment, sets the display function to object1, sets the timer function to timer, and enters the GLUT event-processing loop using glutMainLoop().

When the program is executed, it creates a window titled "Animation" and displays a rectangle that moves horizontally back and forth within the window. The animation is achieved by repeatedly redrawing the window with updated coordinates using the timer function.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */