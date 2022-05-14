/*sudo apt-get install freeglut3-dev

g++ cgr-neve.cpp -lGLU -lGL -lglut -o bonecoNeve

./bonecoNeve
*/


#include "neve.h"

// float angulo = 0.0;
#define NUM 4000

Particula neve[NUM];


void iniciaFlocos(int part) {
    neve[part].tempoVida = (double) (8 + rand() % 4) / 10;
    neve[part].gravidade = -0.5;
    neve[part].pos_x = (double) ((rand() % 100) - 60)/10;
    neve[part].pos_z = (double) ((rand() % 200) - 100)/10;
    neve[part].pos_y = 4.0;
    neve[part].velocidade = 3.14;
    neve[part].vivo = false;
    //define o tamanho
    neve[part].raio = (double)(13 + rand()%10)/1000;
}

void nevar() {

    for(int i = 0; i < NUM; i++ ){
        glColor3f(0.9, 0.9, 0.9);
        glPushMatrix();
            glTranslatef(neve[i].pos_x, neve[i].pos_y, neve[i].pos_z);
            glutSolidSphere(neve[i].raio, 10, 10);
        glPopMatrix();

        if (neve[i].vivo) {
            //direção de movimento
            double quedax = -5000 + rand() % 2000;
            neve[i].pos_x += -neve[i].velocidade /quedax;
            neve[i].pos_y += neve[i].velocidade /1000;
            neve[i].velocidade += neve[i].gravidade;
            neve[i].tempoVida -= 0.006;

        }
        else {
            if (rand() % 100 < 2) {
                neve[i].vivo = true;
            }
        }

        if (neve[i].tempoVida < 0.0) {
            iniciaFlocos(i);
        }
    }
}
void init(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, 640, 0, 480, -1, 1);
}

void bolotinhaPreta(double x, double y, double z){
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(x, y, z);
	    glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	nevar();

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

	//Baixo
	glColor3f(0.9, 0.9, 0.9);
	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.1);
		glutSolidSphere(0.9, 20, 20);
	glPopMatrix();

	//Meio
	glPushMatrix();
		glTranslatef(0.0, 0.0, 1.15);
		glutSolidSphere(0.6, 20, 20);
	glPopMatrix();

	//Braço
	glPushMatrix();
		glColor3f(0.36, 0.2, 0.1);
		glTranslatef(0.4, 0.2, 1.2);
		glRotated(90, -1.8, 2, 0);			
		// glutSolidCylinder(0.04, 1, 20, 30);
		gluCylinder(pObj, 0.05, 0.01, 1.0, 200, 300);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.36, 0.2, 0.1);
		glTranslatef(-0.4, 0.2, 1.2);
		glRotated(90, -1.8, -2, 0);			
		gluCylinder(pObj, 0.05, 0.01, 1.0, 200, 300);

	glPopMatrix();

	//Cima
	glPushMatrix();
		glColor3f(0.9, 0.9, 0.9);
		glTranslatef(0.0, 0.0, 1.85);
		glutSolidSphere(0.4, 20, 20);
	glPopMatrix();

	//Botão
	glPushMatrix();
		    bolotinhaPreta(0.0, 0.55, 1.0);
		    bolotinhaPreta(0.0, 0.57, 1.20);
		    bolotinhaPreta(0.0, 0.52, 1.40);
	glPopMatrix();

	//Olhos
	glPushMatrix();
			bolotinhaPreta(-0.15, 0.3, 2.0);
			bolotinhaPreta(0.15, 0.3, 2.0);
	glPopMatrix();

	//Boca
	glPushMatrix();
			bolotinhaPreta(-0.2, 0.3, 1.82);
			bolotinhaPreta(-0.1, 0.33, 1.75);
			bolotinhaPreta(0.0, 0.34, 1.73);
			bolotinhaPreta(0.1, 0.33, 1.75);
			bolotinhaPreta(0.2, 0.3, 1.82);
	glPopMatrix();

	//Nariz
	glPushMatrix();
		glColor3f(1.0, 0.6, 0.0);
		glTranslatef(0.0, 0.3, 1.9);
		glRotated(90, -1, 0,0);
		glutSolidCone(0.1, 0.4, 20, 20);
	glPopMatrix();

   	glutSwapBuffers();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize (900, 680);
	glutCreateWindow ("Boneco de Neve com neve");

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
	    glClearColor(0.15, 0.15, 0.15, 1.0);

	    GLfloat mat_shininess[] =  { 50.0 };
	    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

	    GLfloat light_ambient[] =  {  0.5,  0.5,  0.5, 1.0 };
	    GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
	    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
	    GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

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
