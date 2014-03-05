#include "bomberman.hpp"
#include "Camera.hpp"

Camera::Camera(void) : pos_(0.0f, 0.0f, 900.0f), rot_(0.0f, 0.0f, 0.0f)
{
}

void		Camera::initialize(int pos)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, 1200.0f/800.0f, 1.0f, 10000.0f);
  if (pos)
    gluLookAt(pos_.x, pos_.y, pos_.z, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
  else
    gluLookAt(pos_.x, pos_.y, pos_.z, posn_.x, pos_.y, posn_.z, 0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void		Camera::reset_cam(float const & x, float const & y, int pos)
{
  pos_.x = 0.0f;
  if (!pos)
    {
      pos_.y = 0.0f;
      pos_.z = 900.0f;
    }
  else
    {
      pos_.y = (x + y) * (300.0f/1.5);
      pos_.z = 1200.0f;
    }
  posn_.x = 0.0f;
  posn_.y = 0.0f;
  posn_.z = -1.0f;
}

void		Camera::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(pos_.x, pos_.y, pos_.z,
	    posn_.x, posn_.y, posn_.z,
	    0.0f, 1.0f, 0.0f);
  (void) gameClock;
  (void) input;
}

void		Camera::getKeys(gdl::GameClock const & gameClock, gdl::Input & input)
{
  if (input.isKeyDown(gdl::Keys::Numpad2) == true)
    this->pos_.y += 40;
  if (input.isKeyDown(gdl::Keys::Numpad8) == true)
    this->pos_.y -= 40;
  if (input.isKeyDown(gdl::Keys::Numpad4) == true)
    this->pos_.z -= 40;
  if (input.isKeyDown(gdl::Keys::Numpad6) == true)
    this->pos_.z += 40;
  if (input.isKeyDown(gdl::Keys::Numpad7) == true)
    this->rot_.x += 40;
  if (input.isKeyDown(gdl::Keys::Numpad9) == true)
    this->rot_.x -= 40;
  if (input.isKeyDown(gdl::Keys::Numpad7) == true)
    this->posn_.x += 40;
  if (input.isKeyDown(gdl::Keys::Numpad9) == true)
    this->posn_.x -= 40;
  if (input.isKeyDown(gdl::Keys::Numpad1) == true)
    this->posn_.y += 40;
  if (input.isKeyDown(gdl::Keys::Numpad3) == true)
    this->posn_.y -= 40;
  if (input.isKeyDown(gdl::Keys::M) == true)
    this->posn_.z += 40;
  if (input.isKeyDown(gdl::Keys::L) == true)
    this->posn_.z -= 40;
  if (input.isKeyDown(gdl::Keys::K) == true)
    this->pos_.x += 40;
  if (input.isKeyDown(gdl::Keys::J) == true)
    this->pos_.x -= 40;
   this->update(gameClock, input);
}

Vector3f	Camera::getPos(void) const
{
  return (this->pos_);
}

Vector3f	Camera::getPosn(void) const
{
  return (this->posn_);
}

Vector3f	Camera::getRot(void) const
{
  return (this->rot_);
}

void		Camera::setPos(Vector3f const & pos)
{
  this->pos_ = pos;
}

void		Camera::setPosn(Vector3f const & posn)
{
  this->posn_ = posn;
}

void		Camera::setRot(Vector3f const & rot)
{
  this->rot_ = rot;
}
