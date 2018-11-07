//#include "pch.h"		// required by visual studio only
#include <iostream>
#include <cmath>
#include <GL/glut.h>

#include "Exp.h"

using namespace std;

//prototype
void drawAxis();
void initLight();
void update(int);
void drawScene();
void drawCurve();
void printText();
void initRendering();
void handleResize(int, int);
void handleKeypress(unsigned char, int, int);
void renderbitmap(float x, float y, float z, void *font, string s);

// control variables
const float rotationDelta = 1;
const float yShift = 0.01;
const float updateDelay = 50;
bool controlRotateRight = false, controlRotateLeft = false;
float controlYDistance = 0, controlRotationAngle = 0;
bool rotateAboutX = false, rotateAboutY = false;

bool buildingDone = false;
float buildingAngle = 0;
float finalBuildAngle = 360;
const float BUILDING_ANGLE_DELTA = 5;

Exp expression;
string input;


int main(int argc, char** argv) {
	
	printf("Valid expressions are polynomials and trig functions with (x) inside of them..\n");
	printf("Enter an expression to draw:\n");
	getline(cin, input);
	if (input == "" || input == "\n") input = "0";
	expression.parse(input);

	char inChar;
	while (1) {
		printf("Enter rotaion axis (x/y): ");
		cin >> inChar;
		inChar = tolower(inChar);
		if (inChar == 'x') {
			rotateAboutX = 1;
			break;
		}
		else if (inChar == 'y') {
			rotateAboutY = 1;
			if (expression.isEven()) finalBuildAngle = 180;
			break;
		}
		printf("Invalid input, try again\n");
	}

	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	//Create the window
	glutCreateWindow("Solids Of Revolution");
	initRendering();
	initLight();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(updateDelay, update, 0); //Add a timer to update UI

	glutMainLoop();
	return 0;
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void initLight() {

	glClearColor(0, 0, 0, 0);

	GLfloat ambientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightPos0[] = { -3.0f, 3.0f, 5.0f, 1.0f }; 
	GLfloat lightColor0[] = { 0.5f, 0.5f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); 

	//Specular light
	GLfloat lightPos1[] = { -3.0f, 3.0f, 5.0f, 1.0f }; 
	GLfloat specularColor[] = { 0.8f,0.8f,1.0f,1.0f };
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	GLfloat shininess[] = { 100 };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

}


//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	if (key == 27){
		exit(0);
	}
	
	if (!buildingDone) return;
	
	switch (key) {
		case 'a':
			if (controlRotateRight) controlRotateRight = 0;
			else controlRotateLeft = 1;
			break;
		case 'd':
			if (controlRotateLeft) controlRotateLeft = 0;
			else controlRotateRight = 1;
			break;
		case 'w':
			controlYDistance += yShift;
			break;
		case 's':
			controlYDistance -= yShift;
			break;
	}
	
}


void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(updateDelay, update, 0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective

	gluLookAt(-3.0, 3.0 , 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glTranslatef(0, controlYDistance, 0);

	glRotatef(controlRotationAngle, rotateAboutY, rotateAboutX, 0);
	if (controlRotateRight) controlRotationAngle += rotationDelta;
	else if (controlRotateLeft) controlRotationAngle -= rotationDelta;
	
	if (abs(controlRotationAngle) > 360) controlRotationAngle = 0;

	drawAxis();
	drawCurve();
	printText();

	glutSwapBuffers();
	glFlush();
}

void drawCurve() {

	for (float angle = 0; angle < buildingAngle; angle += 0.15) {

		float scaleFactor = 0.1;

		glPushMatrix();

		glRotatef(angle, rotateAboutX, rotateAboutY, 0);
		glScalef(scaleFactor, scaleFactor, scaleFactor);
		glColor3f(0.4f, 0.4f, 0.4f);
		
		glBegin(GL_LINE_STRIP);

		for (float x = -15; x <= 15; x += 0.5) {
			float y = expression.eval(x);
			if (abs(y) > 10) continue;
			glNormal3f(x, y , 1.0f);
			glVertex3f(x, y, 0.0);
		}

		glEnd();

		glPopMatrix();
	}
	
	if (!buildingDone){
		buildingAngle += BUILDING_ANGLE_DELTA;
		if (buildingAngle >= finalBuildAngle){
			buildingAngle = finalBuildAngle;
			buildingDone = true;
			controlRotateRight = true;
		}
	}
}

// draw the axis
void drawAxis() {
	glBegin(GL_LINES);

		// x
		glPushMatrix();
			glColor3f(0.0, 0.0, 1.0f);
			glVertex3f(500.0, 0.0, 0.0);
			glVertex3f(-500.0, 0.0, 0.0);
		glPopMatrix();

		// y
		glPushMatrix();
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(0.0, -500.0, 0.0);
			glVertex3f(0.0, 500.0, 0.0);
		glPopMatrix();

		// z
		glPushMatrix();
			glColor3f(0.0, 1.0, 0.0);
			glVertex3f(0.0, 0.0, -500.0);
			glVertex3f(0.0, 0.0, 500.0);
		glPopMatrix();

	glEnd();
}
void renderbitmap(float x, float y, float z, void *font, string s) {

	glRasterPos3f(x, y, z);
	for (int i = 0; i < s.size(); i++) {
		glutBitmapCharacter(font, (int)s[i]);
	}

}

void printText() {
	
	glColor3f(0.4f, 0.0f, 0.7f);
	renderbitmap(0, 1.5, 0.035, GLUT_BITMAP_TIMES_ROMAN_24, input );
	glColor3f(0.4f, 0.4f, 0.4f);
	renderbitmap(3.25, 0.15, 0, GLUT_BITMAP_TIMES_ROMAN_24, "X");
	renderbitmap(-2.5, 0.15, 0, GLUT_BITMAP_TIMES_ROMAN_24, "-X");
	renderbitmap(0, 2.25, 0.035, GLUT_BITMAP_TIMES_ROMAN_24, "Y");
	renderbitmap(0, -3.5, 0.15, GLUT_BITMAP_TIMES_ROMAN_24, "-Y");
	renderbitmap(0, 0.035, 3, GLUT_BITMAP_TIMES_ROMAN_24, "Z");
	renderbitmap(0, 0, -12, GLUT_BITMAP_TIMES_ROMAN_24, "-Z");
	
}
