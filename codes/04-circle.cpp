#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void setPixel(int x, int y) {
    glVertex2f(x, y);
    glVertex2f(y, x);
    glVertex2f(-y, x);
    glVertex2f(-x, y);
    glVertex2f(-x, -y);
    glVertex2f(-y, -x);
    glVertex2f(y, -x);
    glVertex2f(x, -y);
    
}

void brasenham(int r) {
    int x = 0, y = r, d = 3 - 2*r;
    while (x <= y)  {
        setPixel(x, y);
        if (d < 0)  d = d + 4*x + 6;
        else {
            d = d + 4*(x - y) + 10;
            y--;
        }
        x++; 
    }
}

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    // draw stuff
    glPointSize(5.0);
    glBegin(GL_POINTS);
    brasenham(50);
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
    gluOrtho2D(-70, 70, -70, 70);
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