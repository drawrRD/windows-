#include "character.h"

//��ʼ��ȫ�ֱ���
int flag = -1;
int nowgame = -1;
int if_win = 0;


Person person1;

Monsters mt1[50], mt2;
int mt1_num = 5;


//��ʼ��ȫ�ֺ���

//���״̬
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


void MyTransparentBlt( HDC hdcDest,      // Ŀ��DC
					 int nXOriginDest,   // Ŀ��Xƫ��
					 int nYOriginDest,   // Ŀ��Yƫ��
					 int nWidthDest,     // Ŀ����
					 int nHeightDest,    // Ŀ��߶�
					 HDC hdcSrc,         // ԴDC
					 int nXOriginSrc,    // ԴX���
					 int nYOriginSrc,    // ԴY���
					 int nWidthSrc,      // Դ���
					 int nHeightSrc,     // Դ�߶�
					 UINT crTransparent  // ͸��ɫ,COLORREF����
					 )
{
	HBITMAP hOldImageBMP, hImageBMP = CreateCompatibleBitmap(hdcDest, nWidthDest, nHeightDest);	// ��������λͼ
	HBITMAP hOldMaskBMP, hMaskBMP = CreateBitmap(nWidthDest, nHeightDest, 1, 1, NULL);			// ������ɫ����λͼ
	HDC		hImageDC = CreateCompatibleDC(hdcDest);
	HDC		hMaskDC = CreateCompatibleDC(hdcDest);
	hOldImageBMP = (HBITMAP)SelectObject(hImageDC, hImageBMP);
	hOldMaskBMP = (HBITMAP)SelectObject(hMaskDC, hMaskBMP);
	// ��ԴDC�е�λͼ��������ʱDC��
	if (nWidthDest == nWidthSrc && nHeightDest == nHeightSrc)
		BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY);
	else
		StretchBlt(hImageDC, 0, 0, nWidthDest, nHeightDest,
		hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, SRCCOPY);
	// ����͸��ɫ
	SetBkColor(hImageDC, crTransparent);
	// ����͸������Ϊ��ɫ����������Ϊ��ɫ������λͼ
	BitBlt(hMaskDC, 0, 0, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCCOPY);
	// ����͸������Ϊ��ɫ���������򱣳ֲ����λͼ
	SetBkColor(hImageDC, RGB(0,0,0));
	SetTextColor(hImageDC, RGB(255,255,255));
	BitBlt(hImageDC, 0, 0, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	// ͸�����ֱ�����Ļ���䣬�������ֱ�ɺ�ɫ
	SetBkColor(hdcDest,RGB(0xff,0xff,0xff));
	SetTextColor(hdcDest,RGB(0,0,0));
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMaskDC, 0, 0, SRCAND);
	// "��"����,��������Ч��
	BitBlt(hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hImageDC, 0, 0, SRCPAINT);
	SelectObject(hImageDC, hOldImageBMP);
	DeleteDC(hImageDC);
	SelectObject(hMaskDC, hOldMaskBMP);
	DeleteDC(hMaskDC);
	DeleteObject(hImageBMP);
	DeleteObject(hMaskBMP);
}
