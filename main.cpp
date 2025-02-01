#include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

using namespace std;

const float PI = 3.1416;
float moveWave = 0.0f;
float moveWave2 = 0.0f;
float moveCloud1 = 0.0f;
float moveCloud2 = 0.0f;
float moveShip = -1150.0f;
float moveWave_factor = 3.0f;
float moveCloud_factor = 1.0f;
float moveShip_factor = 2.0f;
float moveBird_factor = 2.0f;

bool night = false;
float starSize = 2.0f;
float starSize1 = 4.0f;
float birdmove= 0.0f;

//0 none, 1 black, 2 light yellow, 3 white, 4 dark yellow, 5 dark white, 6 red, 7 darker yellow
char bird[12][18] = {"00000011111100000",
                     "00001122213310000",
                     "00012244133331000",
                     "01111444153313100",
                     "13333144153313100",
                     "13333314415333100",
                     "15333514441111110",
                     "01555144416666661",
                     "00111444161111111",
                     "00177444416666610",
                     "00011777771111100",
                     "00000111110000000"};

char batmanLogo[20][32] = {"0000000000111111111110000000000",
                     "0000000111222222222221110000000",
                     "0000011222222122212222211100000",
                     "0001112111222111112221122111000",
                     "0011222112222111112222112221100",
                     "0112211112222111112222111122110",
                     "0121111112222111112222111111210",
                     "1121111111221111111221111111121",
                     "1211111111111111111111111111121",
                     "1211111111111111111111111111121",
                     "1211111111111111111111111111121",
                     "1211111111111111111111111111121",
                     "1211111111111111111111111111121",
                     "0121112222122111112212222111210",
                     "0112212222122211122212222122110",
                     "0011221222222221222222221221100",
                     "0001112222222221222222222111000",
                     "0000011122222222222222211100000",
                     "0000000111112222222111110000000",
                     "0000000000111111111110000000000"};

void update(int value) {
    moveWave += moveWave_factor;
    moveWave2 += moveWave_factor;
    moveCloud1 += moveCloud_factor;
    moveCloud2 += moveCloud_factor;
    moveShip += moveShip_factor;
    birdmove += moveBird_factor;

    if (moveWave > 1400) {
        moveWave = -1050.0f;
    }
    if (moveWave2 > 700) {
        moveWave2 = -1300.0f;
    }
    if (moveCloud1 > 1300) {
        moveCloud1 = -700.0f;
    }
    if (moveCloud2 > 600) {
        moveCloud2 = -1200.0f;
    }
    if(moveShip > 800)
    {
        moveShip = -1400.0f;
    }
    if (birdmove > 1400.0f) {
        birdmove = -200.0f;
    }


    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void updateStars(int value)
{
    if(starSize == 4)
    {
        starSize = 2.0f;
        starSize1 = 4.0f;
    }
    else
    {
        starSize = 4.0f;
        starSize1 = 2.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(500, updateStars, 0);
}

void drawBird(int x, int y)
{
    float pointSize = 2.0f;
    glPointSize(pointSize);

    glBegin(GL_POINTS);
    int currY = y;
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 18; j++){
                if(bird[i][j] == '0'){
                    //skip
                }
                else if(bird[i][j] == '1'){
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '2'){
                    glColor3f(0.976f, 0.843f, 0.553f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '3'){
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '4'){
                    glColor3f(0.973f, 0.718f, 0.208f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '5'){
                    glColor3f(0.847f, 0.902f, 0.804f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '6'){
                    glColor3f(0.961f, 0.220f, 0.004f);
                    glVertex2f(j*pointSize+x, currY);
                }
                else if(bird[i][j] == '7'){
                    glColor3f(0.878f, 0.502f, 0.173f);
                    glVertex2f(j*pointSize+x, currY);
                }
            }
            currY -= pointSize;
        }
    glEnd();
}

void drawBatman(float x, float y, float size)
{
    glColor3f(0.8f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y-size*20*0.5);
    glVertex2f(x+size*31*0.5, 300);
    glVertex2f(x+size*31, y-size*20*0.5);
    glEnd();

    glPointSize(size);
    glBegin(GL_POINTS);
    int currY = y;
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 31; j++){
                if(batmanLogo[i][j] == '0'){
                    //glColor3f(1.0f, 1.0f, 1.0f);
                    //glVertex2f(j*size+x, currY);
                }
                else if(batmanLogo[i][j] == '1'){
                    glColor3f(0.0f, 0.0f, 0.0f);
                    glVertex2f(j*size+x, currY);
                }
                else if(batmanLogo[i][j] == '2'){
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(j*size+x, currY);
                }
            }

            currY -= size;
        }
    glEnd();
}

void drawWater()
{
	glBegin(GL_QUADS);

	if(night == false) glColor3f(0.149, 0.847, 0.866);
	else glColor3f(0.0039, 0.227, 0.388);
	glVertex2f(0, 0);
	glVertex2f(1400, 0);
	glVertex2f(1400, 140);
	glVertex2f(0, 140);

	glEnd();
}
void drawLand()
{
	glBegin(GL_QUADS);

	if(night == false) glColor3f(0.647, 0.549, 0.561);
	else glColor3f(0.247, 0.176, 0.231);
	glVertex2f(0, 140);
	glVertex2f(1400, 140);
	glVertex2f(1400, 230);
	glVertex2f(0, 230);

	//horizontal line
	if(night == false) glColor3f(0.541, 0.471, 0.482);
	else glColor3f(0.180, 0.117, 0.145);
	glVertex2f(0, 200);
	glVertex2f(1400, 200);
	glVertex2f(1400, 210);
	glVertex2f(0, 210);

	//vertical lines
	for(int i=50; i<=1350; i+=100)
	{
		if(night == false) glColor3f(0.824, 0.776, 0.776);
		else glColor3f(0.647, 0.549, 0.560);
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

	if(night == false)glColor3f(0.553, 0.824, 0.957);
	else glColor3f(0.0, 0.2, 0.4);
	glVertex2f(0, 230);
	glVertex2f(1400, 230);
	glVertex2f(1400, 750);
	glVertex2f(0, 750);

	glEnd();
}

void drawWave(float startX, float startY, float length, string color)
{
	if(color == "dark")
    {
        if(night == false) glColor3f(0.145, 0.694, 0.855);
        else glColor3f(0.0, 0.184, 0.294);
    }
	else
    {
        if(night == false) glColor3f(0.161, 0.996, 0.847);
        else glColor3f(0.0039, 0.309, 0.525);
    }

	float waveRadius = 4.0f;
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
	if(night == false) glColor3f(0.443, 0.749, 0.824);
	else glColor3f(0.066, 0.168, 0.263);

    glBegin(GL_QUADS);
	glVertex2f(0, 230);
    glVertex2f(20, 230);
    glVertex2f(20, 420);
    glVertex2f(00, 420);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(20, 230);
    glVertex2f(40, 230);
    glVertex2f(40, 400);
    glVertex2f(20, 400);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(40, 230);
    glVertex2f(90, 230);
    glVertex2f(90, 370);
    glVertex2f(40, 370);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(90, 230);
    glVertex2f(190, 230);
    glVertex2f(190, 430);
    glVertex2f(90, 430);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(190, 230);
    glVertex2f(300, 230);
    glVertex2f(300, 400);
    glVertex2f(190, 400);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(300, 230);
    glVertex2f(380, 230);
    glVertex2f(380, 480);
    glVertex2f(300, 480);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(330, 230);
    glVertex2f(350, 230);
    glVertex2f(350, 520);
    glVertex2f(330, 520);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(380, 230);
    glVertex2f(400, 230);
    glVertex2f(400, 460);
    glVertex2f(380, 460);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(400, 230);
    glVertex2f(450, 230);
    glVertex2f(450, 400);
    glVertex2f(400, 400);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(450, 230);
    glVertex2f(510, 230);
    glVertex2f(510, 450);
    glVertex2f(450, 450);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(510, 230);
    glVertex2f(580, 230);
    glVertex2f(580, 420);
    glVertex2f(510, 420);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(600, 230);
    glVertex2f(660, 230);
    glVertex2f(660, 400);
    glVertex2f(600, 400);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(660, 230);
    glVertex2f(800, 230);
    glVertex2f(800, 430);
    glVertex2f(660, 430);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(800, 230);
    glVertex2f(900, 230);
    glVertex2f(900, 400);
    glVertex2f(800, 400);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(900, 230);
    glVertex2f(1000, 230);
    glVertex2f(1000, 350);
    glVertex2f(900, 350);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(1050, 230);
    glVertex2f(1150, 230);
    glVertex2f(1150, 390);
    glVertex2f(1050, 390);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(1150, 230);
    glVertex2f(1200, 230);
    glVertex2f(1200, 430);
    glVertex2f(1150, 430);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(1200, 230);
    glVertex2f(1300, 230);
    glVertex2f(1300, 450);
    glVertex2f(1200, 450);
    glEnd();

    glBegin(GL_QUADS);
	glVertex2f(1330, 230);
    glVertex2f(1400, 230);
    glVertex2f(1400, 470);
    glVertex2f(1330, 470);
    glEnd();
}

void drawPortBuilding()
{
    glColor3f(0.443, 0.749, 0.824);
    glBegin(GL_POLYGON);

    glEnd();
}

void drawCircle(float cx, float cy, float r, int numSegments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * PI * i / numSegments;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawRays(float cx, float cy, float innerRadius, float outerRadius, int numRays) {
    float angleStep = 2.0f * PI / numRays;

    glBegin(GL_LINES);
    for (int i = 0; i < numRays; i++) {
        float angle = i * angleStep;
        float xInner = cx + innerRadius * cos(angle);
        float yInner = cy + innerRadius * sin(angle);
        float xOuter = cx + outerRadius * cos(angle);
        float yOuter = cy + outerRadius * sin(angle);
        glVertex2f(xInner, yInner);
        glVertex2f(xOuter, yOuter);
    }
    glEnd();
}

void drawCloud(float x, float y, float size) {
    if(night == false) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.498f, 0.549f, 0.553f);

    drawCircle(x, y, size, 100);
    drawCircle(x + size * 0.5, y + size * 0.5, size, 100);
    drawCircle(x - size * 0.5, y + size * 0.5, size, 100);
    drawCircle(x + size * 0.5, y - size * 0.5, size, 100);
    drawCircle(x - size * 0.5, y - size * 0.5, size, 100);
    drawCircle(x - size, y, size, 100);
    drawCircle(x + size, y, size, 100);
}

void drawContainer(float startX, float startY, string color)
{
	if(color == "p")
    {
        if(night == false) glColor3f(0.416, 0.204, 0.533);
        else glColor3f(0.325, 0.145, 0.423);
    }
	else if(color == "y")
    {
        if(night == false) glColor3f(0.902, 0.866, 0.149);
        else glColor3f(0.737, 0.702, 0);
    }
	else if(color == "b")
    {
        if(night == false)  glColor3f(0.145, 0.694, 0.855);
        else glColor3f(0.301, 0.525, 0.635);
    }
	else if(color == "r")
    {
        if(night == false) glColor3f(0.859, 0.196, 0.224);
        else glColor3f(0.556, 0.031, 0.054);
    }

	glBegin(GL_QUADS);
	glVertex2f(startX, startY);
	glVertex2f(startX + 100, startY);
	glVertex2f(startX + 100, startY + 50);
	glVertex2f(startX, startY + 50);
	glEnd();

	if(color == "p")
    {
        if(night == false) glColor3f(0.711, 0.176, 1);
        else glColor3f(0.416, 0.204, 0.533);
    }
	else if(color == "y")
	{
	    if(night == false) glColor3f(0.737, 0.702, 0);
	    else glColor3f(0.902, 0.866, 0.149);
	}
	else if(color == "b")
    {
        if(night == false) glColor3f(0.380, 0.796, 1);
        else glColor3f(0.145, 0.694, 0.855);
    }
	else if(color == "r")
    {
        if(night == false) glColor3f(1, 0.471, 0.494);
        else glColor3f(0.859, 0.196, 0.224);
    }
	glLineWidth(2);
	glBegin(GL_LINES);
	for(int i=10; i<100; i+=10)
	{
		glVertex2f(startX + i, startY + 5);
		glVertex2f(startX + i, startY + 45);
	}
	glEnd();
}

void drawShip()
{
    // red bottom of ship
    glBegin(GL_QUADS);
    if(night == false) glColor3f(0.858f, 0.196f, 0.223f);
    else glColor3f(0.415f, 0.019f, 0.035f);
	glVertex2f(700, 70);
	glVertex2f(1100, 70);
	glVertex2f(1100, 90);
	glVertex2f(700, 90);
	glEnd();

	//body of ship
	glBegin(GL_QUADS);
    if(night == false) glColor3f(0.353f, 0.309f, 0.317f);
    else glColor3f(0.258f, 0.262f, 0.243f);
	glVertex2f(700, 90);
	glVertex2f(1100, 90);
	glVertex2f(1140, 150);
	glVertex2f(660, 150);
	glEnd();

    //railing part of ship
	glBegin(GL_QUADS);
    if(night == false) glColor3f(0.353f, 0.309f, 0.317f);
    else glColor3f(0.258f, 0.262f, 0.243f);
	glVertex2f(660, 150);
	glVertex2f(1140, 150);
	glVertex2f(1140, 170);
	glVertex2f(660, 170);
	glEnd();

	//first floor of ship
	glBegin(GL_QUADS);
    if(night == false) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.678f, 0.709f, 0.741f);
	glVertex2f(900, 170);
	glVertex2f(1105, 170);
	glVertex2f(1095, 210);
	glVertex2f(900, 210);
	glEnd();

	//second floor of ship
	glBegin(GL_QUADS);
    if(night == false) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.678f, 0.709f, 0.741f);
	glVertex2f(900, 170);
	glVertex2f(1120, 170);
	glVertex2f(1095, 210);
	glVertex2f(900, 210);
	glEnd();

	glBegin(GL_QUADS);
    glColor3f(0.353f, 0.309f, 0.317f);
	glVertex2f(900, 210);
	glVertex2f(1075, 210);
	glVertex2f(1075, 220);
	glVertex2f(900, 220);
	glEnd();

	glBegin(GL_QUADS);
    if(night == false) glColor3f(1.0f, 1.0f, 1.0f);
    else glColor3f(0.678f, 0.709f, 0.741f);
	glVertex2f(900, 220);
	glVertex2f(1075, 220);
	glVertex2f(1050, 260);
	glVertex2f(900, 260);
	glEnd();

	//windows
	glBegin(GL_QUADS);
    if(night == false) glColor3f(0.145f, 0.695f, 0.855f);
    else glColor3f(0.737f, 0.701f, 0.0f);
	glVertex2f(910, 180);
	glVertex2f(1080, 180);
    glVertex2f(1070, 200);
    glVertex2f(910, 200);
	glEnd();

	glBegin(GL_QUADS);
    if(night == false) glColor3f(0.145f, 0.695f, 0.855f);
    else glColor3f(0.737f, 0.701f, 0.0f);
	glVertex2f(910, 230);
	glVertex2f(1050, 230);
    glVertex2f(1040, 250);
    glVertex2f(910, 250);
	glEnd();

	// round windows
	if(night == false) glColor3f(0.035f, 0.255f, 0.388f);
	else  glColor3f(0.737f, 0.701f, 0.0f);
	for(int i=0; i<=390; i+=35)
	{
	    drawCircle(710+i, 150, 7, 100);
	}

	//add containers
	drawContainer(680, 170, "p");
	drawContainer(780, 170, "b");
	drawContainer(685, 220, "r");
	drawContainer(785, 220, "y");

	    /*for(int i=1; i<=4 ; i++)
	{
	    glVertex2f(900+10*i, 180);
        glVertex2f(900+10*i*3, 180);
        glVertex2f(900+10*i*3, 200);
        glVertex2f(900+10*i, 200);
	}*/
}

void drawStars()
{
    glPointSize(starSize);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2f(100, 680);
    glVertex2f(200, 580);
    glVertex2f(300, 650);
    glVertex2f(400, 630);
    glVertex2f(500, 600);
    glVertex2f(600, 660);
    glVertex2f(700, 540);
    glVertex2f(650, 460);
    glVertex2f(750, 440);
    glVertex2f(800, 610);
    glEnd();

    glPointSize(starSize1);
    glBegin(GL_POINTS);
    glVertex2f(900, 620);
    glVertex2f(1000, 640);
    glVertex2f(1100, 500);
    glVertex2f(1200, 680);
    glVertex2f(1300, 660);
    glVertex2f(140, 580);
    glVertex2f(240, 590);
    glVertex2f(180, 540);
    glVertex2f(280, 510);
    glVertex2f(530, 690);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	drawSky();
	drawWater();
	drawLand();
	if(night)
    {
        drawBatman(600, 580, 2.0f);
    }
    drawBgBuildings();

    // draw sun moon stars
	if(night == false)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
        drawCircle(850.0f, 600.0f, 30.0f, 100);

        glColor3f(1.0f, 1.0f, 0.0f);
        drawRays(850.0f, 600.0f, 30.0f, 30.0f + 25.0f, 16);
    }
    else
    {
        glColor3f(0.8f, 0.8f, 0.0f);
        drawCircle(450.0f, 600.0f, 30.0f, 100);
        glColor3f(0.0, 0.2, 0.4);
        drawCircle(460.0f, 600.0f, 25.0f, 100);

        drawStars();
    }
    // end sun moon stars



    glPushMatrix();
    glTranslatef(moveCloud1, 0.0f, 0.0f);
    drawCloud(200, 650, 25);
    drawCloud(700, 675, 20);
    drawCloud(400, 625, 18);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(moveCloud2, 0.0f, 0.0f);
    drawCloud(1000, 625, 22.5);
    drawCloud(1200, 635, 20);
    glPopMatrix();

    if(!night)
    {
        glPushMatrix();
        glTranslatef(birdmove, 0.0f, 0.0f);
        drawBird(100, 500);
        glPopMatrix();
    }

	glPushMatrix();
    glTranslatef(moveWave, 0.0f, 0.0f);
	drawWave(25, 60, 100, "dark");
    drawWave(185, 95, 200, "light");
    drawWave(225, 30, 100, "dark");
    drawWave(400, 35, 350, "dark");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(moveWave2, 0.0f, 0.0f);
    drawWave(900, 65, 250, "light");
	drawWave(1100, 25, 200, "dark");
	drawWave(1200, 105, 150, "dark");
	glPopMatrix();

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

	glPushMatrix();
    glTranslatef(moveShip, 0.0f, 0.0f);
	drawShip();
	glPopMatrix();

	//glutSwapBuffers();
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'N':
        case 'n':
            night = true;
            break;
        case 'D':
        case 'd':
            night = false;
            break;
        case ' ':
            moveWave_factor = 0.0f;
            moveCloud_factor = 0.0f;
            moveShip_factor = 0.0f;
            moveBird_factor = 0.0f;
            break;
        case 'S':
        case 's':
            moveWave_factor = 5.0f;
            moveCloud_factor = 1.0f;
            moveShip_factor = 2.0f;
            moveBird_factor = 2.0f;
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,1400,0,750);
}
int main(int argc, char** argv) {

    cout << "       Sea Port Scenery       " << endl;
    cout << "------------------------------" << endl;
    cout << "Press 'N' or 'n': Transition to night" << endl;
    cout << "Press 'D' or 'd': Transition to day" << endl;
    cout << "Press space: Stop scenery" << endl;
    cout << "Press 'S' or 's': Start scenery" << endl;
    cout << "Press Esc: Exit App" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1400, 750);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Sea port");

    myInit();

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutTimerFunc(10, updateStars, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
