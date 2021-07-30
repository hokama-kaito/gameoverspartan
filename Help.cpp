#include "Help.h"
#include "SceneMgr.h"
#include "Dxlib.h"
#include "Input.h"

static int mImageHandle;	//画像ハンドル格納用変数

//初期化
void Help_Initialize() {
    mImageHandle = LoadGraph("images/.png");  //背景画像

}

//終了処理
void Help_Finalize() {
    DeleteGraph(mImageHandle);//画像の解放

}

//更新
void Help_Update() {
    if (CheckHitKey(KEY_INPUT_ESCAPE)) { //Escキーが押されていたら
        SceneMgr_ChangeScene(eScene_Menu); //シーンをゲーム画面に変更
    }
}

//描画
void Help_Draw() {
    DrawGraph(0, 0, mImageHandle, FALSE);

    SetFontSize(30);
    DrawString(20, 20, "ヘルプ画面", 0xffffff, 0);

    SetFontSize(20);
    DrawString(20, 340, "", 0xffffff, 0);
    DrawString(20, 360, "", 0xffffff, 0);
    DrawString(20, 380, "", 0xffffff, 0);
    DrawString(20, 400, "", 0xffffff, 0);

    DrawString(150, 450, "---- Xキーを押してタイトルへ戻る ----", 0xffffff, 0);
}