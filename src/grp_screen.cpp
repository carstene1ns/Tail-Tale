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

#include <cstdlib>
#include "cute_png.hpp"
#include "grp_screen.hpp"
#include "debug.hpp"

/* -------------------------------------------------------------- */
/* --- スクリーン管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGameScreen::TGameScreen(int width, int height, const char *title)
{
  /* ----- スクリーンの生成 */
  Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_RESIZABLE);
  Renderer = SDL_CreateRenderer(Window, -1, 0);
  SDL_RenderSetLogicalSize(Renderer, width, height);

  for(int i=0; i<TEXTUREMAX; i++) {
    Textures[i] = NULL;
  }

  Width = width; // UNUSED
  Height = height; // UNUSED
  pixelFormat = SDL_PIXELFORMAT_RGBA32; // TODO

  /* --- 初期化 */
  for(int i=0; i<SPRITEMAX; i++) {
    Sprites[i] = make_unique<TGameSprite>();
  }

  /* ----- デバッグプリントの初期化 */
#ifdef DEBUG
  TDebugInit(this);
#endif
}

TGameScreen::~TGameScreen()
{
  /* ----- テクスチャの解放 */
  for(int i=0; i<TEXTUREMAX; i++) {
    SDL_DestroyTexture(Textures[i]);
  }

  /* ----- スクリーンの解放 */
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);

  /* ----- デバッグも終了 */
#ifdef DEBUG
  TDebugFree();
#endif
}

/* ---------------------------------------- */
/* --- ウィンドウタイトルの設定             */
void TGameScreen::SetWMName(char *name)
{
  SDL_SetWindowTitle(Window, name);
}

/* ---------------------------------------- */
/* --- フレームタイミングによる全描画       */
void TGameScreen::DispScreen()
{
  /* --- スプライト描画 */
  for(int i=0; i<SPRITEMAX; i++) {
    if (Sprites[i]->DispSw && Sprites[i]->Texture) {
      /* --- スプライトの描画 */
      Render(Sprites[i].get());
    }
  }
}

void TGameScreen::RefreshScreen()
{
  /* --- 全クリア */
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0x40, 0xff);
  SDL_RenderClear(Renderer);

  /* -- 画面更新 */
  TGameScreen::DispScreen();

  /* -- 開発デバッグフォント */
#ifdef DEBUG
  TDebugDisp(this);
#endif

  /* --- スクリーンアップデート */
  SDL_RenderPresent(Renderer);
}

/* ---------------------------------------- */
/* --- テクスチャをロードする               */

void TGameScreen::LoadTexture(int num, const char *filename)
{
  /* ----- テクスチャ番号が不正だったら終了 */
  if (num < 0 || num > TEXTUREMAX) return;

  /* ----- 既にテクスチャがあったら解放 */
  if (Textures[num] != NULL) {
    SDL_DestroyTexture(Textures[num]);
    Textures[num] = NULL;
  }

  /* ----- テクスチャーの読み込み */
  char name[256];
#ifdef HIGH_QUALITY
  #define RES_PREFIX "480"
#else
  #define RES_PREFIX "320"
#endif

#ifdef DATA_PREFIX
  snprintf(name, sizeof(name), "%s/gfx/%s/%s", DATA_PREFIX, RES_PREFIX, filename);
#else
  snprintf(name, sizeof(name), "./data/gfx/%s/%s", RES_PREFIX, filename);
#endif

#ifdef DEBUG
  printf("Loading %s\n", name);
#endif

  cp_image_t png = cp_load_png(name);
  if (!png.pix) {
    printf("...failed: %s\n", cp_error_reason);
    Textures[num] = NULL;
    return;
  }

  SDL_Surface *temp = SDL_CreateRGBSurfaceWithFormatFrom(png.pix, png.w, png.h,
                                                         0, png.w*4,
                                                         SDL_PIXELFORMAT_RGBA32);
  if (!temp) {
    cp_free_png(&png);
    Textures[num] = NULL;
    return;
  }

  SDL_Texture *plane = SDL_CreateTextureFromSurface(Renderer, temp);
  SDL_FreeSurface(temp);
  cp_free_png(&png);
  if (!plane) {
    Textures[num] = NULL;
    return;
  }
  Textures[num] = plane;
}

/* ---------------------------------------- */
/* --- スプライトを渡す                     */
TGameSprite *TGameScreen::GetSprite(int id) const
{
  if (id < 0 || id > SPRITEMAX) return NULL;

  return Sprites[id].get();
}

/* ---------------------------------------- */
/* --- テクスチャを渡す                     */
SDL_Texture *TGameScreen::GetTexture(int id) const
{
  return Textures[id];
}

/* ---------------------------------------- */
/* --- スプライトの表示(画面転送)           */
void TGameScreen::Render(TGameSprite *spr)
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

  SDL_RenderCopy(Renderer, spr->Texture, &rect1, &rect2);

  if (org_alpha != spr->alpha) {
    SDL_SetTextureAlphaMod(spr->Texture, org_alpha);
  }
}
