/* ---------------------------------------------------------- */
/*  grp_sprite.h                                              */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   grp_sprite.h                                         */
/*     スプライト管理構造体                               */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef GRP_SPRITE_H
#define GRP_SPRITE_H

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <stdbool.h>
#include <SDL.h>

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

typedef struct {
  int  TextureId;
  /* - public */
  bool DispSw;
  int  x, y;
  int  w, h;
  int  tx, ty;
  unsigned char  alpha;
  SDL_Texture  *Texture;
} TGameSprite, *PTGameSprite;

/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

TGameSprite *TGameSprite_Create();
void TGameSprite_Destroy(TGameSprite *class);
void TGameSprite_SetTextureDirect(TGameSprite *class, int  texture_id,
                                  SDL_Texture *texture);

#endif //GRP_SPRITE_H
