# coding=UTF-8

# =============================================================================
# titre           :arbre_binaire_test.py
# description     :Tests pour le module arbre_binaire_externe
# author          :Olivier Meloche
# date            :20191204
# version         :1.0
# usage           :python arbre_binaire_test.py
# notes           :
# license         :Aucune
# python_version  :3.7.3
# =============================================================================

from arbre_binaire_externe import (creer, charger, detruire, sauvegarder,
                                   nombre_elements, nombre_feuilles, hauteur,
                                   element, modifier_element, contient_element,
                                   enfant_gauche, creer_enfant_gauche,
                                   retirer_enfant_gauche, enfant_droit,
                                   creer_enfant_droit, retirer_enfant_droit)

arbre1 = None
arbre2 = None
gauche = None
droit = None

arbre1 = creer(69)
print("\n========== ARBRE1 CRÉÉ ==========")
if arbre1:
    creer_enfant_gauche(arbre1, 70)
    gauche = enfant_gauche(arbre1)
    creer_enfant_gauche(gauche, 71)
    gauche = enfant_gauche(gauche)
    creer_enfant_gauche(gauche, 72)
    creer_enfant_droit(gauche, 73)
    try:
        creer_enfant_droit(gauche, 773) # <Erreur, car enfant droit existe déjà
    except Exception as message:
        print("Erreur 'arbre1': " + str(message))
    creer_enfant_droit(arbre1, 170)
    droit = enfant_droit(arbre1)
    creer_enfant_gauche(droit, 171)
    creer_enfant_droit(droit, 172)

    print("Élément à la racine: "+str(element(arbre1)))
    print("Hauteur: "+str(hauteur(arbre1)))
    print("Nombre de feuilles: "+str(nombre_feuilles(arbre1)))
    print("Nombre d'éléments: "+str(nombre_elements(arbre1)))
    modifier_element(arbre1, 690)
    print("Contient élément [690]: "+
                str(contient_element(arbre1, 690))) # <1=True
    try:
        sauvegarder(arbre1, "test1.bin")
    except Exception as message:
        print("Erreur 'arbre1': " + str(message) + "\n")
    detruire(arbre1)
else:
    print("'arbre1' Une erreur est survenue.")


try:
    arbre2 = charger("test1.bin")
    print("\n========= ARBRE2 CHARGÉ =========")
except Exception as message:
    print("\nErreur: " + str(message) + "\n")
if arbre2:
    gauche = enfant_gauche(arbre2)
    retirer_enfant_gauche(gauche) # <Reste 690, 70, 170, 171, 172

    print("Élément à la racine: "+str(element(arbre2)))
    print("Hauteur: "+str(hauteur(arbre2)))
    print("Nombre de feuilles: "+str(nombre_feuilles(arbre2)))
    print("Nombre d'éléments: "+str(nombre_elements(arbre2)))
    modifier_element(arbre2, 999)
    print("Élément à la racine: "+str(element(arbre2)))
    print("Contient élément [690]: "+
                str(contient_element(arbre2, 690))) # <0=False
    detruire(arbre2)
else:
    print("'arbre2' Une erreur est survenue.")
