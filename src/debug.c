/* ---------------------------------------------------------- */
/*  debug.c                                                   */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   debug.c                                             */
/*     デバッグ用チェックルーチン                         */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		デバッグチェックルーチン
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
#include <string.h>
#include <SDL.h>
#include "cute_png.h"
#include "debug.h"
#include "grp_screen.h"

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/* ----- デバッグルーチンが有効か否か(ASCIIが準備出来てるか) */
static bool UseDebug;

/* ----- アスキーフォントテクスチャー */
static SDL_Surface *AsciiFont;

/* ----- アスキープレーン */
static SDL_Surface *AsciiPlane;
static SDL_Texture *AsciiTex;

/* ----- 表示文字列 */
static char StockString[MessageMax][128];
static int StockNum;

/* ----- アスキーテクスチャー名 */
#ifdef DATA_PREFIX
static char *TextureName = DATA_PREFIX "/gfx/ascii.png";
#else
static char *TextureName = "./gfx/data/ascii.png";
#endif

/* --- デバッグフォント文字列 */
char debug_line[128];


/* -------------------------------------------------------------- */
/* --- デバッグ用チェックルーチン                                 */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- メッセージのライン表示    */
static void print_msg(char *mes, int disp_x, int disp_y)
{
  int  i, l;
  int  c;
  SDL_Rect  rect1, rect2;

  l = strlen(mes);
  rect1.w = 8;
  rect1.h = 8;
  rect2.w = 8;
  rect2.h = 8;
  for(i=0; i<l; i++) {
    c = mes[i];
    rect1.x = (c % 16) * 8;
    rect1.y = (c / 16) * 8;
    rect2.x = disp_x;
    rect2.y = disp_y;
    SDL_BlitSurface(AsciiFont, &rect1, AsciiPlane, &rect2);
    disp_x = disp_x + 8;
  }
}


/* ---------------------------------------- */
/* --- デバッグフェイス初期化               */
/* ---------------------------------------- */
void TDebugInit(TGameScreen *screen, int Width, int Height)
{
  StockNum = 0;
  UseDebug = true;

  cp_image_t png = cp_load_png(TextureName);
  if (!png.pix) {
    printf("Loading %s failed: %s\n", TextureName, cp_error_reason);
    UseDebug = false;
    return;
  }

  AsciiFont = SDL_CreateRGBSurfaceWithFormatFrom(png.pix, png.w, png.h, 0,
                                                 png.w*4, SDL_PIXELFORMAT_RGBA32);
  if (!AsciiFont) {
    UseDebug = false;
    return;
  }

  AsciiPlane = SDL_CreateRGBSurfaceWithFormat(0, Width, Height, 0,
                                              screen->pixelFormat);

  AsciiTex = SDL_CreateTexture(screen->Renderer, screen->pixelFormat,
                               SDL_TEXTUREACCESS_STREAMING, Width, Height);
  SDL_SetTextureBlendMode(AsciiTex, SDL_BLENDMODE_BLEND);

  if (!AsciiPlane || !AsciiTex) {
    UseDebug = false;
  }
}


/* ---------------------------------------- */
/* --- デバッグフェイス解放                 */
/* ---------------------------------------- */
void TDebugFree()
{
  SDL_FreeSurface(AsciiPlane);
  free(AsciiFont->pixels);
  SDL_FreeSurface(AsciiFont);
  SDL_DestroyTexture(AsciiTex);
  UseDebug = false;
}


/* ---------------------------------------- */
/* --- デバッグフェイスの定期描画           */
/* ---------------------------------------- */
void TDebugDisp(TGameScreen *screen)
{
  int  disp_x, disp_y;
  int  disp_edge;
  SDL_Rect  rect1, rect2;
  int  i;

  /* --- 準備が出来ていなかったら回避 */
  if (!UseDebug) {
    return;
  }

  /* --- 表示キューに積まれている分だけ表示 */
  disp_x = 0;
  disp_y = 0;
  disp_edge = 0;
  for(i=0; i<StockNum; i++) {
    print_msg(StockString[i], disp_x, disp_y);
    if (disp_edge < (strlen(StockString[i]) * 8)) {
      disp_edge = strlen(StockString[i]) * 8;
    }
    disp_y = disp_y + 8;
  }

  /* --- アスキープレーンをスクリーンに */
  if (disp_edge > 0) {
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = disp_edge;
    rect1.h = disp_y;
    rect2.x = 0;
    rect2.y = 0;
    rect2.w = disp_edge;
    rect2.h = disp_y;
    SDL_UpdateTexture(AsciiTex, NULL, AsciiPlane->pixels, AsciiPlane->pitch);
    SDL_RenderCopy(screen->Renderer, AsciiTex, &rect1, &rect2);
    SDL_FillRect(AsciiPlane, NULL, SDL_MapRGBA(AsciiPlane->format,0xff,0xff,0xff,0x00));
  }
  StockNum = 0;  
}


/* ---------------------------------------- */
/* --- デバッグメッセージのキューイング     */
/* ---------------------------------------- */
void TDebugPrint(char *mes)
{
  if (StockNum < MessageMax) {
    strncpy(StockString[StockNum], mes, 127);
    StockNum = StockNum + 1;
  }
}


/* ---------------------------------------- */
/* --- 数字を文字列に変換                   */
/* ---------------------------------------- */
void IntToStr(int num, char *buf)
{
  snprintf(buf, 127, "%d", num);
}


/* ---------------------------------------- */
/* --- 16進数表示用                         */
/* ---------------------------------------- */
void IntToHex(int num, int length, char *buf)
{
  snprintf(buf, 127, "%x", num);
}
