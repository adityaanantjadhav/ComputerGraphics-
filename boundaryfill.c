#include<stdio.h>
#include<GL/glut.h>

int poly[2][10];
int v,xinside,yinside;
float fill[3]={0,0,1};
float boundary[3]={1,0,0};
float back[3]={1,1,1};

int roundoff(float x){
	return x+0.5;
}
void ddaline(int xa,int ya,int xb,int yb){
	int dx=xb-xa;
	int dy=yb-ya;
	int steps;
	if(abs(dx)>abs(dy)){
	steps=abs(dx);
	}
	else{
		steps=abs(dy);
	}
	float xin= dx/(float)steps;
	float yin= dy/(float)steps;
	glBegin(GL_POINTS);
	float x=xa, y=ya;
	glVertex2d(roundoff(x),roundoff(y));
	for(int i=0;i<steps;i++){
		x=xin+x;
		y=yin+y;
		glVertex2d(roundoff(x),roundoff(y));
	}
}	

void boundaryfill(float* boundary,float* fill, int x,int y){
	float color[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
	if((color[0]!=boundary[0] || color[1]!=boundary[1] || color[2]!=boundary[2]) &&( color[0]!=fill[0] ||color[1]!=fill[1] || color[2]!=fill[2])){				//do not forgot bracket to (colr!=boud)&&(col!=fill)
		glColor3f(fill[0],fill[1],fill[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();
		boundaryfill(boundary,fill,x+2,y);
		boundaryfill(boundary,fill,x-2,y);
		boundaryfill(boundary,fill,x,y+2);
		boundaryfill(boundary,fill,x,y-2);	
	}
}


void mouse(int button,int state,int x, int y){
	y=640-y;
	if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		xinside=x;
		yinside=y;
		boundaryfill(back,fill,xinside,yinside);
	}
}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    glBegin(GL_POINTS);
	int i;
	for(i=0;i<v-1;i++){
		ddaline(poly[0][i],poly[1][i],poly[0][i+1],poly[1][i+1]);
	}
	ddaline(poly[0][i],poly[1][i],poly[0][0],poly[1][0]);

	glEnd();
	glFlush();
}

int main(int argc,char** argv){
	printf("enter the no.of vertices:");
	scanf("%d",&v);
	for(int i=0;i<v;i++){
		printf("enter the x cordinate:");
		scanf("%d",&poly[0][i]);
		printf("enter the y cordinate:");
		scanf("%d",&poly[1][i]);
	}
	printf("enter the boundary color:");
    for(int i=0;i<3;i++){
    	scanf("%f",&boundary[i]);
	}
	printf("enter the fill color:");
	for(int i=0;i<3;i++){
		scanf("%f",&fill[i]);
	}
	for(int j=0;j<2;j++){
		for(int k=0;k<v;k++){
			printf("%d\t",poly[j][k]);
		}printf("\n");
	}printf("\n");
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
	glutInitWindowSize(640,640);
	glutInitWindowPosition(0,0);
	glutCreateWindow("revise");
	glClearColor(1,1,1,0);
	glColor3f(boundary[0],boundary[1],boundary[2]);
	gluOrtho2D(0,640,0,640);
	glutMouseFunc(mouse);
	glutDisplayFunc(draw); 
	glutMainLoop();
}