////////////////////////////////////////////////////////////////////////////////
/// \file    exo5-2.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  realiser le meme programme que pour l exercice 5.1 sauf que l'on range les coordonne par couleur(R B V)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int main()
{	
	int valeur1, valeur2,b,r,v, xmin, ymin, xmax, ymax;
	double distance, distancemin, distancemax;
	string couleur;
	b = 0; v = 0; r = 0;
	distancemin = 999999; distancemax = -999999;
	ifstream points("points.txt");
	vector<int> verts;
	vector<int> rouges;
	vector<int> bleus;

	while (!ws(points).eof()) //On lit chaque ligne du fichier que l'on stoke dans "ligne" 
	{
		points >> valeur1;
		points >> valeur2;
		points >> couleur;

		if (couleur == "V")
		{
			verts.push_back(valeur1);
			verts.push_back(valeur2);
			v++;

		}
		else if(couleur=="R")
		{
			rouges.push_back(valeur1);
			rouges.push_back(valeur2);
			r++;
		}
		else if(couleur=="B")
		{
			bleus.push_back(valeur1);
			bleus.push_back(valeur2);
			b++;
		}

	}
	int x, y;
	cout << "veuillez entrer un x et un y" << endl;
	cin >> x >> y;
	string c;
	cout << "veuillez entrer une couleur= R ou B ou  V en majuscule " << endl;
	cin >> c;

	if (c == "V")
	{
		if  (verts.size()==0)
		{}

		else
		{

			for (int i = 0; i < v * 2; i = i + 2)
			{
				distance = sqrt(pow(x - verts[i], 2) + pow(y - verts[i + 1], 2));
		
				if (distance <= distancemin)
				{
					xmin = verts[i];
					ymin = verts[i + 1];
					distancemin = distance;
				}
				if (distance >= distancemax)
				{
					xmax = verts[i];
					ymax = verts[i + 1];
					distancemax = distance;
				}
				
			}
		}
	}
	if (c == "R")
	{
		if (rouges.size() == 0)
		{}

		else
		{
			for (int o = 0; o < r * 2; o = o + 2)
			{
				distance = sqrt(pow(x - rouges[o], 2) + pow(y - rouges[o + 1], 2));

				if (distance <= distancemin)
				{
					xmin = rouges[o];
					ymin = rouges[o + 1];
					distancemin = distance;
				}
				if (distance >= distancemax)
				{
					xmax = rouges[o];
					ymax = rouges[o + 1];
					distancemax = distance;
				}
			}
		}
	}
	if (c == "B")
	{
		if (bleus.size() == 0)
		{}

		else
		{

			for (int p = 0; p < b * 2; p = p + 2)
			{
				distance = sqrt(pow(x - bleus[p], 2) + pow(y - bleus[p + 1], 2));

				if (distance <= distancemin)
				{
					xmin = bleus[p];
					ymin = bleus[p + 1];
					distancemin = distance;
				}
				if (distance >= distancemax)
				{
					xmax = bleus[p];
					ymax = bleus[p + 1];
					distancemax = distance;
				}
			}
		}
	}

	if (c == "B" and bleus.size() == 0 or c == "V" and verts.size() == 0 or c == "R" and rouges.size() == 0)
	{
		cout << "Il n'existe pas de points de cette couleur dans le fichier " << endl;
	}

	else
	{

		cout << "les coordonnees du point le plus proche est " << xmin << " " << ymin << endl;
		cout << "les coordonnees du point le plus loin est " << xmax << " " << ymax << endl;
	}
	
	points.close();
	return 0;


}