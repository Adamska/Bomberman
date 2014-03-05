#include <sstream>
#include <fstream>
#include <cstdlib>
#include "Map.hpp"
#include "Pattern.hpp"
#include "Bonus.hpp"
#include "Tools.hpp"


std::vector<std::vector<Ibloc> >	Map::getMap() const
{
  return (_map);
}

unsigned int				Map::getWidth() const
{
  return (_width);
}

unsigned int				Map::getHeight() const
{
  return (_height);
}

void					Map::setWidth(const unsigned int &x)
{
  this->_width = x;
}

void					Map::setHeight(const unsigned int &y)
{
  this->_height = y;
}

void					Map::setStone(Stone* stone)
{
  this->block = stone;
}

void					Map::setBox(Box *box)
{
  this->wall = box;
}

void					Map::setFloor(Floor *floor)
{
  this->ground = floor;
}

void					Map::setExplosion(Explosion *explosion)
{
  this->explosion = explosion;
}

void					Map::setBombSup(BombSup *bombsup)
{
  this->bomb = bombsup;
}

void					Map::setSpeed(Speed *speed)
{
  this->speed = speed;
}
 
void					Map::setRange(Range *range)
{
  this->range = range;
}

void					Map::setMap(std::vector<std::vector<Ibloc> > &map)
{
  this->_map = map;
}

Ibloc					Map::createBonusBloc(const Settings& opt) const
{
  Ibloc		ret = DESTRUCTIBLE;
 
  if ((unsigned int)(rand() % 100) <= 50)
    {
    ret = (Ibloc)(rand() % 3 + (DESTRUCTIBLE + 1));
}
  return (ret);
}

void					Map::removeBlocAroundPlayers(std::list<APlayer*> playerList)
{
  std::list<APlayer*>::iterator it = playerList.begin();

  while (it != playerList.end())
    {
      if ((*it)->getX() < this->getWidth() / 2 && (*it)->getY() < getHeight() / 2)
	{
	  this->_map[(*it)->getY()][(*it)->getX() + 1] = EMPTY;
	  this->_map[(*it)->getY() + 1][(*it)->getX()] = EMPTY;
	}
      else if ((*it)->getX() > this->getWidth() / 2 && (*it)->getY() < getHeight() / 2)
	{
	  this->_map[(*it)->getY() + 1][(*it)->getX()] = EMPTY;
	  this->_map[(*it)->getY()][(*it)->getX() - 1] = EMPTY;
	}
      else if ((*it)->getX() < this->getWidth() / 2 && (*it)->getY() > getHeight() / 2)
	{
	  this->_map[(*it)->getY()][(*it)->getX() + 1] = EMPTY;
	  this->_map[(*it)->getY() - 1][(*it)->getX()] = EMPTY;
	}
      else
	{
	  this->_map[(*it)->getY()][(*it)->getX() - 1] = EMPTY;
	  this->_map[(*it)->getY() - 1][(*it)->getX()] = EMPTY;
	}
      this->_map[(*it)->getY()][(*it)->getX()] = EMPTY;
      it++;
    }
}


void					Map::createMap(const Settings & opt)
{
  std::vector<Ibloc>			tmp;
  int					xmax = opt.getWidth();
  int					ymax = opt.getHeight();
  int					x = 0;
  int					y = 0;

  _width = opt.getWidth();
  _height = opt.getHeight();
  while (y < ymax)
    {
      while (x < xmax)
	{
	  if (y == 0 || y == ymax - 1 || x == 0 || x == xmax - 1 || (y % 2 == 0 && x % 2 == 0))
	    tmp.push_back(INDESTRUCTIBLE);
	  else if ((y >= 1 && y <= 2 && (x == 1 || x == xmax - 2)) ||
		   (y >= ymax - 3 && y <= ymax - 2 && (x == 1 || x == xmax - 2)) ||
		   (x >= 1 && x <= 2 && (y == 1 || y == ymax - 2)) ||
		   (x >= xmax - 3 && x <= xmax - 2 && (y == 1 || y == ymax - 2)))
	    tmp.push_back(EMPTY);
	  else if (rand() % 100 < 50)
	    tmp.push_back(createBonusBloc(opt));
	  else
	    tmp.push_back(EMPTY);
	  x++;
	}
      this->_map.push_back(tmp);
      tmp.clear();
      x = 0;
      y++;
    }
}

void					Map::createMap(const Settings & opt, std::list<char> list_block)
{
  std::vector<Ibloc>			tmp;
  int					xmax = opt.getWidth();
  int					ymax = opt.getHeight();
    int					x = 0;
  int					y = 0;
  std::list<char>::iterator		it;
  char					ca;

  _width = opt.getWidth();
  _height = opt.getHeight();
  while (y < ymax)
    {
      while (x < xmax)
	{
	  if (y == 0 || y == ymax - 1 || x == 0 || x == xmax - 1 || (y % 2 == 0 && x % 2 == 0))
	    tmp.push_back(INDESTRUCTIBLE);
	  else if ((y >= 1 && y <= 2 && (x == 1 || x == xmax - 2)) ||
		   (y >= ymax - 3 && y <= ymax - 2 && (x == 1 || x == xmax - 2)) ||
		   (x >= 1 && x <= 2 && (y == 1 || y == ymax - 2)) ||
		   (x >= xmax - 3 && x <= xmax - 2 && (y == 1 || y == ymax - 2)))
	    tmp.push_back(EMPTY);
	  else if (list_block.size())
	    {
	      it = list_block.begin();
	      ++it;
	      ca = *it;
	      if (ca >= 'a' && ca <= 'e')
	      	tmp.push_back((Ibloc)(ca - 97));
	      if (ca > 'e' && ca <= 'i')
	      	tmp.push_back((Ibloc)(ca - 96));
	    }
	  else
	    tmp.push_back(EMPTY);
	  if (list_block.size())
	    list_block.pop_front();
	  x++;
	}
      this->_map.push_back(tmp);
      tmp.clear();
      x = 0;
      y++;
    }
}

Ibloc					Map::getAt(const double &dx, const double &dy) const
{
  return (_map[dy][dx]);
}

void	Map::draw()
{
  int	x = 0;
  int	y = 0;

  glPushMatrix();
  glTranslatef(-(this->getWidth() * 300.0f), 0, -(this->getHeight() * 300.0f));

  while ((unsigned int)y < this->getHeight())
    {
      while ((unsigned int)x < this->getWidth())
	{
	  if (_map[y][x] == DESTRUCTIBLE ||_map[y][x] == DESTRUCTIBLE_RANGE || _map[y][x] == DESTRUCTIBLE_BOMB || _map[y][x] == DESTRUCTIBLE_SPEED)
	    {
	      this->wall->initialize(x * 600.0f, 0, y * 600.0f);
	      this->wall->draw();
	    }
	  else
	    {
	      switch (_map[y][x])
		{
		case (SPEED):
		  this->speed->initialize(x * 600.0f, 0, y * 600.0f);
		  this->speed->draw();
		  break;
		case (BOMB):
		  this->bomb->initialize(x * 600.0f, 0, y * 600.0f);
		  this->bomb->draw();
		  break;
		case (RANGE):
		  this->range->initialize(x * 600.0f, 0, y * 600.0f);
		  this->range->draw();
		  break;
		case (INDESTRUCTIBLE):
		  this->block->initialize(x * 600.0f, 0, y * 600.0f);
		  this->block->draw();
		  break;
		default:
		  this->ground->initialize(x * 600.0f, 0, y * 600.0f);
		  this->ground->draw();
		  break;
		}
	    }
	  if (_map[y][x] == BOMB || _map[y][x] == RANGE || _map[y][x] == SPEED)
	    {
	      this->ground->initialize(x * 600.0f, 0, y * 600.0f);
	      this->ground->draw();
	    }
	  x++;
	}
      x = 0;
      y++;
    }
  glPopMatrix();
}

void					Map::setAt(const double & dx, const double &dy, Ibloc value)
{
  double	x, y;

  x = dx + 0.5f;
  y = dy + 0.5f;
  _map[y][x] = value;
}
