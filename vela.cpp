//sudo apt-get install freeglut3-dev g++ fogo.cpp -lGLU -lGL -lglut -o fogo && ./fogo

#include "particulas.hpp"

// float angulo = 0.0;
#define NUM 20000

Particula fire[NUM];


void start(int part) {
    fire[part].tempoVida = (double) (8 + rand() % 4) / 11;
    fire[part].gravidade = 0.5;
    fire[part].pos_x = (double) ((rand() % 100) - 60)/300;
    fire[part].pos_z = -5.0;
    fire[part].pos_y = 0.0;
    fire[part].velocidade = 3.15;
    fire[part].vivo = false;
    //define o tamanho
    fire[part].raio = (double)(15 + rand()%10)/2000;
}

void acender() {
	bool queda = true;
    for(int i = 0; i < NUM; i++ ){
        glColor3f(1.0, 0.45, 0);
        if(fire[i].pos_x > -0.15 && fire[i].pos_x < 0.05 && queda){
            glColor3f(2.65, 1.65, 0);
        }
        glPushMatrix();
            glTranslatef(fire[i].pos_x, fire[i].pos_y, fire[i].pos_z);
            glutSolidSphere(fire[i].raio, 5, 5);
        glPopMatrix();

        if (fire[i].vivo) {
            //direção de movimento
            double quedax = -5000 + rand() % 2000;
            //fire[i].pos_x += -fire[i].velocidade /quedax;
            fire[i].pos_y += fire[i].velocidade /1000;
            fire[i].velocidade += fire[i].gravidade/10;
            fire[i].tempoVida -= 0.006;
			if(fire[i].pos_y > 0.01 && fire[i].pos_y < 0.3 && queda==true){
				if(fire[i].pos_x > -0.1){
                	fire[i].pos_x += -3*fire[i].velocidade /quedax;
            	}else if(fire[i].pos_x < -0.1){
                	fire[i].pos_x += 3*fire[i].velocidade /quedax;
            	}
				queda = !(queda);
			}else if(fire[i].pos_x > -0.1 && fire[i].pos_x < 0.0){
				fire[i].pos_x = fire[i].pos_x;
			}
			
			else{
	            if(fire[i].pos_x > 0.0){
    	            fire[i].pos_x += fire[i].velocidade /quedax;
        	    }else if(fire[i].pos_x < 0.0){
            	    fire[i].pos_x += -fire[i].velocidade /quedax;
            	}
				queda = !(queda);
			}
        }
        else {
            if (rand() % 100 < 2) {
                fire[i].vivo = true;
            }
        }

        if (fire[i].tempoVida < 0.0) {
            start(i);
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
	
	acender();

	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	
	gluLookAt(0.0, 5.0, 1.0,
	 		  0.0, 0.0, 1.0,
	 		  0.0, 0.0, 1.0);

	glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.03f, 0.01f, -0.8f);
		glRotatef(90.0f, 0.0f, 0.0f, 5.0f);
		gluCylinder(pObj, 0.2f, 0.2f, 1.8f, 26, 13);  
	glPopMatrix(); 

   	glutSwapBuffers();
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize (900, 680);
	glutCreateWindow ("Velinha >.<");

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

	    // GLfloat mat_shininess[] =  { 50.0 };
	    // GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

	    // GLfloat light_ambient[] =  {  0.5,  0.5,  0.5, 1.0 };
	    // GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
	    // GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
	    // GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

	    // glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	    // glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	    // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	    // glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	    // glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	    // glEnable(GL_LIGHTING);
	    // glEnable(GL_LIGHT0);

	    // glEnable(GL_COLOR_MATERIAL);

	    // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	    glutMainLoop();


	return 0;
}