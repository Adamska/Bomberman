#include "Run.hpp"

Run::Run(gdl::GameClock *clock)
{
  this->_bombSong = false;
  this->_map = new Map();
  this->gameClock_ = clock;
  this->_time = 0;
}

Run::~Run()
{
  delete(_map);
  while (!this->_players.empty())
    {
      delete this->_players.front();
      this->_players.pop_front();
    }
  while (!this->_bombs.empty())
    {
      delete this->_bombs.front();
      this->_bombs.pop_front();
    }
}

void					Run::setSong(Song * mus)
{
  this->_musicBomb = mus;
}

void					Run::manageBomb()
{
  std::list<Bomb*>::iterator		it;

  for (it = _bombs.begin(); _bombs.size() > 0 && it != _bombs.end(); it++)
    {
      if ((*it)->timeOver(gameClock_->getTotalGameTime()) == true)
	{
	  this->_musicBomb->play("bomb");
	  (*it)->explose(this);
	  this->getPlayerById((*it)->getId())->getSkills().delBomb();
	  delete *it;
	  it = _bombs.erase(it);
	}
    }
}

bool					Run::isBombInX_Y(const unsigned int &x, const unsigned int &y)
{
  std::list<Bomb*>::iterator		it = _bombs.begin();

  for (; it != _bombs.end(); it++)
    {
      if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	return true;
    }
  return false;
}

void					Run::setMap(Map* map)
{
  this->_map = map;
}

void					Run::setPlayers(std::list<APlayer*> players)
{
  this->_players = players;
}

Vector2f*				Run::placePlayers(const Settings& opt)
{
  unsigned int				x;
  unsigned int				y;
  bool					findPlace = true;
  std::list<APlayer*>::iterator		it;

  while (findPlace)
    {
      findPlace = false;
      x = 1 + (rand() % (opt.getWidth() - 1));
      y = 1 + (rand() % (opt.getHeight() - 1));
      if (x % 2 == 0)
	(int)x < (opt.getWidth() / 2)? x++: x--;
      if (y % 2 == 0)
	(int)y < (opt.getWidth() / 2)? y++: y--;
      it = this->_players.begin();
      while (it != this->_players.end())
	{
	  if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	    findPlace = true;
	  it++;
	}
    }
  float posX = (float)x + 0.5;
  float posY = (float)y + 0.5;
  Vector2f *ret = new Vector2f(posX, posY);
  return ret;
}

void					Run::createPlayers(const Settings & opt)
{
  unsigned int				id = 0;
  unsigned int				nb = opt.getNbPlayer() + opt.getNbIa();
  unsigned int				nb_tmp = 0;
  Skills				*carac;
  APlayer				*player;

  while (nb_tmp < nb)
    {
      carac = new Skills();
      if (id < opt.getNbPlayer())
	player = new APlayer(id, this->placePlayers(opt), carac, false);
      else
	player = new APlayer(id, placePlayers(opt), carac, true);
      player->initialize();
      this->_players.push_back(player);
      nb_tmp++;
      id++;
    }
}

APlayer*				Run::getPlayerById(const unsigned int& id) const
{
  std::list<APlayer*>::iterator		it;
  std::list<APlayer*>			pl = this->getPlayer();

  for (it = pl.begin(); it != pl.end() && (*it)->getId() != id; it++)
    ;
  if ((*it)->getId() != id)
    return NULL;
  return (*it);
}

Map*					Run::getMap() const
{
  return _map;
}

std::list<APlayer*>			Run::getPlayer() const
{
  return _players;
}

void					Run::isSomeone(unsigned int x, unsigned int y)
{
  std::list<APlayer*>::iterator		it;

  for (it = _players.begin(); it != _players.end(); it++)
    {
      if ((int)(*it)->getX() == (int)x && (int)(*it)->getY() == (int)y)
	(*it)->getSkills().setAlive(false);
    }
}


void					Run::setBombs(std::list<Bomb*> bombs)
{
  this->_bombs = bombs;
}

unsigned int				Run::isBomb(const unsigned int& x, const unsigned int& y, const unsigned int &prevRet)
{
  std::list<Bomb*>::iterator		it;

  for (it = this->_bombs.begin(); it != this->_bombs.end(); it++)
    {
      if ((unsigned int)(*it)->getX() == x && (unsigned int)(*it)->getY() == y)
	return INDESTRUCTIBLE;
    }
  return prevRet;
}

unsigned int				Run::getWidth(void) const
{
  return _map->getWidth();
}

unsigned int				Run::getHeight(void) const
{
  return _map->getHeight();
}

void					Run::pushBomb(Bomb* newBomb)
{
  this->_bombs.push_back(newBomb);
}

std::list<Bomb*>			Run::getBomb() const
{
  return _bombs;
}

gdl::GameClock				*Run::getGameClock() const
{
  return gameClock_;
}

float					Run::getTime(void) const
{
  return this->_time;
}

void					Run::setTime(const float & time)
{
  this->_time = time;
}
