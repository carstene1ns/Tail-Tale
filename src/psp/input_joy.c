// not finished


void  joy_read_button_down_psp(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    /* △ */
    if ((btn->button == 0) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button3;
    /* ○ */
    if ((btn->button == 1) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button1;
    /* × */
    if ((btn->button == 2) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button2;
    /* □ */
    if ((btn->button == 3) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button4;
    /* L */
    if ((btn->button == 4) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button5;
    /* R */
    if ((btn->button == 5) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button6;
    /* ↓ */
    if ((btn->button == 6) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Down;
    /* ← */
    if ((btn->button == 7) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Left;
    /* ↑ */
    if ((btn->button == 8) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Up;
    /* → */
    if ((btn->button == 9) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Right;
  }
}

void  joy_read_button_up_psp(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    /* △ */
    if ((btn->button == 0) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button3));
    /* ○ */
    if ((btn->button == 1) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button1));
    /* × */
    if ((btn->button == 2) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button2));
    /* □ */
    if ((btn->button == 3) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button4));
    /* L */
    if ((btn->button == 4) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button5));
    /* R */
    if ((btn->button == 5) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button6));
    /* ↓ */
    if ((btn->button == 6) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Down));
    /* ← */
    if ((btn->button == 7) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Left));
    /* ↑ */
    if ((btn->button == 8) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Up));
    /* → */
    if ((btn->button == 9) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Right));
  }
}
