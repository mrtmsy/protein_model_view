#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "./myGLUT.h"

// キーボードイベントに関するマウスの位置
static int keyx = 0;
static int keyy = 0;
int movable;
int display_num;
int camera_num;
int shade_num;

void
myKeyboard(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,         /* キーボードが打ち込まれたときのマウスの位置 */ 
		int y)
	
{
#ifdef KEYBOARD_FUNCTION 
	keyx = x;
	keyy = y;	
	myKeyboard0(key, x, y);
#endif	
	/*
	 再描画イベントを起こすための関数
		glutDisplayFuncで登録された関数がコールバックされる
	*/
	glutPostRedisplay();	
}


void
myKeyboard0(unsigned char key,  /* キーボードから打ち込まれた文字 */
		int x,          /* キーボードが打ち込まれたときのマウスの位置 */ 
		int y)
	
{
	switch(key) {
		case 'q': {
			exit(EXIT_FAILURE);
			break;
		}
		case 'Q': {
			exit(EXIT_FAILURE);
			break;
		}
		case 'x': {
			myCameraRotateX(1.0/M_PI);
			operationModeSet(xrotation);			
			break;
		}
		case 'y': {
			myCameraRotateY(1.0/M_PI);
			operationModeSet(yrotation);			
			break;
		}
		case 'z': {
			myCameraRotateZ(1.0/M_PI);
			operationModeSet(zrotation);	
			break;
		}
		case '1': {
			display_num=1;
			break;
		}
		case '2': {
			display_num=2;
			break;
		}
		case 's': {
			movable^=1;
			break;
		}
		case 'p': {
			camera_num^=1;
			if(camera_num==0){
				printf("透視投影\n");
			}else if(camera_num==1){
				printf("正射投影\n");
			}
			break;
		}
		case 'S': {
			shade_num^=1;
			if(shade_num==0){
				printf("フラットシェーディング\n");
			}else if(shade_num==1){
				printf("スムーズシェーディング\n");
			}
			break;
		}
		case 'h': {
			printf("キーボード\n");
			printf("qまたはQ：終了\n");
			printf("s：停止とロッキングの切り替え\n");
			printf("1：分子表示方法１に切り替え\n");
			printf("2：分子表示方法２に切り替え\n");
			printf("p：投影方法の切り替え\n");
			printf("S：シェーディングの切り替え\n");
			printf("x：x軸を中心に回転\n");
			printf("y：y軸を中心に回転\n");
			printf("z：z軸を中心に回転\n");
			printf("\n");
			printf("マウス\n");
			printf("左ボタン：分子の回転\n");
			printf("中ボタン：分子の移動\n");
			printf("右ボタン：分子の移動\n");
			printf("shift+左ボタン：分子のズーム\n");
			printf("shift+中ボタン：z軸周りの回転\n");
			printf("shift+右ボタン：z軸周りの回転\n");
			break;
		}
		default: { /* 定義されていないキーが入力された時には、何もしない。 */
			break;
		}
	}	

}
