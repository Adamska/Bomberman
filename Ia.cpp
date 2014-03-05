//
// Ia.cpp for  in /home/chevillard/Bomberman
// 
// Made by CHEVILLARD Alan
// Login   <chevillard@epitech.net>
// 
// Started on  Tue May 28 13:41:48 2013 CHEVILLARD Alan
// Last update Sun Jun  9 13:26:44 2013 Geoffrey Heckmann
//

#include <iostream>
#include "MyGame.hpp"
#include "Run.hpp"
#include "bomberman.hpp"
#include "Ia.hpp"

#define ABS(a) (((a) < 0) ? -(a) : (a))

Ia::Ia(MyGame *game, APlayer *ia)
{
  this->_ia = ia;
  this->_game = game;
  this->_dir = this->_ia->getDirection();
  this->_path = this->_ia->getPath();
  this->_beginPath = this->_ia->getBeginPath();
  this->_endPath = this->_ia->getEndPath();
}

Ia::~Ia()
{
  this->_ia->setPath(this->_path);
}

void				Ia::putBomb(gdl::Input &input, gdl::GameClock &gameClock)
{
  if (this->_ia->getSkills().getActualBomb() < this->_ia->getSkills().getMaxBomb() && this->_game->getRun().isBombInX_Y((unsigned int)this->_ia->getX(), (unsigned int)this->_ia->getY()) == false)
    {
      this->_game->getRun().pushBomb(new Bomb(this->_ia, gameClock.getTotalGameTime()));
      this->_ia->getSkills().putBomb();
    }
}

void	Ia::updateEndPath(std::list<Direction> path)
{
  std::list<Direction>::iterator	it;
  int					x;
  int					y;

  x = this->_ia->getX();
  y = this->_ia->getY();

  if (!path.empty())
    {
      for (it = path.begin(); it != path.end(); ++it)
	{
	  if ((*it) == UP)
	    y --;
	  else if ((*it) == LEFT)
	    x --;
	  else if ((*it) == DOWN)
	    y ++ ;
	  else if ((*it) == RIGHT)
	    x ++;
	}
    }
  else
    {
      x = -1;
      y = -1;
    }
  this->_endPath->_x = x;
  this->_endPath->_y = y;
}

void	Ia::updateBeginPath(std::list<Direction> path)
{
  int		x;
  int		y;
  Direction	dir;

  if (!path.empty())
    {
      dir = path.front();
      
      x = this->_ia->getX();
      y = this->_ia->getY();
      
      if (dir == UP)
	y --;
      else if (dir == LEFT)
	x --;
      else if (dir == DOWN)
	y ++ ;
      else if (dir == RIGHT)
	x ++;
    }
  else
    {
      x = -1;
      y = -1;
    }
  this->_beginPath->_x = x;
  this->_beginPath->_y = y;
}

int				Ia::getAleaPath(int *paths)
{
  int	i;
  int	alea;

  i = 0;
  alea = 0;
  while (i < 4)
    {
      if (paths[i] != 0)
	alea ++;
      i ++;
    }


  if (alea == 0)
    i = 5;
  else
    i = (rand() % alea);

  return (paths[i]);
}

std::list<Direction>		Ia::recGetSafePath(int x, int y, std::list<Direction> path)
{
  int			i;
  int			test;
  int			alea;
  int			paths[4];
  std::list<Direction>	pathTmp;
  std::list<Direction>	tmp1;
  std::list<Direction>	tmp2;
  std::list<Direction>	tmp3;
  std::list<Direction>	tmp4;
  Direction		prevDir;

  paths[0] = 0;
  paths[1] = 0;
  paths[2] = 0;
  paths[3] = 0;

  test = 0;
  if (!path.empty())
    prevDir = path.back();
  else
    prevDir = NONE;

  if (checkIsSafe(x, y - 1) == true && checkIsFreeCase(x, y - 1) == true)
    path.push_back(UP);
  else if (checkIsSafe(x - 1, y) == true && checkIsFreeCase(x - 1, y) == true)
    path.push_back(LEFT);
  else if (checkIsSafe(x, y + 1) == true && checkIsFreeCase(x, y + 1) == true)
   path.push_back(DOWN);
  else if (checkIsSafe(x + 1, y) == true && checkIsFreeCase(x + 1, y) == true)
    path.push_back(RIGHT);
  else
    {
      pathTmp = path;
      if (getInverseDir(prevDir) != UP && checkIsFreeCase(x, y - 1) == true)
	{
	  test = 1;
	  path.push_back(UP);
	  tmp1 = recGetSafePath(x, y - 1, path);
	}
      path = pathTmp;
      if (getInverseDir(prevDir) != LEFT && checkIsFreeCase(x - 1, y) == true)
	{
	  test = 1;
	  path.push_back(LEFT);
	  tmp2 = recGetSafePath(x - 1, y, path);
	}
      path = pathTmp;
      if (getInverseDir(prevDir) != DOWN && checkIsFreeCase(x, y + 1) == true)
	{
	  test = 1;
	  path.push_back(DOWN);
	  tmp3 = recGetSafePath(x, y + 1, path);
	}
      path = pathTmp;
      if (getInverseDir(prevDir) != RIGHT && checkIsFreeCase(x + 1, y) == true)
	{
	  test = 1;
	  path.push_back(RIGHT);
	  tmp4 = recGetSafePath(x + 1, y, path);
	}

      i = 0;
      if (tmp1.size() != path.size() && tmp1.size() > 0)
	{
	  paths[i] = 1;
	  i ++;
	}
      if (tmp2.size() != path.size() && tmp2.size() > 0)
	{
	  paths[i] = 2;
	  i ++;
	}
      if (tmp3.size() != path.size() && tmp3.size() > 0)
	{
	  paths[i] = 3;
	  i ++;
	}
      if (tmp4.size() != path.size() && tmp4.size() > 0)
	{
	  paths[i] = 4;
	  i ++;
	}

      alea = getAleaPath(paths);

      if (alea == 1)
	path = tmp1;
      if (alea == 2)
	path = tmp2;
      if (alea == 3)
	path = tmp3;
      if (alea == 4)
	path = tmp4;
      if (alea == 5)
	path = pathTmp;

      if (test == 0)
	{
	  if (!path.empty())
	    path.pop_back();
	}
    }
  return path;
}

Direction	Ia::getInverseDir(Direction dir)
{
  if (dir == UP)
    return DOWN;
  if (dir == DOWN)
    return UP;
  if (dir == RIGHT)
    return LEFT;
  if (dir == LEFT)
    return RIGHT;
  if (dir == NONE)
    return NONE;
}

bool	Ia::checkIsSafe(int x, int y)
{
  std::list<Bomb*>		bomb;
  std::list<Bomb*>::iterator	it;
  int				i;
  int				test;

  bomb = this->_game->getRun().getBomb();
  it = bomb.begin();
  i = 0;
  
  while (it != bomb.end())
    {
      if ( ((int)(*it)->getX() == (int)x && ABS( (int)(*it)->getY() - (int)y ) <= (*it)->getRange()) || ((int)(*it)->getY() == (int)y && ABS((int)(*it)->getX() - (int)x) <= (*it)->getRange()))
	return false;
      i++;
      ++it;
    }
  return true;
}

bool	Ia::checkIsFreeCase(int x, int y)
{
  int	test;

  test = this->_game->getRun().getMap()->getAt(x, y);
  test = this->_game->getRun().isBomb(x, y, test);

  if (test == 6)
    return true;
  else
    return false;
}

Vector2f	*Ia::getNewPosition(int x, int y, Direction dir)
{
  Vector2f	*pos;

  pos = new Vector2f(x, y);
  if (dir == UP)
    pos->_y --;
  else if (dir == LEFT)
    pos->_x --;
  else if (dir == DOWN)
    pos->_y ++;
  else if (dir == RIGHT)
    pos->_x ++;
  return pos;
}

void		Ia::displayList(std::list<Direction> path)
{
  std::list<Direction>::iterator it;

  for (it = path.begin(); it != path.end(); ++ it)
    {
      if ((*it) == UP)
	std::cout << "UP" << std::endl;
      else if ((*it) == LEFT)
	std::cout << "LEFT" << std::endl;
      else if ((*it) == DOWN)
	std::cout << "DOWN" << std::endl;
      else if ((*it) == RIGHT)
	std::cout << "RIGHT" << std::endl;
    }
}

void		Ia::displayDir(Direction dir)
{
  if (dir == UP)
    std::cout << "IA go UP" << std::endl;
  else if (dir == LEFT)
    std::cout << "IA go LEFT" << std::endl;
  else if (dir == DOWN)
    std::cout << "IA go DOWN" << std::endl;
  else if (dir == RIGHT)
    std::cout << "IA go RIGHT" << std::endl;
  
}

void		Ia::go(gdl::Input input, gdl::GameClock& gameClock)
{
  std::list<Direction>			path;
  std::list<Direction>::iterator	it;
  Direction				dir;
  int					x;
  int					y;
  int					newX;
  int					newY;

  x = this->_ia->getX();
  y = this->_ia->getY();
  path = this->_path;

  // Si je suis dans la premier maillon du path
  if (this->_beginPath->_x == x && this->_beginPath->_y == y)
    {
      path.pop_front();
      updateBeginPath(path);
    }

  // Si je suis dans le dernir element du path
  if (this->_endPath->_x == x && this->_endPath->_y == y)
    {
      putBomb(input, gameClock);
      path.clear();
      updateEndPath(path);
    }

  // Si dans zone mortelle
  if (checkIsSafe(x, y) == false)
    {
      // Si cest la premiere action de lIA OU que le dernier element du path est mortelle
      if ((this->_endPath->_x == -1 && this->_endPath->_y == -1) ||
	  (checkIsSafe(this->_endPath->_x, this->_endPath->_y) == false))
	{
	  path = recGetSafePath(x, y, path);
	  updateBeginPath(path);
	  updateEndPath(path);
	}

      // Execute le deplacement de lIA
      if (!path.empty())
	{ 
	  dir = path.front();
	  newX = getNewPosition(x, y, dir)->_x;
	  newY = getNewPosition(x, y, dir)->_y;
	  if (checkIsFreeCase(newX, newY) == true)
	    {
	      this->_ia->changeDir(dir);
	      this->_ia->update(*(this->_game->getRun().getGameClock()), input);
	    }
	}
    }
  else
    {
      putBomb(input, gameClock);
    }
  this->_path = path;
}
