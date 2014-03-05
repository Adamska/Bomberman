#ifndef __FileContent_HH__
#define __FileContent_HH__

#include <string>
#include <iostream>
#include <fstream>
#include <regex.h>
#include <list>
#include <sstream>
#include <stdlib.h>

class FileContent
{
private:
  bool isProb;
  std::list<int> my_value;
  int _widthBig;
  int _heightBig;
  std::list<char> caracMap;

public:
  FileContent();
  ~FileContent();
  void prob(int i);
  void my_read_map();
  void my_read_datas();
  bool syntax_valid(std::string contenu, const char* reg);
  bool verif_value(int nb, int pos);
  std::list<int> getList() const;
  bool is_valid_datas() const;
  void after_equals(std::string contenu, int pos, int i);
  std::list<char> getListStone() const;
  void check_bool(std::string text);
  void check_bool();
};

#endif
