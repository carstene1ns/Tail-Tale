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

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <SDL.h>
#include "grp_sprite.h"

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- 管理する最大テクスチャー数 */
#define TEXTUREMAX 16

/* --- 管理する最大スプライト数 */
#define SPRITEMAX 1024

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

typedef struct {
  SDL_Window   *Window;
  SDL_Renderer *Renderer;
  SDL_Texture  *Textures[TEXTUREMAX];
  TGameSprite  *Sprites[SPRITEMAX];
  int Width;
  int Height;
  int pixelFormat;
} TGameScreen, *PTGameScreen;


/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

TGameScreen *TGameScreen_Create(int width, int height, const char *title);
void TGameScreen_Destroy(TGameScreen *class);
void TGameScreen_SetWMName(TGameScreen *class, char *name);
void TGameScreen_DispScreen(TGameScreen *class);
void TGameScreen_RefreshScreen(TGameScreen *class);
TGameSprite *TGameScreen_GetSprite(TGameScreen *class, int id);
SDL_Texture *TGameScreen_GetTexture(TGameScreen *class, int id);
void TGameScreen_LoadTexture(TGameScreen *class, int num, char *filename);

#endif //GRP_SCREEN_H
