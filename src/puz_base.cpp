/* ---------------------------------------------------------- */
/*  puz_base.c                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_base.c                                           */
/*     スプライト管理構造体                               */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		スプライト管理
    @author		K.Kunikane (rerofumi)
    @since		Sep.23.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#include <cstdlib>
#include "debug.hpp"
#include "sound.hpp"
#include "puz_base.hpp"
#include "game.hpp"

namespace {
  /*-------------------------------*/
  /* data table                    */
  /*-------------------------------*/

  int SwapTable[5] = { 0, 6, 4, 0, 0 };
  int BlockColorSet[7] = { 0, 5, 1, 3, 4, 2, 6 };

  /* --- 難易度設定 */
  int LevelColor_hard[30] = {
    3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
    5, 5, 5, 5, 5, 6, 6, 6, 7, 7  };

  int LevelColor_normal[30] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 5, 5, 5, 5, 5, 5, 5, 6, 6  };

  int LevelColor_easy[30] = {
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 5, 5, 5  };


  int LevelSpeed_easy[30] = {
    240, 220, 220, 200, 200,
    200, 200, 240, 220, 220,
    200, 200, 200, 180, 180,
    160, 160, 200, 200, 180,
    180, 160, 160, 140, 180,
    160, 140, 140, 130, 120 };

  int LevelSpeed_normal[30] = {
    220, 220, 200, 200, 200,
    180, 180, 220, 220, 200,
    200, 180, 180, 180, 180,
    160, 160, 200, 180, 180,
    180, 160, 140, 120, 180,
    140, 140, 120, 120, 100 };

  int LevelSpeed_hard[30] = {
    220, 200, 180, 160, 160,
    140, 140, 200, 200, 180,
    180, 180, 160, 160, 140,
    140, 120, 180, 160, 140,
    140, 120, 120, 100, 140,
    120, 120, 100, 100,  80 };

  /* UNUSED
  int  LevelColor_veryhard[30] = {
    3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 5, 5,
    5, 5, 5, 5, 5, 6, 6, 6, 7, 7  };

  int  LevelSpeed_veryhard[30] = {
    220, 180, 180, 160, 160,
    160, 140, 200, 180, 160,
    160, 160, 140, 140, 140,
    120, 100, 160, 140, 120,
    120, 100, 100,  80, 140,
    120, 120, 100, 100,  80 };
  */

  int LevelBlock[30] = {
    0,  30,  60, 100, 150,
    200, 250, 300, 350, 400,
    500, 550, 600, 650, 700,
    900, 950,1000,1050,1100,
    1300,1350,1400,1450,1500,
    1800,1950,2100,2300,2500 };
}

/* -------------------------------------------------------------- */
/* --- テクスチャ管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TPuzzleBase::TPuzzleBase(TGame *game, int difficult) :
  sound(game->sound), Difficult(difficult)
{
  /* --- 確保できたら初期化 */
  for(int i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    Field[i] = 0;
  }
}

/* ---------------------------------------- */
/* --- ワークの全初期化                     */
/* ---------------------------------------- */
void TPuzzleBase::GameInit(int col)
{
  int i;

  /* --- フィールド配列クリア */
  for(i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    Field[i] = 0;
  }
  /* --- ブロック情報初期化 */
  for(i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    Item[i].Color = 0;
    Item[i].LineCheck = false;
    Item[i].LineBlock = false;
    Item[i].LineTimer = 0;
    Item[i].PopupTimer = 0;
    Item[i].PopupOffset = 0;
    Item[i].DropCheck = false;
    Item[i].DropTimer = 0;
    Item[i].DropOffset = 0;
    Item[i].SwapSide = SwapFlag::NONE;
    Item[i].SwapTimer = 0;
    Item[i].SwapOffsetX = 0;
    Item[i].SwapOffsetY = 0;
  }
  GameStep = GamePhase::PAUSE;
  Animation = false;
  CharaColor = col;
  Level = 1;
  ColorNum = 3;
  NextInterval = 150;
  NextTimer = 0;
  EraseBlock = 0;
  EraseScore = 0;
  Score = 0;
  Combo = 1;
  GameOver = false;
  GameLevel(Level);
  /* --- ブロックカラー */
  for(i=0; i<7; i++) {
    BlockColor[i] = BlockColorSet[i];
  }
  /* --- 初期ブロック */
  SetBlock();
  /* --- カーソル位置 */
  UA.X = 4;
  UA.Y = 4;
  UA.SwapTimer = 0;
  UA.SwapOffsetX = 0;
  UA.SwapOffsetY = 0;
  UA.PopupTimer = 0;
  UA.PopupOffset = 0;
  UA.HaveBlock = false;
}

/* ---------------------------------------- */
/* --- パズルゲームデータベースメイン       */
/* ---------------------------------------- */
void TPuzzleBase::GameExec()
{
  int watch;

  switch(GameStep) {
    /* --- 先に進まない停止状態 */
  case GamePhase::PAUSE:
    NextTimer = NextInterval;
    break;

    /* --- 通常待ち受け状態 */
  case GamePhase::NORMAL:
    Animation = false;
    Combo = 1;
    if (PopupWork()) {
      GameStep = GamePhase::LINECHECK;
    }
    break;

    /* --- ユーザーによるブロック移動要求 */
  case GamePhase::SWAP:
    PopupWork();
    if (!MoveWork()) {
      if (DropRequest()) {
        GameStep = GamePhase::DROPWORK;
      }
      else {
        watch = LineCheck();
        if (watch > 0) {
          EraseBlock = EraseBlock + watch; 
          EraseScore = ((watch - 3) * 10 * Combo) * 4;
          Score = Score + EraseScore;
          sound->SE(5);
          GameStep = GamePhase::LINEFLASH;
        }
        else {
          GameStep = GamePhase::DROPCHECK;
        }
      }
    }
    break;

    /* --- 動かした後落下を伴うか */
  case GamePhase::DROPCHECK:
    if (DropRequest()) {
      GameStep = GamePhase::DROPWORK;
    }
    else {
      GameStep = GamePhase::LINECHECK;
    }
    break;

    /* --- 落下中処理 */
  case GamePhase::DROPWORK:
    Animation = true;
    PopupWork();
    if (!DropWork()) {
      GameStep = GamePhase::LINECHECK;
    }
    break;

    /* --- 揃ったブロックがあるかどうかのチェック */
  case GamePhase::LINECHECK:
    watch = LineCheck();
    if (watch > 0) {
      EraseBlock = EraseBlock + watch;
      EraseScore = ((watch - 3) * 10 * Combo) * 4;
      Score = Score + EraseScore;
      sound->SE(5);
      GameStep = GamePhase::LINEFLASH;
    }
    else {
      GameStep = GamePhase::NORMAL;
    }
    break;

    /* --- ライン揃い時のブロック点滅アニメーション */
  case GamePhase::LINEFLASH:
    Animation = true;
    PopupWork();
    if (!LineWork()) {
      Combo = Combo + 1;
      GameStep = GamePhase::DROPCHECK;
    }
    break;

    /* --- 終了時 */
  case GamePhase::END:
    break;

  default:
    break;
  }
}

/* ---------------------------------------- */
/* --- ゲームステップの指定                 */
/* ---------------------------------------- */
void TPuzzleBase::GamePause(GamePhase mode)
{
  GameStep = mode;
}

/* ---------------------------------------- */
/* --- ゲームレベルの指定                   */
/* ---------------------------------------- */
void TPuzzleBase::GameLevel(int lset)
{
  /* -- レベルに合わせて難易度設定 */
  int l = lset - 1;
  if (l < 0) {
    l = 0;
  }
  if (l > 29) {
    l = 29;
  }
  /* 変化するのはこの二つ */
  switch(Difficult) {
  case LevelEasy:
    ColorNum = LevelColor_easy[l];
    NextInterval = LevelSpeed_easy[l] * 2;
    break;

  case LevelNormal:
    ColorNum = LevelColor_normal[l];
    NextInterval = LevelSpeed_normal[l] * 2;
    break;

  case LevelHard:
    ColorNum = LevelColor_hard[l];
    NextInterval = LevelSpeed_hard[l] * 2;
    break;
  }
}

/* ---------------------------------------- */
/* --- 現在のゲームレベル                   */
/*     レベル変更で true                    */
/* ---------------------------------------- */
bool TPuzzleBase::LevelCheck()
{
  int lv = 0;
  for(int i=0; i<30; i++) {
    if (LevelBlock[i] < EraseBlock) {
      lv = i;
    }
  }
  if (lv == Level) {
    Level = Level + 1;
    return true;
  }
  return false;
}

/* ---------------------------------------- */
/* --- ブロックの入れ替えを行う             */
/* ---------------------------------------- */
bool TPuzzleBase::MoveRequest(int posx, int posy, MoveDir dir)
{
  Block *master, *target;

  /* --- カーソル位置にブロックが無いならスキップ */
  if (Field[posx + (posy * FIELD_WIDTH)] == 0)
    return false;

  /* --- 壁方向へ移動しようとしていたらエラー */
  if ((posx == 0) && (dir == MoveDir::LEFT)) 
    return false;

  if ((posx == (FIELD_WIDTH - 1)) && (dir == MoveDir::RIGHT))
    return false;

  if ((posy == 1) && (dir == MoveDir::DOWN))
    return false;

  if ((posy == (FIELD_HEIGHT - 1)) && (dir == MoveDir::UP))
    return false;

  if ((Field[posx + ((posy - 1) * FIELD_WIDTH)] == 0) &&
      (dir == MoveDir::UP))
    return false;

  /* ---------------------------------------------- */
  /* --- 移動リクエスト  */
  if (dir == MoveDir::UP) {
    master = Field[posx + (posy * FIELD_WIDTH)];
    target = Field[posx + ((posy + 1) * FIELD_WIDTH)];
    if (target != 0) {
      Field[posx + ((posy + 1) * FIELD_WIDTH)] = master;
      Field[posx + (posy * FIELD_WIDTH)] = target;
      master->SwapSide = SwapFlag::MASTER;
      master->SwapTimer = 3;
      master->SwapOffsetX = 0;
      master->SwapOffsetY = -BLOCK_HEIGHT;
      master->LineCheck = true;
      if (target != 0) {
        target->SwapSide = SwapFlag::SLAVE;
        target->SwapTimer = 3;
        target->SwapOffsetX = 0;
        target->SwapOffsetY = -BLOCK_HEIGHT;
        target->LineCheck = true;
      }
      UA.SwapTimer = 3;
      UA.SwapOffsetX = 0;
      UA.SwapOffsetY = BLOCK_HEIGHT;
    }
  }
  if (dir == MoveDir::DOWN) {
    master = Field[posx + (posy * FIELD_WIDTH)];
    target = Field[posx + ((posy - 1) * FIELD_WIDTH)];
    Field[posx + ((posy - 1) * FIELD_WIDTH)] = master;
    Field[posx + (posy * FIELD_WIDTH)] = target;
    master->SwapSide = SwapFlag::MASTER;
    master->SwapTimer = 3;
    master->SwapOffsetX = 0;
    master->SwapOffsetY = -BLOCK_HEIGHT;
    master->LineCheck = true;
    if (target != 0) {
      target->SwapSide = SwapFlag::SLAVE;
      target->SwapTimer = 3;
      target->SwapOffsetX = 0;
      target->SwapOffsetY = BLOCK_HEIGHT;
      target->LineCheck = true;
    }
    UA.SwapTimer = 3;
    UA.SwapOffsetX = 0;
    UA.SwapOffsetY = -BLOCK_HEIGHT;
  }
  if (dir == MoveDir::LEFT) {
    master = Field[posx + (posy * FIELD_WIDTH)];
    target = Field[posx - 1 + (posy * FIELD_WIDTH)];
    Field[posx - 1 + (posy * FIELD_WIDTH)] = master;
    Field[posx + (posy * FIELD_WIDTH)] = target;
    master->SwapSide = SwapFlag::MASTER;
    master->SwapTimer = 3;
    master->SwapOffsetX = BLOCK_WIDTH;
    master->SwapOffsetY = 0;
    master->LineCheck = true;
    if (target != 0) {
      target->SwapSide = SwapFlag::SLAVE;
      target->SwapTimer = 3;
      target->SwapOffsetX = -BLOCK_WIDTH;
      target->SwapOffsetY = 0;
      target->LineCheck = true;
    }
    UA.SwapTimer = 3;
    UA.SwapOffsetX = BLOCK_WIDTH;
    UA.SwapOffsetY = 0;
  }
  if (dir == MoveDir::RIGHT) {
    master = Field[posx + (posy * FIELD_WIDTH)];
    target = Field[posx + 1 + (posy * FIELD_WIDTH)];
    Field[posx + 1 + (posy * FIELD_WIDTH)] = master;
    Field[posx + (posy * FIELD_WIDTH)] = target;
    master->SwapSide = SwapFlag::MASTER;
    master->SwapTimer = 3;
    master->SwapOffsetX = -BLOCK_WIDTH;
    master->SwapOffsetY = 0;
    master->LineCheck = true;
    if (target != 0) {
      target->SwapSide = SwapFlag::SLAVE;
      target->SwapTimer = 3;
      target->SwapOffsetX = BLOCK_WIDTH;
      target->SwapOffsetY = 0;
      target->LineCheck = true;
    }
    UA.SwapTimer = 3;
    UA.SwapOffsetX = -BLOCK_WIDTH;
    UA.SwapOffsetY = 0;
  }

  /* - 移動完了 */
  GameStep = GamePhase::SWAP;

  return true;
}

/* -------------------------------------------------------------- */
/* --- クラスメソッド                                             */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- ブロック初期パターン                 */
/* ---------------------------------------- */
void TPuzzleBase::SetBlock()
{
  /* --- フィールド配列クリア */
  for(int i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    Field[i] = 0;
  }
  /* --- スタート時に色が揃っていないように */
  /* == 取り敢えず後回し (^^; */
  /* --- 初期ブロックを置く */
  for(int i=0; i<(FIELD_WIDTH * 4); i++) {
    Field[i] = GetBlock();
    Field[i]->Color = GetBlockColor() + 1;
    Field[i]->LineCheck = true;
    Field[i]->LineBlock = false;
  }
}

/* ---------------------------------------- */
/* --- 空いているブロックを返す             */
/* ---------------------------------------- */
Block *TPuzzleBase::GetBlock()
{
  Block *b = 0;
  for(int i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (Item[i].Color == 0) {
      b = &(Item[i]);
      break;
    }
  }
  return b;
}

/* ---------------------------------------- */
/* --- 難易度に対し適切なブロックカラーを設定 */
/* ---------------------------------------- */
int TPuzzleBase::GetBlockColor()
{
  /* - ブロックカラーはランダム */
  /* === いずれはアイテム混ぜの調整など */
  int c = rand() % ColorNum;
  /* - おわり */
  return BlockColor[c];
}

/* ---------------------------------------- */
/* --- ネクストブロックの迫り上がりと次準備 */
/* ---------------------------------------- */
void TPuzzleBase::PopupNext()
{
  int i, pos;

  /* --- フィールド内ブロックの持ち上げ */
  for(i=0; i<(FIELD_WIDTH * (FIELD_HEIGHT - 1)); i++) {
    pos = FIELD_WIDTH * FIELD_HEIGHT - 1 - i;
    Field[pos] = Field[pos - FIELD_WIDTH];
    if (Field[pos] != 0) {
      Field[pos]->PopupTimer = 4;
      Field[pos]->PopupOffset = 24;
    }
  }
  /* --- ネクストブロックの準備 */
  for(i=0; i<FIELD_WIDTH; i++) {
    Field[i] = 0;
    Field[i] = GetBlock();
    Field[i]->Color = GetBlockColor() + 1;
    Field[i]->PopupTimer = 4;
    Field[i]->PopupOffset = BLOCK_HEIGHT;
    Field[i]->LineCheck = true;
  }
  /* --- つかみアクションの途中であったらカーソルも移動 */
  if (UA.HaveBlock) {
    UA.Y = UA.Y + 1;
    UA.PopupTimer = 4;
    UA.PopupOffset = BLOCK_HEIGHT;
  }
}

/* -------------------------------------------- */
/* --- ネクストの迫り上がりカウントとオフセット */
/* -------------------------------------------- */
bool TPuzzleBase::PopupWork()
{
  bool r = false;
  /* --- せり上がりオフセット */
  for(int i=0; i<ALL_BLOCK; i++) {
    if (Item[i].Color != 0) {
      if (Item[i].PopupTimer != 0) {
        Item[i].PopupTimer = Item[i].PopupTimer - 1;
        Item[i].PopupOffset = Item[i].PopupOffset - 6;
        if ((Item[i].PopupOffset < 0) ||
          (Item[i].PopupTimer == 0)) {
          Item[i].PopupOffset = 0;
          r = true;
        }
      }
    }
  }
  if (UA.PopupTimer > 0) {
    UA.PopupTimer = UA.PopupTimer - 1;
    UA.PopupOffset = UA.PopupOffset - 6;
    if ((UA.PopupOffset < 0) ||
      (UA.PopupTimer == 0)) {
      UA.PopupOffset = 0;
    }
  }
  /* --- ネクスト迫り上がりまでのtimer */
  if (NextTimer > 0) {
    NextTimer = NextTimer - 1;
  }
  if ((NextTimer == 0) && 
      (GameStep == GamePhase::NORMAL)) {
    NextTimer = NextInterval;
    /* -- ゲームオーバー判定 */
    if (FieldHeight() == 0) {
      GameOver = true;
    }
    else {
      /* -- ネクスト迫り上がり */
      PopupNext();
    }
  }
  /* -- SE */
  if (NextTimer == 10) {
    sound->SE(8);
  }
  /* --- せりあがり処理終了 */
  return r;
}

/* -------------------------------------------- */
/* --- フィールド内の最高位ブロックの位置を返す */
/* -------------------------------------------- */
int TPuzzleBase::FieldHeight()
{
  int r = 0;
  for(int i=0; i<FIELD_HEIGHT; i++) {
    bool hit = false;
    for(int j=0; j<FIELD_WIDTH; j++) {
      if (Field[(((FIELD_HEIGHT - 1) - i) * FIELD_WIDTH) + j] != 0) {
        hit = true;
      }
    }
    if (hit) {
      r = i;
      break;
    }
  }
  /* - 戻り値 */
  return r;
}

/* -------------------------------------------- */
/* --- フィールド内の最高位ブロックの位置を返す */
/* -------------------------------------------- */
bool TPuzzleBase::MoveWork()
{
  bool working = false;
  /* --- フィールド内ブロックの移動 */
  for(int i=FIELD_WIDTH; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (Field[i] != 0) {
      if (Field[i]->SwapTimer > 0) {
        Field[i]->SwapTimer = Field[i]->SwapTimer - 1;
        if (Field[i]->SwapTimer == 0) {
          Field[i]->SwapSide = SwapFlag::NONE;
          Field[i]->SwapOffsetX = 0;
          Field[i]->SwapOffsetY = 0;
        }
        else {
          Field[i]->SwapOffsetX = Field[i]->SwapOffsetX % 2;
          Field[i]->SwapOffsetY = Field[i]->SwapOffsetY % 2;
          if (Field[i]->SwapSide == SwapFlag::SLAVE) {
            Field[i]->SwapOffsetY = Field[i]->SwapOffsetY + SwapTable[Field[i]->SwapTimer];
          }
          working = true;
        }
      }
    }
  }
  /* --- カーソルの移動 */
  if (UA.SwapTimer > 0) {
    UA.SwapTimer = UA.SwapTimer - 1;
    if (UA.SwapTimer == 0) {
      UA.SwapOffsetX = 0;
      UA.SwapOffsetY = 0;
    }
    else {
      UA.SwapOffsetX = UA.SwapOffsetX % 2;
      UA.SwapOffsetY = UA.SwapOffsetY % 2;
    }
  }
  /* - おしまい */
  return working;
}

/* -------------------------------------------- */
/* --- 落下ブロックの判定と落下リクエスト       */
/* -------------------------------------------- */
bool TPuzzleBase::DropRequest()
{
  int position, t;
  Block *b;

  bool working = false;
  for(int i=FIELD_WIDTH; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (Field[i] != 0) {
      if (Field[i - FIELD_WIDTH] == 0) {
        working = true;
        /* -- 下に無いのでどこまで落ちるかサーチ */
        position = i - FIELD_WIDTH;
        t = 0;
        do {
          if (Field[position] != 0) break;
          position = position - FIELD_WIDTH;
          t = t + 1;
        } while(!(position < FIELD_WIDTH));
        /* -- 落下設定 */
        position = position + FIELD_WIDTH;
        b = Field[i];
        b->LineCheck = true;
        b->DropCheck = true;
        b->DropTimer = 2 * t;
        b->DropOffset = 24 * t;
        Field[position] = b;
        Field[i] = 0;
      }
    }
  }
  return working;
}

/* -------------------------------------------- */
/* --- ブロックの落下                           */
/* -------------------------------------------- */
bool TPuzzleBase::DropWork()
{
  bool working = false;
  for(int i=FIELD_WIDTH; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (Field[i] != 0) {
      if (Field[i]->DropTimer > 0) {
        working = true;
        Field[i]->DropTimer = Field[i]->DropTimer - 1;
        if (Field[i]->DropTimer == 0) {
          Field[i]->DropOffset = 0;
        }
        else {
          Field[i]->DropOffset = Field[i]->DropOffset - 12;
        }
      }
    }
  }
  /* - おしまい */
  return working;
}

/* -------------------------------------------- */
/* --- ブロック揃いのチェック                   */
/* -------------------------------------------- */
int TPuzzleBase::LineCheck()
{
  int working = 0;
  for(int j=1; j<FIELD_HEIGHT; j++) {
    for(int i=0; i<FIELD_WIDTH; i++) {
      if (Field[(j * FIELD_WIDTH) + i] != 0) {
        if (Field[(j * FIELD_WIDTH) + i]->LineCheck) {
          Field[(j * FIELD_WIDTH) + i]->LineCheck = false;
          working = working + LineCount(i, j, 1, 0, 0);
          working = working + LineCount(i, j, 0, 1, 0);
        }
      }
    }
  }
  /* --- おしまい */
  return working;
}

/* -------------------------------------------- */
/* --- ブロックが揃って消えるエフェクト         */
/* -------------------------------------------- */
bool TPuzzleBase::LineWork()
{
  bool working = false;
  bool playSound = false;
  for(int i=FIELD_WIDTH;i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (Field[i] != 0) {
      if (Field[i]->LineTimer > 0) {
        if (Field[i]->LineTimer == 10) {
          playSound = true;
        }
        working = true;
        Field[i]->LineTimer = Field[i]->LineTimer - 1;
        if (Field[i]->LineTimer == 0) {
          Field[i]->Color = 0;
          Field[i]->LineBlock = false;
          Field[i]->LineCheck = false;
          Field[i] = 0;
        }
      }
    }
  }
  if (playSound) {
    sound->SE(6);
  }
  /* - おしまい */
  return working;
}

/* -------------------------------------------- */
/* --- ブロック揃いのカウント                   */
/* -------------------------------------------- */
int TPuzzleBase::LineCount(int x, int y, int dx, int dy, int layer)
{
  int  col, nextcol;
  int  score, ready;

  score = 0;
  ready = 0;
  col = Field[x + (y * FIELD_WIDTH)]->Color;
  if (Field[x + (y * FIELD_WIDTH)]->LineBlock) {
    ready = ready + 1;
  }
  do {
    if (layer == 2) {
      if (Field[x + (y * FIELD_WIDTH)] != 0) {
        Field[x + (y * FIELD_WIDTH)]->LineBlock = true;
        Field[x + (y * FIELD_WIDTH)]->LineTimer = 15;
      }
    }
    x = x + dx;
    y = y + dy;
    if ((x < 0) || (x >= FIELD_WIDTH) || (y < 1) || (y >= FIELD_HEIGHT)) {
      nextcol = 0;
    }
    else {
      if (Field[x + (y * FIELD_WIDTH)] != 0) {
        nextcol = Field[x + (y * FIELD_WIDTH)]->Color;
      }
      else {
        nextcol = 0;
      }
    }
    score = score + 1;
    if (col == nextcol) {
      if (Field[x + (y * FIELD_WIDTH)] != 0) {
        if (Field[x + (y * FIELD_WIDTH)]->LineBlock) {
          ready = ready + 1;
        }
      }
    }
  } while(!((x < 0) || (x >= FIELD_WIDTH) || (y < 1) || (y >= FIELD_HEIGHT) ||
    (col != nextcol)));
  x = x - dx;
  y = y - dy;

  /* --- 次レイヤへ */
  switch(layer) {
  case 0:
    score = LineCount(x, y, -dx, -dy, 1);
    break;
    
  case 1:
    if ((score >= LINE_LENGTH) && (score > ready)) {
      score = LineCount(x, y, -dx, -dy, 2);
    }
    else {
      score = 0;
    }
    break;
    
  case 2:
    score = score - ready;
    break;

  }

  return score;
}
