#include <windows.h>
#include <math.h>
#include <time.h>

#ifndef CHARACTER_H
#define CHARACTER_H

struct Person
{
    int curx;
    int cury;
    int w, h;

    int hp;
    int cur_hp;
    int mp;
    int cur_mp;
    int direction;

    bool if_die;
    int die_all_cnt;
    int die_cnt;

    bool if_be_attacked;
    int be_a_all_cnt;
    int be_a_cnt;

    //静止站立
    bool if_stand;
    int stand_all_cnt; //总静止帧数
    int stand_cnt; //当前静止帧数
    //走动
    bool if_walk;
    int walk_all_cnt; //总走动帧数
    int walk_cnt; //当前走动帧数
    int walk_dis; //走动距离
    //跑动
    bool if_run;
    int run_all_cnt;
    int run_cnt;
    int run_dis;
    //跳跃
    bool if_jump;
    int jump_all_cnt;
    int jump_cnt;
    int jump_height;
    //普通攻击1
    bool if_attack;
    int attack_all_cnt;
    int attack_cnt;
    int attack_harm;
    //跑动攻击1
    bool if_dj;
    int dj_all_cnt;
    int dj_cnt;
    int dj_harm;
    //技能1
    bool if_u;
    int u_all_cnt;
    int u_cnt;
    int u_harm;
    //技能2
    bool if_i;
    int i_all_cnt;
    int i_cnt;
    int i_harm;
    //技能3
    bool if_o;
    int o_all_cnt;
    int o_cnt;
    int o_harm;
    //技能4
    bool if_p;
    int p_all_cnt;
    int p_cnt;
    int p_harm;
};
extern Person person1;

extern void clear_state();

extern void init_person_state();

extern void MyTransparentBlt( HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,
					 HDC hdcSrc,int nXOriginSrc,int nYOriginSrc,int nWidthSrc,int nHeightSrc,UINT crTransparent);

extern void MySound();



struct Monsters
{
    int curx;
    int cury;
    int w, h;
    int eye;
    int direction;

    int hp;
    int cur_hp;

    bool if_die;
    int die_all_cnt;
    int die_cnt;

    //静止站立
    bool if_stand;
    int stand_all_cnt;
    int stand_cnt;
    //走动
    bool if_walk;
    int walk_all_cnt;
    int walk_cnt;
    int walk_dis;
    //跑动
    bool if_run;
    int run_all_cnt;
    int run_cnt;
    int run_dis;
    //普通攻击
    bool if_attack;
    int attack_all_cnt;
    int attack_cnt;
    int attack_harm;
    //被攻击
    bool if_be_attacked;
    int be_a_all_cnt;
    int be_a_cnt;
    //抵挡
    bool if_resist;
    int resist_all_cnt;
    int resist_cnt;
    int recover;
    //冲撞
    bool if_rush;
    int rush_all_cnt;
    int rush_cnt;
    int rush_dis;
    int rush_harm;
    //远程
    bool if_ra;
    int ra_curx, ra_cury, ra_w, ra_h;
    int ra_all_cnt;
    int ra_cnt;
    int ra_dis;
    int ra_harm;
    //技能1
    bool if_kj;
    int kj_all_cnt;
    int kj_cnt;
    int kj_harm;
    int kj_dis;
};

extern Monsters mt1[50], mt2;
extern int mt1_num;

extern int flag;
extern int nowgame;
extern int if_win;



#endif

