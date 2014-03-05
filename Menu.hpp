#ifndef __MENU_HPP___
#define __MENU_HPP___

#include "bomberman.hpp"
#include "AObject.hpp"
#include "Vector3f.hpp"
#include "MenuManager.hpp"
#include "Tools.hpp"
#include "FontImage.hpp"
#include "MenuManager.hpp"
#include "Settings.hpp"
#include "Arrow.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

#define ABSCISSE 1890
#define ORDONNEE 1260

class Menu
{
public:
  Menu(void);
  ~Menu(void);
  void		reset_accueil(void);
  void		initialize(void);
  void		initialize(float const &, float const &, float const &);
  int		update(int const & , float const &, float const &);
  int		update(int const & , int const & );
  void		draw(Settings const & opt, int const & mod);
  bool		isNewGame(void) const;
  void		setNewGame(bool const & );
  void		init_map();
  void		loadScore();
  void		saveScore(int);
 
private:
  Vector3f	pos_;
  gdl::Image	tTitle_;
  gdl::Image	tSettings_;
  int		victoryP1;
  int		victoryP2;
  int		victoryIA;
  gdl::Image	tplay;
  gdl::Image	tplayj;
  gdl::Image	tload;
  gdl::Image	tcredit;
  gdl::Image	tsetting;
  gdl::Image	texit;
  gdl::Image	tloadj;
  gdl::Image	tcreditj;
  gdl::Image	tsettingj;
  gdl::Image	texitj;
  gdl::Image	cup_or;
  gdl::Image	cup_argent;
  gdl::Image	cup_bronze;
  gdl::Image	pcredit;
  gdl::Image	pplay;
  gdl::Image	arrow;
  gdl::Image	psetting;
  gdl::Image	pscore;
  FontImage	fontImage_;
  Arrow		mb_;
  bool		oldKey_;
  bool		ng_;
  int		who_;

  void		main_menu(int const & );
  void		settings_menu(int const & );
  void		start_menu(int const & );
  void		initialize_(void);
  void		draw_main_menu(void);
  void		draw_credits(void);
  void		draw_settings(Settings const & opt);
  void		put_arrow();
  void		draw_start_menu(void);
  void		draw_score(void);
  int		get_victoryP1() const;
  int		get_victoryP2() const;
  int		get_victoryIA() const;
  void		draw_cup();
  void		cup_p1_(gdl::Image);
  void		cup_p2_(gdl::Image);
  void		cup_ia_(gdl::Image);
};

#endif
