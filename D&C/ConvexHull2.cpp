#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <stdlib.h>
#include <glut.h>
#include "USClocker.h"//a class of us time-meter
using namespace std;
#define N 1000000
int n = 0;
int t = 0;

struct Points
{
	int x, y;
}p[N], ConvexHull[N];

int Catch[N], mark[N];
int Get_Area(Points a1, Points a2, Points a3)
{
	int area = a1.x*a2.y + a3.x*a1.y + a2.x*a3.y - a3.x*a2.y - a2.x*a1.y - a1.x*a3.y;
	return area;
}
bool cmp(const Points a, const Points b) //Sort the points by x value
{
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}
void Find_Max(int a1, int a2)//Assume that a1 and a2 are the index of two points on the triangle.
{
	int max = 0, index = -1;
	int i = a1;
	if (a1 < a2)
	{
		for (i = a1 + 1; i < a2; i++) //Clockwise
		{
			int area = Get_Area(p[a1], p[i], p[a2]);// Using the cross product to caculate the area of triangle.
			if (area == 0) { Catch[i] = 1; } //Store the possible point
			if (area > max)
			{
				max = area;
				index = i;            //Get the point may create the greatest triangle
			}
		}
	}
	else
	{
		for (i - 1; i > a2; i--) //Counterclockwise
		{
			int area = Get_Area(p[a1], p[i], p[a2]);
			if (area == 0) { Catch[i] = 1; } 
			if (area > max)
			{
				max = area;
				index = i;
			}
		}
	}
	if (index != -1)
	{
		Catch[index] = 1; //Store the index of the points
		Find_Max(a1, index);
		Find_Max(index, a2);//D&C
	}
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 1);
	glLineWidth(2.0);

	glPointSize(4.0);
	for (int i = 0; i < n; i++)
	{
		float x1 = p[i].x /800.0 - 0.5; float y1 = p[i].y /800.0 - 0.5;
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		glEnd();
	}
	glPointSize(6.0);
	glColor3f(0.5, 0.5, 0.3);
	glBegin(GL_POINTS);
	for (int i = 0; i <t; i++)
	{
		float x2 = ConvexHull[i].x/800.0 - 0.5; float y2 = ConvexHull[i].y/800.0 - 0.5;
		
		glVertex2f(x2, y2);
	}
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	std::cout << "Input the number of points :";
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		p[i].x = rand() % 1000;
		p[i].y = rand() % 1000;
		Catch[i] = 0;
	}
	stop_watch watch;
	watch.start();
	
	Catch[0] = 1;
	Catch[n - 1] = 1;
	sort(p, p + n, cmp);
	Find_Max(0, n - 1); 
	Find_Max(n - 1, 0); 
	
	for (int i = 0; i < n; i++)
	{
		if (Catch[i] == 1)
		{
			ConvexHull[t].x = p[i].x;
			ConvexHull[t].y = p[i].y;
			t++;
		}
	}

	watch.stop();
	cout << watch.elapsed() << " ns" << endl;
	
	//Output the points on convex hull
	mark[0] = mark[t - 1] = 1; 
	for (int i = 1; i < t - 1; i++)
	{
		mark[i] = 0;
	}
	cout << ConvexHull[0].x << " " << ConvexHull[0].y << endl;
	for (int i = 1; i < t - 1; i++)
	{
		int d = Get_Area(ConvexHull[0], ConvexHull[t - 1], ConvexHull[i]);
		if (d >= 0)
		{
			cout << ConvexHull[i].x << " " << ConvexHull[i].y << endl;
			mark[i] = 1;
		}
	}
	cout << ConvexHull[t - 1].x << " " << ConvexHull[t - 1].y << endl;
	for (int i = 1; i < t; i++)
	{
		if (mark[i] != 1)
		{
			int d = Get_Area(ConvexHull[0], ConvexHull[t - 1], ConvexHull[i]);
			if (d < 0)
			{
				cout << ConvexHull[i].x << " " << ConvexHull[i].y << endl;
			}
		}
	}
	

	glutInit(&argc, argv);//Draw the fig.
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Project 2 - Convex Hull");
	init();
	glutDisplayFunc(&Display);
	glutMainLoop();
	system("pause");
	return 0;
}