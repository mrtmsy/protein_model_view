#include <stdio.h>
#include <math.h>
#include "./myGLUT.h"


void
myReshape(int width, int height)
{
	cameraInfo* camera;
	
	/* 画面に映し出すviewportの設定: Viewport変換の設定  */
	glViewport(0, 0, width, height);

	// 現在のカメラの位置を覚えている変数のポインタを取得
	camera = getMyCamera();
	
	// ウィンドウの大きさが変わった場合に、アスペクト比が問題となるので指定しておく
	camera->Aspect = (GLfloat)width/(GLfloat)height;
}

