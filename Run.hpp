#ifndef __RUN_HPP__
#define __RUN_HPP__

#include <iostream>
#include <list>
#include <vector>
#include "APlayer.hpp"
#include "Ia.hpp"
#include "Map.hpp"
#include "Settings.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "GameClock.hpp"

class			Bomb;

class			Run
{
public:
  Run(gdl::GameClock*);
  ~Run();

private:
  Map				        *_map;
  Song					* _musicBomb;
  gdl::GameClock			*gameClock_;
  std::list<APlayer*>			_players;
  std::list<Bomb*>			_bombs;
  bool					_bombSong;
  float					_time;
  
public:
  void					manageBomb(void);
  void					createPlayers(const Settings & opt);
  void					createAI(const Settings & opt);
  Vector2f				*placePlayers(const Settings& opt);
  APlayer*				getPlayerById(const unsigned int& id) const;
  Map*					getMap() const;
  std::list<APlayer*>			getPlayer() const;
  std::list<Bomb*>			getBomb() const;
  unsigned int				getWidth() const;
  unsigned int				getHeight() const;
  float					getTime(void) const;
  void					setTime(const float & time);
  void					setMap(Map* map);
  void					setSong(Song *);
  void					setPlayers(std::list<APlayer*> players);
  void					setBombs(std::list<Bomb*> bombs);
  void					isSomeone(unsigned int x, unsigned int y);
  void					pushBomb(Bomb* newBomb);
  gdl::GameClock		        *getGameClock() const;
  bool					isBombInX_Y(const unsigned int & x, const unsigned int & y);
  unsigned int				isBomb(const unsigned int& x, const unsigned int& y, const unsigned int& prevRet);
};


#endif

