#ifndef PARTICULAS_HPP
#define PARTICULAS_HPP

#include <bits/stdc++.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>

using namespace std;

class Particula
{
public:
	double tempoVida;
    double pos_x;
    double pos_y; 
    double pos_z; 
    double velocidade;
    double raio;
    double gravidade;
    bool vivo;

};

#endif