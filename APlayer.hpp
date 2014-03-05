#ifndef __APLAYER_HPP__
#define __APLAYER_HPP__

#include "bomberman.hpp"
#include "Vector2f.hpp"
#include "Skills.hpp"
#include "Vector3f.hpp"
#include "Map.hpp"
#include "Song.hpp"

class Run;
class Map;

enum			Direction
  {
    UP,
    LEFT,
    DOWN,
    RIGHT,
    NONE
  };

class			APlayer
{
public:
  APlayer(const unsigned int& id, const double& posx, const double& posy, Skills*, bool _ia = true);
  APlayer(const unsigned int& id, Vector2f* pos, Skills* carac, bool _ia = true);

private:
  Vector2f*			_endPath;
  Vector2f*			_beginPath;
  std::list<Direction>		_path;
  unsigned int			_id;
  Vector2f*			_pos;
  Skills*			_carac;
  Direction			_dir;
  bool			        _ia;
  Vector3f		        _pos3f;
  Vector3f		        _rot;
  gdl::Model			_model; 

public:
  Vector2f*	        	getEndPath(void) const;
  void				setEndPath(Vector2f *);
  Vector2f*	        	getBeginPath(void) const;
  void				setBeginPath(Vector2f *);
  std::list<Direction> 		getPath(void) const;
  void				setPath(std::list<Direction>);
  void			        initialize(void);
  void			        initialize(float, float, float);
  void				init_rand(int *a, int *b, int *c, int *d);
  Vector2f&			getVector2f(void) const;
  Skills&			getSkills(void) const;
  unsigned int			getId(void) const;
  Direction			getDirection(void)const;
  double		        getX(void) const;
  double		        getY(void) const;
  gdl::Model			getModel(void) const;
  void			        setVector2f(Vector2f*& pos);
  void			        setVector2f(const double& x, const double& y);
  void			        setSkills(Skills*& carac);
  void			        setDirection(const Direction &direction);
  bool			        isIA() const;
  void			        update(gdl::GameClock const & gameClock, gdl::Input & input);
  void			        draw(const Map* map);
  void			        changeDir(Direction);
  void				addBonus(const unsigned int& bonus);
};

#endif
