#include "judge1.h"


void judge1()
{
    check_die1();
    judge_person_attack();
    judge_monsters_attack();
    monsters_chase();
}

void check_die1()
{
    if (person1.cur_hp <= 0)
    {
        person1.if_die = 1;
        if_win = -1;
    }
    int ck = 0;
    for (int i = 0; i < mt1_num; i++)
    {
        if (mt1[i].cur_hp <= 0)
            mt1[i].if_die = 1;
        if (mt1[i].cur_hp > 0)
            ck = 1;
    }
    if (ck == 0)
        if_win = 1;
}

void judge_person_attack()
{
    int px = person1.curx, py = person1.cury;
    int pl = px - person1.w, pr = px + person1.w;

    for (int i = 0; i < mt1_num; i++)
    {
        int mx = mt1[i].curx, my = mt1[i].cury;
        int ml = mx - mt1[i].w, mr = mx + mt1[i].w;
        if (person1.if_attack == 1 || person1.if_dj == 1 || person1.if_u == 1 || person1.if_i == 1 || person1.if_o == 1 || person1.if_p == 1)
        {
            if(pr >= ml && pl <= mr)
            {
                if (mt1[i].hp > 0)
                {
                    mt1[i].if_stand = 0;
                    mt1[i].if_walk = 0;
                    mt1[i].if_attack = 0;
                    mt1[i].if_be_attacked = 1;

                    if (person1.if_attack == 1)
                        mt1[i].cur_hp -= person1.attack_harm;
                    else if (person1.if_dj == 1)
                        mt1[i].cur_hp -= person1.dj_harm;
                   else if (person1.if_u == 1)
                        mt1[i].cur_hp -= person1.u_harm;
                    else if (person1.if_i == 1)
                        mt1[i].cur_hp -= person1.i_harm;
                    else if (person1.if_o == 1)
                        mt1[i].cur_hp -= person1.o_harm;
                    else if (person1.if_p == 1)
                        mt1[i].cur_hp -= person1.p_harm;
                }
            }
        }
    }
}


void judge_monsters_attack()
{
    int px = person1.curx, py = person1.cury;
    int pl = px - person1.w, pr = px + person1.w, ph = py + person1.h;

    for (int i = 0; i < mt1_num; i++)
    {
        int mx = mt1[i].curx, my = mt1[i].cury;
        int ml = mx - mt1[i].w, mr = mx + mt1[i].w, mh= my - mt1[i].h;
        if (mt1[i].if_attack == 1)
        {
            if(mr >= pl && ml <= pr && ph >= mh && mt1[i].attack_cnt >= 1)
            {
                if (person1.hp > 0)
                {
                    if (mt1[i].attack_cnt == 3)
                    {
                        clear_state();
                        person1.if_be_attacked = 1;
                    }
                    person1.cur_hp -= mt1[i].attack_harm;
                }
            }
        }
    }
}


void monsters_chase()
{
    int px = person1.curx, py = person1.cury;

    for (int i = 0; i < mt1_num; i++)
    {
        int mx = mt1[i].curx, my = mt1[i].cury;
        int attack_eye = mt1[i].w;
        if (mt1[i].if_die == 1)
        {
            continue;
        }
        if (mt1[i].if_attack == 1 || mt1[i].if_be_attacked == 1)
        {
            continue;
        }

        mt1[i].if_stand = 1;
        mt1[i].if_walk = 0;

        if (px < mx)
            mt1[i].direction = 0;
        else if (px >= mx)
            mt1[i].direction = 1;

        if (abs(mx - px) <= attack_eye)
        {
            mt1[i].if_stand = 0;
            mt1[i].if_attack = 1;
        }
        else if (abs(mx - px) <= mt1[i].eye)
        {
            mt1[i].if_stand = 0;
            mt1[i].if_walk = 1;
        }
    }

}
