////////////////////////////////////////////////////////////////////////////////
/// \file    exo1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée :
/// \since   Création : 3 octobre 2018
///
///  utiliser le binome de Newton
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main()
{
	cout << "entrez n et k" << endl;
	double n = 0;
	double k= 0;
	cin >> n>> k;
	while (n < k)
	{
		cout << "erreur entrer un n>k";
		cin >> n >> k;
	}

	double i, bin;
	i = n - 1;
	bin = 1;
	if (k != n)
	{
		while (i != k)
		{
			bin = bin * ((i + 1) / (n - i));
			i = i - 1;
		}
	}
	cout << "le binome de Newton est " << bin << endl;
	return 0;

}