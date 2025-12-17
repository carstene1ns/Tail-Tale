/* ---------------------------------------------------------- */
/*  puz_disp.c                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_disp.c                                           */
/*     パズル画面表示管理                                 */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		パズル画面表示管理
    @author		K.Kunikane (rerofumi)
    @since		Sep.24.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#include <cstdlib>
#include "debug.hpp"
#include "puz_base.hpp"
#include "puz_disp.hpp"
#include "game.hpp"

namespace {
  /*-------------------------------*/
  /* data table                    */
  /*-------------------------------*/

  constexpr int animekoma_x[8] = {
    0, 0, 0, 0, 0, 1, 0, 1
  };
  constexpr int animekoma_y[8] = {
    0, 0, 0, 0, 0, 0, CHARA_SIZE, 0
  };

  constexpr int disp_sin[360] = {
    0x8000,0x823b,0x8477,0x86b2,0x88ed,0x8b27,0x8d61,0x8f99,
    0x91d0,0x9406,0x963a,0x986c,0x9a9c,0x9ccb,0x9ef7,0xa120,
    0xa348,0xa56c,0xa78d,0xa9ac,0xabc7,0xaddf,0xaff3,0xb203,
    0xb40f,0xb618,0xb81c,0xba1c,0xbc17,0xbe0e,0xbfff,0xc1ec,
    0xc3d4,0xc5b6,0xc793,0xc96a,0xcb3c,0xcd08,0xcecd,0xd08d,
    0xd246,0xd3f9,0xd5a6,0xd74b,0xd8ea,0xda82,0xdc13,0xdd9c,
    0xdf1f,0xe09a,0xe20d,0xe379,0xe4dd,0xe639,0xe78d,0xe8d9,
    0xea1d,0xeb59,0xec8c,0xedb7,0xeed9,0xeff3,0xf104,0xf20c,
    0xf30b,0xf401,0xf4ef,0xf5d3,0xf6ad,0xf77f,0xf847,0xf906,
    0xf9bc,0xfa68,0xfb0a,0xfba3,0xfc32,0xfcb8,0xfd33,0xfda5,
    0xfe0e,0xfe6c,0xfec1,0xff0b,0xff4c,0xff83,0xffb0,0xffd3,
    0xffec,0xfffb,0xffff,0xfffb,0xffec,0xffd3,0xffb0,0xff83,
    0xff4c,0xff0b,0xfec1,0xfe6c,0xfe0e,0xfda5,0xfd33,0xfcb8,
    0xfc32,0xfba3,0xfb0a,0xfa68,0xf9bc,0xf906,0xf847,0xf77f,
    0xf6ad,0xf5d3,0xf4ef,0xf401,0xf30b,0xf20c,0xf104,0xeff3,
    0xeed9,0xedb7,0xec8c,0xeb59,0xea1d,0xe8d9,0xe78d,0xe639,
    0xe4dd,0xe379,0xe20d,0xe09a,0xdf1f,0xdd9c,0xdc13,0xda82,
    0xd8ea,0xd74b,0xd5a6,0xd3f9,0xd246,0xd08d,0xcecd,0xcd08,
    0xcb3c,0xc96a,0xc793,0xc5b6,0xc3d4,0xc1ec,0xc000,0xbe0e,
    0xbc17,0xba1c,0xb81c,0xb618,0xb40f,0xb203,0xaff3,0xaddf,
    0xabc7,0xa9ac,0xa78d,0xa56c,0xa348,0xa120,0x9ef7,0x9ccb,
    0x9a9c,0x986c,0x963a,0x9406,0x91d0,0x8f99,0x8d61,0x8b27,
    0x88ed,0x86b2,0x8477,0x823b,0x8000,0x7dc5,0x7b89,0x794e,
    0x7713,0x74d9,0x729f,0x7067,0x6e30,0x6bfa,0x69c6,0x6794,
    0x6564,0x6335,0x6109,0x5ee0,0x5cb8,0x5a94,0x5873,0x5654,
    0x5439,0x5222,0x500d,0x4dfd,0x4bf1,0x49e8,0x47e4,0x45e4,
    0x43e9,0x41f2,0x4001,0x3e14,0x3c2c,0x3a4a,0x386d,0x3696,
    0x34c4,0x32f8,0x3133,0x2f73,0x2dba,0x2c07,0x2a5a,0x28b5,
    0x2716,0x257e,0x23ed,0x2264,0x20e1,0x1f66,0x1df3,0x1c87,
    0x1b23,0x19c7,0x1873,0x1727,0x15e3,0x14a7,0x1374,0x1249,
    0x1127,0x100d,0x0efc,0x0df4,0x0cf5,0x0bff,0x0b11,0x0a2d,
    0x0953,0x0881,0x07b9,0x06fa,0x0644,0x0598,0x04f6,0x045d,
    0x03ce,0x0348,0x02cd,0x025b,0x01f2,0x0194,0x013f,0x00f5,
    0x00b4,0x007d,0x0050,0x002d,0x0014,0x0005,0x0001,0x0005,
    0x0014,0x002d,0x0050,0x007d,0x00b4,0x00f5,0x013f,0x0194,
    0x01f2,0x025b,0x02cd,0x0348,0x03ce,0x045d,0x04f6,0x0598,
    0x0644,0x06fa,0x07b9,0x0881,0x0953,0x0a2d,0x0b11,0x0bff,
    0x0cf5,0x0df4,0x0efc,0x100d,0x1127,0x1249,0x1374,0x14a7,
    0x15e3,0x1727,0x1873,0x19c7,0x1b23,0x1c87,0x1df3,0x1f66,
    0x20e1,0x2263,0x23ed,0x257e,0x2716,0x28b5,0x2a5a,0x2c07,
    0x2dba,0x2f73,0x3133,0x32f8,0x34c4,0x3696,0x386d,0x3a4a,
    0x3c2c,0x3e14,0x4000,0x41f2,0x43e9,0x45e4,0x47e4,0x49e8,
    0x4bf1,0x4dfd,0x500d,0x5221,0x5439,0x5654,0x5873,0x5a94,
    0x5cb8,0x5ee0,0x6109,0x6335,0x6564,0x6794,0x69c6,0x6bfa,
    0x6e30,0x7067,0x729f,0x74d9,0x7713,0x794e,0x7b89,0x7dc5,
  };

  constexpr int disp_cos[360] = {
    0x0000,0xfffb,0xffec,0xffd3,0xffb0,0xff83,0xff4c,0xff0b,
    0xfec1,0xfe6c,0xfe0e,0xfda5,0xfd33,0xfcb8,0xfc32,0xfba3,
    0xfb0a,0xfa68,0xf9bc,0xf906,0xf847,0xf77f,0xf6ad,0xf5d3,
    0xf4ef,0xf401,0xf30b,0xf20c,0xf104,0xeff3,0xeed9,0xedb7,
    0xec8c,0xeb59,0xea1d,0xe8d9,0xe78d,0xe639,0xe4dd,0xe379,
    0xe20d,0xe09a,0xdf1f,0xdd9c,0xdc13,0xda82,0xd8ea,0xd74b,
    0xd5a6,0xd3f9,0xd246,0xd08d,0xcecd,0xcd08,0xcb3c,0xc96a,
    0xc793,0xc5b6,0xc3d4,0xc1ec,0xc000,0xbe0e,0xbc17,0xba1c,
    0xb81c,0xb618,0xb40f,0xb203,0xaff3,0xaddf,0xabc7,0xa9ac,
    0xa78d,0xa56c,0xa348,0xa120,0x9ef7,0x9ccb,0x9a9c,0x986c,
    0x963a,0x9406,0x91d0,0x8f99,0x8d61,0x8b27,0x88ed,0x86b2,
    0x8477,0x823b,0x8000,0x7dc5,0x7b89,0x794e,0x7713,0x74d9,
    0x729f,0x7067,0x6e30,0x6bfa,0x69c6,0x6794,0x6564,0x6335,
    0x6109,0x5ee0,0x5cb8,0x5a94,0x5873,0x5654,0x5439,0x5222,
    0x500d,0x4dfd,0x4bf1,0x49e8,0x47e4,0x45e4,0x43e9,0x41f2,
    0x4001,0x3e14,0x3c2c,0x3a4a,0x386d,0x3696,0x34c4,0x32f8,
    0x3133,0x2f73,0x2dba,0x2c07,0x2a5a,0x28b5,0x2716,0x257e,
    0x23ed,0x2264,0x20e1,0x1f66,0x1df3,0x1c87,0x1b23,0x19c7,
    0x1873,0x1727,0x15e3,0x14a7,0x1374,0x1249,0x1127,0x100d,
    0x0efc,0x0df4,0x0cf5,0x0bff,0x0b11,0x0a2d,0x0953,0x0881,
    0x07b9,0x06fa,0x0644,0x0598,0x04f6,0x045d,0x03ce,0x0348,
    0x02cd,0x025b,0x01f2,0x0194,0x013f,0x00f5,0x00b4,0x007d,
    0x0050,0x002d,0x0014,0x0005,0x0001,0x0005,0x0014,0x002d,
    0x0050,0x007d,0x00b4,0x00f5,0x013f,0x0194,0x01f2,0x025b,
    0x02cd,0x0348,0x03ce,0x045d,0x04f6,0x0598,0x0644,0x06fa,
    0x07b9,0x0881,0x0953,0x0a2d,0x0b11,0x0bff,0x0cf5,0x0df4,
    0x0efc,0x100d,0x1127,0x1249,0x1374,0x14a7,0x15e3,0x1727,
    0x1873,0x19c7,0x1b23,0x1c87,0x1df3,0x1f66,0x20e1,0x2264,
    0x23ed,0x257e,0x2716,0x28b5,0x2a5a,0x2c07,0x2dba,0x2f73,
    0x3133,0x32f8,0x34c4,0x3696,0x386d,0x3a4a,0x3c2c,0x3e14,
    0x4000,0x41f2,0x43e9,0x45e4,0x47e4,0x49e8,0x4bf1,0x4dfd,
    0x500d,0x5221,0x5439,0x5654,0x5873,0x5a94,0x5cb8,0x5ee0,
    0x6109,0x6335,0x6564,0x6794,0x69c6,0x6bfa,0x6e30,0x7067,
    0x729f,0x74d9,0x7713,0x794e,0x7b89,0x7dc5,0x8000,0x823b,
    0x8477,0x86b2,0x88ed,0x8b27,0x8d61,0x8f99,0x91d0,0x9406,
    0x963a,0x986c,0x9a9c,0x9ccb,0x9ef7,0xa120,0xa348,0xa56c,
    0xa78d,0xa9ac,0xabc7,0xadde,0xaff3,0xb203,0xb40f,0xb618,
    0xb81c,0xba1c,0xbc17,0xbe0e,0xbfff,0xc1ec,0xc3d4,0xc5b6,
    0xc793,0xc96a,0xcb3c,0xcd08,0xcecd,0xd08d,0xd246,0xd3f9,
    0xd5a6,0xd74b,0xd8ea,0xda82,0xdc13,0xdd9c,0xdf1f,0xe09a,
    0xe20d,0xe379,0xe4dd,0xe639,0xe78d,0xe8d9,0xea1d,0xeb59,
    0xec8c,0xedb7,0xeed9,0xeff3,0xf104,0xf20c,0xf30b,0xf401,
    0xf4ef,0xf5d3,0xf6ad,0xf77f,0xf847,0xf906,0xf9bc,0xfa68,
    0xfb0a,0xfba3,0xfc32,0xfcb8,0xfd33,0xfda5,0xfe0e,0xfe6c,
    0xfec1,0xff0b,0xff4c,0xff83,0xffb0,0xffd3,0xffec,0xfffb,
  };
}

/* -------------------------------------------------------------- */
/* --- テクスチャ管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TPuzzleDisp::TPuzzleDisp(GameMode mode, int level, TGame *game) :
  puz_mode(mode), screen(game->screen)
{
  int i, j;
  int objstep;

  j = 0;
  objstep = 0;
  /* ------------------------------------- */

  /* ----- 初期化あれこれ */
  disptimer = 0;
  /* --- モードによってフィールド表示位置が違う */
  switch(mode) {

  case GameMode::CHALLENGE:
    fieldpos_x = FIELD_POS_X;
    objstep = 0;
    j = 0;
    break;

  case GameMode::MODE1P:
    fieldpos_x = 0;
    objstep = 0;
    j = 0;
    break;

  case GameMode::MODE2P:
    fieldpos_x = 240;
    objstep = 1;
    j = 1;
    break;
  }

  /* ------------------------------------- */
  /* ----- 画面表示初期化 */
  for(i=0; i<TEXMAX; i++) {
    texture[i] = screen->GetTexture(2+j+(i*2)+objstep);
  }
  for(i=0; i<OBJMAX; i++) {
    obj[i] = screen->GetSprite(1+j+(i*2)+objstep);
  }
  for(i=0; i<KIRAMAX; i++) {
    kirakira[i].DispSw = false;
    kirakira[i].obj = obj[128+i];
  }
  tanuki[0].y = 400;
  tanuki[1].y = 500;
  tanuki[2].y = 600;
  tanuki[3].y = 700;
  tanuki[0].x = rand() % (BLOCK_WIDTH*FIELD_WIDTH-60);
  tanuki[1].x = rand() % (BLOCK_WIDTH*FIELD_WIDTH-60);
  tanuki[2].x = rand() % (BLOCK_WIDTH*FIELD_WIDTH-60);
  tanuki[3].x = rand() % (BLOCK_WIDTH*FIELD_WIDTH-60);

  /* -- スーパークラスの取得 */
  base = make_unique<TPuzzleBase>(game, level);
}

TPuzzleDisp::~TPuzzleDisp()
{
  /* --- オブジェを消しておく */
  for(int i=0; i<OBJMAX; i++) {
    obj[i]->DispSw = false;
  }
}

/* ---------------------------------------- */
/* --- 表示リクエスト                       */
/* ---------------------------------------- */
void TPuzzleDisp::DispField()
{
  disptimer += 1;
  /* ------------------------------------- */
  /* ----- 背景の表示 */
  DispBack();
  /* ------------------------------------- */
  /* ----- ブロックの表示 */
  DispBlock();
  /* ------------------------------------- */
  /* ----- カーソルの表示 */
  DispCursor();
  /* ------------------------------------- */
  /* ----- キャラクターの表示 */
  DispChara();
  /* ------------------------------------- */
  /* ----- NEXT の表示 */
  DispNext();
  /* ------------------------------------- */
  /* ----- スコア類の表示 */
  DispScore();
  /* ------------------------------------- */
  /* ----- きらきらエフェクトの表示 */
  DispKira();
}


/* ---------------------------------------- */
/* --- Ready-Go! の表示                     */
/* ---------------------------------------- */
void TPuzzleDisp::DispReady(int time)
{
  if (time < 15*2) {
    /* -- Ready せりあがり */
    obj[160]->DispSw = true;
    obj[160]->x = fieldpos_x + 8;
    obj[160]->y = 160 + (15 - (time/2)) * 20;
    obj[160]->w = 170;
    obj[160]->h = 44;
    obj[160]->tx = 192;
    obj[160]->ty = READY_RECT_TY;
    obj[160]->Texture = texture[0];
    obj[160]->alpha = 255;
  }
  else if (time < 38*2) {
    /* -- Ready */
    obj[160]->DispSw = true;
    obj[160]->x = fieldpos_x + 8;
    obj[160]->y = 160;
    obj[160]->w = 170;
    obj[160]->h = 44;
    obj[160]->tx = 192;
    obj[160]->ty = READY_RECT_TY;
    obj[160]->Texture = texture[0];
    obj[160]->alpha = 255;
  }
  else if (time < 75*2) {
    /* -- Go!! */
    obj[160]->DispSw = true;
    obj[160]->x = fieldpos_x + 40;
    obj[160]->y = 160;
    obj[160]->w = 114;
    obj[160]->h = 44;
    obj[160]->tx = 192;
    obj[160]->ty = BOXES_TY+45;
    obj[160]->Texture = texture[0];
    obj[160]->alpha = 255;
    /* - スパークエフェクト */
    if (time == 38*2) {
      for(int i=0; i<KIRAMAX; i++) {
        KiraRequest(fieldpos_x + 40 + 57, 160+22, 200);
      }
    }
  }
  else {
    /* -- 消す */
    obj[160]->DispSw = false;
  }
}

/* ---------------------------------------- */
/* --- GAMEOVER の表示                      */
/* ---------------------------------------- */
void TPuzzleDisp::DispGameover(int time)
{
  int mx, my;
  int home;

  time /= 2;
  home = GAMEOVER_X;
  /* -- G */
  if (time > 40) {
    mx = home;
    my = GAMEOVER_Y;
  }
  else {
    mx = home + (40 - time) * 12;
    my = GAMEOVER_Y + ((disp_sin[(360 * (40 - time) / 20) % 360] - 0x8000) * (40 - time) * 6) / 0x8000;
  }
  obj[160]->DispSw = true;
  obj[160]->x = mx;
  obj[160]->y = my;
  obj[160]->w = 38;
  obj[160]->h = 52;
  obj[160]->tx = 0 + 192;
  obj[160]->ty = 90 + BOXES_TY;
  obj[160]->Texture = texture[0];
  obj[160]->alpha = 255;
  /* -- A */
  if (time > 45) {
    mx = home + 38;
    my = GAMEOVER_Y;
  }
  else {
    mx = home + 38 + (45 - time) * 12;
    my = GAMEOVER_Y + ((disp_sin[(360 * (45 - time) / 20 + 7) % 360] - 0x8000) * (45 - time) * 6) / 0x8000;
  }
  obj[161]->DispSw = true;
  obj[161]->x = mx;
  obj[161]->y = my;
  obj[161]->w = 37;
  obj[161]->h = 52;
  obj[161]->tx = 38 + 192;
  obj[161]->ty = 90 + BOXES_TY;
  obj[161]->Texture = texture[0];
  obj[161]->alpha = 255;
  /* -- M */
  if (time > 50) {
    mx = home + 75;
    my = GAMEOVER_Y;
  }
  else {
    mx = home + 75 + (50 - time) * 12;
    my = GAMEOVER_Y + ((disp_sin[(360 * (50 - time) / 20 + 2) % 360] - 0x8000) * (50 - time) * 6) / 0x8000;
  }
  obj[162]->DispSw = true;
  obj[162]->x = mx;
  obj[162]->y = my;
  obj[162]->w = 55;
  obj[162]->h = 52;
  obj[162]->tx = 75 + 192;
  obj[162]->ty = 90 + BOXES_TY;
  obj[162]->Texture = texture[0];
  obj[162]->alpha = 255;
  /* -- E */
  if (time > 55) {
    mx = home + 130;
    my = GAMEOVER_Y;
  }
  else {
    mx = home + 130 + (55 - time) * 12;
    my = GAMEOVER_Y + ((disp_sin[(360 * (55 - time) / 20 + 6) % 360] - 0x8000) * (55 - time) * 6) / 0x8000;
  }
  obj[163]->DispSw = true;
  obj[163]->x = mx;
  obj[163]->y = my;
  obj[163]->w = 31;
  obj[163]->h = 52;
  obj[163]->tx = 130 + 192;
  obj[163]->ty = 90 + BOXES_TY;
  obj[163]->Texture = texture[0];
  obj[163]->alpha = 255;
  /* -- O */
  if (time > 60) {
    mx = home + 161 - 161;
    my = GAMEOVER_Y + 80;
  }
  else {
    mx = home + 161 - 161 + (60 - time) * 12;
    my = GAMEOVER_Y + 80 + ((disp_sin[(360 * (60 - time) / 20 + 4) % 360] - 0x8000) * (60 - time) * 6) / 0x8000;
  }
  obj[164]->DispSw = true;
  obj[164]->x = mx;
  obj[164]->y = my;
  obj[164]->w = 45;
  obj[164]->h = 52;
  obj[164]->tx = 161 + 192;
  obj[164]->ty = 90 + BOXES_TY;
  obj[164]->Texture = texture[0];
  obj[164]->alpha = 255;
  /* -- V */
  if (time > 65) {
    mx = home + 206 - 161;
    my = GAMEOVER_Y + 80;
  }
  else {
    mx = home + 206 - 161 + (65 - time) * 12;
    my = GAMEOVER_Y + 80 + ((disp_sin[(360 * (65 - time) / 20 + 2) % 360] - 0x8000) * (65 - time) * 6) / 0x8000;
  }
  obj[165]->DispSw = true;
  obj[165]->x = mx;
  obj[165]->y = my;
  obj[165]->w = 36;
  obj[165]->h = 52;
  obj[165]->tx = 206 + 192;
  obj[165]->ty = 90 + BOXES_TY;
  obj[165]->Texture = texture[0];
  obj[165]->alpha = 255;
  /* -- E */
  if (time > 70) {
    mx = home + 242 - 161;
    my = GAMEOVER_Y + 80;
  }
  else {
    mx = home + 242 - 161 + (70 - time) * 12;
    my = GAMEOVER_Y + 80 + ((disp_sin[(360 * (70 - time) / 20 + 6) % 360] - 0x8000) * (70 - time) * 6) / 0x8000;
  }
  obj[166]->DispSw = true;
  obj[166]->x = mx;
  obj[166]->y = my;
  obj[166]->w = 32;
  obj[166]->h = 52;
  obj[166]->tx = 242 + 192;
  obj[166]->ty = 90 + BOXES_TY;
  obj[166]->Texture = texture[0];
  obj[166]->alpha = 255;
  /* -- R */
  if (time > 75) {
    mx = home + 274 - 161;
    my = GAMEOVER_Y + 80;
  }
  else {
    mx = home + 274 - 161 + (75 - time) * 12;
    my = GAMEOVER_Y + 80 + ((disp_sin[(360 * (75 - time) / 20 + 1) % 360] - 0x8000) * (75 - time) * 6) / 0x8000;
  }
  obj[167]->DispSw = true;
  obj[167]->x = mx;
  obj[167]->y = my;
  obj[167]->w = 34;
  obj[167]->h = 52;
  obj[167]->tx = 274 + 192;
  obj[167]->ty = 90 + BOXES_TY;
  obj[167]->Texture = texture[0];
  obj[167]->alpha = 255;

}

/* ---------------------------------------- */
/* --- オブジェクトの消去                   */
/* ---------------------------------------- */
void TPuzzleDisp::DispClear()
{
  /* --- オブジェを消しておく */
  for(int i=0; i<OBJMAX; i++) {
    obj[i]->DispSw = false;
  }
}

/* ---------------------------------------- */
/* --- キラキラエフェクトのリクエスト       */
/* ---------------------------------------- */
void TPuzzleDisp::KiraRequest(int x, int y, int l)
{
  int j;
  bool hit = false;
  /* -- 空きエフェクトを探す */
  for(int i=0; i<KIRAMAX; i++) {
    if (!kirakira[i].DispSw) {
      hit = true;
      j = i;
      break;
    }
  }
  /* -- リクエスト */
  if (hit) {
    kirakira[j].DispSw = true;
    kirakira[j].timer = 0;
    kirakira[j].timer_end = 22;
    kirakira[j].x = x * 0x10000;
    kirakira[j].y = y * 0x10000;
    kirakira[j].dx = (disp_cos[(rand()%360)] - 0x8000) * (l / 15.0);
    kirakira[j].dy = (disp_sin[(rand()%360)] - 0x8000) * (l / 15.0);
  }
}

/* -------------------------------------------------------------- */
/* --- クラスメソッド                                             */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- 手のひらカーソルの表示               */
/* ---------------------------------------- */
void TPuzzleDisp::DispCursor()
{
  /* ----- ハンドカーソル */
  int x = fieldpos_x + (base->UA.X * BLOCK_WIDTH) + 4;
  int y = FIELDTOP + ((FIELD_HEIGHT - base->UA.Y - 1) * BLOCK_WIDTH) + 4;
  obj[122]->DispSw = true;
  obj[122]->x = x + base->UA.SwapOffsetX;
  obj[122]->y = y + base->UA.SwapOffsetY + base->UA.PopupOffset;
  obj[122]->w = BLOCK_WIDTH;
  obj[122]->h = BLOCK_HEIGHT;
  if (!base->UA.HaveBlock) {
    obj[122]->tx = 24 * 2;
  }
  else {
    obj[122]->tx = 24 * 3;
  }
  obj[122]->ty = (24 * 2)+BOXES_TY;
  obj[122]->Texture = texture[0];
  obj[122]->alpha = 255;
  /* ----- つかみブロック枠 */
  if (base->UA.HaveBlock) {
    x = fieldpos_x + (base->UA.X * BLOCK_WIDTH);
    y = FIELDTOP + ((FIELD_HEIGHT - base->UA.Y - 1) * BLOCK_WIDTH);
    obj[121]->DispSw = true;
    obj[121]->x = x + base->UA.SwapOffsetX;
    obj[121]->y = y + base->UA.SwapOffsetY + base->UA.PopupOffset;
    obj[121]->w = BLOCK_WIDTH;
    obj[121]->h = BLOCK_HEIGHT;
    if ((disptimer % 2) == 0) {
      obj[121]->tx = 24 * 0;
    }
    else {
      obj[121]->tx = 24 * 1;
    }
    obj[121]->ty = (24 * 2)+BOXES_TY;
    obj[121]->Texture = texture[0];
    obj[121]->alpha = 255;
  }
  else {
    obj[121]->DispSw = false;
  }
}

/* ---------------------------------------- */
/* --- ブロック群の表示                     */
/* ---------------------------------------- */
void TPuzzleDisp::DispBlock()
{
  int i;
  int colx, coly;
  int x, y;

  for(i=0; i<(FIELD_WIDTH * FIELD_HEIGHT); i++) {
    if (base->Field[i] != 0) {
      if (base->Field[i]->Color != 0) {
        if (base->Field[i]->Color >= 0x10) {
          colx = ((base->Field[i]->Color - 0x10) - 1) * BLOCK_WIDTH;
          coly = BLOCK_HEIGHT;
        }
        else {
          colx = (base->Field[i]->Color - 1) * BLOCK_WIDTH;
          coly = 0;
        }
        x = ((i % FIELD_WIDTH) * BLOCK_WIDTH);
        if ((i / FIELD_WIDTH) == 0) {
          y = ((FIELD_HEIGHT - 1) - (i / FIELD_WIDTH)) * BLOCK_HEIGHT + 4 + FIELDTOP;
        }
        else {          
          y = ((FIELD_HEIGHT - 1) - (i / FIELD_WIDTH)) * BLOCK_HEIGHT + FIELDTOP;
        }
        obj[10+i]->DispSw = true;
        obj[10+i]->x = x + base->Field[i]->SwapOffsetX + fieldpos_x;
        obj[10+i]->y = y + base->Field[i]->SwapOffsetY + base->Field[i]->PopupOffset - base->Field[i]->DropOffset;
        obj[10+i]->w = BLOCK_WIDTH;
        obj[10+i]->h = BLOCK_HEIGHT;
        obj[10+i]->tx = colx;
        obj[10+i]->ty = coly + BOXES_TY;
        obj[10+i]->Texture = texture[0];
        obj[10+i]->alpha = 255;
        /* --- 消えエフェクト中か */
        if (base->Field[i]->LineTimer > 0) {
          DispEraseBlock(obj[10+i], base->Field[i]);
        }
      }
    }
    else {
      obj[10+i]->DispSw = false;
    }
  }
}

/* ---------------------------------------- */
/* --- 消えるブロックの表示                 */
/* ---------------------------------------- */
void TPuzzleDisp::DispEraseBlock(TGameSprite *obj, Block *bl)
{
  if (bl->LineTimer < 3) {
    obj->tx = 5 * 24;
    obj->ty = 2 * 24;
  }
  else {
    if ((bl->LineTimer % 2) == 0) {
      obj->tx = 4 * 24;
      obj->ty = 2 * 24;
    }
  }
  /* -- きらきらエフェクト */
  if (bl->LineTimer == 3) {
    KiraRequest(obj->x+(BLOCK_WIDTH / 2), obj->y+(BLOCK_HEIGHT / 2), 60);
    KiraRequest(obj->x+(BLOCK_WIDTH / 2), obj->y+(BLOCK_HEIGHT / 2), 60);
    KiraRequest(obj->x+(BLOCK_WIDTH / 2), obj->y+(BLOCK_HEIGHT / 2), 60);
  }
}

/* ---------------------------------------- */
/* --- 背景の表示                           */
/* ---------------------------------------- */
void TPuzzleDisp::DispBack()
{
  obj[0]->DispSw = true;
  obj[0]->x = 0;
  obj[0]->y = 0;
  obj[0]->w = 480;
  obj[0]->h = 360;
  obj[0]->tx = 0;
  obj[0]->ty = 0;
  obj[0]->Texture = texture[0];
  obj[0]->alpha = 255;
  /* -------------------------------------- */
  /* --- 隠すべき枠 */
  obj[115]->DispSw = true;
  obj[115]->x = BLOCKER_X;
  obj[115]->y = BLOCKER_1Y;
  obj[115]->w = 192;
  obj[115]->h = BLOCKER_1H;
  obj[115]->tx = BLOCKER_X;
  obj[115]->ty = BLOCKER_1Y;
  obj[115]->Texture = texture[0];
  obj[115]->alpha = 255;

  obj[116]->DispSw = true;
  obj[116]->x = BLOCKER_2X;
  obj[116]->y = 0;
  obj[116]->w = 192;
  obj[116]->h = BLOCKER_2H;
  obj[116]->tx = BLOCKER_2X;
  obj[116]->ty = 0;
  obj[116]->Texture = texture[0];
  obj[116]->alpha = 255;

#ifdef BLOCKER_3_NEEDED
  obj[117]->DispSw = true;
  obj[117]->x = 81;
  obj[117]->y = 344;
  obj[117]->w = 192;
  obj[117]->h = 16;
  obj[117]->tx = 81;
  obj[117]->ty = 344;
  obj[117]->Texture = texture[0];
  obj[117]->alpha = 255;
#endif
}

/* ---------------------------------------- */
/* --- キャラクターの表示                   */
/* ---------------------------------------- */
void TPuzzleDisp::DispChara()
{
  int i, tanux;
  int koma;

  texture[3] = screen->GetTexture(8);
  koma = (disptimer / 8) % 8;
  obj[9]->DispSw = true;
  obj[9]->x = fieldpos_x;
  obj[9]->y = FIELDTOP;
  obj[9]->w = 192;
  obj[9]->h = CHARA_H;
  obj[9]->tx = animekoma_x[koma] * 192;
  obj[9]->ty = animekoma_y[koma] + KOMA_OFFSET;
  obj[9]->Texture = texture[3];
  obj[9]->alpha = 255;
  /* --- 後ろのタヌキ絵 */
  for(i=0; i<4; i++) {
    tanuki[i].y = tanuki[i].y - 1;
    if (tanuki[i].y < 0) {
      tanuki[i].y = TANUKI_Y + rand() % 40;
      tanuki[i].x = rand() % (BLOCK_WIDTH*FIELD_WIDTH - 60);
    }
    tanux = disp_sin[(int)(360*(tanuki[i].y % 120) / 120)%360] * 8 / 0x10000;
    obj[i+2]->DispSw = true;
    obj[i+2]->x = tanuki[i].x + tanux + fieldpos_x + 20;
    obj[i+2]->y = tanuki[i].y;
    obj[i+2]->w = 36;
    obj[i+2]->h = 22;
    obj[i+2]->tx = 72;
    obj[i+2]->ty = 72 + BOXES_TY;
    obj[i+2]->Texture = texture[0];
    obj[i+2]->alpha = 255;
  }
}

/* ---------------------------------------- */
/* --- ネクストブロックの 'NEXT'            */
/* ---------------------------------------- */
void TPuzzleDisp::DispNext()
{
  int mode = 0;
  if (base->NextTimer < 24*2) {
    mode = 32 * (base->NextTimer % 2);
  }
  obj[120]->DispSw = true;
  obj[120]->x = fieldpos_x + 80;
  obj[120]->y = FIELDTOP + ((FIELD_HEIGHT - 1) * BLOCK_HEIGHT) - 8;
  obj[120]->w = 32;
  obj[120]->h = 16;
  obj[120]->tx = mode;
  obj[120]->ty = 72 + BOXES_TY;
  obj[120]->Texture = texture[0];
  obj[120]->alpha = 255;
}


/* ---------------------------------------- */
/* --- SCORE等のインフォメーション          */
/* ---------------------------------------- */
void TPuzzleDisp::DispScore()
{
  /* 168 : SCORE */
  /* 169 : BLOCK */
  /* 170 : LEVEL */
  /* 171-178 : score num (400x48) */
  /* 179-183 : block num (424x96) */
  /* 184-185 : score num (436x144) */

  int shift = SCORE_SHIFT;
  /* ------------------------------ */
  /* --- 文字 */
  obj[168]->DispSw = true;
  obj[168]->x = 416 - shift;
  obj[168]->y = 27;
  obj[168]->w = 48;
  obj[168]->h = 18;
  obj[168]->tx = 0 + 368;
  obj[168]->ty = 16 + BOXES_TY;
  obj[168]->Texture = texture[0];
  obj[168]->alpha = 255;
  obj[169]->DispSw = true;
  obj[169]->x = 364 - shift;
  obj[169]->y = 75;
  obj[169]->w = 100;
  obj[169]->h = 18;
  obj[169]->tx = 0 + 368;
  obj[169]->ty = 34 + BOXES_TY;
  obj[169]->Texture = texture[0];
  obj[169]->alpha = 255;
  obj[170]->DispSw = true;
  obj[170]->x = 421 - shift;
  obj[170]->y = 123;
  obj[170]->w = 43;
  obj[170]->h = 18;
  obj[170]->tx = 0 + 368;
  obj[170]->ty = 52 + BOXES_TY;
  obj[170]->Texture = texture[0];
  obj[170]->alpha = 255;
  DispNum(400 - shift, 48, 8, 171, base->Score);
  DispNum(424 - shift, 96, 5, 179, base->EraseBlock);
  DispNum(436 - shift, 144, 2, 184, base->Level);
}


/* ---------------------------------------- */
/* --- 数値を表示するサブルーチン           */
/* ---------------------------------------- */
void TPuzzleDisp::DispNum(int x, int y, int n, int o, int num)
{
  int i, j;
  int c;

  /* x, y : 表示位置 */
  /* n : 表示文字数 */
  /* o : Obj番号 */
  /* num : 表示する数字 */
  bool top = true;
  j = 1;
  for(i=0; i<n; i++) {
    j = j * 10;
  }
  if (num >= j) num = j - 1;
  for(i=0; i<n; i++) {
    c = num / (j / 10);
    num = num % (j / 10);
    if (c > 9) c = 9;
    if (i == (n - 1)) top = false;
    /* -- 表示 */
    if ((c == 0) && top) {
      obj[o]->DispSw = false;
    }
    else {
      top = false;
      obj[o]->DispSw = true;
      obj[o]->x = x;
      obj[o]->y = y;
      obj[o]->w = 8;
      obj[o]->h = 16;
      obj[o]->tx = c * 8 + 368;
      obj[o]->ty = 0 + BOXES_TY;
      obj[o]->Texture = texture[0];
      obj[o]->alpha = 255;
    }
    x = x + 8;
    o = o + 1;
    j = j / 10;
  }
}

/* ---------------------------------------- */
/* --- きらきらエフェクトの表示と移動       */
/* ---------------------------------------- */
void TPuzzleDisp::DispKira()
{
  int i;
  int alpha;
  int d;

  for(i=0; i<KIRAMAX; i++) {
    if (kirakira[i].DispSw) {
      /* -- 表示位置 */
      kirakira[i].x = kirakira[i].x + kirakira[i].dx;
      kirakira[i].y = kirakira[i].y + kirakira[i].dy;
      /* -- 移動 */
      alpha = 255;
      if (kirakira[i].timer > (kirakira[i].timer_end / 4)) {
        kirakira[i].dx = (kirakira[i].dx * 0xc0) / 0x100;
        kirakira[i].dy = (kirakira[i].dy * 0xc0) / 0x100;
        d = kirakira[i].timer - (kirakira[i].timer_end / 2);
        d = (d * 255) / (kirakira[i].timer_end / 2);
        alpha = 255 - d;
        if (alpha < 0) alpha = 0;
        if (alpha > 255) alpha = 255;
      }
      /* -- 表示 */
      kirakira[i].obj->DispSw = true;
      kirakira[i].obj->x = kirakira[i].x / 0x10000;
      kirakira[i].obj->y = kirakira[i].y / 0x10000;
      kirakira[i].obj->w = 11;
      kirakira[i].obj->h = 11;
      kirakira[i].obj->tx = 144;
      kirakira[i].obj->ty = 48 + BOXES_TY;
      kirakira[i].obj->Texture = texture[0];
      kirakira[i].obj->alpha = alpha;
      /* -- 表示時間の管理 */
      kirakira[i].timer = kirakira[i].timer + 1;
      if (kirakira[i].timer >= kirakira[i].timer_end) {
        kirakira[i].obj->DispSw = false;
        kirakira[i].DispSw = false;
      }
    }
  }
}
