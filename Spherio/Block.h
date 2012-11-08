#include <SFML\Graphics.hpp>
#include <gl\glut.h>


class Block;
class MovingBlock;
class Sphere;

void subtractVectors(double vec[4], double vec2[4], double output[4]) 
{
	output[0] = vec[0] - vec2[0];
	output[1] = vec[1] - vec2[1];
	output[2] = vec[2] - vec2[2];
	output[3] = 1;
}

double dotProduct(double vec[4],double vec2[4])
{
	return vec[0]*vec2[0]+vec[1]*vec2[1]+vec[2]*vec2[2];
}
double dotProduct(double vec[4],double x,double y,double z)
{
	return vec[0]*x+vec[1]*y+vec[2]*z;
}

void transposeMatrix(double m[16],double output[16]) {
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			output[i*4+j]=m[j*4+i];
}
bool gluInvertMatrix(const double m[16], double invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}
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
struct Point4{
	double x;
	double y;
	double z;
	double w;

	Point4(double a, double b, double c,double d) 
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	Point4(){}
};

void vectorTransform(double transform[16],double input[4],double output[4]) {
	double w = transform[12]*input[0]+transform[13]*input[1]+transform[14]*input[2]+transform[15]*input[3];
	double x = (transform[0]*input[0]+transform[1]*input[1]+transform[2]*input[2]+transform[3]*input[3])/w;
	double y = (transform[4]*input[0]+transform[5]*input[1]+transform[6]*input[2]+transform[7]*input[3])/w;
	double z = (transform[8]*input[0]+transform[9]*input[1]+transform[10]*input[2]+transform[11]*input[3])/w;
	output[0] = x;
	output[1] = y;
	output[2] = z;
	output[3] = 1;
	}

Point4 vectorTransform(double transform[16],Point4 input) {
	double w = transform[12]*input.x+transform[13]*input.y+transform[14]*input.z+transform[15]*input.w;
	double x = (transform[0]*input.x+transform[1]*input.y+transform[2]*input.z+transform[3]*input.w)/w;
	double y = (transform[4]*input.x+transform[5]*input.y+transform[6]*input.z+transform[7]*input.w)/w;
	double z = (transform[8]*input.x+transform[9]*input.y+transform[10]*input.z+transform[11]*input.w)/w;
	return Point4(x,y,z,1);
}

class Block 
{
protected:
	Point3 center;
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
	double rotationMatrix[16];
	Block(){}

	Block(double *colors, double a1[], double *rot) {
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(a1[0], a1[1], a1[2]);

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

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslated(centerPoint[0], centerPoint[1], centerPoint[2]);
		glRotated(theta, 0, 1, 0);
		glRotated(-phi, 0, 0, 1);
		glScaled(w/2, h/2, d/2);
		glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
		glPopMatrix();
	}


	void display() 
	{
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		//glMultMatrixd(rotationMatrix);

		glColor3dv(color);
		//glColor3d(1,1,1);

//		glColor3d(1, 1, 1);
		/*glBegin(GL_QUADS);
			// Far face
			glNormal3d(0,0,-1);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(-1, 1, -1);
		
//		glColor3d(0.5, 0.5, 0.5);
			// Near face
			glNormal3d(0,0,1);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);

//		glColor3d(1, 0, 0);
			// Top face
			glNormal3d(0,1,0);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, 1, 1);
			displayFaceVertex(-1, 1, 1);

//		glColor3d(0, 1, 1);
			// Bottom face
			glNormal3d(0,-1,0);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(-1, -1, 1);

//		glColor3d(0, 1, 0);
			// Right face
			glNormal3d(1,0,0);
			displayFaceVertex(1, 1, -1);
			displayFaceVertex(1, -1, -1);
			displayFaceVertex(1, -1, 1);
			displayFaceVertex(1, 1, 1);

//		glColor3d(1, 0, 1);
			// Left face
			glNormal3d(-1,0,0);
			displayFaceVertex(-1, 1, -1);
			displayFaceVertex(-1, -1, -1);
			displayFaceVertex(-1, -1, 1);
			displayFaceVertex(-1, 1, 1);
		glEnd();
		double d = 0.001;
		glColor3d(1,1,1);
		glBegin(GL_LINES);
			glVertex3d(1+d,1+d,1+d);
			glVertex3d(1+d,1+d,-1-d);
			glVertex3d(1+d,1+d,-1-d);
			glVertex3d(-1-d,1+d,-1-d);
			glVertex3d(-1-d,1+d,-1-d);
			glVertex3d(-1-d,1+d,1+d);
			glVertex3d(-1-d,1+d,1+d);
			glVertex3d(1+d,1+d,1+d);

			glVertex3d(1+d,-1-d,1+d);
			glVertex3d(1+d,-1-d,-1-d);
			glVertex3d(1+d,-1-d,-1-d);
			glVertex3d(-1-d,-1-d,-1-d);
			glVertex3d(-1-d,-1-d,-1-d);
			glVertex3d(-1-d,-1-d,1+d);
			glVertex3d(-1-d,-1-d,1+d);
			glVertex3d(1+d,-1-d,1+d);

			glVertex3d(1+d,-1-d,1+d);
			glVertex3d(1+d,1+d,1+d);
			glVertex3d(1+d,-1-d,-1-d);
			glVertex3d(1+d,1+d,-1-d);
			glVertex3d(-1-d,-1-d,-1-d);
			glVertex3d(-1-d,1+d,-1-d);
			glVertex3d(-1-d,-1-d,1+d);
			glVertex3d(-1-d,1+d,1+d);
		glEnd();*/
		double corners[15][4] = {{-1,1,1,1},{1,1,1,1},{-1,-1,1,1},{1,-1,1,1},{-1,1,-1,1},{1,1,-1,1},{-1,-1,-1,1},{1,-1,-1,1},{0,0,1,1},{0,0,-1,1},{0,1,0,1},{0,-1,0,1},{-1,0,0,1},{1,0,0,1},{0,0,0,1}};
		double transformedCorners[15][4];
		double transpose[16];
		transposeMatrix(rotationMatrix, transpose);

		for(int i=0;i<15;i++)
			vectorTransform(transpose, corners[i], transformedCorners[i]);

		for (int j = 8; j < 14; j++)
		{
			subtractVectors(corners[j], corners[14], corners[j]);
		}

		glBegin(GL_QUADS);
			glNormal3dv(corners[8]);
			glVertex3dv(transformedCorners[0]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[3]);
			glVertex3dv(transformedCorners[2]);
			
			glNormal3dv(corners[9]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[6]);
			glVertex3dv(transformedCorners[7]);
			
			glNormal3dv(corners[10]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[0]);
			
			glNormal3dv(corners[11]);
			glVertex3dv(transformedCorners[2]);
			glVertex3dv(transformedCorners[3]);
			glVertex3dv(transformedCorners[7]);
			glVertex3dv(transformedCorners[6]);
			
			glNormal3dv(corners[12]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[0]);
			glVertex3dv(transformedCorners[2]);
			glVertex3dv(transformedCorners[6]);
			
			glNormal3dv(corners[13]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[7]);
			glVertex3dv(transformedCorners[3]);
		glEnd();
		glPopMatrix();
	}
};

class MovingBlock : public Block {
private:
	double time;
	double timeSoFar;
	double deltaX;
	double deltaY;
	double deltaZ;

public:
	double xOffset;
	double yOffset;
	double zOffset;

	MovingBlock(double *colors, double centerPoint[], double end[], double w, double h, double d, double theta, double phi, double timeTaken)
	{
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		center = Point3(centerPoint[0], centerPoint[1], centerPoint[2]);
		deltaX = (end[0] - centerPoint[0])*2;
		deltaY = (end[1] - centerPoint[1])*2;
		deltaZ = (end[2] - centerPoint[2])*2;

		xOffset = 0;
		yOffset = 0;
		zOffset = 0;

		time = timeTaken;
		timeSoFar = 0;

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		//glTranslated(centerPoint[0], centerPoint[1], centerPoint[2]);
		//glRotated(theta, 0, 1, 0);
		//glRotated(phi, 0, 0, 1);
		//glScaled(w, h, d);

		glTranslated(centerPoint[0], centerPoint[1], centerPoint[2]);
		glRotated(theta, 0, 1, 0);
		glRotated(-phi, 0, 0, 1);
		glScaled(w/2, h/2, d/2);

		glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
		glPopMatrix();
	}

	void display(double elapsedTime)
	{

		double xOffset = deltaX*(elapsedTime-timeSoFar)/time;
		double yOffset = deltaY*(elapsedTime-timeSoFar)/time;
		double zOffset = deltaZ*(elapsedTime-timeSoFar)/time;
		if ( elapsedTime-timeSoFar > time )

		{
			timeSoFar = elapsedTime;
			center.x += deltaX; // This does nothing - have to change the transformation matrix.
			center.y += deltaY;
			center.z += deltaZ;
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			glMultMatrixd(rotationMatrix);
			glTranslated(deltaX, deltaY, deltaZ);

			glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
			glPopMatrix();
			//printf("%.2f %.2f %.2f\n", deltaX, deltaY, deltaZ);

			deltaX *= -1;
			deltaY *= -1;
			deltaZ *= -1;
			xOffset = 0;
			yOffset = 0;
			zOffset = 0;
		}
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		
		//glLoadIdentity();
		//glMultMatrixd(rotationMatrix);

		glColor3dv(color);

		double corners[15][4] = {{-1,1,1,1},{1,1,1,1},{-1,-1,1,1},{1,-1,1,1},{-1,1,-1,1},{1,1,-1,1},{-1,-1,-1,1},{1,-1,-1,1},{0,0,1,1},{0,0,-1,1},{0,1,0,1},{0,-1,0,1},{-1,0,0,1},{1,0,0,1},{0,0,0,1}};
		double transformedCorners[15][4];
		double transpose[16];
		transposeMatrix(rotationMatrix, transpose);

		for(int i=0;i<15;i++)
		{
			corners[i][0] += xOffset;
			corners[i][1] += yOffset;
			corners[i][2] += zOffset;
			vectorTransform(transpose, corners[i], transformedCorners[i]);
		}

		for (int j = 8; j < 14; j++)
		{
			subtractVectors(corners[j], corners[14], corners[j]);
		}

		glBegin(GL_QUADS);
			glNormal3dv(corners[8]);
			glVertex3dv(transformedCorners[0]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[3]);
			glVertex3dv(transformedCorners[2]);
			
			glNormal3dv(corners[9]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[6]);
			glVertex3dv(transformedCorners[7]);
			
			glNormal3dv(corners[10]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[0]);
			
			glNormal3dv(corners[11]);
			glVertex3dv(transformedCorners[2]);
			glVertex3dv(transformedCorners[3]);
			glVertex3dv(transformedCorners[7]);
			glVertex3dv(transformedCorners[6]);
			
			glNormal3dv(corners[12]);
			glVertex3dv(transformedCorners[4]);
			glVertex3dv(transformedCorners[0]);
			glVertex3dv(transformedCorners[2]);
			glVertex3dv(transformedCorners[6]);
			
			glNormal3dv(corners[13]);
			glVertex3dv(transformedCorners[1]);
			glVertex3dv(transformedCorners[5]);
			glVertex3dv(transformedCorners[7]);
			glVertex3dv(transformedCorners[3]);
		glEnd();
		glPopMatrix();

	}
};

class Sphere
{
private:
	Point3 center;
	double radius;
	double color[3];
	double velocity[3];
public:

	void getCenter(double * point)
	{
		point[0] = center.x;
		point[1] =center.y;
		point[2] = center.z;
	}

	void setCenter( Point3 newCenter )
	{
		center = newCenter;
	}

	void stopBall()
	{
		velocity[0] = velocity[1] = velocity[2] = 0;
	}	Sphere(){}

	Sphere(double *colors, double c[3],double r) {
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];
		center = Point3(c[0],c[1],c[2]);
		radius = r;
		velocity[0] = velocity[1] = velocity[2] = 0;
	}

	void accelerate(double xaccel,double yaccel,double zaccel) {
		velocity[0]+=xaccel;
		velocity[1]+=yaccel;
		velocity[2]+=zaccel;
		center.x+=velocity[0];
		center.y+=velocity[1];
		center.z+=velocity[2];
	}

	

/*	double evaluateQuadric(double quadric[16],double x,double y,double z){
		return quadric[0]*x*x+(quadric[1]+quadric[4])*x*y+(quadric[2]+quadric[8])*x*z+(quadric[3]+quadric[12])*x+quadric[5]*y*y+(quadric[6]+quadric[9])*y*z+(quadric[7]+quadric[13])*y+quadric[10]*z*z+(quadric[11]+quadric[14])*z+quadric[15];
	}

	void collideCorner(double quadric[16],double x,double y,double z,double newCenter[4]) {
		if(evaluateQuadric(quadric,x,y,z)<0) {
			double dir[4];
			dir[0] = x-newCenter[0];
			dir[1] = y-newCenter[1];
			dir[2] = z-newCenter[2];
			dir[3] = 1;
			double dist = std::sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
			
		}
	}

	void collideEdge(double quadric[16],double x,double y,double z) {

	}

	#define faceThreshold 0.01
	void collideFace(double quadric[16],double x,double y,double z,double newCenter[4]) {
		if(y!=0) {
			z = ((quadric[3]+quadric[12])*(quadric[2]+quadric[8])-2*(quadric[0])*(quadric[11]+quadric[14]))/(4*(quadric[0])*(quadric[10])-(quadric[2]+quadric[8])*(quadric[2]+quadric[8]));
			x = (-(quadric[11]+quadric[14])-2*(quadric[10])*z)/(quadric[2]+quadric[8]);
			r = 
		} else if(x!=0) {
		} else if(z!=0) {
		}
	}*/
	int getIndexFromDir(int direction) {
		switch(direction) {
			//corner
		case 21:
			return 0;
		case 22:
			return 4;
		case 25:
			return 2;
		case 26:
			return 6;
		case 37:
			return 1;
		case 38:
			return 5;
		case 41:
			return 3;
		case 42:
			return 7;

			//face
		case 1:
			return 0;
		case 2:
			return 1;
		case 4:
			return 2;
		case 8:
			return 3;
		case 16:
			return 4;
		case 32:
			return 5;

			//edge
		case 5:
			return 0*8+1;
		case 6:
			return 4*8+5;
		case 9:
			return 2*8+3;
		case 10:
			return 6*8+7;
		case 17:
			return 0*8+2;
		case 18:
			return 4*8+6;
		case 33:
			return 1*8+3;
		case 34:
			return 5*8+7;
		case 20:
			return 0*8+4;
		case 24:
			return 2*8+6;
		case 36:
			return 1*8+5;
		case 40:
			return 3*8+7;
		default:
			printf("Invalid direction: %d",direction);
			return 0;
		}
	}
	//int getEdgesFromDir(int direction) {
	//	switch(direction) {
	//	}
	//}

	void testCollision(Block block) {
		double corners[15][4] = {{-1,1,1,1},{1,1,1,1},{-1,-1,1,1},{1,-1,1,1},{-1,1,-1,1},{1,1,-1,1},{-1,-1,-1,1},{1,-1,-1,1},            {0,0,1,1},{0,0,-1,1},    {0,1,0,1},{0,-1,0,1},    {-1,0,0,1},{1,0,0,1},{0,0,0,1}};
		double normals[6][4];
		double transpose[16];
		transposeMatrix(block.rotationMatrix, transpose);

		for(int i=0;i<15;i++)
			vectorTransform(transpose, corners[i], corners[i]);
		for (int j = 0; j < 6; j++)
		{
			subtractVectors(corners[j+8], corners[14], normals[j]);
			double size = std::sqrt(dotProduct(normals[j],normals[j]));
			normals[j][0]/=size;
			normals[j][1]/=size;
			normals[j][2]/=size;
		}
		double dists[6];
		double totalDist = 0;
		int count = 0;int direction = 0;
		for(int i=0;i<6;i++) {
			dists[i] = dotProduct(normals[i],center.x-corners[i+8][0],center.y-corners[i+8][1],center.z-corners[i+8][2]);
			if(dists[i]>0) {
				count++;
				direction+=1<<i;
				totalDist+=dists[i]*dists[i];
			}
		}
		totalDist = std::sqrt(totalDist);
		//printf("Distance: %.2f \tRadius: %.2f \tCount: %d \tDirection: %d \tCenterY: %.2f\n",totalDist,radius,count,direction,center.y);
		if(totalDist>radius)
			return;
		if(count==3) {
			int corner = getIndexFromDir(direction);
			double pos[4] = {center.x,center.y,center.z,1};
			double r[4];
			subtractVectors(pos,corners[corner],r);
			center.x = corners[corner][0]+r[0]/totalDist*radius;
			center.y = corners[corner][1]+r[1]/totalDist*radius;
			center.z = corners[corner][2]+r[2]/totalDist*radius;
			double vel = dotProduct(velocity,r);
			vel/=totalDist;
			velocity[0]-=r[0]/totalDist*vel;
			velocity[1]-=r[1]/totalDist*vel;
			velocity[2]-=r[2]/totalDist*vel;
		} else if(count == 2) {
			int edge = getIndexFromDir(direction);
			int vertex1 = edge/8;
			int vertex2 = edge%8;
			double pos[4] = {center.x,center.y,center.z,1};
			double r[4];
			subtractVectors(pos,corners[vertex1],r);
			double edgeVector[4];
			subtractVectors(corners[vertex2],corners[vertex1],edgeVector);
			double edgeSize = std::sqrt(dotProduct(edgeVector,edgeVector));
			edgeVector[0]/=edgeSize;edgeVector[1]/=edgeSize;edgeVector[2]/=edgeSize;
			double edgeDist = dotProduct(edgeVector,r);
			r[0]-=edgeVector[0]*edgeDist;
			r[1]-=edgeVector[1]*edgeDist;
			r[2]-=edgeVector[2]*edgeDist;
			center.x+=r[0]*(radius-totalDist);
			center.y+=r[1]*(radius-totalDist);
			center.z+=r[2]*(radius-totalDist);
			double vel = dotProduct(velocity,r);
			vel/=totalDist;
			velocity[0]-=r[0]/totalDist*vel;
			velocity[1]-=r[1]/totalDist*vel;
			velocity[2]-=r[2]/totalDist*vel;
		} else if(count == 1) {
			int face = getIndexFromDir(direction);
			center.x+=normals[face][0]*(radius-totalDist);
			center.y+=normals[face][1]*(radius-totalDist);
			center.z+=normals[face][2]*(radius-totalDist);
			double vel = dotProduct(velocity,normals[face]);
			velocity[0]-=normals[face][0]*vel;
			velocity[1]-=normals[face][1]*vel;
			velocity[2]-=normals[face][2]*vel;
		}
	}

	void testCollisionMoving(MovingBlock block) {
		double corners[15][4] = {{-1,1,1,1},{1,1,1,1},{-1,-1,1,1},{1,-1,1,1},{-1,1,-1,1},{1,1,-1,1},{-1,-1,-1,1},{1,-1,-1,1},            {0,0,1,1},{0,0,-1,1},    {0,1,0,1},{0,-1,0,1},    {-1,0,0,1},{1,0,0,1},{0,0,0,1}};
		double normals[6][4];
		double transpose[16];
		//moving
		transposeMatrix(block.rotationMatrix, transpose);
		double transformedCorners[15][4];
		for(int i=0;i<15;i++)
		{
			corners[i][0] += block.xOffset;
			corners[i][1] += block.yOffset;
			corners[i][2] += block.zOffset;
			vectorTransform(transpose, corners[i], transformedCorners[i]);
		}

		for(int i=0;i<15;i++)
			vectorTransform(transpose, transformedCorners[i], transformedCorners[i]);
		for (int j = 0; j < 6; j++)
		{
			subtractVectors(corners[j+8], corners[14], normals[j]);
			double size = std::sqrt(dotProduct(normals[j],normals[j]));
			normals[j][0]/=size;
			normals[j][1]/=size;
			normals[j][2]/=size;
		}
		double dists[6];
		double totalDist = 0;
		int count = 0;int direction = 0;
		for(int i=0;i<6;i++) {
			dists[i] = dotProduct(normals[i],center.x-transformedCorners[i+8][0],center.y-transformedCorners[i+8][1],center.z-transformedCorners[i+8][2]);
			if(dists[i]>0) {
				count++;
				direction+=1<<i;
				totalDist+=dists[i]*dists[i];
			}
		}
		totalDist = std::sqrt(totalDist);
		//printf("Distance: %.2f \tRadius: %.2f \tCount: %d \tDirection: %d \tCenterY: %.2f\n",totalDist,radius,count,direction,center.y);
		if(totalDist>radius)
			return;
		if(count==3) {
			int corner = getIndexFromDir(direction);
			double pos[4] = {center.x,center.y,center.z,1};
			double r[4];
			subtractVectors(pos,transformedCorners[corner],r);
			center.x = transformedCorners[corner][0]+r[0]/totalDist*radius;
			center.y = transformedCorners[corner][1]+r[1]/totalDist*radius;
			center.z = transformedCorners[corner][2]+r[2]/totalDist*radius;
			double vel = dotProduct(velocity,r);
			vel/=totalDist;
			velocity[0]-=r[0]/totalDist*vel;
			velocity[1]-=r[1]/totalDist*vel;
			velocity[2]-=r[2]/totalDist*vel;
		} else if(count == 2) {
			int edge = getIndexFromDir(direction);
			int vertex1 = edge/8;
			int vertex2 = edge%8;
			double pos[4] = {center.x,center.y,center.z,1};
			double r[4];
			subtractVectors(pos,transformedCorners[vertex1],r);
			double edgeVector[4];
			subtractVectors(transformedCorners[vertex2],transformedCorners[vertex1],edgeVector);
			double edgeSize = std::sqrt(dotProduct(edgeVector,edgeVector));
			edgeVector[0]/=edgeSize;edgeVector[1]/=edgeSize;edgeVector[2]/=edgeSize;
			double edgeDist = dotProduct(edgeVector,r);
			r[0]-=edgeVector[0]*edgeDist;
			r[1]-=edgeVector[1]*edgeDist;
			r[2]-=edgeVector[2]*edgeDist;
			center.x+=r[0]*(radius-totalDist);
			center.y+=r[1]*(radius-totalDist);
			center.z+=r[2]*(radius-totalDist);
			double vel = dotProduct(velocity,r);
			vel/=totalDist;
			velocity[0]-=r[0]/totalDist*vel;
			velocity[1]-=r[1]/totalDist*vel;
			velocity[2]-=r[2]/totalDist*vel;
		} else if(count == 1) {
			int face = getIndexFromDir(direction);
			center.x+=normals[face][0]*(radius-totalDist);
			center.y+=normals[face][1]*(radius-totalDist);
			center.z+=normals[face][2]*(radius-totalDist);
			double vel = dotProduct(velocity,normals[face]);
			velocity[0]-=normals[face][0]*vel;
			velocity[1]-=normals[face][1]*vel;
			velocity[2]-=normals[face][2]*vel;
		}
	}

	void display() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(center.x,center.y,center.z);
		//glScaled(radius,radius,radius);
		glColor3dv(color);
		glutSolidSphere(radius, 40, 40);
		glPopMatrix();
	}
};

