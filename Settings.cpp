#include "Game.hpp"
#include "Settings.hpp"
#include <string>
#include <iostream>

Settings::Settings(const int & x, const int & y, const unsigned int & nb_player, const unsigned int & nb_ia)
{
  this->setWidth(x);
  this->setHeight(y);
  this->setNbPlayer(nb_player);
  this->setNbIa(nb_ia);
}

Settings::~Settings()
{
}

void		Settings::setWidth(const int & x)
{
  this->_width = x;
  if (_width > _height + 10)
    _height += 1;
  else if (_width < _height - 10)
    _height -= 1;
  if (_width < 7)
    _width = 7;
  if (_height < 7)
    _height = 7;
  setNbIa(getNbIa());
}

int		Settings::getWidth() const
{
  return (this->_width);
}

void		Settings::setHeight(const int & y)
{
  this->_height = y;
    if (_height > _width + 10)
    _width += 1;
  else if (_height < _width - 10)
    _width -= 1;
  if (_height < 7)
    _height = 7;
  if (_width < 7)
    _width = 7;
  setNbIa(getNbIa());
}

int		Settings::getHeight() const
{
  return (this->_height);
}

void		Settings::setNbPlayer(const unsigned int & nb)
{
  this->_nbPlayer = nb;
  if (nb > 2)
    this->_nbPlayer = 2;
  else if (nb < 1)
  this->_nbPlayer = 1;
  setNbIa(getNbIa());
}

unsigned int	Settings::getNbPlayer() const
{
  return (this->_nbPlayer);
}

void		Settings::setNbIa(const int & nb)
{
  int		max;
  int		sizeWidth;
  int		sizeHeight;
  
  if (getWidth() % 2 == 0)
    sizeWidth = 1;
  if (getHeight() % 2 == 0)
    sizeHeight = 1;

  sizeWidth += getWidth() - 2;
  sizeHeight += getHeight() - 2;
  
  
  max = (sizeHeight - (sizeHeight / 2)) * (sizeWidth - (sizeWidth / 2)) - _nbPlayer;
  this->_nbIa = nb;
  if (nb > max)
    this->_nbIa = max;
  if (nb < 0)
    this->_nbIa = 0;
}

unsigned int	Settings::getNbIa() const
{
  return (this->_nbIa);
}
