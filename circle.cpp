#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

//Defalut radius of circle 
int cx=300,cy=300,R=70;
bool flag=1;

//Color struct 
struct color{
	GLubyte r,g,b;
};

//init function for init.
void init()
{
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,600,0,600);
	glColor3f(0,0,0);
}

//ploat the pixel (x,y)
void plotpixel(int x,int y)
{
	glPointSize(1.5);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

//ploat the points using the circle sym.
void octant(int xc,int yc,int x,int y)
{
	plotpixel(xc+x,yc+y);
	plotpixel(xc+y,yc+x);
	plotpixel(xc+y,yc-x);
	plotpixel(xc+x,yc-y);

	plotpixel(xc-x,yc-y);
	plotpixel(xc-y,yc-x);
	plotpixel(xc-y,yc+x);
	plotpixel(xc-x,yc+y);
	
}

//mid point circle drawing 
void circleMP(int xc,int yc,int r)
{
	int p=1-r,x=0,y=r;
	//loop til the x become y equal to radius (r,r)
	while(x<y)
	{
		octant(xc,yc,x,y);
		x++;
		if(p>0)			//if p>0 decrement the y and 2(x-y)+1
			y--,p+=2*(x-y)+1;
		else			//if p<=0 add 2x+1 to p
			p+=2*x+1;
	}
}

//convert the rad to deg
double ang(int q)
{
	return (double)q*3.142/180;
}

void plottofill(int x,int y,color c)
{
	glPointSize(1.0);
	glColor3ub(c.r,c.g,c.b);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
void seedfill(int x,int y,color oc,color nc)
{
	color c;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
	if(c.r==oc.r&&c.b==oc.b&&c.g==oc.g)
	{
		plottofill(x,y,nc);
		seedfill(x+1,y,oc,nc);
		seedfill(x-1,y,oc,nc);
		seedfill(x,y+1,oc,nc);
		seedfill(x,y-1,oc,nc);
	}
}

//Draw all the Cirlces
void drawcircles(int x,int y,int r)
{
	circleMP(x,y,r);
	
	circleMP(x+2*r,y,r);
	circleMP(x-2*r,y,r);
	
	circleMP(x+2*r*cos(ang(60)),y+2*r*sin(ang(60)),r);
	circleMP(x-2*r*cos(ang(60)),y+2*r*sin(ang(60)),r);
	circleMP(x-2*r*cos(ang(60)),y-2*r*sin(ang(60)),r);
	circleMP(x+2*r*cos(ang(60)),y-2*r*sin(ang(60)),r);	
	
	circleMP(x,y,3*r);
	
	circleMP(x,y,(float)2*r-r*(0.20));
}

//Display Function
void draw()
{
	
}

//Clear the whole screen
void clear_screen()
{
	 glClearColor(1,1,1,0);
	 glClear(GL_COLOR_BUFFER_BIT);	
}

//Mouse click function
void mouseClick(int button,int state,int x,int y)
{	
	cout<<"Mouse Clicked"<<endl;
	//First point to get the xc,yc
	if(flag&&button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		cout<<"Center Found"<<endl;
		cx=x,cy=600-y;
		glPointSize(5.0);
		glColor3f(1,0,0);
		glBegin(GL_POINTS);
			glVertex2i(x,600-y);
		glEnd();
		glFlush();
		flag=0;	
	}
	//find the radius of the circle
	else if (!flag&&button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		cout<<"Ohhho !!, I got a radius"<<endl;
		glColor3f(0,0,1);
		glPointSize(1.0);
		glBegin(GL_POINTS);
			glVertex2i(x,600-y);
		glEnd();
		glFlush();
		R=abs(x-cx);
		flag=1;
	}
}


//Menu function
void menu(int ch)
{
	color oc={255,255,255};
	color nc={255,0,0};
	switch(ch)
	{
		case 1:
			drawcircles(cx,cy,R);
			break;
		case 2:
			clear_screen();
			break;
		case 3:
			cout<<"Fill the Centered Circle"<<endl;
			seedfill(cx+5,cy,oc,nc);
			break;
		case 4:
			exit(0);
			break;
	}

}


int main(int agrc,char ** agrv)
{
	glutInit(&agrc,agrv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("Circle");
	init();
	glutDisplayFunc(draw);
	glutCreateMenu(menu);
		glutAddMenuEntry("Draw",1);
		glutAddMenuEntry("Clear",2);
		glutAddMenuEntry("Color Fill",3);
		glutAddMenuEntry("Exit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(mouseClick);
	glutMainLoop();
}

/*

Certainly! Let's go through the code and explain each function and its purpose:

```cpp
#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;
```
This section includes the necessary header files for the program, including `iostream` for input/output operations, `GL/glut.h` for OpenGL and GLUT functions, and `math.h` for mathematical functions. The `using namespace std;` statement allows using standard library functions and objects without explicitly specifying the namespace.

```cpp
int cx=300,cy=300,R=70;
bool flag=1;
```
These variables store the initial values for the center coordinates (`cx` and `cy`) and the radius (`R`) of the circle. The `flag` variable is used as a flag to indicate whether the center of the circle has been clicked or not.

```cpp
struct color{
    GLubyte r,g,b;
};
```
This `color` struct is defined to store the RGB values for colors. `GLubyte` is an OpenGL specific unsigned byte type.

```cpp
void init()
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0,600,0,600);
    glColor3f(0,0,0);
}
```
The `init` function is used to set up the OpenGL environment. It sets the clear color to white using `glClearColor`, clears the color buffer using `glClear`, sets up a 2D orthographic projection using `gluOrtho2D`, and sets the current drawing color to black using `glColor3f`.

```cpp
void plotpixel(int x,int y)
{
    glPointSize(1.5);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}
```
The `plotpixel` function is used to draw a single pixel on the screen. It takes the x and y coordinates as parameters. It sets the point size using `glPointSize`, starts drawing points using `glBegin(GL_POINTS)`, specifies the vertex using `glVertex2i`, ends drawing using `glEnd`, and flushes the drawing commands to the screen using `glFlush`.

```cpp
void octant(int xc,int yc,int x,int y)
{
    plotpixel(xc+x,yc+y);
    plotpixel(xc+y,yc+x);
    plotpixel(xc+y,yc-x);
    plotpixel(xc+x,yc-y);
    plotpixel(xc-x,yc-y);
    plotpixel(xc-y,yc-x);
    plotpixel(xc-y,yc+x);
    plotpixel(xc-x,yc+y);  
}
```
The `octant` function is used to plot the pixels using the circle symmetry. It takes the center coordinates (`xc` and `yc`) and the current coordinates (`x` and `y`) as parameters. It calls the `plotpixel` function to plot pixels in all eight octants of the circle.

```cpp
void circleMP(int xc,int yc,int r)
{
    int p=1-r,x=0,y=r;
    while(x<y)
    {
        octant(xc,yc,x,y);
        x++;
        if(p>0)
            y--,p+=2*(x-y)+1;
        else
            p+=2*x+1;
    }
}
```
The `circleMP` function is used to draw a circle using the midpoint circle drawing algorithm. It takes the center coordinates (`xc` and `yc`) and the radius (`r`) as parameters. It uses the midpoint algorithm to draw the circle by plotting pixels in each octant using the `oct

ant` function.

```cpp
double ang(int q)
{
    return (double)q*3.142/180;
}
```
The `ang` function is used to convert the angle in degrees to radians. It takes the angle in degrees as a parameter and returns the corresponding angle in radians.

```cpp
void plottofill(int x,int y,color c)
{
    glPointSize(1.0);
    glColor3ub(c.r,c.g,c.b);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}
```
The `plottofill` function is used to plot a pixel with a specific color for filling purposes. It takes the x and y coordinates and a `color` struct (`c`) as parameters. It sets the point size, color, and plots the pixel using the `glBegin`, `glVertex2i`, and `glEnd` functions.

```cpp
void seedfill(int x,int y,color oc,color nc)
{
    color c;
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
    if(c.r==oc.r&&c.b==oc.b&&c.g==oc.g)
    {
        plottofill(x,y,nc);
        seedfill(x+1,y,oc,nc);
        seedfill(x-1,y,oc,nc);
        seedfill(x,y+1,oc,nc);
        seedfill(x,y-1,oc,nc);
    }
}
```
The `seedfill` function is used for the seed fill algorithm to fill a closed area with a new color. It takes the starting coordinates (`x` and `y`), the old color (`oc`), and the new color (`nc`) as parameters. It reads the color of the current pixel using `glReadPixels` and checks if it matches the old color. If it does, it plots the pixel with the new color using `plottofill` and recursively calls `seedfill` for the neighboring pixels.

```cpp
void drawcircles(int x,int y,int r)
{
    circleMP(x,y,r);
    
    circleMP(x+2*r,y,r);
    circleMP(x-2*r,y,r);
    
    circleMP(x+2*r*cos(ang(60)),y+2*r*sin(ang(60)),r);
    circleMP(x-2*r*cos(ang(60)),y+2*r*sin(ang(60)),r);
    circleMP(x-2*r*cos(ang(60)),y-2*r*sin(ang(60)),r);
    circleMP(x+2*r*cos(ang(60)),y-2*r*sin(ang(60)),r);  
    
    circleMP(x,y,3*r);
    
    circleMP(x,y,(float)2*r-r*(0.20));
}
```
The `drawcircles` function is used to draw all the circles using the `circleMP` function. It takes the center coordinates (`x` and `y`) and the radius (`r`) as parameters. It draws multiple circles by calling `circleMP` with different parameters to create the desired pattern.

```cpp
void draw()
{
    
}
```
The `draw` function is an empty function that doesn't have any functionality. It is used as the display callback function for GLUT.

```cpp
void clear_screen()
{
     glClearColor(1,1,1,0);
     glClear(GL_COLOR_BUFFER_BIT);    
}
```
The `clear_screen` function is used to clear the whole screen by setting the clear color to white and clearing the color buffer.

```cpp
void mouseClick(int button,int state,int x,int y)
{
    // ...
}
```
The `mouseClick`

 function is the mouse click callback function for GLUT. It is called when a mouse button is pressed or released. It takes the button, state, x, and y coordinates as parameters. The function handles mouse clicks to identify the center and radius of the circle.

```cpp
void menu(int ch)
{
    // ...
}
```
The `menu` function is the menu callback function for GLUT. It is called when a menu item is selected. It takes the selected menu item as a parameter. The function implements different actions based on the selected menu item, such as drawing circles, clearing the screen, filling the centered circle, or exiting the program.

```cpp
int main(int agrc,char ** agrv)
{
    // ...
}
```
The `main` function is the entry point of the program. It initializes GLUT, sets up the window and display mode, creates the window, sets up the display and menu functions, attaches the menu to the right mouse button, registers the mouse click callback function, and enters the GLUT main loop to handle events.

Overall, this program uses OpenGL and GLUT to draw circles, handle mouse clicks, and provide a menu for different actions such as drawing, clearing, and filling circles. It implements various functions to achieve these functionalities using the provided OpenGL functions.

*/
