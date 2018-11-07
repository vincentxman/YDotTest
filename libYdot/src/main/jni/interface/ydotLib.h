//
// Created by Administrator on 2018-11-06.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YDOTTEST_YDOTLIB_H
#define YDOTTEST_YDOTLIB_H

#define CameraWidth  	240
#define CameraHeight  	240

typedef unsigned char	U8;
typedef signed char		Num8;

typedef unsigned short	U16;
typedef signed short	Num16;

typedef unsigned long	U32;
typedef signed long		Num32;

typedef U8				BoolX;

#define In
#define Out
#define CoorType 		U8
#define TRUE			1
#define FALSE			0

typedef void	(*CBTouch)(In BoolX bTouch);
typedef void	(*CBRecognized)	(In U32 id);

typedef struct yInitData_TAG
{
    CBTouch 		fTouch;
    CBRecognized	fRecognized;
    void 			*pFixedMem;
}IniData;

U32		yGetFixedMemSize(void);
void 	yInitYdot(IniData *idata);
U8 		*yGetImageBuf(void);
BoolX 	yResetBuf(void);
BoolX 	yDecodeImage(BoolX bLoop);
void    yFreeYdot(void);

#endif //YDOTTEST_YDOTLIB_H
