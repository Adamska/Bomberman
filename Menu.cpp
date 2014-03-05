#include "Menu.hpp"

Menu::Menu(void)
{
}

Menu::~Menu(void)
{
}

void		Menu::reset_accueil(void)
{
  this->mb_.resetArrow(this->who_);
}

void		Menu::initialize_(void)
{
  this->tTitle_ = gdl::Image::load("Textures/menu.png");
  this->tSettings_ = gdl::Image::load("Textures/menu.png");

  /* CHARGE LES ICONES PLAY LOAD CREDIT SETTING EXIT */
  this->tplay = gdl::Image::load("Textures/menu/playb.png");
  this->tplayj = gdl::Image::load("Textures/menu/playj.png");
  this->tload = gdl::Image::load("Textures/menu/loadb.png");
  this->tcredit = gdl::Image::load("Textures/menu/creditsb.png");
  this->tsetting = gdl::Image::load("Textures/menu/bombsetb.png");
  this->texit = gdl::Image::load("Textures/menu/exitb.png");
  this->tloadj = gdl::Image::load("Textures/menu/loadj.png");
  this->tcreditj = gdl::Image::load("Textures/menu/creditsj.png");
  this->tsettingj = gdl::Image::load("Textures/menu/bombsetj.png");
  this->texitj = gdl::Image::load("Textures/menu/exitj.png");

  this->cup_or = gdl::Image::load("Textures/or.png");
  this->cup_argent = gdl::Image::load("Textures/argent.png");
  this->cup_bronze = gdl::Image::load("Textures/bronze.png");

  /* PAGE CREDIT PLAY SETTINGS SCORE */
  this->pcredit = gdl::Image::load("Textures/credit.png");
  this->pplay = gdl::Image::load("Textures/play.png");
  this->psetting = gdl::Image::load("Textures/settings.png");
  this->pscore = gdl::Image::load("Textures/scores.png");

  this->oldKey_ = false;
  this->ng_ = true;
  this->who_ = 1;
  this->mb_.initialize(this->who_);
}

void		Menu::initialize(void)
{
  this->pos_.setPos(0.0, 0.0, 1.0);
  this->initialize_();
}

void		Menu::initialize(float const & x, float const & y, float const &z)
{
  this->pos_.setPos(x, y, z);
  this->initialize_();
}

void		Menu::main_menu(int const & dir)
{
  if (dir == KEY_UP)
    this->who_ -= 1;
  else if (dir == KEY_DOWN)
    this->who_ += 1;
    
  if (this->who_ > (MAX_MAIN))
    this->who_ = 1;
  else if (this->who_ < 1)
    this->who_ = (MAX_MAIN);
}

void    Menu::settings_menu(int const & dir)
{
  if (dir == KEY_UP)
    this->who_ -= 1;
  else if (dir == KEY_DOWN)
    this->who_ += 1;
    
  if (this->who_ > MAX_SETTINGS)
    this->who_ = CHOICE_1;
  else if (this->who_ < CHOICE_1)
    this->who_ = MAX_SETTINGS;

  switch (this->who_)
    {
    case 1:
      this->mb_.update(320, 2.6);
      break;
    case 2:
      this->mb_.update(320, 4.0);
      break;
    case 3:
      this->mb_.update(320, 5.45);
      break;
    case 4:
      this->mb_.update(320, 6.9);
      break;
    case 5:
      this->mb_.update(2200, 7.3);
      break;
    }
}


void    Menu::start_menu(int const & dir)
{
  if (dir == KEY_UP)
    this->who_ -= 1;
  else if (dir == KEY_DOWN)
    this->who_ += 1;

  if (this->who_ > MAX_START)
    this->who_ = CHOICE_1;
  else if (this->who_ < CHOICE_1)
    this->who_ = MAX_START;

  if (this->who_ == 1)
    this->mb_.update(1200,2.4);
  else if (this->who_ == 2)
    this->mb_.update(1200,3.7);
  else if (this->who_ == 3)
    this->mb_.update(1200,5.1);
  else
    this->mb_.update(2700,6.9);
}

int		Menu::update(int const & who, float const &x, float const &y)
{
  this->who_ = who;
  this->mb_.update(x, y);
  return(0);
}

int		Menu::update(int const & dir, int const & menu)
{
  if (dir != 0)
    {
      switch (menu)
	{
	case MAIN_MENU:
	  this->main_menu(dir);
	  break;
	case START_MENU:
	  this->start_menu(dir);
	  break;
	case SETTINGS:
	  this->settings_menu(dir);
	  break;
	}    
    }
  return(this->who_);
}

void		Menu::draw_main_menu(void)
{
  int		xplay = 370;
  int		yplay = 200;

  this->tTitle_.bind();
  glPushMatrix();
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-ABSCISSE, -ORDONNEE, 0);
  glTexCoord2d(0, 0); glVertex3f(-ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 0); glVertex3f(ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 1); glVertex3f(ABSCISSE, -ORDONNEE, 0);
  glEnd();
  glPopMatrix();


  /*PLAY LOAD CREDITS*/

  /*PLAY*/
    
  if (who_ == 1)
    this->tplayj.bind();
  else
    this->tplay.bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(1350,600,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-xplay, -yplay, 0);
  glTexCoord2d(0, 0); glVertex3f(-xplay, yplay, 0);
  glTexCoord2d(1, 0); glVertex3f(xplay, yplay, 0);
  glTexCoord2d(1, 1); glVertex3f(xplay, -yplay, 0);
  glEnd();
  glPopMatrix();


  /*LOAD*/
  if (who_ == 2)
    this->tloadj.bind();
  else
    this->tload.bind();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(1350,-150,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-xplay, -yplay, 0);
  glTexCoord2d(0, 0); glVertex3f(-xplay, yplay, 0);
  glTexCoord2d(1, 0); glVertex3f(xplay, yplay, 0);
  glTexCoord2d(1, 1); glVertex3f(xplay, -yplay, 0);
  glEnd();
  glPopMatrix();


  /*CREDITS*/
  if (who_ == 3)
    this->tcreditj.bind();
  else
    this->tcredit.bind();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(1350,-850,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-370, -200, 0);
  glTexCoord2d(0, 0); glVertex3f(-370, 200, 0);
  glTexCoord2d(1, 0); glVertex3f(370, 200, 0);
  glTexCoord2d(1, 1); glVertex3f(370, -200, 0);
  glEnd();

  glPopMatrix();



  /*SETTINGS*/
  if (who_ == 4)
    this->tsettingj.bind();
  else
    this->tsetting.bind();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(-1600,-750,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-370, -200, 0);
  glTexCoord2d(0, 0); glVertex3f(-370, 200, 0);
  glTexCoord2d(1, 0); glVertex3f(370, 200, 0);
  glTexCoord2d(1, 1); glVertex3f(370, -200, 0);
  glEnd();
  glPopMatrix();


  /*EXIT*/
  if (who_ == 5)
    this->texitj.bind();
  else
    this->texit.bind();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(-1600,-1050,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-370, -200, 0);
  glTexCoord2d(0, 0); glVertex3f(-370, 200, 0);
  glTexCoord2d(1, 0); glVertex3f(370, 200, 0);
  glTexCoord2d(1, 1); glVertex3f(370, -200, 0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();

}

void    Menu::draw_start_menu(void)
{
  this->pplay.bind();
  glPushMatrix();
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-ABSCISSE, -ORDONNEE, 0);
  glTexCoord2d(0, 0); glVertex3f(-ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 0); glVertex3f(ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 1); glVertex3f(ABSCISSE, -ORDONNEE, 0);
  glEnd();
  glPopMatrix();
  this->mb_.draw();
}

void			Menu::draw_settings(Settings const & opt)
{
  std::ostringstream    x;
  std::ostringstream    y;
  std::ostringstream    nbPlayer;
  std::ostringstream    nbIa;

  nbPlayer << opt.getNbPlayer();
  nbIa << opt.getNbIa();
  x << opt.getWidth();
  y << opt.getHeight();

  this->psetting.bind();
  glPushMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-ABSCISSE, -ORDONNEE, 0);
  glTexCoord2d(0, 0); glVertex3f(-ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 0); glVertex3f(ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 1); glVertex3f(ABSCISSE, -ORDONNEE, 0);

  glEnd();
  glDisable(GL_BLEND);

  this->mb_.draw();

  glTranslatef(-500, 100, 0);
  this->fontImage_.putStr(x.str());
  glTranslatef(0, -350, 0);
  this->fontImage_.putStr(y.str());

  glTranslatef(250, -380, 0);
  this->fontImage_.putStr(nbPlayer.str());
  glTranslatef(-300, -340, 0);
  this->fontImage_.putStr(nbIa.str());
  glPopMatrix();
}

void    Menu::draw_credits(void)
{
  this->pcredit.bind();
  glPushMatrix();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-ABSCISSE, -ORDONNEE, 0);
  glTexCoord2d(0, 0); glVertex3f(-ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 0); glVertex3f(ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 1); glVertex3f(ABSCISSE, -ORDONNEE, 0);

  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();
}
  
void			Menu::draw_score(void)
{
  std::stringstream	ss;
  std::string		P1;
  std::string		P2;
  std::string		IA;


  this->pscore.bind();

  glPushMatrix();
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-ABSCISSE, -ORDONNEE, 0);
  glTexCoord2d(0, 0); glVertex3f(-ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 0); glVertex3f(ABSCISSE, ORDONNEE, 0);
  glTexCoord2d(1, 1); glVertex3f(ABSCISSE, -ORDONNEE, 0);
  glEnd();
    
  ss << victoryP1 << " " << victoryP2 << " " << victoryIA;
  ss >> P1;
  ss >> P2;
  ss >> IA;

  glTranslatef(-1350, -120, 0);
  this->fontImage_.putStr(P1);
  glTranslatef(1325, 0, 0);
  this->fontImage_.putStr(IA);
  glTranslatef(1300, 0, 0);
  this->fontImage_.putStr(P2);
  glPopMatrix();
  draw_cup();
}

void		Menu::draw(Settings const & opt, int const & mod)
{
  switch (mod)
    {
    case MAIN_MENU:
      this->draw_main_menu();
      break;
    case START_MENU:
      this->draw_start_menu();
      break;
    case SETTINGS:
      this->draw_settings(opt);
      break;
    case SCORES:
      this->draw_score();
      break;
    case CREDITS:
      this->draw_credits();
      break;
    }
}

bool  Menu::isNewGame(void) const
{
  return(this->ng_);
}

void  Menu::setNewGame(bool const & ng)
{
  this->ng_ = ng;
}

int	Menu::get_victoryP1() const
{
  return this->victoryP1;
}

int	Menu::get_victoryP2() const
{
  return this->victoryP2;
}
  
int	Menu::get_victoryIA() const
{
  return this->victoryIA;
}


void			Menu::loadScore(void)
{
  std::ifstream		file("ScoreTable.txt", std::ios::in);
  std::stringstream	parse_line;
  std::string		line;

  if (file)
    {
      getline(file, line);
      parse_line << line;
      parse_line >> victoryP1;
      parse_line >> victoryP2;
      parse_line >> victoryIA;
      file.close();
    }
}

void		Menu::saveScore(int player)
{
  std::ofstream file("ScoreTable.txt", std::ios::out | std::ios::trunc);

  if (player == 0)
    this->victoryP1++;
  else if (player == 1)
    this->victoryP2++;
  else
    this->victoryIA++;
  if (file)
    {
      file << this->victoryP1 << " " << this->victoryP2 << " " << this->victoryIA << std::endl;
      file.close(); 
    }
}

void	Menu::cup_p1_(gdl::Image tmp)
{
  tmp.bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(-1300,-700,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-500, -500, 0);
  glTexCoord2d(0, 0); glVertex3f(-500, 500, 0);
  glTexCoord2d(1, 0); glVertex3f(500, 500, 0);
  glTexCoord2d(1, 1); glVertex3f(500, -500, 0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();    
}
  
void	Menu::cup_p2_(gdl::Image tmp)
{
  tmp.bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(1300,-700,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-500, -500, 0);
  glTexCoord2d(0, 0); glVertex3f(-500, 500, 0);
  glTexCoord2d(1, 0); glVertex3f(500, 500, 0);
  glTexCoord2d(1, 1); glVertex3f(500, -500, 0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();    
}
  
void	Menu::cup_ia_(gdl::Image tmp)
{
  tmp.bind();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPushMatrix();
  glTranslatef(0,-700,0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-500, -500, 0);
  glTexCoord2d(0, 0); glVertex3f(-500, 500, 0);
  glTexCoord2d(1, 0); glVertex3f(500, 500, 0);
  glTexCoord2d(1, 1); glVertex3f(500, -500, 0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();    
}
  
void	Menu::draw_cup()
{
  int	vp1_ = 0;
  int	vp2_ = 0;
  int	via_ = 0;

  vp1_ = get_victoryP1();
  vp2_ = get_victoryP2();	
  via_ = get_victoryIA();
  if (vp1_ > vp2_ && vp1_ > via_)
    {
      cup_p1_(cup_or);
      if (vp2_ > via_)
	{
	  cup_p2_(cup_argent);
	  cup_ia_(cup_bronze);
	}
      else
	{
	  cup_p2_(cup_bronze);
	  cup_ia_(cup_argent);
	}
    }
  else if (vp2_ > vp1_ && vp2_ > via_)
    {
      cup_p2_(cup_or);
      if (vp1_ > via_)
	{
	  cup_p1_(cup_argent);
	  cup_ia_(cup_bronze);
	}
      else
	{
	  cup_ia_(cup_argent);
	  cup_p1_(cup_bronze);
	}
    }
  else if (via_ > vp1_ && via_ > vp2_)
    {
      cup_ia_(cup_or);
      if (vp1_ > vp2_)
	{
	  cup_p1_(cup_argent);
	  cup_p2_(cup_bronze);
	}
      else
	{
	  cup_p1_(cup_bronze);
	  cup_p2_(cup_argent);
	}
    }
}
