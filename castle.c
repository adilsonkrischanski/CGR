// gcc snowman_sample.c -lglut -lGL -lGLU -lm -o snowman && ./snowman

#include <GL/glut.h>
  
// Rotation
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;

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
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 0.25f };  
    GLfloat  lightPos[] = { -1.0f, 5.0f, 5.0f, 1.0f };  
  
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
        
    if(key == GLUT_KEY_UP)  
        xRot -= 5.0f;  
  
    if(key == GLUT_KEY_DOWN)  
        xRot += 5.0f; 
                  
    yRot = (GLfloat)((const int)yRot % 360);
    xRot = (GLfloat)((const int)xRot % 360);  
  
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
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);  

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

	//floor
	glPushMatrix();
		glColor3f(0.2f, 1.0f, 0.2f); 
		glTranslatef(0.0, 0.0, -0.8f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glScalef(7.0f, 7.0f, 0.05f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	
		
	//Telhados
	glColor3f(1.0, 0.2, 0.0);
	glPushMatrix();
		glTranslatef(1.2f, 1.15f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.26f, 0.4f, 26, 13);  
	glPopMatrix(); 	
	glPushMatrix();
		glTranslatef(-1.2f, 1.15f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.26f, 0.4f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 1.15f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.26f, 0.4f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2f, 1.15f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.26f, 0.4f, 26, 13);  
	glPopMatrix();
	

	// Towers
	glColor3f(0.8f, 0.8f, 0.8f);  
	glPushMatrix();
		glTranslatef(1.2f, 0.8f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.2f, 0.2f, 0.8f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 0.8f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.2f, 0.2f, 0.8f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 0.8f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.2f, 0.2f, 0.8f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2f, 0.8f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.2f, 0.2f, 0.8f, 26, 13);  
	glPopMatrix();
	

	//Muro Principal
	glColor3f(0.6f, 0.6f, 0.6f); 
	glPushMatrix();
		glTranslatef(-0.6, 0.25, 0.4f);
		glScalef(1.8f, 1.0f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.6, 0.25, 0.4f);
		glScalef(1.8f, 1.0f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0, 0.376, 0.4f);
		glScalef(1.0f, 0.5f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	//Muros
	glPushMatrix();
		glTranslatef(0.0, 0.25, -2.0f);
		//glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
		glScalef(4.0f, 1.0f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.25, -0.8f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(4.0f, 1.0f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.25, -0.8f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(4.0f, 1.0f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	//detalhe nos muros
	glPushMatrix();
		glTranslatef(0.0, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.3, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.3, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.6, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.6, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.9, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.9, 0.5, 0.4f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.3, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.3, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.6, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.6, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.9, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-0.9, 0.5, -2.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.2, 0.5, -0.8f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, -1.1f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, -0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, -1.4f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, -0.2f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, -1.7f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2, 0.5, 0.1f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -0.8f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -1.1f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -0.5f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -1.4f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -0.2f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, -1.7f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2, 0.5, 0.1f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.3f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	//janelas
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(1.2f, 0.6f, 0.59f);
		glScalef(0.1f, 0.2f, 0.05f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 0.6f, 0.59f);
		glScalef(0.1f, 0.2f, 0.05f);
		glutSolidCube(0.5);
	glPopMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(1.2f, 0.6f, -2.19f);
		glScalef(0.1f, 0.2f, 0.05f);
		glutSolidCube(0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 0.6f, -2.19f);
		glScalef(0.1f, 0.2f, 0.05f);
		glutSolidCube(0.5);
	glPopMatrix();
	
	//bandeiras
	glPushMatrix();
		glTranslatef(-1.2f, 1.39f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.008f, 0.008f, 0.3f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2f, 1.39f, 0.4f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.008f, 0.008f, 0.3f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.2f, 1.39f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.008f, 0.008f, 0.3f, 26, 13);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.2f, 1.39f, -2.0f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.008f, 0.008f, 0.3f, 26, 13);  
	glPopMatrix();
	
	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(-1.15f, 1.353f, 0.4f);
		glScalef(0.16f, 0.16f, 0.03f);
		glutSolidCube(0.5);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.25f, 1.353f, 0.4f);
		glScalef(0.16f, 0.16f, 0.03f);
		glutSolidCube(0.5);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.15f, 1.353f, -2.0f);
		glScalef(0.16f, 0.16f, 0.03f);
		glutSolidCube(0.5);  
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.25f, 1.353f, -2.0f);
		glScalef(0.16f, 0.16f, 0.03f);
		glutSolidCube(0.5); 
	glPopMatrix();
	
	//arvore
	glColor3f(0.7, 0.35, 0.25);
	glPushMatrix();
		glTranslatef(0.4f, 0.4f, -0.8f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.05f, 0.05f, 0.3f, 26, 13);  
	glPopMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glTranslatef(0.4f, 0.7f, -0.8f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.13f, 0.38f, 26, 13);  
	glPopMatrix();
		glPushMatrix();
		glTranslatef(0.4f, 0.8f, -0.8f);
		glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.0f, 0.09f, 0.3f, 26, 13);  
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
