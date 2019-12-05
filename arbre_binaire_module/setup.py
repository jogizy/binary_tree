# coding=UTF-8

# =============================================================================
# titre           :setup.py
# description     :Script de compilation du module 'arbre_binaire_externe'
# author          :Olivier Meloche
# date            :20191119
# version         :1.0
# usage           :python setup.py build
# notes           :
# license         :Aucune
# python_version  :3.7.3
# =============================================================================

from distutils.core import setup, Extension

arbre_binaire_externe = Extension('arbre_binaire_externe',
                    include_dirs = ['../arbre_binaire/'],
                    libraries = ['arbre_binaire'],
                    library_dirs = ['../arbre_binaire/bin/Release/'],
                    sources = ['arbre_binaire_module.c'])

setup (name = 'arbre_binaire_externe',
       version = '1.0',
       description = "Gestionnaire d'arbre binaire.",
       ext_modules = [arbre_binaire_externe])
