/* ---------------------------------------------------------- */
/*  gamemain.c                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   gamemain.c                                           */
/*     ゲーム本体のメインフロー                           */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		ゲーム本体ステップ
    @author		K.Kunikane (rerofumi)
    @since		Sep.20.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <stdlib.h>
#include <math.h>
#include "gamemain.h"
#include "input.h"
#include "sound.h"
#include "debug.h"
#include "puz_trial.h"

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/*-------------------------------*/
/* local function                */
/*-------------------------------*/

/* -------------------------------------------------------------- */
/* --- ゲームメインステップ                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGameMain *TGameMain_Create(TGameScreen *mainscreen)
{
  TGameMain *class;

  class = malloc(sizeof(TGameMain));
  if (!class) return NULL;

  class->sound_volume = 96;
  class->control_reverse = 0;

  class->screen = mainscreen;
  class->step = TitleInit;
  class->level = LevelEasy;

  return(class);
}

void TGameMain_Destroy(TGameMain *class)
{
  if (!class) return;
  /* インスタンスの解放 */
  free(class);
}


/* ---------------------------------------- */
/* --- ゲームメイン                         */
/* ---------------------------------------- */
bool TGameMain_Poll(TGameMain *class, int counter)
{
  int  i;
  TGameSprite  *sp;

  if (!class) return false;

  bool skip = true;

  /* -------------------------------- */
  /* --- ボリュームコントロール */
  // TODO: volume control?

  /* -------------------------------- */
  /* --- ゲームメインステップ */
  
  switch(class->step) {

    /* -- タイトル初期化 */
  case TitleInit:
    TGameScreen_LoadTexture(class->screen, 0, "title_320.png");
    class->bg = TGameScreen_GetSprite(class->screen, 0);
    class->logo = TGameScreen_GetSprite(class->screen, 1);
    class->push = TGameScreen_GetSprite(class->screen, 2);
    class->release = TGameScreen_GetSprite(class->screen, 3);
    class->select_level = TGameScreen_GetSprite(class->screen, 4);
    class->bg->DispSw = true;
    class->bg->x = 0;
    class->bg->y = 0;
    class->bg->w = 320;
    class->bg->h = 240;
    class->bg->tx = 0;
    class->bg->ty = 0;
    class->bg->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->bg->alpha = 255;
    class->logo->DispSw = false;
    class->logo->x = 0;
    class->logo->y = 0;
    class->logo->w = 300;
    class->logo->h = 84;
    class->logo->tx = 0;
    class->logo->ty = 240;
    class->logo->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->logo->alpha = 255;
    class->push->DispSw = false;
    class->push->x = 40;
    class->push->y = 180;
    class->push->w = 240;
    class->push->h = 23;
    class->push->tx = 0;
    class->push->ty = 325;
    class->push->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->push->alpha = 255;
    class->release->DispSw = false;
    class->release->x = 40;
    class->release->y = 210;
    class->release->w = 240;
    class->release->h = 10;
    class->release->tx = 0;
    class->release->ty = 349;
    class->release->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->release->alpha = 255;
    class->select_level->DispSw = false;
    class->select_level->x = 160-40;
    class->select_level->y = 160;
    class->select_level->w = 80;
    class->select_level->h = 18;
    class->select_level->tx = 300;
    class->select_level->ty = 240 + (24 * class->level);
    class->select_level->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->select_level->alpha = 255;
    class->titletimer = 0;
    class->step = TitleIn;
    skip = false;
    break;

    /* -- タイトルロゴフレームイン */
  case TitleIn:
    /* - SE */
    if (class->titletimer == 15*2) SoundSE(1);
    if (class->titletimer > 20*2) {
      /* はずむ */
      class->logo->x = 10;
      class->logo->y = 120 - (int)(sin(3.1415926 * 2.0 * (((float)class->titletimer - 40.0) / 120.0)) * 120.0);
      class->logo->DispSw = true;
    }
    else {
      /* 上から降ってくる */
      class->logo->x = 10;
      class->logo->y = 120 - ((40 - class->titletimer) * 10);
      class->logo->DispSw = true;
    }
    /* -- 次へ進むステップ */
    class->titletimer = class->titletimer + 1;
    if (class->titletimer == 38*2) {
      SoundSE(6);
    }
    if (class->titletimer == 45*2) {
      SoundMusic(2);
      class->step = TitleMain;
    }
    i = InputJoyKeyTriger(0);
    if ((i & IN_Button1) != 0) {
      SoundMusic(2);
      class->step = TitleMain;
    }
    break;

    /* -- スタートボタン待ち */
  case TitleMain:
    class->logo->DispSw = true;
    class->logo->x = 10;
    class->logo->y = 60;
    class->release->DispSw = true;
    class->select_level->DispSw = true;
    if (((class->titletimer / 8) % 2) == 1) {
      class->push->DispSw = true;
    }
    else {
      class->push->DispSw = false;
    }
    class->titletimer = class->titletimer + 1;
    i = InputJoyKeyTriger(0);
    if ((i & (IN_Button1|IN_Button2|IN_Button3|IN_Button4|IN_Button7)) != 0) {
      SoundSE(2);
      class->titletimer = 0;
      class->step = TitleStart;
    }
    if (i & IN_Button8) {
      class->step = ConfigInit;
    }
    /* レベルセレクト */
    if ((i & IN_Left) != 0) {
      class->level ^= LevelHard;
    }
    if ((i & IN_Right) != 0) {
      class->level ^= LevelHard;
    }
    class->select_level->ty = 240 + (24 * class->level);
    break;

    /* -- スタート時アトラクト */
  case TitleStart:
    class->logo->DispSw = true;
    class->logo->x = 10;
    class->logo->y = 60;
    class->release->DispSw = true;
    if ((class->titletimer % 2) == 1) {
      class->push->DispSw = true;
    }
    else {
      class->push->DispSw = false;
    }
    class->titletimer = class->titletimer + 1;
    if (class->titletimer == 20) {
      SoundMusicStop();
      class->step = TitleFree;
    }
    break;

    /* -- タイトルロゴ後しまつ */
  case TitleFree:
    srand(counter);
    class->bg->DispSw = false;
    class->logo->DispSw = false;
    class->push->DispSw = false;
    class->release->DispSw = false;
    class->select_level->DispSw = false;
    class->step = PuzzleInit;
    break;


    /* -- ゲーム初期化 */
  case PuzzleInit:
    class->puzzle = TPuzzleTrial_Create(class->screen, class->level);
    class->step = PuzzleMain;
    skip = false;
    break;

    /* -- ゲームメイン */
  case PuzzleMain:
    TPuzzleTrial_GameMain(class->puzzle);
    if (!TPuzzleTrial_GameStat(class->puzzle)) {
      class->step = PuzzleFree;
    }
    break;

    /* -- ゲーム終了後しまつ */
    case PuzzleFree:
      TPuzzleTrial_Destroy(class->puzzle);
      for( i=0; i<SPRITEMAX; i++) {
        sp = TGameScreen_GetSprite(class->screen, i);
        sp->DispSw = false;
      }
      class->step = TitleInit;
      break;

    /* -- GP2X キーコンフィグ */
  case ConfigInit:
    TGameScreen_LoadTexture(class->screen, 0, "control.png");
    class->bg = TGameScreen_GetSprite(class->screen, 0);
    class->push = TGameScreen_GetSprite(class->screen, 2);
    class->bg->DispSw = true;
    class->bg->x = 0;
    class->bg->y = 0;
    class->bg->w = 320;
    class->bg->h = 240;
    class->bg->tx = 0;
    class->bg->ty = 0;
    class->bg->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->bg->alpha = 255;
    class->push->DispSw = true;
    class->push->x = 0;
    class->push->y = 48;
    class->push->w = 320;
    class->push->h = 112;
    class->push->tx = 0;
    class->push->ty = 240 + 112*(class->control_reverse ^ 1);
    class->push->Texture = TGameScreen_GetTexture(class->screen, 0);
    class->push->alpha = 255;
    class->logo->DispSw = false;
    class->release->DispSw = false;
    class->select_level->DispSw = false;
    class->control_anime = 0;
    class->control_anime_y = 112*(class->control_reverse ^ 1);
    class->step = ConfigMain;
    break;

    /* -- GP2X キーコンフィグ選択中 */
  case ConfigMain:
    if (class->control_anime != 0) {
      class->control_anime_y += class->control_anime;
      class->push->ty = 240 + class->control_anime_y;
      if ((class->control_anime_y <= 0) ||
        (class->control_anime_y >= 112)) {
        class->control_anime = 0;
      }
    }
    else {
      i = InputJoyKeyTriger(0);
      if ((i & (IN_Button8)) != 0) {
        SoundSE(6);
        class->control_reverse ^= 1;
        if (class->control_reverse == 0) {
          class->control_anime = 8;
        }
        else {
          class->control_anime = -8;
        }
      }
      if ((i & (IN_Button7)) != 0) {
        SoundSE(2);
        class->step = ConfigFree;
      }
    }
    break;

    /* -- GP2X キーコンフィグ終了 */
  case ConfigFree:
    InputJoyKeySwap(class->control_reverse);
    class->step = TitleInit;
    break;


  } // switch

  return skip;
}
