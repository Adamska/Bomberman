#include "FontImage.hpp"

FontImage::FontImage()
{
  this->tab_texture_['0'] = gdl::Image::load("font/zero.png");
  this->tab_texture_['1'] = gdl::Image::load("font/un.png");
  this->tab_texture_['2'] = gdl::Image::load("font/deux.png");
  this->tab_texture_['3'] = gdl::Image::load("font/trois.png");
  this->tab_texture_['4'] = gdl::Image::load("font/quatre.png");
  this->tab_texture_['5'] = gdl::Image::load("font/cinq.png");
  this->tab_texture_['6'] = gdl::Image::load("font/six.png");
  this->tab_texture_['7'] = gdl::Image::load("font/sept.png");
  this->tab_texture_['8'] = gdl::Image::load("font/huit.png");
  this->tab_texture_['9'] = gdl::Image::load("font/neuf.png");
  this->sentence = "";
  this->isDisplay_ = false;
}

FontImage::~FontImage()
{

}

void		FontImage::setContent(std::string const & content)
{
  this->sentence = content;
  this->isDisplay_ = true;
}

void		FontImage::setPopup(bool const & pop)
{
  this->isDisplay_ = pop;
}

void		FontImage::putStr(std::string const str)
{
  int		i = 0;
  float		x = 50;
  float		y = 50;

  glPushMatrix();
  while(str[i])
  {
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     tab_texture_[str[i]].bind();
     glBegin(GL_QUADS);
     if (str[i++] == '1')
       x = 25;
     glTexCoord2d(0, 0); glVertex3f(-x, y, 0);
     glTexCoord2d(0, 1); glVertex3f(-x, -y, 0);
     glTexCoord2d(1, 1); glVertex3f(x, -y, 0);
     glTexCoord2d(1, 0); glVertex3f(x, y, 0);
     x = 50;
     glEnd();
     glDisable(GL_BLEND);
     glTranslatef(100, 0, 0);
 }
 glPopMatrix();
}

void		FontImage::displaySentence(void)
{
  if (this->isDisplay_ == true)
    {
      glPushMatrix();
      glTranslatef(-500, 0, 0);
      glPopMatrix();
    }
}
