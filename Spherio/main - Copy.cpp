
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Block.h"

#define RESOLUTION 512

#define TRUE 1
#define FALSE 0
#define MAXTILT 10
#define TILTSPEED 1
#define CAMERASPEED 1

// Storage space for the various transformations we'll need
double translationMatrix[16], inverseTranslationMatrix[16], rotationMatrix[16];

void
display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*void
update_Modelview_Matrix()
{
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 9.0, 0.0, 1.0, 0.0);
	glMultMatrixd(translation1);
	glMultMatrixd(translation2);
	glMultMatrixd(rotation);
}*/


void gfxinit()
{
	glEnable(GL_DEPTH_TEST);
	
	// initialize the projection stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 0.1, 100);
	
	// initialize the modelview stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
	glTranslated(0, 0, -5);
	glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &translationMatrix);
	glTranslated(0, 0, 10);
	glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &inverseTranslationMatrix);
	glClearColor(0,0,0, 1);
	gluLookAt(0, 0, 0, 0, 0, -20, 0, 1, 0);
}


class GLBox
{
public:
	GLBox()
	{
		App = new sf::Window(sf::VideoMode(RESOLUTION, RESOLUTION, 32), "Spherio");
		
		cameraLookMode = false;
		lastPos[0] = -1;
		lastPos[1] = -1;
		cameraTheta = tiltX = tiltZ = 0;
		cameraPhi = 50;
		gfxinit();
		
		double a[] = {20, 0, -20};
		double b[] = {20, 10, -20};

		double block1Color[3] = {1, 0, 0};
		double block1Center[3] = {2, 0, 0};
		level[0] = Block(block1Color, block1Center, 4, 1, 4, 0, 0);
		double ballColor[3] = {0,1,1};
		double ballCenter[3] = {0,1,0};
		ball = Sphere(ballColor,ballCenter,0.1);

		//double block2Color[3] = {0, 0, 1};
		//double block2Center[3] = {2, 0, -5};
		//level[1] = Block(block2Color, block2Center, 1, 1, 1, 0, 45);
		/*level[2] = Block(0, 0, -200, 0, 10, -200, 2);
		level[3] = Block(0, -10, -20, 0, 10, -20, 2);
		level[4] = Block(-10, 0, -20, 10, 0, -2, 2);
		*/
		//level[0].toString();
		while (App->IsOpened())
		{
			
			App->SetActive();
			
			handleEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			updateModelviewMatrix();
			for (int i = 0; i < 1; ++i)
			{
				level[i].display();
			}
			ball.display();
			App->Display();
		}
	}
	
private:
	Block level[5];
	Sphere ball;
	sf::Window *App;
	sf::Clock motionClock;
	int lastPos[2];
	bool cameraLookMode;
	double cameraTheta;
	double cameraPhi;
	double tiltX;
	double tiltZ;

	void updateModelviewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glMultMatrixd(translationMatrix);
		//glMultMatrixd(rotationMatrix);
		//glMultMatrixd(inverseTranslationMatrix);
		//glRotated(cameraTheta, 0, 1, 0);
		//glRotated(cameraPhi, 0, 0, 1);
		gluLookAt(sin(cameraPhi*M_PI/180)*cos(cameraTheta*M_PI/180)*5, cos(cameraPhi*M_PI/180)*5, sin(cameraPhi*M_PI/180)*sin(cameraTheta*M_PI/180)*5, 0, 0, 0, 0, 1, 0);
		glRotated(-tiltX,0,0,1);
		glRotated(tiltZ,1,0,0);
	}
	
	void handleEvents()
	{
		const sf::Input& Input = App->GetInput();
		bool shiftDown = Input.IsKeyDown(sf::Key::LShift) || Input.IsKeyDown(sf::Key::RShift);
		sf::Event Event;
		while (App->GetEvent(Event))
		{
			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				App->Close();
			
			// Escape key : exit
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App->Close();
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::W)) {
				tiltX-=cos(cameraTheta*M_PI/180)*TILTSPEED;
				tiltZ-=sin(cameraTheta*M_PI/180)*TILTSPEED;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S)) {
				tiltX+=cos(cameraTheta*M_PI/180)*TILTSPEED;
				tiltZ+=sin(cameraTheta*M_PI/180)*TILTSPEED;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A)) {
				tiltX-=sin(cameraTheta*M_PI/180)*TILTSPEED;
				tiltZ+=cos(cameraTheta*M_PI/180)*TILTSPEED;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {
				tiltX+=sin(cameraTheta*M_PI/180)*TILTSPEED;
				tiltZ-=cos(cameraTheta*M_PI/180)*TILTSPEED;
			}
			if(tiltX*tiltX+tiltZ*tiltZ>MAXTILT*MAXTILT) {
				double size = sqrt(tiltX*tiltX+tiltZ*tiltZ);
				tiltX*=MAXTILT/size;
				tiltZ*=MAXTILT/size;
			}
			
			if (cameraLookMode && Event.Type == sf::Event::MouseMoved)
			{
				int deltaX = Event.MouseMove.X - lastPos[0];
				int deltaY = Event.MouseMove.Y - lastPos[1];

				/*glPushMatrix();
				glLoadIdentity();
				glRotated(deltaY, 1, 0, 0);
				glRotated(deltaX, 0, 1, 0);
				glMultMatrixd(rotationMatrix);
				glGetDoublev(GL_MODELVIEW_MATRIX, (GLdouble*) &rotationMatrix);
				glPopMatrix();*/

				cameraTheta += deltaX*CAMERASPEED;
				//cameraPhi -= deltaY*CAMERASPEED;

				if (cameraPhi > 180)
					cameraPhi = 180;
				if (cameraPhi < 0.01)
					cameraPhi = 0.01;

				lastPos[0] = Event.MouseMove.X;
				lastPos[1] = Event.MouseMove.Y;
			}

			if (Event.Type == sf::Event::MouseButtonPressed
				  && Event.MouseButton.Button == sf::Mouse::Left)
			{
				lastPos[0] = Event.MouseButton.X;
				lastPos[1] = Event.MouseButton.Y;
				cameraLookMode = !cameraLookMode;
			}
		}
		ball.accelerate(tiltX*0.0001,0.0001,0.0001*tiltZ);
		ball.testCollision(level[0]);
	}
};


int main(int argc, char **argv)
{
	GLBox prog;
	return EXIT_SUCCESS;
}
