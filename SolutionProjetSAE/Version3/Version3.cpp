#include <iostream>
#include <sstream>
#include <array>
#include "function.h"

int main()
{

    std::string nomFichierEntree = ChoixFichierEntree();
    std::string nomFichierSortie = ChoixFichierSortie();
    std::string choixPalette = ChoixPalette();

    OutFile(nomFichierEntree, nomFichierSortie, choixPalette);
}
