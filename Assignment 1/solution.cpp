#include <GL/glut.h>
#include <vector>
#include <cmath>
//#include <stdio.h>

using namespace std;

const float PI = acos(-1);

void display();
void drawPolygon(float, int, float, float);
vector<pair<float, float>> getPolygonPoints(float, int, float, float);
 
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygons");
    
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}

void display(){
	float r = 0.2; // the radius of the inner circle of the polygon
	glColor3f(0.0,0.0,1.0);		// set the drawing color to blue
    glClear(GL_COLOR_BUFFER_BIT);
    	drawPolygon(r * 0.6, 3, -0.66, 0.5);
    	drawPolygon(r, 4, 0.0, 0.5);
    	drawPolygon(r, 5, 0.66, 0.5);
    	
    	drawPolygon(r, 6, -0.66, 0.0);
    	drawPolygon(r, 7, 0.0, 0.0);
    	drawPolygon(r, 8, 0.66, 0.0);
    	
    	drawPolygon(r, 9, -0.66, -0.5);
    	drawPolygon(r, 10, 0.0, -0.5);
    	drawPolygon(r, 11, 0.66, -0.5);
    glFlush();
}

// gets the points and draws them
void drawPolygon(float innerCircleRadius, int sidesCount, float originX, float originY) {
	auto points = getPolygonPoints(innerCircleRadius, sidesCount, originX, originY);
    glBegin(GL_LINE_LOOP);
	for (auto point : points) {	
		glVertex2f(point.first, point.second);
	}
	glEnd();
}

// returns the points of the vertices of the desired polygon
// l: the radius of the inner circle of the pollygon
// n: the number of sides of the polygon
// dx: x of the polygn's inner circle's center
// dy: y of the polygn's inner circle's center
vector<pair<float, float>> getPolygonPoints(float l, int n, float dx, float dy) {
	auto points = vector<pair<float, float>>();
	float a = 2 * PI / n;
	float x = l * tan(a/2);
	float y = l;
	for (int i = 0 ; i < n ; ++i) {
		float nx = x * cos(a) + y * sin(a);
		float ny = y * cos(a) - x * sin(a);
		x = nx;
		y = ny;
		points.push_back(make_pair(x + dx, y + dy));
	}
	return points;
}
