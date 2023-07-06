#include <stdlib.h>
#include "./myGLUT.h"

int lightControl=1;

static GLfloat light0Pos[]      = {0.0, 0.0, 100.0, 0};   /* 照明の位置：(0,0,100,0) (x,y,z,w) 
								w=0の時は無限遠においたことになり、平行光。*/
static GLfloat light0Diffuse[]  = {0.8, 0.8, 0.8, 1.0}; /* 拡散光: RGBA */
static GLfloat light0Specular[] = {0.3, 0.3, 0.3, 1.0}; /* 鏡面光: RGBA */

static GLfloat light1Pos[]      = {100.0, 100.0, 1000.0, 0.0}; 
static GLfloat light1Diffuse[]  = {0.5, 0.5, 0.5, 1.0}; 
static GLfloat light1Specular[] = {0.3, 0.3, 0.3, 1.0}; 
static GLfloat lightAmbient[]   = {0.3, 0.3, 0.3, 1.0}; /* 環境光: RGBA */

static GLfloat light00Pos[]={0.0,0.0,1.0,0};
static GLfloat light11Pos[]={100.0,100.0,1000.0,1.0};

void Light(){
  light0Pos[0]=light00Pos[0];
  light0Pos[1]=light00Pos[1];
  light0Pos[2]=light00Pos[2];
  light0Pos[3]=light00Pos[3];
  light1Pos[0]=light11Pos[0];
  light1Pos[1]=light11Pos[1];
  light1Pos[2]=light11Pos[2];
  light1Pos[3]=light11Pos[3];
}



void
myLightSet(void)
{
	// ライト属性の設定 
	// ライトの個数： GL_MAX_LIRHTS : 0 <= i < GL_MAX_LIGHTS
	// ライトの属性：
	/*
		GL_AMBIENT
		GL_DIFFUSE
		GL_SPECULAR
		GL_POSITION
		GL_SPOT_CUTOFF
		GL_SPOT_DIRECTION
		GL_SPOT_EXPONENT
		GL_CONSTANT_ATTENUATION
		GL_LINEAR_ATTENUATION
		GL_QUADRATIC_ATTENUATION
	*/
	// ライト0の属性の設定 
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);      /* 照明属性指定： ライトの名前(最低８個), 属性(位置), パラメータ */
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0Diffuse);  /* 照明属性指定： ライトの名前(最低８個), 属性(拡散光), パラメータ */
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular); /* 照明属性指定： ライトの名前(最低８個), 属性(鏡面光), パラメータ */

	// ライト1の属性の設定 
	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);      
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  light1Diffuse); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmbient); /* 照明属性指定： ライトの名前(最低８個), 属性, パラメータ */

	glEnable(GL_LIGHTING); /* 照明を使ったレンダリングを有効にする */
	glEnable(GL_LIGHT0);   /* ライト0を有効にする */
	glEnable(GL_LIGHT1);   /* ライト1を有効にする */
}

/*
	ライトの位置を指定した配列のポインタを返す.	
*/ 
GLfloat* 
getMyLightPos(int index)
{
	switch(index) {
		case 0: {
			return light0Pos; 
		}
		case 1: {
			return light1Pos;	
		}
	}
	return NULL;
}


