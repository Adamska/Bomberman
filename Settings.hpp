#ifndef		__SETTINGS_HPP__
#define		__SETTINGS_HPP__

class Settings
{
  int			_width;
  int			_height;
  unsigned int		_nbPlayer;
  unsigned int		_nbIa;

public:
  Settings(const int & x, const int & y, const unsigned int & nb_player, const unsigned int & nb_ia);
  ~Settings();

  void			setNbPlayer(const unsigned int & nb);
  void			setNbIa(const int & nb);
  void			setWidth(const int & x);
  void			setHeight(const int & x);
  int			getWidth() const;
  int			getHeight() const;
  unsigned int		getNbPlayer() const;
  unsigned int		getNbIa() const;
};

#endif
