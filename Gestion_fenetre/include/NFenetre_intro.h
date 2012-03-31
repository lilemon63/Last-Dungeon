#ifndef NFENETRE_INTRO_H
#define NFENETRE_INTRO_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "HFenetre.h"

class NFenetre_intro : public HFenetre
{
    private :
        unsigned int nb_fenetre;
        sf::Image *liste_images;
        int num_image;
        sf::Clock Clock;
        class Hevent * Hevent;
        bool deplacement;
        int depart_x;
        int depart_y;
    public :
        virtual void lost_focus();
        NFenetre_intro(std::string chemin, class Hevent *Hevent);
        virtual ~NFenetre_intro();
        virtual bool isNotTouch(int x, int y);
        virtual void getImage(Nwindow &wind);
        virtual void setEvent(sf::Event &Event);
};

#endif // NFENETRE_INTRO_H
