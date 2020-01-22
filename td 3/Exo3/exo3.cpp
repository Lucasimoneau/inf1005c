////////////////////////////////////////////////////////////////////////////////
/// \file    exo3.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  changer une lettre d"un mot par une autre lettre
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
	cout << "entrer la lettre que tu veux remplacer et la lettre qui la remplacera"<<endl;
	char lettre1, lettre2;
	cin >> lettre1 >> lettre2;

	for (int i = 0; i < nombre; i++)
	{
		if (chaine[i] == lettre1)
		{
			chaine[i] = lettre2;
		}
	}
	cout << "la chaine de caractere est maintenant: " << chaine << endl;
	return 0;

}