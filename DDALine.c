#include <stdio.h>
#include <GL/glut.h>
int xa, ya, xb, yb;
int lineType;
int Round(float a)
{
	return (int)(a + 0.5);
}
void ddaline(int xa, int ya, int xb, int yb, int lineType)
{
	int dx, dy, steps;
	dx = xb - xa;
	dy = yb - ya;
	if (abs(dx) > abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	float xincrement, yincrement;
	xincrement = dx / (float)(steps);
	yincrement = dy / (float)(steps);
	float x, y;
	x = xa;
	y = ya;
	glVertex2d(Round(x), Round(y));
	int k;
	for (k = 0; k < steps; k++)
	{
		int m = 0;
		if (lineType == 4)
		{
			glPointSize(3.0);
			glBegin(GL_POINTS);
			glVertex2d(Round(x), Round(y));
		}
		if (lineType == 3)
		{
			if (k % 4 != 0)
			{
				glBegin(GL_POINTS);
				glVertex2d(Round(x), Round(y));
			}
		}
		else if (lineType == 2)
		{
			if (k % 4 == 0)
			{
				glBegin(GL_POINTS);
				glVertex2d(Round(x), Round(y));
			}
		}
		else
		{
			glBegin(GL_POINTS);
			glVertex2d(Round(x), Round(y));
		}
		x = x + xincrement;
		y = y + yincrement;
	}
	glEnd();
	glFlush();
}

void mouse1(int button, int state, int x, int y)
{ // mouse function take input with mouse
	y = 480 - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{ // press the left click for first vertex input
		xa = x;
		ya = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{ // leave the left click for second vertex input
		xb = x;
		yb = y;
		glColor3f(1.0, 0.0, 0.0);
		ddaline(xa, ya, xb, yb, lineType);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{ // right click to change the linetype while drawing.
		if (lineType == 4)
		{
			lineType = 1;
			glPointSize(1);
		}
		else
			lineType++;
	}
}
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	ddaline(0, 240, 640, 240, 1);
	ddaline(320, 0, 320, 480, 1);
}
int main(int argc, char **argv)
{
	printf("Enter what type of line to draw (1. Simple 2. Dotted 3. Dashed 4. Solid) ");
	scanf("%d", &lineType);
	printf("Drag a line across the screen\nAnd RIGHT CLICK to chnage the line type while drawing\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutCreateWindow("DDA Line");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(Draw);
	glutMouseFunc(mouse1);
	glutMainLoop();
	return 0;
}
