#ifndef __VICTORY_H__
#define __VICTORY_H__

#include <list>
#include <SFML/Audio.hpp>
#include "APlayer.hpp"
#include "bomberman.hpp"                                                                   
#include "AObject.hpp"                                                              
#include "Vector3f.hpp"
#include "FontImage.hpp"   
#include "Model.hpp"
#include "Camera.hpp"
#include "Song.hpp"

enum Winner
  {
    P1,
    P2,
    IA,
  };

class Victory
{
public:
  Victory(void);
  ~Victory(void);
  void			endSong();
  void			startSong();
  void			initialize();
  void			initialize(float, float, float);
  void			update( );
  void			draw(enum Winner who);

private:
  Vector3f		pos_;
  Camera		camera_;
  bool			start_;
  gdl::Image		textureP1w_;
  gdl::Image		textureP2w_;
  gdl::Image		textureIaa_;
  Song			*song_;

  void			initialize_(void);
};

#endif
