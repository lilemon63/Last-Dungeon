#include "../include/HFenetre.h"

HFenetre::HFenetre()
{
	Other_desactive = false;
}

HFenetre::~HFenetre()
{

}

void HFenetre::lost_focus()
{

}

void HFenetre::setSuivante(HFenetre *valeur)
{
	if(valeur != NULL)
		suivante = valeur;
}

HFenetre * HFenetre::getSuivante()
{
	return suivante;
}

HFenetre * HFenetre::getPrecedante()
{
	return precedante;
}
void HFenetre::setPrecedante(HFenetre *valeur)
{
	if(valeur != NULL)
		precedante = valeur;
}
HFenetre *HFenetre::getid()
{
	return this;
}

sf::Sprite HFenetre::getSprite()
{
	return fond;
}


void HFenetre::getImage(Nwindow &wind)
{
	wind.Draw(fond);
}

bool HFenetre::isNotTouch(int x, int y)//TODO coordonnée
{
	return false;
}

bool HFenetre::isOther_desactive()
{
	return Other_desactive;
}

bool HFenetre::isRaccourcit_clavier()
{
	return Raccourcit_clavier;
}

void HFenetre::setEvent(sf::Event &Event)
{

}
