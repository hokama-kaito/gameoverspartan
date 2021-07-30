#include"Menu.h"
#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"

#define PI 3.1415926535897932384626433832795f

static int MenuNumber = 0;  //���j���[�J�[�\���Ǘ��p�ϐ�

static int mImageHandle;
static int mImagegame;
static int mImagehelp;
static int mImageend;

static int mImageKnife;

// ������
void Menu_Initialize() {
    mImageHandle = LoadGraph("images/haikeigazo.png"); //�摜�̃��[�h
    mImagegame = LoadGraph("images/game.png");
    mImagehelp = LoadGraph("images/help.png");
    mImageend = LoadGraph("images/end.png");

    mImageKnife = LoadGraph("images/knife1.png");
}

// �I������
void Menu_Finalize() {
    DeleteGraph(mImageHandle); //�摜�̉��
    DeleteGraph(mImagegame);
    DeleteGraph(mImagehelp);
    DeleteGraph(mImageend);

    DeleteGraph(mImageKnife);
}

//�X�V
void Menu_Update() {
    //���j���[�J�[�\���ړ�����
    if (iKeyFlg & PAD_INPUT_DOWN) {
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Z�L�[��������Ă�����
        switch (MenuNumber) {       //�V�[���ɂ���ď����𕪊�
        case 0:    //���݂̉�ʂ����j���[�Ȃ�
            SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Help); //�V�[�����w���v��ʂɕύX
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End);	//�V�[�����G���h��ʂɕύX
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