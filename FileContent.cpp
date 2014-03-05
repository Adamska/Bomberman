#include "FileContent.hpp"
#include "Tools.hpp"

FileContent::FileContent()
{
  isProb = false;
}

FileContent::~FileContent()
{
}

void	FileContent::check_bool()
{
  if (this->isProb)
    Tools::in_file("prob");
  else
    Tools::in_file("no prob");
}

void	FileContent::check_bool(std::string text)
{
  Tools::in_file(text);
  if (this->isProb)
    Tools::in_file("prob");
  else
    Tools::in_file("no prob");
}

bool	FileContent::syntax_valid(std::string contenu, const char* reg)
{
  int final;
  regex_t my_reg;

  regcomp(&my_reg, reg, 0);
  final = regexec(&my_reg, contenu.c_str(), 0, NULL, 0);
  if (final == 0)
    return true;
  this->isProb = true;
  return false;
}

bool	FileContent::verif_value(int nb, int pos)
{
  if (pos == 0 && nb % 2 == 1 && nb >= 7 && nb <= 17)
    return true;
  if (pos == 1 && (nb == 1 || nb == 2))
	return true;
  if (pos == 2 && nb >= 0 && nb <= 10)
    return true;
  this->isProb = true;
  return false;
}

void	FileContent::my_read_map()
{
  std::string line;
  std::ifstream fichier("mapTable.txt", std::ios::in);
    if (fichier) 
      {
	std::string contenu; 
	while (getline(fichier, line))
	  {
	    if (line.size() && line.at(0) != '#')
	      {
		for (unsigned i = 0; i < line.length(); ++i)
		  {
		    if (line.at(i) > 'k' || line.at(i) < 'a')
		      this->isProb = true;
		    caracMap.push_back(line.at(i));
		  }
	      }
	  }
      }
    else
      this->isProb = true;
    if ((int)this->caracMap.size() != (this->_heightBig * this->_widthBig))
      this->isProb = true;
}

void	FileContent::my_read_datas()
{
  int i = 0;

  std::ifstream fichier("genMap.txt", std::ios::in);
  if (fichier) 
    {
      std::string contenu; 
      while (getline(fichier, contenu))
	{
	  if (i == 0 && (this->syntax_valid(contenu, "xMap=[0-9][0-9]$")))
	    this->after_equals(contenu, 0, 0);
	  if (i == 1 && (this->syntax_valid(contenu, "yMap=[0-9][0-9]$")))
	    this->after_equals(contenu, 0, 1);
	  if (i == 2 && (this->syntax_valid(contenu, "nbPlayer=[1-2]$")))
	    this->after_equals(contenu, 1, 2);
	  if (i == 3 && (this->syntax_valid(contenu, "nbIa=[0-9][0-9]$")))
	    this->after_equals(contenu, 2, 2);
	  i++;
	}
      fichier.close();
    }
  else
    this->isProb = true;
  if (i < 4)
    this->isProb = true;
}

std::list<int>	FileContent::getList() const
{
  return this->my_value;
}

bool	FileContent::is_valid_datas() const
{
  return !this->isProb;
}

void	FileContent::after_equals(std::string contenu, int pos, int i)
{
  int nb;
  int count;

  count = contenu.find("=");
  contenu = contenu.substr(count + 1, contenu.size());
  nb = atoi(contenu.c_str());
  this->verif_value(nb, pos);
  if (this->verif_value(nb, pos))
    {
      if (i == 0)
	this->_widthBig = nb;
      else if (i == 1)
	this->_heightBig = nb;
      my_value.push_back(nb);
    }
}

std::list<char> FileContent::getListStone() const
{
  return this->caracMap;
}
