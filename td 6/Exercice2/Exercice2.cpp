////////////////////////////////////////////////////////////////////////////////
///// \file    Exercice2.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 01/12/2018
/// \since   Création : 21/11/2018
///
///  faire un programme pour convertir des nombres
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <math.h> 

using namespace std;

string lireEntree(){
	string texte;
	getline(cin, texte);
	return texte;
}




void afficherTexte(const string& texte){
	cout.write(&texte[0], texte.size());
}




/*TODO: Fonction dec2int.

[in]= decimal

[out]=final
*/
int dec2int(string decimal) {
	int final = 0;
	for (int i = 0; i < int(decimal.size()); i++) {
		final += int(pow (10,(decimal.size() - (i + 1))))*(decimal[i] - 48);
	}
	return final;
}




/*TODO: Fonction hex2int.

[in]= hexadecimal

[out]=final
*/
int hex2int(string hexadecimal) {
	int final = 0;
	for (int i = 0; i < int(hexadecimal.size()); i++) {
		int lettre = 0;
		if (hexadecimal[i] == 'A') {
			lettre = 10;
		}
		else if (hexadecimal[i] == 'B') {
			lettre = 11;
		}
		else if (hexadecimal[i] == 'C') {
			lettre = 12;
		}
		else if (hexadecimal[i] == 'D') {
			lettre = 13;
		}
		else if (hexadecimal[i] == 'E') {
			lettre = 14;
		}
		else if (hexadecimal[i] == 'F') {
			lettre = 15;
		}
		if (lettre == 0) {
			final += int(pow(16, (hexadecimal.size() - (i + 1))))*(hexadecimal[i] - 48);
		}
		else {
			final += int(pow(16, (hexadecimal.size() - (i + 1))))*(lettre);
		}
	}
	return final;
}




/*TODO: Fonction int2dec.

[in]= nombre

[out]=final
*/
string int2dec(int nombre) {
	string final = "";
	char chiffre = NULL;
	int compteur = 1;
	while (nombre != 0) {
		int test = nombre / (int(pow(10, compteur)));
		if (-1 < test && test < 1) {
			break;
		}
		else {
			compteur++;
		}
	}
	for (int i = compteur; i >= 1; i--) {
		double unChiffre = int(nombre / (int(pow(10, i - 1))));
		if (i < compteur) {
			unChiffre /= 10;
			unChiffre -= int(unChiffre);
			unChiffre *= 10;
			unChiffre = round(unChiffre);
		}
		chiffre = unChiffre;
		final += chiffre + 48;
	}
	return final;
}




int main(){
	afficherTexte("Entrer un nombre decimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string decimal = lireEntree();

	afficherTexte("Entrer un nombre hexadecimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string hexadecimal = lireEntree();

	//TODO: Utiliser vos fonctions dec2int, hex2int et int2dec pour calculer la somme des deux nombres.
	string somme = int2dec(dec2int(decimal) + hex2int(hexadecimal));

	afficherTexte("La somme decimale est: ");
	//TODO: Afficher la somme en utilisant afficherTexte.
	afficherTexte(somme);
}