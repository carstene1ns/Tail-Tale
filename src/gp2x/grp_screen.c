/* ---------------------------------------------------------- */
/*  debug.c                                                   */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   grp_screen.c                                         */
/*     画面管理クラス                                     */
/*                                                        */
/*--------------------------------------------------------*/


/*------------------------------------------------------------- */
/** @file
    @brief		描画スクリーン管理
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

#include <stdlib.h>

#include "grp_screen.h"
#include "debug.h"


/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/*-------------------------------*/
/* local function                */
/*-------------------------------*/

/* --- スプライトを一枚スクリーンに貼り付ける */
void Render(TGameScreen *class, TGameSprite *spr);

/* -------------------------------------------------------------- */
/* --- スクリーン管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGameScreen *TGameScreen_Create(int width, int height, int depth)
{
  int  i;

  TGameScreen *class;

  /* --- インスタンスの生成 */
  class = malloc(sizeof(TGameScreen));
  if (class == 0) {
    return(0);
  }

  /* ----- スクリーンの生成 */
  class->Screen = SDL_SetVideoMode(width, height, depth, SDL_SWSURFACE);
  class->Texture = TGameTexture_Create();
  class->Width = width;
  class->Height = height;
  class->Depth = depth;
  SDL_ShowCursor(SDL_DISABLE);
  /* --- 初期化 */
  for(i=0; i<SPRITEMAX; i++) {
    class->Sprites[i] = TGameSprite_Create();
  }

  /* ----- デバッグプリントの初期化 */
#ifdef DEBUG
  TDebugInit(class, width, height, depth);
#endif

  /* --- ポインタを返して終了 */
  return(class);
}

void TGameScreen_Destroy(TGameScreen *class)
{
  int  i;

  if (class) {
    /* ----- テクスチャの解放 */
    TGameTexture_Destroy(class->Texture);
    /* ----- スクリーンの解放 */
    SDL_FreeSurface(class->Screen);
    /* ----- スプライトの解放 */
    for(i=0; i<SPRITEMAX; i++) {
      TGameSprite_Destroy(class->Sprites[i]);
    }
    /* ----- デバッグも終了 */
#ifdef DEBUG
    TDebugFree();
#endif
    /* ----- インスタンスの破棄 */
    free(class);
  }
}

/* ---------------------------------------- */
/* --- ウィンドウタイトルの設定             */
void TGameScreen_SetWMName(TGameScreen *class, char *name)
{
  SDL_WM_SetCaption(name, name);
}


/* ---------------------------------------- */
/* --- フレームタイミングによる全描画       */
void TGameScreen_DispScreen(TGameScreen *class)
{
  int  i;

  /* --- スプライト描画 */
  for(i=0; i<SPRITEMAX; i++) {
    if (class->Sprites[i]->DispSw &&
      (class->Sprites[i]->Texture != NULL)) {
      /* --- スプライトの描画 */
      /* 回転拡大縮小なし、単純矩形コピー */
      Render(class, class->Sprites[i]);
    }
  }
}

void TGameScreen_RefreshScreen(TGameScreen *class)
{
  /* -- 画面更新 */
  TGameScreen_DispScreen(class);

  /* -- 開発デバッグフォント */
#ifdef DEBUG
  TDebugDisp(class);
#endif

  /* --- スクリーンアップデート */
  SDL_UpdateRect(class->Screen, 0, 0, class->Width, class->Height);
  /* --- 全クリア */
  //SDL_FillRect(class->Screen, 0, 0x0000);
}


/* ---------------------------------------- */
/* --- テクスチャをロードする               */

void TGameScreen_LoadTexture(TGameScreen *class,
			     int num,
			     char *filename)
{
  TGameTexture_Load(class->Texture, num, filename, class->Screen, true);
}

void TGameScreen_LoadTexturePure(TGameScreen *class,
				 int num,
				 char *filename)
{
  TGameTexture_Load(class->Texture, num, filename, class->Screen, false);
}


/* ---------------------------------------- */
/* --- スプライトを渡す                     */
TGameSprite *TGameScreen_GetSprite(TGameScreen *class, int id)
{
  if (id < 0) return(0);
  if (id > SPRITEMAX) return(0);

  return(class->Sprites[id]);
}


/* ---------------------------------------- */
/* --- テクスチャを渡す                     */
SDL_Surface *TGameScreen_GetTexture(TGameScreen *class, int id)
{
  return(TGameTexture_GetTexture(class->Texture, id));
}


/* ---------------------------------------- */
/* --- スプライトの表示(画面転送)           */
void Render(TGameScreen *class, TGameSprite *spr)
{
  unsigned char  org_alpha;
  SDL_Rect  rect1, rect2;
  int  r;

  /* --- 表示スイッチ */
  if (!spr->DispSw) return;
  if (!spr->Texture) return;

  /* --- 表示範囲 */
  rect1.w = spr->w;
  rect1.h = spr->h;
  rect2.w = spr->w;
  rect2.h = spr->h;
  rect1.x = spr->tx;
  rect1.y = spr->ty;
  rect2.x = spr->x;
  rect2.y = spr->y;
  org_alpha = spr->Texture->format->alpha;
  if (org_alpha != spr->alpha) {
    if (spr->alpha < 255) {
      SDL_SetAlpha(spr->Texture, SDL_SRCALPHA, spr->alpha);
    }
    else {
      SDL_SetAlpha(spr->Texture, 0, 0);
    }
  }
  r = SDL_BlitSurface(spr->Texture, &rect1, class->Screen, &rect2);
  if (org_alpha != spr->alpha) {
    SDL_SetAlpha(spr->Texture, SDL_SRCALPHA, org_alpha);
  }
}
