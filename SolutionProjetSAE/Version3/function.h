#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>

using DecodagePGM_t = std::vector<std::vector<char>>;
using DecodagePalette_t = std::vector<std::string>;

std::string			ChoixPalette		();
std::string			ChoixFichierEntree	();
std::string			ChoixFichierSortie	();
DecodagePGM_t		DecodagePGM			(std::string fichier);
DecodagePalette_t	DecodagePalette		(std::string palette);
std::string			AskChar				(char valeur, std::string choixPalette);
void				OutFile				(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette);
