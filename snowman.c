// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>
  
// Rotation
static GLfloat yRot = 0.0f;

// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    }  
  
  
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  

    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.7f, 0.8f, 1.0f, 0.0f);  

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  

    if(key == GLUT_KEY_LEFT)  
        yRot -= 5.0f;  
  
    if(key == GLUT_KEY_RIGHT)  
        yRot += 5.0f;  
                  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}
  
// Called to draw scene  
void RenderScene(void){  

    GLUquadricObj *pObj;    // Quadric Object  
      
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);  

	// white
	glColor3f(1.0f, 1.0f, 1.0f);  

	// Main Body  
//	gluSphere();  // Bottom

	// Mid section
//	glPushMatrix();
//		glTranslatef(); 
//		gluSphere();
//	glPopMatrix();

	// Head
	glPushMatrix(); // save transform matrix state
		glTranslatef(0.0f, 1.4f, 0.0f);
		gluSphere(pObj, 0.24f, 26, 13);
	glPopMatrix(); // restore transform matrix state
	
	
	// Nose (orange)
	glColor3f(1.0, 0.2, 0.0); 
	glPushMatrix();
		glTranslatef(0.0f, 1.4f, 0.2f);
		gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);  
	glPopMatrix();  

	// Eyes (black)
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.07f, 1.5f, 0.18f);
		gluSphere(pObj, 0.048f, 26, 13);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.07f, 1.5f, 0.18f);
		gluSphere(pObj, 0.048f, 26, 13);
	glPopMatrix();
	
	// Body
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(0.0, 0.88, 0.0);
		gluSphere(pObj, 0.38f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.3, 0.0);
		gluSphere(pObj, 0.48f, 26, 13);
	glPopMatrix();
	
	// Arms
	glColor3f(0.7, 0.35, 0.25);//tentativa de marrom
	glPushMatrix();
		glTranslatef(0.28, 0.93, 0.0f);
		glRotatef(-150.0f, 5.0f, 0.5f, 5.0f);
		gluCylinder(pObj, 0.02f, 0.01f, 0.5f, 26, 13); 
	glPopMatrix();
		//left hand
		glPushMatrix();
			glTranslatef(0.72, 1.148, 0.038f);
			glRotatef(-90.0f, 5.0f, 0.0f, 5.0f);
			gluCylinder(pObj, 0.01f, 0.005f, 0.2f, 26, 13); 
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.72, 1.148, 0.038f);
			glRotatef(-180.0f, 5.0f, 0.0f, 5.0f);
			gluCylinder(pObj, 0.01f, 0.005f, 0.2f, 26, 13); 
		glPopMatrix();
		
	glPushMatrix();
		glTranslatef(-0.84, 1.1, 0.02f);
		glRotatef(150.0f, 5.0f, 0.5f, 5.0f);
		gluCylinder(pObj, 0.01f, 0.02f, 0.5f, 26, 13); 
	glPopMatrix();
		//right hand
		glPushMatrix();
			glTranslatef(-0.98, 1.22, -0.02f);
			glRotatef(-240.0f, 5.0f, 0.0f, 5.0f);
			gluCylinder(pObj, 0.005f, 0.01f, 0.2f, 26, 13); 
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.04, 1.1, 0.03f);
			glRotatef(-240.0f, 10.0f, 10.0f, 10.0f);
			gluCylinder(pObj, 0.005f, 0.01f, 0.2f, 26, 13); 
		glPopMatrix();

	// Hat
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0, 1.9, 0.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.1f, 0.1f, 0.2f, 50, 150); 
	glPopMatrix();
	// Hat brim
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0, 1.63, 0.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.25f, 0.25f, 0.05f, 50, 150); 
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0, 1.7, 0.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.1f, 0.1f, 0.1f, 50, 150); 
	glPopMatrix();
	
	// Mouth
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0f, 1.28, 0.2f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.08, 1.3, 0.18f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.11, 1.36, 0.18f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-0.08, 1.3, 0.18f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(-0.11, 1.36, 0.18f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	
	
	// Button
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0f, 0.9, 0.37f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0f, 1.1, 0.3f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0f, 1.0, 0.35f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0f, 0.8, 0.36f);
		gluSphere(pObj, 0.03f, 26, 13);
	glPopMatrix();
	
	
	//Scarf
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0, 1.24, 0.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.25f, 0.25f, 0.08f, 50, 150); 
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.15, 1.13, 0.24f);
		glRotatef(-220.0f, 5.0f, 0.5f, -1.5f);
		glScalef(0.4f, 0.6f, 0.05f);
		glutSolidCube(0.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.2, 1.13, -0.2f);
		glRotatef(220.0f, 5.0f, -1.0f, -1.8f);
		glScalef(0.4f, 0.6f, 0.05f);
		glutSolidCube(0.2);
	glPopMatrix();


          
    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    

int main(int argc, char *argv[]){

    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(800, 600);  
    glutCreateWindow("Modeling with Quadrics");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}

