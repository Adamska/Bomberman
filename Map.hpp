#ifndef __MAP_HPP__
#define __MAP_HPP__

#include <vector>
#include <list>
#include "Settings.hpp"
#include "APlayer.hpp"
#include "FontImage.hpp"
#include "bomberman.hpp"
#include "Bonus.hpp"
#include "Pattern.hpp"

class APlayer;

typedef enum e_bloc
{
    INDESTRUCTIBLE,
    DESTRUCTIBLE,
    DESTRUCTIBLE_BOMB,
    DESTRUCTIBLE_SPEED,
    DESTRUCTIBLE_RANGE,
    SPECIAL,
    EMPTY,
    BOMB,
    SPEED,
    RANGE,
  }		Ibloc;

  class					        Map
  {
    std::vector<std::vector<Ibloc> >		_map;
    unsigned int				_width;
    unsigned int				_height;
    Stone					*block;
    Box						*wall;
    Floor					*ground;
    Explosion					*explosion;
    BombSup					*bomb;
    Speed					*speed;
    Range					*range;


  public:
    Map(){};
    ~Map(){};

    void						draw();
    void						createMap(const Settings & opt);
    void						createMap(const Settings & opt, std::list<char> list_bloc);
    std::vector<std::vector<Ibloc> >			getMap() const;
    unsigned int					getWidth() const;
    unsigned int					getHeight() const;
    void				                setWidth(const unsigned int &x);
    void						setHeight(const unsigned int &y);
    void						setStone(Stone *);
    void						setBox(Box *);
    void						setFloor(Floor *);
    void						setExplosion(Explosion *);
    void						setBombSup(BombSup *);
    void						setSpeed(Speed *);
    void						setRange(Range *);
    void						setMap(std::vector<std::vector<Ibloc> >& map);
    Ibloc						getAt(const double &dx, const double &dy) const;
    void						setAt(const double &dd, const double&d, Ibloc);
    Ibloc						createBonusBloc(const Settings&) const;
    void						removeBlocAroundPlayers(std::list<APlayer*> playerList);
  };

#endif
