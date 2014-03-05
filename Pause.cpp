#include "Pause.hpp"
#include "bomberman.hpp"
#include "MenuManager.hpp"
#include "Bomb.hpp"
#include "Skills.hpp"
#include "Map.hpp"

Map*		Load::create_map(unsigned int x, unsigned int y, std::vector<std::vector<Ibloc> > map)
{
  Map*		coremap = new Map();

  coremap->setWidth(x);
  coremap->setHeight(y);
  coremap->setMap(map);
  return (coremap);
}

Skills*					Load::create_carac(std::list<unsigned int> list_carac)
{
  int					i = 0;
  unsigned int				alive = 0;
  unsigned int				speed = 0;
  unsigned int				actualBomb = 0;
  unsigned int				maxBomb = 0;
  unsigned int				range = 0;
  std::list<unsigned int>::iterator	it;
  Skills				*caracteristique = new Skills();

  for (it = list_carac.begin(); it != list_carac.end(); ++it, i++)
    {
      i == 0 ? 	alive = *it :
	i == 1 ? speed = *it :
	i == 2 ? actualBomb = *it :
	i == 3 ? maxBomb = *it :
	i == 4 ? range = *it : i = i;
    }
  caracteristique->setAlive(alive);
  caracteristique->setSpeed(speed);
  caracteristique->setActualBomb(actualBomb);
  caracteristique->setMaxBomb(maxBomb);
  caracteristique->setRange(range);
  return (caracteristique);
}

std::list<unsigned int>		Load::add_list_carac(unsigned int alive, unsigned int speed,
						     unsigned int actualBomb, unsigned int maxBomb, unsigned int range)
{
  std::list<unsigned int>	my_list;
  
  my_list.push_back(alive);
  my_list.push_back(speed);
  my_list.push_back(actualBomb);
  my_list.push_back(maxBomb);
  my_list.push_back(range);
  return (my_list);
}

APlayer*		Load::create_player(unsigned int id, Vector2f *pos, std::list<unsigned int> list_carac,
					    bool ia, unsigned int dir, gdl::Color color)
{
  APlayer		*player = new APlayer(id, pos, this->create_carac(list_carac), ia);
  
  player->initialize();
  player->changeDir(static_cast<Direction>(dir));
  player->getModel().set_default_model_color(color);
  return (player);
}

bool			Load::parse(Run* & core, Settings* & option, Camera & camera)
{
  std::string		buf;
  Map*			map = NULL;
  Settings*		opt = NULL;
  std::list<APlayer*>	players;
  std::list<Bomb*>	bombs;

  while (this->file.good())
    {
      getline(this->file, buf);
      if (buf.find("<map>") != std::string::npos)
	if ((map = this->map()) == NULL)
	  return (false);
      if (buf.find("<camera>") != std::string::npos)
	if (this->camera(camera) == false)
	  return (false);
      if (buf.find("<player>") != std::string::npos)
	{
	  players.push_back(this->player());
	  if (players.back() == NULL)
	    {
	      while (!core->getPlayer().empty())
		{
		  delete core->getPlayer().front();
		  core->getPlayer().pop_front();
		}
	      return (false);
	    }
	}
      if (buf.find("<option>") != std::string::npos)
	if ((opt = this->option()) == NULL)
	  return (false);
      if (buf.find("<bomb>") != std::string::npos)
	bombs.push_back(this->bomb(core->getGameClock()));
    }
  return (this->assign_datas_one(core, option, opt, map) && this->assign_datas_two(core, bombs, players));
}

bool			Load::assign_datas_one(Run* & core, Settings* & option, Settings *opt, Map *map)
{
  if (opt != NULL)
    option = opt;
  else
    return (false);
  if (map != NULL)
    {
      if (core->getMap() != NULL)
        delete core->getMap();
      core->setMap(map);
    }
  else
    return (false);
  return true;
}

bool			Load::assign_datas_two(Run* & core, std::list<Bomb*> bombs, std::list<APlayer*> players)
{
  while (!core->getBomb().empty())
    {
      delete core->getBomb().front();
      core->getBomb().pop_front();
    }
  if (!bombs.empty())
    core->setBombs(bombs);
  while (!core->getPlayer().empty())
    {
      delete core->getPlayer().front();
      core->getPlayer().pop_front();
    }
  if (players.empty())
    return (false);
  else
    core->setPlayers(players);
  return (true);
}
