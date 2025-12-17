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

#include <cstdlib>
#include <math.h>
#include "game.hpp"
#include "input.hpp"
#include "sound.hpp"
#include "debug.hpp"
#include "puz_trial.hpp"
#include "puz_disp.hpp"
#include "puz_base.hpp"

/* -------------------------------------------------------------- */
/* --- ゲームメインステップ                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGame::TGame(TGameScreen *scr, TSound *snd, TInput *inp) :
  screen(scr), sound(snd), input(inp)
{
  sound_volume = 96;
  control_reverse = 0;

  step = Step::TitleInit;
  level = LevelEasy;
}

/* ---------------------------------------- */
/* --- ゲームメイン                         */
/* ---------------------------------------- */
bool TGame::Poll(int counter)
{
  TGameSprite *sp;
  bool skip = true;

  /* -------------------------------- */
  /* --- ボリュームコントロール */
  // TODO: volume control?

  /* -------------------------------- */
  /* --- ゲームメインステップ */
  
  switch(step) {

    /* -- タイトル初期化 */
  case Step::TitleInit:
    screen->LoadTexture(0, "title.png");
    bg = screen->GetSprite(0);
    bg->DispSw = true;
    bg->x = 0;
    bg->y = 0;
    bg->w = SCREEN_WIDTH;
    bg->h = SCREEN_HEIGHT;
    bg->tx = 0;
    bg->ty = 0;
    bg->Texture = screen->GetTexture(0);
    bg->alpha = 255;

    logo = screen->GetSprite(1);
    logo->DispSw = false;
    logo->x = 0;
    logo->y = 0;
    logo->w = LOGO_RECT_W;
    logo->h = LOGO_RECT_H;
    logo->tx = 0;
    logo->ty = SCREEN_HEIGHT;
    logo->Texture = screen->GetTexture(0);
    logo->alpha = 255;

    push = screen->GetSprite(2);
    push->DispSw = false;
    push->x = PUSH_RECT_X;
    push->y = PUSH_RECT_Y;
    push->w = PUSH_RECT_W;
    push->h = PUSH_RECT_H;
    push->tx = 0;
    push->ty = SCREEN_HEIGHT+LOGO_RECT_H;
    push->Texture = screen->GetTexture(0);
    push->alpha = 255;

    release = screen->GetSprite(3);
    release->DispSw = false;
    release->x = RELEASE_RECT_X;
    release->y = RELEASE_RECT_Y;
    release->w = RELEASE_RECT_W;
    release->h = RELEASE_RECT_H;
    release->tx = 0;
    release->ty = SCREEN_HEIGHT+LOGO_RECT_H+PUSH_RECT_H + 2;
    release->Texture = screen->GetTexture(0);
    release->alpha = 255;

    select_level = screen->GetSprite(4);
    select_level->DispSw = false;
    select_level->x = SELECT_RECT_X;
    select_level->y = SELECT_RECT_Y;
    select_level->w = SELECT_RECT_W;
    select_level->h = SELECT_RECT_H;
    select_level->tx = LOGO_RECT_W + 1;
    select_level->ty = SCREEN_HEIGHT + (((4/3.f)*SELECT_RECT_H) * level);
    select_level->Texture = screen->GetTexture(0);
    select_level->alpha = 255;

    titletimer = 0;
    step = Step::TitleIn;
    skip = false;
    break;

    /* -- タイトルロゴフレームイン */
  case Step::TitleIn:
    /* - SE */
    if (titletimer == 15*2) {
      sound->SE(1);
    }
    if (titletimer > 20*2) {
      /* はずむ */
      logo->x = LOGO_RECT_X;
      logo->y = 120 - (int)(sin(3.1415926 * 2.0 * (((float)titletimer - 40.0) / 120.0)) * 120.0);
      logo->DispSw = true;
    }
    else {
      /* 上から降ってくる */
      logo->x = LOGO_RECT_X;
      logo->y = 120 - ((40 - titletimer) * 10);
      logo->DispSw = true;
    }
    /* -- 次へ進むステップ */
    titletimer = titletimer + 1;
    if (titletimer == 38*2) {
      sound->SE(6);
    }
    if (titletimer == 45*2) {
      sound->Music(2);
      step = Step::TitleMain;
    }
    if ((input->JoyKeyTriger(0) & IN_Button1) != 0) {
      sound->Music(2);
      step = Step::TitleMain;
    }
    break;

    /* -- スタートボタン待ち */
  case Step::TitleMain:
    {
      logo->DispSw = true;
      logo->x = LOGO_RECT_X;
      logo->y = 60;
      release->DispSw = true;
      select_level->DispSw = true;
      if (((titletimer / 8) % 2) == 1) {
        push->DispSw = true;
      }
      else {
        push->DispSw = false;
      }
      titletimer = titletimer + 1;
      int key = input->JoyKeyTriger(0);
      if ((key & (IN_Button1|IN_Button2|IN_Button3|IN_Button4|IN_Button7)) != 0) {
        sound->SE(2);
        titletimer = 0;
        step = Step::TitleStart;
      }
      if (key & IN_Button8) {
        step = Step::ConfigInit;
      }
      /* レベルセレクト */
      if ((key & IN_Left) != 0) {
        level ^= LevelHard;
      }
      if ((key & IN_Right) != 0) {
        level ^= LevelHard;
      }
    }
    select_level->ty = SCREEN_HEIGHT + (((4/3.f)*SELECT_RECT_H) * level);
    break;

    /* -- スタート時アトラクト */
  case Step::TitleStart:
    logo->DispSw = true;
    logo->x = LOGO_RECT_X;
    logo->y = 60;
    release->DispSw = true;
    if ((titletimer % 2) == 1) {
      push->DispSw = true;
    }
    else {
      push->DispSw = false;
    }
    titletimer = titletimer + 1;
    if (titletimer == 20) {
      sound->MusicStop();
      step = Step::TitleFree;
    }
    break;

    /* -- タイトルロゴ後しまつ */
  case Step::TitleFree:
    srand(counter);
    bg->DispSw = false;
    logo->DispSw = false;
    push->DispSw = false;
    release->DispSw = false;
    select_level->DispSw = false;
    step = Step::PuzzleInit;
    break;

    /* -- ゲーム初期化 */
  case Step::PuzzleInit:
    puzzle = make_unique<TPuzzleTrial>(this, level);
    step = Step::PuzzleMain;
    skip = false;
    break;

    /* -- ゲームメイン */
  case Step::PuzzleMain:
    puzzle->GameMain();
    if (!puzzle->GameStat()) {
      step = Step::PuzzleFree;
    }
    break;

    /* -- ゲーム終了後しまつ */
    case Step::PuzzleFree:
      puzzle.reset();
      for(int i=0; i<SPRITEMAX; i++) {
        sp = screen->GetSprite(i);
        sp->DispSw = false;
      }
      step = Step::TitleInit;
      break;

    /* -- GP2X キーコンフィグ */
  case Step::ConfigInit:
    screen->LoadTexture(0, "control.png");

    bg = screen->GetSprite(0);
    bg->DispSw = true;
    bg->x = 0;
    bg->y = 0;
    bg->w = 320;
    bg->h = 240;
    bg->tx = 0;
    bg->ty = 0;
    bg->Texture = screen->GetTexture(0);
    bg->alpha = 255;

    push = screen->GetSprite(2);
    push->DispSw = true;
    push->x = 0;
    push->y = 48;
    push->w = 320;
    push->h = 112;
    push->tx = 0;
    push->ty = 240 + 112*(control_reverse ^ 1);
    push->Texture = screen->GetTexture(0);
    push->alpha = 255;

    logo->DispSw = false;
    release->DispSw = false;
    select_level->DispSw = false;
    control_anime = 0;
    control_anime_y = 112*(control_reverse ^ 1);
    step = Step::ConfigMain;
    break;

    /* -- GP2X キーコンフィグ選択中 */
  case Step::ConfigMain:
    if (control_anime != 0) {
      control_anime_y += control_anime;
      push->ty = 240 + control_anime_y;
      if ((control_anime_y <= 0) ||
        (control_anime_y >= 112)) {
        control_anime = 0;
      }
    }
    else {
      int key = input->JoyKeyTriger(0);
      if ((key & (IN_Button8)) != 0) {
        sound->SE(6);
        control_reverse ^= 1;
        if (control_reverse == 0) {
          control_anime = 8;
        }
        else {
          control_anime = -8;
        }
      }
      if ((key & (IN_Button7)) != 0) {
        sound->SE(2);
        step = Step::ConfigFree;
      }
    }
    break;

    /* -- GP2X キーコンフィグ終了 */
  case Step::ConfigFree:
    input->JoyKeySwap(control_reverse);
    step = Step::TitleInit;
    break;


  } // switch

  return skip;
}
