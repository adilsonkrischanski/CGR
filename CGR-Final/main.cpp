#include "main.hpp"

struct RGBType {
	double r;
	double g;
	double b;
};

void savebmp (int w, int h, RGBType *data) {
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;
	
	double factor = 39.375;
	int m = static_cast<int>(factor);
	
	int ppm = dpi*m;
	
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);
	
	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);
	
	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);
	
	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);
	
	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);
	

	//salvar em results
	string pathName = "result/";
	string fileName = "/rayTracing.bmp";
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	pathName.append(asctime(timeinfo));
	pathName.append("rayTracing.bmp");

	f = fopen(pathName.c_str(), "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	
	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];
		
		double red = (data[i].r)*255;
		double green = (data[i].g)*255;
		double blue = (data[i].b)*255;
		
		unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)};
		
		fwrite(color,1,3,f);
	}
	
	fclose(f);
}


int winningObjectIndex(vector<double> objIntersec) {
	//sem interseçao
	if (objIntersec.size() == 0) {
		return -1;
	
	}else if (objIntersec.size() == 1) {
		if (objIntersec[0] > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {

		//Percorre todo o vetor para encontrar o valor maximo de interseção
		double max = 0;
		for (int i = 0; i < objIntersec.size(); i++) {
			if (max < objIntersec[i]) {
				max = objIntersec[i];
			}
		}
		
		// comeca do valor maximo
		if (max > 0) {
			int idx = 0;

			//acha o menor ponto de intersecao não negativo
			for (int i = 0; i < objIntersec.size(); i++) {
				if (objIntersec[i] > 0 && objIntersec[i] <= max) {
					max = objIntersec[i];
					idx = i;
				}
			}
			
			return idx;
		}
		else {
			//so intersecao negativa
			return -1;
		}
	}
}

Color getColorAt(Vect posIntersec, Vect rayDirIntersec, vector<Object*> objCena, int indice, vector<Light*> fonteLuz) {
	
	Color winning_object_color = objCena[ indice ]->getColor();
	Vect winning_object_normal = objCena[ indice ]->getNormalAt(posIntersec);
	
	Color corFinal = winning_object_color.colorScalar(luzAmbiente);
	
	//Se o reflexo for maior que zero e menor que 1
	if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
		// especularidade
		double dot1 = winning_object_normal.dotProduct(rayDirIntersec.negative());
		Vect scalar1 = winning_object_normal.vectMult(dot1);
		Vect add1 = scalar1.vectAdd(rayDirIntersec);
		Vect scalar2 = add1.vectMult(2);
		Vect add2 = rayDirIntersec.negative().vectAdd(scalar2);
		Vect reflection_direction = add2.normalize();
		
		Ray reflection_ray (posIntersec, reflection_direction);

		vector<double> intersecReflexao;
		//Adiciona no vetor todos os objetos que tem interseção com o raio refletido
		for (int i = 0; i < objCena.size(); i++) {
			intersecReflexao.push_back(objCena[i]->findIntersection(reflection_ray));
		}
		
		int indiceObjReflexo = winningObjectIndex(intersecReflexao);
		

		//faz o cálculo recursivo para criar uma reflexão entre os objetos, semelhante ao espelho
		if (indiceObjReflexo != -1) {
			if (intersecReflexao[ indiceObjReflexo ] > acuracia) {
				// o ray so afeta a cor se estiver refletindo algo
				
				Vect posIntersecReflete = posIntersec.vectAdd(reflection_direction.vectMult(intersecReflexao.at(indiceObjReflexo)));
				Vect dirRayReflete = reflection_direction;
				
				Color corRefletido = getColorAt(posIntersecReflete, dirRayReflete, objCena, indiceObjReflexo, fonteLuz);
				
				corFinal = corFinal.colorAdd(corRefletido.colorScalar(winning_object_color.getColorSpecial()));
			}
		}
	}
	
	//Percorre o vetor de luzes no cenário
	for (int i = 0; i < fonteLuz.size(); i++) {
		Vect dirLuz = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();
		
		float cos = winning_object_normal.dotProduct(dirLuz);
		
		if (cos > 0) {
			bool sombra = false;
			
			Vect distance_to_light = fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize();
			float distance_to_light_magnitude = distance_to_light.magnitude();
			
			//Cria o ray da sombra, onde a origem é a intersecao entre os objetos
			// e a direção é o sentido da fonte luminosa
			Ray raySombra (posIntersec, fonteLuz[i]->posLuz.vectAdd(posIntersec.negative()).normalize());
			
			vector<double> intersecAux;
			
			for (int i = 0; i < objCena.size() && !sombra; i++) {
				intersecAux.push_back(objCena[i]->findIntersection(raySombra));
			}
			
			//Faz o cálculo da sombra
			for (int c = 0; c < intersecAux.size(); c++) {
				if (intersecAux[c] > acuracia) {
					if (intersecAux[c] <= distance_to_light_magnitude) {
						sombra = true;
					}
				}
			}
			
			if (!sombra) {
				corFinal = corFinal.colorAdd(winning_object_color.colorMultiply(fonteLuz[i]->corLuz).colorScalar(cos));
				
				if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
					// special [0-1]
					double dot1 = winning_object_normal.dotProduct(rayDirIntersec.negative());
					Vect scalar1 = winning_object_normal.vectMult(dot1);
					Vect add1 = scalar1.vectAdd(rayDirIntersec);
					Vect scalar2 = add1.vectMult(2);
					Vect add2 = rayDirIntersec.negative().vectAdd(scalar2);
					Vect reflection_direction = add2.normalize();
					
					double specular = reflection_direction.dotProduct(dirLuz);
					if (specular > 0) {
						specular = pow(specular, 10);
						corFinal = corFinal.colorAdd(fonteLuz[i]->corLuz.colorScalar(specular*winning_object_color.getColorSpecial()));
					}
				}
				
			}
			
		}
	}
	
	return corFinal.clip();
}



int main (int argc, char *argv[]) {	
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int n = width*height;

	RGBType *pixels = new RGBType[n];


	//getVectX() > 3
	if(posCam.getVectX() < 3){
		posCam.setVectX(3);
	}	

	//Diferença entre a posição da camera e o lookat
	Vect diferenca (posCam.getVectX() - look_at.getVectX(), posCam.getVectY() - look_at.getVectY(), posCam.getVectZ() - look_at.getVectZ());
	
	Vect dirCam = diferenca.negative().normalize();
	Vect camright = Y.crossProduct(dirCam).normalize();
	Vect camdown = camright.crossProduct(dirCam);

	Camera camera (posCam, dirCam, camright, camdown);

	Light luzCena (Vect (-1, 10 , -5), white_light);

	vector<Light*> fonteLuz;
	fonteLuz.push_back(dynamic_cast<Light*>(&luzCena));
	
	vector<Object*> objCena;
	objCena.push_back(dynamic_cast<Object*>(&esfera1));
	objCena.push_back(dynamic_cast<Object*>(&esfera2));
	objCena.push_back(dynamic_cast<Object*>(&parede));
	objCena.push_back(dynamic_cast<Object*>(&parede2));
	objCena.push_back(dynamic_cast<Object*>(&chao));
	
	int thisone, aa_index;
	double xamnt, yamnt;
	
	string entrada;
	bool exit = false;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			thisone = y*width + x;
			
			// pixel temp
			double tempRed;
			double tempGreen;
			double tempBlue;

			// Faz a modificação da imagem, quando redimensiona a janela
			if (width > height) {
				xamnt = (x+0.5) / (double)height - (((width-height)/(double)height)/2);
				yamnt = ((height - y) + 0.5)/height;
			}
			else if (height > width) {
				xamnt = (x + 0.5)/ width;
				yamnt = (height - y + 0.5)/(double) width - ((height - width)/(double)width)/2;
			}
			else {
				xamnt = (x + 0.5)/width;
				yamnt = ((height - y) + 0.5)/height;
			}

			//Origem dos raios de luz da câmera e a direção
			Vect rayOrigem = camera.posCam;
			Vect rayDirecao = dirCam.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			

			Ray rayCamera (rayOrigem, rayDirecao);
			
			vector<double> intersections;
			
			//Encontra a interseaoo dos raios da câmera com os objetos em cena
			//é salvo no vetor a quantidade de raios atingidos em cada objeto
			for (int index = 0; index < objCena.size(); index++) {
				intersections.push_back(objCena[index]->findIntersection(rayCamera));
			}
			
			int indice = winningObjectIndex(intersections);
			

			//Se nao houver interseção do ray com o objeto, o pixel é marcado como preto
			if (indice == -1) {
				tempRed = 0;
				tempGreen = 0;
				tempBlue = 0;

			//Se houver, é calculado na função getColorAt a cor (preto (sombra), branco (reflexo da luz)
			// ou a propria cod do objeto)
			}else{
				if (intersections[indice] > acuracia) {
					Vect posIntersec = rayOrigem.vectAdd(rayDirecao.vectMult(intersections[indice]));
					Vect rayDirIntersec = rayDirecao;

					Color corIntersec = getColorAt(posIntersec, rayDirIntersec, objCena, indice, fonteLuz);
					
					tempRed = corIntersec.getColorRed();
					tempGreen = corIntersec.getColorGreen();
					tempBlue = corIntersec.getColorBlue();
				}
			}

			pixels[thisone].r = tempRed;
			pixels[thisone].g = tempGreen;
			pixels[thisone].b = tempBlue;
		}
	}
	
	savebmp(width, height, pixels);

	return 0;
}
