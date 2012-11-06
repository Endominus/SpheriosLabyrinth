
#include "ShaderManager.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Levels.h"

#define RESOLUTION 512

#define TRUE 1
#define FALSE 0
#define MAXTILT 10
#define TILTSPEED 0.01
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

		glEnable(GL_LIGHTING);
		
		cameraLookMode = false;
		lastPos[0] = -1;
		lastPos[1] = -1;
		cameraTheta = tiltX = tiltZ = 0;
		cameraPhi = 50;
		buttonPressed[0] = buttonPressed[1] = buttonPressed[2] = buttonPressed[3] = false;
		gfxinit();
		
		double a[] = {20, 0, -20};
		double b[] = {20, 10, -20};

		double block1Color[3] = {1, 0, 0};
		double block1Center[3] = {0, 0, 0};
		double ballColor[3] = {0,1,1};
		double ballCenter[3] = {0,3,0};
		ball = Sphere(ballColor,ballCenter,0.314159);

		//double block2Color[3] = {0, 0, 1};
		//double block2Center[3] = {2, 0, -5};
		//level[1] = Block(block2Color, block2Center, 1, 1, 1, 0, 45);
		/*level[2] = Block(0, 0, -200, 0, 10, -200, 2);
		level[3] = Block(0, -10, -20, 0, 10, -20, 2);
		level[4] = Block(-10, 0, -20, 10, 0, -2, 2);
		*/
		//level[0].toString();

		FILE * logFile;
		logFile = fopen("log.txt", "wb");
		if(logFile == NULL)
		{
			printf("Unable to open log file. Exiting...\n");
			exit(2);
		}
		
		__glewInit(logFile);
		ShaderManager shaders = ShaderManager(logFile);
		
		const char * vertPath = "Shaders/Render3dModel.vert";
		const char * fragPath = "Shaders/Render3dModel.frag";
		prog = shaders.buildShaderProgram(&vertPath, &fragPath, 1, 1);
		vertPath = "Shaders/BallShader.vert";
		fragPath = "Shaders/BallShader.frag";
		ballProg = shaders.buildShaderProgram(&vertPath, &fragPath, 1, 1);

		level = createLevel1(&ball);
		level.resetLevel();
		while (App->IsOpened())
		{
			App->SetActive();
			
			handleEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			updateModelviewMatrix();
			glUseProgram(prog);
			setShaderVariables(prog);
			setShaderVariables(ballProg);

			level.display();
			//for (int i = 0; i < 1; ++i)
			//{
			//	level[i].display();
			//}
			glUseProgram(ballProg);
			ball.display();
			App->Display();
		}
	}
	
private:
	bool buttonPressed[4];
	Sphere ball;
	sf::Window *App;
	sf::Clock motionClock;
	int lastPos[2];
	bool cameraLookMode;
	double cameraTheta;
	double cameraPhi;
	double tiltX;
	double tiltZ;
	GLint prog;
	GLint ballProg;
	bool GL20Support;
	Level level;

	void updateModelviewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glMultMatrixd(translationMatrix);
		//glMultMatrixd(rotationMatrix);
		//glMultMatrixd(inverseTranslationMatrix);
		//glRotated(cameraTheta, 0, 1, 0);
		//glRotated(cameraPhi, 0, 0, 1);
		double center[3];
		ball.getCenter(center);
		gluLookAt(center[0]+sin(cameraPhi*M_PI/180)*cos(cameraTheta*M_PI/180)*5, cos(cameraPhi*M_PI/180)*5, 
			center[2]+sin(cameraPhi*M_PI/180)*sin(cameraTheta*M_PI/180)*5, 
			center[0], 0, center[2], 0, 1, 0);
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
				buttonPressed[0] = true;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S)) {
				buttonPressed[1] = true;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A)) {
				buttonPressed[2] = true;
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D)) {
				buttonPressed[3] = true;
			}
			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::W)) {
				buttonPressed[0] = false;
			}
			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::S)) {
				buttonPressed[1] = false;
			}
			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::A)) {
				buttonPressed[2] = false;
			}
			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::D)) {
				buttonPressed[3] = false;
			}
			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::R)) {
				reset();
			}

			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Num1)) {
				level = createLevel1(&ball);
				reset();
			}

			if((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Num2)) {
				level = createLevel2(&ball);
				reset();
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
		if(buttonPressed[0]) {
			tiltX-=cos(cameraTheta*M_PI/180)*TILTSPEED;
			tiltZ-=sin(cameraTheta*M_PI/180)*TILTSPEED;
		}
		if(buttonPressed[1]) {
			tiltX+=cos(cameraTheta*M_PI/180)*TILTSPEED;
			tiltZ+=sin(cameraTheta*M_PI/180)*TILTSPEED;
		}
		if(buttonPressed[2]) {
			tiltX-=sin(cameraTheta*M_PI/180)*TILTSPEED;
			tiltZ+=cos(cameraTheta*M_PI/180)*TILTSPEED;
		}
		if(buttonPressed[3]) {
			tiltX+=sin(cameraTheta*M_PI/180)*TILTSPEED;
			tiltZ-=cos(cameraTheta*M_PI/180)*TILTSPEED;
		}
		if(tiltX*tiltX+tiltZ*tiltZ>MAXTILT*MAXTILT) {
			double size = sqrt(tiltX*tiltX+tiltZ*tiltZ);
			tiltX*=MAXTILT/size;
			tiltZ*=MAXTILT/size;
		}

		ball.accelerate(tiltX*0.000001,-0.00001,0.000001*tiltZ);
		//ball.testCollision(level[0]);
		level.testCollision();
		if (level.isLost())
			reset();
	}

	void reset() {
		double *cam = level.resetLevel();
		cameraTheta = cam[0];
		cameraPhi = cam[1];
		tiltX = 0;
		tiltZ = 0;
	}

	void __glewInit(FILE * logFile)
	{
		GL20Support = false;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			fprintf(logFile, "Error: %s\n", glewGetErrorString(err));
		}
		else
		{
			printf("GLEW init finished...\n");
			fprintf(logFile, "GLEW init finished...\n");
			if( __GLEW_VERSION_2_0 )
			{
				printf("OpenGL 2.0 is supported. Shaders should run correctly.\n");
				fprintf(logFile, "OpenGL 2.0 is supported. Shaders should run correctly.\n");
				GL20Support = true;
			}
			else
			{
				printf("OpenGL 2.0 is NOT enabled. The program may not work correctly.\n");
				fprintf(logFile, "OpenGL 2.0 is NOT enabled. The program may not work correctly.\n");
			}
			
			if( GLEW_ARB_vertex_program )
			{
				printf("ARB vertex programs supported.\n");
				fprintf(logFile, "ARB vertex programs supported.\n");
			}
			else
			{
				printf("ARB vertex programs NOT supported. The program may not work correctly.\n");
				fprintf(logFile, "ARB vertex programs NOT supported. The program may not work correctly.\n");
			}
			if( GLEW_ARB_fragment_program )
			{
				printf("ARB fragment programs supported.\n");
				fprintf(logFile, "ARB fragment programs supported.\n");
			}
			else
			{
				printf("ARB fragment programs NOT supported. The program may not work correctly.\n");
				fprintf(logFile, "ARB fragment programs NOT supported. The program may not work correctly.\n");
			}
		}
	}

	void setShaderVariables(GLuint shaderProg)
	{
		GLfloat projMatrix[16];
		GLfloat viewMatrix[16];
		glGetFloatv(GL_PROJECTION_MATRIX, projMatrix);
		glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);
		
		double center[3];
		ball.getCenter( center );

		if(GL20Support)
		{
			glUniform3f(glGetUniformLocation(shaderProg, "ballPos"),center[0], center[1], center[2]);
		}
		else
		{
			//glUniform3fvARB(glGetUniformLocationARB(shaderProg, "ballPos"), 3, (float*)ball.getCenter());
		}
	}
};


int main(int argc, char **argv)
{
	GLBox prog;
	return EXIT_SUCCESS;
}
