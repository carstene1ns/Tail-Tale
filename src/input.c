/* ---------------------------------------------------------- */
/*  input.c                                                   */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   input.c                                              */
/*     入力マネージャ                                     */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		入力マネージャ
    @author		K.Kunikane (rerofumi)
    @since		Jul.27.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include "input.h"
#include <SDL.h>

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/* ----- イベント */
SDL_Event event;

/* ----- ユーザーのゲーム操作 */
SDL_Joystick *JoyPtr[JOY_NUM_MAX];
unsigned long JoyKey[JOY_NUM_MAX];
unsigned long JoyStick[JOY_NUM_MAX];
unsigned long JoyKeyPast[JOY_NUM_MAX];
unsigned long JoyStickPast[JOY_NUM_MAX];

/* ----- ジョイスティックの情報 */
/*  まあ、一応情報として  */
int JoyStickAxes[JOY_NUM_MAX];
int JoyStickButtons[JOY_NUM_MAX];

/* ----- 終了キーフラグ */
int AppExit;

/* ----- GP2X キー設定コンフィギュレーション */
bool GpKeySwap;

/* -------------------------------------------------------------- */
/* --- 入力管理                                                   */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- キーの判別処理                       */
/* ---------------------------------------- */
void key_read_down(SDL_KeyboardEvent *key)
{
  if (key->keysym.sym == SDLK_UP)
    JoyKey[0] = JoyKey[0] | IN_Up;
  if (key->keysym.sym == SDLK_DOWN)
    JoyKey[0] = JoyKey[0] | IN_Down;
  if (key->keysym.sym == SDLK_LEFT)
    JoyKey[0] = JoyKey[0] | IN_Left;
  if (key->keysym.sym == SDLK_RIGHT)
    JoyKey[0] = JoyKey[0] | IN_Right;
#ifdef GCW0
  if (key->keysym.sym == SDLK_LCTRL) //A
    JoyKey[0] = JoyKey[0] | IN_Button1;
  if (key->keysym.sym == SDLK_LALT) //B
    JoyKey[0] = JoyKey[0] | IN_Button2;
#else
  if (key->keysym.sym == SDLK_z)
    JoyKey[0] = JoyKey[0] | IN_Button1;
  if (key->keysym.sym == SDLK_x)
    JoyKey[0] = JoyKey[0] | IN_Button2;
#endif
  if (key->keysym.sym == SDLK_c)
    JoyKey[0] = JoyKey[0] | IN_Button3;
  if (key->keysym.sym == SDLK_v)
    JoyKey[0] = JoyKey[0] | IN_Button4;
  if (key->keysym.sym == SDLK_SPACE)
    JoyKey[0] = JoyKey[0] | IN_Button1;
  if (key->keysym.sym == SDLK_a)
    JoyKey[0] = JoyKey[0] | IN_Button7;
  if (key->keysym.sym == SDLK_s)
    JoyKey[0] = JoyKey[0] | IN_Button8;

  if (key->keysym.sym == SDLK_q)
    AppExit = 1;
  if (key->keysym.sym == SDLK_ESCAPE)
    AppExit = 1;
}

void key_read_up(SDL_KeyboardEvent *key)
{
  if (key->keysym.sym == SDLK_UP)
    JoyKey[0] = JoyKey[0] & (~(IN_Up));
  if (key->keysym.sym == SDLK_DOWN)
    JoyKey[0] = JoyKey[0] & (~(IN_Down));
  if (key->keysym.sym == SDLK_LEFT)
    JoyKey[0] = JoyKey[0] & (~(IN_Left));
  if (key->keysym.sym == SDLK_RIGHT)
    JoyKey[0] = JoyKey[0] & (~(IN_Right));
#ifdef GCW0
  if (key->keysym.sym == SDLK_LCTRL) //A
    JoyKey[0] = JoyKey[0] & (~(IN_Button1));
  if (key->keysym.sym == SDLK_LALT) //B
    JoyKey[0] = JoyKey[0] & (~(IN_Button2));
#else
  if (key->keysym.sym == SDLK_z)
    JoyKey[0] = JoyKey[0] & (~(IN_Button1));
  if (key->keysym.sym == SDLK_x)
    JoyKey[0] = JoyKey[0] & (~(IN_Button2));
#endif
  if (key->keysym.sym == SDLK_c)
    JoyKey[0] = JoyKey[0] & (~(IN_Button3));
  if (key->keysym.sym == SDLK_v)
    JoyKey[0] = JoyKey[0] & (~(IN_Button4));
  if (key->keysym.sym == SDLK_SPACE)
    JoyKey[0] = JoyKey[0] & (~(IN_Button1));
  if (key->keysym.sym == SDLK_a)
    JoyKey[0] = JoyKey[0] & (~(IN_Button7));
  if (key->keysym.sym == SDLK_s)
    JoyKey[0] = JoyKey[0] & (~(IN_Button8));
}

/* ---------------------------------------- */
/* --- ジョイスティックの判別処理           */
/* ---------------------------------------- */
void joy_read_stick(SDL_JoyAxisEvent *stick)
{
  if (stick->which < JOY_NUM_MAX) {
    switch(stick->axis) {
      /* --- 横方向 */
    case 0:
      JoyStick[stick->which] &= (~(IN_Left|IN_Right));
      if (stick->value < (-JOY_STICK_DITHER)) {
        JoyStick[stick->which] = JoyStick[stick->which] | IN_Left;
       }
      if (stick->value > JOY_STICK_DITHER) {
        JoyStick[stick->which] = JoyStick[stick->which] | IN_Right;
      }
      break;

      /* --- 縦方向 */
    case 1:
      JoyStick[stick->which] &= (~(IN_Up|IN_Down));
      if (stick->value < (-JOY_STICK_DITHER)) {
        JoyStick[stick->which] = JoyStick[stick->which] | IN_Up;
       }
      if (stick->value > JOY_STICK_DITHER) {
        JoyStick[stick->which] = JoyStick[stick->which] | IN_Down;
      }
      break;
    }
  }
}


void joy_read_button_up_pc(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == 0) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button1));
    if ((btn->button == 1) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button2));
    if ((btn->button == 2) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button3));
    if ((btn->button == 3) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button4));
    if ((btn->button == 4) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button5));
    if ((btn->button == 5) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button6));
    if ((btn->button == 6) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button7));
    if ((btn->button == 7) && (btn->state == SDL_RELEASED))
      JoyKey[btn->which] = JoyKey[btn->which] & (~(IN_Button8));
  }
}

void joy_read_button_down_pc(SDL_JoyButtonEvent *btn)
{
  if (btn->which < JOY_NUM_MAX) {
    if ((btn->button == 0) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button1;
    if ((btn->button == 1) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button2;
    if ((btn->button == 2) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button3;
    if ((btn->button == 3) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button4;
    if ((btn->button == 4) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button5;
    if ((btn->button == 5) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button6;
    if ((btn->button == 6) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button7;
    if ((btn->button == 7) && (btn->state == SDL_PRESSED))
      JoyKey[btn->which] = JoyKey[btn->which] | IN_Button8;
  }
}

/* ---------------------------------------- */
/* --- 入力装置の初期設定                   */
/* ---------------------------------------- */
void InputInit(void)
{
  GpKeySwap = false;

  for(int i=0; i<JOY_NUM_MAX; i++) {
    JoyPtr[i] = 0;
    JoyStickAxes[i] = 0;
    JoyStickButtons[i] = 0;
    JoyKey[i] = 0;
    JoyStick[i] = 0;
  }
  /* ----- ジョイスティックの存在確認 */
  int JoyNum = SDL_NumJoysticks();
  if (JoyNum > JOY_NUM_MAX) {
    JoyNum = JOY_NUM_MAX;
  }
  for(int i=0; i<(JoyNum + 1); i++) {
    JoyPtr[i] = SDL_JoystickOpen(i);
    if (JoyPtr[i] != NULL) {
      /* --- ジョイスティックの種類をチェック */
      JoyStickAxes[i] = SDL_JoystickNumAxes(JoyPtr[i]);
      JoyStickButtons[i] = SDL_JoystickNumButtons(JoyPtr[i]);
    }
  }
}


/* ---------------------------------------- */
/* --- 入力装置の解放                       */
/* ---------------------------------------- */
void InputFree(void)
{
  /* ----- ジョイスティックの解放 */
  for(int i=0; i<JOY_NUM_MAX; i++) {
    if (JoyPtr[i] != 0) {
      SDL_JoystickClose(JoyPtr[i]);
    }
  }
}


/* ---------------------------------------- */
/* --- キーの定期的読みとり                 */
/* ---------------------------------------- */
void InputPoll(void)
{
  AppExit = 0;

  /* ----- for Triger */
  for(int i=0; i<JOY_NUM_MAX; i++) {
    JoyKeyPast[i] = JoyKey[i];
    JoyStickPast[i] = JoyStick[i];
  }

  /* ----- Key Event Read */
  while(SDL_PollEvent(&event) != 0) {
    switch(event.type) {
    case SDL_KEYUP:
      key_read_up(&event.key);
      break;

    case SDL_KEYDOWN:
      key_read_down(&event.key);
      break;

    case SDL_JOYBUTTONUP:
#ifdef __GP2X__
      if (!GpKeySwap) {
        joy_read_button_up_gp2x(&event.jbutton);
      } else {
        joy_read_button_up_gp2x_rev(&event.jbutton);
      }
#elif defined __PSP__
      joy_read_button_up_psp(&event.jbutton);
#else
      joy_read_button_up_pc(&event.jbutton);
#endif
      break;

    case SDL_JOYBUTTONDOWN:
#ifdef __GP2X__
      if (!GpKeySwap) {
        joy_read_button_down_gp2x(&event.jbutton);
      } else {
        joy_read_button_down_gp2x_rev(&event.jbutton);
      }
#elif defined __PSP__
      joy_read_button_down_psp(&event.jbutton);
#else
      joy_read_button_down_pc(&event.jbutton);
#endif
      break;

    case SDL_JOYAXISMOTION:
      joy_read_stick(&event.jaxis);
      break;

    case SDL_QUIT:
      AppExit = 1;
      break;
    }
  }
}


/* ---------------------------------------- */
/* --- アプリケーション終了キーの判別       */
/* ---------------------------------------- */
int InputExit(void)
{
  return(AppExit);  
}


/* ---------------------------------------- */
/* --- ユーザー入力の読みとり               */
/* ---------------------------------------- */
int InputJoyKey(int side)
{
  int r1, r2;

  r1 = r2 = 0;
  if (side < JOY_NUM_MAX) {
    r1 = JoyKey[side];
    r2 = JoyStick[side];
    r1 |= r2;
  }

  return(r1);
}


/* ---------------------------------------- */
/* --- ユーザー入力のトリガー読みとり       */
/* ---------------------------------------- */
int InputJoyKeyTriger(int side)
{
  int  r1, r2;

  r1 = r2 = 0;
  if (side < JOY_NUM_MAX) {
    r1 = (JoyKey[side] ^ JoyKeyPast[side]) & JoyKey[side];
    r2 = (JoyStick[side] ^ JoyStickPast[side]) & JoyStick[side];
    r1 |= r2;
  }
  return(r1);
}


/* ----------------------------------------------- */
/* --- GP2X 向け、ボタンとスティック入れ替え  */
/* ----------------------------------------------- */
void InputJoyKeySwap(bool sw)
{
  GpKeySwap = sw;
}
