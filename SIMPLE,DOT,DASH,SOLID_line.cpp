#include <iostream>
#include <GL/glut.h>
using namespace std;

int screenWidth = 600;
int screenHeight = 600;
int quadrantSize = screenWidth / 2;

int x1, y1, x2, y2;
int lineType = 0; // 0: simple, 1: dotted, 2: dashed, 3: solid

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-screenWidth / 2, screenWidth / 2, -screenHeight / 2, screenHeight / 2);
}

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2) {
     float dx = x2 - x1;
     float dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement=dx/steps;
    float yIncrement=dy/steps;

    float x=x1,y=y1;

    for (int i = 0; i <= steps; i++) {
        if (lineType == 1 && i % 2 == 1) { // dotted line
            x += xIncrement;
            y += yIncrement;
            continue;
        }
        else if (lineType == 2 && i % 10 >= 5) { // dashed line
            x += xIncrement;
            y += yIncrement;
            continue;
        }

        drawPixel((x + 20),(y + 20));
        x += xIncrement;
        y += yIncrement;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // Draw the quadrant lines
    glBegin(GL_LINES);
    glVertex2i(-quadrantSize, 0);
    glVertex2i(quadrantSize, 0);
    glVertex2i(0, -quadrantSize);
    glVertex2i(0, quadrantSize);
    glEnd();

    // Draw the line based on user input
    drawLine(x1, y1, x2, y2);

    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = x - quadrantSize;
        y1 = -y + quadrantSize;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x2 = x - quadrantSize;
        y2 = -y + quadrantSize;
        glutPostRedisplay();
    }
}

void menu(int option) {
    lineType = option;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DDA Line Drawing");

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    int menuId = glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 0);
    glutAddMenuEntry("Dotted Line", 1);
    glutAddMenuEntry("Dashed Line", 2);
    glutAddMenuEntry("Solid Line", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutMainLoop();
return 0;
}

/*

This program uses the OpenGL library to draw lines using the DDA (Digital Differential Analyzer) algorithm. The user can specify the endpoints of the line by clicking on the window, and they can choose different line types using a right-click menu.

Here's a breakdown of the program:

1. The necessary header files are included: `<iostream>` for input/output operations and `<GL/glut.h>` for OpenGL functionality.

2. Global variables are declared to store the screen width, screen height, quadrant size, line endpoints, and line type.

3. The `init()` function is defined to set up the initial OpenGL environment. It sets the clear color and the projection matrix using `gluOrtho2D()`.

4. The `drawPixel()` function is defined to draw a single pixel on the screen. It uses the `glBegin()` and `glEnd()` functions to enclose the pixel drawing operation.

5. The `drawLine()` function implements the DDA algorithm to draw a line between two points. It calculates the difference in x and y coordinates (`dx` and `dy`) and determines the number of steps required for drawing the line. It then calculates the increments in x and y (`xIncrement` and `yIncrement`) based on the number of steps. The function uses a loop to draw each pixel along the line. It also handles different line types by skipping certain pixels based on the value of `lineType`.

6. The `display()` function is the main rendering function. It clears the color buffer and sets the drawing color to red. It first draws the quadrant lines using `glBegin()` and `glEnd()`. Then, it calls the `drawLine()` function to draw the line specified by the user.

7. The `mouseClick()` function is the mouse callback function. It is called when the user clicks the mouse. When the left button is pressed down, it calculates the starting point of the line based on the mouse coordinates. When the left button is released, it calculates the endpoint of the line, updates the endpoint variables, and calls `glutPostRedisplay()` to trigger a redraw.

8. The `menu()` function is the menu callback function. It is called when the user selects an option from the right-click menu. It updates the `lineType` variable based on the selected option and calls `glutPostRedisplay()` to redraw the line.

9. The `main()` function initializes GLUT and creates a window with the specified size and position. It sets the display function to `display()` and the mouse callback function to `mouseClick()`. It creates a right-click menu using `glutCreateMenu()` and adds menu entries for different line types. The menu function is attached to the right mouse button using `glutAttachMenu()`. Finally, it initializes the OpenGL environment and starts the event processing loop using `glutMainLoop()`.

Overall, this program provides a basic implementation of DDA line drawing in OpenGL, allowing the user to interactively draw lines with different line types.

*/