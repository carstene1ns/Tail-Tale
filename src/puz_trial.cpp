/* ---------------------------------------------------------- */
/*  puz_trial.c                                               */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_trial.c                                          */
/*     パズルとことんモード                               */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		パズルとことんモード
    @author		K.Kunikane (rerofumi)
    @since		Sep.30.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#include <cstdlib>
#include "debug.hpp"
#include "input.hpp"
#include "sound.hpp"
#include "puz_trial.hpp"
#include "puz_disp.hpp"
#include "puz_base.hpp"
#include "game.hpp"

/* -------------------------------------------------------------- */
/* --- とことんモードパズルクラス                                 */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TPuzzleTrial::TPuzzleTrial(TGame *game, int level) :
  game(game), game_level(level)
{
  /* --- クラスメンバー初期化 */
  step = TrialStep::Init;
  status = true;
  /* --- テクスチャー読み込み */
  LoadTexture();

  /* -- スーパークラスの取得 */
  disp = make_unique<TPuzzleDisp>(GameMode::CHALLENGE, level, game);
}

/* ---------------------------------------- */
/* --- テクスチャーの読み込み               */
/* ---------------------------------------- */
void TPuzzleTrial::LoadTexture()
{
  game->screen->LoadTexture(2, "trial_parts.png");
  game->screen->LoadTexture(8, "chara01_1.png");
}

/* ---------------------------------------- */
/* --- ゲーム実行中かどうかを返すフラグ     */
/* ---------------------------------------- */
bool TPuzzleTrial::GameStat()
{
  if (step == TrialStep::End) return false;

  return true;
}

/* ---------------------------------------- */
/* --- ゲーム本体部分の実行                 */
/* ---------------------------------------- */
void TPuzzleTrial::GameMain()
{
  /* --------------------------------------------- */
  /* --- パズルゲームステップ  */
  switch(step) {
    /* --- ゲーム準備 */
  case TrialStep::Init:
    /* -- ゲームワーク初期化(TPuzzleBase) */
    disp->base->GameInit(1);
    disp->base->GamePause(GamePhase::PAUSE);
    game->sound->MusicOneshot(4);
    readytimer = 0;
    step = TrialStep::Ready;
    break;

    /* --- ゲーム開始 */
  case TrialStep::Ready:
    disp->base->GameExec();
    disp->DispField();
    disp->DispReady(readytimer);
    /* - 一定時間で次へ */
    readytimer = readytimer + 1;
    if (readytimer > (84*2)) {
      game->sound->MusicStop();
      game->sound->Music(3);
      disp->base->GamePause(GamePhase::LINECHECK);
      step = TrialStep::Game;
    }
    break;

    /* --- ゲーム本体 */
  case TrialStep::Game:
    UserControl();
    disp->base->GameExec();
    if (disp->base->LevelCheck()) {
      /* --- レベルアップ時アトラクト */
      disp->base->GameLevel(disp->base->Level);
      ChangeCharacter(disp->base->Level);
      game->sound->SE(2);
      for(int i=0; i<16; i++) {
        disp->KiraRequest(KIRA_REQUEST_X, 152, 80);
      }
    }
    disp->DispField();
    /* - ゲームオーバーで次に */
    if (disp->base->GameOver) {
      game->sound->MusicStop();
      game->sound->SE(7);
      readytimer = 0;
      step = TrialStep::Miss;
    }
    break;

    /* --- 終了 */
  case TrialStep::Miss:
    {
      /* -- ブロックを灰色に */
      int j = (readytimer / 2) + 1;
      for(int i=0; i<FIELD_WIDTH; i++) {
        if (disp->base->Field[j*FIELD_WIDTH + i] != 0) {
          if (disp->base->Field[j*FIELD_WIDTH + i]->Color < 0x10) {
            disp->base->Field[j*FIELD_WIDTH + i]->Color =
              disp->base->Field[j*FIELD_WIDTH + i]->Color + 0x10;
          }
        }
      }
      disp->DispField();
      /* -- */
      readytimer = readytimer + 1;
      if (readytimer == ((FIELD_HEIGHT - 1) * 2)) {
        game->sound->MusicOneshot(1);
        readytimer = 0;
        step = TrialStep::Gameover;
      }
    }
    break;

    /* --- ゲームオーバー */
  case TrialStep::Gameover:
    {
      disp->DispGameover(readytimer);
      int key = game->input->JoyKeyTriger(0);
      readytimer = readytimer + 1;
      if (readytimer > 160) {
        if ((key & (IN_Button1|IN_Button2|IN_Button3|IN_Button4|IN_Button7)) != 0) {
          step = TrialStep::End;
          if (readytimer > 320) {
            game->sound->MusicStop();
            step = TrialStep::End;
          }
        }
      }
    }
    break;

    /* --- パズルクラス終了 */
  case TrialStep::End:
    break;

  }
}

/* ---------------------------------------- */
/* --- ユーザーコントロール                 */
/* ---------------------------------------- */
void TPuzzleTrial::UserControl()
{
  int inp;

  /* --- 入れ替え中は制限 */
  if (disp->base->GameStep == GamePhase::SWAP) {
    return;
  }
  /* --- 入力とホールド */
  disp->base->UA.HaveBlock = false;
  inp = game->input->JoyKeyDown(0);
  if (((inp & (IN_Button1|IN_Button2|IN_Button3|IN_Button4|IN_Button5|IN_Button6)) != 0) && (!disp->base->Animation)) {
    /* -- 現在のカーソル位置にブロックはあるか */
    if (disp->base->Field[disp->base->UA.X + (disp->base->UA.Y * FIELD_WIDTH)] != 0) {
      disp->base->UA.HaveBlock = true;
    }
  }
  /* --- 入力とカーソル移動 */
  inp = game->input->JoyKeyTriger(0);
  if (((inp & IN_Up) != 0) && (disp->base->UA.Y < (FIELD_HEIGHT -1))) {
    if (disp->base->UA.HaveBlock) {
      disp->base->MoveRequest(disp->base->UA.X, disp->base->UA.Y, MoveDir::UP);
    }
    disp->base->UA.Y = disp->base->UA.Y + 1;
  }
  if (((inp & IN_Down) != 0) && (disp->base->UA.Y > 1)) {
    if (disp->base->UA.HaveBlock) {
      disp->base->MoveRequest(disp->base->UA.X, disp->base->UA.Y, MoveDir::DOWN);
    }
    disp->base->UA.Y = disp->base->UA.Y - 1;
  }
  if (((inp & IN_Left) != 0) && (disp->base->UA.X > 0)) {
    if (disp->base->UA.HaveBlock) {
      disp->base->MoveRequest(disp->base->UA.X, disp->base->UA.Y, MoveDir::LEFT);
    }
    disp->base->UA.X = disp->base->UA.X - 1;
  }
  if (((inp & IN_Right) != 0) && (disp->base->UA.X < (FIELD_WIDTH -1))) {
    if (disp->base->UA.HaveBlock) {
      disp->base->MoveRequest(disp->base->UA.X, disp->base->UA.Y, MoveDir::RIGHT);
    }
    disp->base->UA.X = disp->base->UA.X + 1;
  }

}

/* -------------------------------------------------------------- */
/* --- クラスメソッド                                             */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- キャラクター変更                     */
/* ---------------------------------------- */
void TPuzzleTrial::ChangeCharacter(int level)
{
  switch(level) {
  case 6:
    game->screen->LoadTexture(8, "chara01_2.png");
    break;
    
  case 11:
    game->screen->LoadTexture(8, "chara01_3.png");
    break;
    
  case 16:
    game->screen->LoadTexture(8, "chara01_4.png");
    break;
    
  case 21:
    game->screen->LoadTexture(8, "chara01_5.png");
    break;
    
  case 26:
    game->screen->LoadTexture(8, "chara01_6.png");
    break;
  }
}
