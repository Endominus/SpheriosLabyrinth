
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

	double startPoint[3];

	Block *pEnd;

public:

	Level (int blocks, int movingBlocks, double start[3]){
		pb = (Block*)malloc(blocks*sizeof(Block));
		pmb = (MovingBlock*)malloc(movingBlocks*sizeof(MovingBlock));
		pEnd = (Block*)malloc(4*sizeof(Block));
		numBlocks = blocks;
		numMovingBlocks = movingBlocks;
		currentBlock = 0;
		currentMovingBlock = 0;
		startPoint[0] = start[0];
		startPoint[1] = start[1];
		startPoint[2] = start[2];
	}

	void addGoal(double centerPoint[], double theta, double phi) {
		double colors[] = {0, 1, 0};
		double b1[] = {centerPoint[0]-1, centerPoint[1], centerPoint[2]+1.5};
		double b2[] = {centerPoint[0]+1.5, centerPoint[1], centerPoint[2]+1};
		double b3[] = {centerPoint[0]+1, centerPoint[1], centerPoint[2]-1.5};
		double b4[] = {centerPoint[0]-1.5, centerPoint[1], centerPoint[2]-1};
		pEnd[0] = Block(colors, b1,  1.5, 1, 1, theta, phi);
		pEnd[1] = Block(colors, b2,  1, 1, 1.5, theta, phi);
		pEnd[2] = Block(colors, b3,  1.5, 1, 1, theta, phi);
		pEnd[3] = Block(colors, b4,  1, 1, 1.5, theta, phi);
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

	void display(double elapsedTime)
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
			pmb[i].display(elapsedTime);
		}
	}
};

Level createLevel1() {
	double start[] = {0, 0.5, 0};
	Level level1 = Level(5, 0, start);
	double centers[][] = {{0,0,4},{3,0,10},{6,0,14},{3,0,16},{2,0,20},{2,0,26}};
	double w[] = {1, 4, 1, 2, 1};
	double d[] = {5, 1, 3, 1, 3};
	double color[] = {0.2, 0.4, 0.6};

	for (int i = 0; i < 5; i++)
	{
		level1.addBlock(color, centers[i], w[i], 1, d[i], 0, 0);
	}

	level1.addGoal(centers[5], 0, 0);

	return level1;
}

Level createLevel2() {
	int i;
	double start[] = {10, 0.5, 10};
	Level level2 = Level(9, 4, start);
	double centers[][] = {{5,0,2},{6,0,-3},{-1,0,-6},{-6,0,1},{3,0,6},{10,0,-3},{-1,0,-10},{-10,0,1},{1,0,10},{15,2,0},{5,2,0},{-15,2,0},{-5,2,0},{0,2,15},{0,2,5},{0,2,-15},{0,2,-5},{0,0,0}};
	double w[] = {2,1,6,1,8,1,10,1,10,2,2,1,1};
	double d[] = {,1,4,1,6,1,8,10,1,1,1,2,2};
	double colorBlock[] = {0.5, 0.68, 0.14};
	double colorMove[] = {0.8, 0.38, 0.04};

	for (i = 0; i < 9; i++)
	{
		level2.addBlock(colorBlock, centers[i], w[i], 1, d[i], 0, 0);
	}

	for (i = 9; i < 17; i+=2)
	{
		level2.addMovingBlock(colorMove, centers[i], centers[i+1], w[i], 1, d[i], 0, 0, 3);
	}

	level2.addGoal(centers[17], 0, 0);

	return level2;
}