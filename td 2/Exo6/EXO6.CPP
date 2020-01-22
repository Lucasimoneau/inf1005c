////////////////////////////////////////////////////////////////////////////////
/// \file    exo1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 2018-09-20
/// \since   Création : 2018-09-12
///
///  Ce code permet d'aller chercher des informations dans un fichier, puis de les traiter pour enfin les redistribuer d'une differente maniere dans un nouveau fichier.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <iomanip>
df#include <fstream>

using namespace std;

int main()
{
	int nombre11;
	int nombre12;
	int nombre13;
	int nombre21;
	int nombre22;
	int nombre23;
	string  ville;
	string  joueur1;
	string  joueur2;
	ifstream donnees("res.txt");

	getline(donnees, ville);
	getline(donnees, joueur1);
	donnees >> nombre11;
	donnees >> nombre12;
	donnees >> nombre13;
	donnees.ignore();
	getline(donnees, joueur2);
	donnees >> nombre21;
	donnees >> nombre22;
	donnees >> nombre23;
	double moyenne1 = (nombre11 + nombre12 + nombre13) / 3;
	double moyenne2 = (nombre21 + nombre22 + nombre23) / 3;
	
	ofstream Vainqueur("Vainqueur.txt");
	Vainqueur << ville << endl << joueur1 << " " << moyenne1 << endl << joueur2 << " " << moyenne2 << endl << joueur1 << " meilleur que " << joueur2 << "? ";
	bool question(moyenne1<moyenne2);
	Vainqueur << boolalpha << question;
	
	return 0;
}