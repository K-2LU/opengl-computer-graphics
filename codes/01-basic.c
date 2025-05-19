#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display()  {}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);               // specify window position
    glutInitWindowSize(500, 500);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    
    glutMainLoop();
}