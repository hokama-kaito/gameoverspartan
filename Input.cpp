#include "Dxlib.h"
//#include "game.h"

int iOldKey;	//
int iNowKey;	//
int iKeyFlg;	//

int iMouseX;
int iMouseY;

void InputKey(void) {
	//
	iOldKey = iNowKey;
	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	iKeyFlg = iNowKey & ~iOldKey;
}