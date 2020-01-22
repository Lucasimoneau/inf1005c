////////////////////////////////////////////////////////////////////////////////
/// \file    exo2.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  trouver tout les nombres entre 100 et 500 dont la somme de leurs nombre puissance 3 est egales a leurs nombres
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;

int main()
{
	
	for (int i = 100; i <= 500; i++)
	{
		string nombre = to_string(i);

		int x1 = nombre[0] - 48;
		int x2 = nombre[1] - 48;
		int x3 = nombre[2] - 48;

		if (pow(x1, 3) + pow(x2, 3) + pow(x3, 3) == i)
		{
			cout << i<<endl;
		}
	}
	
	
	return 0;

}