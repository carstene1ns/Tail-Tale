/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   sound.pp                                             */
/*     簡易サウンド(SDL_mixer使用)                        */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		サウンドマネージャ
    @author		K.Kunikane (rerofumi)
    @since		Sep.04.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_mixer.h>

#include  "sound.h"

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

#define SECHANMAX 8

/*-------------------------------*/
/* local value                   */
/*-------------------------------*/

/* ----- BGM トラック */
Mix_Music *SoundTrack;
char BGMPool[BGMMAX][256];

/* ----- BGM トラック */
Mix_Chunk *SEPool[SEMAX];

/* ----- サウンド有効フラグ */
bool SoundEnable;

/* ----- サウンドチャンネルのトラック */
int track;

/* -------------------------------------------------------------- */
/* --- サウンド                                                   */
/* -------------------------------------------------------------- */

/* ---------------------------------------- */
/* --- サウンドの初期とリスト読み込み       */
/* ---------------------------------------- */
void SoundInit(void)
{
  track = 0;

  /* ----- SDL_mixer のオープン */
  SoundEnable = true;
  int ret = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 1024);
  if (ret != 0) {
    SoundEnable = false;
#ifdef DEBUG
    printf("SDL mixer open failed.\n");
#endif   
    return;
  }

  for(int i=0; i<SECHANMAX; i++) {
    Mix_Volume(i, VOLUMEDEFAULT);
  }
  Mix_VolumeMusic(VOLUMEDEFAULT);

  /* ----- 配列クリア */
  for(int i=0; i<BGMMAX; i++) {
    BGMPool[i][0] = 0;
  }

  for(int i=0; i<SEMAX; i++) {
    SEPool[i] = 0;
  }

  /* --- BGM list */
  for(int i=0; i<BGMMAX; i++) {
#ifdef DATA_PREFIX
    snprintf(BGMPool[i], sizeof(BGMPool[i]), "%s/bgm%02d.ogg", DATA_PREFIX, i);
#else
    snprintf(BGMPool[i], sizeof(BGMPool[i]), "./data/bgm%02d.ogg", i);
#endif
  }

  /* --- SE list */
  char name[256];
  for(int i=0; i<SEMAX; i++)  {
#ifdef DATA_PREFIX
    snprintf(name, sizeof(name), "%s/se%02d.wav", DATA_PREFIX, i);
#else	
    snprintf(name, sizeof(name), "./data/se%02d.wav", i);
#endif	
    SEPool[i] = Mix_LoadWAV(name);
#ifdef DEBUG
    if(!SEPool[i] && !access(name, F_OK)) {
      printf("Could not load %s\n", name);
    }
#endif
  }
}


/* ---------------------------------------- */
/* --- サウンドの解放                       */
/* ---------------------------------------- */
void SoundFree(void)
{
  if (!SoundEnable) {
    return;
  }

  /* ----- 保持サウンドの解放 */
  if (SoundTrack != 0) {
    Mix_HaltMusic();
    Mix_FreeMusic(SoundTrack);
    SoundTrack = 0;
  }

  /* ----- SEチャンネルの停止 */
  for(int i=0; i<SECHANMAX; i++) {
    Mix_HaltChannel(i);
  }

  /* ----- SE chank の解放 */
  for(int i=0; i<SEMAX; i++) {
    if (SEPool[i] != 0) {
      Mix_FreeChunk(SEPool[i]);
      SEPool[i] = 0;
    }
  }

  /* ----- SDL_Mixer のクローズ */
  Mix_CloseAudio();
}


/* ---------------------------------------- */
/* --- BGM のリクエスト                     */
/* ---------------------------------------- */
void SoundMusic(int req)
{
  if (!SoundEnable) {
    return;
  }

  /* --- 範囲チェック */
  if (req < 0) return;
  if (req >= BGMMAX) return;
  if (BGMPool[req][0] == 0) return;

  /* ----- それまでの演奏停止 */
  if (SoundTrack != 0) {
    Mix_HaltMusic();
    Mix_FreeMusic(SoundTrack);
    SoundTrack = 0;
  }

  /* ----- BGM 演奏開始 */
  SoundTrack = Mix_LoadMUS(BGMPool[req]);
  if (!SoundTrack) {
#ifdef DEBUG
    printf("Could not load %s\n", BGMPool[req]);
#endif
    SoundTrack = 0;
    return;
  }
  Mix_PlayMusic(SoundTrack, -1);
}

/* ---------------------------------------- */
/* --- 繰り返さない BGM のリクエスト        */
/* ---------------------------------------- */
void SoundMusicOneshot(int req)
{
  if (!SoundEnable) {
    return;
  }

  /* --- 範囲チェック */
  if (req < 0) return;
  if (req >= BGMMAX) return;
  if (BGMPool[req][0] == 0) return;

  /* ----- それまでの演奏停止 */
  if (SoundTrack != 0) {
    Mix_HaltMusic();
    Mix_FreeMusic(SoundTrack);
    SoundTrack = 0;
  }

  /* ----- BGM 演奏開始 */
  SoundTrack = Mix_LoadMUS(BGMPool[req]);
  if (!SoundTrack) {
    return;
  }
  Mix_PlayMusic(SoundTrack, 1);
}


/* ---------------------------------------- */
/* --- SE のリクエスト                      */
/* ---------------------------------------- */
void SoundSE(int req)
{
  if (!SoundEnable) return;

  /* --- 範囲チェック */
  if (req < 0) return;
  if (req >= BGMMAX) return;
  if (SEPool[req] == 0) return;

  /* ----- SE 発呼 */
  Mix_PlayChannel(track, SEPool[req], 0);

  track = (track + 1) % SECHANMAX;
}

/* ---------------------------------------- */
/* --- BGM トラックの停止                   */
/* ---------------------------------------- */
void SoundMusicStop(void)
{
  if (!SoundEnable) {
    return;
  }

  /* --- */
  Mix_HaltMusic();
}

/* ---------------------------------------- */
/* --- SE の全停止                          */
/* ---------------------------------------- */
void SoundSEStop(void)
{
  if (!SoundEnable) {
    return;
  }

  /* --- */
  /* ----- SEチャンネルの停止 */
  for(int i=0; i<SECHANMAX; i++) {
    Mix_HaltChannel(i);
  }
}

/* ---------------------------------------- */
/* --- Volume値の設定                      */
/* ---------------------------------------- */
void  SoundVolume(int value)
{
  if (value > MIX_MAX_VOLUME) {
    value = MIX_MAX_VOLUME;
  }

  for(int i=0; i<SECHANMAX; i++) {
    Mix_Volume(i, value);
  }

  Mix_VolumeMusic(value);
}

