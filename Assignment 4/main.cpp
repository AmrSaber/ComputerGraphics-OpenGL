
//#include "pch.h"		// required by visual studio only
#include <iostream>
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

int lBig = 18;
int lSmall = 14;
int depth = -6;
int zFront = -10;
int zBack = zFront + depth;
float theta = 30 * PI / 180.0;
float dBig = lBig * sin(theta);
float hBig = lBig * cos(theta);
float dSmall = lSmall * sin(theta);
float hSmall = lSmall * cos(theta);

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
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); //Enable smooth shading

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

	gluLookAt(-10, -3, 50.0, 0, 0, 0, 0.0, 1.0, 0.0);

	float amb = 0.6;
	GLfloat ambientLight[] = { amb, amb, amb, 0.8f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	/*
	//Add positioned light
	GLfloat lightPos0[] = { 5.0f, 20.0f, zFront + 3.0f, 1.0f };
	GLfloat lightColor0[] = { 1, 1, 1, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	*/


	//Specular light
	GLfloat lightPos1[] = { 5.0f, 20.0f, zFront + 5.0f, 1.0f };
	GLfloat specularColor[] = { 1, 1, 1,1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	GLfloat shininess[] = { 100 };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);


	glEnable(GL_TEXTURE_2D);

	drawWindow();
	drawBackground();
	drawGrandfather();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void drawWindow() {
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureWood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPushMatrix();

	for (int i = 0; i < 6; ++i) {

		glRotatef(2 * theta * 180 / PI, 0, 0, 1);

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

		glNormal3f(0, 0, 1);

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

		glNormal3f(0, 1, 0);

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

		glNormal3f(0, -1, 0);

		glEnd();

	}

	glPopMatrix();

}

void drawBackground() {

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBg);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float x = 100;
	float y = 70;
	float z = zBack;

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(-x, -y, z);

	glTexCoord2f(0, 1);
	glVertex3f(-x, y, z);

	glTexCoord2f(1, 1);
	glVertex3f(x, y, z);

	glTexCoord2f(1, 0);
	glVertex3f(x, -y, z);

	glNormal3f(0, 0, 1);

	glEnd();


	//first coulmn 
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureWood);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float x1 = 40;
	float y1 = 70;
	float zFro = 1;
	float zBac = zBack;

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(x1, y1, zFro);

	glTexCoord2f(0, 1);
	glVertex3f(x1+6, y1, zFro);

	glTexCoord2f(1, 1);
	glVertex3f(x1+6, -y1, zFro);

	glTexCoord2f(1, 0);
	glVertex3f(x1, -y1, zFro);

	glNormal3f(0, 0, 1);

	glEnd();



	//second coulmn 

	float x2 = -40;

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(x2, y1, zFro);

	glTexCoord2f(0, 1);
	glVertex3f(x2 +6, y1, zFro);

	glTexCoord2f(1, 1);
	glVertex3f(x2 +6, -y1, zFro);

	glTexCoord2f(1, 0);
	glVertex3f(x2, -y1, zFro);

	glNormal3f(0, 0, 1);

	glEnd();


}

void drawGrandfather() {

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float z = zBack - (depth / 3.0f);

	glBegin(GL_POLYGON);

	glTexCoord2f(0.75, 1);
	glVertex3f(dSmall, hSmall, z);

	glTexCoord2f(1, 0.5);
	glVertex3f(2 * dSmall, 0, z);

	glTexCoord2f(0.75, 0);
	glVertex3f(dSmall, -hSmall, z);

	glTexCoord2f(0.25, 0);
	glVertex3f(-dSmall, -hSmall, z);

	glTexCoord2f(0, 0.5);
	glVertex3f(-2 * dSmall, 0, z);

	glTexCoord2f(0.25, 1);
	glVertex3f(-dSmall, hSmall, z);

	glNormal3f(0, 0, 1);

	glEnd();
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
