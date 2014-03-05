#include "Bonus.hpp"

Speed::Speed()
{
  initialize();
  angle_ = 150;
  ascend_ = true;
}

void Speed::initialize(void)
{
  this->texture_ = gdl::Image::load("Textures/speed.png");
}

void Speed::initialize(float const & x, float const & y, float const & z)
{
  this->pos_.setPos(x, y, z);
}

void Speed::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void) gameClock;
  (void) input;
}

void Speed::draw(void)
{
  texture_.bind();
  glPushMatrix();
  glTranslatef(this->pos_.getX(), this->pos_.getY(), this->pos_.getZ());
  glBegin(GL_QUADS);

  if (angle_ > 200)
    ascend_ = false;
  if (angle_ < 150)
    ascend_ = true;
  if (ascend_ == true)
    angle_+= 0.5;
  else
    angle_ -= 0.5;
  glTexCoord2d(0, 0); glVertex3f(-angle_, angle_, 0);
  glTexCoord2d(0, 1); glVertex3f(-angle_, -angle_, angle_);
  glTexCoord2d(1, 1); glVertex3f(angle_, -angle_, angle_);
  glTexCoord2d(1, 0); glVertex3f(angle_, angle_, 0);
  glEnd();
  glPopMatrix();
}
