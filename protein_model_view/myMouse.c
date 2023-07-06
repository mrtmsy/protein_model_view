#include<math.h>
#include "./myGLUT.h"

// マウスイベントのコールバック関数間でやりとりするための変数
// ファイルに関する静的変数なので、このファイルの中だけで有効
static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;
static int shift=-1;
void
myMouse(int button, int state, int x, int y)
{
#ifdef MOUSE_FUNCTION
	switch(state) {
		case  GLUT_DOWN: {  // マウスボタンが押された
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
			case GLUT_LEFT_BUTTON: { //左ボタン
			  if(glutGetModifiers()&GLUT_ACTIVE_SHIFT){ //shift
			    shift=1;
			    break;
			  }else{
			    shift=-1;
			    break;
			  }
			  break;
			}
			  
			case GLUT_MIDDLE_BUTTON: {//中ボタン
				if(glutGetModifiers()&GLUT_ACTIVE_SHIFT){
					shift=1;
					break;
				}else{
					shift=-1;
					break;
				}
				break;
			}
			
		  	case GLUT_RIGHT_BUTTON: {//右ボタン
			  if(glutGetModifiers()&GLUT_ACTIVE_SHIFT){ //shift
			  
			    shift=1;
			    break;
			    
			  }else{
			    shift=-1;
			    break;
			  
			  }
			  break;
			}
		}
		break;
		}

		  
		  
		case GLUT_UP: { // マウスボタンが離された
			endx = x;
			endy = y;
			pressedButton = -1;
			switch(button) {
				case GLUT_LEFT_BUTTON: {
					break;
				}	
				case GLUT_MIDDLE_BUTTON: {
					break;
				}	
				case GLUT_RIGHT_BUTTON: {
					break;
				}	
			}
			break;
		}
	}	
#endif	
	// 再描画イベント
	glutPostRedisplay();
}


void
myMouseMotion(int x, int y)
{
#ifdef MOTION_FUNCTION
	int delx, dely;

	delx = x - startx;
	dely = y - starty; // デバイス座標系のy軸の関係

	switch(pressedButton) {
		case GLUT_MIDDLE_BUTTON: {
			if(shift==1){
			//z軸回りの回転
				myCameraRotateZ(delx/M_PI/20);
		    		startx =  x;
		    		starty = y;
		    		break;
		    	}else{	
		    	//分子の平行移動(X-Y平面)
				myCameraTranslateX(delx/5.0);
				myCameraTranslateY(dely/15.0);
				startx =  x;
				starty =  y;
				break;
			}
		}
		
		case GLUT_RIGHT_BUTTON: {
		  if(shift==1){
		    //z軸回りの回転
		    myCameraRotateZ(delx/M_PI/20);
		    startx =  x;
		    starty = y;
		    break;
		  }else{
			//分子の平行移動(X-Y平面)
			myCameraTranslateX(delx/15.0);
			myCameraTranslateY(dely/15.0);
			startx =  x;
			starty =  y;
			break;
		  }
		  break;
		}
		
		 case GLUT_LEFT_BUTTON: {
		   if(shift==1){
		      //分子の拡大・縮小
		        myCameraTranslateZ(dely/5.0);
		        starty =y;
			 break;
		   }else{
		      //分子の回転
		      myCameraRotateY(delx/M_PI/-20);	
	              myCameraRotateX(dely/M_PI/-20);	
		      startx =  x;
		      starty =  y;
		      break;
	           }
	           break;
		}
	}
#endif
	// 再描画イベント
	glutPostRedisplay();
}


void
myMousePassiveMotion(int x, int y)
{
#ifdef PASSIVEMOTION_FUNCTION
#endif
	// 再描画イベント
	glutPostRedisplay();
}
