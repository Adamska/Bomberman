#include "Pattern.hpp"

Explosion::Explosion()
{
  initialize();
}

void Explosion::initialize(void)
{
  this->texture_ = gdl::Image::load("Textures/images-fire.png");
}

void Explosion::initialize(float const & x, float const & y, float const & z)
{
  this->pos_.setPos(x, y, z);
}

void Explosion::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void) gameClock;
  (void) input;
}

void Explosion::draw(void)
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
