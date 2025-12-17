/* ---------------------------------------------------------- */
/*  puz_disp.h                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_disp.h                                           */
/*     パズル画面表示管理                                 */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef PUZ_DISP_HPP
#define PUZ_DISP_HPP

#include "support.hpp"
#include "puz_res.hpp"
#include "puz_base.hpp"

class TGame;
class TGameScreen;
struct TGameSprite;
struct SDL_Texture;

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- 表示関係の定数 */
#define OBJMAX   186
#define TEXMAX   5
#define KIRAMAX  36

enum class GameMode {
  CHALLENGE,
  MODE1P,
  MODE2P
};

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

/* -------------------------------- */
/* --- きらきらエフェクト */
typedef struct {
  /* - 表示スイッチ */
  bool  DispSw;
  /* - 表示オブジェクトの保持 */
  TGameSprite *obj;
  /* - 表示時間タイマー */
  int timer;
  /* - 消える時間 */
  int timer_end;
  /* - 表示位置 */
  int  x;
  int  y;
  /* - 移動量 */
  int  dx;
  int  dy;
} Kira;

/* -------------------------------- */
/* --- 背景のタヌキ座標 */
typedef struct {
  int  x, y;
} TanuPos;

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */
/* --- クラスメンバー */
class TPuzzleDisp {
public:
  TPuzzleDisp() = delete;
  explicit TPuzzleDisp(GameMode mode, int level, TGame *game);
  ~TPuzzleDisp();
  TPuzzleDisp(const TPuzzleDisp&) = delete;
  TPuzzleDisp& operator=(const TPuzzleDisp&) = delete;

  void DispField();
  void DispReady(int time);
  void DispGameover(int time);
  void DispClear();
  void KiraRequest(int x, int y, int l);

private:
  void DispCursor();
  void DispBlock();
  void DispEraseBlock(TGameSprite *obj, Block *bl);
  void DispBack();
  void DispChara();
  void DispNext();
  void DispScore();
  void DispNum(int x, int y, int n, int o, int num);
  void DispKira();

public:
  /* - 親クラス */
  unique_ptr<TPuzzleBase> base;
  /* - ゲームモード */
  GameMode puz_mode;
  /* - 表示位置指定 */
  int fieldpos_x;
  /* - 表示用オブジェクトポインター */
  TGameSprite *obj[OBJMAX];
  /* - テクスチャーポインター */
  SDL_Texture *texture[TEXMAX];

private:
  /* - きらきらエフェクト */
  Kira kirakira[KIRAMAX];
  /* - タヌキ表示 */
  TanuPos tanuki[4];
  /* - スクリーンの保持 */
  const TGameScreen *screen;
  /* - 表示用タイマー */
  int disptimer;
};

#endif //PUZ_DISP_HPP
