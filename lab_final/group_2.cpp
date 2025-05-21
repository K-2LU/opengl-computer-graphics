#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static GLfloat          spin            =       0.0;
static float            tx              =       0.0;
static float            ty              =       0.0;
static float            mirrored_pos_x  =       200.0;
static float            mirrored_pos_y  =       0.0;
const int               window_w        =       500;
const int               window_h        =       500;

void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void display(void)  {
    glClear(GL_COLOR_BUFFER_BIT);

    // original circle
    glPushMatrix();
    glTranslatef(tx, ty, 0);
    glRotatef(spin, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(50.0f);
    glPopMatrix();

    // mirrorred circle
    glPushMatrix();
    glTranslatef(mirrored_pos_x, mirrored_pos_y, 0);
    glColor3f(0.0, 1.0, 0.0);  
    drawCircle(50.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); // yellow line - mirror
    glBegin(GL_LINES);
    glVertex2f((mirrored_pos_x - tx)/2, (mirrored_pos_y - ty - 100)/2);
    glVertex2f((mirrored_pos_x - tx)/2, (mirrored_pos_y-ty+100)/2);
    glEnd();
    glPopMatrix();

    glFlush();
}


void spinDisplay_left(void)     {
    spin = 5;
    glutPostRedisplay();
    glRotatef(spin, 0.0, 0.0, 1.0);
}

void spinDisplay_right(void)    {
    spin = -5;
    glutPostRedisplay();
    glRotatef(spin, 0.0, 0.0, 1.0);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
}

void my_keyboard(unsigned char key, int x, int y)   {
    switch (key) {
        case 'a':
            spinDisplay_left();
            break;
        case 'd':
            spinDisplay_right();
            break;
        case 's':
            glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

void spe_key(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            mirrored_pos_x -= 5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            mirrored_pos_x += 5;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("group_2");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(spe_key);

    glutMainLoop();
    return 0;
}
