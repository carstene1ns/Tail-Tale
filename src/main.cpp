/**
 *  --- SDL puzzle project 'tailtale'.
 *
 */

#include <cstdlib>
#include <time.h>
#include <SDL.h>
#include "support.hpp"
#include "main.hpp"
#include "debug.hpp"
#include "input.hpp"
#include "sound.hpp"
#include "grp_screen.hpp"
#include "game.hpp"
#include "puz_trial.hpp"
#include "puz_disp.hpp"

/* --------------------------------------------- */
/* --- メインルーチン                        --- */
/* --------------------------------------------- */
int main(int argc, char *argv[])
{
  /* --- タイムカウント */
  int WorkTime = 0;
  int FrameSkip = 0;

  /* ----- SDL 初期化 */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK) != 0) {
    /* --- SDLが初期化できなかった */
#ifdef DEBUG
    printf("SDL initialize error.");
#endif
    return -1;
  }

  /* --- メインルーチンループフラグ */
  bool endflag = false;

  /* ----- ハードウェア初期化 */
  auto input = make_unique<TInput>();
  auto sound = make_unique<TSound>();
  auto gamescreen = make_unique<TGameScreen>(SCREEN_WIDTH, SCREEN_HEIGHT, WindowName);

  int SystemTime = SDL_GetTicks();
  int BeforeTiming = SystemTime;
  int DispTime = 0;
  int FrameCounter = 0;
  srand(time(NULL));
  input->JoyKeySwap(false);

  /* ----- ゲーム本体初期化 */
  auto game = make_unique<TGame>(gamescreen.get(), sound.get(), input.get());

  /* ---------------------------------------- */
  /* ----- メインルーチン                     */
  /* ---------------------------------------- */
  while(!endflag) {
    /* --- ゲーム本体ループ */
    for(int i=0; i<=FrameSkip; i++) {
      FrameCounter = FrameCounter + 1;
      input->Poll();
      /* ------------------------------- */
      /* ----- ゲームメインへ */
      if (!game->Poll(FrameCounter) || input->Exit()) {
        BeforeTiming = SDL_GetTicks();
        break;
      }
    }

    /* ----- デバッグ用監視 */
    DEBUGPRINT("%d", FrameCounter);
    DEBUGPRINT("Work Time : W%02d/D%02d/%d", WorkTime, DispTime, (1000/FRAME_RATE));
    DEBUGPRINT("Frame Skip : %d", FrameSkip);
    DEBUGPRINT("Key Input : %x", input->JoyKeyDown(0));

    WorkTime = SDL_GetTicks() - BeforeTiming;

    /* --- フレーム終了、スクリーン描画 */
    gamescreen->RefreshScreen();
    /* --- フレームタイマー */
    DispTime = SDL_GetTicks() - BeforeTiming;

    int NowTiming = (1000 / FRAME_RATE) - WorkTime;
    if ((NowTiming > 0) && (NowTiming <= (1000 / FRAME_RATE))) {
      SDL_Delay(NowTiming);
    }
    endflag = input->Exit();
    FrameSkip = DispTime / (1000 / FRAME_RATE);
    if (FrameSkip > FRAME_SKIP_MAX) {
      FrameSkip = FRAME_SKIP_MAX;
    }

    BeforeTiming = SDL_GetTicks();

    /* ---------------------------------------- */
    /* ----- メインループココまで               */
  }

  SDL_Quit();

  return 0;
}
