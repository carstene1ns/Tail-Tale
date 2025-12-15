/* ---------------------------------------------------------- */
/*  debug.h                                                   */
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
    @brief		デバッグチェックルーチン
    @author		K.Kunikane (rerofumi)
    @since		Jul.27.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#ifndef DEBUG_H
#define DEBUG_H

/*-------------------------------*/
/* include                       */
/*-------------------------------*/

#include "grp_screen.h"

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* ----- メッセージの表示量 */
#define  MessageMax  20

#ifdef DEBUG
 #define DEBUGPRINT(FMT, ...) \
    snprintf(debug_line, 127, FMT, __VA_ARGS__); \
    TDebugPrint(debug_line);
#else
 #define DEBUGPRINT(FMT, ...) 
#endif

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

extern char debug_line[128];

/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

void TDebugInit(TGameScreen *screen, int Width, int Height);
void TDebugFree();
void TDebugDisp(TGameScreen *screen);
void TDebugPrint(char *mes);
void IntToStr(int num, char *buf);
void IntToHex(int num, int length, char *buf);

#endif //DEBUG_H
