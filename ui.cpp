#include "ui.h"


void draw_ui(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    draw_p_hp(hdc, mdc, bufdc, start_map);

    draw_skill(hdc, mdc, bufdc, start_map);


}

void draw_skill(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    HBITMAP s1, s2, s3, s4;
    BITMAP bm1, bm2, bm3, bm4;
    s1 = (HBITMAP)LoadImage(NULL, "picture/s1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    s2 = (HBITMAP)LoadImage(NULL, "picture/s2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    s3 = (HBITMAP)LoadImage(NULL, "picture/s3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    s4 = (HBITMAP)LoadImage(NULL, "picture/s4.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(s1, sizeof(BITMAP), &bm1);
    SelectObject(bufdc, s1);
    MyTransparentBlt(mdc, start_map + 750, 510, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    SelectObject(bufdc, s2);
    MyTransparentBlt(mdc, start_map + 810, 510, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    SelectObject(bufdc, s3);
    MyTransparentBlt(mdc, start_map + 870, 510, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    SelectObject(bufdc, s4);
    MyTransparentBlt(mdc, start_map + 930, 510, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));


    DeleteObject(s1);
    DeleteObject(s2);
    DeleteObject(s3);
    DeleteObject(s4);
}


void draw_p_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    HBITMAP p_hp, p;
    BITMAP bm;
    p_hp = (HBITMAP)LoadImage(NULL, "picture/hp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(p_hp, sizeof(BITMAP), &bm);
    SelectObject(bufdc, p_hp);
    MyTransparentBlt(mdc, start_map + 43, 30, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255,255,255));
    MyTransparentBlt(mdc, start_map + 43, 45, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255,255,255));

    p = (HBITMAP)LoadImage(NULL, "picture/person.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(p, sizeof(BITMAP), &bm);
    SelectObject(bufdc, p);
    MyTransparentBlt(mdc, start_map, 17, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255,255,255));


    HPEN hp = CreatePen(PS_SOLID,1,RGB(255,0,0));
    SelectObject(mdc, hp);
    HBRUSH hbr = CreateSolidBrush(RGB(255,0,0));
    SelectObject(mdc, hbr);
    if (person1.cur_hp > 0)
        Rectangle(mdc, start_map + 43, 30, start_map + 43 + 200 * cal_hp(1, -1), 42);

    hp = CreatePen(PS_SOLID,1,RGB(0,0,200));
    SelectObject(mdc, hp);
    hbr = CreateSolidBrush(RGB(0,0,200));
    SelectObject(mdc, hbr);
    if (person1.cur_mp > 0)
        Rectangle(mdc, start_map + 43, 45, start_map + 43 + 200 * cal_mp(), 57);

    DeleteObject(hp);
    DeleteObject(hbr);
    DeleteObject(p_hp);
    DeleteObject(p);
}


void draw_boss_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    HPEN hp = CreatePen(PS_SOLID,1,RGB(255,0,0));
    SelectObject(mdc, hp);
    HBRUSH hbr = CreateSolidBrush(RGB(255,0,0));
    SelectObject(mdc, hbr);

    if (mt2.cur_hp > 0)
    {
        Rectangle(mdc, start_map + 135, 120, start_map + 135 + 800 * cal_hp(2, -1), 130);

        HBITMAP p;
        BITMAP bm;
        p = (HBITMAP)LoadImage(NULL, "mt2/1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(p, sizeof(BITMAP), &bm);
        SelectObject(bufdc, p);
        MyTransparentBlt(mdc, start_map + 98, 100, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, bm.bmWidth, bm.bmHeight, RGB(255,255,255));
    }


    DeleteObject(hp);
    DeleteObject(hbr);
}

void draw_mt1_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map)
{
    for (int i = 0; i < mt1_num; i++)
    {
        if (mt1[i].if_be_attacked == 1)
        {
            if (mt1[i].cur_hp > 0)
            {
                HPEN hp = CreatePen(PS_SOLID,1,RGB(255,0,0));
                SelectObject(mdc, hp);
                HBRUSH hbr = CreateSolidBrush(RGB(255,0,0));
                SelectObject(mdc, hbr);
                Rectangle(mdc, mt1[i].curx - 30, mt1[i].cury - 65, mt1[i].curx - 30 + 80 * cal_hp(3, i), mt1[i].cury - 55);
                DeleteObject(hp);
                DeleteObject(hbr);
            }
        }
    }
}


double cal_hp(int who, int i)
{
    //1: person
    if (who == 1)
    {
        if (person1.cur_hp <= 0)
        {
            return 0;
        }
        double rate = (1.0 * person1.cur_hp) / (1.0 * person1.hp);
        return rate;
    }
    //2:boss
    else if (who == 2)
    {
        if (mt2.cur_hp <= 0)
        {
            return 0;
        }
        double rate = (1.0 * mt2.cur_hp) / (1.0 * mt2.hp);
        return rate;
    }
    //3:mt1
    else if (who == 3)
    {
        if (mt1[i].cur_hp <= 0)
        {
            return 0;
        }
        double rate = (1.0 * mt1[i].cur_hp) / (1.0 * mt1[i].hp);
        return rate;
    }
    return 0;
}

double cal_mp()
{
    if (person1.cur_mp <= 0)
    {
        return 0;
    }
    double rate = (1.0 * person1.cur_mp) / (1.0 * person1.mp);
    return rate;
}
