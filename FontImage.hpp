#ifndef __FONTIMAGE__
#define __FONTIMAGE__

#include "bomberman.hpp"
#include <map>

class FontImage
{
private:
  std::map<char, gdl::Image>	tab_texture_;
  std::string			sentence;
  bool				isDisplay_;

public:
  FontImage();
  ~FontImage();

  void		setContent(std::string const &);
  void		setPopup(bool const &);
  void		setMap(std::string const & file);
  void		setSize(int size);
  void		putStr(std::string const);
  void		displaySentence(void);
};

#endif
