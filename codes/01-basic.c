#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    // draw stuff
    glPointSize(5.0);
    glBegin(GL_POINTS);
    int initX, initY;
    initX = 0;
    initY = 10;
    for (int i = 0; i < 5; i++) {
        glVertex2f(initX, initY);
        glVertex2f(-initX, initY);
        initX += 2;
        initY -= 2;
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
    gluOrtho2D(-10, 10, -10, 10);
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