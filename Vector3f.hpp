#ifndef __VECTOR3F__
#define __VECTOR3F__

class Vector3f
{
public:
  float x;
  float y;
  float z;
  
  Vector3f(void);
  Vector3f(float x, float y, float z);
  ~Vector3f(void);
  void		setPos(const float x, const float y, const float z);
  float		getX() const;
  float		getY() const;
  float		getZ() const;
  void		setX(const float x);
  void		setY(const float y);
  void		setZ(const float z);
};

#endif
