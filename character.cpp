#include "character.h"

//初始化全局变量
int flag = -1;
int nowgame = -1;
int if_win = 0;


Person person1;

Monsters mt1[50], mt2;
int mt1_num = 5;


//初始化全局函数

//清空状态
void clear_state()
{
    person1.if_stand = 0;
    person1.if_walk = 0;
    person1.if_run = 0;
    //person1.if_jump = 0;
    person1.if_attack = 0;
    person1.if_dj = 0;
}

void init_person_state()
{
    person1.hp = 300;
    person1.mp = 300;
    person1.attack_harm = 10;
    person1.dj_harm = 10;
    person1.u_harm = 40;
    person1.i_harm = 40;
    person1.o_harm = 20;
    person1.p_harm = 20;
}


void MySound()
{
//    if (bgsound == 0)
//    {
//        PlaySound(TEXT("sound/SystemStart"), NULL,
//          SND_ALIAS | SND_ASYNC);
//        bgsound = 1;
//    }
        if (person1.if_attack == 1)
        {
            PlaySound(NULL, NULL,SND_PURGE);
            PlaySound(TEXT("sound/attack0"), NULL,SND_ALIAS | SND_ASYNC);
        }
        if (person1.if_dj == 1)
        {
            PlaySound(NULL, NULL,SND_PURGE);
            PlaySound(TEXT("sound/attack1"), NULL,SND_ALIAS | SND_ASYNC);
        }
}


void MyTransparentBlt( HDC hdcDest,      // 目标DC
					 int nXOriginDest,   // 目标X偏移
					 int nYOriginDest,   // 目标Y偏移
					 int nWidthDest,     // 目标宽度
					 int nHeightDest,    // 目标高度
					 HDC hdcSrc,         // 源DC
					 int nXOriginSrc,    // 源X起点
					 int nYOriginSrc,    // 源Y起点
					 int nWidthSrc,      // 源宽度
					 int nHeightSrc,     // 源高度
					 UINT crTransparent  // 透明色,COLORREF类型
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// 创建兼容位图
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// 创建单色掩码位图
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	// 将源DC中的位图拷贝到临时DC中
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest,
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	// 设置透明色
	SetBkColor(hImageDC, crTransparent);
	// 生成透明区域为白色，其它区域为黑色的掩码位图
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	// 生成透明区域为黑色，其它区域保持不变的位图
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	// 透明部分保持屏幕不变，其它部分变成黑色
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	// "或"运算,生成最终效果
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}
