////////////////////////////////////////////////////////////////////////////////
/// \file    exo1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  calculer coordonnees centre de gravite d un triangle a l aide des coordonnees de trois points
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;
int main()

{
	cout << "donne moi les coordonnées de xA, yA, xB, yB, xC, yC" << endl;
	double xa, ya, xb, yb, xc, yc;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;

	double xd = (xa + xb + xc) / 3;
	double yd = (ya + yb + yc) / 3;

	cout << "les cooordonnees de xD: " << xd << " de yD: " << yd << " ";
	return 0;
}