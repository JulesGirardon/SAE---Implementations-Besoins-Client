#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>

int main()
{
    // Version 1

    std::ifstream fichier("img1.pgm", std::ios_base::binary);  // Ouverture de notre image au format pgm

    if (!fichier.is_open()) {                                     // On vérifie que le fichier est bien ouvert
        std::cerr << "Le ficher n'a pu être ouvert !";
        return 1;
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

    std::vector<std::vector<char>> donnes_complete;         // Ce tableau stocke toutes les lignes
    std::vector<char> donnes(largeur);

    for (size_t i = 0; i < hauteur; i++) {                  // Cette boucle récupère lignes par lignes les données et les mets dans le tableau donnes_complete
        fichier.read(donnes.data(), largeur);
        donnes_complete.push_back(donnes);
    }

    std::ofstream file_out("test42.txt");

    for (size_t i = 0; i < donnes_complete.size(); i++) {           // On affiche les données de donnees_complete
        for (size_t j = 0; j < donnes_complete[i].size(); j++) {
            if (donnes_complete[i][j] < 0)                          // Certains char sont inférieur à 0, ainsi vu que nous sommes sur 256 valeurs et que le char est signé (donc -128 à 127) on ajoute 128 pour avoir que des chars positifs
                donnes_complete[i][j] += 128;
            if (donnes_complete[i][j] >= 0 && donnes_complete[i][j] < 51)
                file_out << "█";
            else if (donnes_complete[i][j] >= 51 && donnes_complete[i][j] < 102)
                file_out << "▓";
            else if (donnes_complete[i][j] >= 102 && donnes_complete[i][j] < 153)
                file_out << "▒";
            else if (donnes_complete[i][j] >= 153 && donnes_complete[i][j] < 204)
                file_out << "░";
            else if(donnes_complete[i][j] >= 204 && donnes_complete[i][j] < 255)
                file_out << " ";
        }
        file_out << "\n";
    }
}
