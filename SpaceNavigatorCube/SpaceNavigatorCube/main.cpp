#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <iostream>

float shipX = 0.0f, shipY = 0.0f, shipZ = -5.0f;  // Spaceship position
float rotateX = 0.0f, rotateY = 0.0f;  // Rotation angles
bool perspective = true;  // Toggle perspective/parallel projection

void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective) {
        gluPerspective(60.0, 1.0, 1.0, 50.0); // Perspective Projection
    } else {
        glOrtho(-5, 5, -5, 5, 1, 50); // Parallel Projection
    }
    glMatrixMode(GL_MODELVIEW);
}

void drawSpaceship() {
    glPushMatrix();
    glTranslatef(shipX, shipY, shipZ);  // Move spaceship
    glRotatef(rotateX, 1, 0, 0);  // Rotate around X
    glRotatef(rotateY, 0, 1, 0);  // Rotate around Y
    
    // Draw a cube as spaceship
    glColor3f(0.5, 0.8, 1.0);
    glutWireCube(1);
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    setupProjection();

    // Set camera position
    gluLookAt(0, 0, 5, 0, 0, -1, 0, 1, 0);

    drawSpaceship();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': shipY += 0.1f; break;
        case 's': shipY -= 0.1f; break;
        case 'a': shipX -= 0.1f; break;
        case 'd': shipX += 0.1f; break;
        case 'q': shipZ += 0.1f; break;
        case 'e': shipZ -= 0.1f; break;
        case 'p': perspective = !perspective; break; // Toggle projection
        case 27: exit(0); // Escape key to exit
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: rotateY -= 5; break;
        case GLUT_KEY_RIGHT: rotateY += 5; break;
        case GLUT_KEY_UP: rotateX -= 5; break;
        case GLUT_KEY_DOWN: rotateX += 5; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Space Navigation Simulator");

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
