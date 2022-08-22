#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Plane.h"
#include <unistd.h>
using namespace std;

int thisone;
int dpi = 72;
double aathreshold = 0.1;
double luzAmbiente = 0.2;
double acuracia = 0.00000001;

Vect Y (0,1,0);
Vect posCam (10,7, -17);	
Vect posLuz (-10,10,-10);
Vect look_at (0, 3, 0);

//cores base
Color white_light (1.0, 1.0, 1.0, 0);
Color maroon (0.5, 0.25, 0.25, 0.8);
Color red (1.0, 0.2, 0.1, 0.3);
Color black (0.0, 0.0, 0.0, 0.4);
Color blue (0.2, 1.0, 1.0, 0);

//objs na cena
Sphere esfera1 (Vect(5, 1, -5), 2.0, maroon);
Sphere esfera2 (Vect(0, 4, -7), 3.0, black);
Plane parede (Vect(-1,0,-1), -10, blue);
Plane parede2 (Vect(1,0,1), -10, red);
Plane chao (Vect(0,1,0), -1, Color(1.0, 0.4, 0.1, 0.3)); //laranja


#endif