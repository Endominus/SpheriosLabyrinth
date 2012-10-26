#include <SFML\Graphics.hpp>

typedef struct {
	double x;
	double y;
	double z;
} Point3;

class Block 
{
private:
	Point3 p1;
	Point3 p2;
	Point3 p3;
	Point3 p4;
	Point3 p5;
	Point3 p6;
	Point3 p7;
	Point3 p8;
	bool horizontal;
	int width1;
	int width2;

	
	void getVert(Point3 p) {
		glVertex3d(p.x, p.y, p.z);
	}

	void setPoint(Point3 p, int a[3])
	{
		p.x = a[0];
		p.y = a[1];
		p.z = a[2];
	}

public:
	Block(){}

	Block(double a1[], double a2[], int thickness1, int thickness2 = -1) {
		width1 = thickness1;
		if (thickness2 == -1)
			width2 = width1;
		else
			width2 = thickness2;

		if (a1[0] == a2[0])
		{
			horizontal = false;
			Point3 temp = {a1[0]+width1, a1[1]-width1, a1[2]-width1};
			p1 = temp;
			Point3 temp1 = {a1[0]-width1, a1[1]-width1, a1[2]-width1};
			p2 = temp1;
			Point3 temp2 = {a1[0]+width1, a1[1]-width1, a1[2]+width1};
			p3 = temp2;
			Point3 temp3 = {a1[0]-width1, a1[1]-width1, a1[2]+width1};
			p4 = temp3;
			Point3 temp4 = {a2[0]+width2, a2[1]+width2, a2[2]-width2};
			p5 = temp4;
			Point3 temp5 = {a2[0]-width2, a2[1]+width2, a2[2]-width2};
			p6 = temp5;
			Point3 temp6 = {a2[0]+width2, a2[1]+width2, a2[2]+width2};
			p7 = temp6;
			Point3 temp7 = {a2[0]-width2, a2[1]+width2, a2[2]+width2};
			p8 = temp7;
		}
		else
		{
			horizontal = true;
			Point3 p1 = {a1[0]-width1, a1[1]-width1, a1[2]-width1};
			Point3 p2 = {a1[0]-width1, a1[1]+width1, a1[2]-width1};
			Point3 p3 = {a1[0]-width1, a1[1]-width1, a1[2]+width1};
			Point3 p4 = {a1[0]-width1, a1[1]+width1, a1[2]+width1};
			Point3 p5 = {a2[0]+width2, a2[1]-width2, a2[2]-width2};
			Point3 p6 = {a2[0]+width2, a2[1]+width2, a2[2]-width2};
			Point3 p7 = {a2[0]+width2, a2[1]-width2, a2[2]+width2};
			Point3 p8 = {a2[0]+width2, a2[1]+width2, a2[2]+width2};
		}
	}

	Block (int a[8][3])
	{
		setPoint(p1, a[0]);
		setPoint(p2, a[1]);
		setPoint(p3, a[2]);
		setPoint(p4, a[3]);
		setPoint(p5, a[4]);
		setPoint(p6, a[5]);
		setPoint(p7, a[6]);
		setPoint(p8, a[7]);
	}

	void display() 
	{
		//printf("Here");
		glBegin(GL_POLYGON);
		getVert(p1);
		getVert(p2);
		getVert(p3);
		getVert(p4);
		getVert(p8);
		getVert(p2);
		getVert(p6);
		getVert(p1);
		getVert(p5);
		getVert(p7);
		getVert(p6);
		getVert(p8);
		getVert(p7);
		getVert(p3);
		getVert(p1);
		glEnd();

		/*glBegin(GL_TRIANGLES);
		glVertex3d(p3.x, p3.y, p3.z);
		glVertex3d(p4.x, p4.y, p4.z);
		glVertex3d(p8.x, p8.y, p8.z);
		//getVert(p3);
		//getVert(p4);
		//getVert(p8);
		glEnd();*/
		/*
		glBegin(GL_TRIANGLES);
		glVertex3d(0, 20, -10);
		glVertex3d(0, 0, -10);
		glVertex3d(10, 0, -10);
		glEnd();
		*/
		
	}

	void toString()
	{
		printf("Point: [%d, %d, %d]", p1.x, p2.y, p3.z);
		Point3 p;
		p.x = 0;
		p.y = 1;
		p.z = 2;
		printf("Point: [%d, %d, %d]", p.x, p.y, p.z);
	}
};