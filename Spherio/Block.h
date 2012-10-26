#include <SFML\Graphics.hpp>

typedef struct {
	float x;
	float y;
	float z;
} Point3;

class Block 
{
private:
	Point3 p1;
	Point3 p2;
	bool horizontal;
	int width;

public:
	Block(){}

	Block(int x1, int y1, int z1, int x2, int y2, int z2, int thickness) {
		p1.x = x1;
		p1.y = y1;
		p1.z = z1;
		p2.x = x2;
		p2.y = y2;
		p2.z = z2;
		width = thickness;

		if (x1 == x2)
			horizontal = false;
		else
			horizontal = true;
	}

	void display() {
		if (horizontal)
		{
			glBegin(GL_POLYGON);
			//1
			glVertex3d(p1.x-width, p1.y-width, p1.z-width);
			glVertex3d(p1.x-width, p1.y+width, p1.z-width);
			glVertex3d(p1.x-width, p1.y-width, p1.z+width);
			glVertex3d(p1.x-width, p1.y+width, p1.z+width);
			//5
			glVertex3d(p2.x+width, p2.y+width, p2.z+width);
			glVertex3d(p1.x-width, p1.y+width, p1.z-width);
			glVertex3d(p2.x+width, p2.y+width, p2.z-width);
			glVertex3d(p1.x-width, p1.y-width, p1.z-width);
			glVertex3d(p2.x+width, p2.y-width, p2.z-width);
			//10
			glVertex3d(p2.x+width, p2.y-width, p2.z+width);
			glVertex3d(p2.x+width, p2.y+width, p2.z-width);
			glVertex3d(p2.x+width, p2.y+width, p2.z+width);
			glVertex3d(p2.x+width, p2.y-width, p2.z+width);
			glVertex3d(p1.x-width, p1.y-width, p1.z+width);
			glVertex3d(p1.x-width, p1.y-width, p1.z-width);
			glEnd();
		}
		else
		{
			glBegin(GL_POLYGON);
			glVertex3d(p1.x+width, p1.y-width, p1.z-width);
			glVertex3d(p1.x-width, p1.y-width, p1.z-width);
			glVertex3d(p1.x+width, p1.y-width, p1.z+width);
			glVertex3d(p1.x-width, p1.y-width, p1.z+width);
			//5
			glVertex3d(p2.x-width, p2.y+width, p2.z+width);
			glVertex3d(p1.x-width, p1.y-width, p1.z-width);
			glVertex3d(p2.x-width, p2.y+width, p2.z-width);
			glVertex3d(p1.x+width, p1.y-width, p1.z-width);
			glVertex3d(p2.x+width, p2.y+width, p2.z-width);
			//10
			glVertex3d(p2.x+width, p2.y+width, p2.z+width);
			glVertex3d(p2.x-width, p2.y+width, p2.z-width);
			glVertex3d(p2.x-width, p2.y+width, p2.z+width);
			glVertex3d(p2.x+width, p2.y+width, p2.z+width);
			glVertex3d(p1.x+width, p1.y-width, p1.z+width);
			glVertex3d(p1.x+width, p1.y-width, p1.z-width);
			glEnd();
		}
	}
};