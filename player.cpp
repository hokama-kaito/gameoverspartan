#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Player.h"
#include "Enemy.h"

struct PLAYER mPlayer;

extern int HitBoxPlayer(PLAYER*, ENEMY*);	//当たり判定（四角）

int mx = 0;

//static int mImagePlayer;	//画像ハンドル格納用変数

//初期化
void Player_Initialize() {
	LoadDivGraph("images/thomas2clear.png", 21, 3, 7, 70, 95, gh);

	//プレイヤーの初期化設定
	mPlayer.jflag = false;
	mPlayer.huse = false;//しゃがみしているかのフラグ
	mPlayer.panchi = false;
	mPlayer.stop = false;//攻撃したときに歩きを止めるフラグ
	mPlayer.x = 400;//x座標
	mPlayer.y = 400;//y座標
	mPlayer.y_prev = 0;//座標
	mPlayer.y_temp = 0;//座標
	mPlayer.oldchar = 3;//前の画像を入れる(右向きか左向きか判断するため)
	mPlayer.attack = 0;//しゃがみ攻撃
	mPlayer.move = 1.0f;//移動係数
	mPlayer.xcount = 0;//横方向のカウント数
	mPlayer.ycount = 0;//縦方向のカウント数
	mPlayer.ix = 0;//添字用変数
	mPlayer.iy = 0;//添字用変数
	mPlayer.result = 0;//添字用変数
	mPlayer.hp = PLAYER_HP;
}

//終了処理
void Player_Finalize() {
	//DeleteGraph(mImagePlayer);	//画像の解放
}

//更新
void Player_Update() {
	//LoadDivGraph("images/thomas2.png", 21, 3, 7, 70, 95, gh);
	if (CheckHitKey(KEY_INPUT_LEFT) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		mPlayer.move = 1.0f;
	}
	else if (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) {
		mPlayer.move = 1.0f;
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		if (mPlayer.stop == false) {
				//mPlayer.x -= (int)4 * mPlayer.move;
			if (mx <= -3) {
				mx += 3;
			}
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		if (mPlayer.stop == false) {
			//mPlayer.x += (int)4 * mPlayer.move;
			if (mx >= -2197) {
				mx -= 3;
			}
		}
	}

	DrawFormatString(500, 100, 0xFFFFFF, "%d",mx);

	//画面移動制御
	if (mPlayer.x + (PLAYER_WIDHT / 2) > 800)
		mPlayer.x = 800 - (PLAYER_WIDHT / 2);
	if (mPlayer.x < (49 / 2))
		mPlayer.x = (49 / 2);



	//ジャンプ処理
	if (mPlayer.jflag == true) {			//ジャンプフラグがtrueになったら
		mPlayer.y_temp = mPlayer.y;					//tempに360を代入
		mPlayer.y += (mPlayer.y - mPlayer.y_prev) + 1;		//yに(y - y_prev) + 1を足す
		mPlayer.y_prev = mPlayer.y_temp;			//prevにtemp（360）を代入
		if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {//右向きなら
			mPlayer.ix = 0;			//[0]の画像を表示(ジャンプの画像)
		}
		else {//左向きなら
			mPlayer.ix = 1;			//[1]の画像を表示(ジャンプの画像)
		}
		mPlayer.result = mPlayer.ix;		//画像を表示(ジャンプの画像)
		if (mPlayer.y == 400)				//yが360なら
			mPlayer.jflag = false;			//フラグをfalseにする
	}
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && mPlayer.jflag == false) {
		mPlayer.jflag = true;			//ジャンプフラグをtrueにする
		mPlayer.y_prev = mPlayer.y;				//prevに360を代入
		mPlayer.y = mPlayer.y - 15;				//yに340を代入
	}

	//パンチ
	if (CheckHitKey(KEY_INPUT_Z) == 1 && mPlayer.panchi == false) {//Zキーを押したら

		mPlayer.panchi = true;			//panchiをtrueにする
		mPlayer.stop = true;

		}
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (HitBoxPlayer(&mPlayer, &mEnemy[i]) == TRUE) {
				mEnemy[i].gekiha = true;
				//mEnemy[i].flg = false;
		}


		if (mPlayer.panchi == true) {		//panchiがtrueなら
			if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {
				mPlayer.ix = 15;//右向きパンチ
				mPlayer.result = mPlayer.ix;
			}
			else if (mPlayer.oldchar == 6 || mPlayer.oldchar == 7 || mPlayer.oldchar == 8) {
				mPlayer.ix = 16;//左向きパンチ
				mPlayer.result = mPlayer.ix;

			}
		}
	}
	if (CheckHitKey(KEY_INPUT_Z) != 1 && mPlayer.panchi == false) {//Zキーを押されていなければ
		mPlayer.stop = false;
	}




	//しゃがみ
	if (CheckHitKey(KEY_INPUT_DOWN) == 1 && mPlayer.huse == false) {//したキーを押したら
		mPlayer.huse = true;			//huseをtrueにする

		if (mPlayer.huse == true) {		//huseがtrueなら
			if (mPlayer.oldchar == 3 || mPlayer.oldchar == 4 || mPlayer.oldchar == 5) {
				mPlayer.ix = 13;//右向きしゃがみ
				mPlayer.result = mPlayer.ix;
				if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 1)//しゃがみ攻撃
				{
					mPlayer.attack++;
					if (mPlayer.attack == 1) {//attackが１なら

						timer++;									//テスト
						if (timer < 100) {							//
							//ix += 1;								//
							//result = ix;							//
						}											//テスト
						mPlayer.ix += 1;	//ixに+1して
						mPlayer.result = mPlayer.ix;//攻撃画像にきりかえ

						//敵を倒すプログラムを書く

					}
				}
				else if (mPlayer.attack > 0)
				{
					mPlayer.attack = -1;
				}
				else {
					mPlayer.attack = 0;
				}
			}
			else  if (mPlayer.oldchar == 6 || mPlayer.oldchar == 7 || mPlayer.oldchar == 8) {
				mPlayer.ix = 10;//左向きしゃがみ
				mPlayer.result = mPlayer.ix;
				if (CheckHitKey(KEY_INPUT_Z) == 1 && CheckHitKey(KEY_INPUT_DOWN) == 1) {
					mPlayer.ix += 1;
					mPlayer.result = mPlayer.ix;
					//敵を倒すプログラムを書く

				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {			//移動した際にモーションをつける
		if (mPlayer.stop == false) {//ストップフラグがfalse1なら
			if (mPlayer.xcount > 0)
				mPlayer.xcount = 0;
			--mPlayer.xcount;
		}
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {		//移動した際にモーションをつける
		if (mPlayer.stop == false) {//ストップフラグがfalse1なら
			if (mPlayer.xcount < 0)
				mPlayer.xcount = 0;
			++mPlayer.xcount;
		}
	}

	//
	mPlayer.ix = abs(mPlayer.xcount) % 30 / 10;
	mPlayer.iy = abs(mPlayer.ycount) % 30 / 10;

	//
	if (mPlayer.xcount > 0) {
		mPlayer.ix += 3;
		mPlayer.result = mPlayer.ix;
		mPlayer.oldchar = mPlayer.ix;
	}
	else if (mPlayer.xcount < 0) {
		mPlayer.ix += 6;
		mPlayer.result = mPlayer.ix;
		mPlayer.oldchar = mPlayer.ix;
	}

	//DrawGraph(mPlayer.x - (PLAYER_WIDHT / 2), mPlayer.y - (PLAYER_HEIGHT / 2), gh[mPlayer.result], TRUE);

	DrawRotaGraph(400, mPlayer.y,1.2,0, gh[mPlayer.result], TRUE);	//test

	//押されてなければカウントをゼロにする
	if (CheckHitKey(KEY_INPUT_LEFT) != 1 && CheckHitKey(KEY_INPUT_RIGHT) != 1) {
		mPlayer.xcount = 0;

		mPlayer.panchi = false;
		mPlayer.huse = false;
		if (mPlayer.panchi == false) {
			mPlayer.ix += 3;
			mPlayer.result = mPlayer.oldchar;
		}
		if (mPlayer.huse == false) {
			mPlayer.ix += 3;
			mPlayer.result = mPlayer.oldchar;
		}
	}
}

//描画
void Player_Draw() {

}
int HitBoxPlayer(PLAYER* p, ENEMY* e)
{
	// x, y は中心座標とする
	int sx1 =
		p->x - (int)(
			40 * 0.45f);
	int sy1 =
		p->y - (int)(
			95 * 0.45f);
	int sx2 =
		p->x + (int)(
			40 * 0.45f);
	int sy2 =
		p->y + (int)(
			95 * 0.45f);
	int dx1 =
		e->x - (int)(
			40 * 0.4f);
	int dy1 =
		e->y - (int)(
			95 * 0.4f);
	int dx2 =
		e->x + (int)(
			40 * 0.4f);
	int dy2 =
		e->y + (int)(
			95 * 0.4f);
	// 矩形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}