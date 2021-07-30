#include "DxLib.h"
#include "SceneMgr.h"
#include "Input.h"
#include "Enemy.h"
#include "player.h"

//struct ENEMY mEnemy[i];
struct ENEMY mEnemy[ENEMY_MAX];

static int mImageEnemy;

extern int HitBoxEnemy(PLAYER*, ENEMY*);	//�����蔻��i�l�p�j

void Enemy_Initialize() {

	//mImageEnemy = LoadDivGraph("images/enemy1.png", 8, 2, 4, 70, 95, ene,TRUE);	//�摜�̃��[�h
	LoadDivGraph("images/enemy1clear.png", 8, 2, 4, 70, 95, ene);
	LoadDivGraph("images/tomtom.png", 8, 2, 4, 70, 95, tom);

	// �G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		mEnemy[i].flg = FALSE;
		mEnemy[i].dashLeft = true;			//���Ɉړ����锻��
		mEnemy[i].dashRight = true;			//�E�Ɉړ����锻��
		mEnemy[i].x = 800;
		mEnemy[i].y = 395;				//x,y���W
		mEnemy[i].move = 1.0f;				//�ړ��W��
		mEnemy[i].oldchar = 0;			//�O�̉摜������
		mEnemy[i].xcount = 0;
		mEnemy[i].ycount = 0;		//�������Əc�����̃J�E���g��
		mEnemy[i].ix = 0;
		mEnemy[i].iy = 0;
		mEnemy[i].result = 0;		//�Y���p�ϐ�

		mEnemy[i].gekiha = false;
		mEnemy[i].y_temp;
		mEnemy[i].y_prev;
		mEnemy[i].angle = 0;
	}

}
void Enemy_Finalize() {
	DeleteGraph(mImageEnemy); //�摜�̉��
}
void Enemy_Update() {

	//�G�l�~�[����
	for (int i = 0; i < ENEMY_MAX; i++) {

		if (mEnemy[i].flg == TRUE) {


			//�e�X�g
			if (mEnemy[i].gekiha == true) {			//���j�t���O��true�ɂȂ�����

				SetFontSize(20);
				DrawFormatString(600, 100, 0xFFFFFF, "true");
				mEnemy[i].angle = 1;	//�G���X����

				mEnemy[i].y_prev = mEnemy[i].y;				//prev��360����
				mEnemy[i].y_temp = mEnemy[i].y;					//temp��360����
				mEnemy[i].y = mEnemy[i].y + 15;				//y��340����

				mEnemy[i].y +=1;		//y��(y - y_prev) + 1�𑫂�
				mEnemy[i].y_prev = mEnemy[i].y_temp;			//prev��temp�i360�j����


				if (mEnemy[i].y == 370)				//y��360�Ȃ�								//360
					mEnemy[i].gekiha = false;			//�t���O��false�ɂ���

			}
			else if (mEnemy[i].gekiha == false) {				//����
				SetFontSize(20);
				DrawFormatString(600, 100, 0xFFFFFF, "false");	//����
			}



			if (HitBoxEnemy(&mPlayer, &mEnemy[i]) == TRUE && mPlayer.panchi == false) {
				mPlayer.hp -= 20;
				mEnemy[i].flg = FALSE;
			}
			//�ړ�
			if (mEnemy[i].x >= 765) {//�G�l�~�[�̈ʒu�����[�Ȃ�
				mEnemy[i].dashLeft = true;//dashLeft��true�ɂ���
				mEnemy[i].dashRight = false;//dashRight��false�ɂ���
			}
			else if (mEnemy[i].x <= 35) {//�G�l�~�[�̈ʒu�����[�Ȃ�
				mEnemy[i].dashRight = true;//dashRight��true�ɂ���
				mEnemy[i].dashLeft = false;//dashLeft��false�ɂ���
			}

			if (mEnemy[i].dashLeft == true) {//dashLeft��true�Ȃ�
				mEnemy[i].x -= (int)2 * mEnemy[i].move;//���Ɉړ�����
			}
			if (mEnemy[i].dashRight == true) {//dashRight��true�Ȃ�
				mEnemy[i].x += (int)2 * mEnemy[i].move;//�E�Ɉړ�����
			}
			if (mEnemy[i].dashLeft == true) {			//�ړ������ۂɃ��[�V����������
				if (mEnemy[i].xcount > 0)
					mEnemy[i].xcount = 0;
				--mEnemy[i].xcount;

			}
			if (mEnemy[i].dashRight == true) {		//�ړ������ۂɃ��[�V����������
				if (mEnemy[i].xcount < 0)
					mEnemy[i].xcount = 0;
				++mEnemy[i].xcount;

			}
			mEnemy[i].ix = abs(mEnemy[i].xcount) % 20 / 10;		//�摜2���p���p��
			mEnemy[i].iy = abs(mEnemy[i].ycount) % 20 / 10;

			//
			if (mEnemy[i].xcount > 0) {
				mEnemy[i].ix += 0;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 190 && mEnemy[i].x <= 400) {//�G�l�~�[�����痈��x��190�ɓ���ƈЊd���[�V�����ɂ���
					mEnemy[i].ix += 4;	//�Њd�摜
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}
			else if (mEnemy[i].xcount < 0) {
				mEnemy[i].ix += 2;
				mEnemy[i].result = mEnemy[i].ix;
				mEnemy[i].oldchar = mEnemy[i].ix;
				if (mEnemy[i].x >= 400 && mEnemy[i].x <= 610) {//�G�l�~�[�E���痈��x��610�ɓ���ƈЊd���[�V�����ɂ���
					mEnemy[i].ix += 4;	//�Њd�摜
					mEnemy[i].result = mEnemy[i].ix;
					mEnemy[i].oldchar = mEnemy[i].ix;
				}
			}

			// ��ʂ��͂ݏo���������
			if (mEnemy[i].x > 800)
				mEnemy[i].flg = FALSE;

		}
		//������ĂȂ���΃J�E���g���[���ɂ���
		if (mEnemy[i].dashLeft != true && mEnemy[i].dashRight != true) {//�����Ă��Ȃ���΃��[�V�������~�߂�
			mEnemy[i].xcount = 0;
		}


	}
	// �G�l�~�[�̐���
	if (0 % ENEMY_CREATE_TIME == 0) {
		CreateEnemy();
	}


}
void Enemy_Draw() {

	//�G�l�~�[����
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (mEnemy[i].flg == true) {
			DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.2, mEnemy[i].angle, ene[mEnemy[i].result], TRUE);	//angle����
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
			// ����
			return TRUE;
		}
	}
	// ���s
	return FALSE;
}
int HitBoxEnemy(PLAYER* p, ENEMY* e)
{
	// x, y �͒��S���W�Ƃ���
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
	// ��`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}


////�e�X�g
	//if (mEnemy[i].gekiha == true) {			//���j�t���O��true�ɂȂ�����

	//	mEnemy[i][i].angle = 1;	//�G���X����

	//	mEnemy[i][i].y_prev = mEnemy[i].y;				//prev��360����
	//	mEnemy[i].y_temp = mEnemy[i].y;					//temp��360����
	//	mEnemy[i].y = mEnemy[i].y + 15;				//y��340����

	//	mEnemy[i].y +=/* (mEnemy[i].y - mEnemy[i].y_prev) + */1;		//y��(y - y_prev) + 1�𑫂�
	//	mEnemy[i].y_prev = mEnemy[i].y_temp;			//prev��temp�i360�j����


	//	if (mEnemy[i].y == 370)				//y��360�Ȃ�								//360
	//		mEnemy[i].gekiha = false;			//�t���O��false�ɂ���

	//}
	//if (HitBox(&mPlayer, &mEnemy[i]) == TRUE && mPlayer.panchi == false) {
	//	mPlayer.hp -= 20;
	//	mEnemy[i].flg = FALSE;
	//}

	////�ړ�
	//if (mEnemy[i].x >= 765) {//�G�l�~�[�̈ʒu�����[�Ȃ�
	//	mEnemy[i].dashLeft = true;//dashLeft��true�ɂ���
	//	mEnemy[i].dashRight = false;//dashRight��false�ɂ���
	//}
	//else if (mEnemy[i].x <= 35) {//�G�l�~�[�̈ʒu�����[�Ȃ�
	//	mEnemy[i].dashRight = true;//dashRight��true�ɂ���
	//	mEnemy[i].dashLeft = false;//dashLeft��false�ɂ���
	//}

	//if (mEnemy[i].dashLeft == true) {//dashLeft��true�Ȃ�
	//	mEnemy[i].x -= (int)2 * mEnemy[i].move;//���Ɉړ�����
	//}
	//if (mEnemy[i].dashRight == true) {//dashRight��true�Ȃ�
	//	mEnemy[i].x += (int)2 * mEnemy[i].move;//�E�Ɉړ�����
	//}

	//if (mEnemy[i].dashLeft == true) {			//�ړ������ۂɃ��[�V����������
	//	if (mEnemy[i].xcount > 0)
	//		mEnemy[i].xcount = 0;
	//	--mEnemy[i].xcount;

	//}
	//if (mEnemy[i].dashRight == true) {		//�ړ������ۂɃ��[�V����������
	//	if (mEnemy[i].xcount < 0)
	//		mEnemy[i].xcount = 0;
	//	++mEnemy[i].xcount;

	//}
	//mEnemy[i].ix = abs(mEnemy[i].xcount) % 20 / 10;		//�摜2���p���p��
	//mEnemy[i].iy = abs(mEnemy[i].ycount) % 20 / 10;

	////
	//if (mEnemy[i].xcount > 0) {
	//	mEnemy[i].ix += 0;
	//	mEnemy[i].result = mEnemy[i].ix;
	//	mEnemy[i].oldchar = mEnemy[i].ix;
	//	if (mEnemy[i].x >= 190 && mEnemy[i].x <= 400) {//�G�l�~�[�����痈��x��190�ɓ���ƈЊd���[�V�����ɂ���
	//		mEnemy[i].ix += 4;	//�Њd�摜
	//		mEnemy[i].result = mEnemy[i].ix;
	//		mEnemy[i].oldchar = mEnemy[i].ix;
	//	}
	//}
	//else if (mEnemy[i].xcount < 0) {
	//	mEnemy[i].ix += 2;
	//	mEnemy[i].result = mEnemy[i].ix;
	//	mEnemy[i].oldchar = mEnemy[i].ix;
	//	if (mEnemy[i].x >= 400 && mEnemy[i].x <= 610) {//�G�l�~�[�E���痈��x��610�ɓ���ƈЊd���[�V�����ɂ���
	//		mEnemy[i].ix += 4;	//�Њd�摜
	//		mEnemy[i].result = mEnemy[i].ix;
	//		mEnemy[i].oldchar = mEnemy[i].ix;
	//	}
	//}

	//DrawGraph(mEnemy[i].x - (70 / 2), mEnemy[i].y - (95 / 2),ene[mEnemy[i].result], TRUE);

	//DrawRotaGraph(mEnemy[i].x, mEnemy[i].y, 1.2, mEnemy[i].angle, ene[mEnemy[i].result], TRUE);	//angle����

	////������ĂȂ���΃J�E���g���[���ɂ���
	//if (mEnemy[i].dashLeft != true && mEnemy[i].dashRight != true) {//�����Ă��Ȃ���΃��[�V�������~�߂�
	//	mEnemy[i].xcount = 0;
	//}