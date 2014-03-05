#ifndef __BONUS__
#define __BONUS__

#include "bomberman.hpp"
#include "AObject.hpp"
#include "Vector3f.hpp"

class Range : public AObject
{
public:
  Range();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
  float		angle_;
  bool		ascend_;
};

class BombSup : public AObject
{
public:
  BombSup();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
  float		angle_;
  bool		ascend_;
};

class Speed : public AObject
{
public:
  Speed();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
  float		angle_;
  bool		ascend_;
};

#endif
