
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

//int buttonDown[3] = {0,0};

// Storage space for the various transformations we'll need
float translation1[16], translation2[16], rotation[16], inc_rotation[16];

void
display()
{
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw_color_cube();
}

void
update_Modelview_Matrix()
{
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 9.0, 0.0, 1.0, 0.0);
	glMultMatrixf(translation1);
	glMultMatrixf(translation2);
	glMultMatrixf(rotation);
}


void gfxinit()
{
	glEnable(GL_DEPTH_TEST);
	
	// initialize the projection stack
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 0.1, 400);
	gluLookAt(RESOLUTION/2, 0, 10, RESOLUTION/2, RESOLUTION/2, -200, 0, 1, 0);
	
	// initialize the modelview stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, translation1);
	glGetFloatv(GL_MODELVIEW_MATRIX, translation2);
	glGetFloatv(GL_MODELVIEW_MATRIX, rotation);
	glGetFloatv(GL_MODELVIEW_MATRIX, inc_rotation);
	glClear(GL_CLEAR);
	
}


class GLBox
{
public:
	GLBox()
	{
		App = new sf::Window(sf::VideoMode(RESOLUTION, RESOLUTION, 32), "Spherio");
		
		gfxinit();
		
		Block level[5];

		level[0] = Block(RESOLUTION/2, RESOLUTION/2, -210, RESOLUTION/2, (RESOLUTION/2) + 10, -210, 2);
		level[1] = Block(0, 0, -20, 0, 10, -20, 2);		
		level[2] = Block(0, 0, -200, 0, 10, -200, 2);
		level[3] = Block(0, -10, -20, 0, 10, -20, 2);
		level[4] = Block(-10, 0, -20, 10, 0, -2, 2);

		while (App->IsOpened())
		{
			
			App->SetActive();
			
			handleEvents();
			
			glColor3f(1, 1, 0);
			level[0].display();
			level[1].display();
			level[2].display();
			level[3].display();
			level[4].display();

			App->Display();
		}
	}
	
private:
	sf::Window *App;
	sf::Clock motionClock;
	float timeSinceMotion;
	
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
			
		}
	}
};


int main(int argc, char **argv)
{
	GLBox prog;
	return EXIT_SUCCESS;
}
