#ifndef HFENETRE_H
#define HFENETRE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Window.h"

class HFenetre
{

	private :
		HFenetre * suivante;
		HFenetre * precedante;
	protected :
        bool Other_desactive;
        bool Raccourcit_clavier;
        sf::Sprite fond;
        sf::Mutex afficher;
	public :
        virtual void lost_focus();
		HFenetre();
		virtual ~HFenetre();
		void setSuivante(HFenetre *valeur);
		HFenetre *getSuivante();
		HFenetre *getPrecedante();
		void setPrecedante(HFenetre *valeur);
		HFenetre *getid();
		sf::Sprite getSprite();
		virtual void getImage(Nwindow &wind);
		virtual bool isNotTouch(int x, int y);//TODO coordonnée
		bool isRaccourcit_clavier();
		virtual void setEvent(sf::Event &Event);
        bool isOther_desactive();
};

#endif // HFENETRE_H
