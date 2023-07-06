#ifndef MYGLUT_H
#define MYGLUT_H
#include <stdio.h>

// GLUTヘッダファイルのインクルード
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#undef  IDLE_FUNCTION
#define KEYBOARD_FUNCTION 
#define MOUSE_FUNCTION 
#define MOTION_FUNCTION 
#define PASSIVEMOTION_FUNCTION

typedef struct Atom Atom;
struct Atom
{
	char resName[4];
	int resNumber;
	float tempFactor;
	float occupancy;
	char atomName[5];
	char element[3];
	float x;
	float y;
	float z;
};

typedef struct Line Line;
struct Line
{
	Atom start;
	Atom end;
};

typedef struct arrayPDB arrayPDB;
struct arrayPDB
{
	int numAtom;
	int numCAAtom;
	Atom *CA;
};

typedef struct recordPDB recordPDB;
struct recordPDB
{
	Atom atom;
	recordPDB *nextAtom;
	recordPDB *nextCA;
};

typedef struct PDB PDB;
struct PDB
{
	Atom Center;
	float maxRadius;
	Atom min;
	Atom max;
	int numAtom;
	int numCA;
	recordPDB *top;
	recordPDB *topCA;
	recordPDB *current;
	recordPDB *currentCA;
};

typedef struct cameraInfo {
	GLdouble Fovy;      /* 視野角 [degree] */  
	GLdouble Aspect;    /* アスペクト比: 巾/高さ */  
	GLdouble ClipNear;  /* カメラ位置に近いクリップ面 */  
	GLdouble ClipFar;   /* カメラ位置から遠いクリップ面 */  
	GLdouble Eye[3];
	GLdouble Centre[3];
	GLdouble Up[3];
} cameraInfo;

typedef enum operationMode {
	xrotation  = 0, 
	yrotation  = 1, 
	zrotation  = 2 
} operationMode;

typedef struct Coord {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Coord;

extern PDB pdb;
extern int lightControl;
extern int camera_num;
extern int display_num;
extern int shade_num;

extern float theta;
extern int turn;
extern int movable;

extern int background;
extern void myInit(void);                                    /* 初期化関数 */
extern void myIdle(void);                                    /* イベントが何もないときのためのコールバック関数 */
extern void myDisplay(void);                                 /* 描画用コールバック関数 */
extern void myReshape(int width, int height);                /* ウィンドウサイズなど変更用コールバック関数 
								width: ウィンドウの巾
								height: ウィンドウの高さ
								*/
extern void myCameraRotateY(GLdouble angle);        
extern void myMouse(int button, int state, int x, int y);    /* マウスイベント用コールバック関数 
								button: どのボタンが押されたか。
								state:  そのときのボタンの状態はなにか。*/
extern void myMouseMotion(int x, int y);                     /* マウスイベント用コールバック関数: ボタンを押したままの移動 */ 
extern void myMousePassiveMotion(int x, int y);              /* マウスイベント用コールバック関数: ボタンを押していないときの移動 */
extern void myKeyboard(unsigned char key, int x, int y);     /* キーボードイベント用コールバック関数 */
extern void myKeyboard0(unsigned char key, int x, int y);     /* キーボードイベント用コールバック関数 */
extern operationMode operationModeGet(void);
extern void          operationModeSet(operationMode);

extern void atom_camera();
extern void myCameraRotateX(GLdouble angle);        
extern void myCameraRotateY(GLdouble angle); 
extern void myCameraRotateYY(GLdouble angle);       
extern void myCameraRotateZ(GLdouble angle);        
extern void myCameraTranslateX(GLdouble pan);        
extern void myCameraTranslateY(GLdouble pan);        
extern void myCameraTranslateZ(GLdouble pan);        
extern cameraInfo* getMyCamera(void);
extern void  upCalc();

extern void myLightSet(void);
extern GLfloat* getMyLightPos(int index);

extern int pdbRead(FILE *fpt, PDB *pdb);
extern void lpdbCenterCalc(PDB* pdb);
extern void lpdbSizeCalc(PDB* pdb);
extern void myCameraSetting(void);
extern void myCameraFarset(void);

#endif /* MYGLUT_H */
