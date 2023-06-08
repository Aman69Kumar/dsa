#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;
float R=0,G=0,B=0;
int Algo; void init(){
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,640,0,480);
}
void floodFill(int x, int y, float *newCol, float *oldcol)
{
    float pixel[3];
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixel);
if(oldcol[0]==pixel[0] && oldcol[1]==pixel[1] && oldcol[2]==pixel[2])
    {
        glBegin(GL_POINTS);
glColor3f(newCol[0],newCol[1],newCol[2]);
glVertex2i(x,y);
glEnd();
glFlush();
floodFill(x,y+1,newCol,oldcol);
floodFill(x+1,y,newCol,oldcol);
floodFill(x,y-1,newCol,oldcol);
floodFill(x-1,y,newCol,oldcol);
}
}
void boundaryFill(int x, int y, float* fillColor, float* bc)
{
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2]) && (fillColor[0]!=color[0] || fillColor[1]!=color[1] || fillColor[2]!=color[2]))
{
glColor3f(fillColor[0],fillColor[1],fillColor[2]); glBegin(GL_POINTS);
glVertex2i(x,y);
glEnd();
glFlush();
boundaryFill(x+1,y,fillColor,bc);
boundaryFill(x-1,y,fillColor,bc);
boundaryFill(x,y+1,fillColor,bc);
boundaryFill(x,y-1,fillColor,bc);
}
return;
}
void mouse(int btn, int state, int x, int y)
{
    y = 480-y;
if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float bcol[] = {1,0,0};
float oldcol[] = {1,1,1};
float newCol[] = {R,G,B};
if(Algo==1){
        boundaryFill(x,y,newCol,bcol);
}
if(Algo==2){ floodFill(x,y,newCol,oldcol);
}
}
}
void B_Draw(){
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0);
glBegin(GL_LINE_LOOP);
glVertex2i(150,100);
glVertex2i(300,300);
glVertex2i(450,100);
glEnd();
glFlush();
}
void F_Draw(){
glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_LINES);
glColor3f(1,0,0);
glVertex2i(150,100);
glVertex2i(300,300);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f(0,0,1);
glVertex2i(300,300);
glVertex2i(450,100);
glEnd();
glBegin(GL_LINE_LOOP);
glColor3f(0,0,0);
glVertex2i(450,100);
glVertex2i(150,100);
glEnd();
glFlush();
}
void goMenu(int value){
    switch(value){
case 1:
R = 0, G = 1, B=0;
break;
case 2:
R = 1, G = 1, B=0;
break;
case 3:
R = 0, G = 0, B=1;
break;
}
glutPostRedisplay();
}
int main(int argc, char** argv)
{ cout<<"\n \t Select the Algorithm ";
cout<<"\n \t 1. Boundary Fill Algorithm ";
cout<<"\n \t 2. Flood Fill Algorithm \n \t";
cin>>Algo;
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(200,200);
glutCreateWindow("Boundary Fill and Flood Fill");
init();
glutCreateMenu(goMenu);
glutAddMenuEntry("Color 1 Green",1);
glutAddMenuEntry("Color 2 Yellow",2);
glutAddMenuEntry("Color 3 Blue",3);
glutAttachMenu(GLUT_RIGHT_BUTTON);
if(Algo==1)
    {
glutDisplayFunc(B_Draw);
}
if(Algo==2)
{ glutDisplayFunc(F_Draw);

}
glutMouseFunc(mouse);
glutMainLoop();
return 0;
}

/*
Sure! Let's go through the code and explain its functionality along with some relevant concepts.

1. First, the necessary header files are included: `<iostream>`, `<math.h>`, and `<GL/glut.h>`. These headers provide functions and declarations required for input/output, mathematical operations, and OpenGL rendering, respectively.

2. Next, some global variables are declared:
   - `R`, `G`, and `B` represent the RGB color values for filling shapes.
   - `Algo` is used to determine the selected algorithm (1 for Boundary Fill, 2 for Flood Fill).

3. The `init()` function is defined to set up the initial state of OpenGL. It sets the clear color using `glClearColor()` (white in this case), configures the projection matrix using `glMatrixMode()`, and specifies the orthographic projection using `gluOrtho2D()`.

4. The `floodFill()` function implements the Flood Fill algorithm. It takes the current coordinates (`x` and `y`), the new color to fill (`newCol`), and the old color (`oldcol`). The function starts by reading the color of the current pixel using `glReadPixels()`. If the current pixel color matches the old color, it fills the pixel with the new color using `glColor3f()` and `glVertex2i()`, and then recursively calls `floodFill()` on the neighboring pixels (up, right, down, left).

5. The `boundaryFill()` function implements the Boundary Fill algorithm. It takes similar parameters as `floodFill()`. It starts by reading the color of the current pixel using `glReadPixels()`. If the current pixel color is different from the boundary color and different from the fill color, it fills the pixel with the fill color and recursively calls `boundaryFill()` on the neighboring pixels.

6. The `mouse()` function is the mouse callback function. It is called when a mouse button is pressed. It receives the button, state, and coordinates of the mouse click. The y-coordinate is adjusted to match the OpenGL coordinate system. If the left button is pressed, it checks the selected algorithm (`Algo`) and calls the respective fill function (`boundaryFill()` or `floodFill()`).

7. The `B_Draw()` and `F_Draw()` functions are responsible for drawing the initial shapes on the screen. They clear the color buffer using `glClear()` and draw the shapes using `glBegin()` and `glVertex2i()`. The colors are specified using `glColor3f()`. `B_Draw()` is used for Boundary Fill, and `F_Draw()` is used for Flood Fill.

8. The `goMenu()` function is called when a menu entry is selected. It changes the fill color (`R`, `G`, `B`) based on the selected option (1 for Green, 2 for Yellow, 3 for Blue). It then calls `glutPostRedisplay()` to trigger a redraw of the window.

9. In the `main()` function, the user is prompted to select the algorithm (1 for Boundary Fill, 2 for Flood Fill) using `cout` and `cin`. Then, the GLUT library functions are called to initialize the window and set the display mode, size, and position. The window title is set to "Boundary Fill and Flood Fill". The `init()` function is called to set up the initial OpenGL state.

10. A menu is created using `glutCreateMenu()`. Three menu entries are added for selecting different colors. The `goMenu()` function is specified as the menu's callback function. The menu is attached to the right mouse button using `glutAttachMenu()`.

11. Depending on the selected

 algorithm (`Algo`), the appropriate display function (`B_Draw()` or `F_Draw()`) is set using `glutDisplayFunc()`.

12. The mouse callback function (`mouse()`) and the main event loop (`glutMainLoop()`) are set using `glutMouseFunc()` and `glutMainLoop()`, respectively.

Overall, this code provides a simple graphical interface using OpenGL and GLUT to perform the Boundary Fill and Flood Fill algorithms based on user input and mouse clicks. The user can select the algorithm and choose colors to fill shapes on the screen.
*/