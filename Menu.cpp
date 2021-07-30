#include"Menu.h"
#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"

#define PI 3.1415926535897932384626433832795f

static int MenuNumber = 0;  //メニューカーソル管理用変数

static int mImageHandle;
static int mImagegame;
static int mImagehelp;
static int mImageend;

static int mImageKnife;

// 初期化
void Menu_Initialize() {
    mImageHandle = LoadGraph("images/haikeigazo.png"); //画像のロード
    mImagegame = LoadGraph("images/game.png");
    mImagehelp = LoadGraph("images/help.png");
    mImageend = LoadGraph("images/end.png");

    mImageKnife = LoadGraph("images/knife1.png");
}

// 終了処理
void Menu_Finalize() {
    DeleteGraph(mImageHandle); //画像の解放
    DeleteGraph(mImagegame);
    DeleteGraph(mImagehelp);
    DeleteGraph(mImageend);

    DeleteGraph(mImageKnife);
}

//更新
void Menu_Update() {
    //メニューカーソル移動処理
    if (iKeyFlg & PAD_INPUT_DOWN) {
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
        switch (MenuNumber) {       //シーンによって処理を分岐
        case 0:    //現在の画面がメニューなら
            SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Help); //シーンをヘルプ画面に変更
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End);	//シーンをエンド画面に変更
            break;

        }
    }

}


void Menu_Draw() {

    DrawGraph(0, 0, mImageHandle, FALSE);

    DrawGraph(350, 330, mImagegame, TRUE);
    DrawGraph(350, 370, mImagehelp, TRUE);
    DrawGraph(350, 410, mImageend, TRUE);
    SetFontSize(100);
    DrawString(190, 10, "spartan", GetColor(255, 255, 255));

    DrawRotaGraph(320, 345 + MenuNumber * 40, 0.7f, 0, mImageKnife, TRUE);
}