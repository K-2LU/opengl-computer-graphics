#include <GL/glut.h>

float           tx              =       0.0f;
float           scale           =       1.0f;
const float     scaleFactor     =       1.25f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPushMatrix();
        glTranslatef(tx, 0.0f, 0.0f);
        glScalef(scale, scale, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(-20.0f, -25.0f);
        glVertex2f( 20.0f, -25.0f);
        glVertex2f( 20.0f,  25.0f);
        glVertex2f(-20.0f,  25.0f);
        glEnd();
    glPopMatrix();

    glFlush();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            tx += 40.0f;
            scale *= scaleFactor;
            break;
        case GLUT_KEY_LEFT:
            tx -= 40.0f;
            scale /= scaleFactor;
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Group 0");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
