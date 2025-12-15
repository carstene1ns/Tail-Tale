/**
 *  --- SDL puzzle project 'tailtale'.
 *
 */

#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "bootmain.h"
#include "debug.h"
#include "input.h"
#include "sound.h"
#include "grp_screen.h"

#include "gamemain.h"

TGameScreen  *scr;
TGameMain  *gamemain;

/* --------------------------------------------- */
/* --- メインルーチン                        --- */
/* --------------------------------------------- */
int  main(int argc, char *argv[])
{
  int  i;
  /* --- メインルーチンループフラグ */
  int  endflag;
  /* --- タイムカウント */
  int  SystemTime;
  int  BeforeTiming;
  int  NowTiming;
  int  WorkTime;
  int  DispTime;
  int  FrameCounter;
  int  FrameSkip;

  WorkTime = 0;
  FrameSkip = 0;

  /* ----- SDL 初期化 */
  i = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK);
  if (i != 0) {
    /* --- SDLが初期化できなかった */
#ifdef DEBUG
    printf("SDL initialize error.");
#endif
    return -1;
  }

  /* --- 終了フラグ */
  endflag = 0;

  /* ----- ハードウェア初期化 */
  InputInit();
  SoundInit();
  scr = TGameScreen_Create(SCREEN_WIDTH, SCREEN_HEIGHT, WindowName);

  SystemTime = SDL_GetTicks();
  BeforeTiming = SystemTime;
  DispTime = 0;
  FrameCounter = 0;
  srand(time(NULL));
  InputJoyKeySwap(false);

  /* ----- ゲーム本体初期化 */
  gamemain = TGameMain_Create(scr);

  /* ---------------------------------------- */
  /* ----- メインルーチン                     */
  /* ---------------------------------------- */
  while(endflag == 0) {
    /* --- ゲーム本体ループ */
    for(i=0; i<=FrameSkip; i++) {
      FrameCounter = FrameCounter + 1;
      InputPoll();
      /* ------------------------------- */
      /* ----- ゲームメインへ */
      if (!TGameMain_Poll(gamemain, FrameCounter) ||
        (InputExit() != 0)) {
        BeforeTiming = SDL_GetTicks();
        break;
      }
    }

    /* ----- デバッグ用監視 */
    DEBUGPRINT("%d", FrameCounter);
    DEBUGPRINT("Work Time : W%02d/D%02d/%d", WorkTime, DispTime, (1000/FRAME_RATE));
    DEBUGPRINT("Frame Skip : %d", FrameSkip);
    DEBUGPRINT("Key Input : %x", InputJoyKey(0));

    WorkTime = SDL_GetTicks() - BeforeTiming;

    /* --- フレーム終了、スクリーン描画 */
    TGameScreen_RefreshScreen(scr);
    /* --- フレームタイマー */
    DispTime = SDL_GetTicks() - BeforeTiming;

    NowTiming = (1000 / FRAME_RATE) - WorkTime;
    if ((NowTiming > 0) && (NowTiming <= (1000 / FRAME_RATE))) {
      SDL_Delay(NowTiming);
    }
    endflag = InputExit();
    FrameSkip = DispTime / (1000 / FRAME_RATE);
    if (FrameSkip > FRAME_SKIP_MAX) {
      FrameSkip = FRAME_SKIP_MAX;
    }

    BeforeTiming = SDL_GetTicks();

    /* ---------------------------------------- */
    /* ----- メインループココまで               */
  }

  /* --- ゲームメインループ終了 */
  TGameMain_Destroy(gamemain);
  /* --- スクリーン解放 */
  TGameScreen_Destroy(scr);
  /* --- 終了、SDL 後処理 */
  SoundFree();
  InputFree();
  SDL_Quit();

  return 0;
}
