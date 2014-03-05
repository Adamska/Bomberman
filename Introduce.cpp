#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "bomberman.hpp"
#include "MenuManager.hpp"
#include "Bomb.hpp"
#include "Skills.hpp"
#include "Settings.hpp"
#include "Map.hpp"
#include "MyGame.hpp"
#include "Pause.hpp"

Load::Load(const std::string & filename)
{
  this->file.open(filename.c_str(), std::ios::in);
  this->gameclock = 0;
}

Load::~Load()
{
  if (this->file.is_open())
    this->file.close();
}

template<typename T>
T			Load::convertNumber(T & type, const std::string & str)
{
  std::istringstream	ss(str);
  ss >> type;
  return (type);
}

bool			Load::isFileOpen(void) const
{
  if (this->file.is_open())
    return (true);
  return (false);
}

std::string*		Load::recupValue(const std::string & buf, const std::string & id)
{
  int			start;
  int			end;

  if ((start = buf.find("<" + id + ">")) != (int)std::string::npos)
    {
      end = buf.find("</" + id + ">");
      std::string *str = new std::string(buf, (start + 2 + id.length()), end - (start + 2 + id.length()));
      return (str);
    }
  return (NULL);
}

std::vector<Ibloc>	Load::cutExpression(const std::string & strValue, const char & separator)
{
  std::vector<Ibloc>	vecstrResult;
  unsigned int		tmp;
  int			startpos = 0;
  int			endpos = 0;

  endpos = strValue.find_first_of(separator, startpos);
  while (endpos != -1)
    {
      vecstrResult.push_back(static_cast<Ibloc>(convertNumber(tmp, strValue.substr(startpos, endpos-startpos))));
      startpos = endpos+1;
      endpos = strValue.find_first_of(separator, startpos);
      if(endpos == -1)
	vecstrResult.push_back(static_cast<Ibloc>(convertNumber(tmp, strValue.substr(startpos))));
    }
  return vecstrResult;
}

Vector2f*		Load::findPosInStr(const std::string & str)
{
  std::string		strX(str, 0, str.find(";"));
  std::string		strY(str, str.find(";") + 1, str.length() - str.find(";"));
  double		x = 0;
  double		y = 0;

  convertNumber(x, strX);
  convertNumber(y, strY);
  if (x < 0 || y < 0)
    return (NULL);
  return (new Vector2f(x, y));
}

Bomb*			Load::bomb(gdl::GameClock const *currentGC)
{
  std::string		buf;
  std::string		*res = NULL;
  unsigned int		idPlayer;
  unsigned int		range;
  Vector2f		*pos = NULL;
  float			delayMs;
  float			startTimer;

  getline(this->file, buf);
  while (buf.find("</bomb>") == std::string::npos)
    {
      if ((res = this->recupValue(buf, "idPlayer")) != NULL)
        convertNumber(idPlayer, *res);
      else if ((res = this->recupValue(buf, "range")) != NULL)
        convertNumber(range, *res);
      else if ((res = this->recupValue(buf, "timer")) != NULL)
        convertNumber(startTimer, *res);
      else if ((res = this->recupValue(buf, "delay")) != NULL)
        convertNumber(delayMs, *res);
      else if ((res = this->recupValue(buf, "pos")) != NULL)
	pos = findPosInStr(*res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  Bomb* bomb = new Bomb(0, 0, idPlayer, range, currentGC->getTotalGameTime());
  return this->return_bomb(bomb, pos, delayMs, startTimer);
}

Bomb*			Load::return_bomb(Bomb* bomb, Vector2f* pos, float delayMs, float startTimer)
{
  bomb->setVector2f(pos);
  bomb->setDelayExplosion(delayMs - (this->gameclock - startTimer));
  return (bomb);
}

Settings*			Load::option()
{
  std::string		buf;
  std::string		*res = NULL;
  int			xMap;
  int			yMap;
  unsigned int		nbPlayer;
  unsigned int		nbIa;

  getline(this->file, buf);
  while (buf.find("</option>") == std::string::npos)
    {
      if ((res = this->recupValue(buf, "gameclock")) != NULL)
        convertNumber(this->gameclock, *res);
      else if ((res = this->recupValue(buf, "xmap")) != NULL)
        convertNumber(xMap, *res);
      else if ((res = this->recupValue(buf, "ymap")) != NULL)
        convertNumber(yMap, *res);
      else if ((res = this->recupValue(buf, "nbPlayer")) != NULL)
        convertNumber(nbPlayer, *res);
      else if ((res = this->recupValue(buf, "nbIA")) != NULL)
        convertNumber(nbIa, *res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  if (xMap < 0 || yMap < 0 || res == NULL)
    return (NULL);
  return this->return_option(xMap, yMap, nbPlayer, nbIa);
}

Settings*			Load::return_option(int xMap, int yMap, unsigned int nbPlayer, unsigned int nbIa)
{
  Settings* option = new Settings(xMap, yMap, nbPlayer, nbIa);
  return (option);
}

bool			Load::camera(Camera & camera)
{
  std::string		buf;
  std::string		*res = NULL;
  float			posx = -1;
  float			posy = -1;
  float			posz = -1;
  float			posnx = -1;
  float			posny = -1;
  float			posnz = -2;
  float			rotx = -1;
  float			roty = -1;
  float			rotz = -1;

  getline(this->file, buf);
  while (buf.find("</camera>") == std::string::npos)
    {
      if ((res = this->recupValue(buf, "posX")) != NULL)
        convertNumber(posx, *res);
      else if ((res = this->recupValue(buf, "posY")) != NULL)
        convertNumber(posy, *res);
      else if ((res = this->recupValue(buf, "posZ")) != NULL)
        convertNumber(posz, *res);
      else if ((res = this->recupValue(buf, "posnX")) != NULL)
        convertNumber(posnx, *res);
      else if ((res = this->recupValue(buf, "posnY")) != NULL)
        convertNumber(posny, *res);
      else if ((res = this->recupValue(buf, "posnZ")) != NULL)
        convertNumber(posnz, *res);
      else if ((res = this->recupValue(buf, "rotX")) != NULL)
        convertNumber(rotx, *res);
      else if ((res = this->recupValue(buf, "rotY")) != NULL)
        convertNumber(roty, *res);
      else if ((res = this->recupValue(buf, "rotZ")) != NULL)
        convertNumber(rotz, *res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  if (posx == -1 || posy == -1 || posz == -1 ||
      posnx == -1 || posny == -1 || posnz == -2 ||
      rotx == -1 || roty == -1 || rotz == -1)
    return (false);
  Vector3f pos(posx, posy, posz);
  Vector3f posn(posnx, posny, posnz);
  Vector3f rot(rotx, roty, rotz);
  camera.setPos(pos);
  camera.setPosn(posn);
  camera.setRot(rot);
  return (true);
}

Map*		Load::map()
{
  std::vector<std::vector<Ibloc> >	map;
  std::string		*res = NULL;
  std::string		buf;
  unsigned int		xmax;
  unsigned int		ymax;
  int			i = 0;
  bool			isX = false;
  bool			isY = false;

  xmax = 0;
  ymax = 0;
  getline(this->file, buf);
  while (buf.find("</map>") == std::string::npos)
    {
      if ((res = this->recupValue(buf, "xmax")) != NULL)
	{
	  convertNumber(xmax, *res);
	  if (!isX)
	    i++;
	  isX = true;
	}
      else if ((res = this->recupValue(buf, "ymax")) != NULL)
	{
	  convertNumber(ymax, *res);
	  if (!isY)
	    i++;
	  isY = true;
	}
      else if ((res = this->recupValue(buf, "line")) != NULL)
	map.push_back(this->cutExpression(*res, ';'));
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  if (i != 2)
    return NULL;
  return this->create_map(xmax, ymax, map);
}

APlayer*		Load::player()
{
  std::string		buf;
  std::string		*res = NULL;
  std::string		sid = "";
  unsigned int	       	id;
  Vector2f		*pos = NULL;
  unsigned int		dir = 1;
  bool			ia;
  unsigned int		alive;
  unsigned int		speed;
  unsigned int		actualBomb;
  unsigned int		maxBomb;
  unsigned int		range;
  std::string		col;
  unsigned int		r = 0;
  unsigned int		g = 0;
  unsigned int		b = 0;
  unsigned int		a = 255;
  std::list<unsigned int> list_carac;

  getline(this->file, buf);
  while (buf.find("</player>") == std::string::npos)
    {
      if ((res = this->recupValue(buf, "id")) != NULL)
        sid = *res;
      else if ((res = this->recupValue(buf, "colorR")) != NULL)
        convertNumber(r, *res);
      else if ((res = this->recupValue(buf, "colorG")) != NULL)
        convertNumber(g, *res);
      else if ((res = this->recupValue(buf, "colorB")) != NULL)
        convertNumber(b, *res);
      else if ((res = this->recupValue(buf, "colorA")) != NULL)
        convertNumber(a, *res);
      else if ((res = this->recupValue(buf, "pos")) != NULL)
	pos = findPosInStr(*res);
      else if ((res = this->recupValue(buf, "direction")) != NULL)
        convertNumber(dir, *res);
      else if ((res = this->recupValue(buf, "ia")) != NULL)
        convertNumber(ia, *res);
      else if ((res = this->recupValue(buf, "alive")) != NULL)
        convertNumber(alive, *res);
      else if ((res = this->recupValue(buf, "speed")) != NULL)
        convertNumber(speed, *res);
      else if ((res = this->recupValue(buf, "maxBomb")) != NULL)
        convertNumber(maxBomb, *res);
      else if ((res = this->recupValue(buf, "actualBomb")) != NULL)
        convertNumber(actualBomb, *res);
      else if ((res = this->recupValue(buf, "range")) != NULL)
        convertNumber(range, *res);
      getline(this->file, buf);
      if (res != NULL)
	delete res;
    }
  if (pos == NULL || sid == "")
    return (NULL);
  convertNumber(id, sid);
  gdl::Color color(r, g, b, a);
  list_carac = add_list_carac(alive, speed, actualBomb, maxBomb, range);
  return this->create_player(id, pos, list_carac, ia, dir, color);
}
