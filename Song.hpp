#ifndef __SONG_H__
#define __SONG_H__
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>

class Song
{  
public:
  Song();
  ~Song();
  void			play(const char *s);
  void			stop();
  void			pause();
  void			menu();
  void			bomb();
  void			bonus();
  void			game();
  void			endIA();
  void			endP1();
  void			endP2();
  void			ResumeGame();

private:
  sf::Music		*Songbomb_;
  sf::Music		*Songpose_;
  sf::Music		*Songmenu_;
  sf::Music		*Songpower_;
  sf::Sound		*Songgame_;
  sf::SoundBuffer	*Buffergame_;

  sf::Sound		*SongendIA_;
  sf::SoundBuffer	*BufferendIA_;
  sf::Sound		*SongendP1_;
  sf::SoundBuffer	*BufferendP1_;
  sf::Sound		*SongendP2_;
  sf::SoundBuffer	*BufferendP2_;
};

typedef struct sptrSong
{
  const char *a;
  void (Song::*f)();
}tPtrSong;

#endif
