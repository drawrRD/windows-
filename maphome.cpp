#include "maphome.h"


void draw_maphome(HDC hdc, HDC mdc, HDC bufdc, int i)
{
    //建立空的位图并置入mdc中,清空mdc
    HBITMAP fullmap;
	fullmap = CreateCompatibleBitmap(hdc,1024, 640);
	SelectObject(mdc,fullmap);

    HBITMAP home;
    BITMAP bm;
    if (i == -1)
    {
        home = (HBITMAP)LoadImage(NULL, "picture/map.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(home, sizeof(BITMAP), &bm);
        SelectObject(bufdc, home);
        BitBlt(mdc, 0, 0, 1024, 640, bufdc, 0, 0, SRCCOPY);
    }
    else if (i == 1)
    {
        home = (HBITMAP)LoadImage(NULL, "picture/map1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(home, sizeof(BITMAP), &bm);
        SelectObject(bufdc, home);
        BitBlt(mdc, 0, 0, 1024, 640, bufdc, 0, 0, SRCCOPY);
    }
    else if (i == 2)
    {
        home = (HBITMAP)LoadImage(NULL, "picture/map2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(home, sizeof(BITMAP), &bm);
        SelectObject(bufdc, home);
        BitBlt(mdc, 0, 0, 1024, 640, bufdc, 0, 0, SRCCOPY);
    }


    //将mdc贴到hdc
    BitBlt(hdc, 0, 0, 1024, 640, mdc, 0, 0, SRCCOPY);

    DeleteObject(fullmap);

}
