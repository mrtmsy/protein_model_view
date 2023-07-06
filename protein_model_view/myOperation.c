#include "./myGLUT.h"

static operationMode __operation = xrotation;

void 
operationModeSet(operationMode mode)
{
	__operation = mode; 
}

operationMode
operationModeGet(void)
{
	return __operation;
}

