//
// Created by Administrator on 2018-11-06.
//

#include "ydotLib.h"
#include "yPattern.h"

U32	yGetFixedMemSize(void)
{
    return szMemBrk();
    //return szMemScan()+szMemSpace()+szMemBrk();
}

static IniData g_idata;
static void blink_(In BoolX bOk,InOut IDKey *idKey,In Num8 state)
{
    if(g_idata.fTouch)
        g_idata.fTouch(state>0);
}

static void reconized_(In const IDKey *idKey,In Num32 cntRecognize)
{
    if(g_idata.fRecognized)
        g_idata.fRecognized(idKey->id[0]);
}

typedef struct CodeRange_Tag
{
    U32 beg;
    U32 end;
}CodeRange;

#define U32swap(x) (((x<<16)|(x>>16))&(0xFFFFFFFF))
#define U32mask(x) ((U32)(x^0x19680921))


#define _i(x) U32swap((U32mask(x)))
#define _o(x) U32mask((U32swap(x)))

static const CodeRange g_codeRange[]={
        //-------------------
        {_i(10001),_i(10100)},
        //-------------------
        {0,0}
};

static BoolX isCodeInRange(U32 num,const CodeRange *rg)
{
    U8 i=0;
    U32 beg=_o(rg[i].beg);
    U32 end=_o(rg[i].end);

    for(;rg[i].end!=0;i++)
    {
        if(num>=_o(rg[i].beg) && num<=_o(rg[i].end) )
            return TRUE;
    }
    return FALSE;
}
static BoolX isInFranchise(U32 num)
{
    return isCodeInRange(num,g_codeRange);
}

static BoolX cbYdotInRange_(In const IDKey *idKey)
{
    if(isInFranchise(idKey->id[0]))
        return TRUE;
    return FALSE;
}

void yInitYdot(IniData *idata)
{
    yCbMem memCB;
    yCbIo ioCB;

    memCB.cbMalloc	=malloc;
    memCB.cbFree	=free;
    memCB.cbMemcpy	=memcpy;
    memCB.cbMemset	=memset;

    g_idata=*idata;

    ioCB.cbPrintf	=NULL;
    ioCB.cbSprintf	=NULL;
    ioCB.cbVsprintf	=NULL;

    g_cbYdotAfterDecode	=blink_;
    g_cbYdotReconized	=reconized_;
    g_cbYdotInRange		=cbYdotInRange_;

    yDot_init(&memCB,&ioCB,NULL,NULL,g_idata.pFixedMem);
}

void yFreeYdot()
{
    yDot_close();
}

U8 *yGetImageBuf(void)
{
    return yDotWhole_Buf();
}

BoolX yResetBuf(void)
{
    return yDotWhole_resetBuf();
}

BoolX yDecodeImage(BoolX bLoop)
{
    IDKey idKey;
    Num8 state;

    if(g_cbYdotInRange==NULL)//防止被Hk; 當g_cbYdotInRange=NULL時 就無法限制碼的使用範圍。
        return FALSE;

    return yDotWhole_decode(&idKey,&state, bLoop);
}

