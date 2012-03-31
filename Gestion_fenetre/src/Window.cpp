#include "../include/Window.h"
#include <fstream>

Nwindow::Nwindow()
{
	std::ifstream fichier("version", std::ios::in);
	if(!fichier)
	{
		std::cerr << "Erreur lors de l'ouverture du fichier de param" << std::endl;
		exit(1);//TODO erreur
	}
	std::getline(fichier, titre);
	titre = "Last Dungeon v." + titre;
	if (!icone.LoadFromFile("icone.png"))
	{
		std::cerr << "icone.png non trouvé\n" << std::endl;
		exit(1);//TODO erreur
	}
	this->Create(sf::VideoMode(500, 500, 32), titre, sf::Style::Titlebar | sf::Style::Close/**/);
	this->SetIcon(icone.GetWidth(), icone.GetHeight(), icone.GetPixelsPtr());
	this->Display();
	this->SetActive(false);
}
Nwindow::~Nwindow()
{

}
