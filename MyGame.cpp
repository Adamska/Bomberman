#include <unistd.h>
#include "APlayer.hpp"
#include "MyGame.hpp"
#include "Pattern.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "Bomb.hpp"
#include "Pause.hpp"

void					MyGame::new_game()
{
  this->run_ = new Run(&gameClock_);
  this->run_->getMap()->setStone(this->block);
  this->run_->getMap()->setBox(this->wall);
  this->run_->getMap()->setFloor(this->ground);
  this->run_->getMap()->setExplosion(this->explosion);
  this->run_->getMap()->setBombSup(this->bomb);
  this->run_->getMap()->setSpeed(this->speed);
  this->run_->getMap()->setRange(this->range);
  this->run_->setSong(this->song_);
  if (settings_->getHeight() % 2 == 0)
    settings_->setHeight(settings_->getHeight() + 1);
  if (settings_->getWidth() % 2 == 0)  
    settings_->setWidth(settings_->getWidth() + 1);
  this->getRun().createPlayers(*(this->settings_));
  this->getRun().getMap()->createMap(*(this->settings_));
  this->getRun().getMap()->removeBlocAroundPlayers(this->getRun().getPlayer());
  this->run_->setTime(0);
}

void					MyGame::new_game(std::list<char> list_block)
{
  this->run_ = new Run(&gameClock_);
  this->run_->getMap()->setStone(this->block);
  this->run_->getMap()->setBox(this->wall);
  this->run_->getMap()->setFloor(this->ground);
  this->run_->getMap()->setExplosion(this->explosion);
  this->run_->getMap()->setBombSup(this->bomb);
  this->run_->getMap()->setSpeed(this->speed);
  this->run_->getMap()->setRange(this->range);
  this->run_->setSong(this->song_);
  if (settings_->getHeight() % 2 == 0)
    settings_->setHeight(settings_->getHeight() + 1);
  if (settings_->getWidth() % 2 == 0)  
    settings_->setWidth(settings_->getWidth() + 1);
  this->getRun().createPlayers(*(this->settings_));
  this->getRun().getMap()->createMap(*(this->settings_), list_block);
  this->getRun().getMap()->removeBlocAroundPlayers(this->getRun().getPlayer());
  this->run_->setTime(0);
}

void					MyGame::initialize_game_(void)
{
  song_ = new Song();
  this->settings_ = new Settings(9, 9, 1, 1);
  this->block = new Stone;
  this->wall = new Box;
  this->ground = new Floor;
  this->explosion = new Explosion;
  this->bomb = new BombSup;
  this->speed = new Speed;
  this->range = new Range;
  pause_ = gdl::Image::load("Textures/Pause.png");
}

void					MyGame::initialize(void)
{
  window_.setTitle("Bomberman");
  window_.setWidth(1200.0f);
  window_.setHeight(800.0f);
  window_.create();
  camera_.initialize(0);
}

void					MyGame::initialize_all_(void)
{
  this->initialize_menu_();
  this->initialize_game_();
  this->oldKey_ = false;
  this->run_ = NULL;
  this->new_game();
  this->victory_ = new Victory();
  this->victory_->initialize();
  this->posMenu_.state = MENU;
  this->inGame_ = true;
}


void					MyGame::AI_Controls(APlayer *p, MyGame *mygame, gdl::Input &input_)
{
  Ia					*ia = new Ia(mygame, p);

  ia->go(input_, gameClock_);
  delete ia;
}

void					MyGame::update_game_(void)
{
  APlayer				*pl;
  std::list<APlayer*>::iterator		it;

  if (input_.isKeyDown(gdl::Keys::P) == true && this->oldKey_ == false && inGame_ == true)
    {
      this->posMenu_.state = PAUSED;
      this->song_->pause();
      save_game();
    }
  if (input_.isKeyDown(gdl::Keys::Return) == true && this->oldKey_ == false && inGame_ == false)
    {
      victory_->endSong();
      this->reset_menu_();
      this->menu_.saveScore(this->id_win);
    }
  camera_.getKeys(gameClock_, input_);
  if (inGame_ == true)
    {
      std::list<APlayer*> plist = this->getRun().getPlayer();
      for (it = plist.begin(); it != plist.end(); it++)
	{
	  if ((*it)->getSkills().getAlive() == true && (*it)->isIA() == true)
	    {
	      this->AI_Controls(*it, this, input_);
	      this->checkBonus(*it);
	    }
	}
      if ((pl = this->getRun().getPlayerById(0)) != NULL && pl->isIA() == false && pl->getSkills().getAlive() == true)
	P1_controls(input_);
      if ((pl = this->getRun().getPlayerById(1)) != NULL && pl->isIA() == false&& pl->getSkills().getAlive()  == true)
	P2_controls(input_);
      this->getRun().manageBomb();
    }
  this->oldKey_ = input_.isKeyDown(gdl::Keys::P);
}

void					MyGame::pause_game()
{
  load_game();
  if (input_.isKeyDown(gdl::Keys::U) == true)
    {
      this->song_->ResumeGame();
      this->posMenu_.state = GAME;
    }
  else if (input_.isMouseButtonDown(gdl::Mouse::Left) == true)
    this->reset_menu_();
}

void					MyGame::update(void)
{
  switch (this->posMenu_.state)
    {
    case MENU:
      this->update_menu_();
      break;
    case GAME:
      this->update_game_();
      break;
    case LOAD:
      this->initialize_all_();
      break;
    case PAUSED:
      this->pause_game();
      break;
    }
  if (input_.isKeyDown(gdl::Keys::Escape) == true)
    {
      save_game();
      this->window_.close();
    }
  usleep(19000);
  this->camera_.update(gameClock_, input_);
}

bool					MyGame::isVictory()
{
  std::list<APlayer*>::iterator		it;
  std::list<APlayer*>			_pl;
  unsigned int				nb_alive = 0;
  unsigned int				id = 2;
  unsigned int				nb_ia = 0;
  unsigned int				nb_pl = 0;

  _pl = this->getRun().getPlayer();
  for (it = _pl.begin(); it != _pl.end(); it++)
    {
      if ((*it)->getSkills().getAlive() == true)
	{
	  nb_alive++;
	  (*it)->isIA() == true ? (id = 2) : (id = (*it)->getId());
	  (*it)->isIA() == true ? (nb_ia++) : (nb_pl++);
	}
      if (nb_alive > 1 && nb_pl != 0)
	return(true);
    }
  this->song_->stop();
  this->getVictory()->draw((Winner)id);
  this->id_win = id; 
  return(false);
}

void					MyGame::draw_game_(void)
{
  std::list<Bomb*>			bomb;
  std::list<APlayer*>			pl;
  std::list<Bomb*>::iterator		itb;
  std::list<APlayer*>::iterator		itp;

  pl = this->getRun().getPlayer();
  this->getRun().getMap()->draw();
  for (itp = pl.begin(); itp != pl.end(); itp++)
    if ((*itp)->getSkills().getAlive() == true)
      (*itp)->draw(this->getRun().getMap());
  bomb = this->getRun().getBomb();
  for (itb = bomb.begin(); itb != bomb.end(); itb++)
    (*itb)->draw(this->getRun().getMap(), gameClock_.getTotalGameTime());
  inGame_ = isVictory();
}

void					MyGame::draw_pause()
{
  pause_.bind();
  glPushMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 0); glVertex3f(-2000, 3500, -0);
  glTexCoord2d(0, 1); glVertex3f(-2000, 3500, 2000);
  glTexCoord2d(1, 1); glVertex3f(2000, 3500, 2000);
  glTexCoord2d(1, 0); glVertex3f(2000, 3500, -0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();
}

void					MyGame::draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.8f ,1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);

  switch (this->posMenu_.state)
    {
    case MENU:
      song_->stop();
      this->draw_menu_();
      break;
    case GAME :
      this->draw_game_();
      break;
    case PAUSED :
      this->draw_game_();
      this->draw_pause();
      break;
    default:
      this->posMenu_.state = LOAD;
      break;
    }
  this->window_.display();
}

void					MyGame::unload(void)
{
  song_->stop();
  delete run_;
  delete block;
  delete wall;
  delete ground;
  delete explosion;
  delete bomb;
  delete speed;
  delete range;
  delete victory_;
  delete fontImage_;
  delete song_;
  delete settings_;
}

unsigned int				MyGame::getOldId(void)
{
  return (this->oldId_);
}

Run&					MyGame::getRun(void) const
{
  return (*run_);
}

unsigned int				MyGame::isWalkable(const APlayer* player, Direction dir)
{
  unsigned int				ret;

  double				x = player->getX();
  double				y = player->getY();

  switch (dir)
    {
    case RIGHT :
      x = player->getX() + 0.2 + 0.03f * player->getSkills().getSpeed();
      break;
    case LEFT :
      x = player->getX() - 0.2 - 0.03f * player->getSkills().getSpeed();
      break;
    case UP :
      y = player->getY() - 0.2 - 0.03f * player->getSkills().getSpeed();
      break;
    case DOWN :
      y = player->getY() + 0.2 + 0.03f * player->getSkills().getSpeed();
      break;
    }
  if ((int)player->getX() == (int)x && (int)player->getY() == (int)y)
    ret = EMPTY;
  else
    {
      ret = this->getRun().getMap()->getAt(x, y);
      ret = this->getRun().isBomb(x, y, ret);
    }
  return (ret);
}

unsigned int				MyGame::isWalkable(const double xp, const double yp, Direction dir, double speed)
{
  unsigned int				ret;
  double				x;
  double				y;

  x = 0;
  switch (dir)
    {
    case RIGHT :
      x = xp + 0.2 + 0.03f * speed;
      break;
    case LEFT :
      x = xp - 0.2 - 0.03f * speed;
      break;
    case UP :
      y = yp - 0.2 - 0.03f * speed;
      break;
    case DOWN :
      y = yp + 0.2 + 0.03f * speed;
      break;
    }
  if ((int)xp == (int)x && (int)yp == (int)y)
    ret = EMPTY;
  else
    {
      ret = this->getRun().getMap()->getAt(x, y);
      ret = this->getRun().isBomb(x, y, ret);
    }
  return (ret);
}

void					MyGame::checkBonus(APlayer* player)
{
  unsigned int				bloc;
  
  bloc = this->getRun().getMap()->getAt(player->getX(), player->getY());
  if (bloc > EMPTY)
    {
      song_->play("bonus");
      player->addBonus(bloc);
      this->getRun().getMap()->setAt((int)player->getX(), (int)player->getY(), EMPTY);
    }
}

Victory*				MyGame::getVictory(void) const
{
  return (this->victory_);
}

void					MyGame::P2_controls(gdl::Input & input_)
{
  APlayer				*pl;

  pl = this->getRun().getPlayerById(1);
  if (input_.isKeyDown(gdl::Keys::Right) == true)
    {
      pl->changeDir(RIGHT);
      if (this->isWalkable(pl, RIGHT) >= EMPTY)
  	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Left) == true )
    {
      pl->changeDir(LEFT);
      if (this->isWalkable(pl, LEFT) >= EMPTY)
  	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Down) == true)
    {
      pl->changeDir(DOWN);
      if (this->isWalkable(pl, DOWN) >= EMPTY)
  	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Up) == true)
    {
      pl->changeDir(UP);
      if (this->isWalkable(pl, UP) >= EMPTY)
  	pl->update(*(this->getRun().getGameClock()), input_);
    }
  this->checkBonus(pl);
  if (input_.isKeyDown(gdl::Keys::Numpad0) == true)
    {
      if (pl->getSkills().getActualBomb() < pl->getSkills().getMaxBomb()
  	  && this->getRun().isBombInX_Y((unsigned int)pl->getX(), (unsigned int)pl->getY()) == false)
  	{
  	  this->getRun().pushBomb(new Bomb(pl, gameClock_.getTotalGameTime()));
  	  pl->getSkills().putBomb();
  	}
    }
}

void					MyGame::P1_controls(gdl::Input & input_)
{
  APlayer				*pl;

  pl = this->getRun().getPlayerById(0);
  if (input_.isKeyDown(gdl::Keys::D) == true)
    {
      pl->changeDir(RIGHT);
      if (this->isWalkable(pl, RIGHT) >= EMPTY)
	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Q) == true )
    {
      pl->changeDir(LEFT);
      if (this->isWalkable(pl, LEFT) >= EMPTY)
	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::S) == true)
    {
      pl->changeDir(DOWN);
      if (this->isWalkable(pl, DOWN) >= EMPTY)
	pl->update(*(this->getRun().getGameClock()), input_);
    }
  else if (input_.isKeyDown(gdl::Keys::Z) == true)
    {
      pl->changeDir(UP);
      if (this->isWalkable(pl, UP) >= EMPTY)
	pl->update(*(this->getRun().getGameClock()), input_);
    }
  this->checkBonus(pl);
  if (input_.isKeyDown(gdl::Keys::Space) == true)
    {
      if (pl->getSkills().getActualBomb() < pl->getSkills().getMaxBomb()
	  && this->getRun().isBombInX_Y((unsigned int)pl->getX(), (unsigned int)pl->getY()) == false)
	{
	  this->getRun().pushBomb(new Bomb(pl, gameClock_.getTotalGameTime()));
	  pl->getSkills().putBomb();
	}
    }
}

bool			MyGame::load_game(void)
{
  Load			load("save.xml");

  if (this->inGame_ == false)
    return (false);
  if (load.isFileOpen())
    {
      if (this->run_ != NULL)
	delete this->run_;
      this->run_ = new Run(&gameClock_);
      this->run_->setSong(this->song_);
      if (load.parse(this->run_, this->settings_, this->camera_) == false)
	return (false);
      this->run_->getMap()->setStone(this->block);
      this->run_->getMap()->setBox(this->wall);
      this->run_->getMap()->setFloor(this->ground);
      this->run_->getMap()->setExplosion(this->explosion);
      this->run_->getMap()->setBombSup(this->bomb);
      this->run_->getMap()->setSpeed(this->speed);
      this->run_->getMap()->setRange(this->range);
    }
  else
    return (false);
  return (true);
}
