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
protected:
	Point3 center;
	double width;
	double height;
	double depth;
	double rotationMatrix[16];
	double color[3];

	void displayFaceVertex(int x, int y, int z) {
		glVertex3d(x, y, z);
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
		glTranslated(centerPoint[0], centerPoint[1], centerPoint[2]);
		glRotated(theta, 0, 1, 0);
		glRotated(phi, 0, 0, 1);
		glScaled(w, h, d);
		glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
		glPopMatrix();
	}


	void display() 
	{
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		//glLoadIdentity();
		glMultMatrixd(rotationMatrix);

		glColor3dv(color);

		// Near face
		glColor3d(1, 1, 1);
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(-1, 1, -1);
		glEnd();

		// Far face
		
		glColor3d(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();

		// Top face
		glColor3d(1, 0, 0);
		glBegin(GL_QUADS);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();

		// Bottom face
		glColor3d(0, 1, 1);
		glBegin(GL_QUADS);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(-1, -1, 1);
		glEnd();

		// Right face
		glColor3d(0, 1, 0);
		glBegin(GL_QUADS);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);
		glEnd();

		// Left face
		glColor3d(1, 0, 1);
		glBegin(GL_QUADS);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();
		
		glPopMatrix();
	}
};

class MovingBlock : public Block {
private:
	double time;
	double deltaX;
	double deltaY;
	double deltaZ;

public:

	MovingBlock(double *colors, double centerPoint[], double end[], double w, double h, double d, double theta, double phi, double timeTaken)
	{
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(centerPoint[0], centerPoint[1], centerPoint[2]);
		width = w;
		height = h;
		depth = d;

		deltaX = end[0] - centerPoint[0];
		deltaY = end[1] - centerPoint[1];
		deltaZ = end[2] - centerPoint[2];

		time = timeTaken;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslated(centerPoint[0], centerPoint[1], centerPoint[2]);
		glRotated(theta, 0, 1, 0);
		glRotated(phi, 0, 0, 1);
		glScaled(w, h, d);
		glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
		glPopMatrix();
	}

	void display(double elapsedTime)
	{

		double xOffset = (deltaX*elapsedTime)/time;
		if (abs(xOffset) > abs(deltaX))
		{
			center.x += deltaX; // This does nothing - have to change the transformation matrix.
			center.y += deltaY;
			center.z += deltaZ;
			deltaX *= -1;
			deltaY *= -1;
			deltaZ *= -1;
			xOffset = (deltaX*elapsedTime)/time;
		}
		double yOffset = (deltaY*elapsedTime)/time;
		double zOffset = (deltaZ*elapsedTime)/time;
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		//glLoadIdentity();
		glMultMatrixd(rotationMatrix);

		glColor3dv(color);

		// Near face
		glColor3d(1, 1, 1);
		glBegin(GL_QUADS);
			glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
			glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
		glEnd();

		// Far face
		
		glColor3d(0.5, 0.5, 0.5);
		glBegin(GL_QUADS);
			glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
			glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
			glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		glEnd();

		// Top face
		glColor3d(1, 0, 0);
		glBegin(GL_QUADS);
			glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
			glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		glEnd();

		// Bottom face
		glColor3d(0, 1, 1);
		glBegin(GL_QUADS);
			glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
			glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
		glEnd();

		// Right face
		glColor3d(0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
			glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
		glEnd();

		// Left face
		glColor3d(1, 0, 1);
		glBegin(GL_QUADS);
			glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
			glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
			glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
			glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		glEnd();
		
		glPopMatrix();

	}
};