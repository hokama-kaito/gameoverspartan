#pragma once

#define PI 3.1415926535897932384626433832795f

#define PLAYER_WIDHT 70
#define PLAYER_HEIGHT 95

const int PLAYER_HP = 100;

extern struct PLAYER mPlayer;

struct PLAYER {
	bool jflag;
	bool huse;//しゃがみしているかのフラグ
	bool panchi;
	bool stop;//攻撃したときに歩きを止めるフラグ
	int x, y, y_prev, y_temp;//座標
	int oldchar;//前の画像を入れる(右向きか左向きか判断するため)
	int attack;//しゃがみ攻撃
	float move;//移動係数
	int xcount, ycount;//横方向と縦方向のカウント数
	int ix, iy, result;//添字用変数
	int hp;
};

static int timer = 0;//タイマー
//グラフィックハンドル格納用配列
static int gh[21];
//キー取得用配列
static char key[256];

extern void Player_Initialize();//
extern void Player_Finalize();
extern void Player_Update();	//
extern void Player_Draw();		//