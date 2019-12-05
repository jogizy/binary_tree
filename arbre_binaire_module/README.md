Module python pour la librairie Arbre Binaire
==========================================

Préparer la compilation (Windows seulement)
-------------------------------------------

	- Installer MinGW avec MSYS
	- Dans MSYS, s'assurer que "C:\MinGW" est monté dans "/mingw":

***

	mount 'C:\MinGW' /mingw

***

	- Installer Python 3 et le rendre accessible dans le path:

***

	export PATH=$PATH:/c/Python37

***

	- Créer (s'il n'existe pas déjà) le fichier C:\Python37\Lib\distutils\distutils.cfg:

***

	vim /c/Python37/Lib/distutils/distutils.cfg

***

	- Inscrire dans le fichier:

***

	[build]
	compiler=mingw32

***



Compiler la librairie
---------------------

  - Assurez-vous que:
		* le fichier ../arbre_binaire/bin/Release/libarbre_binaire.a existe (et compiler avec -fpic)
		* le fichier ../arbre_binaire/bin/Release/libarbre_binaire.so n'existe pas
		* Commandes:

***

	pushd ..
	make clean
	make release_static
	popd

***

  - Assurez-vous également que Python 3 est installé et accessible dans le PATH:

  - Compiler la librairie (dans le répertoire contenant ce fichier README.md):

***

	python setup.py build

***
	Note: Utiliser python3 sur Linux

  - Déplacer le fichier compiler dans le répertoire en cours:

***

	mv build/lib.*/*.* ./

***

Exécuter les tests
------------------

  - Assurez-vous que la librairie est compilé et est dans le répertoire de ce fichier README.md (voir plus haut)

***

	python arbre_binaire_test.py

***
	Note: Utiliser python3 sur Linux

License
-------

    Copyright (c) 2019 Olivier Meloche

    L'autorisation est accordée, gracieusement, à toute personne acquérant une
    copie de cette bibliothèque et des fichiers de documentation associés
    (la "Bibliothèque"), de commercialiser la Bibliothèque sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Bibliothèque, ainsi que d'autoriser les personnes auxquelles la
    Bibliothèque est fournie à le faire, sous réserve des conditions suivantes:

    La déclaration de copyright ci-dessus et la présente autorisation doivent
    être incluses dans toutes copies ou parties substantielles de la
    Bibliothèque.

    LA BIBLIOTHÈQUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALITÉ MARCHANDE,
    D’ADÉQUATION À UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFAÇON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, RÉCLAMATION OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTRE, EN PROVENANCE DE, CONSÉCUTIF À OU
    EN RELATION AVEC LA BIBLIOTHÈQUE OU SON UTILISATION, OU AVEC D'AUTRES
    ÉLÉMENTS DE LA BIBLIOTHÈQUE.
