
//#include "pch.h" 
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <GL/glut.h>
#include "Exp.h"

using namespace std;

//prototype
void init();
void handleResize(int, int);
void handleKeypress(unsigned char, int, int);
void update(int);
void drawScene();
void drawAxis();
void drawCurve();

// control variables
const float rotationDelta = 1.5;
const float yShift = 0.01;
const float updateDelay = 20;
bool controlRotateRight = 0, controlRotateLeft = 0;
float controlYDistance = 0, controlRotationAngle = 0;
bool rotateAboutX = 0, rotateAboutY = 0;
Exp expression;


int main(int argc, char** argv) {

	string input;
	printf("Valid expressions are polynomials and trig functions with (x) inside of them..\n");
	printf("Enter an expression to draw:\n");
	getline(cin, input);
	expression.parse(input);
	
	char inChar;
	while(1){
		printf("Enter rotaion axis (x/y): ");
		cin >> inChar;
		inChar = tolower(inChar);
		if (inChar == 'x'){
			rotateAboutX = 1;
			break;
		} else if (inChar == 'y') {
			rotateAboutY = 1;
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
	init();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(updateDelay, update, 0); //Add a timer to update UI

	glutMainLoop();
	return 0;
}


void init() {

	glClearColor(0, 0, 0, 0);
		
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING); //Enable lighting

    glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1

    glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
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
	switch (key) {
		case 27: //Escape key
			exit(0);
			break;
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
	//glutPostRedisplay();
}


void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(updateDelay, update, 0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	gluLookAt(0, 0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glTranslatef(0, controlYDistance, 0);
	
	glRotatef(controlRotationAngle, 0, 1, 0);
	if (controlRotateRight) controlRotationAngle += rotationDelta;
	else if (controlRotateLeft) controlRotationAngle -= rotationDelta;
	
	if (abs(controlRotationAngle) > 360) controlRotationAngle = 0;
	
	//printf("right: %d, left: %d, angle: %f, y: %f\n", controlRotateRight, controlRotateLeft, controlRotationAngle, controlYDistance);
	
	//Add ambient light
	GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	drawAxis();
	drawCurve();

	glutSwapBuffers();
	glFlush();
}

void drawCurve() {

	for (float angle = 0 ; angle <= 360 ; angle+=0.1) {
	
		float scaleFactor = 0.1;
	
		glPushMatrix();
		
			glRotatef(angle, rotateAboutX, rotateAboutY, 0);
			glScalef(scaleFactor, scaleFactor, scaleFactor);
			glColor3f(0.5f, 0.0, 1.0f);
			
			glBegin(GL_LINE_STRIP);
			
				for (float x = -15 ; x <= 15 ; x += 0.1) {
					float y = expression.eval(x);
					if (abs(y) > 10) continue;
					glVertex3f(x, y , 0.0);
				}
				
			glEnd();
		
		glPopMatrix();
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
