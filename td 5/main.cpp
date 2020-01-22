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

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "CodeDemande.hpp"
#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}




void tests_partie1()
{
	// Dans la partie 1, on déclare une liste de cibles avec un tableau statique, puisque l'allocation dynamique est vue en classe seulement la semaine suivante.
	Cible tableauCibles[3] = {};
	ListeCibles cibles = { tableauCibles, 0, size(tableauCibles) };

	//TODO: Ajouter 3 fois une cible (ajouterCible) à la cibles, chacun avec un ID différent (les autres valeurs ne sont pas importantes);
	//TODO: après chaque ajout vérifier que le nombre de cibles est bon (i.e. 1 après le premier ajout, 2 après le deuxième), et que les données de la cible sont dans la liste (vérifiez uniquement l'ID).
	//TODO: Ajouter une autre cible, le nombre d'éléments devrait être encore 3 puisque c'est la capacité de la liste.
	Cible element1 = { 000000, {0,0},'0','0' };
	Cible element2 = { 111111,{ 0,0 },'0','0' };
	Cible element3 = { 333333,{ 0,0 },'0','0' };
	Cible element4 = { 444444,{ 0,0 },'0','0' };

	ajouterCible(cibles, element1);
	cout << "Apres 1 ajout:" << endl;
	afficherCibles(cibles);

	ajouterCible(cibles, element2);
	cout << "Apres 2 ajout:" << endl;
	afficherCibles(cibles);

	ajouterCible(cibles, element3);
	cout << "Apres 3 ajout:" << endl;
	afficherCibles(cibles);

	ajouterCible(cibles, element4);
	cout << "Apres 4 ajout:" << endl;
	afficherCibles(cibles);

	//TODO: Retirer la cible (retirerCible) ayant l'ID que vous avez mis en 2e, vérifier qu'il reste 2 éléments aux indices 0 et 1 dont les ID sont les bons.
	retirerCible(cibles, 111111);
	cout << "Apres avoir enelever la 2e cible: " << endl;
	afficherCibles(cibles);

	//TODO: Écrire les cibles (ecrireCibles) dans le fichier fichierTestCibles. Vérifier que la tête d'écriture est rendue au bon endroit.
	fstream fichierTestCibles("fichierTestCibles.bin", ios::in | ios::out | ios::trunc | ios::binary);
	ecrireCibles(fichierTestCibles, cibles);

	Cible tableauCibles2[3] = {};
	ListeCibles cibles2 = { tableauCibles2, 0, size(tableauCibles) };
	if (fichierTestCibles.tellg() == sizeof(Cible)*cibles.nbElements) {
		cout << "c'est au bon endroit" << endl;
	}
	else {
		cout << "Pas au bon endroit";
	}

	//TODO: Remettre la tête de lecture au début du fichier puis lire les cibles (lireCibles) dans cibles2. Vérifier que les 2 bonnes cibles y sont.

	fichierTestCibles.seekg(0, ios::beg);
	lireCibles(fichierTestCibles, cibles2);
	cout << "Conteu cibles2:" << endl;
	afficherCibles(cibles2);

	//TODO: Créer une variable de type JournalDetection avec des valeurs quelconques et une ListeCibles déjà créé ci-dessus.

	JournalDetection testjournal = { {"test","ceci est un test journal detection",{0,0,0,1,0,1950,0,0,1}}, cibles2 };

	//TODO: Écrire ce journal (ecrireJournalDetection) dans un nouveau fichier binaire.

	fstream fichier_binaire("fichierjournal.bin", ios::in | ios::out | ios::trunc | ios::binary);
	bool ok;
	ecrireJournalDetection("fichierjournal.bin", testjournal, ok);

	//TODO: Vérifier que ok est vrai.
	if (ok == 1) {
		cout << "c'est vrai";
	}

	//NOTE: La relecture du fichier pour vérifier qu'il est bon se fera seulement dans la partie 2.  Vous pouvez pour l'instant vérifier que la taille du fichier est bonne (propriétés du fichier dans Windows; la "taille" en octets devrait être une taille d'entête plus le bon nombre de cibles; attention de ne pas regarder la "taille sur disque" qui peut être différente de la "taille" dans les propriétés du fichier).  Vous pouvez aussi ouvrir le fichier binaire avec un éditeur binaire (par exemple celui de VisualStudio) pour voir si les ID sont bien dans le fichier.

	//TODO: Ajouter une observation (ecrireObservation) au fichier créé ci-dessus à l'indice 1 (deuxième cible).
	//NOTE: Même chose que ci-dessus: la taille du fichier ne devrait pas avoir changée, et dans l'éditeur binaire vous devriez voir le texte après le deuxième ID.

	ecrireObservation("fichierjournal.bin", 2, "test ecrireobservation");

}




void tests_partie2()
{
	cout << endl << "PARTIE 2" << endl << endl;
	//TODO: Allouer une liste de cibles (allouerListe) de capacité 2; vérifier que la capacité est la bonne et que le nombre d'éléments est zéro.
	ListeCibles cibles = allouerListe(2);
	cout << "Capacite: " << cibles.capacite << " nombre d'elements: " << cibles.nbElements << endl;


	//TODO: Ajouter une cible la liste; ça devrait fonctionner.
	Cible element1 = { 000000, {0,0},'0','0' };
	ajouterCible(cibles, element1);
	cout << "test ajouter Cible " << endl;
	afficherCibles(cibles);

	//TODO: Conserver le pointeur vers le tableau de cibles dans une variable.
	Cible* pointeurTableau = cibles.elements;

	//TODO: Désallouer la liste (desallouerListe); vérifier que les valeurs sont à zéro.
	desallouerListe(cibles);
	cout << "Apres avoir desallouer, Capacite: " << cibles.capacite << " nombre d'elements: " << cibles.nbElements << endl;
	//TODO: Allouer une nouvelle liste de cibles de capacité 2; vérifier que son pointeur est le même que celui conservé ci-dessus.  NOTE: Il n'y a pas de manière dans le standard ISO C++ pour vérifier que la mémoire a bien été désallouée.  Ce test n'est donc pas standard et pourrait échouer même si le programme est correct, mais on a la garantie qu'il peut réussir uniquement si la désallocation est faite.
	ListeCibles nouvelleListe = allouerListe(2);
	if (nouvelleListe.elements == pointeurTableau) {
		cout << "c'est le meme pointeur" << endl;
	}
	//TODO: Désallouer cette deuxième liste.
	desallouerListe(nouvelleListe);

	//NOTE: lireJournalDetection est directement testé par ce qu'il y a à faire dans le main.

}





int main()
{
	tests_partie1();
	tests_partie2();

	const string nomFichierCibles = "Cibles.data";
	const string nomFichierCiblesFinal = "Cibles_final.data";

	string observation = "Cercle noir, E rouge";

	Cible c11 = { 11, {38.140728, -76.426494}, "Triangle gris, O orange", "cible_11.jpg" };

	// TODO: Lire le journal de détection "Cibles.data".

	bool ok;
	JournalDetection journal = lireJournalDetection("Cibles.data", ok);

	// TODO: Faire la vérification d'erreur et terminer le programme avec un
	//       message s'il y a erreur.

	if (!ok) {
		cout << "Le fichier data cibles ne c est pas ouvert" << endl;
		return -10;
	}
	else
	{
		cout << "le fichier data est ouvert" << endl;
	}

	// TODO: Afficher le journal.  (Devrait afficher un journal avec 10 cibles ayant des données valides.)

	afficherJournal(journal);

	// TODO: Retirer la cible 5 de la liste du journal.

	retirerCible(journal.cibles, journal.cibles.elements[4].id);
	

	// TODO: Ajouter la cible 11 (variable 'c11' ci-dessus) à la liste du journal.
	ajouterCible(journal.cibles, c11);

	// TODO: Afficher les cibles pour vérifier que les opérations ci-dessus ont bien fonctionnées.
	cout << endl << "cibles sans la 5" << endl;
	afficherCibles(journal.cibles);

	// TODO: Écrire le journal de détection dans "Cibles_final.data".

	ecrireJournalDetection("Cibles_final.data", journal, ok);

	// TODO: Écrire l'observation (variable 'observation' ci-dessus) dans la
	//       deuxième cible du fichier créé ci-dessus.

	ecrireObservation("Cibles_final.data", 1, observation);

	// TODO: Lire ce nouveau journal et l'afficher.  Toutes les cibles (autre que la 5 qu'on a enlevée) devrait y être, et la nouvelle observation devrait être sur la deuxième cible (qui a aussi l'ID 2, mais c'est une coïncidence).
	cout << endl << "journal avec l'observation" << endl;
	JournalDetection nouveaujournal = lireJournalDetection("Cibles_final.data", ok);
	afficherJournal(nouveaujournal);

	// TODO: Désallouer les deux listes de cibles.

	desallouerListe(journal.cibles);
	desallouerListe(nouveaujournal.cibles);
	

	// TODO: Faire la vérification d'erreur et terminer le programme avec un
	//       message s'il y a erreur.

	cout << "la capacite est de : " << journal.cibles.capacite <<" le nombre d'elements est de : " << journal.cibles.nbElements << endl;

	return 0;
}
