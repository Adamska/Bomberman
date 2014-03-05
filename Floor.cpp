#include "Pattern.hpp"

Floor::Floor()
{
  initialize();
}

void Floor::initialize(void)
{
  this->texture_ = gdl::Image::load("Textures/metal.jpg");
}

void Floor::initialize(float const & x, float const & y, float const & z)
{
  this->pos_.setPos(x, y, z);
}

void Floor::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void) gameClock;
  (void) input;
}

void Floor::draw(void)
{
  texture_.bind();
  glPushMatrix();
  glTranslatef(this->pos_.getX(), this->pos_.getY() - 600.0f, this->pos_.getZ());

  glBegin(GL_QUADS);

  glTexCoord2d(0, 1); glVertex3f(-300.0f, 300.0f, 300.0f);
  glTexCoord2d(0, 0); glVertex3f(-300.0f, 300.0f, -300.0f);
  glTexCoord2d(1, 0); glVertex3f(300.0f, 300.0f, -300.0f);
  glTexCoord2d(1, 1); glVertex3f(300.0f, 300.0f, 300.0f);

  glEnd();
  glPopMatrix();
}
