
#include <stdio.h>
#include <math.h>
#include "./myGLUT.h"

int     movable=1;
float   theta = 0.0;
float   x = 0;
double  rad = 0;

void
myIdle(void)
{
  if(movable==1){
    myCameraRotateYY(-theta * M_PI / 180.0);
    
    if(x>=360)
      x=0;
    else
      x=x+2;
    
    rad = x * M_PI / 180.0;
    
    // 物体を回転
    theta = 30 * sin(rad) ;	   
    myCameraRotateYY(theta * M_PI / 180.0);
  }
  /*
	 再描画イベントを起こすための関数
		glutDisplayFuncで登録された関数がコールバックされる
	*/
	glutPostRedisplay();	
#ifdef IDLE_FUNCTION
#endif
}
