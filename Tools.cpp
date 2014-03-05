#include "Tools.hpp"

void			Tools::in_file(std::string text)
{
  std::ofstream		fichier;
  
  fichier.open("test.txt", std::ios::app);
  if (fichier)
    fichier << text << std::endl;
  else
    abort();
  fichier.close();
}

void			Tools::c(char c)
{
  std::ofstream		fichier;
  
  fichier.open("test.txt", std::ios::app);
  if (fichier)
    fichier << c << std::endl;
  else
    abort();
  fichier.close();
}

std::string		Tools::int_to_str(int i)
{
  std::string		s;
  std::stringstream	out;
  out << i;
  s = out.str();
  return s;
}

void						Tools::display_map(std::list<std::pair<int, int> > coor)
{
  std::list<std::pair<int, int> >::iterator	it;

  in_file("debut map");
  for (it = coor.begin(); it != coor.end(); ++it)
    {
      in_file(int_to_str(it->first));
      in_file(int_to_str(it->second));
      in_file("NEXT");
    }
  in_file("fin map\n");
}

void			Tools::replace_score(std::list<std::pair<std::string, int> > list_score)
{
  std::ofstream		fichier;
  std::string		aline;

  fichier.open("highscore", std::ios::trunc);
  std::list<std::pair<std::string,int> >::iterator it;
  if (fichier)
    {
      for (it = list_score.begin(); it != list_score.end(); ++it)
	{
	  aline = it->first + "=" + Tools::int_to_str(it->second);
	  fichier << aline << std::endl;
	  aline.clear();
	}
    }
  else
    std::cerr << "file cannot replace score" << std::endl;
}
