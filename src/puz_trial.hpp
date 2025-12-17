/* ---------------------------------------------------------- */
/*  puz_trial.h                                               */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_trial.h                                          */
/*     パズルとことんモード                               */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef PUZ_TRIAL_H
#define PUZ_TRIAL_H

#include "support.hpp"

class TGame;
class TGameScreen;
class TPuzzleDisp;

/*-------------------------------*/
/* define                        */
/*-------------------------------*/
enum class TrialStep {
  Init,
  Ready,
  Game,
  Miss,
  Gameover,
  End
};

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */
/* --- クラスメンバー */
class TPuzzleTrial {
public:
  TPuzzleTrial() = delete;
  explicit TPuzzleTrial(TGame *game, int level);
  TPuzzleTrial(const TPuzzleTrial&) = delete;
  TPuzzleTrial& operator=(const TPuzzleTrial&) = delete;

  void LoadTexture();
  void GameMain();
  bool GameStat();
  void UserControl();

private:
  void ChangeCharacter(int level);

  /* - 親クラス */
  unique_ptr<TPuzzleDisp> disp;
  /* - ゲーム状態 */
  bool status;

  /* - ゲーム画面 */
  TGame *game;
  /* - ステート */
  TrialStep step;
  /* - スタートカウント */
  int readytimer;

  /* - 難易度 */
  int game_level;
};

#endif //PUZ_TRIAL_H
