#include <GL/glut.h>
#include <cmath>  // For sine wave function

// Global variables for color blending
float redColor = 0.0f;
float blueColor = 0.0f;
bool blendingToRed = true;

// Global variables for car and bird positions
float carPosX = -1.0f; // Initial position of the car
float carSpeed = 0.001f; // Initial speed of the car
float birdPosX[7] = { -0.8f, -0.6f, -0.4f, -0.2f, 0.0f, 0.2f, 0.4f }; // Initial positions of the birds

// Rain parameters
const int numRaindrops = 100;
float raindropX[numRaindrops];
float raindropY[numRaindrops];
bool isRaining = false; // Flag to check if it's raining

// Snowfall parameters
const int numSnowflakes = 100;
float snowflakeX[numSnowflakes];
float snowflakeY[numSnowflakes];
bool isSnowing = false; // Flag to check if it's snowing

// Function to initialize the scene
void init() {
    glEnable(GL_DEPTH_TEST);
    // Initialize raindrop positions
    for (int i = 0; i < numRaindrops; ++i) {
        raindropX[i] = (rand() % 200 - 100) / 100.0f; // Random X position between -1 and 1
        raindropY[i] = (rand() % 200) / 100.0f;       // Random Y position between 0 and 2
    }
    // Initialize snowflake positions
    for (int i = 0; i < numSnowflakes; ++i) {
        snowflakeX[i] = (rand() % 200 - 100) / 100.0f; // Random X position between -1 and 1
        snowflakeY[i] = (rand() % 200) / 100.0f;       // Random Y position between 0 and 2
    }
}



// Function to update the background color
void updateBackgroundColor(int value) {
    if (blendingToRed) {
        redColor += 0.01f;
        blueColor -= 0.01f;
        if (redColor >= 1.0f) {
            redColor = 1.0f;
            blueColor = 0.0f;
            blendingToRed = false;
        }
    } else {
        redColor -= 0.01f;
        blueColor += 0.01f;
        if (redColor <= 0.0f) {
            redColor = 0.0f;
            blueColor = 1.0f;
            blendingToRed = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, updateBackgroundColor, 0); // Update every 25 ms
}

// Function to draw snowflakes
void drawSnow() {
    if (isSnowing) {
        glColor3f(1.0f, 1.0f, 1.0f); // Snow color white
        glBegin(GL_POINTS);
        for (int i = 0; i < numSnowflakes; ++i) {
            glVertex2f(snowflakeX[i], snowflakeY[i]);
        }
        glEnd();
    }
}

// Function to update snowflake positions
void updateSnow(int value) {
    if (isSnowing) {
        for (int i = 0; i < numSnowflakes; ++i) {
            snowflakeY[i] -= 0.01f; // Move snowflakes down
            if (snowflakeY[i] < -1.0f) {
                snowflakeY[i] = 1.0f; // Reset snowflake to the top when it goes off screen
                snowflakeX[i] = (rand() % 200 - 100) / 100.0f; // Random X position between -1 and 1
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(25, updateSnow, 0); // Update every 25 ms
}

// Function to draw raindrops
void drawRain() {
    if (isRaining) {
         glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
        for (int i = 0; i < numRaindrops; ++i) {
            glVertex2f(raindropX[i], raindropY[i]);
            glVertex2f(raindropX[i], raindropY[i] - 0.05f); // Draw line for raindrop
        }
        glEnd();
    }
}


// Function to update raindrop positions
void updateRain(int value) {
    if (isRaining) {
        for (int i = 0; i < numRaindrops; ++i) {
            raindropY[i] -= 0.02f; // Move raindrop down
            if (raindropY[i] < -1.0f) {
                raindropY[i] = 1.0f; // Reset raindrop to the top when it goes off screen
                raindropX[i] = (rand() % 200 - 100) / 100.0f; // Random X position between -1 and 1
            }
        }
        glutPostRedisplay();
    }
    glutTimerFunc(25, updateRain, 0); // Update every 25 ms
}

// Function to draw hills
void drawHills() {
    glBegin(GL_TRIANGLES);
        // Draw first hill (triangle) beside the sun
        glColor3f(0.5f, 0.35f, 0.05f);  // Brown color for the hills
        glVertex2f(-0.3f, 0.0f); // Bottom-left
        glVertex2f(0.0f, 0.3f);  // Peak of the hill
        glVertex2f(0.3f, 0.0f);  // Bottom-right

        // Draw second hill (triangle) beside the first one
        glVertex2f(0.1f, 0.0f);  // Bottom-left of second hill
        glVertex2f(0.4f, 0.25f); // Peak of the second hill
        glVertex2f(0.7f, 0.0f);  // Bottom-right of second hill
    glEnd();

      // Left-side hills (new hills)
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.35f, 0.05f);  // Brown color for the hills
        glVertex2f(-0.5f, 0.0f);  // Peak of the first left-side hill
        glVertex2f(-0.2f, 0.0f);  // Right base
        glVertex2f(-0.35f, 0.3f); // Left base

        glVertex2f(-0.3f, 0.0f);  // Peak of the second left-side hill
        glVertex2f(0.0f, 0.0f);  // Right base
        glVertex2f(-0.15f, 0.3f); // Left base
    glEnd();

}


// Function to draw palm trees
void drawPalmTree(float posX, float posY) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Draw trunk
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.35f, 0.05f);  // Brown trunk
        glVertex2f(-0.02f, -0.2f);
        glVertex2f(0.02f, -0.2f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(-0.02f, 0.2f);
    glEnd();

    // Draw leaves (use triangles to form the leaves)
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.8f, 0.0f); // Green leaves
        for (float angle = 0.0f; angle < 360.0f; angle += 60.0f) {
            float rad = angle * 3.14159f / 180.0f;
            glVertex2f(0.0f, 0.2f);  // Center of palm leaves
            glVertex2f(0.15f * cos(rad), 0.2f + 0.15f * sin(rad));  // End of each leaf
            glVertex2f(0.15f * cos(rad + 0.1f), 0.2f + 0.15f * sin(rad + 0.1f));  // Slight angle for leaf width
        }
    glEnd();

    glPopMatrix();
}







// Function to draw the car
void drawCar(float posX) {
    glPushMatrix();
    glTranslatef(posX, -0.65f, 0.0f); // Position the car on the road

    // Car body
    glBegin(GL_QUADS);
        glColor3f(0.8f, 0.0f, 0.0f); // Red car
        glVertex2f(-0.1f, -0.05f);
        glVertex2f(0.1f, -0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    // Car roof
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.0f, 0.0f); // Dark red roof
        glVertex2f(-0.05f, 0.05f);
        glVertex2f(0.05f, 0.05f);
        glVertex2f(0.05f, 0.1f);
        glVertex2f(-0.05f, 0.1f);
    glEnd();

    // Car wheels
    glColor3f(0.0f, 0.0f, 0.0f); // Black wheels
    glPushMatrix();
    glTranslatef(-0.07f, -0.1f, 0.0f);
    glutSolidSphere(0.03f, 20, 20); // Approximate circle using a sphere
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.07f, -0.1f, 0.0f);
    glutSolidSphere(0.03f, 20, 20); // Approximate circle using a sphere
    glPopMatrix();

    glPopMatrix();
}



// Function to draw a bird
void drawBird(float posX, float posY) {
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);

    // Draw a triangle to represent the bird
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f); // Black color for the bird
        glVertex2f(-0.03f, 0.0f); // Left wing
        glVertex2f(0.03f, 0.0f);  // Right wing
        glVertex2f(0.0f, 0.03f);  // Top
    glEnd();

    glPopMatrix();
}





// Function to draw the house
void drawHouse() {
    // Draw the house base
    glBegin(GL_QUADS);
        glColor3f(0.8, 0.52, 0.25); // Light brown
        glVertex2f(-0.1, -0.1);
        glVertex2f(0.1, -0.1);
        glVertex2f(0.1, 0.1);
        glVertex2f(-0.1, 0.1);
    glEnd();

    // Draw the roof
    glBegin(GL_TRIANGLES);
        glColor3f(0.6, 0.3, 0.1); // Brown
        glVertex2f(-0.15, 0.1);
        glVertex2f(0.15, 0.1);
        glVertex2f(0.0, 0.2);
    glEnd();

    // Draw the door
    glBegin(GL_QUADS);
        glColor3f(0.4, 0.2, 0.1); // Dark brown
        glVertex2f(-0.025, -0.1);
        glVertex2f(0.025, -0.1);
        glVertex2f(0.025, 0.0);
        glVertex2f(-0.025, 0.0);
    glEnd();

    // Draw windows
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.8); // Blue
        glVertex2f(-0.075, 0.025);
        glVertex2f(-0.025, 0.025);
        glVertex2f(-0.025, 0.075);
        glVertex2f(-0.075, 0.075);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.8); // Blue
        glVertex2f(0.05, 0.05);
        glVertex2f(0.15, 0.05);
        glVertex2f(0.15, 0.15);
        glVertex2f(0.05, 0.15);
    glEnd();
}

// Function to draw the tree
void drawTree() {
    // Draw tree trunk
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.3f, 0.1f);  // Tree trunk color
        glVertex2f(0.5f, -0.3f);
        glVertex2f(0.55f, -0.3f);
        glVertex2f(0.55f, -0.1f);
        glVertex2f(0.5f, -0.1f);
    glEnd();

    // Draw tree leaves
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.8f, 0.0f);  // Tree leaves color
        glVertex2f(0.475f, -0.1f);
        glVertex2f(0.575f, -0.1f);
        glVertex2f(0.525f, 0.2f);
    glEnd();
}

// Function to draw the Road
void drawRoad() {
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f); // Grass gray
        glVertex2f(-1.0f, -0.5f); // Set the top edge just below the house and tree
        glVertex2f(1.0f, -0.5f);
        glVertex2f(1.0f, -0.9f);
        glVertex2f(-1.0f, -0.9f);
    glEnd();
}
// Function to draw a big tree with circle leaves
void drawBigTree() {
    // Draw the tree trunk
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.3f, 0.1f);  // Brown trunk color
        glVertex2f(0.6f, -0.3f); // Bottom-left
        glVertex2f(0.65f, -0.3f); // Bottom-right
        glVertex2f(0.65f, 0.0f); // Top-right
        glVertex2f(0.6f, 0.0f); // Top-left
    glEnd();

    // Draw circular leaves using circles (glutSolidSphere)
    glColor3f(0.0f, 0.6f, 0.0f); // Green leaves color

    // Draw the bottom set of leaves
    glPushMatrix();
    glTranslatef(0.625f, 0.05f, 0.0f); // Position above the trunk
    glutSolidSphere(0.08, 50, 50); // Draw the circle (bottom leaves)
    glPopMatrix();

    // Draw the middle set of leaves
    glPushMatrix();
    glTranslatef(0.575f, 0.15f, 0.0f); // Slightly offset to the left
    glutSolidSphere(0.1, 50, 50); // Middle left leaves
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.675f, 0.15f, 0.0f); // Slightly offset to the right
    glutSolidSphere(0.1, 50, 50); // Middle right leaves
    glPopMatrix();

    // Draw the top set of leaves
    glPushMatrix();
    glTranslatef(0.625f, 0.25f, 0.0f); // Top-center leaves
    glutSolidSphere(0.12, 50, 50); // Top leaves
    glPopMatrix();
}




// Function to draw the grass
void drawGrass() {
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.8f, 0.0f); // Grass green
        glVertex2f(-1.0f, -0.4f); // Set the top edge just below the house and tree
        glVertex2f(1.0f, -0.4f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}
    float sunPosY = 0.2f; // Initial Y position of the sun
    float sunSpeed = 0.001f; // Speed of the sun's movement
// Function to draw the sun
void drawSun() {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the sun
    glPushMatrix();
    glTranslatef(0.0f, sunPosY, 0.0f); // Adjust position based on sunPosY
    glutSolidSphere(0.1, 50, 50); // Sun radius
    glPopMatrix();
}

// Function to draw the sea with gradient color
void drawSea() {
    glBegin(GL_QUADS);
        // Dark blue at the bottom of the sea
        glColor3f(0.0, 0.0, 0.5); // Deep sea color
        glVertex2f(-1.0, -1.0); // Bottom-left
        glVertex2f(1.0, -1.0); // Bottom-right

        // Lighter blue, transitioning towards the horizon
        glColor3f(0.2, 0.5, 1.0); // Horizon color
        glVertex2f(1.0, 0.0); // Top-right
        glVertex2f(-1.0, 0.0); // Top-left
    glEnd();
}




// Function to draw the scene
void display() {
    glClearColor(redColor, 0.0f, blueColor, 1.0f); // Set background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     // Draw rain
    drawRain();

     // Draw snowflakes
    drawSnow();


    // Draw 7 birds flying in the sky
    for (int i = 0; i < 7; i++) {
        drawBird(birdPosX[i], 0.7f + 0.05f * sin(birdPosX[i] * 10.0f)); // Bird wave movement
    }


       // Draw the moving car
    drawCar(carPosX);





      // Update car position based on its speed
    carPosX += carSpeed;
    if (carPosX > 1.0f) {
        carPosX = -1.0f; // Reset car to the left side when it moves off the screen
    }

    // Draw the road and grass
    drawRoad();

      // Draw the hills beside the sea and the sun
    drawHills();

     drawSun();




    glPushMatrix();
glTranslatef(-0.5f, -0.4f, 0.0f); // Adjust position beside the house
drawBigTree();
glPopMatrix();

    // Draw two palm trees, one on each side
    drawPalmTree(-0.9f, -0.4f); // Left side palm tree
    drawPalmTree(0.9f, -0.4f);  // Right side palm tree


    drawGrass();

    // Draw the houses and trees
    glPushMatrix();
    glTranslatef(-0.7f, -0.4f, 0.0f);
    drawHouse();
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.4f, 0.0f);
    drawHouse();
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -0.4f, 0.0f);
    drawHouse();
    drawTree();
    glPopMatrix();

    // Draw the gradient sky
    glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.5); // Dark blue
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);
        glColor3f(1.0, 0.5, 0.0); // Orange
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
    glEnd();



    // Draw the sea
    drawSea();













    glutSwapBuffers();
}

// Function to update the car's and birds' positions
void updateCarAndBirds(int value) {
    carPosX += 0.02f; // Move the car to the right
    if (carPosX > 1.0f) {
        carPosX = -1.0f; // Reset position to left if car goes off screen
    }

    // Move the birds to the right
    for (int i = 0; i < 7; i++) {
        birdPosX[i] += 0.01f;
        if (birdPosX[i] > 1.0f) {
            birdPosX[i] = -1.0f; // Reset bird position to left if it goes off screen
        }
    }

    glutPostRedisplay();
    glutTimerFunc(25, updateCarAndBirds, 0); // Update every 25 ms
}

// Function to update the sun's position
void updateSun(int value) {
    sunPosY += sunSpeed; // Move the sun upwards or downwards

    // Check if the sun reaches the top of the sky
    if (sunPosY > 0.9f) {
        sunSpeed = -0.001f; // Change direction to move the sun down
    }
    // Check if the sun reaches the bottom, behind the hills
    else if (sunPosY < 0.2f) {
        sunSpeed = 0.001f; // Change direction to move the sun back up
    }

    glutPostRedisplay(); // Redraw the scene with the new sun position
    glutTimerFunc(25, updateSun, 0); // Update every 25 ms
}






// Function to handle keyboard input
void handleKeyboard(unsigned char key, int x, int y) {
{
    if (key == 'R' || key == 'r') {
        isRaining = true;  // Start raining
    } else if (key == 'O' || key == 'o') {
        isRaining = false; // Stop raining
    }
}

 {
    if (key == 'S' || key == 's') {
        isSnowing = true;  // Start snowing
    } else if (key == 'D' || key == 'd') {
        isSnowing = false; // Stop snowing
    }
}
}

// Function to handle special keyboard input (for arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        carSpeed += 0.01f;  // Increase the car's speed
    } else if (key == GLUT_KEY_DOWN) {
        carSpeed -= 0.01f;  // Decrease the car's speed
        if (carSpeed < 0.0f) carSpeed = 0.0f;  // Ensure the speed doesn't go negative
    }
}


// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tareq Jamil Sarkar's Project");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
     glutKeyboardFunc(handleKeyboard); // Register keyboard handler
       glutSpecialFunc(handleSpecialKeys);   // Register handler for special keys (arrow keys)
    glutTimerFunc(25, updateBackgroundColor, 0); // Set the timer to call update every 25 ms
    glutTimerFunc(25, updateCarAndBirds, 0); // Set the timer to call updateCarAndBirds every 25 ms
    glutTimerFunc(25, updateRain, 0); // Set the timer to call updateRain every 25 ms
    glutTimerFunc(25, updateSun, 0); // Start the sun animation
     glutTimerFunc(25, updateSnow, 0); // Set the timer to update snow every 25 ms
    glutMainLoop();
    return 0;
}
