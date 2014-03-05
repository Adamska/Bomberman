#ifndef __CAMERA__
#define __CAMERA__

#include "Vector3f.hpp"
#include "Song.hpp"

class Camera
{
public:
  Camera(void);
  void		reset_cam(float const & x, float const & y, int pos);
  void		initialize(int pos);
  void		update(gdl::GameClock const &, gdl::Input & input);
  void		getKeys(gdl::GameClock const &, gdl::Input & input);
  Vector3f	getPos(void) const;
  Vector3f	getPosn(void) const;
  Vector3f	getRot(void) const;
  void		setPos(Vector3f const & pos);
  void		setPosn(Vector3f const & posn);
  void		setRot(Vector3f const & pos);
private:
  Song		song_;
  Vector3f	pos_;
  Vector3f	posn_;
  Vector3f	rot_;
};

#endif
