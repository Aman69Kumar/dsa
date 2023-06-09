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

Sure! Let's go through the code and explain each function and its purpose.

```cpp
#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;
```

The code starts by including necessary header files, including `iostream` for input/output operations, `GL/glut.h` for OpenGL and GLUT functions, and `math.h` for mathematical functions.

```cpp
int cx=300, cy=300, R=70;
bool flag=1;
```

These variables are used to store the center coordinates of the circle (`cx` and `cy`), and the radius of the circle (`R`). The `flag` variable is used to keep track of the state of the program.

```cpp
struct color {
	GLubyte r, g, b;
};
```

This `color` struct is defined to store the RGB values of a color. `GLubyte` is an OpenGL data type for an 8-bit unsigned byte.

```cpp
void init() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, 600, 0, 600);
	glColor3f(0, 0, 0);
}
```

The `init` function is responsible for initializing the OpenGL environment. It sets the clear color to white, clears the color buffer, sets up a 2D orthographic projection with a range of (0, 600) for both x and y axes, and sets the current color to black.

```cpp
void plotpixel(int x, int y) {
	glPointSize(1.5);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}
```

The `plotpixel` function is used to plot a pixel at the given `(x, y)` coordinates. It sets the point size, starts drawing points, specifies the vertex position using `glVertex2i`, ends drawing points, flushes the drawing commands, and updates the screen.

```cpp
void octant(int xc, int yc, int x, int y) {
	plotpixel(xc + x, yc + y);
	plotpixel(xc + y, yc + x);
	plotpixel(xc + y, yc - x);
	plotpixel(xc + x, yc - y);

	plotpixel(xc - x, yc - y);
	plotpixel(xc - y, yc - x);
	plotpixel(xc - y, yc + x);
	plotpixel(xc - x, yc + y);
}
```

The `octant` function is used to plot pixels in all eight octants of a circle given the center coordinates (`xc`, `yc`) and the current point coordinates (`x`, `y`). It calls the `plotpixel` function for each octant to plot the pixels.

```cpp
void circleMP(int xc, int yc, int r) {
	int p = 1 - r, x = 0, y = r;
	while (x < y) {
		octant(xc, yc, x, y);
		x++;
		if (p > 0)
			y--, p += 2 * (x - y) + 1;
		else
			p += 2 * x + 1;
	}
}
```

The `circleMP` function is used to draw a circle using the midpoint circle drawing algorithm. It takes the center coordinates (`xc`, `yc`) and the radius (`r`) as parameters. The algorithm uses the octant function to plot pixels in all eight octants of the circle.

```cpp
double ang(int q) {
	return (double)q

 * 3.142 / 180;
}
```

The `ang` function is used to convert an angle in degrees to radians. It takes an angle `q` as input and returns the corresponding angle in radians.

```cpp
void plottofill(int x, int y, color c) {
	glPointSize(1.0);
	glColor3ub(c.r, c.g, c.b);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}
```

The `plottofill` function is used to plot a pixel with the specified color (`c`) at the given `(x, y)` coordinates. It sets the point size, color, starts drawing points, specifies the vertex position, ends drawing points, flushes the drawing commands, and updates the screen.

```cpp
void seedfill(int x, int y, color oc, color nc) {
	color c;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
	if (c.r == oc.r && c.b == oc.b && c.g == oc.g) {
		plottofill(x, y, nc);
		seedfill(x + 1, y, oc, nc);
		seedfill(x - 1, y, oc, nc);
		seedfill(x, y + 1, oc, nc);
		seedfill(x, y - 1, oc, nc);
	}
}
```

The `seedfill` function implements the seed fill algorithm for filling an area with a new color. It takes the starting coordinates (`x`, `y`), the original color (`oc`), and the new color (`nc`) as parameters. It reads the color of the current pixel using `glReadPixels` and checks if it matches the original color. If it does, it plots the pixel with the new color using `plottofill` and recursively calls `seedfill` for the neighboring pixels.

```cpp
void drawcircles(int x, int y, int r) {
	circleMP(x, y, r);
	
	circleMP(x + 2 * r, y, r);
	circleMP(x - 2 * r, y, r);
	
	circleMP(x + 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
	circleMP(x - 2 * r * cos(ang(60)), y + 2 * r * sin(ang(60)), r);
	circleMP(x - 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);
	circleMP(x + 2 * r * cos(ang(60)), y - 2 * r * sin(ang(60)), r);	
	
	circleMP(x, y, 3 * r);
	
	circleMP(x, y, (float)2 * r - r * (0.20));
}
```

The `drawcircles` function is used to draw multiple circles with different radii and positions. It calls the `circleMP` function for each circle with the appropriate center coordinates and radius.

```cpp
void draw() {
	
}
```

The `draw` function is an empty function. It is provided as a parameter to `glutDisplayFunc` to specify the function that will be called when the window needs to be redrawn.

```cpp
void clear_screen() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}
```

The `clear_screen` function is used to clear the entire screen by setting the clear color to white and clearing the color buffer.

```

cpp
void mouseClick(int button, int state, int x, int y) {
	cout << "Mouse Clicked" << endl;
	if (flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "Center Found" << endl;
		cx = x, cy = 600 - y;
		glPointSize(5.0);
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
			glVertex2i(x, 600 - y);
		glEnd();
		glFlush();
		flag = 0;	
	}
	else if (!flag && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cout << "Ohhho !!, I got a radius" << endl;
		glColor3f(0, 0, 1);
		glPointSize(1.0);
		glBegin(GL_POINTS);
			glVertex2i(x, 600 - y);
		glEnd();
		glFlush();
		R = abs(x - cx);
		flag = 1;
	}
}
```

The `mouseClick` function is a callback function that is triggered when a mouse button is clicked. It handles two scenarios: finding the center of the circle and finding the radius of the circle. When the `flag` is true, it means the program is waiting to find the center. When the left mouse button is clicked, the function stores the center coordinates, plots a red point on the screen, and sets `flag` to false. In the second scenario, when `flag` is false, the function calculates the radius based on the distance between the current mouse position and the center. It plots a blue point on the screen and sets `flag` back to true.

```cpp
void menu(int ch) {
	color oc = {255, 255, 255};
	color nc = {255, 0, 0};
	switch (ch) {
		case 1:
			drawcircles(cx, cy, R);
			break;
		case 2:
			clear_screen();
			break;
		case 3:
			cout << "Fill the Centered Circle" << endl;
			seedfill(cx + 5, cy, oc, nc);
			break;
		case 4:
			exit(0);
			break;
	}
}
```

The `menu` function is a callback function for the GLUT menu. It is triggered when a menu item is selected. It takes an integer `ch` as input, which represents the chosen menu item. Based on the value of `ch`, it performs different actions. If `ch` is 1, it calls `drawcircles` to draw the circles. If `ch` is 2, it calls `clear_screen` to clear the screen. If `ch` is 3, it performs the seed fill operation by calling `seedfill` with the appropriate parameters. If `ch` is 4, it exits the program.

```cpp
int main(int agrc, char** agrv) {
	glutInit(&agrc, agrv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Circle");
	init();
	glutDisplayFunc(draw);
	glutCreateMenu(menu);
		glutAddMenuEntry("Draw", 1);
		glutAddMenuEntry("Clear", 2);
		glutAddMenuEntry("Color Fill", 3);
		glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMouseFunc(mouseClick);
	glutMainLoop();
}
```

The `main` function is the entry point of the program. It initializes GLUT, sets the display

 mode, window position, and window size. It creates a window with the title "Circle" and initializes the OpenGL environment using the `init` function. It specifies the `draw` function as the display callback function. It creates a menu using `glutCreateMenu` and adds menu entries for drawing, clearing, color fill, and exiting. It attaches the menu to the right mouse button using `glutAttachMenu`. It sets the `mouseClick` function as the callback function for mouse clicks. Finally, it enters the GLUT main loop to start the program execution.

This code sets up an interactive program where the user can draw circles, clear the screen, fill circles with color, and exit the program using mouse clicks and a menu.

*/

/* cd Desktop  g++ bresencircle.cpp -lglut -lGL -lGLEW -lGLU -o bresencircle
./a.out  */