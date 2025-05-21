#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static GLfloat spin = 0.0;
static float tx = 0.0;
static float ty = 0.0;
static float auto_tx = 200.0;
static float auto_ty = 0.0;

bool dir = 1;

const int window_w = 500;
const int window_h = 500;

void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Controlled circle (keyboard & mouse)
    glPushMatrix();
        glTranslatef(tx, ty, 0);
        glRotatef(spin, 0.0, 0.0, 1.0);
        glColor3f(1.0, 1.0, 1.0);
        drawCircle(50.0f);
    glPopMatrix();

    // Auto-moving circle
    glPushMatrix();
        glTranslatef(auto_tx, auto_ty, 0);
        glColor3f(0.0, 1.0, 0.0);  // green for clarity
        drawCircle(50.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); // yellow line
    glBegin(GL_LINES);
        glVertex2f((auto_tx - tx)/2, (auto_ty - ty - 100)/2);
        glVertex2f((auto_tx - tx)/2, (auto_ty-ty+100)/2);
    glEnd();
glPopMatrix();

    glFlush();
}


void spinDisplay_left(void)
{
    spin = 5;
    glutPostRedisplay();
    glRotatef(spin, 0.0, 0.0, 1.0);
}

void spinDisplay_right(void)
{
    spin = -5;
    glutPostRedisplay();
    glRotatef(spin, 0.0, 0.0, 1.0);
}

void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glOrtho(-500.0, 500.0, -500.0, 500.0, -1.0, 1.0);
}

void my_keyboard(unsigned char key, int x, int y)
{
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

void auto_move_left()
{
    auto_tx -= 0.01;
}

void auto_move_right()
{
    auto_tx += 0.01;
}

void auto_move() {
    if (auto_tx + 25 > tx - 25 && auto_tx - 25 < tx + 25 && auto_ty + 25 > ty - 25 && auto_ty - 25 < ty + 25) {
        dir = !dir;
    }

    if (dir) {
        auto_move_right();
    } else {
        auto_move_left();
    }

    if (auto_tx < -window_w + 25 || auto_tx > window_w - 25)
        dir = !dir;

    glutPostRedisplay();
}

void spe_key(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_LEFT:
            auto_tx -= 5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            auto_tx += 5;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void my_mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay_left);
            break;
        case GLUT_MIDDLE_BUTTON:
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay_right);
            break;
        default:
            break;
    }
}


int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("mist");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(my_keyboard);
    glutSpecialFunc(spe_key);
    // glutIdleFunc(auto_move);

    glutMainLoop();
    return 0;
}
