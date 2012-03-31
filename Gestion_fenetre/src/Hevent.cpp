#include "../include/Hevent.h"
#include "../include/NFenetre_intro.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>


void lance_afficher(void *data)
{

	Hevent *hevent = static_cast<Hevent*>(data);
	hevent->afficher();
}

Hevent::Hevent()
{
	tete = NULL;
	fond = NULL;
	wind.SetActive(false);
	sf::Thread Thread(&lance_afficher, this);
	nb_fenetre =0;
	Thread.Launch();/**/
	NFenetre_intro Fenetre_intro("Config/intro.txt", this);
	fond = &Fenetre_intro;
	event();
	//TODO exit
	Thread.Wait();
}


Hevent::~Hevent()
{
}

void Hevent::event()//TODO thread
{
	Running = true;
	while (Running)
	{
		sf::Event Event;
		while (wind.GetEvent(Event))
		{
			if((Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape) || Event.Type == sf::Event::Closed)
			{
				Running = false;
				break;
			}
			if(tete != NULL)
			{
				HFenetre *destinataire = tete;
				if(Event.Type == sf::Event::MouseButtonPressed)
				{
					bool tour = false;
					while(destinataire->isNotTouch(Event.MouseButton.X, Event.MouseButton.Y))//TODO coordonnée
					{
						if(destinataire == tete && tour)
						{
							destinataire = fond;
							break;
						}
						if(destinataire->isOther_desactive())
						{
						    destinataire = NULL;
						    break;
						}
						tour = true;
						destinataire = destinataire->getPrecedante();
					}
				}
				if(destinataire != NULL && destinataire != fond)
				{
                    if(destinataire != tete)
                    {
                        destinataire->getSuivante()->setPrecedante(destinataire->getPrecedante());
                        destinataire->getPrecedante()->setSuivante(destinataire->getSuivante());
                        //TODO corriger
                        tete->getSuivante()->setPrecedante(destinataire);
                        destinataire->setPrecedante(tete);
                        destinataire->setSuivante(tete->getSuivante());
                        tete->setSuivante(destinataire);
                        tete = destinataire;
                    }
					if(Event.Type == sf::Event::KeyPressed && destinataire->isRaccourcit_clavier())
					{
						std::cout << "raccourcit" << std::endl;//raccourcit clavier()
					}
                    else
					{
						destinataire->setEvent(Event);
					}
				}
				else if(destinataire != NULL)
				{
					fond->setEvent(Event);
					destinataire = tete;
					bool tour = true;
                    while(destinataire != tete || tour)
                    {
                        tour = false;
                        destinataire->lost_focus();
                        destinataire = destinataire->getPrecedante();
                    }
				}
			}
            else if(fond != NULL)
            {
                fond->setEvent(Event);
            }
		}
	}
}

bool Hevent::new_fenetre(HFenetre *id)
{
	HFenetre *tmp;
	if(id == NULL)
	{
		//TODO erreur
		return false;
	}
	if(nb_fenetre == NB_FEN_MAX)
	{
		return false;//TODO erreur
	}
	if(tete == NULL)
	{
		id->setSuivante(id);
		id->setPrecedante(id);
	}
	else
	{
		id->setSuivante(tete->getSuivante());//la dernière fenêtre est la fenetre suivante de la nouvelle
		id->setPrecedante(tete);//la tête est la fenetre précédante de la nouvelle
		tete->getSuivante()->setPrecedante(id);//la nouvelle est la fenêtre précédante de la dernière fenetre
		tete->setSuivante(id);//la nouvelle fenêtre est la fenêtre suivante de la tête
	}
	tete = id;
	nb_fenetre++;
	return true;
}

bool Hevent::close_fenetre(HFenetre *id)
{
	HFenetre *tmp = tete;
	if(tete == NULL)
	{
		return false; //TODO erreur pas de fenêtre
	}
	bool tour = false;
	while(id != tmp)
	{
		if(tmp == tete && tour)
		{
			return false;//TODO erreur pas trouvé
		}
		tour = true;
		tmp = tmp->getPrecedante();
	}
	nb_fenetre--;
	if(tete == id)
	{
	    if(nb_fenetre == 0)
            tete = NULL;
        else
        {
            tete = id->getPrecedante();
            id->getPrecedante()->setSuivante(id->getSuivante());
            id->getSuivante()->setPrecedante(id->getPrecedante());
        }
        return true;
	}
	id->getPrecedante()->setSuivante(id->getSuivante());
	id->getSuivante()->setPrecedante(id->getPrecedante());
	return true;
}

void Hevent::afficher()
{
	wind.SetFramerateLimit(IMGPROSEC);
	while(Running)
	{
		if(fond != NULL)
		{
			fond->getImage(wind);
		}
		if(tete != NULL){
			HFenetre *tmp = tete->getSuivante();
			HFenetre *tmp2 = tmp;
			bool tour = true;
			while(tmp != tmp2 || tour)
			{
				tour = false;
				tmp->getImage(wind);//TODO réduit barre -> wind.addTache()?
				tmp = tmp->getSuivante();
			}
		}
		//utiliser_wind.Lock();
		wind.Display();
		//utiliser_wind.Unlock();
	}
}

void Hevent::setFond(HFenetre * new_fond)
{
    if(fond != NULL)
    {
        //??
    }
    fond = new_fond;
}
