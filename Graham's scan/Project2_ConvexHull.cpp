#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include <glut.h>
#include<cmath>
#include<Windows.h>
using namespace std;


int X, Y,n,NUM;
struct Point
{
	int x, y;
}; Point* P; Point* Q;

void Find_Lowest_Point(Point *a,int n) 
{    
	int min=a[0].y;
	Point* p=new Point;
	for (int i = 0; i < n; i++)
	{
		if (a[i].y<=min)
		{
			min = a[i].y;
			p = &a[i];

		}
		std::cout << " min:" <<min<<" p:"<<p->y<< '\n';
		//Point* t;
		//t = &a[0]; a[0] = *p; p = t;
	}
	swap(a[0], *p);
}

bool AngleCMP(Point a,Point b) 
{
	if (atan2(a.y-Y, a.x-X) == atan2(b.y-Y, b.x-X))
		return atan2(a.y, a.x) < atan2(b.y, b.x);
	else
		return a.x < b.x;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Display() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 1);	
	glPointSize(5.0);
	glBegin(GL_POINTS);
	/*int a = sizeof P / sizeof Point; int b = sizeof Q / sizeof Point;
	std::cout<<"SZ P: "<<sizeof &P<<" SZ Point:"<<sizeof Point<<'\n';*/
	for (int i = 0; i <n; i++)
	{
		std::cout <<P[i].y<< '\n';
		float x1 = P[i].x /1000.0; float y1 = P[i].y / 1000.0;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.8, 0.7, 0.2);
	glPointSize(7.0);

	glBegin(GL_POINTS);
	for (int i = 0; i < NUM; i++)
	{
		float x2 = Q[i].x /1000.0; float y2 = Q[i].y/1000.0;
		glVertex2f(x2, y2);
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	n=0;
    std::cout << "Input the number of random point: "; 
	std::cin >> n;
	Point* a;
	a = new Point[n];
	for (int i = 0; i < n; i++)
	{
		a[i].x= rand()%1000;
		a[i].y= rand()%1000;
	}
	std::cout << a[3].x << '\t' << a[2].y << '\n';
	Point* final = new Point[n];
	Find_Lowest_Point(a, n);
	final[0] = a[0];
	X = a[0].x; Y = a[0].y;
	sort(a+1,a+n,AngleCMP);
	final[1] = a[1];
	NUM = 1;
	int CrossProduct = 0;
	for (int i = 1; i < n; i++)
	{
		CrossProduct = (final[NUM].x-final[NUM-1].x)*(a[i].y-final[NUM-1].y) - (a[i].x - final[NUM-1].x)*(final[NUM].y - final[NUM-1].y);
		if(CrossProduct<0)
		{
			NUM--;
		}
		final[++NUM] = a[i];
	}
	P = a; Q = final;
	std::cout << "a[3].X" << a[0].y << '\n';
	std::cout << "P[3].X"<<P[0].y << '\n';

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Project 2 - Convex Hull");
	init();
	glutDisplayFunc(&Display);
	glutMainLoop();
	return 0;
}

