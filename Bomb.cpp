#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include "Bomb.hpp"
#include "Song.hpp"
#include "Victory.hpp"

Bomb::Bomb(const double& x, const double& y, const unsigned int & id,
	   const unsigned int & range, const float& startTimer)
{
  this->_pos = new Vector2f(x, y);
  this->_id = id;
  this->_range = range;
  this->_TimePosed = startTimer;
  this->_delayExplosion = 3;
  this->_model = gdl::Model::load("assets/bomb.fbx");
  this->_rot.setPos(x * 600.0f, 40.0, y * 600.0f);
}

Bomb::Bomb(APlayer* player, const float& startTimer)
{
  this->_pos = new Vector2f((int)player->getX() + 0.5, (int)player->getY() + 0.5);
  this->_id = player->getId();
  this->_range = player->getSkills().getRange() + 1;
  this->_TimePosed = startTimer;
  this->_delayExplosion = 3;
  this->_model = gdl::Model::load("assets/bomb.fbx");
  this->_rot.setPos(player->getX() * 600.0f, 40.0, player->getY() * 600.0f);
}

Bomb::~Bomb()
{
  delete this->_pos;
}

bool					Bomb::timeOver(const float& time) const 
{
  if (_TimePosed + _delayExplosion < time)
    return (true);
  return (false);
}

Vector2f&				Bomb::getVector2f(void) const
{
  return (*this->_pos);
}

double&					Bomb::getX(void) const
{
  return (this->_pos->_x);
}

double&					Bomb::getY(void) const
{
  return (this->_pos->_y);
}

const float&				Bomb::getTimePosed(void) const
{
  return (this->_TimePosed);
}

const float&				Bomb::getDelayExplosion(void) const
{
  return (this->_delayExplosion);
}

const unsigned int&			Bomb::getId(void) const
{
  return (this->_id);
}

const unsigned int&			Bomb::getRange(void) const
{
  return (this->_range);
}

void					Bomb::setDelayExplosion(const float &d)
{
  this->_delayExplosion = d;
}

void					Bomb::setTimePosed(const float & timer)
{
  this->_TimePosed = timer;
}

void					Bomb::setVector2f(Vector2f*& pos)
{
  this->_pos = pos;
}

void					Bomb::setX(const double& x)
{
  this->_pos->_x = x;
}

void					Bomb::setY(const double& y)
{
  this->_pos->_y = y;
}

void					Bomb::setId(const unsigned int& id)
{
  this->_id = id;

}

void					Bomb::setRange(const unsigned int& r)
{
  this->_range = r;
}

int					Bomb::eachCase(int const & x, int const & y, Run * game)
{
  Ibloc					bloc;
  Ibloc					nbloc;
  std::list<Bomb*>::iterator		it;
  std::list<Bomb*>			cp = game->getBomb();
  
  game->isSomeone(x, y);
  bloc = game->getMap()->getAt(x, y);
  if (bloc != EMPTY)
    {
      if (bloc == DESTRUCTIBLE || bloc == DESTRUCTIBLE_BOMB || bloc == DESTRUCTIBLE_RANGE || bloc == DESTRUCTIBLE_SPEED)
	{
	  bloc == DESTRUCTIBLE_BOMB ? nbloc = BOMB :
	    bloc == DESTRUCTIBLE_SPEED ? nbloc = SPEED :
	    bloc == DESTRUCTIBLE_RANGE ? nbloc = RANGE :
	    nbloc = EMPTY;
	  game->getMap()->setAt(x, y, nbloc);
	}
      else if (bloc == BOMB || bloc == SPEED || bloc == RANGE)
	game->getMap()->setAt(x, y, EMPTY);
      return 0;
    }
  return 1;
}

void					Bomb::explose(Run * game)
{
  std::vector<std::vector<Ibloc> >	gmap;
  unsigned int				x;
  unsigned int				y;
  unsigned int				size_explose = this->_range;

  gmap = game->getMap()->getMap();
  y = this->_pos->_y;
  for (x = this->_pos->_x; x <= this->_pos->_x + size_explose && x <= game->getWidth(); x++)
    if (eachCase(x, y, game) == 0)
      break;
  for (x = this->_pos->_x - 1; x >= this->_pos->_x - size_explose - 1; x--)
    if (eachCase(x, y, game) == 0)
      break;
  x = this->_pos->_x;
  for (y = this->_pos->_y + 1; y <= this->_pos->_y + size_explose && y <= game->getHeight(); y++)
    if (eachCase(x, y, game) == 0)
      break;
  for (y = this->_pos->_y - 1; y >= this->_pos->_y - size_explose - 1; y--)
    if (eachCase(x, y, game) == 0)
      break;
  
}

bool					Bomb::game_over(int x, int y, int t1, int t2, int t3,
						      Ibloc bloc, const Map* map)
{
  bloc = map->getAt(x, y);
  glTranslatef(t1, t2, t3);
  _Explosion.draw();
  if (bloc != EMPTY)
    return (true);
  return (false);
}

void					Bomb::draw_explosion(const Map* map)
{
  Ibloc					bloc;
  int					x = 0;
  int					y = 0;

  this->_Explosion.initialize();
  _Explosion.initialize(this->getX() , -230, this->getY());
  _Explosion.draw();
  y = this->_pos->_y;
  glPushMatrix();
  for (x = this->_pos->_x + 1; x <= this->_pos->_x + this->_range && (unsigned int)x <= map->getWidth(); x++)
    if (this->game_over(x, y, 600.0f, 0, 0, bloc, map))
      break;
  glPopMatrix();
  glPushMatrix();
  for (x = this->_pos->_x - 1; x >= this->_pos->_x - this->_range - 1 && x >= 0; x--)
    if (this->game_over(x, y, -600.0f, 0, 0, bloc, map))
      break;
  glPopMatrix();
  x = this->_pos->_x;
  glPushMatrix();
  for (y = this->_pos->_y + 1; y <= this->_pos->_y + this->_range && (unsigned int)y <= map->getHeight(); y++)
    if (this->game_over(x, y, 0, 0, 600.0f, bloc, map))
      break;
  glPopMatrix();
  glPushMatrix();
  for (y = this->_pos->_y - 1; y >= this->_pos->_y - this->_range - 1 && y >= 0; y--)
    if (this->game_over(x, y, 0, 0, -600.0f, bloc, map))
      break;
  glPopMatrix();
} 

void					Bomb::draw(const Map* map, const float& time)
{
  glPushMatrix();
  glTranslatef(-((double)map->getWidth() / 2) * 600.0f, 0 , -((double)map->getHeight() /2) * 600.0f);
  glTranslatef(this->getX() * 600.0f, -230, this->getY() * 600.0f);
  glTranslatef(-0.5 * 600.0f, 0, -0.5 * 600.0f);
  this->_model.draw();
  if (_TimePosed + _delayExplosion - 0.3f < time)
    this->draw_explosion(map);
  glPopMatrix();
}
