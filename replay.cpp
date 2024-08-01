#include "replay.h"

//初始化全局变量
bool if_replay = 0;

DWORD StartTime = GetTickCount();
DWORD EndTime = GetTickCount();

Replay_parameter re[6005];
int t = 0;

void record()
{
    re[++t].cur_hp = person1.cur_hp;
    re[t].cur_mp = person1.cur_mp;
    re[t].if_die = person1.if_die;
    re[t].die_cnt = person1.die_cnt;
    re[t].direction = person1.direction;
    re[t].if_attack = person1.if_attack;
    re[t].if_be_attacked = person1.if_be_attacked;
    re[t].if_stand = person1.if_stand;
    re[t].if_walk = person1.if_walk;
    re[t].if_run = person1.if_run;
    re[t].if_jump = person1.if_jump;
    re[t].if_dj = person1.if_dj;
    re[t].if_u = person1.if_u;
    re[t].if_i = person1.if_i;
    re[t].if_o = person1.if_o;
    re[t].if_p = person1.if_p;

    re[t].cur_hp2 = mt2.cur_hp;
    re[t].if_die2 =  mt2.if_die;
    re[t].die_cnt2 =  mt2.die_cnt;
    re[t].direction2 =  mt2.direction;
    re[t].if_attack2 =  mt2.if_attack;
    re[t].if_be_attacked2 = mt2.if_be_attacked;
    re[t].if_stand2 =  mt2.if_stand;
    re[t].if_walk2 =  mt2.if_walk;
    re[t].if_run2 =  mt2.if_run;
    re[t].if_resist2 = mt2.if_resist;
    re[t].if_rush2 = mt2.if_rush;
    re[t].if_ra2 = mt2.if_ra;
    re[t].if_kj2 = mt2.if_kj;
}


void replay(HDC hdc)
{
    EndTime = GetTickCount();
    person1.cur_hp = re[t].cur_hp;
    person1.cur_mp = re[t].cur_mp;
    person1.if_die = re[t].if_die;
    person1.die_cnt = re[t].die_cnt;
    person1.direction = re[t].direction;
    person1.if_attack = re[t].if_attack;
    person1.if_be_attacked = re[t].if_be_attacked;
    person1.if_stand = re[t].if_stand;
    person1.if_walk = re[t].if_walk;
    person1.if_run = re[t].if_run;
    person1.if_jump = re[t].if_jump;
    person1.if_dj = re[t].if_dj;
    person1.if_u = re[t].if_u;
    person1.if_i = re[t].if_i;
    person1.if_o = re[t].if_o;
    person1.if_p = re[t].if_p;
    if (re[t].if_die == 1 && re[t].die_cnt == person1.die_all_cnt)
    {
        if_replay = 0;
        if_win = -1;
        return;
    }
    mt2.cur_hp = re[t].cur_hp2;
    mt2.if_die =  re[t].if_die2;
    mt2.die_cnt =  re[t].die_cnt2;
    mt2.direction =  re[t].direction2;
    mt2.if_attack =  re[t].if_attack2;
    mt2.if_be_attacked = re[t].if_be_attacked2;
    mt2.if_stand =  re[t].if_stand2;
    mt2.if_walk =  re[t].if_walk2;
    mt2.if_run =  re[t].if_run2;
    mt2.if_resist = re[t].if_resist2;
    mt2.if_rush = re[t].if_rush2;
    mt2.if_ra = re[t].if_ra2;
    mt2.if_kj = re[t].if_kj2;
    if (re[t].if_die2 == 1 && re[t].die_cnt2 == mt2.die_all_cnt)
    {
        if_replay = 0;
        if_win = -1;
        return;
    }
}
