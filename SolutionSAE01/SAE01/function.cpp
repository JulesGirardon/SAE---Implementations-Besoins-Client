#include "function.h"

std::array<int, 2> GetDimension(std::string nom_fichier) {
    /* Cette fonction a pour objectif de récupérer les dimensions du fichier mis en entree.
    Cette fonction renvoie un tableau de taille 2 avec en premier la largeur et en deuxième la hauteur*/

    std::ifstream fichier(nom_fichier, std::ios_base::binary);  // Ouverture de notre image au format pgm

    if (!fichier.is_open()) {                                   // On vérifie que le fichier est bien ouvert
        std::cerr << "Le ficher n'a pu être ouvert !";
        exit(1);
    }

    std::vector<std::vector<std::string>> tab_entete;
    std::string line;

    for (size_t i = 0; i < 4; i++) {                            // Cette boucle permet de récupérer l'entete du fichier
        std::getline(fichier, line);
        std::stringstream sstr(line);
        std::vector<std::string> lineDataTab;

        while (!sstr.eof()) {
            std::string lineData;
            std::getline(sstr, lineData, ' ');
            lineDataTab.push_back(lineData);
        }
        tab_entete.push_back(lineDataTab);
    }

    return { stoi(tab_entete[2][0]), stoi(tab_entete[2][1]) };  // On récupère largeur et hauteur qui, dans le PGM, est situé à la 3ème ligne.

}

DecodagePalette_t DecodagePalette(std::string palette) {
    /* Cette fonction permet de récupérer les différents éléments de la palette. Ces éléments sont stockés dans un tableau qui est ensuite renvoyé*/
    DecodagePalette_t tab;
    std::string line;

    std::ifstream fichier(palette);

    while (!fichier.eof()) {                 // Lecture de chaque ligne de la palette
        std::getline(fichier, line);
        tab.push_back(line);                 
    }

    return tab;
}

TypeTab DecodagePGM(std::string nom_fichier) {

    /* Cette fonction permet de décoder le fichier PGM
    * Cette fonction renvoie un tableau de deux dimensions qui contient des chars qui sont les valeurs du gris du PGM
    */

    std::ifstream fichier(nom_fichier, std::ios_base::binary);  // Ouverture de notre image au format pgm

    std::vector<std::vector<std::string>> tab_entete;
    std::string line;

    for (size_t i = 0; i < 4; i++) {                            // Cette boucle permet de récupérer l'entete du fichier
        std::getline(fichier, line);
        std::stringstream sstr(line);
        std::vector<std::string> lineDataTab;

        while (!sstr.eof()) {
            std::string lineData;
            std::getline(sstr, lineData, ' ');
            lineDataTab.push_back(lineData);
        }
        tab_entete.push_back(lineDataTab);
    }

    int largeur = stoi(tab_entete[2][0]);                   // On récupère la largeur et la hauteur
    int hauteur = stoi(tab_entete[2][0]);

    if (!fichier.is_open()) {                                   // On vérifie que le fichier est bien ouvert
        std::cerr << "Le ficher n'a pu être ouvert !";
        exit(1);
    }

    TypeTab donnes_complete;                          // Ce tableau stocke toutes les lignes
    std::vector<char> donnes(largeur);

    for (size_t i = 0; i < hauteur; i++) {                  // Cette boucle récupère lignes par lignes les données et les mets dans le tableau donnes_complete
        fichier.read(donnes.data(), largeur);
        donnes_complete.push_back(donnes);
    }

    return donnes_complete;
}


std::string AskChar(char valeur, std::string choixPalette) {

    /* Cette fonction permet de passer du char au charactère de la palette qui lui est associé.
    * Cette fonciton renvoie une lettre
    */

    DecodagePalette_t tabPalette = DecodagePalette(choixPalette);   // On récupère le tableau qui contient les éléments de la palette qui a été choisie.
    int nbEtape = tabPalette.size();          // On récupère la taille de la palette
    std::vector<int> tabNiveauGris;
    for (int i = 0; i < nbEtape + 1; i++)                           // C'est ici que la taille de la palette prend son importance
        tabNiveauGris.push_back(i * (256 / nbEtape));               // En effet, ceci permet de savoir de quelle valeur a quelle valeur les éléments de la palette sont délimités.
    // Imaginons, notre palette contient 8 valeurs, on obtient 256 / 8 = 32
    // Le première élément de la palette prend les valeurs comprises entre 0 (inclus) et 32
    // Le deuxième élément, les valeurs comprises entre 32 (inclus) et 64
    // Ainsi de suite jusqu'à 256.
    // Imaginons, notre palette contient 5 valeurs, on obtient 256 / 5 = 51
    // Le première élément de la palette prend les valeurs comprises entre 0 (inclus) et 51
    // Le deuxième élément, les valeurs comprises entre 51 (inclus) et 102
    // Ainsi de suite jusqu'à 256.

    std::string valeur2;
    for (int i = 0; i < tabNiveauGris.size() - 1; i++) {            // Cette boucle permet de donner la lettre associé à la valeur du char
        if (valeur < 0)
            valeur += 128;
        if (valeur >= tabNiveauGris[i] && valeur < tabNiveauGris[i + 1])
            valeur2 = tabPalette[i];
    }

    return valeur2;
}

void OutFile(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette, int width, int height) {

    /* Cette fonction permet d'enregister dans un fichier .txt le PGM mis en paramètre. Elle permet aussi de réduire la taille en largeur et/ou hauteur de l'image si besoin
    *  Cette fonction ne renvoie rien
    */

    std::array<int, 2> tab_dim = GetDimension(fichier_entrer);      // On récupère les dimensions du fichier mis en entrer
    int largeur = tab_dim[0];
    int hauteur = tab_dim[1];

    std::ofstream file_out(fichier_sortie);                        // On crée le fichier de sortie
    TypeTab donnees_complete;

    if (width == 0 && height == 0)                                 // Toutes ces conditions permettent de savoir si l'image doit être réduite ounon
        donnees_complete = DecodagePGM(fichier_entrer);
    else {
        if (width == 0 && height != 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), largeur, height);
        else if (width != 0 && height == 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, hauteur);
        else
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, height);
    }
    for (size_t i = 0; i < donnees_complete.size(); i++) {           // On enregistre les données de donnees_complete dans le fichier mis en sortie
        for (size_t j = 0; j < donnees_complete[i].size(); j++) {
            std::string valeur = AskChar(donnees_complete[i][j], choixPalette);
            file_out << valeur;
        }
        file_out << "\n";
    }
}

TypeTab ReductionPGM(TypeTab donnees, int width_max, int height_max) {
    /* Cette fonction permet de réduire la taille d'un PGM
    *  Elle renvoie un tableau à deux dimensions
    */

    TypeTab donnes_redimensionnees;

    int largeur = donnees[0].size();    // Sur une image, la largeur est la meme sur toutes les lignes. Ainsi, je récupère la taille de la première ligne
    int hauteur = donnees.size();       // 

    int ratio_largeur = largeur / width_max;
    int ratio_hauteur = hauteur / height_max;

    int div_moy = ratio_hauteur * ratio_hauteur;

    for (int i = 0; i < hauteur; i += ratio_hauteur) {
        std::vector<char> tab_temp;
        for (int j = 0; j < largeur; j += ratio_largeur) {
            int moy = 0;
            for (size_t ij = 0; ij < ratio_hauteur; ij++)
                for (size_t ji = 0; ji < ratio_largeur; ji++) {
                    moy += donnees[i + ij][j + ji];
                }

            tab_temp.push_back(int(char(moy) / (div_moy)));
        }
        donnes_redimensionnees.push_back(tab_temp);
    }

    return donnes_redimensionnees;
}

std::string AccesError() {
    std::string valeur = "";
    std::cout << "\nFichier d'accès non spécifié veuillez entrez un fichier : ";
    std::cin >> valeur;
    return valeur;
}

void OutConsole(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette, int width, int height) {

    /* Cette fonction permet d'afficher le résultat dans la console.
    *  Cette fonction ne renvoie rien
    */

    std::array<int, 2> tab_dim = GetDimension(fichier_entrer);      // On récupère les dimensions du fichier mis en entrer
    int largeur = tab_dim[0];
    int hauteur = tab_dim[1];

    std::ofstream file_out(fichier_sortie);                        // On crée le fichier de sortie
    TypeTab donnees_complete;

    if (width == 0 && height == 0)                                 // Toutes ces conditions permettent de savoir si l'image doit être réduite ounon
        donnees_complete = DecodagePGM(fichier_entrer);
    else {
        if (width == 0 && height != 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), largeur, height);
        else if (width != 0 && height == 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, hauteur);
        else
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, height);
    }
    for (size_t i = 0; i < donnees_complete.size(); i++) {           // On enregistre les données de donnees_complete dans le fichier mis en sortie
        for (size_t j = 0; j < donnees_complete[i].size(); j++) {
            std::string valeur = AskChar(donnees_complete[i][j], choixPalette);
            std::cout << valeur;
        }
        std::cout << "\n";
    }
}