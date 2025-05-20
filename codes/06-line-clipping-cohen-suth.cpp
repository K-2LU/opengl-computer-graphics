#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

const int x_min = -100, y_min = -100;
const int x_max = 100, y_max = 100;

const int numLines = 7;
double lines[numLines][4] = {
    {-150, 50, 150, 50},   // Crosses horizontally
    {-120, -80, 80, 130},  // Diagonal
    {0, -150, 0, 150},     // Vertical through the center
    {50, -50, 150, -150},  // Partially outside
    {-180, 80, -120, 40},  // Fully outside
    {-90, -90, 90, 90},    // Diagonal inside
    {110, 110, 130, 130}   // Completely outside
};
double clippedLines[numLines][4];

enum codes {
    INSIDE  = 0,    // 0000
    LEFT    = 1,    // 0001
    RIGHT   = 2,    // 0010
    BOTTOM  = 4,    // 0100
    UP      = 8     // 1000
};

int regionCode(double x, double y)  {
    int code = INSIDE;

    if (x < x_min)      code |= LEFT;
    if (x > x_max)      code |= RIGHT;
    if (y < y_min)      code |= BOTTOM;
    if (y > y_max)      code |= UP;

    return code;
}

bool cohenSutherland(double &x1, double &y1, double &x2, double &y2)    {
    int code1 = regionCode(x1, y1);
    int code2 = regionCode(x2, y2);
    bool ac = false;

    while (true)    {
        if (!code1 && !code2)   {
            ac = true;
            break;
        }   else if (code1 & code2)   {
            break;
        }   else    {
            double x, y;
            int outsideCode = code1 ? code1 : code2;
            double slope = (x2-x1) != 0 ? (y2-y1) / (x2-x1) : 1e9;

            if (outsideCode & UP) {
                x = x1 + (y_max - y1) / slope;
                y = y_max;
            } else if (outsideCode & BOTTOM) {
                x = x1 + (y_min - y1) / slope;
                y = y_min;
            } else if (outsideCode & RIGHT) {
                y = y1 + slope * (x_max - x1);
                x = x_max;
            }   else if (outsideCode & LEFT) {
                y = y1 + slope * (x_min - x1);
                x = x_min;
            }
            

            if (outsideCode == code1)  {
                x1 = x;
                y1 = y;
                code1 = regionCode(x1, y1);
            }   else    {
                x2 = x;
                y2 = y;
                code2 = regionCode(x2, y2);
            }
        }
    }
    return ac;
}

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();

    // original lines
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)  {
        glVertex2f(lines[i][0], lines[i][1]);
        glVertex2f(lines[i][2], lines[i][3]);
    }
    glEnd();

    // cohen sutherland
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)  {
        clippedLines[i][0] = lines[i][0];
        clippedLines[i][1] = lines[i][1];
        clippedLines[i][2] = lines[i][2];
        clippedLines[i][3] = lines[i][3];

        bool visible = cohenSutherland(clippedLines[i][0], clippedLines[i][1], clippedLines[i][2], clippedLines[i][3]);

        if (visible)    {
            glVertex2f(clippedLines[i][0], clippedLines[i][1]);
            glVertex2f(clippedLines[i][2], clippedLines[i][3]);
        }
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);               // R G B
}

void reshape(int w, int h)  {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(100, 100);               // specify window position
    glutInitWindowSize(500, 500);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}