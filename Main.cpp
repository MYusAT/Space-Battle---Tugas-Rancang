#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "Header.h"
#include "Header1.h"

float pos = 0.1f;
float rotx = 0.0f;
float roty = 180.0f;
float xdwn = 0.0f;
float ydwn = 0.0f;
bool mousedwn = false;
static float posty = 0, postz = 0, postx = 0, posx = 0, posy = 0, posz = 0;
static float scalex = 1, scaley = 1, scalez = 1;


void idle()
{
    if (!mousedwn)
    {   //Rotasi 
        rotx += 0.4f;
        roty += 0.3f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{   //Fungsi Keyboard Zoom In dan Zoom Out
    if (key == 'w')
    {
        printf("\nw pressed");
        scalex += pos;
        scaley += pos;
        scalez += pos;
    }
    if (key == 's')
    {
        printf("\ns pressed");
        scalex -= pos;
        scaley -= pos;
        scalez -= pos;
    }
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {   //Fungsi mouse melakukan rotasi sesuai pointer
        mousedwn = true;
        xdwn = x - roty;
        ydwn = -y + rotx;
    }
    else
        mousedwn = false;
}

void mousemotion(int x, int y)
{   //Fungsi Merotasi Objek
    if (mousedwn)
    {
        roty = x - xdwn;
        rotx = y + ydwn;
        glutPostRedisplay();
    }
}

void cursorkey(int button, int x, int y)
{   //Fungsi tombol arah memindahkan objek sesuai arah
    if (button == GLUT_KEY_LEFT)
    {
        printf("\nleft pressed");
        posx = posx - 0.2f;
        glutPostRedisplay();
    }
    if (button == GLUT_KEY_RIGHT)
    {
        printf("\nright pressed");
        posx = posx + 0.2f;
        glutPostRedisplay();
    }
    if (button == GLUT_KEY_UP)
    {
        printf("\nup pressed");
        posy = posy + 0.2f;
        glutPostRedisplay();
    }
    if (button == GLUT_KEY_DOWN)
    {
        printf("\ndown pressed");
        posy = posy - 0.2f;
        glutPostRedisplay();
    }
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glClearDepth(1.0f);
    return;
}

void renderscene(void)
{   //Fungsi untuk memasukan koordinat dan texture pada file TGA dan NFG 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glTranslatef(posx, posy, posy);

    glScalef(scalex, scaley, scalez);
    glRotatef(postx, 1, 0, 0);
    glRotatef(posty, 0, 1, 0);
    glRotatef(postz, 0, 0, 1);

    glScalef(scalex, scaley, scalez);
    glRotatef(rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(roty, 0.0f, 1.0f, 0.0f);

    glColor3ub(255, 255, 255);
    float posx1 = 0, posx2, posx3, posy1, posy2, posy3, posz1, posz2, posz3, posu1, posu2, posu3, posv1, posv2, posv3;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int i = 0;
    while (i <= 717)    // Perulangan Mengisi Setiap Koordinat dan menampilkan Koordinatnya
    {
        posx1 = coorpost[indices[i].coorindix].copostx;
        posx2 = coorpost[indices[i].coorindiy].copostx;
        posx3 = coorpost[indices[i].coorindiz].copostx;
        posy1 = coorpost[indices[i].coorindix].coposty;
        posy2 = coorpost[indices[i].coorindiy].coposty;
        posy3 = coorpost[indices[i].coorindiz].coposty;
        posz1 = coorpost[indices[i].coorindix].copostz;
        posz2 = coorpost[indices[i].coorindiy].copostz;
        posz3 = coorpost[indices[i].coorindiz].copostz;
        posu1 = coorpost[indices[i].coorindix].uvx;
        posu2 = coorpost[indices[i].coorindiy].uvx;
        posu3 = coorpost[indices[i].coorindiz].uvx;
        posv1 = coorpost[indices[i].coorindix].uvy;
        posv2 = coorpost[indices[i].coorindiy].uvy;
        posv3 = coorpost[indices[i].coorindiz].uvy;

        glBegin(GL_POLYGON);
        glTexCoord2f(posu1, posv1); glVertex3f(posx1, posy1, posz1);
        glTexCoord2f(posu2, posv2); glVertex3f(posx2, posy2, posz2);
        glTexCoord2f(posu3, posv3); glVertex3f(posx3, posy3, posz3);
        glEnd();
        i++;
    }

    float mt1[] = { 0.2f, 0.5f, 0.8f, 1.0f };
    float mt2[] = { 0.3f, 0.5f, 0.6f, 1.0f };
    float mt3[] = { 0.4f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mt1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mt2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mt3);
    glPopMatrix();
    glutSwapBuffers();
}

void resize(int w1, int h1)
{
    glViewport(0, 0, w1, h1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{   //Rotasi Objek
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    if (!mousedwn)
    {
        roty += 2.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(250, 150);
    glutInitWindowSize(640, 480);
    glutCreateWindow("TR_GRAFKOM_672019033");
    init();
    load("Woman1.nfg");
    LoadTGA_custom("Woman1.tga");
    glutDisplayFunc(renderscene);
    glutReshapeFunc(resize);
    glutSpecialFunc(cursorkey);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(renderscene);
    glutTimerFunc(1, timer, 0);
    glutSwapBuffers();
    glutMainLoop();
}