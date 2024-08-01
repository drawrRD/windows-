#include "game1.h"

//bg1.bmp: 512*480
int max_width = 512 * 4;
int max_height = 640;
int fix_width = 512 * 2;
int fix_height = 640;
int start_map = 0;
int eye = 200;
int get_start_map()
{
    return start_map;
}

void init_game1()
{
    //设定人物初始位置和状态
    person1.curx = 100;
    person1.cury = 433;
    person1.w = 0;
    person1.h = 0;
    person1.cur_hp = person1.hp;
    person1.cur_mp = person1.mp;
    person1.direction = 1;

    person1.if_die = 0;
    person1.die_all_cnt = 5;
    person1.die_cnt = 0;

    person1.if_be_attacked = 0;
    person1.be_a_all_cnt = 2;
    person1.be_a_cnt = 0;

    person1.if_stand = 1;
    person1.stand_all_cnt = 8;
    person1.stand_cnt = 0;

    person1.if_walk = 0;
    person1.walk_all_cnt = 8;
    person1.walk_cnt = 0;
    person1.walk_dis = 13;

    person1.if_run = 0;
    person1.run_all_cnt = 6;
    person1.run_cnt = 0;
    person1.run_dis = 30;

    person1.if_jump = 0;
    person1.jump_all_cnt = 8;
    person1.jump_cnt = 0;
    person1.jump_height = 25;

    person1.if_attack = 0;
    person1.attack_all_cnt = 10;
    person1.attack_cnt = 0;

    person1.if_dj = 0;
    person1.dj_all_cnt = 9;
    person1.dj_cnt = 0;

    person1.if_u = 0;
    person1.u_all_cnt = 6;
    person1.u_cnt = 0;

    person1.if_i = 0;
    person1.i_all_cnt = 5;
    person1.i_cnt = 0;

    person1.if_o = 0;
    person1.o_all_cnt = 6;
    person1.o_cnt = 0;

    person1.if_p = 0;
    person1.p_all_cnt = 6;
    person1.p_cnt = 0;

    //设定怪物初始位置和状态
    for (int i = 0; i < mt1_num; i++)
    {
        mt1[i].curx = 400 + i * 300;
        mt1[i].cury = 458;
        mt1[i].eye = 600;
        mt1[i].hp = 200;
        mt1[i].cur_hp = mt1[i].hp;
        mt1[i].direction = 0;
        mt1[i].if_die = 0;

        mt1[i].if_be_attacked = 0;
        mt1[i].be_a_all_cnt = 2;
        mt1[i].be_a_cnt = 0;

        mt1[i].if_stand = 1;
        mt1[i].stand_all_cnt = 8;
        mt1[i].stand_cnt = 0;

        mt1[i].if_walk = 0;
        mt1[i].walk_all_cnt = 6;
        mt1[i].walk_cnt = 0;
        mt1[i].walk_dis = 6;

        mt1[i].if_attack = 0;
        mt1[i].attack_all_cnt = 4;
        mt1[i].attack_cnt = 0;
        mt1[i].attack_harm = 5;
    }

}


void draw_game1(HDC hdc, HDC mdc, HDC bufdc)
{
    //建立空的位图并置入mdc中,清空mdc
    HBITMAP fullmap;
	fullmap = CreateCompatibleBitmap(hdc,max_width, max_height);
	SelectObject(mdc,fullmap);

    draw_map1(hdc, mdc, bufdc);

    if (if_win == 1)
        draw_success1(hdc, mdc, bufdc);
    else
        draw_monsters(hdc, mdc, bufdc);

    draw_person1(hdc, mdc, bufdc);

    judge1();

    draw_ui(hdc, mdc, bufdc, start_map);

    draw_mt1_hp(hdc, mdc, bufdc, start_map);

    person1.cur_mp += 5;
    if (person1.cur_mp >= person1.mp)
        person1.cur_mp = person1.mp;


    //将mdc贴到hdc
    BitBlt(hdc, 0, 0, fix_width, fix_height, mdc, start_map, 0, SRCCOPY);

    DeleteObject(fullmap);
}

void draw_success1(HDC hdc, HDC mdc, HDC bufdc)
{
    if (if_win == 1)
    {
        HBITMAP s, w;
        BITMAP bm_s, bm_w;
        s = (HBITMAP)LoadImage(NULL, "picture/success.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(s, sizeof(BITMAP), &bm_s);
        SelectObject(bufdc, s);
        MyTransparentBlt(mdc, 1800, 235, bm_s.bmWidth, bm_s.bmHeight, bufdc, 0, 0, bm_s.bmWidth, bm_s.bmHeight, RGB(255,255,255));
        w = (HBITMAP)LoadImage(NULL, "picture/w.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(w, sizeof(BITMAP), &bm_w);
        SelectObject(bufdc, w);
        MyTransparentBlt(mdc, 1750, 240, bm_w.bmWidth, bm_w.bmHeight, bufdc, 0, 0, bm_w.bmWidth, bm_w.bmHeight, RGB(0,0,0));

        DeleteObject(s);
        DeleteObject(w);
    }
}


void draw_map1(HDC hdc, HDC mdc, HDC bufdc)
{
    //贴背景图
    HBITMAP bg;
    BITMAP bm;
    bg = (HBITMAP)LoadImage(NULL, "picture/bg1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(bg, sizeof(BITMAP), &bm);
    SelectObject(bufdc, bg);
    BitBlt(mdc, 0, 0, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, SRCCOPY);
    BitBlt(mdc, bm.bmWidth, 0, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, SRCCOPY);
    BitBlt(mdc, bm.bmWidth * 2, 0, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, SRCCOPY);
    BitBlt(mdc, bm.bmWidth * 3, 0, bm.bmWidth, bm.bmHeight, bufdc, 0, 0, SRCCOPY);
    //贴地形
    HBITMAP floor1;
    BITMAP bm1;
    floor1 = (HBITMAP)LoadImage(NULL, "picture/floor1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    GetObject(floor1, sizeof(BITMAP), &bm1);
    SelectObject(bufdc, floor1);
    MyTransparentBlt(mdc, 0, bm.bmHeight - 8, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    MyTransparentBlt(mdc, bm1.bmWidth * 1, bm.bmHeight - 8, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    MyTransparentBlt(mdc, bm1.bmWidth * 2, bm.bmHeight - 8, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));
    MyTransparentBlt(mdc, bm1.bmWidth * 3, bm.bmHeight - 8, bm1.bmWidth, bm1.bmHeight, bufdc, 0, 0, bm1.bmWidth, bm1.bmHeight, RGB(255,255,255));

    DeleteObject(bg);
    DeleteObject(floor1);
}

void draw_person1(HDC hdc, HDC mdc, HDC bufdc)
{
    //贴人物
    HBITMAP standl[10], standr[10], walkl[10], walkr[10], runl[10], runr[10], jump[10], attackl[10], attackr[10], dj[10], u[10], ii[10], ol[10], orr[10], pl[10], pr[10], be_a[10], die[10];
    BITMAP bm_standl[10], bm_standr[10], bm_walkl[10], bm_walkr[10], bm_runl[10], bm_runr[10], bm_jump[10], bm_attackl[10], bm_attackr[10],
    bm_dj[10], bm_u[10], bm_ii[10], bm_ol[10], bm_or[10],  bm_pl[10], bm_pr[10], bm_be_a[10], bm_die[10];
    for (int i = 0; i < person1.stand_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/standl%d.bmp", i);
        standl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(standl[i], sizeof(BITMAP), &bm_standl[i]);
        sprintf(path, "person1/standr%d.bmp", i);
        standr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(standr[i], sizeof(BITMAP), &bm_standr[i]);
    }
    for (int i = 0; i < person1.walk_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/walkl%d.bmp", i);
        walkl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(walkl[i], sizeof(BITMAP), &bm_walkl[i]);
        sprintf(path, "person1/walkr%d.bmp", i);
        walkr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(walkr[i], sizeof(BITMAP), &bm_walkr[i]);
    }
    for (int i = 0; i < person1.run_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/runl%d.bmp", i);
        runl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(runl[i], sizeof(BITMAP), &bm_runl[i]);
        sprintf(path, "person1/runr%d.bmp", i);
        runr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(runr[i], sizeof(BITMAP), &bm_runr[i]);
    }
    for (int i = 0; i < person1.jump_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/jump%d.bmp", i);
        jump[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(jump[i], sizeof(BITMAP), &bm_jump[i]);
    }
    for (int i = 0; i < person1.attack_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/attackl%d.bmp", i);
        attackl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(attackl[i], sizeof(BITMAP), &bm_attackl[i]);
        sprintf(path, "person1/attackr%d.bmp", i);
        attackr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(attackr[i], sizeof(BITMAP), &bm_attackr[i]);
    }
    for (int i = 0; i < person1.dj_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/dj%d.bmp", i);
        dj[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(dj[i], sizeof(BITMAP), &bm_dj[i]);
    }
    for (int i = 0; i < person1.u_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/u%d.bmp", i);
        u[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(u[i], sizeof(BITMAP), &bm_u[i]);
    }
    for (int i = 0; i < person1.i_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/i%d.bmp", i);
        ii[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(ii[i], sizeof(BITMAP), &bm_ii[i]);
    }
    for (int i = 0; i < person1.o_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/ol%d.bmp", i);
        ol[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(ol[i], sizeof(BITMAP), &bm_ol[i]);
        sprintf(path, "person1/or%d.bmp", i);
        orr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(orr[i], sizeof(BITMAP), &bm_or[i]);
    }
    for (int i = 0; i < person1.p_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/pl%d.bmp", i);
        pl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(pl[i], sizeof(BITMAP), &bm_pl[i]);
        sprintf(path, "person1/pr%d.bmp", i);
        pr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(pr[i], sizeof(BITMAP), &bm_pr[i]);
    }
    for (int i = 0; i < person1.be_a_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/be_a%d.bmp", i);
        be_a[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(be_a[i], sizeof(BITMAP), &bm_be_a[i]);
    }
    for (int i = 0; i < person1.die_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "person1/die%d.bmp", i);
        die[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(die[i], sizeof(BITMAP), &bm_die[i]);
    }

    if (person1.if_die == 1)
    {
        int i = person1.die_cnt;
        int tz = 0;
        if (i >= 3)
            tz = 30;
        if (i < person1.die_all_cnt)
        {
            SelectObject(bufdc, die[i]);
            person1.w = bm_die[i].bmWidth * 6 / 20;
            person1.h = bm_die[i].bmHeight * 6 / 20;

            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h + tz, bm_die[i].bmWidth * 6 / 10, bm_die[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_die[i].bmWidth, bm_die[i].bmHeight, RGB(255,255,255));
            person1.die_cnt++;
        }

        if (person1.die_cnt == person1.die_all_cnt)
        {
            return;
        }
    }


    if (person1.if_stand == 1)
    {
        int i = person1.stand_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, standl[i]);
            person1.w = bm_standl[i].bmWidth * 6 / 20;
            person1.h = bm_standl[i].bmHeight * 6 / 20;

            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_standl[i].bmWidth * 6 / 10, bm_standl[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_standl[i].bmWidth, bm_standl[i].bmHeight, RGB(255,255,255));
        }
        if (person1.direction == 1)
        {
            SelectObject(bufdc, standr[i]);
            person1.w = bm_standr[i].bmWidth * 6 / 20;
            person1.h = bm_standr[i].bmHeight * 6 / 20;

            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_standr[i].bmWidth * 6 / 10, bm_standr[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_standr[i].bmWidth, bm_standr[i].bmHeight, RGB(255,255,255));
        }

        person1.stand_cnt++;
        if (person1.stand_cnt == person1.stand_all_cnt)
        {
            person1.stand_cnt = 0;
        }
    }

    if (person1.if_walk == 1)
    {
        int i = person1.walk_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, walkl[i]);
            person1.w = bm_walkl[i].bmWidth * 6 / 20;
            person1.h = bm_walkl[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w , person1.cury - person1.h, bm_walkl[i].bmWidth * 6 / 10, bm_walkl[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_walkl[i].bmWidth, bm_walkl[i].bmHeight, RGB(255,255,255));
            person1.curx -= person1.walk_dis;
        }
        else if (person1.direction == 1)
        {
            SelectObject(bufdc, walkr[i]);
            person1.w = bm_walkr[i].bmWidth * 6 / 20;
            person1.h = bm_walkr[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w , person1.cury - person1.h, bm_walkr[i].bmWidth * 6 / 10, bm_walkr[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_walkr[i].bmWidth, bm_walkr[i].bmHeight, RGB(255,255,255));
            person1.curx += person1.walk_dis;
        }
        person1.walk_cnt++;
        if (person1.walk_cnt == person1.walk_all_cnt)
        {
            person1.walk_cnt = 0;
        }
    }

    if (person1.if_run == 1)
    {
        int i = person1.run_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, runl[i]);
            person1.w = bm_runl[i].bmWidth * 6 / 20;
            person1.h = bm_runl[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w + 8, person1.cury - person1.h, bm_runl[i].bmWidth * 6 / 10, bm_runl[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_runl[i].bmWidth, bm_runl[i].bmHeight, RGB(255,255,255));
            person1.curx -= person1.run_dis;
        }
        else if (person1.direction == 1)
        {
            SelectObject(bufdc, runr[i]);
            person1.w = bm_runr[i].bmWidth * 6 / 20;
            person1.h = bm_runr[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_runr[i].bmWidth * 6 / 10, bm_runr[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_runr[i].bmWidth, bm_runr[i].bmHeight, RGB(255,255,255));
            person1.curx += person1.run_dis;
        }
        person1.run_cnt++;
        if (person1.run_cnt == person1.run_all_cnt)
        {
            person1.run_cnt = 0;
        }
    }

    if (person1.if_jump == 1)
    {
        if (person1.jump_cnt < 4)
        {
            person1.cury -= person1.jump_height;
        }
        else if (person1.jump_cnt < 8)
        {
            person1.cury += person1.jump_height;
        }
        int i = person1.jump_cnt;
        SelectObject(bufdc, jump[i]);
        person1.w = bm_jump[i].bmWidth * 6 / 20;
        person1.h = bm_jump[i].bmHeight * 6 / 20;

        MyTransparentBlt(mdc, person1.curx - bm_jump[i].bmWidth * 6 / 20, person1.cury - bm_jump[i].bmHeight * 6 / 20, bm_jump[i].bmWidth * 6 / 10, bm_jump[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_jump[i].bmWidth, bm_jump[i].bmHeight, RGB(255,255,255));
        person1.jump_cnt++;
        if (person1.jump_cnt == person1.jump_all_cnt)
        {
            person1.jump_cnt = 0;
            person1.if_jump = 0;
            person1.if_stand = 1;
        }
    }

    if (person1.if_attack == 1)
    {
        int i = person1.attack_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, attackl[i]);
            person1.w = bm_attackl[i].bmWidth * 6 / 20;
            person1.h = bm_attackl[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_attackl[i].bmWidth * 6 / 10, bm_attackl[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_attackl[i].bmWidth, bm_attackl[i].bmHeight, RGB(255,255,255));
        }
        else if (person1.direction == 1)
        {
            SelectObject(bufdc, attackr[i]);
            person1.w = bm_attackr[i].bmWidth * 6 / 20;
            person1.h = bm_attackr[i].bmHeight * 6 / 20;
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_attackr[i].bmWidth * 6 / 10, bm_attackr[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_attackr[i].bmWidth, bm_attackr[i].bmHeight, RGB(255,255,255));
        }
        person1.attack_cnt++;
        if (person1.attack_cnt == person1.attack_all_cnt)
        {
            person1.attack_cnt = 0;
        }
    }

    if (person1.if_dj == 1)
    {
        int i = person1.dj_cnt;
        SelectObject(bufdc, dj[i]);
        person1.w = bm_dj[i].bmWidth * 6 / 20;
        person1.h = bm_dj[i].bmHeight * 6 / 20;

        MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h, bm_dj[i].bmWidth * 6 / 10, bm_dj[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_dj[i].bmWidth, bm_dj[i].bmHeight, RGB(255,255,255));
        person1.dj_cnt++;
        person1.curx += person1.run_dis;
        if (person1.dj_cnt == person1.dj_all_cnt)
        {
            person1.dj_cnt = 0;
        }
    }


    if (person1.if_u == 1)
    {
        int i = person1.u_cnt;
        SelectObject(bufdc, u[i]);
        person1.w = bm_u[i].bmWidth * 6 / 20;
        person1.h = bm_u[i].bmHeight * 6 / 20;
        int tz = 0;
        if(i == 3 || i == 4)
            tz = 10;
        else
            tz = 0;
        MyTransparentBlt(mdc, person1.curx - bm_u[i].bmWidth * 6 / 20, person1.cury - bm_u[i].bmHeight * 6 / 20 - tz, bm_u[i].bmWidth * 6 / 10, bm_u[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_u[i].bmWidth, bm_u[i].bmHeight, RGB(255,255,255));
        person1.u_cnt++;
        if (person1.u_cnt == person1.u_all_cnt)
        {
            person1.u_cnt = 0;
            person1.if_u = 0;
            person1.if_stand = 1;
        }
    }

    if (person1.if_i == 1)
    {
        int i = person1.i_cnt;
        SelectObject(bufdc, ii[i]);
        person1.w = bm_ii[i].bmWidth * 6 / 20;
        person1.h = bm_ii[i].bmHeight * 6 / 20;
        int tz = 0;
        if(i == 3 || i == 4)
            tz = 60;
        else
            tz = 10;
        MyTransparentBlt(mdc, person1.curx - bm_ii[i].bmWidth * 6 / 20, person1.cury - bm_ii[i].bmHeight * 6 / 20 - tz, bm_ii[i].bmWidth * 6 / 10, bm_ii[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_ii[i].bmWidth, bm_ii[i].bmHeight, RGB(255,255,255));
        person1.i_cnt++;
        if (person1.i_cnt == person1.i_all_cnt)
        {
            person1.i_cnt = 0;
            person1.if_i = 0;
            person1.if_stand = 1;
        }
    }

    if (person1.if_o == 1)
    {
        int i = person1.o_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, ol[i]);
            person1.w = bm_ol[i].bmWidth * 6 / 20;
            person1.h = bm_ol[i].bmHeight * 6 / 20;
            int tz = 10;
            if (i >= 1)
            {
                person1.curx -= 50;
            }
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h + tz, bm_ol[i].bmWidth * 6 / 10, bm_ol[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_ol[i].bmWidth, bm_ol[i].bmHeight, RGB(255,255,255));
        }
        else if (person1.direction == 1)
        {
            SelectObject(bufdc, orr[i]);
            person1.w = bm_or[i].bmWidth * 6 / 20;
            person1.h = bm_or[i].bmHeight * 6 / 20;
            int tz = 10;
            if (i >= 1)
            {
                person1.curx += 50;
            }
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h + tz, bm_or[i].bmWidth * 6 / 10, bm_or[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_or[i].bmWidth, bm_or[i].bmHeight, RGB(255,255,255));
        }
        person1.o_cnt++;
        if (person1.o_cnt == person1.o_all_cnt)
        {
            person1.o_cnt = 0;
            person1.if_o = 0;
            person1.if_stand = 1;
        }
    }

    if (person1.if_p == 1)
    {
        int i = person1.p_cnt;
        if (person1.direction == 0)
        {
            SelectObject(bufdc, pl[i]);
            person1.w = bm_pl[i].bmWidth * 6 / 20;
            person1.h = bm_pl[i].bmHeight * 6 / 20;
            int tz = 0;
            if (i >= 1)
            {
                person1.curx += 40;
            }
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h + tz, bm_pl[i].bmWidth * 6 / 10, bm_pl[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_pl[i].bmWidth, bm_pl[i].bmHeight, RGB(255,255,255));
        }
        else if (person1.direction == 1)
        {
            SelectObject(bufdc, pr[i]);
            person1.w = bm_pr[i].bmWidth * 6 / 20;
            person1.h = bm_pr[i].bmHeight * 6 / 20;
            int tz = 0;
            if (i >= 1)
            {
                person1.curx -= 40;
            }
            MyTransparentBlt(mdc, person1.curx - person1.w, person1.cury - person1.h + tz, bm_pr[i].bmWidth * 6 / 10, bm_pr[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_pr[i].bmWidth, bm_pr[i].bmHeight, RGB(255,255,255));
        }

        person1.p_cnt++;
        if (person1.p_cnt == person1.p_all_cnt)
        {
            person1.p_cnt = 0;
            person1.if_p = 0;
            person1.if_stand = 1;
        }
    }

    if (person1.if_be_attacked == 1)
    {
        int i = person1.be_a_cnt;
        SelectObject(bufdc, be_a[i]);
        person1.w = bm_be_a[i].bmWidth * 6 / 20;
        person1.h = bm_be_a[i].bmHeight * 6 / 20;
        int tz = 15;
        MyTransparentBlt(mdc, person1.curx - bm_be_a[i].bmWidth * 6 / 20, person1.cury - bm_be_a[i].bmHeight * 6 / 20 - tz, bm_be_a[i].bmWidth * 6 / 10, bm_be_a[i].bmHeight * 6 / 10, bufdc, 0, 0, bm_be_a[i].bmWidth, bm_be_a[i].bmHeight, RGB(255,255,255));
        person1.be_a_cnt++;
        if (person1.be_a_cnt == person1.be_a_all_cnt)
        {
            person1.be_a_cnt = 0;
            person1.if_be_attacked = 0;
            person1.if_stand = 1;
        }
    }

//    POINT fzp[5] = { {person1.curx - person1.w, person1.cury - person1.h}, {person1.curx + person1.w, person1.cury - person1.h},
//                            {person1.curx + person1.w, person1.cury + person1.h}, {person1.curx - person1.w, person1.cury + person1.h}, {person1.curx - person1.w, person1.cury - person1.h}};
//    Polyline(mdc, fzp, 5);
//    char s[50];
//    sprintf(s, "%d", person1.cur_hp);
//    TextOut(mdc, person1.curx,  person1.cury - person1.h - 20, s, strlen(s));



    //判断人物移动边界
    if (person1.curx + person1.w > max_width)
    {
        person1.curx = max_width - person1.w;
    }
    if (person1.curx - person1.w < 0)
    {
        person1.curx = person1.w;
    }
    if (person1.curx + person1.w + eye >= max_width)
    {
        start_map = max_width - fix_width;
    }
    else if (person1.curx + person1.w + eye - start_map > fix_width)
    {
        start_map = person1.curx + person1.w + eye - fix_width;
    }
    if (person1.curx - person1.w - eye <= 0)
    {
        start_map = 0;
    }
    else if (person1.curx - person1.w - eye - start_map < 0)
    {
        start_map = person1.curx - person1.w - eye;
    }

    for (int i = 0; i < 8; i++)
    {
        DeleteObject(standl[i]);
        DeleteObject(standl[i]);
        DeleteObject(walkl[i]);
        DeleteObject(walkr[i]);
        DeleteObject(runl[i]);
        DeleteObject(runr[i]);
        DeleteObject(jump[i]);
    }
    for (int i = 0; i < person1.attack_all_cnt; i++)
        DeleteObject(attackl[i]), DeleteObject(attackr[i]);
    for (int i = 0; i < person1.dj_all_cnt; i++)
        DeleteObject(dj[i]);
    for (int i = 0; i < person1.u_all_cnt; i++)
        DeleteObject(u[i]);
    for (int i = 0; i < person1.i_all_cnt; i++)
        DeleteObject(ii[i]);
    for (int i = 0; i < person1.o_all_cnt; i++)
        DeleteObject(ol[i]), DeleteObject(orr[i]);
    for (int i = 0; i < person1.p_all_cnt; i++)
        DeleteObject(pl[i]), DeleteObject(pr[i]);
    for (int i = 0; i < person1.be_a_all_cnt; i++)
        DeleteObject(be_a[i]);
    for (int i = 0; i < person1.die_all_cnt; i++)
        DeleteObject(die[i]);
}


void draw_monsters(HDC hdc, HDC mdc, HDC bufdc)
{
    //贴怪物
    HBITMAP stand[10], walkl[10], walkr[10], attackl[10], attackr[10], be_al[10], be_ar[10];
    BITMAP bm_stand[10], bm_walkl[10], bm_walkr[10], bm_attackl[10], bm_attackr[10], bm_be_al[10], bm_be_ar[10];
    for (int i = 0; i < mt1[0].stand_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "mt1/stand%d.bmp", i);
        stand[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(stand[i], sizeof(BITMAP), &bm_stand[i]);
    }
    for (int i = 0; i < mt1[0].walk_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "mt1/walkl%d.bmp", i);
        walkl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(walkl[i], sizeof(BITMAP), &bm_walkl[i]);

        sprintf(path, "mt1/walkr%d.bmp", i);
        walkr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(walkr[i], sizeof(BITMAP), &bm_walkr[i]);
    }
    for (int i = 0; i < mt1[0].attack_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "mt1/attackl%d.bmp", i);
        attackl[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(attackl[i], sizeof(BITMAP), &bm_attackl[i]);
        sprintf(path, "mt1/attackr%d.bmp", i);
        attackr[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(attackr[i], sizeof(BITMAP), &bm_attackr[i]);
    }
    for (int i = 0; i < mt1[0].be_a_all_cnt; i++)
    {
        char path[100];
        sprintf(path, "mt1/be_al%d.bmp", i);
        be_al[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(be_al[i], sizeof(BITMAP), &bm_be_al[i]);
        sprintf(path, "mt1/be_ar%d.bmp", i);
        be_ar[i] = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(be_ar[i], sizeof(BITMAP), &bm_be_ar[i]);
    }


    for (int i = 0; i < mt1_num; i++)
    {
        if (mt1[i].if_die == 1)
        {
            continue;
        }

        if (mt1[i].if_stand == 1)
        {
            int j = mt1[i].stand_cnt;
            SelectObject(bufdc, stand[j]);
            mt1[i].w = bm_stand[j].bmWidth / 2;
            mt1[i].h = bm_stand[j].bmHeight / 2;

            MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h, bm_stand[j].bmWidth, bm_stand[j].bmHeight, bufdc, 0, 0, bm_stand[j].bmWidth, bm_stand[j].bmHeight, RGB(255,255,255));
            mt1[i].stand_cnt++;
            if (mt1[i].stand_cnt == mt1[i].stand_all_cnt)
            {
                mt1[i].stand_cnt = 0;
            }
        }

        if (mt1[i].if_walk == 1)
        {
            int j = mt1[i].walk_cnt;
            if (mt1[i].direction == 0)
            {
                SelectObject(bufdc, walkl[j]);
                mt1[i].w = bm_walkl[j].bmWidth / 2;
                mt1[i].h = bm_walkl[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 6, bm_walkl[j].bmWidth, bm_walkl[j].bmHeight, bufdc, 0, 0, bm_walkl[j].bmWidth, bm_walkl[j].bmHeight, RGB(255,255,255));
                mt1[i].curx -= mt1[i].walk_dis;
            }
            else if (mt1[i].direction == 1)
            {
                SelectObject(bufdc, walkr[j]);
                mt1[i].w = bm_walkr[j].bmWidth / 2;
                mt1[i].h = bm_walkr[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 6, bm_walkr[j].bmWidth, bm_walkr[j].bmHeight, bufdc, 0, 0, bm_walkr[j].bmWidth, bm_walkr[j].bmHeight, RGB(255,255,255));
                mt1[i].curx += mt1[i].walk_dis;
            }
            mt1[i].walk_cnt++;
            if (mt1[i].walk_cnt == mt1[i].walk_all_cnt)
            {
                mt1[i].walk_cnt = 0;
            }
        }

        if (mt1[i].if_attack == 1)
        {
            int j = mt1[i].attack_cnt;
            if (mt1[i].direction == 0)
            {
                SelectObject(bufdc, attackl[j]);
                mt1[i].w = bm_attackl[j].bmWidth / 2;
                mt1[i].h = bm_attackl[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 10, bm_attackl[j].bmWidth, bm_attackl[j].bmHeight, bufdc, 0, 0, bm_attackl[j].bmWidth, bm_attackl[j].bmHeight, RGB(255,255,255));
            }
            else if (mt1[i].direction == 1)
            {
                SelectObject(bufdc, attackr[j]);
                mt1[i].w = bm_attackr[j].bmWidth / 2;
                mt1[i].h = bm_attackr[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 10, bm_attackr[j].bmWidth, bm_attackr[j].bmHeight, bufdc, 0, 0, bm_attackr[j].bmWidth, bm_attackr[j].bmHeight, RGB(255,255,255));
            }
            mt1[i].attack_cnt++;
            if (mt1[i].attack_cnt == mt1[i].attack_all_cnt)
            {
                mt1[i].attack_cnt = 0;
                mt1[i].if_attack = 0;
            }
        }

        if (mt1[i].if_be_attacked == 1)
        {
            int j = mt1[i].be_a_cnt;
            if (mt1[i].direction == 0)
            {
                SelectObject(bufdc, be_al[j]);
                mt1[i].w = bm_be_al[j].bmWidth / 2;
                mt1[i].h = bm_be_al[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 10, bm_be_al[j].bmWidth, bm_be_al[j].bmHeight, bufdc, 0, 0, bm_be_al[j].bmWidth, bm_be_al[j].bmHeight, RGB(255,255,255));
            }
            if (mt1[i].direction == 1)
            {
                SelectObject(bufdc, be_ar[j]);
                mt1[i].w = bm_be_ar[j].bmWidth / 2;
                mt1[i].h = bm_be_ar[j].bmHeight / 2;
                MyTransparentBlt(mdc, mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h - 10, bm_be_ar[j].bmWidth, bm_be_ar[j].bmHeight, bufdc, 0, 0, bm_be_ar[j].bmWidth, bm_be_ar[j].bmHeight, RGB(255,255,255));
            }
            mt1[i].be_a_cnt++;
            if (mt1[i].be_a_cnt == mt1[i].be_a_all_cnt)
            {
                mt1[i].be_a_cnt = 0;
                mt1[i].if_be_attacked = 0;
            }
        }



//        POINT fzp[5] = { {mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h}, {mt1[i].curx + mt1[i].w, mt1[i].cury - mt1[i].h},
//                            {mt1[i].curx + mt1[i].w, mt1[i].cury + mt1[i].h}, {mt1[i].curx - mt1[i].w, mt1[i].cury + mt1[i].h}, {mt1[i].curx - mt1[i].w, mt1[i].cury - mt1[i].h}};
//        Polyline(mdc, fzp, 5);
//        char s[50];
//        sprintf(s, "%d", mt1[i].cur_hp);
//        TextOut(mdc, mt1[i].curx, mt1[i].cury - mt1[i].w - 20, s, strlen(s));
    }


    for (int i = 0; i < mt1[0].stand_all_cnt; i++)
        DeleteObject(stand[i]);
    for (int i = 0; i < mt1[0].walk_all_cnt; i++)
        DeleteObject(walkl[i]), DeleteObject(walkr[i]);
    for (int i = 0; i < mt1[0].attack_all_cnt; i++)
        DeleteObject(attackl[i]), DeleteObject(attackr[i]);
    for (int i = 0; i < mt1[0].be_a_all_cnt; i++)
        DeleteObject(be_al[i]), DeleteObject(be_ar[i]);
}
