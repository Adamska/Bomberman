#include <iostream>
#include "Skills.hpp"

Skills::Skills()
{
  this->_alive = 1;
  this->_speed = 2;
  this->_actualBomb = 0;
  this->_maxBomb = 1;
  this->_range = 0;
}

const unsigned int&				Skills::getAlive() const
{
  return this->_alive;
}

const unsigned int&				Skills::getSpeed() const
{
  return this->_speed;
}

const unsigned int&				Skills::getMaxBomb(void) const
{
  return this->_maxBomb;
}

const unsigned int&				Skills::getActualBomb(void) const
{
  return this->_actualBomb;
}

const unsigned int&				Skills::getRange(void) const
{
  return this->_range;
}

void						Skills::setAlive(const unsigned int& alive)
{
  this->_alive = alive;
}

void						Skills::setSpeed(const unsigned int& speed)
{
  this->_speed = speed;
}

void						Skills::setRange(const unsigned int& range)
{
  this->_range = range;
}

void						Skills::setActualBomb(const unsigned int& bomb)
{
  this->_actualBomb = bomb;
}

void						Skills::setMaxBomb(const unsigned int& maxBomb)
{
  this->_maxBomb = maxBomb;
}

bool						Skills::putBomb(void)
{
  if (this->_actualBomb < _maxBomb)
    {
      _actualBomb++;
      return (true);
    }
  return (false);
}

void						Skills::delBomb(void)
{
  this->_actualBomb--;
}

void						Skills::increaseSpeed(const unsigned int& speed)
{
  if (this->_speed < 6)
    this->_speed += speed;
}

void						Skills::increaseRange(const unsigned int& range)
{
  this->_range += range;
}

void						Skills::increaseBomb(const unsigned int& maxbomb)
{
  this->_maxBomb += maxbomb;
}
