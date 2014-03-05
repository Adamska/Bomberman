#ifndef __OBJMENU__
#define __OBJMENU__

#include "bomberman.hpp"
#include "AObject.hpp"
#include "Vector3f.hpp"
#include "MenuManager.hpp"
#include "Tools.hpp"
#include "FontImage.hpp"
#include "MenuManager.hpp"
#include "Settings.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

class Arrow
{
public:
  Arrow(void);
  ~Arrow(void);
  void		resetArrow(float const &);
  void		initialize(void);
  void		initialize(float const &);
  void		update(float const &, float const &);
  void		draw(void);

private:
  Vector3f	pos_;
  Vector3f	rot_;
  gdl::Image	model_;
  float		space_;

  void		initialize_(void);
};

#endif
