#include <windows.h>
#include <math.h>
#include <time.h>
#include "character.h"
#include "ui.h"

#ifndef REPLAY_H
#define REPLAY_H

extern bool if_replay;

extern DWORD StartTime;
extern DWORD EndTime;

struct Replay_parameter
{
    int cur_hp;
    int cur_mp;
    int direction;
    bool if_die;
    int die_cnt;
    bool if_be_attacked;
    bool if_stand;
    bool if_walk;
    bool if_run;
    bool if_jump;
    bool if_attack;
    bool if_dj;
    bool if_u;
    bool if_i;
    bool if_o;
    bool if_p;


    int cur_hp2;
    int direction2;
    bool if_die2;
    int die_cnt2;
    bool if_attack2;
    bool if_be_attacked2;
    bool if_stand2;
    bool if_walk2;
    bool if_run2;
    bool if_resist2;
    bool if_rush2;
    bool if_ra2;
    bool if_kj2;
};
extern struct Replay_parameter re[6005];
extern int t;


extern void replay(HDC hdc);
extern void record();





#endif
