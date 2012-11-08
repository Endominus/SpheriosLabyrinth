#include <SFML\Graphics.hpp>
#include <gl\glut.h>

void transposeMatrix(double m[16],double output[16]) 
{
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

void vectorTransform(double transform[16],double input[4],double output[4]) {
		output[3] = transform[12]*input[0]+transform[13]*input[1]+transform[14]*input[2]+transform[15]*input[3];
		output[0] = (transform[0]*input[0]+transform[1]*input[1]+transform[2]*input[2]+transform[3]*input[3])/output[3];
		output[1] = (transform[4]*input[0]+transform[5]*input[1]+transform[6]*input[2]+transform[7]*input[3])/output[3];
		output[2] = (transform[8]*input[0]+transform[9]*input[1]+transform[10]*input[2]+transform[11]*input[3])/output[3];
		output[3] = 1;
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

	void subtractVectors(double vec[4], double vec2[4], double output[4]) 
	{
		output[0] = vec[0] - vec2[0];
		output[1] = vec[1] - vec2[1];
		output[2] = vec[2] - vec2[2];
		output[3] = 1;
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

class Sphere
{
private:
	Point3 center;
	double radius;
	double color[3];
	double velocity[3];
public:

	void getCenter( double * centerPos)
	{
		centerPos[0] = center.x;
		centerPos[1] = center.y;
		centerPos[2] = center.z;
	}

	void setCenter( Point3 newCenter )
	{
		center = newCenter;
	}

	void stopBall()
	{
		velocity[0] = velocity[1] = velocity[2] = 0;
	}

	Sphere(){}
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

	void testCollision(Block block) {
		double transpose[16];
		transposeMatrix(block.rotationMatrix,transpose);
		double blockCenter[4];blockCenter[0]=0;blockCenter[1]=0;blockCenter[2]=0;blockCenter[3]=1;
		double newCenter[4];
		vectorTransform(transpose,blockCenter,newCenter);
		double up[4];up[0]=0;up[1]=1;up[2]=0;up[3]=1;
		double newup[4];
		vectorTransform(transpose,up,newup);
		double dotp = (newup[0]-newCenter[0])*(center.x-newup[0])+(newup[1]-newCenter[1])*(center.y-newup[1])+(newup[2]-newCenter[2])*(center.z-newup[2]);
		if(dotp>0) {
			double upsize = std::sqrt((newup[0]-newCenter[0])*(newup[0]-newCenter[0])+(newup[1]-newCenter[1])*(newup[1]-newCenter[1])+(newup[2]-newCenter[2])*(newup[2]-newCenter[2]));
			double dist = dotp/upsize;
			if(dist<radius) {
				center.x = newup[0]+(center.x-newup[0])/dist*radius;
				center.y = newup[1]+(center.y-newup[1])/dist*radius;
				center.z = newup[2]+(center.z-newup[2])/dist*radius;
				dotp = (newup[0]-newCenter[0])*velocity[0]+(newup[1]-newCenter[1])*velocity[1]+(newup[2]-newCenter[2])*velocity[2];
				dotp/=upsize;
				velocity[0] = velocity[0]-(newup[0]-newCenter[0])/upsize*dotp;
				velocity[1] = velocity[1]-(newup[1]-newCenter[1])/upsize*dotp;
				velocity[2] = velocity[2]-(newup[2]-newCenter[2])/upsize*dotp;
			}
		}
		/*
		double quadric[16] = {1,0,0,-center.x,0,1,0,-center.y,0,0,1,-center.z,-center.x,-center.y,-center.z,center.x*center.x+center.y*center.y+center.z*center.z-radius*radius};
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		double inverse[16];
		gluInvertMatrix(block.rotationMatrix,inverse);
		double inverseTranspose[16];
		transposeMatrix(inverse,inverseTranspose);
		double oldCenter[4];
		oldCenter[0] = center.x;
		oldCenter[1] = center.y;
		oldCenter[2] = center.z;
		oldCenter[3] = 1;
		double newCenter[4];
		vectorTransform(inverseTranspose,oldCenter,newCenter);
		glMultMatrixd(transpose);
		glMultMatrixd(quadric);
		glMultMatrixd(block.rotationMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX,quadric);*/
	}

	void display() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(center.x,center.y,center.z);
		//glScaled(radius,radius,radius);
		glColor3dv(color);
		/*glBegin(GL_TRIANGLES);
			glVertex3d(0,0,1);
			glVertex3d(1,0,0);
			glVertex3d(0,1,0);
			glVertex3d(1,0,0);
			glVertex3d(0,0,-1);
			glVertex3d(0,1,0);
			glVertex3d(0,0,-1);
			glVertex3d(-1,0,0);
			glVertex3d(0,1,0);
			glVertex3d(-1,0,0);
			glVertex3d(0,0,1);
			glVertex3d(0,1,0);

			glVertex3d(0,0,1);
			glVertex3d(0,-1,0);
			glVertex3d(1,0,0);
			glVertex3d(1,0,0);
			glVertex3d(0,-1,0);
			glVertex3d(0,0,-1);
			glVertex3d(0,0,-1);
			glVertex3d(0,-1,0);
			glVertex3d(-1,0,0);
			glVertex3d(-1,0,0);
			glVertex3d(0,-1,0);
			glVertex3d(0,0,1);
		glEnd();*/
		glutSolidSphere(radius, 20, 20);
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
	bool forward;

public:

	MovingBlock(double *colors, double centerPoint[], double end[], double w, double h, double d, double theta, double phi, double timeTaken)
	{
		color[0] = colors[0];
		color[1] = colors[1];
		color[2] = colors[2];

		forward  = true;

		center = Point3(centerPoint[0], centerPoint[1], centerPoint[2]);
		deltaX = end[0] - centerPoint[0];
		deltaY = end[1] - centerPoint[1];
		deltaZ = end[2] - centerPoint[2];

		time = timeTaken;
		timeSoFar = 0;

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
		double xOffset = (deltaX*(elapsedTime-timeSoFar))/time;
		double yOffset = (deltaY*(elapsedTime-timeSoFar))/time;
		double zOffset = (deltaZ*(elapsedTime-timeSoFar))/time;
		if (abs(xOffset) > abs(deltaX) || abs(yOffset) > abs(deltaY) || abs(zOffset) > abs(deltaZ))
		{
			timeSoFar = elapsedTime;
			center.x += deltaX;
			center.y += deltaY;
			center.z += deltaZ;
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glTranslated(2*deltaX, 2*deltaY, 2*deltaZ);
			glMultMatrixd(rotationMatrix);
			glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
			glPopMatrix();
			//printf("%.2f %.2f %.2f\n", deltaX, deltaY, deltaZ);
			deltaX *= -1;
			deltaY *= -1;
			deltaZ *= -1;
			xOffset = 0;
			yOffset = 0;
			zOffset = 0;
			time = elapsedTime;
		}
		//double currentMatrix[16];
		//glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &currentMatrix);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();


		glColor3dv(color);

		//// Near face
		//glColor3d(1, 1, 1);
		//glBegin(GL_QUADS);
		//	glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
		//	glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
		//glEnd();

		//// Far face
		//
		//glColor3d(0.5, 0.5, 0.5);
		//glBegin(GL_QUADS);
		//	glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
		//	glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
		//	glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		//glEnd();

		//// Top face
		//glColor3d(1, 0, 0);
		//glBegin(GL_QUADS);
		//	glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
		//	glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		//glEnd();

		//// Bottom face
		//glColor3d(0, 1, 1);
		//glBegin(GL_QUADS);
		//	glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
		//	glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
		//glEnd();

		//// Right face
		//glColor3d(0, 1, 0);
		//glBegin(GL_QUADS);
		//	glVertex3d(1+xOffset, 1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(1+xOffset, -1+yOffset, 1+zOffset);
		//	glVertex3d(1+xOffset, 1+yOffset, 1+zOffset);
		//glEnd();

		//// Left face
		//glColor3d(1, 0, 1);
		//glBegin(GL_QUADS);
		//	glVertex3d(-1+xOffset, 1+yOffset, -1+zOffset);
		//	glVertex3d(-1+xOffset, -1+yOffset, -1+zOffset);
		//	glVertex3d(-1+xOffset, -1+yOffset, 1+zOffset);
		//	glVertex3d(-1+xOffset, 1+yOffset, 1+zOffset);
		//glEnd();
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
<<<<<<< .mine
};
=======
};
>>>>>>> .r30
