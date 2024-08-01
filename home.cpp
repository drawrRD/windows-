#include "home.h"


void draw_home(HDC hdc, HDC mdc, HDC bufdc)
{
    //建立空的位图并置入mdc中,清空mdc
    HBITMAP fullmap;
	fullmap = CreateCompatibleBitmap(hdc,1024, 640);
	SelectObject(mdc,fullmap);

    HBITMAP home, start;
    BITMAP bm, bm_start;
    home = (HBITMAP)LoadImage(NULL, "picture/home.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(home, sizeof(BITMAP), &bm);
    SelectObject(bufdc, home);
    StretchBlt(mdc, 0, 0, 1024, 640, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    start = (HBITMAP)LoadImage(NULL, "picture/start.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(start, sizeof(BITMAP), &bm_start);
    SelectObject(bufdc, start);
    //BitBlt(mdc, 512, 320, bm_start.bmWidth, bm_start.bmHeight, bufdc, 0, 0, SRCCOPY);
    MyTransparentBlt(mdc, 370, 470, bm_start.bmWidth * 8 / 10, bm_start.bmHeight * 8 / 10, bufdc, 0, 0, bm_start.bmWidth, bm_start.bmHeight, RGB(0,0,0));

    //将mdc贴到hdc
    BitBlt(hdc, 0, 0, 1024, 640, mdc, 0, 0, SRCCOPY);

    DeleteObject(fullmap);
}



void draw_pause(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    //Rectangle(mdc, start_map + 512 - 200, 320 - 200, start_map + 512 + 200, 321 + 200);

    HBITMAP pause;
    BITMAP bm;
    pause = (HBITMAP)LoadImage(NULL, "picture/pause.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(pause, sizeof(BITMAP), &bm);
    SelectObject(bufdc, pause);
    MyTransparentBlt(mdc, start_map + 400 - 200, 320 - 200, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(0,0,0));


    BitBlt(hdc, 0, 0, 1024, 640, mdc, start_map, 0, SRCCOPY);
    DeleteObject(pause);
}
