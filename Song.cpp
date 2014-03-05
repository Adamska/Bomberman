#include "bomberman.hpp"
#include <SFML/Audio.hpp>
#include "Song.hpp"


Song::Song()
{
  BufferendIA_= new sf::SoundBuffer;
  SongendIA_= new sf::Sound();
  BufferendP1_= new sf::SoundBuffer;
  SongendP1_= new sf::Sound();
  BufferendP2_= new sf::SoundBuffer;
  SongendP2_= new sf::Sound();
  Songgame_= new sf::Sound;
  Buffergame_= new sf::SoundBuffer;
  Songmenu_= new sf::Music;
  Songbomb_= new sf::Music;
  Songpower_ = new sf::Music;
  Songbomb_->OpenFromFile("Sounds/paf.ogg");
  Songmenu_->OpenFromFile("Sounds/click.ogg");
  Songpower_->OpenFromFile("Sounds/dingue.ogg");
  Buffergame_->LoadFromFile("Sounds/game.wav");
  BufferendIA_->LoadFromFile("Sounds/EndIA.wav");
  BufferendP1_->LoadFromFile("Sounds/EndP1.wav");
  BufferendP2_->LoadFromFile("Sounds/EndP2.wav");
}


Song::~Song()
{
  delete Songmenu_;
  delete Songpower_;
  delete Songbomb_;
  delete Songgame_;
  delete Buffergame_;
  delete BufferendIA_;
  delete SongendIA_;
  delete BufferendP1_;
  delete SongendP1_;
  delete BufferendP2_;
  delete SongendP2_;
}

void Song::bomb()
{
  Songbomb_->Play();
  Songbomb_->SetVolume(20.f);
}

void Song::menu()
{
  Songmenu_->Play(); 
  Songmenu_->SetVolume(7.f);
}

void Song::bonus()
{
  Songpower_->Play();
  Songpower_->SetVolume(20.f);

}

void Song::game()
{
  Songgame_->SetBuffer(*Buffergame_);
  Songgame_->Play();
  Songgame_->SetVolume(10.f);
}

void Song::endIA()
{
  SongendIA_->SetBuffer(*BufferendIA_);
  SongendIA_->Play();
}

void Song::endP1()
{
  SongendP1_->SetBuffer(*BufferendP1_);
  SongendP1_->Play();
  SongendP1_->SetVolume(7.f);
}

void Song::endP2()
{
  SongendP2_->SetBuffer(*BufferendP2_);
  SongendP2_->Play();
  SongendP2_->SetVolume(7.f);
}


tPtrSong  FuncPtrSong[]=
  {
    {"bomb",&Song::bomb},
    {"menu",&Song::menu},
    {"bonus",&Song::bonus},
    {"game",&Song::game},
    {"endIA",&Song::endIA},
    {"endP1",&Song::endP1},
    {"endP2",&Song::endP2},
    {0,0},
  };

void		Song::play(const char *s)
{
  int		i = 0;
  std::string	so;
  so = s;
  while(FuncPtrSong[i].a)
    {
      if (FuncPtrSong[i].a == so)
	  (this->*FuncPtrSong[i].f)();
      i++;
    }
}

void Song::stop()
{
  Songmenu_->Stop();
  Songbomb_->Stop();
  Songpower_->Stop();
  Songgame_->Stop();
  SongendIA_->Stop();
  SongendP1_->Stop();
  SongendP2_->Stop();
}

void Song::pause()
{
  Songgame_->Pause();
}

void Song::ResumeGame()
{
  Songgame_->Play();
}
