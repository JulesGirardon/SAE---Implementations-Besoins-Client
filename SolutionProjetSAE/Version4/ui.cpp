#include "ui.h"
#include "function.h"

void Menu(int argc, char* argv[]) {
    // argv est le tableau contenant les commandes et argc est le nb de commande
    std::string fichierEntree = "";
    std::string fichierSortie = "";
    std::string fichierPalette = "palette.txt";
    std::string width = "0";
    std::string height = "0";

    if (std::string(argv[1]) == "--help") {
        std::cout <<
            "Usage: \n" <<
            "pgm2txt    [options] \n" <<
            "Options :\n\n" <<
            "--input fichier                                Spécifie le fichier image à convertir \n" <<
            "                                               Si ce paramètre n'est pas spécifié, le fichier est demandé via la console. \n\n" <<
            "--output fichier                               Spécifie le nom du fichier1 texte qui contiendra l'Ascii Art fichier2 \n" <<
            "                                               Si ce paramètre n'est pas spécifié, l'Ascii Art est sortie dans la console. \n\n" <<
            "--palette fichier                              Spécifie un fichier texte contenant la palette de couleur Ascii. \n" <<
            "                                               Chaque ligne du fichier contient un charactère en UTF - 8, du plus sombre au plus clair. \n" <<
            "                                               Si ce paramètre n'est pas spécifié, la palette par défaut est :\n                      \"W\", \"w\", \"l\", \"i\", \":\", \", \", \".\", \" \" \n\n" <<
            "--help                                         Affiche cette aide. \n";

    }
    else {
		for (int i = 0; i < argc; ++i)
		{
            std::string argument = argv[i];
            if (argument == "--input")
                fichierEntree = argv[i + 1];
            else if (argument == "--output")
                fichierSortie = argv[i + 1];
            else if (argument == "--palette")
                fichierPalette = argv[i + 1];
            else if (argument == "--width")
                width = argv[i + 1];
            else if (argument == "--height")
                height = (argv[i + 1]);
		}

    }
    //si fichier sortie == "" --> sortie console

    int int_witdh = std::stoi(width);
    int int_height = std::stoi(height);
    OutFile(fichierEntree, fichierSortie, fichierPalette, int_witdh, int_height);
}