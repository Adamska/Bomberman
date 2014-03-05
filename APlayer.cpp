#include <unistd.h>
#include <iostream>
#include "Song.hpp"
#include "APlayer.hpp"
#include "Run.hpp"

APlayer::APlayer(const unsigned int& id, const double& posx, const double& posy, Skills* carac, bool ia)
{
  this->_id = id;
  this->_pos = new Vector2f(posx, posy);
  this->_carac = carac;
  this->_ia = ia;
  this->_dir = UP;
  this->_endPath = new Vector2f(posx, posy);
  this->_beginPath = new Vector2f(posx, posy);
}

APlayer::APlayer(const unsigned int& id, Vector2f* pos, Skills* carac, bool ia)
{
  this->_id = id;
  this->_pos = pos;
  this->_carac = carac;
  this->_dir = UP;
  this->_ia = ia;
  this->_endPath = new Vector2f(getX(), getY());
  this->_beginPath = new Vector2f(getX(), getY());

}

std::list<Direction>	APlayer::getPath(void) const
{
  return _path;
}

Vector2f*		APlayer::getEndPath(void) const
{
  return _endPath;
}

void			APlayer::setEndPath(Vector2f* endPath)
{
  this->_endPath = endPath;
}

Vector2f*		APlayer::getBeginPath(void) const
{
  return _beginPath;
}

void			APlayer::setBeginPath(Vector2f* beginPath)
{
  this->_beginPath = beginPath;
}

void			APlayer::setPath(std::list<Direction> path)
{
  this->_path = path;
}


void			APlayer::init_rand(int *a, int *b, int *c, int *d)
{
  *a = rand() % 250;
  *b = rand() % 250;
  *c = rand() % 250;
  *d = rand() % 250;
}

void			APlayer::initialize(void)
{
  int			j;
  int			k;
  int			n;
  int			i;

  this->init_rand(&j, &k, &n, &i);
  _dir = DOWN; 
  this->_model = gdl::Model::load("assets/marvin.fbx");
  gdl::Color random(i,n,j,k);
  this->_model.set_default_model_color(random);
  this->_pos3f.setPos(1.5 * 600.0f, -280.0, 1.5 * 600.0f);
  this->_rot.setPos(0, 0, 0);
  this->_model.cut_animation(_model,"Take 001", 55, 65,"new_anim");
}

void			APlayer::initialize(float x, float y, float z)
{
  this->_model = gdl::Model::load("assets/marvin.fbx");
  this->_pos3f.setPos(x, y, z);
  this->_rot.setPos(0, 0, 0);
}

Vector2f&		APlayer::getVector2f(void) const
{
  return (*_pos);
}

Skills&			APlayer::getSkills(void) const
{
  return (*_carac);
}

Direction		APlayer::getDirection(void) const
{
  return (this->_dir);
}

gdl::Model		APlayer::getModel(void) const
{
  return (this->_model);
}

unsigned int		APlayer::getId(void) const
{
  return (this->_id);
}

double			APlayer::getX(void) const
{
  return (this->_pos->_x);
}

double			APlayer::getY(void) const
{
  return (this->_pos->_y);
}

bool      APlayer::isIA() const
{
  return (this->_ia);
}

void			APlayer::setVector2f(Vector2f*& pos)
{
  this->_pos = pos;
}

void			APlayer::setVector2f(const double& x, const double& y)
{
  this->_pos = new Vector2f(x, y);
}

void			APlayer::setSkills(Skills*& carac)
{
  this->_carac = carac;
}

void			APlayer::setDirection(const Direction& dir)
{
  this->_dir = dir;
}

void			APlayer::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  Direction		dir;

  (void)(input);
  this->_model.update(gameClock);
  dir = this->getDirection();
  this->changeDir(dir);
  if (dir == RIGHT)
    this->setVector2f(this->getX() + 0.03f * this->getSkills().getSpeed(), this->getY());
  else if (dir == LEFT)
    this->setVector2f(this->getX() - 0.03f * this->getSkills().getSpeed(), this->getY());
  else if (dir == DOWN)
    this->setVector2f(this->getX(), this->getY() + 0.03f * this->getSkills().getSpeed());
  else 
    this->setVector2f(this->getX(), this->getY() - 0.03f * this->getSkills().getSpeed());
  this->_model.play("new_anim");
}

void			APlayer::changeDir(Direction n)
{
  if (this->_dir + 2 == n || this->_dir - 2 == n)
    this->_rot.y = ((int)_rot.y + 180) % 360;
  else if (this->_dir + 1 == n || this->_dir - 3 == n)
    this->_rot.y = ((int)_rot.y + 90) % 360;
  else if (this->_dir - 1 == n || this->_dir + 3 == n)
    this->_rot.y = ((int)_rot.y - 90) % 360;
  this->_dir = (Direction)n;
}

void			APlayer::draw(const Map* map)
{
  glPushMatrix();
  glTranslatef(-((double)map->getWidth() / 2) * 600.0f, 0 , -((double)map->getHeight() /2) * 600.0f);
  glTranslatef((this->getX()) * 600.0f, -280.0, (this->getY()) * 600.0f);
  glTranslatef(-0.5 * 600.0f, 0, -0.5 * 600.0f);
  glRotatef(this->_rot.getY(), 0.0f, 1.0f, 0.0f);
  this->_model.draw();
  glPopMatrix();
}

void			APlayer::addBonus(const unsigned int& bonus)
{
  switch (bonus)
    {
    case BOMB :
      this->getSkills().increaseBomb(1);
      break;
    case SPEED :
      this->getSkills().increaseSpeed(1);
      break;
    case RANGE :
      this->getSkills().increaseRange(1);
      break;
    }
}
