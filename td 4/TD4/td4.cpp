////////////////////////////////////////////////////////////////////////////////
/// \file    td4.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 17 octobre 2018
///
///  programme qui produit des images fractales par systemes de fonctions iterees.
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include "ecrireimage.h"
#include <cstdlib>     
#include <ctime>

using namespace std;


/*Fonction borneDansIntervalle renvoye la valeur a borner si elle est dans l'intervalle .
Sinon elle renvoye la borne la plus proche

[out]=borneInferieur / borneSuperieure /  return valeurABorner

[in]=valeurABorner / borneInferieure / borneSuperieure
*/
int borneDansIntervalle(int valeurABorner, int borneInferieure, int borneSuperieure){
	if (valeurABorner < borneInferieure){
		return borneInferieure ;
	}
	if (valeurABorner > borneSuperieure){
		return borneSuperieure ;
	}
	else{
		return valeurABorner;
	}
}


/*Fonction estDansIntervalle ; renvoye 1 ou 0 si la valeur a borner appartient aux bornes .

[out]= true / false

[in]=valeurABorner / borneInferieure / borneSuperieure
*/
bool estDansIntervalle(int valeurABorner, int borneInferieure, int borneSuperieure){
	if (valeurABorner >= borneInferieure and valeurABorner <= borneSuperieure){
		return true ;
	}
	else{
		return false ;
	}
}


/*Fonction dessinePoint; permet de dessiner un point avec une certaine intensite

[out]= rien

[in/out]=point / intensite / image[tailleY][tailleX]
*/
void dessinePoint(Point2d point, int intensite, Pixel image[tailleY][tailleX]){
	int x = int(point.x);
	int y = int(point.y);
	if (estDansIntervalle(x, 0, tailleX) and estDansIntervalle(y, 0,tailleY)){
		image[y][x] = borneDansIntervalle(image[y][x] - intensite, 0, 255);
	}
}


/*Fonction aleatoireZeroUN; permet de renvoyer un nombre entre 0 et 1

[out]= hasard

[in]= rien
*/
double aleatoireZeroUn(){
	double hasard = double((rand() % 100)) / 100;
	return (hasard);
}


/*Fonction aleatoireSelonDistribution; permet de donner un entier aleatoire d'une distribution discrete

[out]= numero

[in]=tableau[10]
*/
int aleatoireSelonDistribution(double tableaux[10]){
	double x = aleatoireZeroUn();
	int numero=0;
	for (int i = 0; i < 10; i++) {
		if (tableaux[i]/100 == 1) {
			break;
		}
		else if (x > tableaux[i]/100) {
			numero=i+1;
		}
	}
	return (numero);
}

/*Fonction transformePoint; permet de transformer un point selon un calcul

[out]= pointTrans

[in]=x / y / transformation[3][2]
*/
Point2d transformePoint(double x, double y, double transformations[3][2]) {					
	Point2d pointTrans;
	pointTrans.x = transformations[0][0] * x + transformations[0][1] * y + transformations[2][0];
	pointTrans.y = transformations[1][0] * x + transformations[1][1]* y + transformations[2][1];
	return (pointTrans);
}


/*Structure informationsfichier; 

*/
struct informationsfichier {
	int nombrePoints, nombreTransPointDepart, nombreTransAvantAfficher, intensite;
	double transAffichages[3][2];
	double trans[10][3][2];
	double probaCumulatives[10];
};


/*Fonction calculerImage; permet de reprendre la plus part des fonctions precedentes et de les utiliser pour en faire une image .

[out]= rien

[in/out]= fichierEntree / fichierSortie
*/
void calculerImage(string fichierEntree, string fichierSortie){

	ifstream points(fichierEntree + ".txt");	//lire le fichier
	informationsfichier donnees;
	points >> donnees.nombrePoints >> donnees.nombreTransPointDepart >> donnees.nombreTransAvantAfficher >> donnees.intensite
		   >> donnees.transAffichages[0][0] >> donnees.transAffichages[0][1] >> donnees.transAffichages[1][0] >> donnees.transAffichages[1][1] >> donnees.transAffichages[2][0] >> donnees.transAffichages[2][1];
	int compteur = 0;
	while (!ws(points).eof()) {
		points >> donnees.trans[compteur][0][0] >> donnees.trans[compteur][0][1] >> donnees.trans[compteur][1][0] >> donnees.trans[compteur][1][1] >> donnees.trans[compteur][2][0] >> donnees.trans[compteur][2][1]
			   >> donnees.probaCumulatives[compteur];
		compteur++;
	}

	Pixel image[tailleY][tailleX];		//image en blanc (255);
	for (int i = 0; i < tailleY; i++){
		for (int j = 0; j < tailleX; j++){
			image[i][j] = 255;
		}
	}
	
	for (int i = 0; i < donnees.nombrePoints; i++) {  
		Point2d point;
		point.x = aleatoireZeroUn();
		point.y = aleatoireZeroUn();
		for (int j = 0; j< donnees.nombreTransPointDepart; j++) {
			
			int indice=aleatoireSelonDistribution(donnees.probaCumulatives);
			double tableaux[3][2];
			for (int k = 0; k < 3; k++) {
				for (int u = 0; u < 2; u++) {
					tableaux[k][u]=donnees.trans[indice][k][u];
				}
			}

			Point2d nouveauPoint = transformePoint(point.x, point.y, tableaux);   
			point.x = nouveauPoint.x;	
			point.y = nouveauPoint.y;	

			if (j >=donnees.nombreTransAvantAfficher) {
				Point2d pointADessiner = transformePoint(point.x, point.y, donnees.transAffichages);
				dessinePoint(pointADessiner, donnees.intensite, image);
			}
		}
	}
	ecrireImage(image, fichierSortie + ".bmp");
}


/*Fonction test; permet de faire tout nos test

*/
void tests(void){
	/*for (int i = -1; i <= 4; i++) {
		cout<<borneDansIntervalle(i, 1, 3)<<endl;
		cout << estDansIntervalle(i, 1, 3) << endl;
		
	}*/

	/* Pixel image[tailleY][tailleX];
	for (int i = 0; i < tailleX; i++)
	{

		for (int j = 0; j < tailleY; j++)
		{
			image[i][j] = 255;
		}
	}
	dessinePoint({ 10, 10 }, 255, image);
	dessinePoint({ 20, 15 }, 100, image);
	dessinePoint({ 30, 20 }, 128, image);
	dessinePoint({ -1, 1 }, 255, image);
	dessinePoint({ 500, 1 }, 255, image);
	dessinePoint({1, -1}, 255, image);
	dessinePoint({ 1, 500 }, 255, image);
	dessinePoint({ 30, 20 }, 128, image);
	ecrireImage(image, "imageTest.bmp"); */


/*	int compteur = 0;
	double tableau[10] = {10,35,100};
	for (int t = 0; t < 1000; t++) {
		if (aleatoireSelonDistribution(tableau) == 1) {
			compteur++;
		}
	}
	cout << compteur<< endl;
	*/
	/*double transformation[3][2] = { {0.5,-0.5},{0.25,0.75},{2.0,3.0} };
	cout<<transformePoint(0.2, 0.7, transformation).x<<endl;
	cout << transformePoint(0.2, 0.7, transformation).y<<endl;*/

	calculerImage("Barnsley fern", "Barnsley fern");
	calculerImage("Golden dragon agrandi", "Golden dragon agrandi");
	calculerImage("Golden dragon", "Golden dragon");
	calculerImage("Heighway dragon", "Heighway dragon");
	calculerImage("Sierpensky triangle", "Sierpensky triangle");
}


/*Fonction main; fonction principale

*/
int main(void){
	srand(unsigned(time(NULL)));
	tests();
	return 0;
}