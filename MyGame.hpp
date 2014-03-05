#ifndef __MYGAME_HPP__
#define __MYGAME_HPP__


#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include "bomberman.hpp"
#include "Camera.hpp"
#include "AObject.hpp"
#include "MenuManager.hpp"
#include "Menu.hpp"
#include "Pattern.hpp"
#include "Song.hpp"
#include "Bonus.hpp"
#include "Run.hpp"
#include "Victory.hpp"

#define MENU	0
#define GAME	1
#define LOAD	2
#define PAUSED  3

class Bomb;
class Run;

typedef void (MyGame::*func)();

class MyGame : public gdl::Game
{
private:
  unsigned int				oldId_;
  bool					oldKey_;
  bool					inGame_;
  Run					*run_;
  Song					*song_;
  Settings				*settings_;
  Victory				*victory_;
  FontImage				*fontImage_;
  Camera				camera_;
  MenuManager				posMenu_;
  Stone					*block;
  Box					*wall;
  Floor					*ground;
  Explosion				*explosion;
  BombSup				*bomb;
  Speed					*speed;
  Range					*range;
  gdl::Image				pause_;
  Menu					menu_;
  std::vector<std::vector<func> >	ptrfunc;
  int					id_win;

  void					reset_menu_(void);

  void					initialize_menu_(void);
  void					initialize_game_(void);

  void					Start_Menu_Choice_Play();
  void					Start_Menu_Choice_Load();
  void					Start_Menu_Choice_Credits();
  void					Start_Menu_Choice_Settings();
  void					Start_Menu_Choice_Exit();

  void					Play_Menu_Choice_Standard();
  void					Play_Menu_Choice_Random();
  void					Play_Menu_Choice_Scores();
  void					Return_Main_Menu();

  void					Settings_Menu_Choice_Map_Width();
  void					Settings_Menu_Choice_Map_Height();
  void					Settings_Menu_Choice_Map_Density_Bloc();
  void					Settings_Menu_Choice_Map_Density_Bonus();
  void					Settings_Menu_Choice_Humans();
  void					Settings_Menu_Choice_AI();

  void					Return_Start_Menu();

  void					update_menu_(void);
  void					update_game_(void);
  void					pause_game();
  void					draw_pause();
  void					draw_menu_(void);
  void					draw_game_(void);
  void					AI_Controls(APlayer*, MyGame*, gdl::Input&);
  void					checkBonus(APlayer* player);
  void					P1_controls(gdl::Input &);
  void					P2_controls(gdl::Input &);
  void					select_map(unsigned int map);
  Victory*				getVictory() const;
  bool					isVictory(void);

  void					save_game(void);
  bool					load_game(void);

public:
  void					new_game();
  void					new_game(std::list<char> list_block);
  void					initialize_all_();
  Run&					getRun(void) const;
  void					initialize(void);
  void					update(void);
  void					draw(void);
  unsigned int				getOldId(void);
  void					unload(void);
  unsigned int				isWalkable(const APlayer*, Direction);
  unsigned int				isWalkable(const double xp, const double yp, Direction dir, double speed);
};

#endif
