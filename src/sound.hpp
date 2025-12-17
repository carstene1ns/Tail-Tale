/* ---------------------------------------------------------- */
/*  sound.h                                                   */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   sound.h                                              */
/*     音声マネージャ                                     */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		音声マネージャ
    @author		K.Kunikane (rerofumi)
    @since		Sep.04.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#ifndef SOUND_HPP
#define SOUND_HPP

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- BGM の管理最大数 */
#define BGMMAX 8

/* --- SE の管理最大数 */
#define SEMAX 16

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */
class TSound {
public:
  TSound();
  ~TSound();
  TSound(const TSound&) = delete;
  TSound& operator=(const TSound&) = delete;

  void Music(int req, bool oneShot = false);
  // 繰り返さない BGM のリクエスト
  inline void MusicOneshot(int req) { Music(req, true); }
  void SE(int req);
  void MusicStop();
  void SEStop();
  void Volume(int value);
};

#endif //SOUND_HPP
