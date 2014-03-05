//
// Ia.hpp for  in /home/chevillard/Bomberman
// 
// Made by CHEVILLARD Alan
// Login   <chevillard@epitech.net>
// 
// Started on  Tue May 28 13:42:28 2013 CHEVILLARD Alan
// Last update Sat Jun  8 15:26:45 2013 CHEVILLARD Alan
//

#ifndef __IA_HPP__
#define __IA_HPP__

#include <unistd.h>

class MyGame;

class Ia
{
public:
  Ia(MyGame *, APlayer *);
  ~Ia();

  int		getAleaPath(int	*);
  void		displayList(std::list<Direction>);
  void		displayDir(Direction);
  void		go(gdl::Input, gdl::GameClock&);
  void		updateEndPath(std::list<Direction>);
  void		updateBeginPath(std::list<Direction>);
  void		putBomb(gdl::Input &, gdl::GameClock &);
    
  bool		checkIsSafe(int, int);
  bool		checkIsFreeCase(int, int);
  std::list<Direction>	recGetSafePath(int, int, std::list<Direction>);

  Direction	getInverseDir(Direction);
  Vector2f	*getNewPosition(int, int, Direction);
private:
  APlayer		*_ia;
  MyGame		*_game;
  Direction		_dir;
  Vector2f		*_endPath;
  Vector2f		*_beginPath;
  std::list<Direction>	_path;
};

#endif
