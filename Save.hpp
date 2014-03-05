#ifndef __SAVE_HPP__
#define __SAVE_HPP__

#include <iostream>
#include <fstream>
#include "Run.hpp"
#include "Settings.hpp"
#include "MyGame.hpp"

class		Save
{
public:
  Save(const std::string & filename);
  ~Save();
private:
  std::ofstream	file;
public:
  bool		isFileOpen(void) const;
  void		players(std::list<APlayer*> players);
  void		caracteristique_player(const Skills *carac);
  void		bombs(std::list<Bomb*> bombs);
  void    	option(const Settings* option, gdl::GameClock *gameclock, const float & gameTime, const bool & gameRunning);
  void		map(Map *map);
  void		camera(const Camera & camera);
};

#endif
