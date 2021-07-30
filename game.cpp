#include "Game.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "player.h"
#include "Enemy.h"

static int mImageHandle; //画像ハンドル格納用変数
static int mImageTime;	//
static int mImageHp;

//初期化
void Game_Initialize() {
	mImageHandle = LoadGraph("images/haikeigazo2.png"); //画像のロード
	mImageTime = LoadGraph("images/time.png");
	mImageHp = LoadGraph("images/player.png");

	Player_Initialize();	//
	Enemy_Initialize();
}

//終了処理
void Game_Finalize() {
	DeleteGraph(mImageHandle); //画像の解放
	DeleteGraph(mImageTime); //画像の解放
	DeleteGraph(mImageHp); //画像の解放

	Player_Finalize();	//プレイヤーの開放
	Enemy_Finalize();
}

//更新
void Game_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Escキーが押されていたら
		SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	DrawGraph(mx, 0, mImageHandle, FALSE);

	Player_Update();
	Enemy_Update();

}
//描画
void Game_Draw() {
	Player_Draw();
	Enemy_Draw();

	DrawGraph(300, 30, mImageTime, TRUE);

	//体力ゲージの表示
	//int X = 100; int Y = 430; int W = 100; int H = 20;
	DrawGraph(100, 30, mImageHp, TRUE);
	DrawBox(100, 70, 100 + (int)(mPlayer.hp * 100 / PLAYER_HP), 90, 0xff0000, TRUE);
	if (mPlayer.hp == 0) {
		SceneMgr_ChangeScene(eScene_gameover);
	}
}