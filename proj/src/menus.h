#include <lcom/lcf.h>


#include "keyboard.h"
#include "mouse.h"
#include "video_gr.h"
#include "Bitmap.h"


typedef struct {
  Bitmap* mainTittle0;
  Bitmap* mainTittle1;

  Bitmap* diffMenu;
  Bitmap* hardBox;
  Bitmap* mediumBox;
  Bitmap* easyBox;

  int difficulty;

  Bitmap* cursor;
  int cursor_x;
  int cursor_y;

  Bitmap* pauseMenu;
  Bitmap* gameOverMenu;

} menus_t;

menus_t startMenus();

int mainTitle(menus_t* menus);

int diffMenu(menus_t* menus);

