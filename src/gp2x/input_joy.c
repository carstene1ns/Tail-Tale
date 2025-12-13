// not finished


/*-------------------------------*/
/* define                        */
/*-------------------------------*/

#define GP2X_BUTTON_UP              (0)
#define GP2X_BUTTON_DOWN            (4)
#define GP2X_BUTTON_LEFT            (2)
#define GP2X_BUTTON_RIGHT           (6)
#define GP2X_BUTTON_UPLEFT          (1)
#define GP2X_BUTTON_UPRIGHT         (7)
#define GP2X_BUTTON_DOWNLEFT        (3)
#define GP2X_BUTTON_DOWNRIGHT       (5)
#define GP2X_BUTTON_CLICK           (18)
#define GP2X_BUTTON_A               (12)
#define GP2X_BUTTON_B               (13)
#define GP2X_BUTTON_X               (14)
#define GP2X_BUTTON_Y               (15)
#define GP2X_BUTTON_L               (10)
#define GP2X_BUTTON_R               (11)
#define GP2X_BUTTON_START           (8)
#define GP2X_BUTTON_SELECT          (9)
#define GP2X_BUTTON_VOLUP           (16)
#define GP2X_BUTTON_VOLDOWN         (17)


void  joy_read_button_down_gp2x(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == GP2X_BUTTON_UP) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Up;
    if ((btn->button == GP2X_BUTTON_DOWN) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Down;
    if ((btn->button == GP2X_BUTTON_LEFT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Left;
    if ((btn->button == GP2X_BUTTON_RIGHT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Right;
    if ((btn->button == GP2X_BUTTON_A) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button1;
    if ((btn->button == GP2X_BUTTON_B) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button2;
    if ((btn->button == GP2X_BUTTON_X) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button3;
    if ((btn->button == GP2X_BUTTON_Y) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button4;
    if ((btn->button == GP2X_BUTTON_L) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button5;
    if ((btn->button == GP2X_BUTTON_R) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button6;
    if ((btn->button == GP2X_BUTTON_START) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button7;
    if ((btn->button == GP2X_BUTTON_SELECT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button8;
    if ((btn->button == GP2X_BUTTON_VOLUP) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button9;
    if ((btn->button == GP2X_BUTTON_VOLDOWN) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button10;
    if ((btn->button == GP2X_BUTTON_CLICK) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button11;
    /* --- slant */
    /* ===== not yet */
  }

  /* --- Exit control */
  if ((JoyKey[btn->which] & (IN_Button5|IN_Button6|IN_Button11)) == (IN_Button5|IN_Button6|IN_Button11))
    AppExit = 1;
}

void  joy_read_button_down_gp2x_rev(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == GP2X_BUTTON_UP) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button4;
    if ((btn->button == GP2X_BUTTON_DOWN) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button3;
    if ((btn->button == GP2X_BUTTON_LEFT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button1;
    if ((btn->button == GP2X_BUTTON_RIGHT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button2;
    if ((btn->button == GP2X_BUTTON_A) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Left;
    if ((btn->button == GP2X_BUTTON_B) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Right;
    if ((btn->button == GP2X_BUTTON_X) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Down;
    if ((btn->button == GP2X_BUTTON_Y) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Up;
    if ((btn->button == GP2X_BUTTON_L) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button5;
    if ((btn->button == GP2X_BUTTON_R) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button6;
    if ((btn->button == GP2X_BUTTON_START) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button7;
    if ((btn->button == GP2X_BUTTON_SELECT) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button8;
    if ((btn->button == GP2X_BUTTON_VOLUP) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button9;
    if ((btn->button == GP2X_BUTTON_VOLDOWN) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button10;
    if ((btn->button == GP2X_BUTTON_CLICK) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | (IN_Button11 | IN_Button1);
    /* --- slant */
    /* ===== not yet */
  }

  /* --- Exit control */
  if ((JoyKey[btn->which] & (IN_Button5|IN_Button6|IN_Button11)) == (IN_Button5|IN_Button6|IN_Button11))
    AppExit = 1;
}


void  joy_read_button_up_gp2x(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == GP2X_BUTTON_UP) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Up));
    if ((btn->button == GP2X_BUTTON_DOWN) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Down));
    if ((btn->button == GP2X_BUTTON_LEFT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Left));
    if ((btn->button == GP2X_BUTTON_RIGHT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Right));
    if ((btn->button == GP2X_BUTTON_A) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button1));
    if ((btn->button == GP2X_BUTTON_B) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button2));
    if ((btn->button == GP2X_BUTTON_X) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button3));
    if ((btn->button == GP2X_BUTTON_Y) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button4));
    if ((btn->button == GP2X_BUTTON_L) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button5));
    if ((btn->button == GP2X_BUTTON_R) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button6));
    if ((btn->button == GP2X_BUTTON_START) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button7));
    if ((btn->button == GP2X_BUTTON_SELECT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button8));
    if ((btn->button == GP2X_BUTTON_VOLUP) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button9));
    if ((btn->button == GP2X_BUTTON_VOLDOWN) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button10));
    if ((btn->button == GP2X_BUTTON_CLICK) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button11));
    /* --- slant */
    /* ===== not yet */
  }
}

void  joy_read_button_up_gp2x_rev(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == GP2X_BUTTON_UP) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button4));
    if ((btn->button == GP2X_BUTTON_DOWN) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button3));
    if ((btn->button == GP2X_BUTTON_LEFT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button1));
    if ((btn->button == GP2X_BUTTON_RIGHT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button2));
    if ((btn->button == GP2X_BUTTON_A) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Left));
    if ((btn->button == GP2X_BUTTON_B) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Right));
    if ((btn->button == GP2X_BUTTON_X) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Down));
    if ((btn->button == GP2X_BUTTON_Y) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Up));
    if ((btn->button == GP2X_BUTTON_L) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button5));
    if ((btn->button == GP2X_BUTTON_R) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button6));
    if ((btn->button == GP2X_BUTTON_START) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button7));
    if ((btn->button == GP2X_BUTTON_SELECT) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button8));
    if ((btn->button == GP2X_BUTTON_VOLUP) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button9));
    if ((btn->button == GP2X_BUTTON_VOLDOWN) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button10));
    if ((btn->button == GP2X_BUTTON_CLICK) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button11|IN_Button1));
    /* --- slant */
    /* ===== not yet */
  }
}
