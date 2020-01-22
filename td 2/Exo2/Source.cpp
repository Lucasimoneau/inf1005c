////////////////////////////////////////////////////////////////////////////////
/// \file    exo2.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Derni�re entr�e : 2018-09-20
/// \since   Cr�ation : 2018-09-12
///
///  Correction du code donn� dans l'exercice 2. Il cherche a trouver les racines d'une equation du second degr�e donn� par un usager.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int a, b, c, y;

	cout << "Entrer a, b et c : " << endl;
	cin >> a >> b >> c;

	cout << "Entrer y : " << endl;
	cin >> y;

	c = c - y; //enlever y � c
	double discriminant = pow(b, 2) - 4 * a * c;
	bool valeurPasBonne = discriminant < 0;

	double x1 = (-b + sqrt(discriminant)) / (2 * a);
	double x2 = (-b - sqrt(discriminant)) / (2 * a);

	cout << "Les 2 valeurs de x pour ce y sont : " << x1 << " et " << x2 << endl << boolalpha << !valeurPasBonne << endl;

	return 0;
}