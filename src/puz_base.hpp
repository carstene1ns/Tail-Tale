/* ---------------------------------------------------------- */
/*  puz_base.h                                                */
/* ---------------------------------------------------------- */

/*--------------------------------------------------------*/
/*                                                        */
/* SDL puzzle project - for COMIKET62                     */
/*                        Fumi2Kick/LiMo/omamori-2002     */
/*                        1st Maintaner  Rerorero@fumi.   */
/*                                                        */
/*   puz_base.h                                           */
/*     パズル情報管理系                                   */
/*                                                        */
/*--------------------------------------------------------*/

#ifndef PUZ_BASE_HPP
#define PUZ_BASE_HPP

#include "puz_res.hpp"

class TGame;
class TSound;

/*-------------------------------*/
/* define                        */
/*-------------------------------*/

/* --- ブロックサイズ */
#define BLOCK_WIDTH  24
#define BLOCK_HEIGHT 24

/* --- フィールドサイズ */
#define FIELD_WIDTH  8
/* Next 込み */
// FIELD_HEIGHT in puz_res.h
#define ALL_BLOCK (FIELD_WIDTH * FIELD_HEIGHT)

/* --- 何個で消えるか */
#define LINE_LENGTH  4

enum class GamePhase {
  PAUSE,
  NORMAL,
  SWAP,
  LINECHECK,
  LINEFLASH,
  LINEERASE,
  DROPCHECK,
  DROPWORK,
  END
};

enum class MoveDir {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum class SwapFlag {
  NONE,
  MASTER,
  SLAVE
};

/* --- ゲームの難易度設定 */
enum GameLevel {
  LevelEasy = 0,
  LevelNormal,
  LevelHard
};

/*-------------------------------*/
/* struct                        */
/*-------------------------------*/

typedef struct {
  /* --- ブロックの種類(0で存在せず) */
  int Color;
  /* --- 揃い判定を行うか否かのフラグ */
  bool LineCheck;
  /* --- 揃ったブロックであるフラグ */
  bool LineBlock;
  /* --- 揃ってきえるtimer */
  int LineTimer;
  /* --- せり上げtimer */
  int PopupTimer;
  /* --- せり上げ位置オフセット*/
  int PopupOffset;
  /* --- 落下するブロックであることのフラグ */
  bool DropCheck;
  /* --- 落下するアニメーションのtimer */
  int DropTimer;
  /* --- 落下するアニメーションのオフセット */
  int DropOffset;
  /* --- 入れ替えアクションフラグ(入れ替えサイドも兼用) */
  SwapFlag SwapSide; 
  /* --- 入れ替えアクションtimer */
  int SwapTimer;
  /* --- 入れ替えアクション位置オフセット */
  int SwapOffsetX;
  int SwapOffsetY;
} Block;

typedef struct {
  /* --- ブロック座標的位置 */
  int X;
  int Y;
  /* --- ブロックをつかんでいるか否か */
  bool HaveBlock;
  /* --- 入れ替えアクションtimer */
  int SwapTimer;
  /* --- 入れ替えアクション位置オフセット */
  int SwapOffsetX;
  int SwapOffsetY;
  /* --- ブロックせり上がり時の追随 */
  int PopupTimer;
  int PopupOffset;
} Cursor;

/* ---------------------------------------------- */
/* --- class                                   -- */
/* ---------------------------------------------- */

class TPuzzleBase {
public:
  TPuzzleBase() = delete;
  explicit TPuzzleBase(TGame *game, int difficult);
  TPuzzleBase(const TPuzzleBase&) = delete;
  TPuzzleBase& operator=(const TPuzzleBase&) = delete;

  void GameInit(int col);
  void GameExec();
  void GamePause(GamePhase mode);
  void GameLevel(int lset);
  bool LevelCheck();
  bool MoveRequest(int posx, int posy, MoveDir dir);

private:
  void SetBlock();
  Block *GetBlock();
  int GetBlockColor();
  void PopupNext();
  bool PopupWork();
  int FieldHeight();
  bool MoveWork();
  bool DropRequest();
  bool DropWork();
  int LineCheck();
  bool LineWork();
  int LineCount(int x, int y, int dx, int dy, int layer);

public:
  int GameTimer;
  /* --- クラス情報 */
  /* - ゲームステップ */
  GamePhase GameStep;
  /* - プレイヤーカーソル */
  Cursor UA;
  /* - ブロックの情報 */
  Block Item[FIELD_WIDTH * FIELD_HEIGHT];
  /* - フィールドの情報 */
  Block *Field[FIELD_WIDTH * FIELD_HEIGHT];
  /* - ブロックカラー順(キャラ色を先頭に) */
  int BlockColor[7];
  /* - ブロックカラー数 */
  int ColorNum;
  /* - ネクストが来るまでのウェイト */
  int NextInterval;
  /* - ネクストのtimer */
  int NextTimer;
  /* - ゲームレベル */
  int Level;
  /* - キャラクターカラー(ブロックの色に影響) */
  int CharaColor;
  /* - アニメーションフラグ(全体の動きが止まっていたらfalse) */
  bool Animation;
  /* - ブロックを消した総数 */
  int EraseBlock;
  /* - 今回消したブロックによる得点 */
  int EraseScore;
  /* - ゲームの得点 */
  int Score;
  /* - 連鎖回数 */
  int Combo;
  /* - ゲームオーバーフラグ */
  bool GameOver;

  TSound *sound;
  /* - ゲーム全体の難易度  */
  int Difficult;
};

#endif //PUZ_BASE_HPP
