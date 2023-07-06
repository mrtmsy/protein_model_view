#include <math.h>
#include "./myTest.h"
#include "./myGLUT.h"

void
myInit(void)
{
	//myLightSet();
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glDepthFunc(GL_LEQUAL);
		/*  デプスを計算するための比較関数の定義
			GL_LEQUAL: Less than or equal	
		*/
	glEnable(GL_DEPTH_TEST); 
		/*  デプステストを有効にする。 */

	//glCullFace(GL_FRONT); // ウラ面を描画しない
	
	//glFrontFace(GL_FRONT); // 表面の定義は頂点で反時計回り
	
	glEnable(GL_CULL_FACE); // 表面だけを表示する

	//glEnable(GL_CW);             	// 時計回りに変更 
	//glEnable(GL_BACK);			// 裏側をカリング 

	glClearColor(0.2,0.2,0.2,0.0);
		/* 背景色の設定　*/

}

