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
#include <SDL_image.h>
#include "grp_screen.h"
#include "debug.h"

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/*-------------------------------*/
/* local function                */
/*-------------------------------*/

/* --- スプライトを一枚スクリーンに貼り付ける */
static void Render(TGameScreen *class, TGameSprite *spr);

/* -------------------------------------------------------------- */
/* --- スクリーン管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGameScreen *TGameScreen_Create(int width, int height, const char *title)
{
  /* --- インスタンスの生成 */
  TGameScreen *class = malloc(sizeof(TGameScreen));
  if (!class) return NULL;

  /* ----- スクリーンの生成 */
  class->Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, width, height,
                                   SDL_WINDOW_RESIZABLE);
  class->Renderer = SDL_CreateRenderer(class->Window, -1, 0);
  SDL_RenderSetLogicalSize(class->Renderer, width, height);

  for(int i=0; i<TEXTUREMAX; i++) {
    class->Textures[i] = NULL;
  }
  class->Width = width; // UNUSED
  class->Height = height; // UNUSED
  class->pixelFormat = SDL_PIXELFORMAT_RGBA32; // TODO
  /* --- 初期化 */
  for(int i=0; i<SPRITEMAX; i++) {
    class->Sprites[i] = TGameSprite_Create();
  }

  /* ----- デバッグプリントの初期化 */
#ifdef DEBUG
  TDebugInit(class, width, height);
#endif

  /* --- ポインタを返して終了 */
  return class;
}

void TGameScreen_Destroy(TGameScreen *class)
{
  if (!class) return;

  /* ----- テクスチャの解放 */
  for(int i=0; i<TEXTUREMAX; i++) {
    SDL_DestroyTexture(class->Textures[i]);
  }

  /* ----- スクリーンの解放 */
  SDL_DestroyRenderer(class->Renderer);
  SDL_DestroyWindow(class->Window);

  /* ----- スプライトの解放 */
  for(int i=0; i<SPRITEMAX; i++) {
    TGameSprite_Destroy(class->Sprites[i]);
  }

  /* ----- デバッグも終了 */
#ifdef DEBUG
  TDebugFree();
#endif

  /* ----- インスタンスの破棄 */
  free(class);
}

/* ---------------------------------------- */
/* --- ウィンドウタイトルの設定             */
void TGameScreen_SetWMName(TGameScreen *class, char *name)
{
  SDL_SetWindowTitle(class->Window, name);
}


/* ---------------------------------------- */
/* --- フレームタイミングによる全描画       */
void TGameScreen_DispScreen(TGameScreen *class)
{
  /* --- スプライト描画 */
  for(int i=0; i<SPRITEMAX; i++) {
    if (class->Sprites[i]->DispSw && class->Sprites[i]->Texture) {
      /* --- スプライトの描画 */
      Render(class, class->Sprites[i]);
    }
  }
}

void TGameScreen_RefreshScreen(TGameScreen *class)
{
  /* --- 全クリア */
  SDL_SetRenderDrawColor(class->Renderer, 0, 0, 0x40, 0xff);
  SDL_RenderClear(class->Renderer);

  /* -- 画面更新 */
  TGameScreen_DispScreen(class);

  /* -- 開発デバッグフォント */
#ifdef DEBUG
  TDebugDisp(class);
#endif

  /* --- スクリーンアップデート */
  SDL_RenderPresent(class->Renderer);
}


/* ---------------------------------------- */
/* --- テクスチャをロードする               */

void TGameScreen_LoadTexture(TGameScreen *class, int num, char *filename)
{
  if (!class) return;

  /* ----- テクスチャ番号が不正だったら終了 */
  if (num < 0 || num > TEXTUREMAX) return;

  /* ----- 既にテクスチャがあったら解放 */
  if (class->Textures[num] != NULL) {
    SDL_DestroyTexture(class->Textures[num]);
    class->Textures[num] = NULL;
  }

  /* ----- テクスチャーの読み込み */
  char name[256];
#ifdef DATA_PREFIX
  snprintf(name, sizeof(name), "%s/%s", DATA_PREFIX, filename);
#else
  snprintf(name, sizeof(name), "./data/%s", filename);
#endif

  SDL_Texture *plane = IMG_LoadTexture(class->Renderer, name);
  if (!plane) {
    class->Textures[num] = NULL;
    return;
  }
  class->Textures[num] = plane;
}

/* ---------------------------------------- */
/* --- スプライトを渡す                     */
TGameSprite *TGameScreen_GetSprite(TGameScreen *class, int id)
{
  if (id < 0 || id > SPRITEMAX) return NULL;

  return class->Sprites[id];
}


/* ---------------------------------------- */
/* --- テクスチャを渡す                     */
SDL_Texture *TGameScreen_GetTexture(TGameScreen *class, int id)
{
  return class->Textures[id];
}


/* ---------------------------------------- */
/* --- スプライトの表示(画面転送)           */
static void Render(TGameScreen *class, TGameSprite *spr)
{
  /* --- 表示スイッチ */
  if (!spr->DispSw || !spr->Texture) return;

  /* --- 表示範囲 */
  SDL_Rect rect1 = { spr->tx, spr->ty, spr->w, spr->h };
  SDL_Rect rect2 = { spr->x, spr->y, spr->w, spr->h };

  unsigned char org_alpha;
  SDL_GetTextureAlphaMod(spr->Texture, &org_alpha);
  if (org_alpha != spr->alpha) {
    if (spr->alpha < 255) {
      SDL_SetTextureAlphaMod(spr->Texture, spr->alpha);
    } else {
      SDL_SetTextureAlphaMod(spr->Texture, 0);
    }
  }

  SDL_RenderCopy(class->Renderer, spr->Texture, &rect1, &rect2);

  if (org_alpha != spr->alpha) {
    SDL_SetTextureAlphaMod(spr->Texture, org_alpha);
  }
}
