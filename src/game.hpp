/* ---------------------------------------------------------- */
/*  gamemain.h                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   gamemain.h                                           */
/*     ゲームの本体フロー                                 */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef GAME_HPP
#define GAME_HPP

#include "support.hpp"

class TGameScreen;
struct TGameSprite;
class TPuzzleTrial;
class TSound;
class TInput;

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- ゲームステップのラベル */
enum class Step {
  TitleInit,
  TitleIn,
  TitleMain,
  TitleStart,
  TitleFree,
  PuzzleInit,
  PuzzleMain,
  PuzzleFree,
  ConfigInit,
  ConfigMain,
  ConfigFree
};

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */
class TGame {
public:
  TGame() = delete;
  explicit TGame(TGameScreen *scr, TSound *snd, TInput *inp);
  TGame(const TGame&) = delete;
  TGame& operator=(const TGame&) = delete;

  bool Poll(int counter);

  TGameScreen *screen;
  TSound *sound;
  TInput *input;

private:
  int titletimer;
  TGameSprite *bg, *logo, *push, *release, *select_level;
  int sound_volume;
  int control_reverse;
  int control_anime;
  int control_anime_y;
  int level;
  Step step;
  unique_ptr<TPuzzleTrial> puzzle;
};

#endif //GAME_HPP
