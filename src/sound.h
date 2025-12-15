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

#ifndef SOUND_H
#define SOUND_H

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- BGM の管理最大数 */
#define BGMMAX 8

/* --- SE の管理最大数 */
#define SEMAX 16

/* --- VOUME の最大値 */
#define VOLUMEDEFAULT MIX_MAX_VOLUME/2

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

void SoundInit();
void SoundFree();
void SoundMusic(int req);
void SoundMusicOneshot(int req);
void SoundSE(int req);
void SoundMusicStop();
void SoundSEStop();
void SoundVolume(int value);

#endif //SOUND_H
