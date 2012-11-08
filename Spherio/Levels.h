
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
		startCameraTheta = 0;
		startCameraPhi = 50;

		resetLevel();
	}

	void setStartCamera( double theta, double phi )
	{
		startCameraPhi = phi;
		startCameraTheta = theta;
	}

	void addGoal(double centerPoint[], double theta, double phi) {
		double colors[] = {0, 0.8, };
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

	void display()
	{
		int i;

		for (i = 0; i < currentBlock; i++)
		{
			pb[i].display();
		}

		for (i = 0; i < 4; i++)
		{
			pEnd[i].display();
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

		double camera[2] = { startCameraTheta, startCameraPhi };
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
			ball->testCollisionMoving(pmb[i]);
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

	level1.setStartCamera( -90, 50 );
	return level1;
}

Level createLevel2(Sphere *ball) {
	int i;
	Point3 start = Point3(9, 1, 10);
	Level level2 = Level(9, 4, start, ball);
	double centers[9][3] = {{5,0,2},{6,0,-3},{-1,0,-6},{-6,0,1},{3,0,6},{10,0,-3},{-1,0,-10},{-10,0,1},{1,0,10}};
	double movingCenters[8][3] = {{10,2,0},{0,2,0},{-5,2,0},{0,2,0},{0,2,5},{0,2,0},{0,2,-5},{0,2,0}};
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
		level2.addMovingBlock(colorMove, movingCenters[(i-9)*2], movingCenters[(i-9)*2+1], 2*w[i], 2, 2*d[i], 0, 0, 3);
		j++;
	}
	
	level2.addGoal(goal, 0, 0);

	return level2;
}


Level createLevel3(Sphere *ball) {
	int i;
	Point3 start = Point3(2, 2, 1);
	Level level3 = Level(7, 0, start, ball);

	double goal[] = {12.5,0,11.5};
	double centers[7][3] =  {{2,0,7.5},	{6,0,17.5}, {13, 0, 21.5}, {18.5, 0, 19.5}, {20, 0, 15.5}, {18.75,0, 12.75}, {16.5, 0, 11.5} };	
	double w[] =		    {4,			3.5,		 3,				2.5,			2,				1.5,			1};
	double d[] =			{15,		8* sqrt(2.0), 8,		5*sqrt(2.0),		5,				2.5*sqrt(2.0),  3};
	double theta[] =		{0,			45,			90,				135,			0,				45,				90};
	double colorBlock[] = {0.4, 0.4, 0.4};

	for (i = 0; i < 7; i++)
	{
		level3.addBlock(colorBlock, centers[i], w[i], 1, d[i], theta[i], 0);
	}
	
	level3.addGoal(goal, 0, 0);
	level3.setStartCamera( -135, 50 );
	return level3;
}

Level createLevel4(Sphere *ball) {
	int i;
	Point3 start = Point3(8.5, 4, 1);
	Level levelx = Level(11, 4, start, ball);

	double goal[] = {12,0,19.5};
	double centers[10][3] =  {{2,0,6.5},	{0.5,0.25,1}, {0, 0, 6}, {-0.5, 0.25, 7.5}, {-1.5, 0.25, 6}, {-0.5, 0.25, 4.5}, {5, 0, 12}, {11, 0, 12}, {12, 0, 14.5}, {8.5, 2.02, 1} };	
	double w[] =		     {2,			1,			    2,		   3,			    1,				3,					4,			4,			  2,		2.4};
	double d[] =			 {13,		    2,				2,		   1,				2,				1,					2,			2,				5,		2};
	double h[] =			 {1,			1.5,			1,		   1.5,				1.5,			1.5,				1,			1,				1,		1};
	double colorBlock[] = {0.6, 0.6, 0.6};
	double colorMove[] = {0.8, 0.1, 0.1};

	double movingStart[4][3] =	{{2,1,12.5}, {8, -2, 12}, {14, 1, 13.5}, {10, 1, 15.5} };
	double movingEnd[4][3]	=	{{2,1,2.5}, {8, 2, 12},	  {12, 1, 13.5}, {12, 1, 15.5} };  
	double mw[] =				{2,		     2,			  2,			 2};
	double md[] =				{1,		     2,			  1,			 1};
	double mh[] =				{1,		     1,			  1,			 1};
	double time[] =				{2,		     2,			  1.5,			 1.5};
	double theta[] =			{0, 0, 0, 0};

	for (i = 0; i < 10; i++)
	{
		levelx.addBlock(colorBlock, centers[i], w[i], h[i], d[i], 0, 0);
	}

	double ramp[] = {4.75, 1, 1};
	levelx.addBlock(colorBlock, ramp, 5.85, 1, 2, 0, -20);

	for (i = 0; i < 4; i++)
	{
		levelx.addMovingBlock(colorMove, movingStart[i], movingEnd[i], mw[i], mh[i], md[i], theta[i], 0, time[i]);
	}

	levelx.addGoal(goal, 0, 0);
	levelx.setStartCamera( -45, 40 );
	return levelx;
}