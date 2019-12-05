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
 *  \file arbre_binaire.c
 *
 *  Fichier d'implémentation contenant la structure de donnée 'arbre_binaire'.
 *  Un arbre binaire est un un graphe connexe acyclique orienté dont tous les
 *  noeuds ont au maximum un parent et dont chaque noeuds peu avoir un maximum
 *  de 2 enfants.
 *
 */

#include "arbre_binaire.h"

/**
 * \brief Un arbre implémentée de structures liées
 */
struct arbre_binaire_struct {
    int noeud; /// <Sa valeur
    struct arbre_binaire_struct* gauche;
    struct arbre_binaire_struct* droit;
    bool a_erreur;
    char* erreur;
};

/**
  * \brief Créer un nouvel arbre_binaire en assignant la `valeur' à sa racine.
  *
  * \param valeur La valeur qui sera assigné à la racine
  *
  * \return l'arbre binaire
  */
arbre_binaire* creer_arbre_binaire(int valeur) {
  arbre_binaire* result;
  result = calloc(1, sizeof(arbre_binaire));
  if (result) {
      result->noeud = valeur;
      result->gauche = NULL;
      result->droit = NULL;
      result->a_erreur = false;
      result->erreur = calloc(ERREUR_TAILLE, sizeof(char));
  }
  return result;
}

/**
  * \brief Lit récursivement le noeud et les enfants contenues dans le fichier.
  *
  * \param file Le fichier
  *
  * \return l'arbre binaire
  */
arbre_binaire* charger(FILE* file) {
  arbre_binaire* result;
  arbre_binaire* gauche;
  arbre_binaire* droit;
  int tableau[2]; /// <[0]=noeud [1]=0,1,2,3

  fread(tableau, sizeof(int), 2, file);
  result = creer_arbre_binaire(tableau[0]);

  if (tableau[1] == 1) { /// <Seulement gauche
    gauche = charger(file);
    result->gauche = gauche;
  }
  if (tableau[1] == 2) { /// <Seulement droite
    droit = charger(file);
    result->droit = droit;
  }
  if (tableau[1] == 3) { /// <Les deux
    gauche = charger(file);
    result->gauche = gauche;
    droit = charger(file);
    result->droit = droit;
  }
  return result;
}

/**
  * \brief Retourne un nouvel arbre_binaire.
  *
  * L'arbre est créé graçe aux données du fichier binaire `nom_fichier'.
  * Le fichier doit être créé à l'aide de la routine “sauvegarder_arbre_binaire”
  *
  * \param nom_fichier Le nom du fichier
  *
  * \return l'arbre binaire
  */
arbre_binaire* charger_arbre_binaire(char* nom_fichier) {
  arbre_binaire* result;
  FILE* file;
  file = fopen(nom_fichier, "rb");
  if (file) {
    result = charger(file);
    fclose(file);
  } else {
    result = NULL;
  }
  return result;
}

/**
  * \brief Libère l'espace mémoire utilisé par l'arbre
  *  (libère également tous les enfants).
  *
  * \param arbre L'arbre à désalloué
  */
void detruire_arbre_binaire(arbre_binaire* arbre) {
  if (arbre->gauche) {
    detruire_arbre_binaire(arbre->gauche);
  }
  if(arbre->droit) {
    detruire_arbre_binaire(arbre->droit);
  }
  free(arbre);
}

/**
  * \brief Écrit récursivement le noeud et les enfants contenues dans l'arbre.
  *
  * \param arbre L'arbre à enregistrer
  * \param file Le fichier
  */
void sauvegarder(arbre_binaire* arbre, FILE* file) {
  int nb;
  int result[2];

	nb = arbre->noeud;

  if (!arbre->gauche && !arbre->droit) {
    result[1] = 0; /// <Aucun enfant
  }
  if (arbre->gauche && !arbre->droit) {
    result[1] = 1; /// <Seulement gauche
  }
  if (!arbre->gauche && arbre->droit) {
    result[1] = 2; /// <Seulement droit
  }
  if (arbre->gauche && arbre->droit) {
    result[1] = 3; /// <Les deux
  }
  result[0] = nb;
  fwrite(result, sizeof(int), 2, file);

  if (arbre->gauche) {
    sauvegarder(arbre->gauche, file);
  }
  if (arbre->droit) {
	  sauvegarder(arbre->droit, file);
  }
}

/**
  * \brief Sauvegarde l'arbre dans le fichier binaire `nom_fichier'
  *
  * \param arbre L'arbre à enregistrer
  * \param nom_fichier Le nom du fichier
  */
void sauvegarder_arbre_binaire(arbre_binaire* arbre, char* nom_fichier) {
  retirer_erreur_arbre_binaire(arbre);
  FILE* file;
  file = fopen(nom_fichier,"wb");
  if (file) {
    sauvegarder(arbre, file);
    fclose(file);
  } else {
    inscrire_erreur_arbre_binaire(arbre,
      "Impossible d'ouvrir le fichier en ecriture.");
  }
}

/**
  * \brief Retourne le nombre d'éléments contenus dans l'arbre.
  *
  * Corresponds également au nombre de noeuds de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return Le nombre d'élément de l'arbre
  *
  * \note 'arbre' ne doit pas être NULL
  */
int nombre_elements_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  int nb = 0;
    if (arbre->gauche) {
      nb = nombre_elements_arbre_binaire(arbre->gauche);
    }
    if (arbre->droit) {
      nb += nombre_elements_arbre_binaire(arbre->droit);
    }
  return nb +1;
}

/**
  * \brief Retourne le nombre de feuilles de l'arbre.
  *
  * Une feuille correspond à un noeud n'ayant AUCUN enfant.
  *
  * \param arbre L'arbre désiré
  *
  * \return Le nombre de feuille de l'arbre
  *
  * \note 'arbre' ne doit pas être NULL
  */
int nombre_feuilles_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  int nb = 0;
    if ((!arbre->gauche) && (!arbre->droit))  {
      nb = 1;
    } else {
      if (arbre->gauche) {
        nb = nombre_feuilles_arbre_binaire(arbre->gauche);
      }
      if (arbre->droit) {
        nb += nombre_feuilles_arbre_binaire(arbre->droit);
      }
    }
  return nb;
}

/**
  * \brief Retourne la hauteur de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return La hauteur de l'arbre
  */
int hauteur_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  int profondeur_gauche = 0;
  int profondeur_droit = 0;
  int max = 0;
  int hauteur = 0;
  if (arbre->gauche) {
    profondeur_gauche = 1+ hauteur_arbre_binaire(arbre->gauche);
  }
  if (arbre->droit) {
    profondeur_droit = 1+ hauteur_arbre_binaire(arbre->droit);
  }
  if (profondeur_gauche > profondeur_droit) {
    max = profondeur_gauche;
  } else {
    max = profondeur_droit;
  }
  hauteur = max;
  return hauteur;
}

/**
  * \brief Retourne l'élément contenu dans la racine de l'arbre.
  *
  * \param arbre L'arbre désiré
  *
  * \return La valeur contenu dans la racine de l'arbre
  */
int element_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  return arbre->noeud;
}

/**
  * \brief Remplace l'élément à la racine de l'arbre par `valeur'.
  *
  * \param arbre L'arbre désiré
  * \param valeur La nouvelle valeur
  */
void modifier_element_arbre_binaire(arbre_binaire* arbre, int valeur) {
  retirer_erreur_arbre_binaire(arbre);
  arbre->noeud = valeur;
}

/**
  * \brief Retourne vrai si l'arbre contient la `valeur'
  *
  * La `valeur' peut être contenue soit dans sa racine ou dans ces descendances.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur recherché
  *
  * \return Vrai si la valeur recherché existe, sinon Faux.
  */
bool contient_element_arbre_binaire(arbre_binaire* arbre, int valeur) {
  retirer_erreur_arbre_binaire(arbre);
  bool result = false;
    if (arbre != NULL) {
      if (arbre->noeud == valeur) {
        result = true;
      }
      if (!result && arbre->gauche) {
        result = contient_element_arbre_binaire(arbre->gauche, valeur);
      }
      if (!result && arbre->droit) {
        result = contient_element_arbre_binaire(arbre->droit, valeur);
      }
    }
  return result;
}

/**
  * \brief Retourne le sous-arbre enfant gauche de `arbre'.
  *
  * Retourne `NULL' si `arbre' n'a pas d’enfant gauche.
  *
  * \param arbre L'arbre désiré
  *
  * \return le sous-arbre enfant gauche
  */
arbre_binaire* enfant_gauche_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  return arbre->gauche;
}

/**
  * \brief Créer l’enfant gauche de `arbre' et assigne `valeur' à sa racine.
  *
  * Si `arbre' a déjà un enfant gauche, ne change rien et retourne une erreur.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur qui sera assigné à sa racine
  */
void creer_enfant_gauche_arbre_binaire(arbre_binaire* arbre, int valeur) {
  retirer_erreur_arbre_binaire(arbre);
  if (arbre->gauche == NULL) {
    arbre->gauche = creer_arbre_binaire(valeur);
  } else {
    inscrire_erreur_arbre_binaire(
      arbre, "'creer_enfant_gauche_arbre_binaire' Enfant gauche existe deja.");
  }
}

/**
  * \brief Libère l’enfant gauche de `arbre'.
  *
  * \param arbre L'arbre désiré
  */
void retirer_enfant_gauche_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  if (arbre->gauche) {
    detruire_arbre_binaire(arbre->gauche);
    arbre->gauche = NULL;
  }
}

/**
  * \brief Retourne le sous-arbre enfant droit de `arbre'.
  *
  * Retourne `NULL' si `arbre' n'a pas d’enfant droit.
  *
  * \param arbre L'arbre désiré
  *
  * \return le sous-arbre enfant droit
  */
arbre_binaire* enfant_droit_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  return arbre->droit;
}

/**
  * \brief Créer l’enfant droit de `arbre' et assigne `valeur' à sa racine.
  *
  * Si `arbre' a déjà un enfant droit, ne change rien et retourne une erreur.
  *
  * \param arbre L'arbre désiré
  * \param valeur La valeur qui sera assigné à sa racine
  */
void creer_enfant_droit_arbre_binaire(arbre_binaire* arbre, int valeur) {
  retirer_erreur_arbre_binaire(arbre);
  if (arbre->droit == NULL) {
    arbre->droit = creer_arbre_binaire(valeur);
  } else {
    inscrire_erreur_arbre_binaire(
      arbre, "'creer_enfant_droit_arbre_binaire' Enfant droit existe deja.");
  }
}

/**
  * \brief Libère l’enfant droit de `arbre'.
  *
  * \param arbre L'arbre désiré
  */
void retirer_enfant_droit_arbre_binaire(arbre_binaire* arbre) {
  retirer_erreur_arbre_binaire(arbre);
  if (arbre->droit) {
    detruire_arbre_binaire(arbre->droit);
    arbre->droit = NULL;
  }
}

/**
  * \brief Valide si une erreur est arrivée lors du dernier appel de fonction
  *  de la librairie.
  *
  * \param arbre L'arbre désiré
  *
  * \return Vrai si une erreur est arrivée, sinon Faux.
  */
bool a_erreur_arbre_binaire(arbre_binaire* arbre) {
  return arbre->a_erreur;
}

/**
  * \brief Si “a_erreur_arbre_binaire” est vrai, retourne une description de
  *  l'erreur.
  *
  * \param arbre L'arbre désiré
  *
  * \return La description de l'erreur.
  */
char* erreur_arbre_binaire(arbre_binaire* arbre) {
  if (!arbre->a_erreur) {
    strncpy(arbre->erreur, "", ERREUR_TAILLE);
  }
  return arbre->erreur;
}

/**
  * \brief Insert le message d'erreur dans l'arbre.
  *
  * Également, mets “a_erreur_arbre_binaire” à Vrai.
  * Une copie de l'erreur doit être gardée dans la librairie.
  *
  * \param arbre L'arbre désiré
  * \param erreur L'erreur à inscrire
  */
void inscrire_erreur_arbre_binaire(arbre_binaire* arbre, const char* erreur) {
  arbre->a_erreur = true;
  strncpy(arbre->erreur, erreur, ERREUR_TAILLE);
}

/**
  * \brief Met “a_erreur_arbre_binaire” à Faux.
  *
  * \param arbre L'arbre désiré
  */
void retirer_erreur_arbre_binaire(arbre_binaire* arbre) {
  arbre->a_erreur = false;
}
