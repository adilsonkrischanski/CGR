#include <GL/glut.h>
#include "particulas.hpp"


#define NUM 5000

Particula chuva[NUM];

void iniciaFlocos(int part) {
    chuva[part].tempoVida = (double) (10 + rand() % 4) / 10;
    chuva[part].gravidade = -0.5;
    chuva[part].pos_x = (double) ((rand() % 100) - 60)/10;
    chuva[part].pos_z = (double) ((rand() % 200) - 100)/10;
    chuva[part].pos_y = 4;
    chuva[part].velocidade = 1.5;
    chuva[part].vivo = false;
    //define o tamanho
 
    chuva[part].raio = (double)(rand()%50)/5000;
}

void tempestade(){

    for(int i = 0; i < NUM; i++ ){
        glColor3f(0.0, 0.0, 0.6); //set_chuvascolor
        glPushMatrix();
            glTranslatef(chuva[i].pos_x, chuva[i].pos_y, chuva[i].pos_z);
            glutSolidSphere(chuva[i].raio, 10, 10);
        glPopMatrix();

        if (chuva[i].vivo) {
            //direção de movimento
            double quedax = -5000 + rand() % 2000;
			chuva[i].pos_x -= chuva[i].velocidade /quedax;	
            chuva[i].pos_y += chuva[i].velocidade /1000;
            chuva[i].velocidade += chuva[i].gravidade;
            chuva[i].tempoVida -= 0.007;

        }
        else {
            if (rand() % 100 < 2) {
                chuva[i].vivo = true;
            }
        }

        if (chuva[i].tempoVida < 0.0) {
            iniciaFlocos(i);
        }
    }
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, 640, 0, 480, -1, 1);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	tempestade();

    GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	
	gluLookAt(0.0, 5.0, 1.0,
			  0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);


    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0,0,-0.80);
        glutSolidCylinder(3.5, 0.05, 20, 20);
    glPopMatrix();

    glColor3f(0.65, 0.3, 0.2);

	glPushMatrix();
		glTranslatef(0.0f, 0.0f, -0.1f);
		// glRotatef(0.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.05f, 0.05f, 0.3f, 26, 13);  
	glPopMatrix();
	glColor3f(0.0, 0.6, 0.2);
	glPushMatrix();
		glTranslatef(0.0, 0.0f, 0.2f);
		glRotatef(90.0f, 0.0f, 0.0f, 90.0f);
		gluCylinder(pObj ,0.20f, 0.0f, 0.4f, 26, 13);  
	glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 0.0f, 0.5f);
		// glRotatef(90.0f, 5.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.15f, 0.0f, 0.3f, 26, 13);  
	glPopMatrix();

   	glutSwapBuffers();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize (900, 680);
	glutCreateWindow ("chuvinha");

	glutDisplayFunc(display);
	glutIdleFunc(display);

	    glMatrixMode(GL_PROJECTION);
	    glViewport(0, 0, 800, 600);
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    GLfloat aspect = (GLfloat) 800 / 600;
	    gluPerspective(45, aspect, 2.0f, 15.0f);
	    glMatrixMode(GL_MODELVIEW);
	    glShadeModel( GL_SMOOTH );
	    glClearDepth( 1.0f );
	    glEnable( GL_DEPTH_TEST );
	    glDepthFunc( GL_LEQUAL );
	    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	    glClearColor(0.1, 0.3, 0.5, 0.5); //backgroundcolor 

	    GLfloat mat_shininess[] =  { 50.0 };
	    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

	    GLfloat light_ambient[] =  {  0.3,  0.3,  0.3, 0.6 };
	    GLfloat light_diffuse[] =  {  0.5,  0.5,  0.5, 0.5 };
	    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
	    GLfloat light_position[] = {  5.0,  2.0,  5.0, 0.0 };

	    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	    glEnable(GL_LIGHTING);
	    glEnable(GL_LIGHT0);

	    glEnable(GL_COLOR_MATERIAL);

	    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	    glutMainLoop();


	return 0;
}