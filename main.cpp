#include <GL/freeglut.h>
#include <GL/glu.h>
#include <cmath>

// Flag dimensions
const int FLAG_WIDTH = 30;
const int FLAG_HEIGHT = 20;

// Time variable for wave animation
float t = 0.0f;

// Function to draw the star in the center of the flag using lines
void drawStar(float cx, float cy, float radius, float innerRadius) {
    const int numPoints = 5;
    float angleStep = M_PI / numPoints;
    float startAngle = M_PI /2 ;

    glColor3f(2.0f, 2.0f, 0.0f); // White color for the star
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 2 * numPoints; ++i) {
        float angle = startAngle + i * angleStep;
        float r = (i % 2 == 0) ? radius : innerRadius;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to draw the blue circle with the star in the center of the flag
void drawBlueCircleWithStar(float cx, float cy, float radius, float starRadius, float starInnerRadius) {
    // Draw the blue circle
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2.0f * M_PI * i / 100;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw the white star in the center of the blue circle
    drawStar(cx, cy, starRadius, starInnerRadius);
}

// Function to draw the flag
void drawFlag() {
    float waveAmplitude = 0.25f; // Amplitude of the wave
    float waveFrequency = 1.0f; // Frequency of the wave

    // Colors of the Ethiopian flag
    GLfloat green[] = { 1.0f, 0.0f, 0.0f };  // Green color
    GLfloat yellow[] = { 1.0f, 1.0f, 0.0f }; // Yellow color
    GLfloat red[] = { 0.0f, 0.5f, 0.0f };    // Red color

    // Draw the flag with wave effect
    glBegin(GL_QUADS);

    // Green stripe
    glColor3fv(green);
    for (int x = 0; x < FLAG_WIDTH; x++) {
        for (int y = 1; y < FLAG_HEIGHT / 3; y++) {
            float wave = waveAmplitude * sin(waveFrequency * x + t);
            glVertex3f(x, y + wave, 0.0f);
            glVertex3f(x + 1, y + wave, 0.0f);
            glVertex3f(x + 1, y + 1 + wave, 0.0f);
            glVertex3f(x, y + 1 + wave, 0.0f);
        }
    }

    // Yellow stripe
    glColor3fv(yellow);
    for (int x = 0; x < FLAG_WIDTH; x++) {
        for (int y = FLAG_HEIGHT / 3; y < 2 * FLAG_HEIGHT / 3; y++) {
            float wave = waveAmplitude * sin(waveFrequency * x + t);
            glVertex3f(x, y + wave, 0.0f);
            glVertex3f(x + 1, y + wave, 0.0f);
            glVertex3f(x + 1, y + 1 + wave, 0.0f);
            glVertex3f(x, y + 1 + wave, 0.0f);
        }
    }

    // Red stripe
    glColor3fv(red);
    for (int x = 0; x < FLAG_WIDTH; x++) {
        for (int y = 2 * FLAG_HEIGHT / 3; y < FLAG_HEIGHT; y++) {
            float wave = waveAmplitude * sin(waveFrequency * x + t);
            glVertex3f(x, y + wave, 0.0f);
            glVertex3f(x + 1, y + wave, 0.0f);
            glVertex3f(x + 1, y + 1 + wave, 0.0f);
            glVertex3f(x, y + 1 + wave, 0.0f);
        }
    }

    glEnd();

    // Draw the blue circle with the white star in the center of the yellow stripe
    float circleCenterX = FLAG_WIDTH / 2.0f;
    float circleCenterY = FLAG_HEIGHT / 2.0f;
    float circleRadius = 5.3f; // Adjust the size of the circle
    float starRadius = 4.15f;  // Adjust the size of the star's outer radius
    float starInnerRadius = 1.57f; // Adjust the size of the star's inner radius
    drawBlueCircleWithStar(circleCenterX, circleCenterY, circleRadius, starRadius, starInnerRadius);
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawFlag();
    glutSwapBuffers();
}

// Idle callback function
void idle() {
    t += 0.01f; // Update time variable for animation
    glutPostRedisplay();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Waving Ethiopian Flag with Blue Circle and yellow Star");

    glClearColor(1.0f, 2.0f, 1.0f, 2.0f);
    gluOrtho2D(-10.0, FLAG_WIDTH, -40.0, FLAG_HEIGHT);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

