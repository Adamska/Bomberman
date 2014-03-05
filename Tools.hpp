#ifndef __Tools_HH__
#define __Tools_HH__

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <list>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


class Tools
{
  public:
  static void in_file(std::string text);
  static void c(char c);
  static std::string int_to_str(int i);
  static void display_map(std::list<std::pair<int, int> > coor);
  static bool sort_score(std::pair<std::string, int> one, std::pair<std::string, int> two);
  static void replace_score(std::list<std::pair<std::string, int> > list_score);
  static std::list<std::pair<std::string, int> > recup_highscore();
};

#endif
