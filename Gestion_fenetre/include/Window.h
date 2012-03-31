#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class Nwindow : public sf::RenderWindow
{
	private :
		sf::Image icone;
		std::string titre;
	public :
		Nwindow();
		~Nwindow();
};

#endif // WINDOW_H
