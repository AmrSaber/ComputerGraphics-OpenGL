
//#include "pch.h"
//#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "imageloader.h"

const float PI = acos(-1);

using namespace std;

void handleKeypress(unsigned char, int, int);
void handleResize(int, int);
GLuint loadTexture(Image*);
void initRendering();

void drawScene();
void drawWindow();
void drawBackground();
void drawGrandfather();

GLuint textureBg;
GLuint textureWood;
GLuint textureImage;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Mulan Scene");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutMainLoop();
	return 0;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
	}
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("image_bg.bmp");
	textureBg = loadTexture(image);
	delete image;
	
	image = loadBMP("image_wood.bmp");
	textureWood = loadTexture(image);
	delete image;
	
	image = loadBMP("image_grandfather.bmp");
	textureImage = loadTexture(image);
	delete image;
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0, 0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	// TODO: add lookAt and lights

	glEnable(GL_TEXTURE_2D);
	
	drawWindow();
	drawBackground();
	drawGrandfather();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void drawWindow() {
	glBindTexture(GL_TEXTURE_2D, textureWood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int lBig = 18;
	int lSmall = 14;
	int depth = -4;
	
	int zFront = -10;
	int zBack = zFront + depth;
	
	float theta = 30 * PI / 180.0;
	
	glPushMatrix();
	
	for (int i = 0 ; i < 6 ; ++i) {
	
		glRotatef(2 * theta * 180 / PI, 0, 0, 1);
	
		float dBig = lBig * sin(theta);
		float hBig = lBig * cos(theta);
		
		float dSmall = lSmall * sin(theta);
		float hSmall = lSmall * cos(theta);
		
		// front
		glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(-dSmall, hSmall, zFront);

			glTexCoord2f(0, 1);
			glVertex3f(-dBig, hBig, zFront);

			glTexCoord2f(1, 1);
			glVertex3f(dBig, hBig, zFront);

			glTexCoord2f(1, 0);
			glVertex3f(dSmall, hSmall, zFront);			

		glEnd();
		
		// top
		glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(-dBig, hBig, zFront);

			glTexCoord2f(0, 1);
			glVertex3f(-dBig, hBig, zBack);

			glTexCoord2f(1, 1);
			glVertex3f(dBig, hBig, zBack);

			glTexCoord2f(1, 0);
			glVertex3f(dBig, hBig, zFront);		

		glEnd();
		
		// bottom
		glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(-dSmall, hSmall, zFront);

			glTexCoord2f(0, 1);
			glVertex3f(-dSmall, hSmall, zBack);

			glTexCoord2f(1, 1);
			glVertex3f(dSmall, hSmall, zBack);

			glTexCoord2f(1, 0);
			glVertex3f(dSmall, hSmall, zFront);		

		glEnd();
		
	}
	
	glPopMatrix();
	
}

void drawBackground() {
	
}

void drawGrandfather() {
	
}


//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
