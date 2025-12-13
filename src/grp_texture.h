/* ---------------------------------------------------------- */
/*  grp_texture.h                                             */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   grp_texture.pp                                       */
/*     テクスチャー管理クラス                             */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef GRP_TEXTURE_H
#define GRP_TEXTURE_H

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <stdbool.h>
#include <SDL.h>

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- 管理する最大テクスチャー数 */
#define TEXTUREMAX 16

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

typedef struct {
  int  texture_id;
  SDL_Surface *bitmap[TEXTUREMAX];
} TGameTexture, *PTGameTexture;

/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

TGameTexture *TGameTexture_Create();
void TGameTexture_Destroy(TGameTexture *class);
void TGameTexture_Load(TGameTexture *class, int num, char *filename,
                       SDL_Surface *GameScreen, bool preconv);
SDL_Surface  *TGameTexture_GetTexture(TGameTexture *class, int index);

#endif //GRP_TEXTURE_H
