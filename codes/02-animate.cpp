#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float x_position = -10;
int state = 1;

void display()  {
    glClear(GL_COLOR_BUFFER_BIT);                   // clear any previous
    glLoadIdentity();

    // draw stuff
    glBegin(GL_POLYGON);

    glVertex2f(x_position, 1.0);
    glVertex2f(x_position, -1.0);
    glVertex2f(x_position+2.0, -1.0);
    glVertex2f(x_position+2.0, 1.0);
    
    glEnd();

    glutSwapBuffers();
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

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);               // call itself 60 fps

    switch(state)   {
        case 1:
            if (x_position < 8) x_position += .15;
            else    state = -1;
            break;
        case -1:
            if (x_position > -10) x_position -= .15;
            else    state = 1;
            break;
    }
}

int main(int argc, char **argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);               // specify window position
    glutInitWindowSize(500, 500);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);                     // ms, func(void), arg
    init();
    glutMainLoop();
}