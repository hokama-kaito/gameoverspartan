#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"

static int mImageHandle;
static int StopTime;

void End_Initialize() {
	mImageHandle = LoadGraph("images/thanks.png");
	StopTime = 0;
}

void End_Finalize() {
	DeleteGraph(mImageHandle);
}

void End_Draw() {
	DrawGraph(150, 200, mImageHandle, FALSE);

	if (++StopTime > 180) {
		SceneMgr_ChangeScene(eScene_Stop);
	}
}