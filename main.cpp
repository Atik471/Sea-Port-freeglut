#include <stdlib.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

const float PI = 3.1416;

float moveWave = 0.0f;
float moveWave2 = 0.0f;
float moveCloud1 = 0.0f;
float moveCloud2 = 0.0f;
float moveShip = -1050.0f;
float movePirateShip = 1000.0f;
float moveWave_factor = 0.5f;
float moveCloud_factor = 1.0f;
float moveShip_factor = 2.0f;
float movePirateShip_factor = -2.0f;
float moveBird_factor = 2.0f;

bool liftContainer = false;
float moveContainer = 0.0f;
float moveContainer_factor = 0.5f;

float hookLength = 345;
bool hookLength_change = false;
float hookLength_changeFactor = 0.5f;

bool night = false;
float starSize = 2.0f;
float starSize1 = 4.0f;
float birdmove1= 0.0f;
float birdmove2= 0.0f;
float birdmove3= 0.0f;
float birdmove4= 0.0f;
float birdmove5= 0.0f;


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

char pirate[14][18] = {"01100000000000110",
                       "11100000000000111",
                       "11110011111001111",
                       "00110111111101100",
                       "00001111111110000",
                       "00001001110010000",
                       "00001001110010000",
                       "00001111011110000",
                       "00001110001110000",
                       "00000011111000000",
                       "00011010001011000",
                       "01111011111011110",
                       "01110001110001110",
                       "00110000000001100"};

void restart()
{
    moveWave = 0.0f;
    moveWave2 = 0.0f;
    moveCloud1 = 0.0f;
    moveCloud2 = 0.0f;
    moveShip = -1050.0f;
    movePirateShip = 1000.0f;
    moveShip_factor = 2.0f;

    liftContainer = false;
    moveContainer = 0.0f;
    moveContainer_factor = 0.5f;

    hookLength = 345;
    hookLength_change = false;

    birdmove1= 0.0f;
    birdmove2= 0.0f;
    birdmove3= 0.0f;
    birdmove4= 0.0f;
    birdmove5= 0.0f;
}


void update(int value) {
    moveWave += moveWave_factor;
    moveWave2 += moveWave_factor;
    moveCloud1 += moveCloud_factor;
    moveCloud2 += moveCloud_factor;
    moveShip += moveShip_factor;
    birdmove1 += moveBird_factor;
    birdmove2 += moveBird_factor;
    birdmove3 += moveBird_factor;
    birdmove4 += moveBird_factor;
    birdmove5 += moveBird_factor;
    movePirateShip += movePirateShip_factor;

    if(liftContainer)
    {
        if(night == false) moveContainer += moveContainer_factor;
    }
    if(hookLength < 345-135 && liftContainer == false)
    {
        hookLength_change = false;
        liftContainer = true;
    }
    if(hookLength_change == true)
    {
        if(night == false) hookLength -= hookLength_changeFactor;
    }
    if(moveShip > 80 && hookLength > 345-135 && liftContainer == false)
    {
        moveShip_factor = 0.0f;
        hookLength_change = true;
    }
    if (moveShip > 80 && liftContainer)
    {
        if(hookLength < 345 && night == false) hookLength += hookLength_changeFactor;
    }
    if (moveContainer > 125)
    {
        moveContainer_factor = 0.0f;
    }

    if(movePirateShip < -1200)
    {
        movePirateShip = 1400;
    }

    if (moveWave > 1400) {
        moveWave = -1400.0f;
    }
    if (moveWave2 > 2800) {
        moveWave2 = -2800.0f;
    }

    if (moveCloud1 > 1300) {
        moveCloud1 = -800.0f;
    }
    if (moveCloud2 > 600) {
        moveCloud2 = -1300.0f;
    }

    if (birdmove1 > 1400.0f) {
        birdmove1 = -200.0f;
    }
    if (birdmove2 > 900.0f) {
        birdmove2 = -700.0f;
    }
    if (birdmove3 > 400.0f) {
        birdmove3 = -1200.0f;
    }
    if (birdmove4 > 700.0f) {
        birdmove4 = -900.0f;
    }
    if (birdmove5 > 500.0f) {
        birdmove5 = -1100.0f;
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


void renderBitmapText(float x, float y, void* font, const char* text) {
    if(night == true) glColor3f(0.902, 0.867, 0.149);
    else glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void drawPortBuilding()
{
    //base
    glColor3f(0.427, 0.475, 0.522);
    glBegin(GL_QUADS);
    glVertex2f(400, 230);
    glVertex2f(700, 230);
    glVertex2f(700, 480);
    glVertex2f(400, 480);
    glEnd();

    //base corner
    glColor3f(0.258, 0.263, 0.243);
    glBegin(GL_QUADS);
    glVertex2f(410, 230);
    glVertex2f(690, 230);
    glVertex2f(690, 470);
    glVertex2f(410, 470);
    glEnd();

    //floor divider
    glLineWidth(5);
    for(int i=0; i<680-450; i+=48)
    {
        glColor3f(0.427, 0.475, 0.522);
        glBegin(GL_LINES);
        glVertex2f(410, 232+i);
        glVertex2f(690, 232+i);
        glEnd();
    }

    //windows
    for(int i=0; i<680-450; i+=48)
    {
        if(night == false) glColor3f(0.443, 0.749, 0.824);
        else glColor3f(0.902, 0.867, 0.149);
        glBegin(GL_QUADS);
        glVertex2f(450, 235+i);
        glVertex2f(650, 235+i);
        glVertex2f(650, 235+i+38);
        glVertex2f(450, 235+i+38);
        glEnd();
    }

    //billboard corner
    if(night == false) glColor3f(0.035, 0.255, 0.388);
    else glColor3f(0.902, 0.867, 0.149);
    glBegin(GL_QUADS);
    glVertex2f(495, 480);
    glVertex2f(605, 480);
    glVertex2f(605, 525);
    glVertex2f(495, 525);
    glEnd();

    //billboard
    if(night == false) glColor3f(0.415, 0.533, 0.6);
    else glColor3f(0.035, 0.255, 0.388);
    glBegin(GL_QUADS);
    glVertex2f(500, 480);
    glVertex2f(600, 480);
    glVertex2f(600, 520);
    glVertex2f(500, 520);
    glEnd();

    renderBitmapText(525.0f, 495.0f, GLUT_BITMAP_HELVETICA_18, "PORT");
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
	if(night == false)
    {
        drawContainer(680, 170, "p");
        drawContainer(780, 170, "y");
        drawContainer(685, 220, "r");
        if(liftContainer)
        {
            glPushMatrix();
            glTranslatef(0.0f, moveContainer, 0.0f);
            drawContainer(785, 220, "b");
            glPopMatrix();
        }
        else
        {
            drawContainer(785, 220, "b");
        }
    }
}

void drawCurvedRectangle(float width, float height, float curveFactor) {
    int segments = 30;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / segments;

        float x1 = -width / 2 - curveFactor * sin(t * 3.14159f);
        float y1 = -height / 2 + t * height;

        float x2 = width / 2 - curveFactor * sin(t * 3.14159f);
        float y2 = -height / 2 + t * height;

        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}

void drawPirateShip()
{
    // bottom of ship
    glBegin(GL_QUADS);
    glColor3f(0.486f, 0.294f, 0.043f);
	glVertex2f(700, 80);
	glVertex2f(1100, 80);
	glVertex2f(1100, 90);
	glVertex2f(700, 90);
	glEnd();

	//body of ship
	glBegin(GL_QUADS);
    glColor3f(0.192f, 0.122f, 0.032f);
	glVertex2f(700, 90);
	glVertex2f(1100, 90);
	glVertex2f(1140, 150);
	glVertex2f(660, 150);
	glEnd();

	drawContainer(760, 150, "p");
    drawContainer(890, 150, "y");

    //left sail stick
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.376f, 0.243f, 0.161f);
    glVertex2f(720, 150);
    glVertex2f(720, 275);
    glEnd();

    //left sail
    glColor3f(0.137f, 0.133f, 0.125f);
	glPushMatrix();
    glTranslatef(725, 230, 0);
    drawCurvedRectangle(80, 80, 20);
    glPopMatrix();

    //right sail stick
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.376f, 0.243f, 0.161f);
    glVertex2f(1060, 150);
    glVertex2f(1060, 275);
    glEnd();

    //right sail
    glColor3f(0.137f, 0.133f, 0.125f);
	glPushMatrix();
    glTranslatef(1065, 230, 0);
    drawCurvedRectangle(80, 80, 20);
    glPopMatrix();

    //middle sail stick
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.376f, 0.243f, 0.161f);
    glVertex2f(880, 150);
    glVertex2f(880, 375);
    glEnd();

    //middle sail
    glColor3f(0.137f, 0.133f, 0.125f);
	glPushMatrix();
    glTranslatef(885, 230, 0);
    drawCurvedRectangle(110, 90, 20);
    glPopMatrix();

    glColor3f(0.137f, 0.133f, 0.125f);
	glPushMatrix();
    glTranslatef(885, 330, 0);
    drawCurvedRectangle(90, 80, 20);
    glPopMatrix();

    //pirate flag
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    int currY = 350;
        for(int i = 0; i < 14; i++){
            for(int j = 0; j < 18; j++){
                if(pirate[i][j] == '0')
                {
                    //skip
                }
                else if(pirate[i][j] == '1'){
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(j*3+845, currY);
                }
            }
            currY -= 3;
        }
    glEnd();


    //railing part of ship
	glBegin(GL_QUADS);
    glColor3f(0.192f, 0.122f, 0.032f);
	glVertex2f(660, 150);
	glVertex2f(740, 150);
	glVertex2f(740, 180);
	glVertex2f(660, 180);
	glEnd();

	glBegin(GL_QUADS);
    glColor3f(0.192f, 0.122f, 0.032f);
	glVertex2f(1000, 150);
	glVertex2f(1140, 150);
	glVertex2f(1140, 180);
	glVertex2f(1000, 180);
	glEnd();

	// round windows
	glColor3f(0.737f, 0.701f, 0.0f);
	for(int i=0; i<=340; i+=50)
	{
	    drawCircle(750+i, 130, 9, 100);
	}
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
    glVertex2f(520, 700);
    glVertex2f(640, 560);
    glVertex2f(750, 500);
    glVertex2f(680, 490);
    glVertex2f(710, 470);
    glVertex2f(850, 650);
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
    glVertex2f(1200, 600);
    glVertex2f(240, 480);

    glEnd();
}

void drawCrane()
{
    if(night == false) glColor3f(0.91, 0.87, 0.15);
    else glColor3f(0.737, 0.702, 0.0);
    //cross lines base
    bool right = true;
    glLineWidth(8);
    glBegin(GL_LINES);
    for(int i = 240; i<420; i+=30)
    {
        if(right == true)
        {
            glVertex2f(700, i);
            glVertex2f(750, i+30);
            right = false;
        }
        else
        {
           glVertex2f(750, i);
           glVertex2f(700, i+30);
           right = true;
        }
    }
    glEnd();

    //top part
    glBegin(GL_QUADS);
    glVertex2f(680, 420);
    glVertex2f(770, 420);
    glVertex2f(770, 470);
    glVertex2f(680, 470);
    glEnd();

    //cross lines hand
    bool up = true;
    glLineWidth(8);
    glBegin(GL_LINES);
    for(int i = 770; i<950; i+=30)
    {
        if(up == true)
        {
            glVertex2f(i, 430);
            glVertex2f(i+30, 460);
            up = false;
        }
        else
        {
           glVertex2f(i, 460);
           glVertex2f(i+30, 430);
           up = true;
        }
    }
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    //body
    glVertex2f(700, 240);
    glVertex2f(700, 420);
    glVertex2f(750, 240);
    glVertex2f(750, 420);
    //hand
    glVertex2f(770, 430);
    glVertex2f(950, 430);
    glVertex2f(770, 460);
    glVertex2f(920, 460);

    //hand wire left
    glColor3f(0.18, 0.12, 0.15);
    glVertex2f(890, 425);
    glVertex2f(915, 370);
    glVertex2f(940, 425);
    glVertex2f(915, 370);
    glEnd();

    //hand wire base
    glBegin(GL_QUADS);
    glVertex2f(900, 370);
    glVertex2f(930, 370);
    glVertex2f(930, 380);
    glVertex2f(900, 380);
    glEnd();

    //hand wire round
    float wireRadius = 15.0f;
    int numSegments = 30;

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 1.0f * M_PI * i / numSegments;
        glVertex2f(915 + wireRadius * cos(angle + M_PI * 1), 375 + wireRadius * sin(angle - M_PI * 1));
    }
    glEnd();

    //hook
    glBegin(GL_LINES);
    glVertex2f(915, 375);
    glVertex2f(915, hookLength);
    glEnd();

    //base
    if(night == false) glColor3f(0.58, 0.58, 0.58);
    else glColor3f(0.353, 0.310, 0.318);
    glBegin(GL_QUADS);
    glVertex2f(680, 230);
    glVertex2f(770, 230);
    glVertex2f(770, 240);
    glVertex2f(680, 240);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

	drawSky();
	drawWater();
	drawLand();

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

    if(night)
    {
        drawBatman(590, 580, 2.0f);
    }

    drawBgBuildings();

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

	glPushMatrix();
    glTranslatef(moveWave, 0.0f, 0.0f);
	drawWave(25, 60, 100, "dark");
    drawWave(185, 95, 200, "light");
    drawWave(225, 30, 100, "dark");
    drawWave(400, 115, 350, "dark");
    drawWave(525, 60, 100, "dark");
    drawWave(685, 95, 200, "light");
    drawWave(725, 30, 100, "dark");
    drawWave(900, 35, 350, "dark");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(moveWave2, 0.0f, 0.0f);
    drawWave(-900, 65, 250, "light");
	drawWave(-1100, 25, 200, "dark");
	drawWave(-1200, 95, 150, "dark");
	drawWave(-100, 35, 250, "light");
	drawWave(-300, 75, 200, "dark");
	drawWave(-400, 105, 150, "dark");
	glPopMatrix();

	glPushMatrix();
    glTranslatef(580, 0.0f, 0.0f);
    drawPortBuilding();
    glPopMatrix();

	drawContainer(600, 230, "b");
	drawContainer(700, 230, "p");
	drawContainer(800, 230, "r");
	drawContainer(900, 230, "p");
    drawContainer(1200, 230, "r");
    drawContainer(1300, 230, "b");
	drawContainer(850, 280, "y");
	if(night == false)
    {
        drawContainer(400, 230, "y");
        drawContainer(500, 230, "r");
        drawContainer(300, 230, "p");
        drawContainer(1100, 230, "y");
        drawContainer(1000, 230, "b");
        drawContainer(1050, 280, "b");
        drawContainer(1150, 280, "y");
        drawContainer(1300, 280, "p");
        drawContainer(1100, 330, "r");
        drawContainer(320, 280, "r");
        drawContainer(430, 280, "b");
        drawContainer(580, 280, "y");
        drawContainer(730, 280, "p");
    }

	drawCrane();

	if (night == false)
    {
        glPushMatrix();
        glTranslatef(moveShip, -50.0f, 0.0f);
        drawShip();
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(80, 0.0f, 0.0f);
        drawShip();
        glPopMatrix();
    }

    if(night)
    {
        glPushMatrix();
        glScalef(0.7f, 0.7f, 1.0f);
        glTranslatef(movePirateShip, -70.0f, 0.0f);
        drawPirateShip();
        glPopMatrix();
    }

    if(!night)
    {
        glPushMatrix();
        glTranslatef(birdmove1, 0.0f, 0.0f);
        drawBird(100, 500);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(birdmove4, 0.0f, 0.0f);
        drawBird(700, 480);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(birdmove5, 0.0f, 0.0f);
        drawBird(900, 520);
        glPopMatrix();
    }

	//glutSwapBuffers();
	glFlush();
}

void playSound(const std::string& soundFile) {
    PlaySound(soundFile.c_str(), NULL, SND_ASYNC | SND_FILENAME);
}
// stop sound
void stopSound() { PlaySound(NULL, NULL, 0); }

bool playing = true;

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'N':
        case 'n':
            night = true;
            stopSound();
            if(playing) playSound("pirates.wav");
            break;
        case 'D':
        case 'd':
            night = false;
            stopSound();
            if(playing) playSound("day-2.wav");
            break;
        case ' ':
            moveWave_factor = 0.0f;
            moveCloud_factor = 0.0f;
            moveShip_factor = 0.0f;
            moveBird_factor = 0.0f;
            movePirateShip_factor = 0.0f;
            hookLength_changeFactor = 0.0f;
            moveContainer_factor = 0.0f;
            break;
        case 'S':
        case 's':
            moveWave_factor = 0.5f;
            moveCloud_factor = 1.0f;
            if(moveShip < 80) moveShip_factor = 2.0f;
            moveBird_factor = 2.0f;
            movePirateShip_factor = -2.0f;
            hookLength_changeFactor = 0.5f;
            moveContainer_factor = 0.5f;
            break;
        case 'R':
        case 'r':
            restart();
            break;
        case 'M':
        case 'm':
            playing = !playing;
            if(!playing) stopSound();
            if(playing && night == false)
            {
                stopSound();
                playSound("day-2.wav");
            }
            else if(playing && night == true)
            {
                stopSound();
                playSound("pirates.wav");
            }
            break;
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN)
        {
            moveWave_factor = 3*0.5f;
            moveCloud_factor = 3*1.0f;
            if(moveShip < 80) moveShip_factor = 3*2.0f;
            else if(moveShip > 80) moveShip_factor = 0.0f;
            moveBird_factor = 3*2.0f;
            if(moveContainer < 125) moveContainer_factor = 3*0.5f;
            else if(moveContainer > 125 ) moveContainer_factor = 0.0f;
            hookLength_changeFactor = 3*0.5f;
            movePirateShip_factor = -3*2.0f;
        }

        else if (state == GLUT_UP)
        {
            moveWave_factor = 0.5f;
            moveCloud_factor = 1.0f;
            if(moveShip < 80) moveShip_factor = 2.0f;
            else if(moveShip > 80) moveShip_factor = 0.0f;
            moveBird_factor = 2.0f;
            if(moveContainer < 125) moveContainer_factor = 0.5f;
            else if(moveContainer > 125) moveContainer_factor = 0.0f;
            hookLength_changeFactor = 0.5f;
            movePirateShip_factor = -2.0f;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN)
        {
            moveWave_factor = 0.5*0.5f;
            moveCloud_factor = 0.5*1.0f;
            if(moveShip < 80) moveShip_factor = 0.5*2.0f;
            else if(moveShip > 80) moveShip_factor = 0.0f;
            moveBird_factor = 0.5*2.0f;
            if(moveContainer < 125) moveContainer_factor = 0.5*0.5f;
            else if(moveContainer > 125 ) moveContainer_factor = 0.0f;
            hookLength_changeFactor = 0.5*0.5f;
            movePirateShip_factor = -0.5*2.0f;
        }

        else if (state == GLUT_UP)
        {
            moveWave_factor = 0.5f;
            moveCloud_factor = 1.0f;
            if(moveShip < 80) moveShip_factor = 2.0f;
            else if(moveShip > 80) moveShip_factor = 0.0f;
            moveBird_factor = 2.0f;
            if(moveContainer < 125) moveContainer_factor = 0.5f;
            else if(moveContainer > 125 ) moveContainer_factor = 0.0f;
            hookLength_changeFactor = 0.5f;
            movePirateShip_factor = -2.0f;
        }
    }
}

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0,1400,0,750);
}
int main(int argc, char** argv) {

    cout << endl << endl;
    cout << ".-------------------------------------------------------------.\n";
    cout << "|             MD. ATIKUR RAHMAN - 22-47944-2                  |\n";
    cout << ".-------------------------------------------------------------.\n";
    cout << "| KEY / MOUSE INPUT        | ACTION                           |\n";
    cout << ".-------------------------------------------------------------.\n";
    cout << "| 'N' or 'n'               | Transition to night              |\n";
    cout << "| 'D' or 'd'               | Transition to day                |\n";
    cout << "| Space                    | Stop scenery                     |\n";
    cout << "| 'S' or 's'               | Start scenery                    |\n";
    cout << "| 'R' or 'r'               | Restart scenery                  |\n";
    cout << "| 'M' or 'm'               | Stop/play music                  |\n";
    cout << "| Hold 'LEFT' Mouse        | Speed 3x                         |\n";
    cout << "| Hold 'RIGHT' Mouse       | Speed 0.5x                       |\n";
    cout << "| Esc                      | Exit App                         |\n";
    cout << ".-------------------------------------------------------------.\n";
    cout << "| GitHub Link: https://github.com/Atik471/Sea-Port-freeglut   |\n";
    cout << ".-------------------------------------------------------------.\n";



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1400, 750);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Sea port");

    playSound("day-2.wav");

    myInit();

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutTimerFunc(10, updateStars, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseCallback);

    glutMainLoop();

    return 0;
}
