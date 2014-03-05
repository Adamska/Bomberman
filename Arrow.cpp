#include "Menu.hpp"
#include "MenuManager.hpp"

Arrow::Arrow(void)
{
}

Arrow::~Arrow(void)
{
}
  
void		Arrow::resetArrow(float const & y)
{
  this->pos_.y = y;
}

void		Arrow::initialize_()
{
  this->model_ = gdl::Image::load("Textures/fleche.png");
  this->rot_.setPos(0.0, 0.0, 0.0);
}

void		Arrow::initialize()
{
  this->pos_.setPos(0, 0, 0);
  this->initialize_();
}

void		Arrow::initialize(float const & y)
{
  this->pos_.setPos(0, y, 0);
  this->initialize_();
}

void		Arrow::update(float const & x,float const & y)
{
  this->pos_.x = x;
  this->pos_.y = y;
}

void		Arrow::draw(void)
{
  this->model_.bind();
  glPushMatrix(); 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glTranslatef(-(1200.0f), (800.0f) - (800.0f / 2), 0);
  glTranslatef(this->pos_.getX(), -(this->pos_.getY() * 250.0f), 0);
  glBegin(GL_QUADS);
  glTexCoord2d(0, 1); glVertex3f(-1000, -1000, 0);
  glTexCoord2d(0, 0); glVertex3f(-1000, 1000, 0);
  glTexCoord2d(1, 0); glVertex3f(1000, 1000, 0);
  glTexCoord2d(1, 1); glVertex3f(1000, -1000, 0);
  glEnd();
  glDisable(GL_BLEND);
  glPopMatrix();
}
