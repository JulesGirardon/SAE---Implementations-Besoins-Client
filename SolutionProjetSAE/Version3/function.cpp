#include "function.h"

std::string ChoixPalette() {

    std::string palette;
    std::cout << "Quelle palette voulez-vous : Palette 1 ou Palette 2 ou Palette 1 UTF-8 ou Palette 2 UTF-8 ";
    std::getline(std::cin >> std::ws, palette);

    return palette;
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

std::string ChoixFichierEntree() {

    std::string nomFichierEntree;
    std::cout << "Quel fichier voulez-vous sélectionner : ";
    std::getline(std::cin >> std::ws, nomFichierEntree);

    return nomFichierEntree;
}

std::string ChoixFichierSortie() {

    std::string nomFichierSortie;
    std::cout << "Veuillez entrer le nom du fichier de sortie : ";
    std::getline(std::cin >> std::ws, nomFichierSortie);

    return nomFichierSortie;
}

DecodagePGM_t DecodagePGM(std::string nom_fichier) {

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

    int largeur = stoi(tab_entete[2][0]);                   // On récupère la largeur et la hauteur
    int hauteur = stoi(tab_entete[2][0]);

    DecodagePGM_t donnes_complete;                          // Ce tableau stocke toutes les lignes
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
    for (int i = 0; i < nbEtape+1; i++)
        tabNiveauGris.push_back(i * (256 / nbEtape));
    
    std::string valeur2;
    for (int i = 0; i < tabNiveauGris.size()-1; i++) {
        if (valeur < 0)
            valeur += 128;
        if (valeur >= tabNiveauGris[i] && valeur < tabNiveauGris[i+1])
            valeur2 = tabPalette[i];
    }

    return valeur2;
}

void OutFile(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette) {

    std::ofstream file_out(fichier_sortie + ".txt");

    DecodagePGM_t donnes_complete = DecodagePGM(fichier_entrer);

    for (size_t i = 0; i < donnes_complete.size(); i++) {           // On affiche les données de donnees_complete
        for (size_t j = 0; j < donnes_complete[i].size(); j++) {
            file_out << AskChar(donnes_complete[i][j], choixPalette);
        }
        file_out << "\n";
    }
}