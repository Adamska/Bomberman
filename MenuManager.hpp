#ifndef __MENUMANAGER__
#define __MENUMANAGER__

typedef enum e_select_choice
{
	CHOICE_1 = 1,
	CHOICE_2,
	CHOICE_3,
	CHOICE_4,
	CHOICE_5,
}		e_choice;

typedef enum e_current_menu
{
	MAIN_MENU = 1,
	START_MENU,
       	SETTINGS,
	SCORES,
	CREDITS
}		e_menu;

#define MAX_MAIN	CHOICE_5
#define MAX_START	CHOICE_4
#define MAX_SETTINGS	CHOICE_5

typedef enum  e_menu_change
{
	KEY_UP = 1,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT
}		e_change;

class MenuManager
{
public:
  int		state;
  int		choice;
  int		menu;
  bool		newgame;
};

#endif
