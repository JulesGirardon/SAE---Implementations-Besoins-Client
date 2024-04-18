#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>

using TypeTab = std::vector<std::vector<char>>;
using DecodagePalette_t = std::vector<std::string>;

TypeTab				DecodagePGM			(std::string fichier);
DecodagePalette_t	DecodagePalette		(std::string palette);
std::string			AskChar				(char valeur, std::string choixPalette);
std::array<int, 2>	GetDimension		(std::string nom_fichier);
void				OutFile				(std::string fichier_entrer, std::string fichier_sortie, std::string choixPalette, int width, int height);
TypeTab				ReductionPGM		(TypeTab donnees, int width_max, int height_max);
std::string			AccesError			();