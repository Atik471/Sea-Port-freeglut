#include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

using namespace std;
	/*
    glPushMatrix();
    glTranslatef(_moveReverse, 0.0f, 0.0f);
    glPopMatrix();
    glutSwapBuffers();
	*/


/*float _move= 0.0f;
float _moveReverse = 0.0f;

void update(int value) {
    _move += 5.0f;
    _moveReverse -= 1.f;

    if (_move > 800) {
        _move = -120.0f;
    }

    if (_moveReverse < -500) {
        _moveReverse = 800.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}*/

void drawWater()
{
	glBegin(GL_QUADS);
	
	glColor3f(0.149, 0.847, 0.866);
	glVertex2f(0, 0);
	glVertex2f(1400, 0);
	glVertex2f(1400, 140);
	glVertex2f(0, 140);
	
	glEnd();
}
void drawLand()
{
	glBegin(GL_QUADS);
	
	glColor3f(0.647, 0.549, 0.561);
	glVertex2f(0, 140);
	glVertex2f(1400, 140);
	glVertex2f(1400, 230);
	glVertex2f(0, 230);
	
	//horizontal line
	glColor3f(0.541, 0.471, 0.482);
	glVertex2f(0, 200);
	glVertex2f(1400, 200);
	glVertex2f(1400, 210);
	glVertex2f(0, 210);
	
	//vertical lines
	for(int i=50; i<=1350; i+=100)
	{
		glColor3f(0.824, 0.776, 0.776);
		glVertex2f(i, 145);
		glVertex2f(i+5, 145);
		glVertex2f(i+5, 195);
		glVertex2f(i, 195);
	}
	
	glEnd();
}

void drawSky()
{
	glBegin(GL_QUADS);
	
	glColor3f(0.553, 0.824, 0.957);
	glVertex2f(0, 230);
	glVertex2f(1400, 230);
	glVertex2f(1400, 750);
	glVertex2f(0, 750);
	
	glEnd();
}

void drawWave(float startX, float startY, float length, string color)
{
	if(color == "dark") glColor3f(0.145, 0.694, 0.855);
	else glColor3f(0.161, 0.996, 0.847);
	
	float waveRadius = 15.0f;
    int numSegments = 30;
	
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 1.0f * M_PI * i / numSegments;
        glVertex2f(startX + waveRadius * cos(angle + M_PI * 0.5), startY + waveRadius * sin(angle + M_PI * 0.5));
    }
    glEnd();
	
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= numSegments; i++) {
        float angle = 1.0f * M_PI * i / numSegments;
        glVertex2f(startX + length + waveRadius * cos(angle - M_PI * 0.5), startY + waveRadius * sin(angle - M_PI * 0.5));
    }
    glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(startX, startY - waveRadius);
	glVertex2f(length + startX, startY - waveRadius);
	glVertex2f(length + startX, startY - waveRadius + 2 * waveRadius);
	glVertex2f(startX, startY - waveRadius + 2 * waveRadius);
	glEnd();
}

void drawBgBuildings()
{
	/*glColor3f(0.443, 0.749, 0.824);
    glBegin(GL_POLYGON);
    glVertex2f(0, 230);
    glVertex2f(1400, 230);
    glVertex2f(1300, 260);
	glVertex2f(500, 280);
    glVertex2f(0, 260);
    //glVertex2f(40, 180);
    //glVertex2f(50, 200);
    glEnd();*/
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	drawSky();
	drawWater();
	drawLand();
	drawWave(25, 60, 100, "dark");
	drawWave(185, 95, 200, "light");
	drawWave(1100, 25, 200, "dark");
	drawWave(225, 30, 100, "dark");
	//drawWave(725, 95, 300, "dark");
	drawWave(900, 65, 250, "light");
	drawWave(1200, 105, 150, "dark");
	drawWave(400, 35, 350, "dark");
	drawBgBuildings();
    glFlush();
}

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,1400,0,750);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1400, 750);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Sea port");
	
    myInit();

    glutDisplayFunc(display);
    //glutTimerFunc(10, update, 0);

    glutMainLoop();

    return 0;
}