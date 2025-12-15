/* ---------------------------------------------------------- */
/*  grp_sptite.c                                              */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   grp_sprite.c                                         */
/*     スプライト管理構造体                               */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		スプライト管理
    @author		K.Kunikane (rerofumi)
    @since		Sep.19.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <stdlib.h>
#include <SDL.h>
#include "grp_sprite.h"

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/*-------------------------------*/
/* local function                */
/*-------------------------------*/

/* -------------------------------------------------------------- */
/* --- テクスチャ管理クラス                                       */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- コンストラクタ・デストラクタ         */
TGameSprite *TGameSprite_Create(void)
{
  TGameSprite *class;

  class = malloc(sizeof(TGameSprite));
  if (!class) return NULL;

  class->Texture = NULL;
  class->TextureId = -1;
  class->DispSw = false;

  return class;
}

void TGameSprite_Destroy(TGameSprite *class)
{
  if (!class) return;

  free(class);
}

/* ---------------------------------------- */
/* --- テクスチャーの登録                   */
/* ---------------------------------------- */
void TGameSprite_SetTextureDirect(TGameSprite *class, int  texture_id,
                                  SDL_Texture *texture)
{
  if (!class) return;

  class->TextureId = texture_id;
  class->Texture = texture;
}
