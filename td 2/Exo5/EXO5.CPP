////////////////////////////////////////////////////////////////////////////////
/// \file    exo1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  Ce code, permet de calculer la monnaie à rendre par la caisse à un utilisateur (entre des billets de 5,10,20 et 100 dollars.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cmath>


using namespace std;

int main()
{
	cout << "entrer le nom de l'item:" << endl;
	string item;
	cin >> item;
	cout << "montant de " << item << ":" << endl;
	int prix;
	cin >> prix;
	cout << "argent donne: " << endl;
	int argent;
	cin >> argent;
	int reste = argent - prix;

	int cent = reste / 100;
	cout << "billet(s) de 100 $: " << cent << endl;
	reste = reste - 100 * cent;

	int vingt = reste / 20;
	cout << "billet(s) de 20 $: " << vingt << endl;
	reste = reste - 20 * vingt;

	int dix = reste / 10;
	cout << "billet(s) de 10 $: " << dix << endl;
	reste = reste - 10 * dix;

	int cinq = reste / 5;
	cout << "billet(s) de 5 $: " << cinq << endl;
	reste = reste - 5 * cinq;

	cout << "billet(s) de 1 $: " << reste << endl;

	return 0;

}