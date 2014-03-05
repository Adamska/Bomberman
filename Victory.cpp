#include <iomanip>
#include <SFML/Audio.hpp>
#include "MyGame.hpp"
#include "FontImage.hpp"
#include "Victory.hpp"
#include "Song.hpp"

Victory::Victory()
{
  song_ = new Song;
}

Victory::~Victory(void)
{
  delete song_;
}

void	Victory::endSong()
{
  song_->stop();
}

void	Victory::startSong()
{
  start_ = false;
}


void Victory::initialize_()
{
 this->textureP1w_ = gdl::Image::load("Textures/p1win.png");
 this->textureP2w_ = gdl::Image::load("Textures/p2win.png");
 this->textureIaa_ = gdl::Image::load("Textures/iawin.png");   
}

void Victory::initialize()
{
  this->pos_.setPos(0.0, 0.0, 1.0);
  this->initialize_();
}

void Victory::initialize(float x, float y, float z)
{
  this->pos_.setPos(x, y, z);
  this->initialize_();
}
  
void Victory::update()
{
  camera_.initialize(1);
}

void Victory::draw(Winner who)
{
  int placex = 220;
  int placey = 220;
  int placez = 220;

  this->update();
  if (who == P1)
    {
      textureP1w_.bind();
      if (start_ == false)  
	{
	  song_->play("endP1");  
	  start_ = true;
	}
    }
  else if (who == P2)
    {
      placex = 600;
      placey = 380;
      textureP2w_.bind();
      if (start_ == false)  
	{
	  song_->play("endP2");  
	  start_ = true;
	}
    }
  else
    {
      textureIaa_.bind();
      if (start_ == false)  
      	{
	  song_->play("endIA");  
	  start_ = true;
	}
    }

  glClearColor(0.8f ,1.0f, 1.0f, 1.0f);
  glClearDepth(1.0f);
  
  glPushMatrix();
  glBegin(GL_QUADS);
  glTexCoord2d(0,0); glVertex3f(-placex, placey, placez);
  glTexCoord2d(0,1); glVertex3f(-placex, -placey, placez);
  glTexCoord2d(1,1); glVertex3f(placex, -placey, placez);
  glTexCoord2d(1,0); glVertex3f(placex, placey, placez);
  glEnd();
  glPopMatrix();  
}
