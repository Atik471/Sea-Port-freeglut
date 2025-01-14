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


float moveWave = 0.0f;

void update(int value) {
    moveWave += 5.0f;

    if (moveWave > 1400) {
        moveWave = -300.0f;
    }
	
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

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
	glColor3f(0.443, 0.749, 0.824);
    glBegin(GL_POLYGON);
	/*glVertex2f(0, 230);
    glVertex2f(0, 380);
    glVertex2f(30, 380);
    glVertex2f(30, 350);
	glVertex2f(200, 350);
	glVertex2f(200, 430);
	glVertex2f(250, 430);
	glVertex2f(250, 330);
	glVertex2f(320, 330);
	glVertex2f(320, 230);*/
    glEnd();
}

void drawContainer(float startX, float startY, string color)
{
	if(color == "p") glColor3f(0.416, 0.204, 0.533);
	else if(color == "y") glColor3f(0.902, 0.866, 0.149);
	else if(color == "b") glColor3f(0.145, 0.694, 0.855);
	else if(color == "r") glColor3f(0.859, 0.196, 0.224);
	
	glBegin(GL_QUADS);
	glVertex2f(startX, startY);
	glVertex2f(startX + 100, startY);
	glVertex2f(startX + 100, startY + 50);
	glVertex2f(startX, startY + 50);
	glEnd();
	
	if(color == "p") glColor3f(0.711, 0.176, 1);
	else if(color == "y") glColor3f(0.737, 0.702, 0);
	else if(color == "b") glColor3f(0.380, 0.796, 1);
	else if(color == "r") glColor3f(1, 0.471, 0.494);
	glLineWidth(2);
	glBegin(GL_LINES);
	for(int i=10; i<100; i+=10)
	{
		glVertex2f(startX + i, startY + 5);
		glVertex2f(startX + i, startY + 45);
	}
	glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	drawSky();
	drawWater();
	drawLand();
	
	glPushMatrix();
    glTranslatef(moveWave, 0.0f, 0.0f);
	drawWave(25, 60, 100, "dark");
	glPopMatrix();
	
	drawWave(185, 95, 200, "light");
	drawWave(1100, 25, 200, "dark");
	drawWave(225, 30, 100, "dark");
	drawWave(900, 65, 250, "light");
	drawWave(1200, 105, 150, "dark");
	drawWave(400, 35, 350, "dark");
	
	drawBgBuildings();
	
	drawContainer(300, 230, "p");
	drawContainer(400, 230, "y");
	drawContainer(500, 230, "r");
	drawContainer(600, 230, "b");
	drawContainer(700, 230, "y");
	drawContainer(800, 230, "r");
	drawContainer(900, 230, "p");
	drawContainer(1000, 230, "b");
	drawContainer(1100, 230, "y");
	drawContainer(1200, 230, "r");
	drawContainer(1300, 230, "b");
	drawContainer(320, 280, "r");
	drawContainer(430, 280, "b");
	drawContainer(580, 280, "y");
	drawContainer(730, 280, "p");
	drawContainer(850, 280, "y");
	drawContainer(1050, 280, "b");
	drawContainer(1150, 280, "y");
	drawContainer(1300, 280, "p");
	drawContainer(1100, 330, "r");
	
	//glutSwapBuffers();
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
    glutTimerFunc(10, update, 0);

    glutMainLoop();

    return 0;
}