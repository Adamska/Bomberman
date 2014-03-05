#include <iostream>
#include <fstream>
#include <iterator>
#include "bomberman.hpp"
#include "MenuManager.hpp"
#include "Skills.hpp"
#include "Map.hpp"
#include "Settings.hpp"
#include "MyGame.hpp"
#include "Save.hpp"

Save::Save(const std::string & filename)
{
  this->file.open(filename.c_str(), std::ios::out);
}

Save::~Save()
{
  if (this->file.is_open())
    this->file.close();
}

bool			Save::isFileOpen() const
{
  if (this->file.is_open())
    return (true);
  return (false);
}

void			Save::caracteristique_player(const Skills *carac)
{
  this->file << "<caract>\n\t\t";
  this->file << "<alive>" << carac->getAlive() << "</alive>\n\t\t";
  this->file << "<speed>" << carac->getSpeed() << "</speed>\n\t\t";
  this->file << "<maxBomb>" << carac->getMaxBomb() << "</maxBomb>\n\t\t";
  this->file << "<actualBomb>" << carac->getActualBomb() << "</actualBomb>\n\t";
  this->file << "<range>" << carac->getRange() << "</range>\n\t";
  this->file << "</caract>\n";
}

void			Save::players(std::list<APlayer*> players)
{
  gdl::Color		color;
  std::list<APlayer*>::iterator	it;

  for (it = players.begin(); it != players.end(); ++it)
    {
      this->file << "<player>\n\t";
      this->file << "<id>" << (*it)->getId() << "</id>\n\t";
      color = ((*it)->getModel()).get_default_model_color();
      this->file << "<colorR>" << static_cast<int>(color.r) << "</colorR>\n\t";
      this->file << "<colorG>" << static_cast<int>(color.g) << "</colorG>\n\t";
      this->file << "<colorB>" << static_cast<int>(color.b) << "</colorB>\n\t";
      this->file << "<colorA>" << static_cast<int>(color.a) << "</colorA>\n\t";
      this->file << "<pos>" << (*it)->getX() << ";" << (*it)->getY() << "</pos>\n\t";
      this->file << "<direction>" << (*it)->getDirection() << "</direction>\n\t";
      this->file << "<ia>" << (*it)->isIA() << "</ia>\n\t";
      caracteristique_player(&((*it)->getSkills()));
      this->file << "</player>\n";
    }
}

void			Save::bombs(std::list<Bomb*> bombs)
{
  std::list<Bomb*>::iterator	it;

  for (it = bombs.begin(); it != bombs.end(); ++it)
    {
      this->file << "<bomb>\n\t";
      this->file << "<idPlayer>" << (*it)->getId() << "</idPlayer>\n\t";
      this->file << "<pos>" << (*it)->getX() << ";" << (*it)->getY() << "</pos>\n\t";
      this->file << "<timer>" << (*it)->getTimePosed() << "</timer>\n\t";
      this->file << "<delay>" << (*it)->getDelayExplosion() << "</delay>\n\t";
      this->file << "<range>" << (*it)->getRange() << "</range>\n";
      this->file << "</bomb>\n";
    }
}

void			Save::option(const Settings* option, gdl::GameClock *gameclock, const float & gameTime, const bool & gameRunning)
{
  this->file << "<option>\n\t";
  this->file << "<run>" << gameRunning << "</run>\n\t";
  this->file << "<gameclock>" << gameclock->getTotalGameTime() << "</gameclock>\n\t";
  this->file << "<xmap>" << option->getWidth() << "</xmap>\n\t";
  this->file << "<ymap>" << option->getHeight() << "</ymap>\n\t";
  this->file << "<nbPlayer>" << option->getNbPlayer() << "</nbPlayer>\n\t";
  this->file << "<nbIA>" << option->getNbIa() << "</nbIA>\n";
  this->file << "</option>\n";
}

void			Save::map(Map *map)
{
  this->file << "<map>\n\t";
  this->file << "<xmax>" << map->getWidth() << "</xmax>\n\t";
  this->file << "<ymax>" << map->getHeight() << "</ymax>\n";
  for (int i = 0; i < map->getHeight(); ++i)
    {
      this->file << "\t<line>";
      for (int j = 0; j < map->getWidth(); ++j)
	{
	  this->file << map->getAt(j, i);
	  if (j + 1 < map->getWidth())
	    this->file << ";";
	}
      this->file << "</line>\n";
    }
  this->file << "</map>\n";
}

void      Save::camera(const Camera & camera)
{
  this->file << "<camera>\n\t";
  this->file << "<posX>" << camera.getPos().getX() << "</posX>\n\t";
  this->file << "<posY>" << camera.getPos().getY() << "</posY>\n\t";
  this->file << "<posZ>" << camera.getPos().getZ() << "</posZ>\n\t";
  this->file << "<posnX>" << camera.getPosn().getX() << "</posnX>\n\t";
  this->file << "<posnY>" << camera.getPosn().getY() << "</posnY>\n\t";
  this->file << "<posnZ>" << camera.getPosn().getZ() << "</posnZ>\n\t";
  this->file << "<rotX>" << camera.getRot().getX() << "</rotX>\n\t";
  this->file << "<rotY>" << camera.getRot().getY() << "</rotY>\n\t";
  this->file << "<rotZ>" << camera.getRot().getZ() << "</rotZ>\n";
  this->file << "</camera>\n";
}

void			MyGame::save_game(void)
{
  Save			save("save.xml");

  if (this->run_ != NULL)
    {
      this->run_->setTime(this->getRun().getGameClock()->getTotalGameTime() - this->run_->getTime());
      if (save.isFileOpen() && this->run_->getPlayer().size() > 0)
	{
	  save.option(this->settings_, this->getRun().getGameClock(), this->run_->getTime(), this->inGame_);
	  save.players(this->run_->getPlayer());
	  save.bombs(this->run_->getBomb());
	  save.map(this->run_->getMap());
	  save.camera(this->camera_);
	}
    }
}
