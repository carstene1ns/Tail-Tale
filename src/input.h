/* ---------------------------------------------------------- */
/*  input.h                                                   */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   input.h                                              */
/*     入力装置読みとり部分                               */
/*                                                        */
/*--------------------------------------------------------*/

/*------------------------------------------------------------- */
/** @file
    @brief		インプットマネージ
    @author		K.Kunikane (rerofumi)
    @since		Jul.29.2005
*/
/*-----------------------------------------------------
 Copyright (C) 2002,2005 rerofumi <rero2@yuumu.org>
 All Rights Reserved.
 ------------------------------------------------------*/

#ifndef INPUT_H
#define INPUT_H

/*-------------------------------*/
/* include                       */
/*-------------------------------*/
#include <stdbool.h>

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

enum IN {
  IN_None     = 0,
  IN_Up       = 1 << 0,
  IN_Down     = 1 << 1,
  IN_Left     = 1 << 2,
  IN_Right    = 1 << 3,
  IN_Button1  = 1 << 4,
  IN_Button2  = 1 << 5,
  IN_Button3  = 1 << 6,
  IN_Button4  = 1 << 7,
  IN_Button5  = 1 << 8,
  IN_Button6  = 1 << 9,
  IN_Button7  = 1 << 10,
  IN_Button8  = 1 << 11,
  IN_Button9  = 1 << 12,
  IN_Button10 = 1 << 13,
  IN_Button11 = 1 << 14,
  IN_Button12 = 1 << 15
};

/* --- ジョイスティック最大数 */
#define JOY_NUM_MAX 2

/* --- ジョイスティックの遊び計数 */
#define JOY_STICK_DITHER 20000

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

/* ---------------------------------------------- */
/* --- extern                                  -- */
/* ---------------------------------------------- */

void InputInit();
void InputFree();
void InputPoll();
int  InputExit();
int  InputJoyKey(int side);
int  InputJoyKeyTriger(int side);
void InputJoyKeySwap(bool sw);

#endif //INPUT.H
