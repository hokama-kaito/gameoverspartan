#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"
#include"gameover.h"

#define PI 3.1415926535897932384626433832795f

static int mImageHandle;

static int mImagegame;
static int mImagehelp;
static int mImageend;

static int MenuNumber = 0;  //メニューカーソル管理用変数

static int mImageKnife;

// 初期化
void gameover_Initialize() {

    mImageHandle = LoadGraph("images/haikeigazo.png"); //画像のロード
    
    mImagegame = LoadGraph("images/game.png");
    mImagehelp = LoadGraph("images/help.png");
    mImageend = LoadGraph("images/end.png");

    mImageKnife = LoadGraph("images/knife1.png");
}

// 終了処理
void gameover_Finalize() {

    DeleteGraph(mImageHandle); //画像の解放

    DeleteGraph(mImagegame);
    DeleteGraph(mImagehelp);
    DeleteGraph(mImageend);

    DeleteGraph(mImageKnife);
}

//更新
void gameover_Update() {
    //メニューカーソル移動処理
    if (iKeyFlg & PAD_INPUT_DOWN) {
        if (++MenuNumber > 1) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        if (--MenuNumber < 0) MenuNumber = 1;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
        switch (MenuNumber) {       //シーンによって処理を分岐
        case 0:    //現在の画面がメニューなら
            SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Menu); //シーンをヘルプ画面に変更
            break;

        }
    }

}


void gameover_Draw() {

    DrawGraph(0, 0, mImageHandle, FALSE);

    SetFontSize(40);
    DrawString(350, 330, "CONTINUE", GetColor(255, 255, 255));
    DrawString(350, 370, "MENU", GetColor(255, 255, 255));
    SetFontSize(100);
    DrawString(160, 10, "GAME OVER", GetColor(255, 255, 255));

    DrawRotaGraph(320, 345 + MenuNumber * 40, 0.7f,0, mImageKnife, TRUE);
}