#include<stdio.h>
#include<GL/glut.h>

float input[2][10],output[2][10],output1[2][10],output2[2][10],window[2][10];
float xmin,ymin,xmax,ymax;
int k=0,v,vinitial;


int roundoff(float val){
	return val+0.5;
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
	float xin=dx/(float)(steps);
	float yin=dy/(float)(steps);
	float x=xa;
	float y=ya;
	glBegin(GL_POINTS);
	glVertex2d(roundoff(x),roundoff(y));
	for(int i=0;i<steps;i++){
		x=x+xin;
		y=y+yin;
		glVertex2d(roundoff(x),roundoff(y));
	}
	
}

void display(float input[2][10]){
	for(int l=0;l<2;l++){
		for(int m=0;m<v;m++){
			printf("%f\t",input[l][m]);
		}printf("\n");
	}printf("\n");
}

void left(float xa,float ya,float xb,float yb){
	float m=(yb-ya)/(xb-xa);
	if(xa<xmin && xb>xmin){
		output[0][k]=xmin;
		output[1][k]=ya+m*(xmin-xa);
		k++;
		output[0][k]=xb;
		output[1][k]=yb;
		k++;
}
	if(xa>xmin && xb>xmin){
		output[0][k]=xb;
		output[1][k]=yb;
		k++;
	}
	if(xa>xmin && xb<xmin){
		output[0][k]=xmin;
		output[1][k]=ya+m*(xmin-xa);
		k++;
	}
}

void right(float xa,float ya,float xb,float yb){
	float m=(yb-ya)/(xb-xa);
	if(xa>xmax && xb<xmax){
		output2[0][k]=xmax;
		output2[1][k]=ya+m*(xmax-xa);
		k++;
		output2[0][k]=xb;
		output2[1][k]=yb;
		k++;
	}
	if(xa<xmax && xb<xmax){
		output2[0][k]=xb;
		output2[1][k]=yb;
		k++;
	}
	if(xa<xmax && xb>xmax){
		output2[0][k]=xmax;
		output2[1][k]=ya+m*(xmax-xa);
		k++;
	}	
}

void up(float xa,float ya,float xb,float yb){
	float m=(yb-ya)/(xb-xa);
	if(ya>ymax && yb<ymax){
		output[1][k]=ymax;	
		output[0][k]=(ymax-ya)/m+xa;
		k++;
		output[0][k]=xb;
		output[1][k]=yb;
		k++;
	}
	if(ya<ymax && yb<ymax){
		output[0][k]=xb;
		output[1][k]=yb;
		k++;
	}
	if(ya<ymax && yb>ymax){
		output[0][k]=(ymax-ya)/m+xa;
		output[1][k]=ymax;
		k++;
	}
}

void down(float xa,float ya,float xb,float yb){
	float m=(ya-yb)/(xa-xb);
	if(ya<ymin && yb>ymin){
		output2[0][k]=(ymin-ya)/m+xa;
		output2[1][k]=ymin;
		k++;
		output2[0][k]=xb;
		output2[1][k]=yb;
		k++;
	}
	if(ya>ymin && yb>ymin){
		output2[0][k]=xb;
		output2[1][k]=yb;
		k++;
	}
	if(ya>ymin && yb<ymin){
		output2[0][k]=(ymin-ya)/m+xa;
		output2[1][k]=ymin;
		k++;
	}
}

void polygon(float input[2][10],int v){
	int i;
	for(i=0;i<v-1;i++){
		ddaline(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
	}
	ddaline(input[0][0],input[1][0],input[0][i],input[1][i]);
}

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2);
	polygon(input,vinitial);
	
	glColor3f(1,0,0);
	polygon(window,4);
	glColor3f(0,0,1);
	polygon(output2,v);
	glEnd();
	glFlush();

}

int main(int argc,char** argv){
	printf("enter the no.of vetices:");
	scanf("%d",&v);
	vinitial=v;
	printf("enter the polygon:\n");
	for(int i=0;i<v;i++){
		printf("enter the x:");
		scanf("%f",&input[0][i]);
		printf("enter the y:");
		scanf("%f",&input[1][i]);

}
	printf("enter the min x and y:");
	scanf("%f%f",&xmin,&ymin);
	printf("enter the max x and y:");
	scanf("%f%f",&xmax,&ymax);
	int i;
	printf("input:\n");
	display(input);
	for(i=0;i<v-1;i++){	
		left(input[0][i],input[1][i],input[0][i+1],input[1][i+1]);
	}left(input[0][i],input[1][i],input[0][0],input[1][0]);
	v=k;
	k=0;	
	for(i=0;i<v-1;i++){	
		right(output[0][i],output[1][i],output[0][i+1],output[1][i+1]);
	}right(output[0][i],output[1][i],output[0][0],output[1][0]);
	printf("output2:\n");
	display(output2);
	v=k;
	k=0;
	for(i=0;i<v-1;i++){	
		up(output2[0][i],output2[1][i],output2[0][i+1],output2[1][i+1]);
	}up(output2[0][i],output2[1][i],output2[0][0],output2[1][0]);
	printf("output:\n");
	display(output);
	v=k;
	k=0;
	for(i=0;i<v-1;i++){	
		down(output[0][i],output[1][i],output[0][i+1],output[1][i+1]);
	}down(output[0][i],output[1][i],output[0][0],output[1][0]);
	printf("output2:\n");
	display(output2);
	v=k;
	window[0][0]=xmin;
	window[1][0]=ymin;
	window[0][1]=xmax;
	window[1][1]=ymin;
	window[0][2]=xmax;
	window[1][2]=ymax;
	window[0][3]=xmin;
	window[1][3]=ymax;

    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE || GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(540,480);
	glutCreateWindow("transform");
	glClearColor(1,1,1,0);
	glColor3f(0,0,0);
	gluOrtho2D(0,540,0,480);
	glutDisplayFunc(draw);
	glutMainLoop();

}