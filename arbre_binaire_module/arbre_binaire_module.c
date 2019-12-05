/*

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

*/

/**
 *  \file arbre_binaire_module.c
 *
 *  Fichier d'implémentation du module Python permettant d'interfacer
 *  avec la librairie "arbre_binaire".
 *
 */

#include <Python.h>
#include "arbre_binaire.h"

/**
 * \brief "Wrapper" pour les erreurs du module
 */
static PyObject* gestion_erreur;

/**
 * \brief "Wrapper" pour la fonction 'creer_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'arbre créé
 */
static PyObject* creer(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	int valeur;
	if (PyArg_ParseTuple(a_args, "i", &valeur)) {
		arbre = creer_arbre_binaire(valeur);
		if (arbre) {
			if (!a_erreur_arbre_binaire(arbre)) {
				result = Py_BuildValue("n", arbre);
			} else {
				PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
			}
		} else {
			PyErr_SetString(gestion_erreur, "Impossible de creer l'arbre.");
		}
	}
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'charger_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'arbre créé
 */
static PyObject* charger(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	char* nom_fichier;
	if (PyArg_ParseTuple(a_args, "s", &nom_fichier)) {
		arbre = charger_arbre_binaire(nom_fichier);
		if (arbre) {
			if (a_erreur_arbre_binaire(arbre)) {
				PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
			} else {
				result = Py_BuildValue("n", arbre);
			}
		} else {
			PyErr_SetString(gestion_erreur, "Impossible d'ouvrir le fichier.");
		}
	}
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'detruire_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* detruire(PyObject* a_self, PyObject* a_args) {
	arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	if (PyArg_ParseTuple(a_args, "n", &arbre)) {
		detruire_arbre_binaire(arbre);
		Py_INCREF(Py_None);
		result = Py_None;
	}
	return result;
}

/**
 * \brief "Wrapper" pour la fonction 'sauvegarder_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* sauvegarder(PyObject* a_self, PyObject* a_args) {
	arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	char* nom_fichier;
	if (PyArg_ParseTuple(a_args, "ns", &arbre, &nom_fichier)) {
		sauvegarder_arbre_binaire(arbre, nom_fichier);
		if (a_erreur_arbre_binaire(arbre)) {
			PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
		} else {
			Py_INCREF(Py_None);
			result = Py_None;
		}
	}
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'nombre_elements_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant le nombre d'éléments (noeuds)
 */
static PyObject* nombre_elements(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  PyObject* result = NULL;
  int nb;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    nb = nombre_elements_arbre_binaire(arbre);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      result = Py_BuildValue("i", nb);
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'nombre_feuilles_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant le nombre de feuilles
 */
static PyObject* nombre_feuilles(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  PyObject* result = NULL;
  int nb;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    nb = nombre_feuilles_arbre_binaire(arbre);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      result = Py_BuildValue("i", nb);
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'hauteur_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant la hauteur
 */
static PyObject* hauteur(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  PyObject* result = NULL;
  int nb;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    nb = hauteur_arbre_binaire(arbre);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      result = Py_BuildValue("i", nb);
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'élément (noeud) à la racine
 */
static PyObject* element(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  PyObject* result = NULL;
  int nb;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    nb = element_arbre_binaire(arbre);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      result = Py_BuildValue("i", nb);
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'modifier_element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* modifier_element(PyObject* a_self, PyObject* a_args) {
	arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	int valeur;
	if (PyArg_ParseTuple(a_args, "ni", &arbre, &valeur)) {
		modifier_element_arbre_binaire(arbre, valeur);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      Py_INCREF(Py_None);
  		result = Py_None;
    }
	}
	return result;
}

/**
 * \brief "Wrapper" pour la fonction 'contient_element_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant vrai ou faux
 */
static PyObject* contient_element(PyObject* a_self, PyObject* a_args) {
	arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	bool contient = false;
	int valeur;
	if (PyArg_ParseTuple(a_args, "ni", &arbre, &valeur)) {
		contient = contient_element_arbre_binaire(arbre, valeur);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      result = Py_BuildValue("i", contient);
    }
	}
	return result;
}

/**
 * \brief "Wrapper" pour la fonction 'enfant_gauche_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'enfant gauche
 */
static PyObject* enfant_gauche(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  arbre_binaire* gauche = NULL;
  PyObject* result = NULL;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    gauche = enfant_gauche_arbre_binaire(arbre);
    if (gauche) {
      if (a_erreur_arbre_binaire(arbre)) {
        PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
      } else {
        result = Py_BuildValue("n", gauche);
      }
    } else {
      Py_INCREF(Py_None);
      result = Py_None;
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'creer_enfant_gauche_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* creer_enfant_gauche(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
  int valeur;
  if (PyArg_ParseTuple(a_args, "ni", &arbre, &valeur)) {
    creer_enfant_gauche_arbre_binaire(arbre, valeur);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      Py_INCREF(Py_None);
      result = Py_None;
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'retirer_enfant_gauche_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* retirer_enfant_gauche(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	if (PyArg_ParseTuple(a_args, "n", &arbre)) {
		retirer_enfant_gauche_arbre_binaire(arbre);
		Py_INCREF(Py_None);
		result = Py_None;
	}
	return result;
}

/**
 * \brief "Wrapper" pour la fonction 'enfant_droit_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python contenant l'adresse de l'enfant droit
 */
static PyObject* enfant_droit(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
  arbre_binaire* droit = NULL;
  PyObject* result = NULL;
  if (PyArg_ParseTuple(a_args, "n", &arbre)) {
    droit = enfant_droit_arbre_binaire(arbre);
    if (droit) {
      if (a_erreur_arbre_binaire(arbre)) {
        PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
      } else {
        result = Py_BuildValue("n", droit);
      }
    } else {
      Py_INCREF(Py_None);
      result = Py_None;
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'creer_enfant_droit_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* creer_enfant_droit(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
  int valeur;
  if (PyArg_ParseTuple(a_args, "ni", &arbre, &valeur)) {
    creer_enfant_droit_arbre_binaire(arbre, valeur);
    if (a_erreur_arbre_binaire(arbre)) {
      PyErr_SetString(gestion_erreur, erreur_arbre_binaire(arbre));
    } else {
      Py_INCREF(Py_None);
      result = Py_None;
    }
  }
  return result;
}

/**
 * \brief "Wrapper" pour la fonction 'retirer_enfant_droit_arbre_binaire'
 *
 * \param self L'objet python représentant le module
 * \param args Conteneur possédant les arguments envoyés à la fonction
 *
 * \return Objet Python 'None' (type NULL de Python)
 */
static PyObject* retirer_enfant_droit(PyObject* a_self, PyObject* a_args) {
  arbre_binaire* arbre = NULL;
	PyObject* result = NULL;
	if (PyArg_ParseTuple(a_args, "n", &arbre)) {
		retirer_enfant_droit_arbre_binaire(arbre);
		Py_INCREF(Py_None);
		result = Py_None;
	}
	return result;
}

/**
 * \brief Liste toutes les fonctions du module
 */
static PyMethodDef arbre_binaire_methods[] = {
    {"creer",  creer, METH_VARARGS,
     "Créer un arbre implémenté avec des structures liées"},
    {"charger",  charger, METH_VARARGS,
     "Charger un arbre binaire à partir du contenue d'un fichier"},
    {"detruire",  detruire, METH_VARARGS,
     "Désalloue l'arbre binaire"},
    {"sauvegarder",  sauvegarder, METH_VARARGS,
     "Enregistre l'arbre binaire dans un fichier binaire"},
    {"nombre_elements",  nombre_elements, METH_VARARGS,
     "Retourne le nombre d'éléments contenus dans l'arbre"},
    {"nombre_feuilles",  nombre_feuilles, METH_VARARGS,
     "Retourne le nombre de feuilles de l'arbre"},
    {"hauteur",  hauteur, METH_VARARGS,
     "Retourne la hauteur de l'arbre"},
    {"element",  element, METH_VARARGS,
     "Retourne l'élément contenu à la racine de l'arbre"},
    {"modifier_element",  modifier_element, METH_VARARGS,
     "Remplace l'élément à la racine de l'arbre par une autre valeur"},
    {"contient_element",  contient_element, METH_VARARGS,
     "Retourne vrai si l'arbre contient la valeur recherché"},
		{"enfant_gauche",  enfant_gauche, METH_VARARGS,
     "Retourne le sous-arbre enfant gauche de l'arbre"},
		{"creer_enfant_gauche",  creer_enfant_gauche, METH_VARARGS,
     "Créer l’enfant gauche de l'arbre et assigne une valeur à sa racine"},
		{"retirer_enfant_gauche",  retirer_enfant_gauche, METH_VARARGS,
     "Libère l’enfant gauche de l'arbre"},
		{"enfant_droit",  enfant_droit, METH_VARARGS,
     "Retourne le sous-arbre enfant droit de l'arbre"},
		{"creer_enfant_droit",  creer_enfant_droit, METH_VARARGS,
     "Créer l’enfant droit de l'arbre et assigne une valeur à sa racine"},
		{"retirer_enfant_droit",  retirer_enfant_droit, METH_VARARGS,
     "Libère l’enfant droit de l'arbre"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

/**
 * \brief Information sur le module
 */
static struct PyModuleDef arbre_binaire_module = {
   PyModuleDef_HEAD_INIT,
   "arbre_binaire_externe",   /* nom du module */
		/* documentation du module, NULL si aucun */
   "Gestionnaire d'arbre binaire.",
   -1,       /*  Taille de l'état "per-interpreter" du module,
                ou -1 si le module ce situe en variable globale. */
   arbre_binaire_methods /* La liste des fonctions du module */
};

/**
 * \brief Initialization du module
 */
PyMODINIT_FUNC PyInit_arbre_binaire_externe(void) {
	PyObject *l_module;
	l_module = PyModule_Create(&arbre_binaire_module); /* Créer le module */
	if (l_module) {
		/* Ajouter un gestionnaire d'exception dans le module */
		gestion_erreur = PyErr_NewException("arbre_binaire_externe.erreur", NULL, NULL);
		Py_INCREF(gestion_erreur);
		PyModule_AddObject(l_module, "erreur", gestion_erreur);
	}
    return l_module;
}
