////////////////////////////////////////////////////////////////////////////////
/// \file    exo2.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  Correction du code donné dans l'exercice 2. Il cherche a trouver les racines d'une equation du second degrée donné par un usager.
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

	c = c - y; //enlever y à c
	double discriminant = pow(b, 2) - 4 * a * c;
	bool valeurPasBonne = discriminant < 0;

	double x1 = (-b + sqrt(discriminant)) / (2 * a);
	double x2 = (-b - sqrt(discriminant)) / (2 * a);

	cout << "Les 2 valeurs de x pour ce y sont : " << x1 << " et " << x2 << endl << boolalpha << !valeurPasBonne << endl;

	return 0;
}