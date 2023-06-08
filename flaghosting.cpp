/*Problem Statement : Write a Program in OpenGL on Linux platform to animate a scene.*/


#include<GL/glut.h>
#include<math.h>
#include<iostream>
using namespace std;

#define pi 3.14

int framenumber=0;

void drawdisk(double rad)					//draws disk
{
	int i;
	glBegin(GL_POLYGON);
	for(i=0;i<32;++i)
	{
		GLdouble angle= 2*pi*i/32;
		glVertex2d(rad*cos(angle),rad*sin(angle));
	}
	glEnd();		
}
void drawbase()								//draws the base in black
{
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex2d(1,-1);						//vertices of the base
	glVertex2d(1,0);
	glVertex2d(6,0);
	glVertex2d(6,-1);
	glEnd();
	glFlush();	
}

void drawflag()								//draws the flag with orange, white and green bands
{
	glColor3f(0.0,1.0,0.0);					//green band
	glBegin(GL_POLYGON);
	glVertex2d(0,0);						//vertices of the green band
	glVertex2d(1.5,0);
	glVertex2d(1.5,0.5);
	glVertex2d(0,0.5);
	glEnd();
	
	glColor3f(1.0,1.0,1.0);					//white band
	glBegin(GL_POLYGON);
	glVertex2d(0,0.5);						//vertices of the white band
	glVertex2d(1.5,0.5);
	glVertex2d(1.5,1.0);
	glVertex2d(0,1.0);
	glEnd();
	
	glColor3f(1.0,0.5,0.5);					//orange band
	glBegin(GL_POLYGON);
	glVertex2d(0,1);						//vertices of orange band
	glVertex2d(1.5,1);
	glVertex2d(1.5,1.5);
	glVertex2d(0,1.5);
	glEnd();
	glFlush();
}
void drawchakra()							//draws the ashoka chakra
{
	int i;
	glColor3f(0.0,0.0,1.0);
	drawdisk(0.5);
	glColor3f(1.0,1.0,1.0);
	drawdisk(0.4);
	glColor3f(0.0,0.0,1.0);
	for(i=0;i<24;++i)						//draws spokes of radius 0.5
	{
		glRotatef(360/24,0,0,1);
		glBegin(GL_LINES);
		glVertex2d(0,0);					
		glVertex2d(0.5,0);
		glEnd();
		
	}
}

void drawsun()								//draws sun of radius 1
{
	int i;
	glColor3f(1.0,1.0,0.0);
	drawdisk(1);
	for(i=0;i<15;++i)
	{
		glRotatef(360/15,0,0,1);
		glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(1.5,0);
		glEnd();
		
	}	
}
void draw()								//main draw function
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	drawbase();
	
	glColor3f(0.0,0.0,0.0);				//draws the pole for the flag
	glLineWidth(50);
	glBegin(GL_LINES);
	glVertex2d(3,0);
	glVertex2d(3,3.5);
	glEnd();
	glLineWidth(1);
	
	glPushMatrix();								//translates the flag
	glTranslated(3.02f,2.1f*(framenumber%300)/300,0);
	drawflag();
	glPopMatrix();

	glPushMatrix();								//translates the chakra
	glTranslated(3.77f,0.75+2.1f*(framenumber%300)/300,0);
	glScaled(0.5,0.5,0);
	drawchakra();
	glPopMatrix();
	
	glPushMatrix();								//translates and rotates the sun 
	glTranslated(6,3,0);
	glRotated(framenumber*0.7f,0,0,1);
	glScaled(0.5,0.5,1);
	drawsun();
	glPopMatrix();
	
	glutSwapBuffers();
}

void doframe(int v)
{
	framenumber++;
	glutPostRedisplay();
	glutTimerFunc(10,doframe,0);	
}
void Init()
{
	glClearColor(0.5f,0.5f,0.8f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,7,-1,4,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)				//main function
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("FLAG HOISTING");
    Init();
    glutDisplayFunc(draw);
    glutTimerFunc(100,doframe,0);
    glutMainLoop();    
    return 0;
}											//end of program

/*

Sure! Here's a detailed explanation of the provided code:

1. The code begins by including the necessary header files, including `<GL/glut.h>`, `<math.h>`, and `<iostream>`.

2. The `drawdisk` function is defined to draw a disk with the specified radius using GL_POLYGON. It uses the provided radius to determine the coordinates of the vertices of the disk.

3. The `drawbase` function is defined to draw the base in black color. It uses GL_POLYGON to draw a rectangle representing the base.

4. The `drawflag` function is defined to draw the flag with orange, white, and green bands. It uses GL_POLYGON to draw three rectangles representing the bands of the flag.

5. The `drawchakra` function is defined to draw the Ashoka Chakra. It first draws a blue disk using the `drawdisk` function, then it uses GL_LINES to draw spokes within the chakra.

6. The `drawsun` function is defined to draw a sun with rays. It uses the `drawdisk` function to draw a yellow disk, and then uses GL_LINES to draw rays around the sun.

7. The `draw` function is the main drawing function. It is called by `glutDisplayFunc` to redraw the scene. In this function:
   - The scene is cleared using `glClear`.
   - The `drawbase` function is called to draw the base.
   - A pole for the flag is drawn using GL_LINES.
   - The flag is translated vertically based on the current frame number, and then `drawflag` is called to draw the flag.
   - The chakra is translated vertically and horizontally based on the current frame number, and then `drawchakra` is called to draw the chakra.
   - The sun is translated and rotated based on the current frame number, and then `drawsun` is called to draw the sun.
   - The scene is swapped using `glutSwapBuffers`.

8. The `doframe` function is a timer function that increments the frame number and calls `glutPostRedisplay` to request a redraw of the scene. It is called by `glutTimerFunc` every 10 milliseconds.

9. The `Init` function is used to initialize the OpenGL settings. It sets the clear color, sets the projection matrix mode, defines the orthographic projection, and sets the model-view matrix mode.

10. The `main` function is the entry point of the program. It initializes GLUT using `glutInit`, sets the display mode to use double buffering, specifies the window size and position, creates a window with the specified title, and sets the initial display function to `draw`. It also sets up a timer using `glutTimerFunc` to continuously call `doframe` every 100 milliseconds. Finally, it enters the main event loop using `glutMainLoop`.

Overall, the code uses OpenGL and GLUT functions to draw an animated scene of a flag hoisting ceremony. It utilizes various geometric shapes, translations, rotations, and color settings to create the animation effect.

*/