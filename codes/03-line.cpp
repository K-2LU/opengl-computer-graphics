#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <bits/stdc++.h>

using namespace std;


vector<pair<int, int>> dda(pair<double, double> p1, pair<double, double> p2) {
    vector<pair<int, int>> ans;

    double dx = p2.first - p1.first;
    double dy = p2.second - p1.second;

    int steps = max(abs(dx), abs(dy));
    double x_inc = dx / steps;
    double y_inc = dy / steps;

    double x = p1.first;
    double y = p1.second;

    for (int i = 0; i <= steps; i++) {
        ans.push_back({round(x), round(y)});
        x += x_inc;
        y += y_inc;
    }

    return ans;
}


vector<pair<int, int>> brasenham(pair<double, double> p1, pair<double, double> p2) {
    vector<pair<int, int>> ans;

    int x1 = round(p1.first), y1 = round(p1.second);
    int x2 = round(p2.first), y2 = round(p2.second);

    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int d = 2*dy - dx;
    int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    for (int x = x1; x <= x2; x++) {
        if (steep)
            ans.push_back({y, x});
        else
            ans.push_back({x, y});

        if (d < 0) {
            d += 2*dy;
        }   else    {
            y += ystep;
            d += 2*(dy-dx);
        }
    }

    return ans;
}

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    pair<double, double> p1 = {-70., 40};
    pair<double, double> p2 = {70., 20};

    vector<pair<int, int>> points = dda(p1, p2);

    // draw stuff
    glPointSize(2.0);
    glBegin(GL_POINTS);

    for (auto point: points)    {
        glVertex2f(point.first, point.second);
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
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);               // specify window position
    glutInitWindowSize(500, 500);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}