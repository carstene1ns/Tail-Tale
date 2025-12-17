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

#ifndef GRP_SPRITE_HPP
#define GRP_SPRITE_HPP

#include "support.hpp"

struct SDL_Texture;

/* ---------------------------------------------- */
/* --- テクスチャ管理クラス                      -- */
/* ---------------------------------------------- */
struct TGameSprite {
  TGameSprite() : TextureId(-1), DispSw(false), Texture(NULL) {}
  TGameSprite(const TGameSprite&) = delete;
  TGameSprite& operator=(const TGameSprite&) = delete;

  // --- テクスチャーの登録
  inline void SetTexture(int texture_id, SDL_Texture *texture)
  {
    TextureId = texture_id;
    Texture = texture;
  }

  int TextureId;
  /* - public */
  bool DispSw;
  int x, y;
  int w, h;
  int tx, ty;
  unsigned char alpha;
  SDL_Texture *Texture;
};

#endif //GRP_SPRITE_HPP
