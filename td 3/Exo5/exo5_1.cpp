////////////////////////////////////////////////////////////////////////////////
/// \file    exo5-1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  entrer un nombre n de coordonnes puis le programme calcul le centre de gravite avec le point le plus proche et le plus loin
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	cout << "entrer un n avec 1<=n<=10 ";
	int n, x,y,xmin,ymin,xmax,ymax;
	double distance, xc, yc, distancemin, distancemax;
	distancemin = 999999;
	distancemax = -999999;

	cin >> n;
	while (n > 10 or n < 1)
	{
		cout << "erreur entrer un n avec 1<=n<=10 ";
		cin >> n;
	}

	vector<int> tableaux(n * 2);

	for (int i = 0; i < n*2; i=i+2)
	{
		cout << "entrer coordonnes x et y" << endl;
		cin >> x >> y;
		tableaux[i] = x;
		tableaux[i+1] = y;
	}

	xc = 0;
	yc = 0;

	for (int o = 0; o < n * 2; o = o + 2)
	{
		xc= xc + tableaux[o];
		yc = yc + tableaux[o+1];
	}
	xc = xc / n;
	yc = yc / n;
	cout << "Le centre de gravité est de coordonnes :  " << xc << " " << yc << endl;

	for (int p = 0; p< n * 2; p = p + 2)
	{
		distance = sqrt(pow(xc - tableaux[p], 2) + pow(yc - tableaux[p + 1], 2));

		if (distance<distancemin)
		{ 
			xmin = tableaux[p];
			ymin = tableaux[p + 1];
			distancemin = distance;
		}
		if (distance> distancemax)
		{
			xmax = tableaux[p];
			ymax = tableaux[p + 1];
			distancemax = distance;
		}
	}
	cout << "Coordonnees du point le plus proche : " << xmin << " " << ymin << endl;
	cout << "Coordonnees du point le plus distant : " << xmax << " " << ymax << endl;
	return 0;

}