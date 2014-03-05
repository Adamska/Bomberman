#ifndef __PAUSE_HPP__
#define __PAUSE_HPP__

#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "Run.hpp"
#include "Vector2f.hpp"
#include "Settings.hpp"
#include "MyGame.hpp"

class			Load
{
public:
  Load(const std::string & filename);
  ~Load();
  bool			isFileOpen(void) const;
  bool			parse(Run* & core, Settings* & option, Camera & camera);

private:
  std::ifstream		file;
  float			gameclock;
  float			gametime;
  template<typename T>
  T			convertNumber(T & type, const std::string & str);
  std::string*		recupValue(const std::string & buf, const std::string & id);
  std::vector<Ibloc>	cutExpression(const std::string & strValue, const char & separator);
  Vector2f*		findPosInStr(const std::string & str);
  Map*			map();
  APlayer*		player();
  Settings*		option();
  Bomb*			bomb(gdl::GameClock const *currentGC);
  bool			camera(Camera & camera);
  bool			assign_datas_two(Run* & core, std::list<Bomb*> bombs, std::list<APlayer*> players);
  bool			assign_datas_one(Run* & core, Settings* & option, Settings *opt, Map *map);
  Settings*		return_option(int xMap, int yMap, unsigned int nbPlayer, unsigned int nbIa);
  Bomb*			return_bomb(Bomb* bomb, Vector2f* pos, float delayMs, float startTimer);
  APlayer*		create_player(unsigned int id, Vector2f *pos, std::list<unsigned int> list_carac,
				      bool ia, unsigned int dir, gdl::Color color);
  std::list<unsigned int> add_list_carac(unsigned int life, unsigned int speed,
					 unsigned int actualBomb, unsigned int maxBomb, unsigned int range);
  Skills*		create_carac(std::list<unsigned int> list_carac);
  Map*			create_map(unsigned int x, unsigned int y, std::vector<std::vector<Ibloc> > map);
};

#endif
