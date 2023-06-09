#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>


															//global variable diclaration
int frameNumber = 0;										//frame no



void drawWindmill() 										//Function to draw windmill
{

	int i;

	glColor3f(1.0,1.0,0.0);									//red green blue

	glBegin(GL_POLYGON);

	glVertex2f(-0.05f, 0);									//for drawing rectangular base part
	glVertex2f(-0.05f, 3);
	glVertex2f(0.05f, 3);
	glVertex2f(0.05f, 0);

    glEnd();

	glTranslatef(0,3,0);									//x,y,z

	glColor3f(1.0,0.0,0.0);									//red,green,blue (RED PLATES OF WINDMILL)

	glRotated(frameNumber * (180.0/45), 0, 0, 1);			//(angle,x,y,z)

		for (i = 0; i < 4; i++) 							//LOOP TO DRAW FOUR PLATES
		{

				glRotated(90, 0, 0, 1);  					//90,0,0,Z

				glBegin(GL_POLYGON);

				glVertex2f(0,0);							//FOR DRAWING TYIANGLULAR PLATE

				glVertex2f(1.0f, 0.2f);

				glVertex2f(1.0f,-0.2f);

	    		glEnd();
	    }
}

void display() 												 //DISPLAY FUNCTION
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();										//TAKES IDENTITY MATRIX



	glPushMatrix();											//PUSH MATRIX

	glTranslated(2.2,1.6,0);								//SET POSITION OF WINDMILL

	glScaled(0.4,0.4,1);									//SCALLING WINDMILL WITH POINT (0.4,0.4,1)

	drawWindmill();											//FUNCTION CALL TO DRAW WINDMILL

	glPopMatrix();											//POP MATRIX



	glPushMatrix();											//PUSH MATRIX

	glTranslated(3.7,0.8,0);								//SET POSITION OF WINDMILL

	glScaled(0.7,0.7,1);									//SCALLING WINDMILL WITH POINT(0.7,0.7,1)

	drawWindmill();											//FUNCTION CALL TO DRAW WINDMILL

	glPopMatrix();											//POP MATRIX



	glutSwapBuffers();										//SWAP BUFFER
}



void doFrame(int v)
{
    frameNumber++;											//INCREMENT FRAME NO

    glutPostRedisplay();									//POST REDISPLAY

    glutTimerFunc(10,doFrame,0);
}



void init()													//FUNCTION INITIALISATION
{
	glClearColor(0,0,0,0);

	glMatrixMode(GL_PROJECTION);							//MATRIX MODE  FOR PROJECTION

	glLoadIdentity();										//LOADS IDENTITY MATRIX

	glOrtho(0, 7, -1, 4, -1, 1);							//MIN X,MAX X,MIN Y,MAX Y,MIN Z,MAX Z VALUE

	glMatrixMode(GL_MODELVIEW);								//MATRIX MODE FOR MODEL VIEW
}



int main(int argc, char** argv) 							//MAIN FUNCTION
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(700,500);							//DEFINED WINDOW SIZE 700*500

    glutInitWindowPosition(100,100);  						//DEFINED WINDOW POSITION 100,100

    glutCreateWindow("WINDMILL"); 							//NAME OF WINDOW

    init();													//FIRSTLY CALL TO INTIALISE VALUE

    glutDisplayFunc(display); 								//DISPLAY

    glutTimerFunc(200,doFrame,0); 							//TIMER FUNC

    glutMainLoop();

    return 0;
}


/*

This code is a simple animation program that uses OpenGL and GLUT (OpenGL Utility Toolkit) library to draw a windmill and animate its rotation. The windmill consists of a rectangular base and four triangular plates rotating around a central point.

Let's go through the code step by step:

1. The necessary header files are included:
```cpp
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
```

2. Global variables are declared:
```cpp
int frameNumber = 0;  // frame number
```
`frameNumber` is used to track the current frame for animation.

3. The `drawWindmill` function is defined to draw the windmill:
```cpp
void drawWindmill() {
    int i;

    glColor3f(1.0, 1.0, 0.0);  // Set the color to yellow

    glBegin(GL_POLYGON);  // Begin drawing the rectangular base
    glVertex2f(-0.05f, 0);
    glVertex2f(-0.05f, 3);
    glVertex2f(0.05f, 3);
    glVertex2f(0.05f, 0);
    glEnd();

    glTranslatef(0, 3, 0);  // Translate to the top of the base

    glColor3f(1.0, 0.0, 0.0);  // Set the color to red (for the plates)

    glRotated(frameNumber * (180.0 / 45), 0, 0, 1);  // Rotate the windmill plates

    for (i = 0; i < 4; i++) {  // Loop to draw the four plates
        glRotated(90, 0, 0, 1);  // Rotate 90 degrees around the z-axis

        glBegin(GL_POLYGON);  // Begin drawing a triangular plate
        glVertex2f(0, 0);
        glVertex2f(1.0f, 0.2f);
        glVertex2f(1.0f, -0.2f);
        glEnd();
    }
}
```
The function sets the colors for the base and plates, and then uses `glBegin(GL_POLYGON)` and `glEnd()` to define the vertices of the base and plates. The windmill plates are rotated based on the `frameNumber` to create the animation effect.

4. The `display` function is defined to handle the display:
```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    glLoadIdentity();  // Load the identity matrix

    glPushMatrix();  // Push the current matrix

    glTranslated(2.2, 1.6, 0);  // Set the position of the first windmill
    glScaled(0.4, 0.4, 1);  // Scale the windmill
    drawWindmill();  // Draw the windmill

    glPopMatrix();  // Pop the matrix

    glPushMatrix();  // Push the current matrix

    glTranslated(3.7, 0.8, 0);  // Set the position of the second windmill
    glScaled(0.7, 0.7, 1);  // Scale the windmill
    drawWindmill();  // Draw the windmill

    glPopMatrix();  // Pop the matrix

    glutSwapBuffers();  // Swap the buffers
}
```
The function clears the color buffer, loads the identity matrix, and then uses `glPushMatrix()` and `glPopMatrix()` to push and pop the matrix stack.

 Inside the matrix stack, it sets the position and scale of each windmill, and calls the `drawWindmill` function to draw the windmill.

5. The `doFrame` function is defined to update the frame number and trigger the redisplay:
```cpp
void doFrame(int v) {
    frameNumber++;  // Increment the frame number

    glutPostRedisplay();  // Post a redisplay event

    glutTimerFunc(10, doFrame, 0);  // Set the timer for the next frame
}
```
The function increments the `frameNumber`, posts a redisplay event to update the display, and sets a timer for the next frame.

6. The `init` function is defined to initialize the OpenGL environment:
```cpp
void init() {
    glClearColor(0, 0, 0, 0);  // Set the clear color to black

    glMatrixMode(GL_PROJECTION);  // Set the matrix mode to projection
    glLoadIdentity();  // Load the identity matrix

    glOrtho(0, 7, -1, 4, -1, 1);  // Set the orthographic view volume

    glMatrixMode(GL_MODELVIEW);  // Set the matrix mode to model view
}
```
The function sets the clear color to black, sets the matrix mode to projection, loads the identity matrix, sets the orthographic view volume, and sets the matrix mode to model view.

7. The `main` function:
```cpp
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Initialize GLUT

    glutInitDisplayMode(GLUT_DOUBLE);  // Set the display mode to double-buffered

    glutInitWindowSize(700, 500);  // Set the window size

    glutInitWindowPosition(100, 100);  // Set the window position

    glutCreateWindow("WINDMILL");  // Create a window with the specified title

    init();  // Call the init function to set up the environment

    glutDisplayFunc(display);  // Set the display function

    glutTimerFunc(200, doFrame, 0);  // Set the timer function

    glutMainLoop();  // Enter the GLUT event-processing loop

    return 0;
}
```
The `main` function initializes GLUT, sets the display mode to double-buffered, sets the window size and position, creates a window with the title "WINDMILL", calls the `init` function to set up the environment, sets the display function to `display`, sets the timer function to `doFrame`, and enters the GLUT event-processing loop using `glutMainLoop()`.

When the program is executed, it creates a window titled "WINDMILL" and displays two windmills that rotate continuously. The animation is achieved by repeatedly updating the frame number and redisplaying the window.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */