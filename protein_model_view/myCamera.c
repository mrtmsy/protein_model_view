#include <stdio.h>
#include <math.h>
#include "./myGLUT.h"

// このファイルの中だけで参照可能な静的変数
// カメラの現在位置を示している。 

static cameraInfo __camera = {
	30.0,             /* Fovy: 視野角 [degree]*/ 
	1.0,              /* Aspect: アスペクト比 */ 
	1.0,              /* ClipNear(目に近い側のクリッピング面) 目の位置からの奥行き(z軸負の向き)への距離 */
	100.0,            /* ClipFar(目から遠い側のクリッピング面) */
	{0.0, 0.0, 100}, /* Eye: 目の位置: (eyex, eyey, eyez) */
	{0.0, 0.0},  /* Centre: 注視点: (centerx, centrey, centrez) */
	{0.0,1.0,0.0}	  /* Up:  目の上向き: (upx, upy, upz) */	
};

// 他のファイルからカメラの情報を変更できるようにポインタを引き渡す
cameraInfo*
getMyCamera()
{
	return &__camera;
}	

void
myCameraSetting()
{
	GLdouble dummy[3];
	double length;	
	
	__camera.Centre[0]=pdb.Center.x;
	__camera.Centre[1]=pdb.Center.y;
	__camera.Centre[2]=pdb.Center.z;
	
	dummy[0]=__camera.Centre[0]-__camera.Eye[0];
	dummy[1]=__camera.Centre[1]-__camera.Eye[1];
	dummy[2]=__camera.Centre[2]-__camera.Eye[2];
	
	length=sqrt(dummy[0]*dummy[0]+dummy[1]*dummy[1]+dummy[2]*dummy[2]);
	
	__camera.ClipFar=length+(double)pdb.maxRadius+100.0;
}

void
myCameraFarset()
{
	GLdouble dummy[3];
	double length;	
	
	dummy[0]=__camera.Centre[0]-__camera.Eye[0];
	dummy[1]=__camera.Centre[1]-__camera.Eye[1];
	dummy[2]=__camera.Centre[2]-__camera.Eye[2];
	
	length=sqrt(dummy[0]*dummy[0]+dummy[1]*dummy[1]+dummy[2]*dummy[2]);
	
	__camera.ClipFar=length+(double)pdb.maxRadius+100.0;
}

// カメラの上向きを計算する。
void 
upCalc()
{
	GLdouble* up     = __camera.Up;
	GLdouble norm;

	int i;

	norm = up[0]*up[0] + up[1]*up[1] + up[2]*up[2];
	if(0 == norm) { 
		up[0] = 0;	
		up[1] = 1;	
		up[2] = 0;	
	} else {
		norm = sqrt(norm);
		for(i=0; i<3; i++) {
			up[i] /= norm;
		}
	}
}

//　画面のＸ軸の周りに回転させる
void
myCameraRotateX(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	dummy[0] = __camera.Eye[0]-__camera.Centre[0];
	dummy[1] = __camera.Eye[1]-__camera.Centre[1];
	dummy[2] = __camera.Eye[2]-__camera.Centre[2];

	norm[0] = __camera.Up[1]*dummy[2] - dummy[1]*__camera.Up[2];	
	norm[1] = __camera.Up[2]*dummy[0] - dummy[2]*__camera.Up[0];	
	norm[2] = __camera.Up[0]*dummy[1] - dummy[0]*__camera.Up[1];	

	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	__camera.Eye[0] = __camera.Centre[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Eye[1] = __camera.Centre[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Eye[2] = __camera.Centre[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;

	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	glFlush();
}

// 本来のＸ軸の周りに回転させる。
void
myCameraRotateXX(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
	/*
		eyex     1   0      0  \  / EyeX \
		eyey =   0  cos   -sin |  | EyeY |
		eyez	 0  sin    cos /  \ EyeZ /
		
	*/	

	dummy[1] = (__camera.Eye[1]-__camera.Centre[1])*cos(angle) - (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = (__camera.Eye[1]-__camera.Centre[1])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[1] = dummy[1] + __camera.Centre[1];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];


	__camera.Up[1] = __camera.Up[1]*cos(angle) - __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = __camera.Up[1]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	/* カメラ位置の回転 */
	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] =  light[0];
		dummy[1] =  (light[1]-__camera.Centre[1])*cos(angle) - (light[2]-__camera.Centre[2])*sin(angle);
		dummy[2] =  (light[1]-__camera.Centre[1])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0];
		light[1] = dummy[1]+__camera.Centre[1];
		light[2] = dummy[2]+__camera.Centre[2];
	}
	}
	glFlush();
}

void
myCameraRotateY(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;

	dummy[0] = __camera.Eye[0]-__camera.Centre[0];
	dummy[1] = __camera.Eye[1]-__camera.Centre[1];
	dummy[2] = __camera.Eye[2]-__camera.Centre[2];

	norm[0] = __camera.Up[0];	
	norm[1] = __camera.Up[1];	
	norm[2] = __camera.Up[2];	
	__camera.Eye[0] = __camera.Centre[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Eye[1] = __camera.Centre[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Eye[2] = __camera.Centre[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];


	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	glFlush();
}

void
myCameraRotateYY(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
	/*
		eyex    cos  0   sin  \  / EyeX \
		eyey =   0   1    0    | | EyeY |
		eyez	-sin 0    cos /  \ EyeZ /
		
	*/	
	dummy[0] =  (__camera.Eye[0]-__camera.Centre[0])*cos(angle) + (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = -(__camera.Eye[0]-__camera.Centre[0])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[0] = dummy[0] + __camera.Centre[0];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];

	__camera.Up[0] =  __camera.Up[0]*cos(angle) + __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = -__camera.Up[0]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	
	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] =  (light[0]-__camera.Centre[0])*cos(angle) + (light[2]-__camera.Centre[2])*sin(angle);
		dummy[1] =  (light[1]-__camera.Centre[1]);
		dummy[2] = -(light[0]-__camera.Centre[0])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0] + __camera.Centre[0];
		light[1] = dummy[1] + __camera.Centre[1];
		light[2] = dummy[2] + __camera.Centre[2];
	}
	}
	glFlush();
}

void
myCameraRotateZ(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	norm[0] = __camera.Eye[0]-__camera.Centre[0];
	norm[1] = __camera.Eye[1]-__camera.Centre[1];
	norm[2] = __camera.Eye[2]-__camera.Centre[2];
	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;


	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	glFlush();
}


//　カメラをＸ軸の方向に動かす。
void
myCameraTranslateX(GLdouble pan) 
{
	GLdouble dummy[3];
	GLdouble norm[3];
	double length;
	
	// ベクトルCE
	dummy[0] = __camera.Eye[0] - __camera.Centre[0];
	dummy[1] = __camera.Eye[1] - __camera.Centre[1];
	dummy[2] = __camera.Eye[2] - __camera.Centre[2];
	
	length = sqrt(dummy[0]*dummy[0] + dummy[1]*dummy[1] + dummy[2]*dummy[2]);
	
	dummy[0] /= length;
	dummy[1] /= length;
	dummy[2] /= length;
	
	// ベクトルu
	length = sqrt(__camera.Up[0]*__camera.Up[0] + __camera.Up[1]*__camera.Up[1] + __camera.Up[2]*__camera.Up[2]);
	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;
	
	// ベクトルf
	norm[0] = dummy[1]*__camera.Up[2] - dummy[2]*__camera.Up[1];
	norm[1] = dummy[2]*__camera.Up[0] - dummy[0]*__camera.Up[2];
	norm[2] = dummy[0]*__camera.Up[1] - dummy[1]*__camera.Up[0];
	
	length = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);
	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;
	
	// Centre
	__camera.Centre[0] += pan*norm[0];
	__camera.Centre[1] += pan*norm[1];
	__camera.Centre[2] += pan*norm[2];
	
	// Eye
	__camera.Eye[0] += pan*norm[0];
	__camera.Eye[1] += pan*norm[1];
	__camera.Eye[2] += pan*norm[2];
	
	upCalc();

	glFlush();
}

void
myCameraTranslateY(GLdouble pan) 
{

	double length;
	
	// ベクトルu
	length = sqrt(__camera.Up[0]*__camera.Up[0] + __camera.Up[1]*__camera.Up[1] + __camera.Up[2]*__camera.Up[2]);
	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;
	
	// Centre
	__camera.Centre[0] += pan*__camera.Up[0];
	__camera.Centre[1] += pan*__camera.Up[1];
	__camera.Centre[2] += pan*__camera.Up[2];
	
	// Eye
	__camera.Eye[0] += pan*__camera.Up[0];
	__camera.Eye[1] += pan*__camera.Up[1];
	__camera.Eye[2] += pan*__camera.Up[2];
	
	upCalc();
	
	glFlush();
}

void
myCameraTranslateZ(GLdouble pan)
{

	GLdouble dummy[3];
	double length;
	
	// ベクトルCE
	dummy[0] = __camera.Eye[0] - __camera.Centre[0];
	dummy[1] = __camera.Eye[1] - __camera.Centre[1];
	dummy[2] = __camera.Eye[2] - __camera.Centre[2];
	
	length = sqrt(dummy[0]*dummy[0] + dummy[1]*dummy[1] + dummy[2]*dummy[2]);
	
	dummy[0] /= length;
	dummy[1] /= length;
	dummy[2] /= length;
	
	// Centre
	__camera.Centre[0] += pan*dummy[0];
	__camera.Centre[1] += pan*dummy[1];
	__camera.Centre[2] += pan*dummy[2];
	
	// Eye
	__camera.Eye[0] += pan*dummy[0];
	__camera.Eye[1] += pan*dummy[1];
	__camera.Eye[2] += pan*dummy[2];
	
	upCalc();
	myCameraFarset();

	glFlush();
}	
