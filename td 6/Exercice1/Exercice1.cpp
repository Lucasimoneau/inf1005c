////////////////////////////////////////////////////////////////////////////////
///// \file    Exercice1.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 01/12/2018
/// \since   Création : 21/11/2018
///
///  faire un programme pour gerer un fichier binaire comptenant des listes de films avec leurs acteurs et d'autres informations
////////////////////////////////////////////////////////////////////////////////

#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include "debogageMemoire.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "unicode.hpp"         // Nos fonctions pour l'utilisation d'Unicode sur wcin/wcout.

#include <iostream>
#include <fstream>
#include <string>
#include <cwchar>
#include <limits>
#include <algorithm>
using namespace std;

#pragma endregion//}

//TODO: Mettre les bons types pour le fichier binaire.
typedef unsigned char UInt8;
typedef unsigned short UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
wstring lireWstring(istream& fichier)
{
	wstring texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], sizeof(texte[0]) * texte.length());
	return texte;
}

#pragma endregion//}




/*TODO: Une fonction pour ajouter un Film à une ListeFilms, le film existant déjà; on veut uniquement ajouter le pointeur vers le film existant.  Vous pouvez vous inspirer de votre fonction du TD5.  Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.

[in]= liste / element

[out]=
*/
void ajouterFilm(ListeFilms& liste, Film*element) {
	if (liste.nElements < liste.capacite) {
		liste.elements[liste.nElements] = element;
		liste.nElements++;
	}
	else if (liste.capacite == 0) {
		liste.capacite = 1;
		Film** liste2 = new Film*[liste.capacite ];

		liste.elements = liste2;
		liste.elements[liste.nElements] = element;
		liste.nElements++;
	}
	else {
		Film** liste2 = new Film*[liste.capacite * 2];
		for (int i = 0; i < liste.nElements; i++) {
			liste2[i] = liste.elements[i];
		}
		liste.elements = liste2;
		liste.elements[liste.nElements] = element;
		liste.nElements++;
	}
}




/*TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.  Encore une fois, vous pouvez vous inspirer de votre fonction du TD5.

[in]= liste / film

[out]=
*/
void enleverFilm(ListeFilms& liste, Film* film) {
	for (int i = 0; i < liste.nElements; i++) {
		if (liste.elements[i] == film) {
			liste.elements[i] = liste.elements[liste.nElements - 1];
			liste.nElements--;
		}
	}
}




/*TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.

[in]= listeFilms / nom

[out]= pointeur
*/
Acteur* trouverActeur(ListeFilms& listeFilms, wstring nom) {
	Acteur* pointeur = nullptr;
	int trouver = 0;
	for (int i = 0; i < listeFilms.nElements; i++) {
		for (int j = 0; j < listeFilms.elements[i]->acteurs.nElements; j++) {
			if (listeFilms.elements[i]->acteurs.elements[j]->nom == nom) {
				pointeur = listeFilms.elements[i]->acteurs.elements[j];
				trouver = 1;
			}
		}
	}
	if (trouver == 0) {
		pointeur = nullptr;
	}
	return pointeur;
}




/*TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.  La ListeFilms devra être passée entre les fonctions, pour vérifier l'existence d'un Acteur avant de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).

[in]= listeFilms / fichier

[out]= pointeur
*/
Acteur* lireActeur(istream& fichier, ListeFilms& listeFilms){
	Acteur acteur = {};
	acteur.nom = lireWstring(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);
	for (int i = 0; i < listeFilms.nElements; i++) {
		for (int j = 0; j < listeFilms.elements[i]->acteurs.nElements; j++) {
			if (trouverActeur(listeFilms, acteur.nom) != nullptr) {
				return trouverActeur(listeFilms, acteur.nom);
			}
		}
	}
	Acteur *pointeur = new Acteur;
	*pointeur = acteur;
	wcout << "acteur cree " <<pointeur->nom<< endl;
	return pointeur; //TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations, selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées; vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
}




/*lire un film

[in]= listeFilms / fichier

[out]= pointeur
*/
Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film film = {};
	film.titre = lireWstring(fichier);
	film.realisateur = lireWstring(fichier);
	film.anneeSortie = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	film.acteurs.nElements = lireUint8(fichier);
	film.acteurs.capacite = film.acteurs.nElements;
	film.acteurs.elements = new Acteur*[film.acteurs.nElements];
	Film* pointeur = new Film;
	*pointeur = film;
	//NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs, sans faire de réallocation comme pour ListeFilms.  Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions et faire un remplacement de Film par Acteur, pour réutiliser cette réallocation.
	for (int i = 0; i < film.acteurs.nElements; i++) {
		//TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		Acteur *acteur = lireActeur(fichier, listeFilms);
		film.acteurs.elements[i] = acteur;
		//TODO: Ajouter le film aux films dans lesquels l'acteur joue.
		ajouterFilm(acteur->joueDans, pointeur);
	}	
	return pointeur; //TODO: Retourner le pointeur vers le nouveau film.
}




/*creer une liste

[in]= nomFichier

[out]= listeFilm
*/
ListeFilms creerListe(string nomFichier){
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);
	//TODO: Créer une liste de films vide.
	ListeFilms listeFilms = {};
	listeFilms.nElements = 0;
	listeFilms.capacite = nElements;
	listeFilms.elements = new Film*[nElements];
	for (int i = 0; i < nElements; i++) {
		//TODO: Ajouter le film à la liste.
		ajouterFilm(listeFilms, lireFilm(fichier, listeFilms));
	}
	return listeFilms; //TODO: Retourner la liste de films.
}




/*TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film, et les acteurs qui ne jouent plus dans aucun films de la collection).  Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.  Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.

[in]= film/ listeFilms

[out]= 
*/
void detruireFilm(Film* film, ListeFilms& listeFilms) {
	for (int i = 0; i < film->acteurs.nElements; i++) {
		enleverFilm(film->acteurs.elements[i]->joueDans, film);
		if (film->acteurs.elements[i]->joueDans.nElements == 0) {
			wcout << "destruction  des acteurs suivant: " << film->acteurs.elements[i]->nom <<endl;
			delete(film->acteurs.elements[i]);
		}
	}
	enleverFilm(listeFilms, film);
	delete(film);
}




/*TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.

[in]= listeFilms

[out]=
*/
void detruireListeFilms(ListeFilms& listeFilms) {
	int compteur = listeFilms.nElements;
	while( compteur >0) {
		compteur--;
		detruireFilm(listeFilms.elements[0], listeFilms);
		wcout <<endl << endl;
	}
}




/*afficher un acteur

[in]= acteur

[out]=
*/
void afficherActeur(const Acteur& acteur){
	wcout << "  " << acteur.nom << "   " << acteur.anneeNaissance << "   " << acteur.sexe << endl;
}




/*TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).

[in]= film

[out]=
*/
void afficheFilmActeurs(Film* film) {
	for (int i = 0; i < film->acteurs.nElements; i++) {
		afficherActeur(*film->acteurs.elements[i]);
	}
}




/*TODO: Une fonction pour afficher tous les films d'une ListeFilms.

[in]= listeFilm

[out]=
*/
void afficherFilmListeFilms(ListeFilms& listeFilms) {
	for (int i = 0; i < listeFilms.nElements; i++) {
		wcout << "  " << listeFilms.elements[i]->titre << "  " << endl;
		afficheFilmActeurs(listeFilms.elements[i]);
		wcout << endl << endl;;
	}
}




/*TODO: Une fonction pour afficher tous les films dans lesquels un acteur joue, prenant en paramètre le nom de l'acteur.  Cette fonction devrait presque uniquement faire des appels aux autres fonctions écrites.  Elle doit se comporter correctement si l'acteur n'existe pas.

[in]= listeFilm / nom

[out]=
*/
void afficheFilmsActeurJoue(wstring nom, ListeFilms& listeFilms) {
	Acteur* acteur = trouverActeur(listeFilms,nom);
	afficherFilmListeFilms(acteur->joueDans);
}




int main(){
	initDebogageMemoire(); // Affichera dans la "Sortie" de VisualStudio les fuites de mémoire, si exécuté avec débogage.
	initUnicode(); // Permet d'afficher des caractères Unicode (pas seulement les accents latin).
	static const wstring LIGNE_DE_SEPARATION = L"\n════════════════════════════════════════\n";

	//Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.
	//TODO: Lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).

	ListeFilms bin = creerListe("films.bin");

	wcout << LIGNE_DE_SEPARATION << L"Le premier film de la liste est:" << endl;
	//TODO: Afficher le premier film de la liste.  Devrait être Alien.

	wcout << bin.elements[0]->titre << endl;

	wcout << LIGNE_DE_SEPARATION << L"Les films sont:" << endl;
	//TODO: Afficher la liste des films.  Il devrait y en avoir 7.

	afficherFilmListeFilms(bin);

	//TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).

	wcout << LIGNE_DE_SEPARATION << L"Liste des films où Benedict Cumberbatch joue sont:" << endl;

	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	afficheFilmsActeurJoue(L"Benedict Cumberbatch", bin);
	wcout << endl;
	
	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.

	detruireFilm(bin.elements[0], bin);

	wcout << LIGNE_DE_SEPARATION << L"Les films sont maintenant:" << endl;
	//TODO: Afficher la liste des films.

	afficherFilmListeFilms(bin);

	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	//TODO: Détruire tout avant de terminer le programme.  Il ne devrait y avoir aucun message "Detected memory leaks!" dans la fenêtre de Sortie de VisualStudio.
	wcout << endl;
	detruireListeFilms(bin);
}