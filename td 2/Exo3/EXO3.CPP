////////////////////////////////////////////////////////////////////////////////
/// \file    exo3.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  Le code transforme une chaine de caractere entrée par un usager.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string chaine;
	cout << "Entrer une chaine de caractere :" << endl;
	getline(std::cin, chaine);
	int nombre;
	nombre = chaine.size();
	cout << "Saisir un nombre entre 1 et " << nombre << endl;
	int place;
	cin >> place;
    chaine.insert(nombre, "" );
	chaine[0] = toupper(chaine[0]);

	string partie1 = chaine.substr(0, place);
	string partie2 = chaine.substr(place, nombre);
	cout << partie2 << endl << setw(nombre) << partie1 << endl;

	return 0;

}