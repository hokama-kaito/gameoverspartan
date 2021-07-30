#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "player.h"

//struct ENEMY mEnemy[i];
struct ENEMY mEnemy[ENEMY_MAX];

static int mImageEnemy;

extern int HitBoxEnemy(PLAYER*, ENEMY*);	//当たり判定（四角）

void Enemy_Initialize() {

	//mImageEnemy = LoadDivGraph("images/enemy1.png", 8, 2, 4, 70, 95, ene,TRUE);	//画像のロード
	LoadDivGraph("images/enemy1clear.png", 8, 2, 4, 70, 95, ene);
	LoadDivGraph("images/tomtom.png", 8, 2, 4, 70, 95, tom);

	// エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
		mEnemy[i].dashLeft = true;			//左に移動する判定
		mEnemy[i].dashRight = true;			//右に移動する判定
		mEnemy[i].x = 800;
		mEnemy[i].y = 395;				//x,y座標
		mEnemy[i].move = 1.0f;				//移動係数
		mEnemy[i].oldchar = 0;			//前の画像を入れる
		mEnemy[i].xcount = 0;
		mEnemy[i].ycount = 0;		//横方向と縦方向のカウント数
		mEnemy[i].ix = 0;
		mEnemy[i].iy = 0;
		mEnemy[i].result = 0;		//添字用変数

		mEnemy[i].gekiha = false;
		mEnemy[i].y_temp;
		mEnemy[i].y_prev;
		mEnemy[i].angle = 0;
	}

}
void Enemy_Finalize() {
	DeleteGraph(mImageEnemy); //画像の解放
}
void Enemy_Update() {

	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {

		if (mEnemy[i].flg == TRUE) {


			//テスト
			if (mEnemy[i].gekiha == true) {			//撃破フラグがtrueになったら

				SetFontSize(20);
				DrawFormatString(600, 100, 0xFFFFFF, "true");
				mEnemy[i].angle = 1;	//敵を傾ける

				mEnemy[i].y_prev = mEnemy[i].y;				//prevに360を代入
				mEnemy[i].y_temp = mEnemy[i].y;					//tempに360を代入
				mEnemy[i].y = mEnemy[i].y + 15;				//yに340を代入

				mEnemy[i].y +=1;		//yに(y - y_prev) + 1を足す
				mEnemy[i].y_prev = mEnemy[i].y_temp;			//prevにtemp（360）を代入


				if (mEnemy[i].y == 370)				//yが360なら								//360
					mEnemy[i].gekiha = false;			//フラグをfalseにする

			}
			else if (mEnemy[i].gekiha == false) {				//消す
				SetFontSize(20);
				DrawFormatString(600, 100, 0xFFFFFF, "false");	//消す
			}



			if (HitBoxEnemy(&mPlayer, &mEnemy[i]) == TRUE && mPlayer.panchi == false) {
				mPlayer.hp -= 20;
				mEnemy[i].flg = FALSE;
			}
			//移動
			if (mEnemy[i].x >= 765) {//エネミーの位置が左端なら
				mEnemy[i].dashLeft = true;//dashLeftをtrueにする
				mEnemy[i].dashRight = false;//dashRightをfalseにする
			}
			else if (mEnemy[i].x <= 35) {//エネミーの位置が左端なら
				mEnemy[i].dashRight = true;//dashRightをtrueにする
				mEnemy[i].dashLeft = false;//dashLeftをfalseにする
			}

			if (mEnemy[i].dashLeft == true) {//dashLeftがtrueなら
				mEnemy[i].x -= (int)2 * mEnemy[i].move;//左に移動する
			}
			if (mEnemy[i].dashRight == true) {//dashRightがtrueなら
				mEnemy[i].x += (int)2 * mEnemy[i].move;//右に移動する
			}
			if (mEnemy[i].dashLeft == true) {			//移動した際にモーションをつける
				if (mEnemy[i].xcount > 0)
					mEnemy[i].xcount = 0;
				--mEnemy[i].xcount;

			}
			if (mEnemy[i].dashRight == true) {		//移動した際にモーションをつける
				if (mEnemy[i].xcount < 0)
					mEnemy[i].xcount = 0;
				++mEnemy[i].xcount;

			}
			mEnemy[i].ix = abs(mEnemy[i].xcount) % 20 / 10;		//画像2枚パラパラ
			mEnemy[i].iy = abs(mEnemy[i].ycount) % 20 / 10;

			//
			if (mEnemy[i].xcount > 0) {
				mEnemy[i].ix += 0;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 190 && mEnemy[i].x <= 400) {//エネミー左から来てxが190に入ると威嚇モーションにする
					mEnemy[i].ix += 4;	//威嚇画像
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}
			else if (mEnemy[i].xcount < 0) {
				mEnemy[i].ix += 2;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 400 && mEnemy[i].x <= 610) {//エネミー右から来てxが610に入ると威嚇モーションにする
					mEnemy[i].ix += 4;	//威嚇画像
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}

			// 画面をはみ出したら消去
			if (mEnemy[i].x > 800)
				mEnemy[i].flg = FALSE;

		}
		//押されてなければカウントをゼロにする
		if (mEnemy[i].dashLeft != true && mEnemy[i].dashRight != true) {//動いていなければモーションを止める
			mEnemy[i].xcount = 0;
		}


	}
	// エネミーの生成
	if (0 % ENEMY_CREATE_TIME == 0) {
		CreateEnemy();
	}


}
void Enemy_Draw() {

	//エネミー処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == true) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.2, mEnemy[i].angle, ene[mEnemy[i].result], TRUE);	//angleつけた
		}
	}


}

int CreateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == FALSE) {
			mEnemy[i].flg = true;
			//mEnemy[i] = enemyCar;
			mEnemy[i].type = GetRand(3);
			//if (mEnemy[i].type == 3) mEnemy[i] = enemyBike;
			//mEnemy[i].img = mImageEnemy[mEnemy[i].type];
			//mEnemy[i].x = mEnemy[i].x;
			// 成功
			return TRUE;
		}
	}
	// 失敗
	return FALSE;
}
int HitBoxEnemy(PLAYER* p, ENEMY* e)
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


////テスト
	//if (mEnemy[i].gekiha == true) {			//撃破フラグがtrueになったら

	//	mEnemy[i][i].angle = 1;	//敵を傾ける

	//	mEnemy[i][i].y_prev = mEnemy[i].y;				//prevに360を代入
	//	mEnemy[i].y_temp = mEnemy[i].y;					//tempに360を代入
	//	mEnemy[i].y = mEnemy[i].y + 15;				//yに340を代入

	//	mEnemy[i].y +=/* (mEnemy[i].y - mEnemy[i].y_prev) + */1;		//yに(y - y_prev) + 1を足す
	//	mEnemy[i].y_prev = mEnemy[i].y_temp;			//prevにtemp（360）を代入


	//	if (mEnemy[i].y == 370)				//yが360なら								//360
	//		mEnemy[i].gekiha = false;			//フラグをfalseにする

	//}
	//if (HitBox(&mPlayer, &mEnemy[i]) == TRUE && mPlayer.panchi == false) {
	//	mPlayer.hp -= 20;
	//	mEnemy[i].flg = FALSE;
	//}

	////移動
	//if (mEnemy[i].x >= 765) {//エネミーの位置が左端なら
	//	mEnemy[i].dashLeft = true;//dashLeftをtrueにする
	//	mEnemy[i].dashRight = false;//dashRightをfalseにする
	//}
	//else if (mEnemy[i].x <= 35) {//エネミーの位置が左端なら
	//	mEnemy[i].dashRight = true;//dashRightをtrueにする
	//	mEnemy[i].dashLeft = false;//dashLeftをfalseにする
	//}

	//if (mEnemy[i].dashLeft == true) {//dashLeftがtrueなら
	//	mEnemy[i].x -= (int)2 * mEnemy[i].move;//左に移動する
	//}
	//if (mEnemy[i].dashRight == true) {//dashRightがtrueなら
	//	mEnemy[i].x += (int)2 * mEnemy[i].move;//右に移動する
	//}

	//if (mEnemy[i].dashLeft == true) {			//移動した際にモーションをつける
	//	if (mEnemy[i].xcount > 0)
	//		mEnemy[i].xcount = 0;
	//	--mEnemy[i].xcount;

	//}
	//if (mEnemy[i].dashRight == true) {		//移動した際にモーションをつける
	//	if (mEnemy[i].xcount < 0)
	//		mEnemy[i].xcount = 0;
	//	++mEnemy[i].xcount;

	//}
	//mEnemy[i].ix = abs(mEnemy[i].xcount) % 20 / 10;		//画像2枚パラパラ
	//mEnemy[i].iy = abs(mEnemy[i].ycount) % 20 / 10;

	////
	//if (mEnemy[i].xcount > 0) {
	//	mEnemy[i].ix += 0;
	//	mEnemy[i].result = mEnemy[i].ix;
	//	mEnemy[i].oldchar = mEnemy[i].ix;
	//	if (mEnemy[i].x >= 190 && mEnemy[i].x <= 400) {//エネミー左から来てxが190に入ると威嚇モーションにする
	//		mEnemy[i].ix += 4;	//威嚇画像
	//		mEnemy[i].result = mEnemy[i].ix;
	//		mEnemy[i].oldchar = mEnemy[i].ix;
	//	}
	//}
	//else if (mEnemy[i].xcount < 0) {
	//	mEnemy[i].ix += 2;
	//	mEnemy[i].result = mEnemy[i].ix;
	//	mEnemy[i].oldchar = mEnemy[i].ix;
	//	if (mEnemy[i].x >= 400 && mEnemy[i].x <= 610) {//エネミー右から来てxが610に入ると威嚇モーションにする
	//		mEnemy[i].ix += 4;	//威嚇画像
	//		mEnemy[i].result = mEnemy[i].ix;
	//		mEnemy[i].oldchar = mEnemy[i].ix;
	//	}
	//}

	//DrawGraph(mEnemy[i].x - (70 / 2), mEnemy[i].y - (95 / 2),ene[mEnemy[i].result], TRUE);

	//DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.2, mEnemy[i].angle, ene[mEnemy[i].result], TRUE);	//angleつけた

	////押されてなければカウントをゼロにする
	//if (mEnemy[i].dashLeft != true && mEnemy[i].dashRight != true) {//動いていなければモーションを止める
	//	mEnemy[i].xcount = 0;
	//}