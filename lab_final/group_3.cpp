#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static GLfloat      spin    =   0.0;
static float        tx      =   0.0;
static float        ty      =   0.0;

enum Orientation {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int face = UP;

void drawTriangle() {
    glBegin(GL_LINE_LOOP);
    glVertex2f(-3.0, 0.0);
    glVertex2f(3.0, 0.0);
    glVertex2f(0.0, 5.0);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(tx, ty, 0.0);
    glRotatef(spin, 0.0, 0.0, 1.0);
    drawTriangle();
    glPopMatrix();

    glFlush();
}

void rotateToFace(int new_face) {
    int diff = 0;

    switch (new_face) {
        case UP:
            if (face == RIGHT) diff = 90;
            else if (face == DOWN) diff = 180;
            else if (face == LEFT) diff = -90;
            break;
        case DOWN:
            if (face == RIGHT) diff = -90;
            else if (face == UP) diff = 180;
            else if (face == LEFT) diff = 90;
            break;
        case LEFT:
            if (face == UP) diff = 90;
            else if (face == DOWN) diff = -90;
            else if (face == RIGHT) diff = 180;
            break;
        case RIGHT:
            if (face == UP) diff = -90;
            else if (face == DOWN) diff = 90;
            else if (face == LEFT) diff = 180;
            break;
    }

    spin += diff;
    face = new_face;
}

void spe_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (face != LEFT) {
                rotateToFace(LEFT);
            } else {
                tx -= 5;
            }
            break;

        case GLUT_KEY_RIGHT:
            if (face != RIGHT) {
                rotateToFace(RIGHT);
            } else {
                tx += 5;
            }
            break;

        case GLUT_KEY_UP:
            if (face != UP) {
                rotateToFace(UP);
            } else {
                ty += 5;
            }
            break;

        case GLUT_KEY_DOWN:
            if (face != DOWN) {
                rotateToFace(DOWN);
            } else {
                ty -= 5;
            }
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Triangle Rotation and Movement");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);

    glutMainLoop();
    return 0;
}
