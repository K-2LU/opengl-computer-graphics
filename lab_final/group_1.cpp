#include <GL/glut.h>
#include <math.h>

#define MAX_BULLETS 100

float tankX = 50, tankY = 50;
float angle = 0;
float speed = 1.0;

struct Bullet
{
    float x, y, angle;
    int active;
};

Bullet bullets[MAX_BULLETS];
int bulletCount = 0;

int isInsideBox(float x, float y)
{
    return (x >= 5 && x <= 95 && y >= 5 && y <= 95);
}

void drawTank()
{
    float w = 6, h = 10;

    glPushMatrix();
    glTranslatef(tankX, tankY, 0);
    glRotatef(angle, 0, 0, 1);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-w, -h);
    glVertex2f(w, -h);
    glVertex2f(w, h);
    glVertex2f(-w, h);
    glEnd();

    // Barrel
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, h + 5);
    glEnd();

    glPopMatrix();
}

void drawBullets()
{
    int i;
    glColor3f(1.0, 1.0, 0.0);
    for (i = 0; i < bulletCount; i++)
    {
        if (bullets[i].active)
        {
            glBegin(GL_POINTS);
            glVertex2f(bullets[i].x, bullets[i].y);
            glEnd();
        }
    }
}

void updateBullets()
{
    int i;
    float speed = 2.0;
    for (i = 0; i < bulletCount; i++)
    {
        if (bullets[i].active)
        {
            float rad = -bullets[i].angle * 3.14159 / 180; // Fixed: NEGATE angle
            bullets[i].x += speed * sin(rad);
            bullets[i].y += speed * cos(rad);

            if (!isInsideBox(bullets[i].x, bullets[i].y))
            {
                bullets[i].active = 0;
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw bounding box
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(5, 5);
    glVertex2i(95, 5);
    glVertex2i(95, 95);
    glVertex2i(5, 95);
    glEnd();

    drawTank();
    drawBullets();

    glFlush();
}

void timer(int value)
{
    updateBullets();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void specialKeys(int key, int x, int y)
{
    float rad = -angle * 3.14159 / 180;
    float nextX = tankX;
    float nextY = tankY;

    if (key == GLUT_KEY_UP)
    {
        nextX += speed * sin(rad);
        nextY += speed * cos(rad);
    }
    else if (key == GLUT_KEY_DOWN)
    {
        nextX -= speed * sin(rad);
        nextY -= speed * cos(rad);
    }
    else if (key == GLUT_KEY_LEFT)
    {
        angle += 5;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        angle -= 5;
    }

    if (isInsideBox(nextX, nextY))
    {
        tankX = nextX;
        tankY = nextY;
    }

    glutPostRedisplay();
}

void normalKeys(unsigned char key, int x, int y)
{
    if (key == ' ' && bulletCount < MAX_BULLETS)
    {
        float rad = -angle * 3.14159 / 180; // Fixed: NEGATE angle

        bullets[bulletCount].x = tankX + (10 + 5) * sin(rad);
        bullets[bulletCount].y = tankY + (10 + 5) * cos(rad);
        bullets[bulletCount].angle = angle;
        bullets[bulletCount].active = 1;
        bulletCount++;
    }
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    glOrtho(0, 100, 0, 100, -1, 1);
    glPointSize(4);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Simple Tank Game");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(normalKeys);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
