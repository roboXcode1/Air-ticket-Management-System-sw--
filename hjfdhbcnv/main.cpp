#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
#include<iostream>
#include<cstring>
#include <stdlib.h>//random-num
using namespace std;
char text1[] = "PINAK-6";
char text2[] = "VUTU";
char text3[] = "X";
void text( float x, float y, char *st)
{
    int l,i;


    l=strlen( st );
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }


}

void SpecialInput(int key, int x, int y);
int _angle1 = 0;
int _carMove=0;
int _carangle = 0;
float _angle2 = 1;
int _boatMove = 0;
int _planeMove = 0;
int _planeMove2 = 0;
bool isDay = true;
bool fullscreen=true;

 int speed_delay = 20;   // car movement speed
    int tire_delay = 5;     // tire rotation speed

    bool isAnimationOn = true;   // animation ON/OFF control


//k.press
 void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
            isDay = true;
            glutPostRedisplay();
            break;
        case 'n':
            isDay = false;
            glutPostRedisplay();
            break;
        case 'f': // fullscreen toggle
            fullscreen = !fullscreen;
            if (fullscreen)
                glutFullScreen();
            else {
                glutReshapeWindow(1200, 900);
                glutPositionWindow(0,0);
            }
            break;

        // new: increase car & tire speed
        case 'h':
            if (speed_delay > 4) speed_delay -= 4;
            if (tire_delay > 1) tire_delay -= 1;
            break;

        // new: decrease car & tire speed
        case 'l':
            speed_delay += 4;
            tire_delay += 1;
            break;

    }
}
//mouse
void mouseControl(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        // Left বা Right click এ animation toggle হবে
        if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON)
        {
            isAnimationOn = !isAnimationOn;
        }
    }
}





float TireRotateAngle = 0.0f;
float TruckTireRotateAngle = 0.0f;
int _TruckMoveReverse = 0;

//float TireRotateAngle = 0.0f;
void CarTire(int xx, int yy, float r)//C028//V048//L066//H102
{
    glMatrixMode(GL_MODELVIEW);
 glPushMatrix();
glTranslatef(0.0f,0.0f,0.0f);
glRotatef(TireRotateAngle, 0.0f, 0.0f,1.0f);
glTranslatef(-0.0f,-0.0f,0.0f);
glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
    for (int i = 0; i < 200; i++)
    {
        // glColor3ub(255, 215, 0);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        // float r = 4.0f;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xx, y + yy);
    }
    glEnd();
    glBegin(GL_LINES);
    glColor3ub(0,0,0);//black-rim
    glVertex2f(-0.075,0);
    glVertex2f(0.075,0);

    glVertex2f(-0.05,-0.075);
    glVertex2f(0.05,0.075);

    glVertex2f(0.05,-0.075);
    glVertex2f(-0.05,0.075);

    glVertex2f(0,-0.1);
    glVertex2f(0,0.1);

    glEnd();

    glPopMatrix();

}
void ScaledTire()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(140.1,95,0);
    glScalef(80,80,0);
    glColor3ub(0,0,0);//black-tire
    CarTire(0, 0, 0.2);
    glColor3ub(192,192,192);//silver-tire-rim
    CarTire(0,0,0.13);
    glColor3ub(211,211,255);//grey-tire-rim
    CarTire(0,0,0.09);
    glPopMatrix();
}
//car
void CarBody()
{

    glColor3f(0.1373, 0.5725, 0.5529); //body
    //glColor3f(0.2, 0.95, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(240, 127);
    glVertex2f(240, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 127);
    glVertex2f(130, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //back-light
    glColor3ub(255, 0, 0);
    glVertex2f(110, 92);
    glVertex2f(115, 92);
    glVertex2f(115, 117);
    glVertex2f(110, 117);
    glEnd();

    glBegin(GL_POLYGON); //window
    glColor3ub(0, 0, 0);//black-window-in=day
    if(!isDay)
    glColor3ub(163, 228, 215);//gray-window-in-night


    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(120, 127);
    glVertex2f(130, 127);
    glEnd();

    glBegin(GL_POLYGON); //window-Divider
    glColor3ub(192, 192, 192);
    glVertex2f(170, 152);
    glVertex2f(165, 152);
    glVertex2f(165, 127);
    glVertex2f(170, 127);
    glEnd();

    glBegin(GL_POLYGON); //roof-plate
    glColor3ub(168, 169, 173);

    glVertex2f(140, 152);
    glVertex2f(190, 152);
    glVertex2f(185, 157);
    glVertex2f(140, 157);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-front
    glColor3ub(168, 169, 173);
    glVertex2f(190, 152);
    glVertex2f(215, 127);
    glVertex2f(210, 127);
    glVertex2f(185, 152);
    glEnd();

    glBegin(GL_POLYGON); //window-holder-back
    glColor3ub(168, 169, 173);
    glVertex2f(140, 157);
    glVertex2f(115, 127);
    glVertex2f(125, 127);
    glVertex2f(140, 152);
    glEnd();

    glBegin(GL_POLYGON); //foot-holder
    glColor3ub(168, 169, 173);
    glVertex2f(242, 92);
    glVertex2f(110, 92);
    glVertex2f(110, 97);
    glVertex2f(242, 97);

    glEnd();

    glBegin(GL_POLYGON);      //mirror
    glColor3f(0.3, 0.9, 0.6); //body
    //glColor3ub(255,250,0);
    glVertex2f(211.5, 134.5);
    glVertex2f(204.5, 135.5);
    glVertex2f(203.5, 129);
    glVertex2f(210.5, 127);
    glEnd();

    glBegin(GL_POLYGON);      //Yellow-headlight
    glColor3f(1.0, 1.0, 0.0); //body
    //glColor3ub(255,250,0);
    glVertex2f(210.5+28, 134.5-10);
    glVertex2f(203.5+28, 135.5-10);
    glVertex2f(203.5+28, 129-10);
    glVertex2f(210.5+28, 127-10);
    glEnd();
    if(!isDay)
    {
        glBegin(GL_POLYGON);      //Yellow-headlight
        glColor3f(1.0, 1.0, 1.0); //body
        glVertex2f(210.5+28+90, 134.5-10-0);
        glVertex2f(205.5+28, 134.5-10);
        glColor3f(0.8, 0.9, 0.0);
        glVertex2f(205.5+28, 127-10);
        glVertex2f(210.5+28+90, 127-10-30);
        glEnd();

    }

    glBegin(GL_POLYGON); //window-opener-1
    glColor3ub(192, 192, 192);
    glVertex2f(150-15-5, 127-5-3);
    glVertex2f(155-5-5, 127-5-3);
    glVertex2f(155-5-5, 129-5);
    glVertex2f(150-15-5, 129-5);
    glEnd();
    glBegin(GL_POLYGON); //window-opener-2
    glColor3ub(192, 192, 192);
    glVertex2f(150-15+40, 127-5-3);
    glVertex2f(155-5+40, 127-5-3);
    glVertex2f(155-5+40, 129-5);
    glVertex2f(150-15+40, 129-5);
    glEnd();
}
void CarThrust()
{
    glBegin(GL_POLYGON);
    glColor3ub(168, 169, 173);
    glVertex2f(110, 92);
    glColor3ub(255, 255, 255);
    glVertex2f(00, 80);
    glVertex2f(00, 110);
    glColor3ub(0, 0, 0);
    glVertex2f(110, 97);
    glEnd();

}
void fullCar()
{

    CarBody();
    ScaledTire();
    glPushMatrix();
    glTranslatef(65,0,0);
    ScaledTire();
    glPopMatrix();

}
void CarForward()
{
    glLineWidth(1);

    glTranslatef(-450.5, 0, 0);
    fullCar();
}
void ScaledCarForward()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(10,40,0);
    glScalef(0.5,0.5,0);
    CarForward();
    glPopMatrix();

}
void ScaledCarReverse()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(10,40,0);
    glScalef(-0.5,0.5,0);
    CarForward();
    glPopMatrix();

}
void MovingScaledCarForward()
{
    glMatrixMode(GL_MODELVIEW);

     //init();
    glPushMatrix();
   // glTranslatef(-100.5, 0, 0);
    glTranslatef((_carMove / 2) % 850, 0, 0);

    ScaledCarForward();
    glPopMatrix();
    //glutSwapBuffers();
}
void MovingScaledCarReverse()
{
    glMatrixMode(GL_MODELVIEW);

     //init();
    glPushMatrix();
    glTranslatef(600.5, 0, 0);
    glTranslatef((-_carMove / 2) % 1000, 0, 0);

    ScaledCarReverse();
    glPopMatrix();
    //glutSwapBuffers();
}
void MoveCarForward(int value)
{
    if (isAnimationOn)
        _carMove += 1;

    glutPostRedisplay();
    glutTimerFunc(speed_delay, MoveCarForward, 0);
}


void TireRotate(int value)
{
    if (isAnimationOn)
        TireRotateAngle -= 5.0f;

    glutPostRedisplay();
    glutTimerFunc(tire_delay, TireRotate, 0);
}




void update(int value)
{
    if (isAnimationOn)
    {
        _angle1 += 1.0f;
        _boatMove += 1;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void update1(int value)
    {


        _angle2 -= 1.0f;
        glutPostRedisplay(); //Notify GLUT that the display has changed

        glutTimerFunc(20, update, 0); //Notify GLUT to call update again in 25 milliseconds
    }

//village
class Village
{
  public:

    void TreeBody()//tree-1//V047
    {
        glColor3ub(210.0f, 105.0, 30.0);//RGB chocholate
        glBegin(GL_QUADS);//body
        glVertex2f(90, (10 + (-10 * 2.0f)));
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 0.0f)));
        glVertex2f(((0.80 * 10) + 100), (10 + (10 * 8.0f)));
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 6.0f)));
        glEnd();

        glColor3ub(139.0, 69.0, 19.0);//RGB_saddle-brown
        glBegin(GL_TRIANGLES);//Left_Branch
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 6.0f)));
        glVertex2f(((-3.5 * 10) + 100), (10 + (10 * 9.0f)));
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 5.4f)));
        glEnd();

        glBegin(GL_TRIANGLES);//Right_Branch
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 5.8f)));
        glVertex2f(((5.0 * 10) + 100), (10 + (10 * 11.5f)));
        glVertex2f(((0.7 * 10) + 100), (10 + (10 * 5.3f)));
        glEnd();

        glColor3ub(139.0, 69.0, 19.0);//RGB_saddle-brown
        glBegin(GL_TRIANGLES);//Right_root
        glVertex2f(((0.5 * 10) + 100), (10 + (10 * 0.0f)));
        glVertex2f(((0.4 * 10) + 100), (10 + (10 * 1.0f)));
        glVertex2f(((4.0 * 10) + 100), (10 + (10 * 0.0f)));
        glEnd();

        glBegin(GL_TRIANGLES);//Left_root
        glVertex2f(((-0.5 * 10) + 100), (10 + (10 * 0.5f)));
        glVertex2f(((-0.4 * 10) + 100), (10 + (10 * 1.5f)));
        glVertex2f(((-4.0 * 10) + 100), (10 + (10 * 0.0f)));
        glEnd();

    }
    void Leaf()
    {

        glBegin(GL_POLYGON);// Draw a green circle centered at up left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 5)));
            float q = (10 + (10 * (10 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON);// Draw a green circle centered at upper left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON);// Draw a green circle centered at up Right
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) + 5)));
            float q = (10 + (10 * (10 + r * sin(A))));
            glVertex2f(p, q);
        }


        glEnd();

        glBegin(GL_POLYGON);// Draw a green circle centered at upper left
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) - 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON);// Draw a green circle centered at upper right
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 3.5;
            float p = (100 + (10 * ((r * cos(A)) + 4)));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }
        glEnd();

        glBegin(GL_POLYGON);// Draw a green circle centered at up middle
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(54.0f, 128.0f, 45.0f);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 5.5;
            float p = (100 + (10 * (r * cos(A))));
            float q = (10 + (10 * (13 + r * sin(A))));
            glVertex2f(p, q);
        }

        glEnd();


    }
    //trees
    void Tree() {

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(200, 380, 0);
        glScalef(0.25, 0.25, 0);
        TreeBody();
        Leaf();
        for (int treeNo = 1; treeNo < 9; treeNo++)
        {
            glTranslatef(120 + (treeNo * 10), 0, 0);
            TreeBody();
            Leaf();

        }

        glPopMatrix();
    }
//mountain
    void Mountain()
    {
        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(85, 430);
        glColor3ub(14, 89, 7);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glColor3ub(72, 36, 20);
        glVertex2f(170, 300);
        // glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glColor3ub(12, 20, 30);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(0, 300);
        glEnd();

        glBegin(GL_POLYGON);

        glColor3ub(79, 92, 89);
        glVertex2f(160, 360);
        glColor3ub(14, 89, 7);
        // glColor3ub(90, 113, 125);
        glVertex2f(260, 480);
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glColor3ub(72, 36, 20);
        glVertex2f(380, 300);
        glColor3ub(12, 20, 30);
        glVertex2f(200, 300);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(107, 107, 71);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(500, 370);
        glVertex2f(500, 300);
        glVertex2f(380, 300);
        glEnd();
    }


    void SmallMountain(int x, int y)
    {
        glBegin(GL_POLYGON);
        glColor3ub(46, 43, 43);
        glVertex2f(0 + x, 370 + y);
        glVertex2f(15 + x, 400 + y);
        glVertex2f(30 + x, 360 + y);
        glVertex2f(0 + x, 350 + y);
        glEnd();
    }

    void outliner()
    {
        glLineWidth(3);
        glBegin(GL_LINES);
        glColor3ub(0, 0, 0);
        glVertex2f(0, 350);
        glVertex2f(80, 450);
        glVertex2f(80, 450);
        glVertex2f(140, 380);
        glVertex2f(140, 380);
        glVertex2f(170, 300);
        glVertex2f(90, 435);
        glVertex2f(100, 455);
        glVertex2f(100, 455);
        glVertex2f(200, 300);
        glVertex2f(260, 480);
        glVertex2f(330, 360);
        glVertex2f(330, 360);
        glVertex2f(380, 300);
        glVertex2f(330, 360);
        glVertex2f(420, 450);
        glVertex2f(420, 450);
        glVertex2f(500, 370);

        glEnd();
    }

    void scaledmountain()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(.5, .5, 0);
        glTranslatef(500, 502, 0);
        Mountain();
        glPopMatrix();
    }
//road11

    void Roadbody()
    {
        //int x = 0, y = 0;


        glBegin(GL_POLYGON);
        glColor3ub(204, 122, 0);
        glVertex2f(500, 180);
        glColor3ub(153, 61, 0);
        glVertex2f(500, 150);
        glColor3ub(255, 170, 0);
        glVertex2f(0, 150);
        glColor3ub(179, 89, 0);
        glVertex2f(0, 180);


        glEnd();
        ;

    }
    void road()
    {

        Roadbody();

    }
    void circle(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
       // glColor3ub(252, 186, 3);     //midday sun color palatte
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
  //river
    void river()
    {
        glLineWidth(2.5);
        glBegin(GL_LINES);
        glColor3ub(128, 150, 0);
        glVertex2f(0, 400);
        glVertex2f(500, 400);
        glEnd();
        /*  glBegin(GL_POLYGON);*/
        glColor3ub(60, 188, 255);

        glBegin(GL_POLYGON);
        glVertex2f(0, 140);
        glVertex2f(200, 130);
        glVertex2f(500, 110);
        glVertex2f(500, 0);
        glVertex2f(0, 0);
        glEnd();

        glLineWidth(5);
        glBegin(GL_LINES);
        glColor3ub(255, 128, 0);
        glVertex2f(0, 140);
        glVertex2f(200, 130);
        glVertex2f(200, 130);
        glVertex2f(500, 110);
        glEnd();

        glBegin(GL_QUADS);      //riverbank
        glColor3ub(11, 20, 9);
        glVertex2f(0, 150);
        glColor3ub(160, 137, 98);
        glVertex2f(0, 141);
        glColor3ub(75, 101, 54);
        glVertex2f(500, 112);
        glColor3ub(92, 52, 20);
        glVertex2f(500, 150);
        glEnd();



    }
    //star
        void star()//V040
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(255, 251, 251); //white-star
        glVertex2f(-0.075, 0);
        glVertex2f(0.075, 0);

        glVertex2f(-0.05, -0.075);
        glVertex2f(0.05, 0.075);

        glVertex2f(0.05, -0.075);
        glVertex2f(-0.05, 0.075);

        glVertex2f(0, -0.1);
        glVertex2f(0, 0.1);

        glEnd();
    }
    void scaledstar()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(05, 490, 0);
        glScalef(15, 15, 0);
        star();
        glPopMatrix();
    }
    void scaledstarLoop()
    {
        scaledstar();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(5, 0, 0);

        for (int i = 0; i < 3; i++)
        {
            glTranslatef(0, -20, 0);
            scaledstar();
            for (int i = 0; i < 40; i++)
            {
                if (i % 2 == 0)
                {
                    glTranslatef(15, -35, 0);
                    scaledstar();
                }
                else
                {
                    glTranslatef(18, 35, 0);
                    scaledstar();
                }
            }
            glTranslatef(-660, -35, 0);
        }
        glPopMatrix();
    }
    //d.sky
    //n.sky
    void sky()             //village sunset
    {

        glBegin(GL_QUADS);
        if (isDay) {

            glColor3ub(247, 191, 190);
            glVertex2f(0, 400);
            glColor3ub(244, 107, 105);
            glVertex2f(500, 400);
            glColor3ub(239, 88, 86);
            glVertex2f(500, 500);
            glColor3ub(247, 65, 59);
            glVertex2f(0, 500);
            glEnd();
        }
        else {
            glColor3ub(0, 0, 0);
            glVertex2f(0, 400);

            glVertex2f(500, 400);

            glVertex2f(500, 500);

            glVertex2f(0, 500);
            glEnd();
           scaledstarLoop();
        }


    }
    void sunmoon()
    {
        if (isDay) {
            glColor3ub(255, 51, 51);    //midday sun effect
    //glColor3ub(128, 128, 128);
            circle(150, 400, 20);
        }
        else
        {
            glColor3ub(255, 255, 255);
            circle(140, 440, 25);
        }
    }
    void BoatBodyStick()//boitha
    {
        glBegin(GL_LINES);
        glColor3ub(165, 42, 42);//brown-stick
        glVertex2f(210, 75);
        glVertex2f(220, 10);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0);//brown-stick
        glVertex2f(218, 20);
        glVertex2f(220, 10);
        glVertex2f(230, 10);
        glEnd();

    }
    void BoatBodyShell()//V051
    {
        glBegin(GL_POLYGON);
        glColor3ub(165, 42, 42);//brown-shell
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glVertex2f(195, 55);
        glVertex2f(125, 55);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(255, 255, 0);//yellow-shell-stripe-pattern
        glVertex2f(120, 30);
        glVertex2f(200, 30);

        glVertex2f(121, 35);
        glVertex2f(199, 35);

        glVertex2f(122, 40);
        glVertex2f(198, 40);

        glVertex2f(123, 45);
        glVertex2f(197, 45);

        glVertex2f(124, 50);
        glVertex2f(196, 50);

        glVertex2f(125, 55);
        glVertex2f(195, 55);


        glEnd();


    }
    //boat
    void BoatBody()
    {
        glBegin(GL_QUADS);
        glColor3ub(0, 0, 0);//black-base
        glVertex2f(120, 10);
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(120, 30);
        glEnd();
        glBegin(GL_TRIANGLES);//black-nose-front
        glVertex2f(120, 10);
        glVertex2f(120, 30);
        glVertex2f(80, 40);
        glEnd();
        glBegin(GL_TRIANGLES);//black-nose-back
        glVertex2f(200, 10);
        glVertex2f(200, 30);
        glVertex2f(240, 40);
        glEnd();

        glBegin(GL_POLYGON);//yellow-inside-shape
        glColor3ub(255, 255, 0);
        glVertex2f(240, 40);
        glVertex2f(80, 40);
        glVertex2f(120, 30);
        glVertex2f(200, 30);
        glEnd();

        glBegin(GL_LINES);
        glColor3b(0, 0, 0);//black_stripe

        glVertex2f(205, 30);
        glVertex2f(200, 40);

        glVertex2f(210, 30);
        glVertex2f(205, 40);

        glVertex2f(215, 30);
        glVertex2f(210, 40);

        glVertex2f(220, 30);
        glVertex2f(215, 40);

        glVertex2f(225, 30);
        glVertex2f(220, 40);

        //
        glVertex2f(115, 30);
        glVertex2f(120, 40);

        glVertex2f(110, 30);
        glVertex2f(115, 40);

        glVertex2f(105, 30);
        glVertex2f(110, 40);

        glVertex2f(100, 30);
        glVertex2f(105, 40);

        glVertex2f(95, 30);
        glVertex2f(100, 40);

        glEnd();
        BoatBodyShell();
        BoatBodyStick();
    }
    void Boat()
    {
        BoatBody();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(10, 110, 0);
        glScalef(0.8, 0.8, 0);
        // glRotatef(-3, 0, 0, 1);
        BoatBody();
        glPopMatrix();
    }

//house1
    void House1()
    {

        glColor3ub(149, 160, 125); //body

        //triangle
        glBegin(GL_POLYGON);
        glVertex2f(50, 250);
        glVertex2f(125, 350);
        glVertex2f(200, 250);
        glEnd();

        //hut // roof
       // glColor3ub(76, 92, 85);
        glColor3ub(204, 68, 0);  // komlar choto vai
        glBegin(GL_POLYGON);
        glVertex2f(125, 350);
        glVertex2f(263, 370);
        glVertex2f(400, 350);
        glColor3ub(179, 60, 0);
        glVertex2f(500, 250);
        glVertex2f(210, 230);
        glEnd();

        //hut       //western part
        glColor3ub(92, 92, 61);
        glBegin(GL_POLYGON);
        glVertex2f(75, 250);
        glVertex2f(220, 250);
        //glColor3ub(134, 89, 45);
        glColor3ub(166, 197, 103);
        glVertex2f(225, 100);
        glVertex2f(79, 100);
        // glVertex2f(200, 250);
        glEnd();

        //hut   //front door
        glColor3ub(200, 165, 130);
        //glColor3ub(124, 188, 108);
        glBegin(GL_POLYGON);
        glVertex2f(220, 250);
        glColor3ub(157, 147, 92);
        glVertex2f(459, 250);
        glVertex2f(460, 100);
        glVertex2f(225, 100);
        // glVertex2f(200, 250);
        glEnd();


    }
   // h1winll
    void h1win11()
    {
        glPushMatrix();
        glTranslatef(-40, -25, 0);
        glBegin(GL_QUADS);
        int j = 0;
        if (isDay) glColor3ub(40, 40, 40);
        else glColor3ub(255, 255, 102);
        for (int i = 1; i < 3; i++)
        {

            glVertex2f(282 + j, 417);
            glVertex2f(292 + j, 417);
            glVertex2f(292 + j, 407);
            glVertex2f(282 + j, 407);
            j += 12;
        }
        glEnd();
        glPopMatrix();

        glBegin(GL_QUADS);
        glVertex2f(217, 390);
        glVertex2f(224, 391);
        glVertex2f(224, 375);
        glVertex2f(217, 374);
        glEnd();
    }
    //hut
    void Hut()  //V032
    {
        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(30, 150);
        glVertex2f(90, 150);
        glColor3ub(125, 65, 6);
        glVertex2f(110, 220);
        glVertex2f(50, 220);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(159, 90, 20);
        glVertex2f(130, 154);
        glColor3ub(125, 65, 6);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(110, 220);
        glEnd();

        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(125, 65, 6);
        glVertex2f(110, 220);
        glVertex2f(130, 154);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(35, 150);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(90, 70);
        glVertex2f(35, 80);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(159, 90, 20);
        glVertex2f(130, 154);
        glVertex2f(90, 150);
        glColor3ub(228, 193, 113);
        glVertex2f(90, 70);
        glVertex2f(130, 80);
        glEnd();

        glLineWidth(0.5);
        glBegin(GL_LINES);  //BORDER
        glColor3ub(0, 0, 0);
        glVertex2f(90, 150);
        glVertex2f(90, 70);
        //glVertex2f(90, 70);
        //glVertex2f(130, 80);
        glVertex2f(130, 80);
        glVertex2f(130, 154);
        glEnd();

        glBegin(GL_QUADS); //window
        if (isDay)glColor3ub(62, 62, 40);
        else glColor3ub(243, 237, 65);
        glVertex2f(45, 150);
        glVertex2f(80, 150);
        glVertex2f(80, 95);
        glVertex2f(45, 100);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(253, 151, 49);
        glVertex2f(45, 150);
        glColor3ub(193, 127, 60);
        glVertex2f(80, 150);
        glColor3ub(94, 49, 5);
        glVertex2f(75, 120);
        glColor3ub(112, 69, 25);
        glVertex2f(40, 123);
        glEnd();

        glLineWidth(8);  // lower shed
        glBegin(GL_LINES);
        glColor3ub(125, 65, 6);
        glVertex2f(131, 75);
        glVertex2f(90, 66);
        glEnd();

        glBegin(GL_QUADS); //door
        if (isDay)
            glColor3ub(102, 0, 0);
        glVertex2f(125, 154);
        glVertex2f(95, 150);
        glVertex2f(95, 70);
        glVertex2f(126, 78);
        glEnd();

        glLineWidth(0.5);
        glBegin(GL_LINES);  //BORDER
        glColor3ub(0, 0, 0);
        glVertex2f(90, 70);
        glVertex2f(130, 80);
        glEnd();

        glLineWidth(5); //bamboo
        glBegin(GL_LINES);
        glColor3ub(151, 105, 31);
        glVertex2f(115, 112);
        glVertex2f(115, 60);
        glEnd();
        // glLineWidth(10);
        glBegin(GL_LINES);
        glColor3ub(151, 105, 31);
        glVertex2f(144, 115);
        glVertex2f(144, 70);
        glEnd();

        glBegin(GL_QUADS);  //shed
        glColor3ub(253, 151, 49);
        glVertex2f(125, 154);
        glColor3ub(193, 127, 60);
        glVertex2f(95, 150);
        glColor3ub(94, 49, 5);
        glVertex2f(115, 110);
        glColor3ub(112, 69, 25);
        glVertex2f(145, 115);
        glEnd();

        glLineWidth(13);
        glBegin(GL_QUADS);
        glColor3ub(125, 65, 6);
        glVertex2f(35, 79);
        glVertex2f(90, 69);
        glVertex2f(90, 60);
        glVertex2f(35, 70);
        glEnd();

        //BORDERS

        glLineWidth(0.5);

        glBegin(GL_LINES); //roof
        glColor3ub(0, 0, 0);
        glVertex2f(30, 150);
        glVertex2f(90, 150);
        glVertex2f(90, 150);
        glVertex2f(110, 220);
        glVertex2f(110, 220);
        glVertex2f(50, 220);
        glVertex2f(50, 220);
        glVertex2f(30, 150);
        glEnd();

        glBegin(GL_LINES); //roof
        glColor3ub(0, 0, 0);
        glVertex2f(130, 154);
        glVertex2f(90, 150);
        glVertex2f(90, 150);
        glVertex2f(110, 220);
        glEnd();

        glBegin(GL_LINES);  //body
        glColor3ub(0, 0, 0);
        glVertex2f(90, 150);
        glVertex2f(90, 70);
        glVertex2f(90, 70);
        glVertex2f(35, 80);
        glVertex2f(35, 80);
        glVertex2f(35, 150);
        glEnd();

        glBegin(GL_LINES); //shed
        glColor3ub(0, 0, 0);
        glVertex2f(80, 150);
        glVertex2f(75, 120);
        glVertex2f(75, 120);
        glVertex2f(40, 123);
        glVertex2f(40, 123);
        glVertex2f(45, 150);
        glEnd();

        glBegin(GL_LINES); //shed
        glColor3ub(0, 0, 0);
        glVertex2f(95, 150);
        glVertex2f(115, 110);
        glVertex2f(115, 110);
        glVertex2f(145, 115);
        glVertex2f(145, 115);
        glVertex2f(125, 154);
        glEnd();

    }
    //house2
    void farmhouse()
    {
        glBegin(GL_POLYGON);      //front 2nd floor
        glColor3ub(255, 26, 26);
        glVertex2f(360, 440);
        glVertex2f(380, 420);
        glVertex2f(380, 402);
        // glColor3ub(125, 65, 6);
        glVertex2f(342, 404);
        glVertex2f(342, 425);
        glEnd();

        glBegin(GL_QUADS);      //side 2nd floor
        glColor3ub(255, 26, 26);
        glVertex2f(380, 422);
        glVertex2f(417, 422);
        // glColor3ub(125, 65, 6);
        glVertex2f(417, 402);
        glVertex2f(380, 402);
        glEnd();


        glBegin(GL_POLYGON);      //front 1st floor
        glColor3ub(255, 26, 26);
        glVertex2f(343, 404);
        glVertex2f(380, 402);
        glVertex2f(390, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 352);
        glVertex2f(333, 354);
        glVertex2f(333, 394);
        glEnd();


        glBegin(GL_QUADS);      //side 1st floor
        glColor3ub(255, 26, 26);
        glVertex2f(390, 392);
        glVertex2f(427, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(427, 352);
        glVertex2f(390, 352);
        glEnd();

        glBegin(GL_QUADS);      //top roof
        glColor3ub(153, 0, 0);
        glVertex2f(360, 440);
        glVertex2f(400, 440);
        // glColor3ub(125, 65, 6);
        glVertex2f(420, 420);
        glVertex2f(380, 420);
        glEnd();

        glBegin(GL_QUADS);      //lower roof
        glColor3ub(153, 0, 0);
        glVertex2f(380, 402);
        glVertex2f(420, 402);
        glVertex2f(430, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 392);

        glEnd();


        glBegin(GL_QUADS);         // windows
        if (isDay) {
            glColor3ub(55, 55, 55);
        }
        else
        {
            glColor3ub(255, 255, 77);
        }
        glVertex2f(345, 424);
        glVertex2f(358, 424);
        glVertex2f(358, 409);
        glVertex2f(345, 409);

        glVertex2f(362, 424);
        glVertex2f(375, 424);
        glVertex2f(375, 409);
        glVertex2f(362, 409);

        int j = 0;
        for (int i = 1; i < 4; i++)
        {

            glVertex2f(382 + j, 417);
            glVertex2f(392 + j, 417);
            glVertex2f(392 + j, 407);
            glVertex2f(382 + j, 407);
            j += 12;
        }

        glVertex2f(392, 382);
        glVertex2f(407, 382);
        glVertex2f(407, 362);
        glVertex2f(392, 362);

        glVertex2f(410, 382);
        glVertex2f(410, 362);
        glVertex2f(425, 362);
        glVertex2f(425, 382);



        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(255, 26, 26);
        glVertex2f(360, 440);
        glVertex2f(380, 420);
        glVertex2f(380, 402);
        glEnd();

        glLineWidth(4);
        glBegin(GL_LINES);
        glColor3ub(153, 0, 0);
        glVertex2f(360, 438);
        glVertex2f(340, 425);
        glEnd();

        glLineWidth(2);
        glBegin(GL_LINE_STRIP);
        glColor3ub(255, 255, 255);
        glVertex2f(344, 399);
        glVertex2f(362, 353);
        glVertex2f(344, 354);
        glVertex2f(362, 398);
        glVertex2f(362, 354);
        glVertex2f(379, 398);
        glVertex2f(362, 398);
        glVertex2f(378, 353);
        glVertex2f(378, 398);
        glVertex2f(362, 398);
        glVertex2f(344, 399);
        glVertex2f(344, 354);
        glEnd();
        glLineWidth(1);         //border
        glBegin(GL_LINES);
        glColor3ub(38, 38, 38);
        glVertex2f(380, 420);
        glVertex2f(380, 352);
        glVertex2f(390, 392);   //side 1st
        glVertex2f(390, 352);
        glVertex2f(427, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(427, 352);
        glVertex2f(390, 352);
        glVertex2f(427, 352);
        // front 1st
        glVertex2f(343, 404);
        glVertex2f(380, 402);
        glVertex2f(390, 392);
        // glColor3ub(125, 65, 6);
        glVertex2f(390, 352);
        glVertex2f(390, 352);
        glVertex2f(333, 354);
        glVertex2f(333, 354);
        glVertex2f(333, 394);
        glVertex2f(333, 394);
        glVertex2f(343, 404);
        glVertex2f(342, 404);
        glVertex2f(342, 425);
        glVertex2f(342, 404);
        glVertex2f(342, 354);



        glEnd();
    }
    void Houses()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(200, 360, 0);
        glScalef(0.15, 0.15, 0);
        House1();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(400, 250, 0);
        glScalef(0.58, 0.4, 0);
        Hut();
        glPopMatrix();
        farmhouse();
        h1win11();

    }
    void wellcircle()
    {
        glLineWidth(7.5);
        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            //glColor3f(1.0, 1.0, 1.0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            float r = 50;
            float x = r * cos(A);
            float y = r / 2 * sin(A);
            glVertex2f(x, y);
        }



        glEnd();
    }
    void PlaceCircles()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(210, 200, 0);
        glColor3ub(255, 0, 0);
        wellcircle();
        glTranslatef(0, -60, 0);
        glColor3ub(255, 255, 0);
        wellcircle();
        glTranslatef(0, 60, 0);
        glScalef(0.85, 0.85, 0);
        glColor3ub(153, 206, 255);  //water
        wellcircle();
        glPopMatrix();
    }
    //well
    void Well()
    {
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex2f(160, 200);
        glVertex2f(260, 200);
        glVertex2f(260, 140);
        glVertex2f(160, 140);
        glEnd();
        PlaceCircles();

        glLineWidth(2);
        glBegin(GL_LINES);//bamboo
        glColor3ub(98, 52, 18);
        glVertex2f(160 + 4, 200);
        glVertex2f(160 + 4, 200 + 120);

        glVertex2f(260 - 4, 200);
        glVertex2f(260 - 4, 200 + 120);

        glVertex2f(160 - 4, 260);
        glVertex2f(260 + 4, 260);
        glEnd();

        glBegin(GL_QUADS);//Shade
        glColor3ub(98, 52, 18);
        glVertex2f(160 - 20, 200 + 120);

        glVertex2f(260 + 20, 200 + 120);

        glVertex2f(260, 200 + 120 + 70);

        glVertex2f(160, 200 + 120 + 70);
        glEnd();

    }
    void scaledwell()
    {
        glPushMatrix();
        glTranslatef(170, 250, 0);
        glScalef(0.25, 0.2, 0);
        Well();
        glPopMatrix();
    }
    //field
    void field()
    {
        glBegin(GL_POLYGON);
        glColor3ub(51, 150, 51);
        glVertex2f(0, 400);
        //  glColor3ub(236, 217, 14);
        glColor3ub(179, 0, 0);
        glVertex2f(200, 400);
        glColor3ub(136, 159, 40);
        glVertex2f(180, 185);
        glColor3ub(204, 204, 0);
        glVertex2f(0, 185);
        glEnd();


        glBegin(GL_QUADS);
        glColor3ub(107, 232, 23);
        glVertex2f(195, 340);
        glVertex2f(200, 400);
        glVertex2f(500, 400);
        glVertex2f(500, 300);

        glColor3ub(186, 159, 4);
        glVertex2f(195, 340);
        glVertex2f(500, 300);
        glVertex2f(500, 200);
        glVertex2f(187, 250);

        glColor3ub(0, 125, 12);
        glVertex2f(187, 250);
        glVertex2f(182, 182);
        glVertex2f(500, 182);
        glVertex2f(500, 250);
        glEnd();

        glBegin(GL_LINES);          //field divider
        glColor3ub(99, 66, 0);
        for (int i = 0; i < 5; i++)
        {
            glVertex2f(40 + (i * 40), 400);
            glVertex2f(36 + (36 * i), 185);
        }
        glEnd();
        glLineWidth(12);
        glBegin(GL_LINES);
        glColor3ub(0, 125, 12);
        glVertex2f(187, 250);
        glVertex2f(181, 182);
        glVertex2f(500, 182);
        glVertex2f(500, 250);
        glEnd();

        glLineWidth(8);
        glBegin(GL_LINES);
        glColor3ub(99, 66, 0);
        glVertex2f(0, 183);
        glVertex2f(180, 183);
        glLineWidth(6);
        glVertex2f(180, 182);
        glVertex2f(500, 182);
        glEnd();


        /*   glFlush();*/
    }
//wavewave
    void Wave(float waveX, float waveY, float waveA, float waveB)//V050
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef((_angle1%20), 0.0f, 0.0f);
        float pi = 3.1416;
        float r = 50;
        for (int waveCol = 0; waveCol < 10; waveCol++)
        {


            for (int waveRow = 0; waveRow < 10; waveRow++)
            {
                glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
                for (int i = 0; i < 200; i++)
                {
                    glColor3ub(66, 135, 245);

                    float A = (i * pi) / 200;

                    float x = (waveX + (waveA * r * 2 * cos(A)));
                    float y = (waveY + (waveB * r * sin(A)));
                    glVertex2f(x, y);

                }
                glEnd();
                waveX = (waveX + 100) * waveA;
            }
            waveY = 0;
        }
        glPopMatrix();

    }
    //river
    void River() {

        float waveX = 00, waveY = 0;//Position
        float waveA = 1, waveB = 0.5;//Scale

        //for(int waveRow=0;waveRow<5;)
        {
            Wave(waveX, waveY, waveA, waveB);
            Wave(.1, 40, 1, 1);
            // Wave(.1, 20, 1, 1);
             //waveY=waveY+100;
        }


    }
    //corn
    void Corn()
    {
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);//yellow//Corn
        glVertex2f(92.5 - 5, 180 + 40);//top-leaf-mid
        glVertex2f(100, 275 + 90 + 40);
        glVertex2f(107.5 + 5, 180 + 40);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0, 1, 0);//green//Corn-stick
        glVertex2f(98, 275 - 80 + 20 + 20);
        glVertex2f(102, 275 - 80 + 20 + 20);
        glVertex2f(102 + 5, 275 - 200 + 20);
        glVertex2f(98 - 5, 275 - 200 + 20);
        glEnd();

        glBegin(GL_LINES);
        glColor3ub(210, 105, 30);
        glVertex2f(100, 275 + 80 + 40);//brown-divider
        glVertex2f(100, 180 + 40);

        glVertex2f(92.5, 180 + 40);//brown-left
        glVertex2f(100, 275 + 80 + 40);

        glVertex2f(107.5, 180 + 40);////brown-right
        glVertex2f(100, 275 + 80 + 40);

        glVertex2f(92.5 + 5, 285 + 40);
        glVertex2f(107.5 - 5, 285 + 40);

        glVertex2f(92.5 + 2, 275 + 40);
        glVertex2f(107.5 - 2, 275 + 40);


        glVertex2f(92.5 + 2, 265 + 40);
        glVertex2f(107.5 - 2, 265 + 40);


        glVertex2f(92.5 + 2, 255 + 40);
        glVertex2f(107.5 - 2, 255 + 40);

        glVertex2f(92.5 + 2, 245 + 40);
        glVertex2f(107.5 - 2, 245 + 40);

        glVertex2f(92.5 + 2, 235 + 40);
        glVertex2f(107.5 - 2, 235 + 40);



        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
        glVertex2f(87.5 + 8, 100 + 80 + 40);//Corn-leaf-left
        glVertex2f(75 + 8, 225 + 80 + 40);
        glVertex2f(100 + 8, 100 + 80 + 40);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5 - 8, 100 + 80 + 40);//Corn-leaf-right
        glVertex2f(125 - 8, 225 + 80 + 40);
        glVertex2f(100 - 8, 100 + 80 + 40);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(87.5, 100 + 50);//mid-leaf-left
        glVertex2f(75 - 10, 225 + 50 + 50);
        glVertex2f(100, 100 + 50);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5, 100 + 50);//mid-leaf-right
        glVertex2f(125 + 10, 225 + 50 + 50);
        glVertex2f(100, 100 + 50);
        glEnd();
    }
    void CornLeaf()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glColor3ub(0, 255, 0);
        glScalef(0.2f, 0.1f, 0.0f);
        glBegin(GL_TRIANGLES);//low-leaf-left
        glVertex2f(75 + 10, 100);
        glVertex2f(50 + 10, 175 + 85);
        glVertex2f(100 + 10, 100);
        glEnd();
        glBegin(GL_TRIANGLES);//low-leaf-right
        glVertex2f(125 - 10, 100);
        glVertex2f(150 - 10, 175 + 85);
        glVertex2f(100 - 10, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(87.5, 100);//mid-leaf-left
        glVertex2f(75, 225 + 112);
        glVertex2f(100, 100);
        glEnd();

        glBegin(GL_TRIANGLES);
        glVertex2f(112.5, 100);//mid-leaf-right
        glVertex2f(125, 225 + 112);
        glVertex2f(100, 100);
        glEnd();




        Corn();
        glPopMatrix();
    }
    void CornLeafloop()
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        for (int col = 0; col < 10; col++)
        {

            glTranslatef(-15.0f, 360.0f, 0.0f);   //for once
            CornLeaf();
            for (int time = 0; time < 12; time++)
            {
                glTranslatef(15.0f, 0.0f, 0.0f);
                CornLeaf();
                //  glTranslatef(0, -100, 0);
            }
            glTranslatef(-166.0f, -380.0f, 0.0f);   //for once
        }
        glPopMatrix();
    }
    void Face()//V058
    {
        glBegin(GL_POLYGON);
        for (int i = 0; i < 200; i++)
        {
            glColor3ub(160, 82, 45);//brown-pitcher
            float pi = 3.1416;
            float A = (2 * pi * i) / 200;
            float r = 25.5;
            float x = 250 + r * cos(A);
            float y = 250 + r * sin(A);
            glVertex2f(x, y);
        }
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(160, 82, 45);//brown-pitcher-neck
        glVertex2f(240, 220);
        glVertex2f(260, 220);
        glVertex2f(260, 240);
        glVertex2f(240, 240);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0);//black_eyes
        if(!isDay)
        {
           glColor3ub(255, 0, 0);//red_eyes
        }
        glVertex2f(250, 250);
        glVertex2f(240, 245);
        glVertex2f(235, 270);
        glEnd();
        glBegin(GL_TRIANGLES);
        glColor3ub(0, 0, 0);//black_eyes
        if(!isDay)
        {
           glColor3ub(255, 0, 0);//red_eyes
        }
        glVertex2f(250, 250);
        glVertex2f(260, 245);
        glVertex2f(265, 270);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3ub(255, 255, 255);//white_mouth

        glVertex2f(240, 238);
        glVertex2f(250, 235);
        glVertex2f(260, 238);
        glEnd();
    }
    void Skeleton()
    {

        glBegin(GL_POLYGON);              // Each set of 4 vertices form a quad
        glColor3f(0.0f, 0.0f, 0.0f); // black-backbone
        glVertex2f(248.0f, 40.0f);    // x, y
        glVertex2f(248.0f, 230.0f);    // x, y
        glVertex2f(252.0f, 230.0f);    // x, y
        glVertex2f(252.0f, 40.0f);    // x, y
        glEnd();
        Face();
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f); // yellow
        glVertex2f(160.0f, 190.0f);    // x, y
        glVertex2f(340.0f, 190.0f);    // x, y
        glVertex2f(340.0f, 170.0f);    // x, y
        glVertex2f(160.0f, 170.0f);    // x, y

        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 0.0f); // green-color
        glVertex2f(235.0f, 215.0f);    // x, y
        glVertex2f(265.0f, 215.0f);    // x, y
        glVertex2f(265.0f, 200.0f);
        glVertex2f(235.0f, 200.0f);    // x, y
        glEnd();


        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan-left-sleeves
        glVertex2f(220.0f, 200.0f);    // x, y
        glVertex2f(200.0f, 200.0f);    // x, y
        glVertex2f(200.0f, 160.0f);
        glVertex2f(220.0f, 160.0f);    // x, y
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan-right-sleeves
        glVertex2f(280.0f, 200.0f);    // x, y
        glVertex2f(300.0f, 200.0f);    // x, y
        glVertex2f(300.0f, 160.0f);
        glVertex2f(280.0f, 160.0f);    // x, y
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0f, 1.0f, 1.0f); // cyan
        glVertex2f(285, 200);    // x, y
        glVertex2f(215, 200);    // x, y
        glVertex2f(215, 100);
        glVertex2f(285, 100);    // x, y
        glEnd();
        glColor3b(0,0,0);
        text(210.0,140.0,text2);

    }
   // void GhostEffect()
   // {
      //  for(int i = 0; i<20; i++)
      ///  glTranslatef((rand()/4 ) % 500-200,(-rand() / 2) % 500+300,0);
   // }
    void ScareCrow()//V058
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(20, 300, 0);
        glScalef(.25, 0.25, 0);
        if(!isDay)//ghosteffect
        {
           // GhostEffect();
        }
        Skeleton();

        glPopMatrix();
    }

    void blades()
    {
        glBegin(GL_POLYGON);          //blade
        glColor3ub(255, 255, 255);
        glVertex2f(257, 370);
        glVertex2f(267, 430);
        glVertex2f(284, 490);
        glVertex2f(280, 430);
        glVertex2f(261, 363);
        glEnd();

    }
    void windmill()
    {
        glBegin(GL_QUADS);          //body
        glColor3ub(255, 255, 255);
        glVertex2f(250, 50);
        glVertex2f(260, 50);
        glVertex2f(257, 350);
        glVertex2f(253, 350);
        glEnd();


        glPushMatrix();

        glTranslatef(255, 360, 0);
        glRotatef(_angle1, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);


        blades();//1st
        glPushMatrix();
        glTranslatef(255, 360, 0);
        glRotatef(120, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);
        blades();//2nd
        glPopMatrix();


        glPushMatrix();
        glTranslatef(255, 360, 0);
        glRotatef(240, 0.0f, 0.0f, 1.0f);
        glTranslatef(-255, -360, 0);
        blades();   //3rd blade
        glPopMatrix();


        glPopMatrix();

    }

    void circle1(int xx, int yy, float r)
    {

        glBegin(GL_POLYGON); // Draw a Red 1x1 Square centered at origin
        for (int i = 0; i < 200; i++)
        {
            // glColor3ub(255, 215, 0);
            float pi = 3.1416;
            float A = (i * 2 * pi) / 200;
            // float r = 4.0f;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x + xx, y + yy);
        }
        glEnd();
    }
    void scaledmill()
    {
        glPushMatrix();
        glTranslatef(05, 310, 0);
        glScalef(0.25, 0.25, 0);
        windmill();
        circle1(255, 360, 10);
        glPopMatrix();
    }


    void showvillage(void)
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(5);

        sky();
        sunmoon();
        river();
        road();

        scaledmountain();
//        Grassloop();
        field();
        Tree();
        Houses();
        River();
        Boat();
        CornLeafloop();
        scaledmill();
        ScareCrow();
        scaledwell();
        //CarForward();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(0,80,0);
        MovingScaledCarForward();
        glPopMatrix();
        glFlush();
    }

};


void  displayVillage()
{
     Village obj;
    obj.showvillage();

}
void redisplayVillage()
{
    glutDestroyWindow(1);
    glClearColor(0.63f, 0.85f, 0.85f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    glutInitWindowSize(640, 640);
    glutCreateWindow("my Village"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    glutFullScreen();
    glutDisplayFunc(displayVillage); // Register display callback handler for window re-paint
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress);
}
void SpecialInput(int key, int x, int y)
{
switch(key)
{
case GLUT_KEY_UP:
//do something here
redisplayVillage();
break;

}
glutPostRedisplay();
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
    glutInit(&argc, argv);                 // Initialize GLUT
    glutInitWindowSize(640, 640);
    glutCreateWindow("My Village(OVI)"); // Create a window with the given title
    gluOrtho2D(0, 500, 0, 500);
    // gluOrtho2D(-1000, 1000, -1000, 1000);
    glutFullScreen();
    glutDisplayFunc(displayVillage);
 // Register display callback handler for window re-paint
    glutTimerFunc(20, update, 0); //Add a timer
    glutTimerFunc(20,MoveCarForward,0);//moves car forward
    glutTimerFunc(20,TireRotate,0);//moves tire forward
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(mouseControl);

    //glLoadIdentity();
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}
