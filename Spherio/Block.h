#include <SFML\Graphics.hpp>

struct Point3{
	double x;
	double y;
	double z;

	Point3(double a, double b, double c) 
	{
		x = a;
		y = b;
		z = c;
	}

	Point3(){}
};

class Block 
{
private:
	Point3 center;
	double width;
	double height;
	double depth;
	double rotationMatrix[16];
	double color[3];

	
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

	Block(double *colors, double a1[], double w, double h, double d, double *rot) {
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(a1[0], a1[1], a1[2]);
		width = w;
		height = h;
		depth = d;

		int i, j;
		for (i = 0; i<16; i++)
		{
			rotationMatrix[i] = rot[i];
		}

	}

	Block(double *colors, double a1[], double w, double h, double d, double theta, double phi) {
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(a1[0], a1[1], a1[2]);
		width = w;
		height = h;
		depth = d;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotated(phi, 0, 0, 1);
		glRotated(theta, 0, 1, 0);
		glGetFloatv(GL_MODELVIEW, (GLfloat*) rotationMatrix); //may be a flaw

	}


	//Deprecated
	void display() 
	{
		glColor3dv(color);
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
		printf("Point: [%f, %f, %f]", p1.x, p1.y, p1.z);
	}
};