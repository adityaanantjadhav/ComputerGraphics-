#include<stdio.h>
#include<GL/glut.h>
#include<math.h>


int xa,ya,xb,yb,iter;

int Round(float a)
{
    return (int)(a+0.5);
}

void ddaline(int xa, int ya, int xb, int yb)
{
	int dx, dy, steps;
	
	dx = xb - xa;
	dy = yb - ya;
	
	if(abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
		
	float xinc, yinc;
	xinc = dx/(float)(steps);
	yinc = dy/(float)(steps);
	
	float x=xa;
	float y=ya;
	glBegin(GL_POINTS);
	glVertex2d(Round(x), Round(y));
	
	for(int i=0; i<steps; i++)
	{
		x = x + xinc;
		y = y + yinc;
		glVertex2d(Round(x), Round(y));
	}
}



void koch(int xa,int ya,int xb,int yb,int iter){
	int x2=(2*xa+xb)/3;
	int y2=(2*ya+yb)/3;
	int x3=(2*xb+xa)/3;
	int y3=(2*yb+ya)/3;
float angle=1.074;
	
	int x=x2+(x3-x2)*cos(angle)+(y3-y2)*sin(angle);
	int y=y2-(x3-x2)*sin(angle)+(y3-y2)*cos(angle);
	
	if(iter>0){
		koch(xa,ya,x2,y2,iter-1);
	koch(x2,y2,x,y,iter-1);
		koch(x,y,x3,y3,iter-1);
		koch(x3,y3,xb,yb,iter-1);
	}
	else{
		ddaline(xa,ya,x2,y2);
		ddaline(x2,y2,x,y);
		ddaline(x,y,x3,y3);
		ddaline(x3,y3,xb,yb);
	}
}	


void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	koch(xa,ya,xb,yb,iter);
	glEnd();
	glFlush();
}

int main(int argc,char** argv){
	printf("enter the first co- ordinates:\n");
	scanf("%d%d",&xa,&ya);
	printf("enter the second co- ordinates:\n");
	scanf("%d%d",&xb,&yb);
	printf("enter the no. of iterations:\n");
	scanf("%d",&iter);
	glutInit(&argc, argv);
	// It is used to initilize glut library
	
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
	// sets the initial display mode.
	
	glutInitWindowSize(644,480);
	
	glutInitWindowPosition(0,0);
	
	glutCreateWindow("DDAline");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// red, green, blue, and alpha 
	// set clear color to white
	glColor3f(0.0, 0.0, 0.0);
	// set feel color to black
	gluOrtho2D(0, 640, 0, 480);
	glutDisplayFunc(draw);
	glutMainLoop();
	//keep displaying until program is closed.	
}

	