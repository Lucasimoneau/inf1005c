////////////////////////////////////////////////////////////////////////////////
/// \file    exo4.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  Ce code calcul la distance maximale, a l'aide de l'angle et d'une vitesse.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	const double G= 9.8;
	const double PI = 3.141592653589793;
	cout << "entrer l'angle et la vitesse" << endl;
	double o, v;
	cin >> o >> v;
	double angle = (o*(PI)) / 180;
	double t = (2 * v*sin(angle)) / G;
	double x = v * cos(angle) *t;
	cout << "la distance maximale est de " << x << "metres" << endl;

	return 0;

}