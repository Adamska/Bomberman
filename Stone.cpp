#include "Pattern.hpp"

Stone::Stone()
{
  initialize();
}

void Stone::initialize(void)
{
  this->texture_ = gdl::Image::load("Textures/pierre.png");
}

void Stone::initialize(float const & x, float const & y, float const & z)
{
  this->pos_.setPos(x, y, z);
}

void Stone::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void) gameClock;
  (void) input;
}

void Stone::draw(void)
{
  texture_.bind();
  glPushMatrix();
  glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());

  glBegin(GL_QUADS);

  glTexCoord2d(0.33, 1); glVertex3f(-300.0f, 300.0f, 300.0f);
  glTexCoord2d(0.33, 0.33); glVertex3f(-300.0f, -300.0f, 300.0f);
  glTexCoord2d(1, 0.33); glVertex3f(300.0f, -300.0f, 300.0f);
  glTexCoord2d(1, 1); glVertex3f(300.0f, 300.0f, 300.0f);


  glTexCoord2d(0.33, 1); glVertex3f(-300.0f, 300.0f, -300.0f);
  glTexCoord2d(0.33, 0.33); glVertex3f(-300.0f, -300.0f, -300.0f);
  glTexCoord2d(1, 0.33); glVertex3f(-300.0f, -300.0f, 300.0f);
  glTexCoord2d(1, 1); glVertex3f(-300.0f, 300.0f, 300.0f);

  glTexCoord2d(0.33, 1); glVertex3f(300.0f, 300.0f, -300.0f);
  glTexCoord2d(0.33, 0.33); glVertex3f(300.0f, -300.0f, -300.0f);
  glTexCoord2d(1, 0.33); glVertex3f(-300.0f, -300.0f, -300.0f);
  glTexCoord2d(1, 1); glVertex3f(-300.0f, 300.0f, -300.0f);

  glTexCoord2d(0.33, 1); glVertex3f(300.0f, 300.0f, 300.0f);
  glTexCoord2d(0.33, 0.33); glVertex3f(300.0f, -300.0f, 300.0f);
  glTexCoord2d(1, 0.33); glVertex3f(300.0f, -300.0f, -300.0f);
  glTexCoord2d(1, 1); glVertex3f(300.0f, 300.0f, -300.0f);

  glTexCoord2d(0, 1); glVertex3f(-300.0f, 300.0f, 300.0f);
  glTexCoord2d(0, 0); glVertex3f(-300.0f, 300.0f, -300.0f);
  glTexCoord2d(0.33, 0); glVertex3f(300.0f, 300.0f, -300.0f);
  glTexCoord2d(0.33, 1); glVertex3f(300.0f, 300.0f, 300.0f);

  glEnd();
  glPopMatrix();
}
