#ifndef __SKILLS_HPP__
#define __SKILLS_HPP__

class			Skills
{
public:
  Skills();
  ~Skills();

private:
  unsigned int			_speed;
  unsigned int			_actualBomb;
  unsigned int			_maxBomb;
  unsigned int			_range;
  unsigned int			_alive;
public:
  const unsigned int&		getSpeed(void) const;
  const unsigned int&		getMaxBomb() const;
  const unsigned int&		getActualBomb() const;
  const unsigned int&		getRange(void) const;
  const unsigned int&		getAlive(void) const;
  void				setSpeed(const unsigned int& speed);
  void				setActualBomb(const unsigned int& bomb);
  void				setMaxBomb(const unsigned int&);
  void				setRange(const unsigned int& range);
  void				setAlive(const unsigned int& alive);
  bool				putBomb(void);
  void				delBomb();
  void				increaseBomb(const unsigned int& toAdd);
  void				increaseRange(const unsigned int&);  
  void				increaseSpeed(const unsigned int& toAdd);
};

#endif
