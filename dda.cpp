#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>

int X1, X2, Y1, Y2;

void print_point(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

int round_off(int v)
{
	return floor(v + 0.5);
}

void dda(float x1, float y1, float x2, float y2)
{
	float xinc, yinc;
	float x = x1, y = y1;

	float dx = (x2 - x1);
	float dy = (y2 - y1);

	int steps = abs(dx) > abs(dy) ? dx : dy;

	xinc = dx / (float)steps;
	yinc = dy / (float)steps;

	print_point(x, y);

	for (int i = 0; i < steps; i++)
	{
		x += xinc;
		y += yinc;
		if (i % 10 < 5)
			print_point(round_off(x), round_off(y));
	}
}
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer before drawing

    // Draw axes
    dda(-640, 0, 640, 0);
    dda(0, -480, 0, 480);

    // Draw rectangle
    dda(X1, Y1, X2, Y1);
    dda(X2, Y1, X2, Y2);
    dda(X1, Y2, X2, Y2);
    dda(X1, Y1, X1, Y2);

    // Draw diagonals
    dda((X2 + X1) / 2, Y1, X2, (Y2 + Y1) / 2);
    dda(X2, (Y2 + Y1) / 2, (X2 + X1) / 2, Y2);
    dda(X1, (Y2 + Y1) / 2, (X2 + X1) / 2, Y2);
    dda((X2 + X1) / 2, Y1, X1, (Y2 + Y1) / 2);

    // Draw inner lines
    dda((X2 + 3 * X1) / 4, (Y2 + 3 * Y1) / 4, (3 * X2 + X1) / 4, (Y2 + 3 * Y1) / 4);
    dda((3 * X2 + X1) / 4, (Y2 + 3 * Y1) / 4, (3 * X2 + X1) / 4, (3 * Y2 + Y1) / 4);
    dda((X2 + 3 * X1) / 4, (3 * Y2 + Y1) / 4, (3 * X2 + X1) / 4, (3 * Y2 + Y1) / 4);
    dda((X2 + 3 * X1) / 4, (Y2 + 3 * Y1) / 4, (X2 + 3 * X1) / 4, (3 * Y2 + Y1) / 4);

    glFlush(); // Update the display
}


void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-640, 640, -480, 480);
    glutDisplayFunc(draw); // Update this line
}


int main(int argc, char **argv)
{
	printf("\nEnter The lower left Point co-ordinates:");
	printf("\nEnter the X co-ordinate:");
	scanf("%d", &X1);
	printf("\nEnter the Y co-ordinate:");
	scanf("%d", &Y1);
	printf("\nEnter The upper left Point co-ordinates:");
	printf("\nEnter the X co-ordinate:");
	scanf("%d", &X2);
	printf("\nEnter the Y co-ordinate:");
	scanf("%d", &Y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("DDA_LINE");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}

/*

Certainly! Here's a detailed explanation of the code:

1. The code includes necessary header files for graphics and math libraries.
2. Global variables `X1`, `X2`, `Y1`, `Y2` are declared to store the coordinates of two points.
3. The `print_point` function is used to plot a point on the screen using OpenGL's `glBegin` and `glEnd` functions.
4. The `round_off` function is used to round off a floating-point value to the nearest integer.
5. The `dda` function implements the Digital Differential Analyzer (DDA) algorithm for line drawing.
   - It calculates the difference in x and y coordinates between the two points.
   - Determines the number of steps required based on the larger difference (either in x or y).
   - Calculates the increment values for x and y coordinates based on the number of steps.
   - Calls the `print_point` function to plot the initial point.
   - Iterates through each step, updates the coordinates, and plots the intermediate points.
6. The `draw` function is used to draw the axes and rectangles based on the provided points.
   - It calls the `dda` function multiple times to draw lines for the axes and rectangles.
   - The rectangle is drawn by connecting the four corners using lines.
   - Additional lines are drawn to create smaller rectangles within the main rectangle.
7. The `init` function is used to initialize OpenGL settings.
   - It sets the clear color to white, clears the color buffer, and sets the projection matrix.
   - The projection matrix is set to an orthographic view with the specified coordinates range.
   - The drawing color is set to black.
   - Finally, it calls the `draw` function to draw the lines and rectangles.
8. The `main` function is the entry point of the program.
   - It prompts the user to enter the coordinates of the lower left and upper right points.
   - Initializes the GLUT library and sets the initial display mode.
   - Creates a window with a specified size and title.
   - Initializes the drawing settings using `init`.
   - Sets the display function to `draw`.
   - Starts the main event loop using `glutMainLoop`, which continuously redraws the scene until the program is closed.

*/


/* -400 -400 100 100 */

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */
