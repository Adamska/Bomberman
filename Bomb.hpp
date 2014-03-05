#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include "bomberman.hpp"
#include "Vector2f.hpp"
#include "MyGame.hpp"
#include "Run.hpp"
#include "Song.hpp"

class Run;
class			Bomb
{
private:
  Explosion		_Explosion;
  unsigned int		_id;
  unsigned int		_range;
  float			_delayExplosion;
  float			_TimePosed;
  Vector2f*		_pos;
  gdl::Model		_model;
  Vector3f		_rot;
  
public:

  Bomb(const double& x, const double& y, const unsigned int & id,
       const unsigned int & range, const float& startTimer);
  Bomb(APlayer* player, const float& startTimer);
  ~Bomb();


  void			draw(const Map*, const float& time);
  void			draw_explosion(const Map*);
  bool			game_over(int x, int y, int t1, int t2, int t3,
				Ibloc bloc, const Map* map);
  Vector2f&		getVector2f(void) const;
  double&		getX(void) const;
  double& 		getY(void) const;
  const unsigned int&	getId(void) const;
  const unsigned int&   getRange(void) const;
  const float&		getTimePosed(void) const;
  const float&		getDelayExplosion(void) const;
  bool			timeOver(const float& time) const;
  void			setDelayExplosion(const float &d);
  void			setVector2f(Vector2f*&);
  void			setX(const double&);
  void			setY(const double&);
  void			setTimePosed(const float & timer);
  void			setId(const unsigned int&);
  void			setRange(const unsigned int&);
  void			explose(Run *);
  int			eachCase(int const & , int const &, Run *);
};

#endif
