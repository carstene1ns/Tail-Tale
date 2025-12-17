
#ifndef PUZ_RES_H
#define PUZ_RES_H

// "high" res mode
#ifdef HIGH_QUALITY
// bootmain.h
/* ----- 画面サイズ設定値 */
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 360
// puz_base.h
#define FIELD_HEIGHT 13
// puz_disp.h
#define FIELDTOP 28
//game_main.c
#define LOGO_RECT_X 38
#define LOGO_RECT_W 400
#define LOGO_RECT_H 112
#define PUSH_RECT_X 80
#define PUSH_RECT_Y 270
#define PUSH_RECT_W 320
#define PUSH_RECT_H 30
#define RELEASE_RECT_X 80
#define RELEASE_RECT_Y 320
#define RELEASE_RECT_W 320
#define RELEASE_RECT_H 16
#define SELECT_RECT_X 240-56-3
#define SELECT_RECT_Y 240
#define SELECT_RECT_W 112
#define SELECT_RECT_H 24
//puz_disp.c
#define FIELD_POS_X 81
#define BOXES_TY 370
#define READY_RECT_TY BOXES_TY
#define GAMEOVER_X 100
#define GAMEOVER_Y 110
#define BLOCKER_X 81
#define BLOCKER_2X BLOCKER_X
#define BLOCKER_1H 4
#define BLOCKER_2H 28
#define BLOCKER_1Y 316
#define BLOCKER_3_NEEDED
#define CHARA_SIZE 288
#define CHARA_H CHARA_SIZE
#define KOMA_OFFSET 0
#define TANUKI_Y 380
#define SCORE_SHIFT 0
//puz_trial.c
#define KIRA_REQUEST_X 444

// low res mode
#else
// bootmain.h
/* ----- 画面サイズ設定値 */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
// puz_base.h
#define FIELD_HEIGHT 10
// puz_disp.h
#define FIELDTOP 4
//game_main.c
#define LOGO_RECT_X 10
#define LOGO_RECT_W 300
#define LOGO_RECT_H 84
#define PUSH_RECT_X 40
#define PUSH_RECT_Y 180
#define PUSH_RECT_W 240
#define PUSH_RECT_H 23
#define RELEASE_RECT_X 40
#define RELEASE_RECT_Y 210
#define RELEASE_RECT_W 240
#define RELEASE_RECT_H 10
#define SELECT_RECT_X 160-40
#define SELECT_RECT_Y 160
#define SELECT_RECT_W 80
#define SELECT_RECT_H 18
//puz_disp.c
#define FIELD_POS_X 4
#define BOXES_TY 272
#define READY_RECT_TY BOXES_TY
#define GAMEOVER_X 20
#define GAMEOVER_Y 40
#define BLOCKER_X 4
#define BLOCKER_2X 81
#define BLOCKER_1H 4
#define BLOCKER_2H BLOCKER_1H
#define BLOCKER_1Y 220
#define CHARA_SIZE 256
#define CHARA_H SCREEN_HEIGHT - 23
#define KOMA_OFFSET 16
#define TANUKI_Y 340
#define SCORE_SHIFT 152
//puz_trial.c
#define KIRA_REQUEST_X 444-152

#endif

#endif //PUZ_RES_H
