// By Rubayet Sadman Sami - 2019331063
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>

#define M_PI 3.14159265358979323846

// Time variables
int hours = 0;
int minutes = 0;
int seconds = 0;

void drawCircle(float xc, float yc, float r)
{
    float x = 0, y = r;
    float d = 1 - r;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    while (x <= y)
    {
        glVertex2d(x + xc, y + yc);
        glVertex2d(y + xc, x + yc);
        glVertex2d(-x + xc, y + yc);
        glVertex2d(-y + xc, x + yc);
        glVertex2d(x + xc, -y + yc);
        glVertex2d(y + xc, -x + yc);
        glVertex2d(-x + xc, -y + yc);
        glVertex2d(-y + xc, -x + yc);

        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glEnd();
}

void drawHand(float angle, float length, float width)
{
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(length * sin(angle), length * cos(angle));
    glEnd();
}

void updateHandAngles()
{
    // Convert time to angles
    // Hours: 360/12 = 30 degrees per hour
    // Minutes: 360/60 = 6 degrees per minute
    // Seconds: 360/60 = 6 degrees per second
    float hourAngle = (hours % 12) * 30 * M_PI / 180;
    float minuteAngle = minutes * 6 * M_PI / 180;
    float secondAngle = seconds * 6 * M_PI / 180;

    // Draw hands
    drawHand(secondAngle, 35, 1.0); // Second hand
    drawHand(minuteAngle, 30, 2.0); // Minute hand
    drawHand(hourAngle, 25, 3.0);   // Hour hand
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clock face
    drawCircle(0, 0, 40);

    // Update and draw hands
    updateHandAngles();

    glFlush();
}

void normalKeys(unsigned char key, int x, int y)
{
    if (key == ' ')
    {
        // Move time forward by 5 seconds
        seconds += 5;

        // Handle minute overflow
        if (seconds >= 60)
        {
            minutes += seconds / 60;
            seconds = seconds % 60;
        }

        // Handle hour overflow
        if (minutes >= 60)
        {
            hours += minutes / 60;
            minutes = minutes % 60;
        }

        // Handle 24-hour overflow
        hours = hours % 24;

        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Clock");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(normalKeys);
    glutMainLoop();
    return 0;
}