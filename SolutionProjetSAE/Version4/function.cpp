#include "function.h"

std::array<int, 2> GetDimension(std::string nom_fichier) {

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

    return { stoi(tab_entete[2][0]), stoi(tab_entete[2][1]) };

}

DecodagePalette_t DecodagePalette(std::string palette) {
    DecodagePalette_t tab;
    int compteur = 0;
    std::string line;

    std::ifstream fichier(palette);

    while (!fichier.eof()) {
        std::getline(fichier, line);
        tab.push_back(line);
        compteur++;
    }

    tab.push_back(std::to_string(compteur));
    return tab;
}

TypeTab DecodagePGM(std::string nom_fichier) {

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

    DecodagePalette_t tabPalette = DecodagePalette(choixPalette);
    int nbEtape = stoi(tabPalette[tabPalette.size() - 1]);
    std::vector<int> tabNiveauGris;
    for (int i = 0; i < nbEtape + 1; i++)
        tabNiveauGris.push_back(i * (256 / nbEtape));

    std::string valeur2;
    for (int i = 0; i < tabNiveauGris.size() - 1; i++) {
        if (valeur < 0)
            valeur += 128;
        if (valeur >= tabNiveauGris[i] && valeur < tabNiveauGris[i + 1])
            valeur2 = tabPalette[i];
    }

    return valeur2;
}

void OutFile(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette, int width, int height) {

    std::array<int, 2> tab_dim = GetDimension(fichier_entrer);
    int largeur = tab_dim[0];
    int hauteur = tab_dim[1];

    std::ofstream file_out(fichier_sortie);
    TypeTab donnees_complete;

    if (width == 0 && height == 0)
        donnees_complete = DecodagePGM(fichier_entrer);
    else {
        if (width == 0 && height != 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), largeur, height);
        else if (width != 0 && height == 0)
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, hauteur);
        else
            donnees_complete = ReductionPGM(DecodagePGM(fichier_entrer), width, height);
    }
    for (size_t i = 0; i < donnees_complete.size(); i++) {           // On affiche les données de donnees_complete
        for (size_t j = 0; j < donnees_complete[i].size(); j++) {
            std::string valeur = AskChar(donnees_complete[i][j], choixPalette);
            file_out << valeur;
        }
        file_out << "\n";
    }
}

TypeTab ReductionPGM(TypeTab donnees, int width_max, int height_max) {

    TypeTab donnes_redimensionnees;

    int largeur = donnees[0].size();
    int hauteur = donnees.size(); 

    int ratio_largeur = largeur / width_max;
    int ratio_hauteur = hauteur / height_max;

    int div_moy = ratio_hauteur * ratio_hauteur;

    for (int i = 0; i < hauteur; i+=ratio_hauteur) { 
        std::vector<char> tab_temp;
        for (int j = 0; j < largeur; j+=ratio_largeur) {
            int moy = 0;
            for (size_t ij = 0; ij < ratio_hauteur; ij++)
                for (size_t ji = 0; ji < ratio_largeur; ji++) {
                    moy += donnees[i + ij][j + ji];
                }
                    
            tab_temp.push_back(int(char(moy)/(div_moy)));
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