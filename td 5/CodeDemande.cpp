////////////////////////////////////////////////////////////////////////////////
///// \file    td5.cpp
/// \authors  Lucas Simoneau  Arthur Leboiteux
/// \matricules 1885195       1896761
/// \version Dernière entrée : 20/11/2018
/// \since   Création : 7 novembre 2018
///
///  faire un programme pour le fonction d'un drone qui analyse des donnees binaires
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"
#include "CodeDemande.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

#pragma endregion //}


#pragma region "Globaux" //{

#pragma region "Fonctions" //{




/*
fonction qui permet d'ajouter des cibles

in : liste , element
out: liste element
*/
void ajouterCible(ListeCibles& liste, const Cible& element)
{
	// TODO: S'il reste de la place, ajouter l'élément à la fin.
	if (liste.nbElements < liste.capacite) {
		liste.elements[liste.nbElements] = element;
		liste.nbElements++;
	}

}






/*
fonction qui permet de retirer des cibles

in : liste , id
out: liste
*/
void retirerCible(ListeCibles& liste, uint32_t id)
{
	// TODO: Rechercher la cible avec le même ID et le retirer de la liste si
	//       présent. ATTENTION! On parle bien de Cible::id, pas de l'index 
	//       dans le tableau.

	for (unsigned int i = 0; i < liste.nbElements; i++) {
		if (id == liste.elements[i].id) {
			for (unsigned int o = i; o < liste.nbElements - 1; o++) {
				liste.elements[o] = liste.elements[o + 1];
			}
			liste.nbElements--;
		}
	}
}







/*
fonction qui permet de lire des cibles

in :cibles , fichier
out: fichier, cibles
*/
void lireCibles(istream& fichier, ListeCibles& cibles)
{
	// TODO: Tant que la fin de fichier n'est pas atteinte :
		// TODO: Lire une 'Cible' à partir du ficher à la position
		//       courante et l'ajouter à la liste.

	int compteur = 0;
	Cible valeur;
	while (fichier.peek() != EOF) {
		fichier.read((char*)&valeur, sizeof(valeur));
		ajouterCible(cibles, valeur);
		compteur++;
	}
}






/*
fonction qui permet d'ecrire des cibles

in : fichier , cibles
out: fichier , cibles
*/
void ecrireCibles(ostream& fichier, const ListeCibles& cibles)
{
	// TODO: Écrire tous les éléments de la liste dans le fichier à partir de la position courante.

	for (unsigned int i = 0; i < cibles.nbElements; i++) {
		fichier.write((char*)&cibles.elements[i], sizeof(cibles.elements[i]));
	}
}





/*
fonction qui permet d'ecrire un journal de detection

in : nomfichier, journal, ok 
out: nomfichier, journal, ok
*/
void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok)
{
	// TODO: Ouvrir un fichier en écriture binaire.

	ofstream fichier(nomFichier, ios::binary);
	
	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.

	if (fichier.fail()) {
		ok = 0;
	}
	else {
		ok = 1;
	}

	// TODO: Écrire les paramètres de mission dans le fichier.

	fichier.write((char*)&journal.parametres, sizeof(journal.parametres));

	// TODO: Écrire les cibles dans le fichier.

	for (unsigned int i = 0; i < journal.cibles.nbElements; i++) {
		fichier.write((char*)&journal.cibles.elements[i], sizeof(journal.cibles.elements[i]));
	}
}




/*
fonction qui permet d'ecrire des observations

in : nomfichier, index, observation
out: nomfichier, observation
*/
void ecrireObservation(const string& nomFichier, size_t index, const string& observation)
{
	// TODO: Ouvrir un fichier en lecture/écriture binaire.

	fstream fichier(nomFichier, ios::in | ios::out | ios::binary);
	Cible cible;

	// TODO: Se positionner (têtes de lecture et d'écriture) au début de la cible 
	//       à l'index donné. On parle ici de l'index dans le fichier, donc 0 est
	//       la première cible dans le fichier, etc.

	fichier.seekg(index * sizeof(cible) + sizeof(ParametresMission), ios::beg);

	// TODO: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isolée, pas tout le
	//       tableau.

	fichier.read((char*)&cible, sizeof(cible));

	// TODO: Copier l'observation donnée en paramètre dans la cible.
	//       Astuce : strcpy()

	strcpy_s(cible.observation, observation.c_str());

	// TODO: Réécrire la cible (et seulement celle-là) dans le fichier.	

	fichier.seekp(index * sizeof(cible) + sizeof(ParametresMission), ios::beg);
	fichier.write((char*)&cible, sizeof(cible));
}






/*
fonction qui permet d'allouer des listes

in : capacite
out: 
*/
ListeCibles allouerListe(size_t capacite)
{
	// TODO: Créer une 'ListeDonnee' vide (nbElements = 0) avec la capacité donnée.

	ListeCibles ListeDonnee = {};
	ListeDonnee.capacite = capacite;
	ListeDonnee.nbElements = 0;

	// TODO: Allouer un tableau de 'Cible' de la taille demandée.

	ListeDonnee.elements = new Cible[capacite];
	return ListeDonnee;
}




/*
fonction qui permet de desallouer des listes

in : cibles
out: cibles
*/
void desallouerListe(ListeCibles& cibles)
{
	// TODO: Désallouer le tableau d'élément.

	delete[] cibles.elements;

	// TODO: Remettre les membres à zéro.

	cibles.capacite = 0;
	cibles.nbElements = 0;
}




/*
fonction qui permet de lire le journal de detection

in : nomficheir, ok
out: nomfichier, ok
*/
JournalDetection lireJournalDetection(const string& nomFichier, bool& ok)
{
	JournalDetection journal;
	// TODO: Ouvrir un fichier en lecture binaire.
	ifstream fichier(nomFichier, ios::in|ios::binary);
	Cible cible;

	int compteur = 0;
	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.

	if (fichier.fail()) {
		ok = false;
	}
	else {
		ok = true;
	}

	// TODO: Lire les paramètres de mission

	fichier.read((char*)&journal.parametres, sizeof(ParametresMission));
	while (fichier.peek() != EOF) {
		fichier.read((char*)&cible, sizeof(Cible));

		// TODO: Compter le nombre de cibles dans le fichier.

		compteur++;
	}

	// TODO: Allouer la liste de cibles avec la bonne capacité.

	journal.cibles = allouerListe(compteur);

	// TODO: Lire les cibles.

	fichier.seekg(sizeof(ParametresMission), ios::beg);
	lireCibles(fichier, journal.cibles);

	return journal;
}

#pragma endregion //}

#pragma endregion //}

