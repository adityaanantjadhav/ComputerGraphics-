//USE gcc filename.c -lglut -lGLU -lGL  command to compile
//USE ./a.out TO EXECUTE


#include<stdio.h>
#include<GL/glut.h>

int xmax, xmin, ymax, ymin, Lx1, Lx2, Ly1, Ly2, flag =0, flag2=0, fx1, fx2, fy1, fy2;
int oc1[4];
int oc2[4];
int and1[4];
int and2[4];

int Round(float a)
{
      return (int)(a+0.5);
}
     
void ddaline(float xa,float ya,float xb,float yb)
{
    int dx,dy,steps;
    dx = xb-xa;
    dy = yb-ya;
    if(abs(dx)>abs(dy))
    {
    	steps = abs(dx);
    }
    else
    {
     	steps = abs(dy);
    }
    float xincrement , yincrement;
    xincrement = dx/(float)(steps);
    yincrement = dy/(float)(steps);
    float x = xa;
    float y = ya;
    glVertex2d(Round(x),Round(y));
    for(int k = 0; k<steps; k++)
    {
        x=x+xincrement;
        y=y+yincrement;
        glVertex2d(Round(x),Round(y));
    }
}


void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1,1,1);
    ddaline(xmin, ymin, xmax, ymin);
    ddaline(xmin, ymin, xmin, ymax);
    ddaline(xmin, ymax, xmax, ymax);
    ddaline(xmax, ymin, xmax, ymax);
    glColor3f(1,0,0);
    ddaline(Lx1, Ly1, Lx2, Ly2);
    glEnd();
    glFlush();
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor3f(0,1,1);
    if(flag==0)
        ddaline(fx1, fy1, fx2, fy2);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    printf("Enter window co-ordinates. \n");
    printf("X min : ");
    scanf("%d", &xmin);
    printf("Y min : ");
    scanf("%d", &ymin);
    printf("X max : ");
    scanf("%d", &xmax);
    printf("Y max : ");
    scanf("%d", &ymax);

    printf("Enter line Co-ordinates. \n");
    printf("X1 : ");
    scanf("%d", &Lx1);
    printf("Y1 : ");
    scanf("%d", &Ly1);
    printf("X2 : ");
    scanf("%d", &Lx2);
    printf("Y2 : ");
    scanf("%d", &Ly2);

    int lx1=Lx1, lx2=Lx2, ly1=Ly1, ly2=Ly2;
for(int j=0; j<3; j++)
{
    flag =0;
    for(int i=0; i<4; i++)
    {
        oc1[i] = 0;
        oc2[i] = 0;
        and1[i] = 0;
        and2[i] = 0;
    }

    if(ly1 > ymax)
        oc1[0] = 1;
    if(ly1 < ymin)
        oc1[1] = 1;
    if(lx1 > xmax)
        oc1[2] = 1;
    if(lx1 < xmin)
        oc1[3] = 1;

    if(ly2 > ymax)
        oc2[0] = 1;
    if(ly2 < ymin)
        oc2[1] = 1;
    if(lx2 > xmax)
        oc2[2] = 1;
    if(lx2 < xmin)
        oc2[3] = 1;

    for(int i=0; i<4; i++)
    {
        printf("%d \t %d \n", oc1[i], oc2[i]);
    }
    printf("\n");


    for(int i=0; i<4; i++)
    {
        if(oc1[i]==1 || oc2[i]==1)
        {
            and1[i] = 1;
            flag = 1;
        }
        if(oc1[i]==1 && oc2[i]==1)
        {
            flag2 = 1;
        }
    }
    if(flag == 0)
    {
        printf("\nLine in inside. \n");
        fx1 = lx1;
        fx2 = lx2;
        fy1 = ly1;
        fy2 = ly2;
        break;
    }

    else if(flag2 == 1)
    {
        printf("\nLine is completely outside.\n");
        fx1 = 0;
        fx2 = 0;
        fy1 = 0;
        fy2 = 0;
        break;
    }

    else
    {
        float m = (ly2-ly1)/(float)(lx2-lx1);
        if(oc1[0] == 1)
        {
            ly1 = ymax;
            lx1 = lx2 + (ly1-ly2)/m;
        }
        else if(oc1[1] == 1)
        {
            ly1 = ymin;
            lx1 = lx2 + (ly1-ly2)/m;
        }
        else if(oc1[2] == 1)
        {
            lx1 = xmax;
            ly1 = ly2 + (lx1-lx2)*m;
        }
        else if(oc1[3] == 1)
        {
            lx1 = xmin;
            ly1 = ly2 + (lx1-lx2)*m;
        }
    
        if(oc2[0] == 1)
        {
            ly2 = ymax;
            lx2 = lx1 + (ly2-ly1)/m;
        }
        else if(oc2[1] == 1)
        {
            ly2 = ymin;
            lx2 = lx1 + (ly2-ly1)/m;
        }
        else if(oc2[2] == 1)
        {
            lx2 = xmax;
            ly2 = ly1 + (lx2-lx1)*m;
        }
        else if(oc2[3] == 1)
        {
            lx2 = xmin;
            ly2 = ly1 + (lx2-lx1)*m;
        }
        fx1 = lx1;
        fx2 = lx2;
        fy1 = ly1;
        fy2 = ly2;
    }
} 

if(flag==1)
{
    printf("Line is completely outside\n");
}

    printf("\n%d \t %d \t %d \t %d\n", Lx1, Ly1, Lx2, Ly2);
    printf("%d \t %d \t %d \t %d\n", fx1, fy1, fx2, fy2);


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Clipping");
    gluOrtho2D(0, 640, 0, 480);
    glClearColor(0,0,0,0);
    glutDisplayFunc(Draw);
    glutMainLoop();
}