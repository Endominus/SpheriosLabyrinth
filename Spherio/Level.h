#define _USE_MATH_DEFINES
#include <math.h>
//#include "Block.h"

#define END_PAD_COLOR {0.9, 0.1, 0.1}
#define END_ZONE_COLOR {0.7, 0.7, 0.7}

class Level
{
private:
	Point3 startPos;
	Point3 endPos;
	Sphere ball;
	double startCameraPhi;
	double startCameraTheta;
	sf::Clock levelClock;
	Block levelBlocks[500];
	int levelBlockCount;
	double endPadColor[3];
	double endZoneColor[3];

public:

	Level( Sphere levelBall )
	{
		levelBlockCount = 0;
		endPadColor[0] = 0.9;
		endPadColor[1] = 0.1;
		endPadColor[2] = 0.1;
		endZoneColor[0] = endZoneColor[1] = endZoneColor[2] = 0.7;
	}

	void display()
	{
		for (int i = 0; i < levelBlockCount; ++i)
		{
			levelBlocks[i].display();
		}
	}

	void addBlock( Block b )
	{
		if ( levelBlockCount < 500 )
		{
			levelBlocks[ levelBlockCount ] = b;
			levelBlockCount++;
		}
	}

	void setStartPos( Point3 pos )
	{
		startPos = pos;
	}

	void addEndZone( double centerPoint[], double theta, double phi )
	{
		endPos = Point3( centerPoint[0], centerPoint[1], centerPoint[2] );
		double blockCenter[3] = { centerPoint[0], centerPoint[1] - 0.5, centerPoint[2] };
		levelBlocks[levelBlockCount++] = Block(endPadColor, blockCenter, 1, 0.5, 1, theta, phi);
		//surrounding
		blockCenter[1] += 0.25;
		blockCenter[0] -= 1;
		levelBlocks[levelBlockCount++] = Block(endZoneColor, blockCenter, 1, 1, 3, theta, phi);
		blockCenter[0] += 2;
		levelBlocks[levelBlockCount++] = Block(endZoneColor, blockCenter, 1, 1, 3, theta, phi);
		blockCenter[0] = centerPoint[0];
		blockCenter[2] = centerPoint[2] + 1;
		levelBlocks[levelBlockCount++] = Block(endZoneColor, blockCenter, 1, 1, 1, theta, phi);
		blockCenter[2] -= 2;
		levelBlocks[levelBlockCount++] = Block(endZoneColor, blockCenter, 1, 1, 1, theta, phi);
	}

	//Returns camera theta and phi
	double * resetLevel()
	{
		//need to reset camera
		levelClock.Reset();
		ball.setCenter( startPos );
		ball.stopBall();

		double camera[2] = { startCameraTheta, startCameraPhi };
		return camera;
	}

	bool isWon()
	{
		double currentPos[3];
		ball.getCenter( currentPos );
		return ( 0.5 > sqrt(  pow( currentPos[0] - endPos.x, 2 ) +
							pow( currentPos[1] - endPos.y, 2 ) +
							pow( currentPos[2] - endPos.z, 2 ) ) );

	}
};

Level CreateSpiralLevel( Sphere levelBall )
{
	Level spiral = Level( levelBall );
	double center[3] = { 0, 0, 0 };
	spiral.addEndZone( center, 0, 0 );
	//ToDo add phi
	double pathColor[3] = { 0.4, 0.4, 0.4 };
	double length = 3;
	double pathSize = 1;
	double theta = 30;
	double connectPoint[3] = { 1.5, 0, 1 };
	double blockCenter[3] = { connectPoint[0] + length/2* cos( theta * M_PI/180 ),
							  connectPoint[1], 
							  connectPoint[2] + length/2* sin( theta * M_PI/180 ) + pathSize/2 };
	Block currentBlock = Block(pathColor, blockCenter, length, 1, 1, 30, 0);
	spiral.addBlock( currentBlock );
	
	connectPoint[0] =  connectPoint[0] + length* cos( theta * M_PI/180 );
	connectPoint[2] = connectPoint[2] + length* sin( theta * M_PI/180 );

	return spiral;
}
