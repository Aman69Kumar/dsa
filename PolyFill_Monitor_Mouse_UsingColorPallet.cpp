#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
double x1,x2,y1,y2;
//struct pixel to store color in rgb format
typedef struct pixel
{
	float r,g,b;
}pixel;
pixel f_clr,b_clr;//fill color and boundary color
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);//to set background color
    glClear(GL_COLOR_BUFFER_BIT);//to apply back ground color to screen
    glColor3f(0.0, 0.0, 0.0);//to set color of object to be shown on screen
    gluOrtho2D(0,500,0,500);//to set 2D projection rectangle
}
//dda line drawing algorithm
void dda(double x1,double y1,double x2,double y2)
{
	double dx,dy,steps;
	float xi,yi;
	dx=x2-x1;
	dy=y2-y1;
	steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
	xi=dx/(float)steps;
	yi=dy/(float)steps;
	int i;
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(x1,y1);
	for(i=0;i<steps;i++)
	{
		x1+=xi;
		y1+=yi;
		glVertex2d(x1,y1);//function to print one pixel
	}
	glEnd();
	glFlush();
}
//boundary fill algorithm
void boundary_fill(int x,int y)
{
	pixel c;
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,&c);
	if((c.r!=b_clr.r||c.g!=b_clr.g||c.b!=b_clr.b)&&(c.r!=f_clr.r||c.g!=f_clr.g||c.b!=f_clr.b))
	{
		glBegin(GL_POINTS);
		glColor3f(f_clr.r,f_clr.g,f_clr.b);
		glVertex2i(x,y);
		glEnd();
		glFlush();
		boundary_fill(x-1,y);
		boundary_fill(x+1,y);
		boundary_fill(x,y-1);
		boundary_fill(x,y+1);
	}
	glFlush();
}
int ch=1,a,b,c,d;
//function defined for mouse handling
void mymouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)//if left click 
	{
		switch(ch)
		{
			//for selecting vertex in polygon to fill
			case 1:
				a=x;
				b=500-y;
				ch=2;
				break;
			//for selecting color in color pallette 
			case 2:
				c=x;
				d=500-y;
				glReadPixels(c,d,1.0,1.0,GL_RGB,GL_FLOAT,&f_clr);
				boundary_fill(a,b);
				ch=1;
				break;
		}
	}
}

void renderFunction()
{
	int xmax,ymax,i;
    glClear(GL_COLOR_BUFFER_BIT);
    //making color palette
    dda(100,400,400,400);
    dda(100,450,400,450);
    dda(100,400,100,450);
    dda(400,400,400,450);
    for(i=1;i<=4;i++)
    {
    	dda(100+i*60,400,100+i*60,450);
    }
    //coloring color palette
    f_clr.r=1.0f;
    f_clr.g=0.0f;
    f_clr.b=0.0f;
    boundary_fill(130,425);
    f_clr.r=0.0f;
    f_clr.g=1.0f;
    f_clr.b=0.0f;
    boundary_fill(190,425);
    f_clr.r=1.0f;
    f_clr.g=1.0f;
    f_clr.b=0.0f;
    boundary_fill(250,425);
    f_clr.r=0.0f;
    f_clr.g=0.0f;
    f_clr.b=1.0f;
    boundary_fill(310,425);
    f_clr.r=0.0f;
    f_clr.g=1.0f;
    f_clr.b=1.0f;
    boundary_fill(370,425);
    //making diagram
    dda(100,100,200,100);
    dda(200,100,170,75);
    dda(170,75,330,75);
    dda(330,75,300,100);
    dda(300,100,400,100);
    dda(100,100,100,300);
    dda(100,300,400,300);
    dda(400,300,400,100);
    dda(125,125,375,125);
    dda(125,125,125,275);
    dda(125,275,375,275);
    dda(375,275,375,125);
    dda(125,125,200,200);
    dda(200,200,250,125);
    dda(250,125,300,250);
    dda(300,250,375,125);
    //setting boundary color
    b_clr.r=0.0f;
    b_clr.g=0.0f;
    b_clr.b=0.0f;
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("**POLYGON FILLING**");
    init();
    glutDisplayFunc(renderFunction);
    glutMouseFunc(mymouse);
    glutMainLoop();    
    return 0;
}


/*

Polygon filling, also known as polygon coloring or polygon shading, is the process of filling the interior of a closed polygonal shape with a specific color or pattern. It is a fundamental operation in computer graphics and is commonly used to render filled shapes, such as polygons and curves, on a computer screen or in printed media.

This code is an implementation of a polygon filling program using the Boundary Fill algorithm. It uses the OpenGL library, specifically the FreeGLUT library, to create a graphical window and draw the polygons.

Let's go through the code step by step:

1. The necessary header files are included:
   - `<GL/freeglut.h>`: It provides functions for creating windows, handling input events, and rendering graphics using OpenGL.
   - `<GL/gl.h>`: It includes the OpenGL function prototypes and constants.
   - `<stdio.h>`: It includes the standard input/output functions.

2. The code defines a `pixel` structure that represents a color in RGB format. It has three float members: `r` for red, `g` for green, and `b` for blue.

3. The `init()` function is defined. It sets up the initial configuration of the OpenGL window. It sets the background color to white, clears the color buffer, sets the drawing color to black, and defines the 2D projection rectangle.

4. The `dda()` function implements the Digital Differential Analyzer (DDA) algorithm for drawing a line. It takes four parameters: the coordinates of the starting point (x1, y1) and the ending point (x2, y2) of the line. It calculates the slope of the line and increments the coordinates accordingly to draw each pixel of the line using the `glVertex2d()` function.

5. The `boundary_fill()` function implements the Boundary Fill algorithm. It takes two parameters: the coordinates (x, y) of the pixel to be filled. It reads the color of the pixel using `glReadPixels()` and checks if it's different from the boundary color (b_clr) and the fill color (f_clr). If so, it fills the pixel with the fill color using `glVertex2i()` and recursively calls itself to fill the neighboring pixels.

6. The `ch` variable is used to keep track of the state of the program. When `ch` is 1, the program expects the user to click on a vertex of the polygon to be filled. When `ch` is 2, the program expects the user to select a color from the color palette.

7. The `mymouse()` function is a callback function that is triggered when a mouse event occurs. When the left button is clicked (`btn == GLUT_LEFT_BUTTON` and `state == GLUT_DOWN`), it handles the mouse click events based on the current value of `ch`. If `ch` is 1, it records the coordinates of the selected vertex. If `ch` is 2, it records the coordinates of the selected color from the color palette, reads the RGB values of the selected color using `glReadPixels()`, and initiates the boundary fill algorithm with the recorded vertex and color.

8. The `renderFunction()` function is the main rendering function. It is responsible for drawing the color palette and the polygon diagram. It uses the `dda()` function to draw the lines of the diagrams and the `boundary_fill()` function to fill the polygon with the selected color.

9. In the `main()` function:
   - The GLUT library is initialized using `glutInit()`.
   - The display mode is set to `GLUT_SINGLE`.
   - The window size and position are defined using `glutInitWindowSize()` and `glutInitWindowPosition()`.
   - A window with the specified parameters is created using `glutCreateWindow()`.
   - The `init()` function is called to initialize the OpenGL window.
   - The `renderFunction()` is set as the display callback function using `glutDisplayFunc()`.
   - The `mymouse()` function is set as the

 mouse callback function using `glutMouseFunc()`.
   - The main event processing loop is started using `glutMainLoop()`.

Overall, this code creates a graphical window, allows the user to select a polygon vertex and a color from the color palette, and fills the selected polygon with the chosen color using the Boundary Fill algorithm.

*/