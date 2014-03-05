#ifndef __PATTERN__
#define __PATTERN__

#include "bomberman.hpp"
#include "AObject.hpp"
#include "Vector3f.hpp"
#include "FontImage.hpp"
#include "Bonus.hpp"
#include "Skills.hpp"

class Floor : public AObject
{
public:
  Floor();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
};

class Stone : public AObject
{
public:
  Stone();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
};

class Explosion : public AObject
{
public:
  Explosion();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
};

class Box : public AObject
{
public:
  Box();
  void initialize(void);
  void initialize(float const & x, float const & y, float const & z);
  void update(gdl::GameClock const &, gdl::Input &);
  void draw(void);
private:
  gdl::Image	texture_;
};

#endif
