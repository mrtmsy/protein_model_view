#include <stdlib.h>
#include <stdio.h>
#include "./myTest.h"
#include "./myGLUT.h"

PDB pdb;

int
main(int argc, char* argv[])
{

  FILE* fpt;
  if(NULL==(fpt=fopen(argv[1],"r"))){
    printf("fopen error!\n");
    exit(1);
  }
  pdbRead(fpt,&pdb);
  lpdbCenterCalc(&pdb);
  lpdbSizeCalc(&pdb);
  fclose(fpt);
  
  myCameraSetting();
  
// GLUTを用いる上で必須の環境設定  
	/* GLUT Liraryの初期化： GLUTライブラリで使用されるオプション・引数の取り扱い */ 	
	glutInit(&argc, argv); 
	/* GLUTライブラリを使った表示モードの設定 */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
		/* 
		GLUT_SINGLE :  シングルバファモード。GLUT_DOUBLEは、ダブルバッファモード 	
		GLUT_RGBA   :  色の指定はRGBAモード設定する(default)。 GLUT_INDEXは、インデックスモード(上書き)
		GLUT_DEPTH  :  z-bufferモードの指定	
		GLUT_ALPHA  :  アルファバッファを確保する。GLUT_RGBAではアルファバッファは用意されない.
		GLUT_ACCUM  :  アキュミュレーションバッファを確保する。
		GLUT_STENCIL:  ステンシルバッファを確保する。
		GLUT_STEREO :  ステレオウィンドウを確保する。
		*/

	/* 最初に開くウィンドウの大きさを指定 */
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);  
	/* 最初に開くウィンドウの位置を指定 */
	glutInitWindowPosition(WIN_POSX, WIN_POSY); 
	/* ウィンドウを作成する。引数はウィンドウの名前 */
	glutCreateWindow(WIN_NAME);

// このアプリケーション専用の環境設定
	/* このプログラム専用の環境設定: 自作 */
	myInit();

// コールバック関数の登録(registeration)
	glutIdleFunc(myIdle);         /* 何もイベントが起きていないときに呼び出す関数 */
  // キーボードに関係したコールバック関数の登録
	glutKeyboardFunc(myKeyboard); /* キーボードが押されたときに呼び出される関数を指定する。*/

  // マウスイベントに関係したコールバック関数の登録
	glutMouseFunc(myMouse);       /* マウスが押されたときに呼び出される関数を指定する。*/
	glutMotionFunc(myMouseMotion);/* マウスを押したまま, マウスが移動するときに呼び出される関数を指定する。*/
	glutPassiveMotionFunc(myMousePassiveMotion);  /* マウスが押されていないとき、マウスが移動するときに呼び出される関数を指定する。*/
  // 画面の表示に関係したコールバック関数の登録
	glutDisplayFunc(myDisplay);   /* 絵を書くときに呼び出される関数を指定する。 */
	glutReshapeFunc(myReshape);   /* ウィンドウの大きさなどが変更したときに呼び出される関数(call back function)を指定する。*/

// GLUTによるメインループ
	glutMainLoop();  // 無限ループ： 上記の4つのイベントがおこった時に、指定された関数をコールバックする。 
			 // どの順番でイベントが起きるかを想定できない。
			 // おこったイベントに応じてコールバックされる関数が変わる。
			 // このような制御法を イベント駆動型(event-driven) とよぶ。
	return 0;  /* ここへは一度もやってこない */
}

