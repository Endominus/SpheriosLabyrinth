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

	void displayFaceVertex(int x, int y, int z) {
		double halfWidth = width / 2.0;
		double halfHeight = height / 2.0;
		double halfDepth = depth / 2.0;
		glVertex3d(center.x + x*halfWidth, center.y + y*halfHeight, center.z + z*halfDepth);
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

		int i;
		for (i = 0; i<16; i++)
		{
			rotationMatrix[i] = rot[i];
		}

	}

	/* centerPoint = center of near plane of block
	 * w = width of block
	 * h = height of block
	 * d = depth of block
	 * theta = amount of rotation around the y axis
	 * phi = amount of rotation around the z axis
	 */
	Block(double *colors, double centerPoint[], double w, double h, double d, double theta, double phi) {
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(centerPoint[0], centerPoint[1], centerPoint[2]);
		width = w;
		height = h;
		depth = d;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glRotated(phi, 0, 0, 1);
		glRotated(theta, 0, 1, 0);
		glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
		glPopMatrix();
	}


	void display() 
	{
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glPushMatrix();

		glTranslated(center.x, center.y, center.z);
		glMultMatrixd(rotationMatrix);
		glTranslated(-center.x, -center.y, -center.z);

		glColor3dv(color);

		double halfWidth = width / 2.0;
		double halfHeight = height / 2.0;
		double halfDepth = depth / 2.0;
		// Near face
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(-1, 1, -1);
		glEnd();

		// Far face
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();

		// Top face
		glBegin(GL_QUADS);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();

		// Bottom face
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(-1, -1, 1);
		glEnd();

		// Right face
		glBegin(GL_QUADS);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);
		glEnd();

		// Left face
		glBegin(GL_QUADS);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();

		glPopMatrix();
	}
};