#include <sstream>
#include <fstream>
#include <iostream>
#include "bomberman.hpp"
#include "MenuManager.hpp"
#include "MyGame.hpp"
#include "Menu.hpp"
#include "FontImage.hpp"
#include "Song.hpp"
#include "FileContent.hpp"

void				MyGame::reset_menu_()
{
  this->posMenu_.state = MENU;
  this->posMenu_.choice = CHOICE_1;
  this->posMenu_.menu = MAIN_MENU;
  this->camera_.reset_cam(0, 0, 0);
}

void				MyGame::initialize_menu_()
{
  this->fontImage_ = new FontImage;
  this->menu_.initialize();
  this->menu_.loadScore();
  this->reset_menu_();
  std::vector<func> main;
  std::vector<func> start;
  std::vector<func> settings;
  std::vector<func> credits;
  std::vector<func> score;

  /* Main Menu Function Pointers vector*/
  main.push_back(&MyGame::Start_Menu_Choice_Play);
  main.push_back(&MyGame::Start_Menu_Choice_Load);
  main.push_back(&MyGame::Start_Menu_Choice_Credits);
  main.push_back(&MyGame::Start_Menu_Choice_Settings);
  main.push_back(&MyGame::Start_Menu_Choice_Exit);

  /* Start Menu Function Pointers vector */
  start.push_back(&MyGame::Play_Menu_Choice_Standard);
  start.push_back(&MyGame::Play_Menu_Choice_Random);
  start.push_back(&MyGame::Play_Menu_Choice_Scores);
  start.push_back(&MyGame::Return_Main_Menu);

  /* Settings Menu Function Pointers vector */
  settings.push_back(&MyGame::Settings_Menu_Choice_Map_Width);
  settings.push_back(&MyGame::Settings_Menu_Choice_Map_Height);
  settings.push_back(&MyGame::Settings_Menu_Choice_Humans);
  settings.push_back(&MyGame::Settings_Menu_Choice_AI);
  settings.push_back(&MyGame::Return_Main_Menu);

  /* Credits Menu Function Pointers vector */
  credits.push_back(&MyGame::Return_Main_Menu);

  /* Score Menu Function Pointeurs vector */
  score.push_back(&MyGame::Return_Start_Menu);

  /* All Menus vectors of vectors of Function Pointers */ 
  ptrfunc.push_back(main);
  ptrfunc.push_back(start);
  ptrfunc.push_back(settings);
  ptrfunc.push_back(score);
  ptrfunc.push_back(credits);
}

/* MAIN MENU */

void					MyGame::Start_Menu_Choice_Play(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = START_MENU;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 1200, 2.4);
    }
}

void					MyGame::Start_Menu_Choice_Load(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      if (load_game() == true)
	{
	  song_->play("game");
	  this->camera_.reset_cam(this->settings_->getWidth(), this->settings_->getHeight(), 1);
	  this->posMenu_.state = GAME;
	  this->menu_.setNewGame(false);
	}
    }
}

void					MyGame::Start_Menu_Choice_Credits(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = CREDITS;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 1200, 2.2);
    }
}

void					MyGame::Start_Menu_Choice_Settings(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = SETTINGS;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 320, 2.6);
    }
}

void					MyGame::Start_Menu_Choice_Exit(void)
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      save_game();
      this->window_.close();
    }
}
/*END MAIN MENU*/


/*START MENU */

void					MyGame::Play_Menu_Choice_Standard()
{
  int					val = 0;
  std::list<int>			value_opt;
  int					_width;
  int					_height;
  int					_nbPlayer;
  unsigned int				_nbIa;
  FileContent				getDatas;
  std::list<int>::iterator		it;

  _nbPlayer = 0;
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      getDatas.my_read_datas();
      if (!getDatas.is_valid_datas())
	this->fontImage_->setContent("Wrong datas");
      else
	{
	  getDatas.my_read_map();
	  if (!getDatas.is_valid_datas())
	    this->fontImage_->setContent("Cannot load files");
	  else
	    {
	      value_opt = getDatas.getList();
	      for (it = value_opt.begin(); it != value_opt.end(); ++it)
		{
		  val == 0 ? _width = *it :
		    val == 1 ? _height = *it :
		    val == 2 ? _nbPlayer = *it :
		    val == 3 ? _nbIa = *it : val = val;
		  val++;
		}
	      delete settings_;
	      settings_ = new Settings(_width, _height, _nbPlayer, _nbIa);
	      song_->play("game");
	      victory_->startSong();
	      this->camera_.reset_cam(this->settings_->getWidth(), this->settings_->getHeight(), 1);
	      delete(this->run_);
	      this->new_game(getDatas.getListStone());
	      this->posMenu_.state = GAME;
	      this->menu_.setNewGame(false);
	    }
	}
    }
}

void					MyGame::Play_Menu_Choice_Random()
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      song_->play("game");
      victory_->startSong();
      this->camera_.reset_cam(this->settings_->getWidth(), this->settings_->getHeight(), 1);
      delete(this->run_);
      this->new_game();
      this->posMenu_.state = GAME;
      this->menu_.setNewGame(false);
    }
}

void					MyGame::Play_Menu_Choice_Scores()
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = SCORES;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 1200, 2.2);
    }
}

void					MyGame::Return_Main_Menu()
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = MAIN_MENU;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 1200, 2.2);
    }
}

/* END START MENU */

/* SETTINGS MENU */

void					MyGame::Settings_Menu_Choice_Map_Width()
{
  if (input_.isKeyDown(gdl::Keys::Right) == true && this->oldKey_ == false)
    this->settings_->setWidth(this->settings_->getWidth() + 1);
  if (input_.isKeyDown(gdl::Keys::Left) == true && this->oldKey_ == false)
    this->settings_->setWidth(this->settings_->getWidth() - 1);
}

void					MyGame::Settings_Menu_Choice_Map_Height()
{
  if (input_.isKeyDown(gdl::Keys::Right) == true && this->oldKey_ == false)
    this->settings_->setHeight(this->settings_->getHeight() + 1);
  if (input_.isKeyDown(gdl::Keys::Left) == true && this->oldKey_ == false)
    this->settings_->setHeight(this->settings_->getHeight() - 1);
}

void					MyGame::Settings_Menu_Choice_Humans()
{
  if (input_.isKeyDown(gdl::Keys::Right) == true && this->oldKey_ == false)
    this->settings_->setNbPlayer(this->settings_->getNbPlayer() + 1);
  if (input_.isKeyDown(gdl::Keys::Left) == true && this->oldKey_ == false)
    this->settings_->setNbPlayer(this->settings_->getNbPlayer() - 1);
}

void					MyGame::Settings_Menu_Choice_AI()
{
  if (input_.isKeyDown(gdl::Keys::Right) == true && this->oldKey_ == false)
    this->settings_->setNbIa(this->settings_->getNbIa() + 1);
  if (input_.isKeyDown(gdl::Keys::Left) == true && this->oldKey_ == false)
    this->settings_->setNbIa(this->settings_->getNbIa() - 1);
}

/* END SETTINGS MENU */

/* SCORE MENU */
void					MyGame::Return_Start_Menu()
{
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false)
    {
      this->posMenu_.menu = START_MENU;
      this->posMenu_.choice = CHOICE_1;
      this->menu_.update(this->posMenu_.choice, 1200, 2.4);
    }
}
/* END SCORE MENU */

void					MyGame::update_menu_(void)
{
  if (input_.isKeyDown(gdl::Keys::Up) == true && this->oldKey_ == false)
    {
      song_->play("menu");
      this->menu_.update(KEY_UP, this->posMenu_.menu);
      this->fontImage_->setPopup(false);
    }
 if (input_.isKeyDown(gdl::Keys::Down) == true && this->oldKey_ == false)
    {
      song_->play("menu");
      this->menu_.update(KEY_DOWN, this->posMenu_.menu);
      this->fontImage_->setPopup(false);
    }

 (this->*ptrfunc[this->posMenu_.menu - 1][this->menu_.update(0, this->posMenu_.menu) - 1])();

 this->posMenu_.choice = this->menu_.update(0, this->posMenu_.menu);

  this->oldKey_ = input_.isKeyDown(gdl::Keys::Up) | input_.isKeyDown(gdl::Keys::Down)
    | input_.isKeyDown(gdl::Keys::Left) | input_.isKeyDown(gdl::Keys::Right)
    | input_.isKeyDown(gdl::Keys::Return) | input_.isKeyDown(gdl::Keys::Escape);

  camera_.update(gameClock_, input_);
}

void					MyGame::draw_menu_(void)
{
  this->fontImage_->displaySentence();
  this->menu_.draw(*(this->settings_), this->posMenu_.menu);
}

