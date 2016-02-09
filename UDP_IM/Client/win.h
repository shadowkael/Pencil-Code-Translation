#ifndef WIN_H
#define WIN_H

#endif // WIN_H

#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include "udpData.h"

#define WIN_TEXT 0
#define WIN_MSG 1

char users[TEXTSIZE / UIDSIZE][UIDSIZE];
ITEM ** user_items;
int n_users = 0;
char * now_user;

// function to initialize window
WINDOW * box_users;
WINDOW * win_msg;
WINDOW * win_text;
MENU * user_list;
void init_window(){
  WINDOW * box_msg;
  WINDOW * box_text;

  initscr();
  noecho();
  nonl();
  raw();
  refresh();

  box_msg = newwin(19, 62, 0, 0);
  win_msg = newwin(17, 60, 1, 1);
  box_text = newwin(6, 62, 18, 0);
  win_text = newwin(4, 60, 19, 1);
  box_users = newwin(LINES, COLS - 61, 0, 61);
  box(box_text, 0, 0);
  box(box_msg, 0, 0);
  box(box_users, 0, 0);

  keypad(stdscr, true);
  scrollok(win_msg, true);
  scrollok(win_text, true);

  // draw three boxes and two windows
  touchwin(box_msg);
  wrefresh(box_msg);
  touchwin(box_text);
  wrefresh(box_text);
  touchwin(win_msg);
  wrefresh(win_msg);
  touchwin(win_text);
  wrefresh(win_text);
  touchwin(box_users);
  wrefresh(box_users);
}

void uid_show(const char * uid){
  mvwprintw(box_users, 1, 1, "%s", uid);
  // draw a line
  mvwaddch(box_users, 2, 0, ACS_LTEE);
  mvwhline(box_users, 2, 1, ACS_HLINE, COLS - 63);
  mvwaddch(box_users, 2, COLS - 62, ACS_RTEE);
  wrefresh(box_users);
}

void win_exit(){  // free MENU and exit
  int i;
  unpost_menu(user_list);
  free_menu(user_list);
  for(i = 0; i < n_users; ++i)
    free_item(user_items[i]);
  endwin();
  exit(0);
}

// functions for users[][] and user_list menu

void uoffline(const char * user){
  int i, j;

  for(i = 0; i < n_users; ++i){
      if(!strcmp(users[i], user)){
          for(j = i; j < n_users - 1; ++j)
              strcpy(users[j], users[j + 1]);
        }
    }
  --n_users;
}

void ttolist(char * text){
  int i = 0, j = 0;

  while(text[i] != 0){
      strcpy(users[j++], text + i);
      i += UIDSIZE;
    }
  n_users = j;
}

void set_now_user(char * user){
  now_user = user;
}

void user_list_show(){
  int i;

  unpost_menu(user_list);
  // create new items
  user_items = (ITEM**)calloc(n_users + 1, sizeof(ITEM*));
  for(i = 0; i < n_users; ++i){
      user_items[i] = new_item(users[i], NULL);
      set_item_userptr(user_items[i], set_now_user);
    }
  user_items[n_users] = (ITEM*)NULL;
  // create new menu for user-list
  user_list = new_menu((ITEM**)user_items);
  set_menu_win(user_list, box_users);
  set_menu_sub(user_list, derwin(box_users, LINES - 5, COLS - 63, 3, 1));
  set_menu_mark(user_list, "&");
  set_menu_format(user_list, 5, 1); // scroll

  post_menu(user_list);
  wrefresh(box_users);
}
