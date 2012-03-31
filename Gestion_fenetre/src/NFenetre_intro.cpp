#include "../include/NFenetre_intro.h"
#include <fstream>
#include "../include/Hevent.h"

NFenetre_intro::NFenetre_intro(std::string chemin, class Hevent *Heventb)
{
    Raccourcit_clavier = false;
    deplacement = false;
    Hevent = Heventb;
    unsigned int i = 0;
    num_image = 0;
    Other_desactive = false;
    std::ifstream fichier(chemin.c_str());
    std::string ligne;
    if(fichier.fail())
    {
        std::cerr << "fichier de config non trouvé\n" << std::endl;
        exit(1);
    }
	fichier >> nb_fenetre;
    liste_images = new sf::Image[nb_fenetre];
    std::getline(fichier, ligne);
    while(i != nb_fenetre)
    {
        std::getline(fichier, ligne);
        if (!liste_images[i].LoadFromFile(ligne))
        {
            std::cerr << "'" << ligne << "' non trouvé\n" << std::endl;
            //exit(1);
        }
        i++;
    }
    //afficher.Lock();
    fond.SetImage(liste_images[0]);
    Clock.Reset();
    //afficher.Unlock();
}

NFenetre_intro::~NFenetre_intro()
{
    delete[] liste_images;
}

void NFenetre_intro::getImage(Nwindow &wind)
{
    wind.Draw(fond);
}

void NFenetre_intro::setEvent(sf::Event &Event)
{
    if(nb_fenetre == 2 && Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Q)
    {
        Hevent->close_fenetre(this);//supprimer fenetre
        this->~NFenetre_intro();
        return;
    }
    if(Event.Type == sf::Event::MouseButtonReleased)
        deplacement = false;
    if(deplacement && Event.Type == sf::Event::MouseMoved)
    {
        fond.SetPosition(depart_x+Event.MouseMove.X,depart_y+Event.MouseMove.Y);
    }
    if(nb_fenetre == 2 && Event.Type == sf::Event::MouseButtonPressed)
    {
        deplacement = true;
        depart_x = fond.GetPosition().x - Event.MouseButton.X;
        depart_y = fond.GetPosition().y - Event.MouseButton.Y;
        return;
    }
    if((Event.Type == sf::Event::KeyPressed || Event.Type == sf::Event::MouseButtonPressed) && Clock.GetElapsedTime() > 0.5)
    {
        num_image++;
        if(num_image >= nb_fenetre)
        {
            num_image = 0;
            if(nb_fenetre != 2)
            {
                NFenetre_intro *fen2 = new NFenetre_intro("Config/zintro.txt",Hevent);
                Hevent->new_fenetre(fen2);
            }
            //Hevent->setFond(NULL);
            //this->~NFenetre_intro();
            //return;
        }
        fond.SetImage(liste_images[num_image]);
        Clock.Reset();
    }
}


bool NFenetre_intro::isNotTouch(int x, int y)
{
    if(deplacement)
        return false;
    int xmin = fond.GetPosition().x;
    int ymin = fond.GetPosition().y;
    if(xmin + fond.GetSize().x >= x && xmin < x && ymin + fond.GetSize().y >= y && ymin < y)
        return false;
    return true;
}

void NFenetre_intro::lost_focus()
{

}
