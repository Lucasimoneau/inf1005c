////////////////////////////////////////////////////////////////////////////////
/// \file    exo4.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  lire un fichier et puis faire un histogramme avec le nombre de caractere
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>


using namespace std;

int main()
{
	
	string  nom;
	cout << "entre le nom de ton fichier texte sans .txt:" << endl;
	cin >> nom;
	nom = nom + ".txt";
	string mot;
	ifstream fichier(nom);
	vector<int> histogrammes(30,0);

	while(fichier.fail())
	{
		cout << " Probleme d'ouverture, entrer un fichier texte valide sans .txt :" << endl;
		cin >> nom;
		nom = nom + ".txt";
		fichier.open(nom);
	}

	while (!ws(fichier).eof())
	{
		fichier >> mot;
		int taille = mot.size();
		histogrammes[taille-1] = histogrammes[taille-1] + 1;	
	}	

	for (int i = 0; i < 30; i++)
	
	{ 
		if (histogrammes[i] == 0)
		{}
		else
		{
			cout << "nombres de mots avec " << i + 1 << " caracteres: ";
			for (int o = 0; o < histogrammes[i]; o++)
			{
				cout << "*";
			}
			cout << endl;
		}
	}

	fichier.close(); //On ferme le fichier 
	
	return 0;

}