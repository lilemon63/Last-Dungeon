#ifndef HEVENT_H
#define HEVENT_H
#include "Window.h"
#include <iostream>
#include <SFML/System.hpp>
#include <stack>
#include "HFenetre.h"
#define NB_FEN_MAX 20
#define IMGPROSEC 60

class Hevent
{
	private:
		int nb_fenetre;
		HFenetre *tete;
		HFenetre *fond;
		Nwindow wind;
		bool Running;
		sf::Mutex utiliser_wind;
	public:
		void event();
		void afficher();//TODO friend?
		bool new_fenetre(HFenetre *id);
		bool close_fenetre(HFenetre *id);
		void setFond(HFenetre * new_fond);
		Hevent();
		~Hevent();
};

#endif // HEVENT_H
