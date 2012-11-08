
#include <stdlib.h>
#include "Block.h"

double * vectorSub(double a[], double b[]) 
{
	double ret[] = {a[0]-b[0], a[1] - b[1], a[2] - b[2]};
	return ret;
}

class Level {
private:
	Block *pb;
	int numBlocks;
	int currentBlock;
	MovingBlock *pmb;
	int numMovingBlocks;
	int currentMovingBlock;
	double startCameraPhi;
	double startCameraTheta;

	Point3 startPoint;
	Point3 endPos;
	Sphere *ball;

	Block *pEnd;
	sf::Clock levelClock;

public:

	Level(){}

	Level (int blocks, int movingBlocks, Point3 start, Sphere *aball){
		pb = (Block*)malloc(blocks*sizeof(Block));
		pmb = (MovingBlock*)malloc(movingBlocks*sizeof(MovingBlock));
		pEnd = (Block*)malloc(4*sizeof(Block));
		numBlocks = blocks;
		numMovingBlocks = movingBlocks;
		currentBlock = 0;
		currentMovingBlock = 0;
		startPoint = start;

		ball = aball;

		resetLevel();
	}

	void addGoal(double centerPoint[], double theta, double phi) {
		double colors[] = {0, 1, 0};
		endPos = Point3(centerPoint[0], centerPoint[1], centerPoint[2]);
		double b1[] = {centerPoint[0]-1, centerPoint[1], centerPoint[2]+1.5};
		double b2[] = {centerPoint[0]+1.5, centerPoint[1], centerPoint[2]+1};
		double b3[] = {centerPoint[0]+1, centerPoint[1], centerPoint[2]-1.5};
		double b4[] = {centerPoint[0]-1.5, centerPoint[1], centerPoint[2]-1};
		pEnd[0] = Block(colors, b1,  3, 1, 2, theta, phi);
		pEnd[1] = Block(colors, b2,  2, 1, 3, theta, phi);
		pEnd[2] = Block(colors, b3,  3, 1, 2, theta, phi);
		pEnd[3] = Block(colors, b4,  2, 1, 3, theta, phi);
	}

	void addBlock(double *colors, double centerPoint[], double w, double h, double d, double theta, double phi)
	{
		if (currentBlock >= numBlocks)
			return;
		pb[currentBlock] = Block(colors, centerPoint, w, h, d, theta, phi);
		currentBlock++;
	}

	void addBlock(double *colors, double a1[], double *rot)
	{
		if (currentBlock >= numBlocks)
			return;
		pb[currentBlock] = Block(colors, a1, rot);
		currentBlock++;
	}

	void addMovingBlock(double *colors, double centerPoint[], double end[], double w, double h, double d, double theta, double phi, double timeTaken)
	{
		if (currentMovingBlock >= numMovingBlocks)
			return;
		pmb[currentMovingBlock] = MovingBlock(colors, centerPoint, end, w, h, d, theta, phi, timeTaken);
		currentMovingBlock++;
	}

	void display(bool shadow)
	{
		int i;

		for (i = 0; i < currentBlock; i++)
		{
			pb[i].display(shadow, i);
		}

		for (i = 0; i < 4; i++)
		{
			pEnd[i].display(shadow, i+currentBlock);
		}

		for (i = 0; i < currentMovingBlock; i++)
		{
			pmb[i].display(levelClock.GetElapsedTime());
		}
	}

	double * resetLevel()
	{
		//need to reset camera
		levelClock.Reset();
		ball->setCenter( startPoint );
		ball->stopBall();

		double camera[2] = { 0, 50 };
		return camera;
	}

	bool isWon()
	{
		double currentPos[3];
		ball->getCenter( currentPos );
		return ( 0.5 > sqrt(  pow( currentPos[0] - endPos.x, 2 ) +
							pow( currentPos[1] - endPos.y, 2 ) +
							pow( currentPos[2] - endPos.z, 2 ) ) );

	}

	bool isLost()
	{
		double center[3];
		ball->getCenter(center);
		return center[1] < -10;
	}

	void testCollision()
	{
		int i;
		for (i = 0; i < currentBlock; i++)
		{
			ball->testCollision(pb[i]);
		}
		
		for (i = 0; i < currentMovingBlock; i++)
		{
			ball->testCollision(pmb[i]);
		}
	}
};

Level createLevel1(Sphere *ball) {
	Point3 start = Point3(0, 1, 0);
	Level level1 = Level(5, 0, start, ball);
	double centers[6][3] = {{0,0,4},{3,0,10},{6,0,14},{3,0,16},{2,0,20},{2,0,26}};
	double w[] = {2, 8, 2, 4, 2};
	double d[] = {10, 2, 6, 2, 6};
	double color[] = {0.2, 0.4, 0.6};

	for (int i = 0; i < 5; i++)
	{
		level1.addBlock(color, centers[i], w[i], 1, d[i], 0, 0);
	}

	level1.addGoal(centers[5], 0, 0);

	return level1;
}

Level createLevel2(Sphere *ball) {
	int i;
	Point3 start = Point3(0, 1, 10);
	Level level2 = Level(9, 4, start, ball);
	double centers[9][3] = {{5,0,2},{6,0,-3},{-1,0,-6},{-6,0,1},{3,0,6},{10,0,-3},{-1,0,-10},{-10,0,1},{1,0,10}};
	double movingCenters[8][3] = {{10,2,0},{0,2,0},{-10,2,0},{0,2,0},{0,2,10},{0,2,0},{0,2,-10},{0,2,0}};
	double goal[] = {0,0,0};
	double w[] = {4,2,12,2,16,2,20,2,20,2,2,1,1};
	double d[] = {2,8,2,12,2,16,2,20,2,1,1,2,2};
	double colorBlock[] = {0.5, 0.68, 0.14};
	double colorMove[] = {0.8, 0.38, 0.04};

	for (i = 0; i < 9; i++)
	{
		level2.addBlock(colorBlock, centers[i], w[i], 1, d[i], 0, 0);
	}
	int j = 0;
	for (i = 9; i < 13; i++)
	{
		level2.addMovingBlock(colorMove, movingCenters[(i-9)*2], movingCenters[(i-9)*2+1], w[i], 1, d[i], 0, 0, 3);
		j++;
	}
	
	level2.addGoal(goal, 0, 0);

	return level2;
}