#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

const int xmin      =   200;
const int ymin      =   250;
const int xmax      =   650;
const int ymax      =   650;

// viewport 
const int vxmin     =   20;
const int vymin     =   20;
const int vxmax     =   220;
const int vymax     =   120;

const double sx     =   (vxmax - vxmin * 1.0) / (xmax - xmin);
const double sy     =   (vymax - vymin * 1.0) / (ymax - ymin);

enum region {
    INSIDE      =   0,
    LEFT        =   1,
    RIGHT       =   2,
    BOTTOM      =   4,
    UP          =   8
};

int regionCode(double x, double y)  {
    int code = INSIDE;

    if (x < xmin)       code    |=  LEFT;
    if (x > xmax)       code    |=  RIGHT;
    if (y < ymin)       code    |=  BOTTOM;
    if (y > ymax)       code    |=  UP;

    return code;
}


bool CohenSutherland(double &x1, double &y1, double &x2, double &y2)    {
    int code1       =       regionCode(x1, y1);
    int code2       =       regionCode(x2, y2);
    bool ac         =       false;

    while (1)   {
        if (!code1 && !code2)   {
            ac = true;
            break;
        }   else if (code1 & code2) {
            break;
        }   else    {
            double x, y;
            int outsideCode = code1 ? code1 : code2;
            double slope = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 1e9;

            if (outsideCode & UP)  {
                x = x1 + (ymax - y1) / slope;
                y = ymax;
            }   else if (outsideCode & BOTTOM)  {
                x = x1 + (ymin - y1) / slope;
                y = ymin;
            }   else if (outsideCode & RIGHT)    {
                y = y1 + (xmax - x1) * slope;
                x = xmax;
            }   else if (outsideCode & LEFT)    {
                y = y1 + (xmin - x1) * slope;
                x = xmin;
            }

            if (outsideCode == code1)   {
                x1 = x;
                y1 = y;
                code1 = regionCode(x1,y1);
            }   else    {
                x2 = x;
                y2 = y;
                code2 = regionCode(x2, y2);
            }
        }
    }

    return ac;
}

pair<double, double> winToViewMap(double x, double y)   {
    double vx       =       sx * (x - xmin) + vxmin;
    double vy       =       sy * (y - ymin) + vymin;

    return {vx, vy};
}

const int numLines = 11;
double lines[numLines][4] =
{
    {100, 420, 320, 200},
    {320, 200, 600, 150},
    {600, 150, 825, 400},
    {825, 400, 675, 750},
    {675, 750, 675, 720},
    {675, 720, 600, 500},
    {600, 500, 600, 850},
    {600, 850, 400, 675},
    {400, 675, 325, 650},
    {325, 650, 250, 450},
    {250, 450, 100, 420}
};

double clipped[numLines][4];

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    // viewport
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(vxmin, vymin);
    glVertex2f(vxmax, vymin);
    glVertex2f(vxmax, vymax);
    glVertex2f(vxmin, vymax);
    glEnd();

    // window
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // original lines
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)  {
        glVertex2f(lines[i][0], lines[i][1]);
        glVertex2f(lines[i][2], lines[i][3]);
    }
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)  {
        clipped[i][0]    =      lines[i][0];
        clipped[i][1]    =      lines[i][1];
        clipped[i][2]    =      lines[i][2];
        clipped[i][3]    =      lines[i][3];

        bool visible = CohenSutherland(clipped[i][0], clipped[i][1], clipped[i][2], clipped[i][3]);

        if (visible)    {
            pair <double, double> p1    =       winToViewMap(clipped[i][0], clipped[i][1]);
            pair <double, double> p2    =       winToViewMap(clipped[i][2], clipped[i][3]);

            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(clipped[i][0], clipped[i][1]);
            glVertex2f(clipped[i][2], clipped[i][3]);

            glColor3f(0.0, 1.0, 1.0);
            glVertex2f(p1.first, p1.second);
            glVertex2f(p2.first, p2.second);
        }
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);               // R G B
}

void reshape(int w, int h)  {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10, 1000, -10, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);               // specify window position
    glutInitWindowSize(700, 700);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}