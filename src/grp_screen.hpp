/* ---------------------------------------------------------- */
/*  grp_screen.h                                              */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   debug.pp                                             */
/*     デバッグ用チェックルーチン                         */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		画面表示管理
    @author		K.Kunikane (rerofumi)
    @since		Jul.27.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#ifndef GRP_SCREEN_H
#define GRP_SCREEN_H

#include <SDL.h>
#include "support.hpp"
#include "grp_sprite.hpp"

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- 管理する最大テクスチャー数 */
#define TEXTUREMAX 16

/* --- 管理する最大スプライト数 */
#define SPRITEMAX 1024

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */
class TGameScreen {
public:
  TGameScreen() = delete;
  explicit TGameScreen(int width, int height, const char *title);
  ~TGameScreen();
  TGameScreen(const TGameScreen&) = delete;
  TGameScreen& operator=(const TGameScreen&) = delete;

  void SetWMName(char *name);
  void DispScreen();
  void RefreshScreen();
  TGameSprite *GetSprite(int id) const;
  SDL_Texture *GetTexture(int id) const;
  void LoadTexture(int num, const char *filename);

private:
  /* --- スプライトを一枚スクリーンに貼り付ける */
  void Render(TGameSprite *spr);

public:
  SDL_Renderer *Renderer;
  int pixelFormat;
  SDL_Window *Window;
  SDL_Texture *Textures[TEXTUREMAX];
  unique_ptr<TGameSprite> Sprites[SPRITEMAX];
  int Width, Height;
};

#endif //GRP_SCREEN_H
