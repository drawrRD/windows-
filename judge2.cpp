#include "judge2.h"


void judge2()
{
    check_die2();
    monsters_chase2();
    judge_person_attack2();
    judge_monsters_attack2();
}

void check_die2()
{
    if (person1.cur_hp <= 0)
    {
        clear_state();
        person1.if_u = 0;
        person1.if_i = 0;
        person1.if_o = 0;
        person1.if_p = 0;
        person1.if_attack = 0;
        person1.if_be_attacked = 0;
        person1.if_die = 1;
        if_win = -1;
    }
    if (mt2.cur_hp <= 0)
    {
        mt2.if_stand = 0;
        mt2.if_walk = 0;
        mt2.if_run = 0;
        mt2.if_attack = 0;
        mt2.if_resist = 0;
        mt2.if_rush = 0;
        mt2.if_ra = 0;
        mt2.if_kj = 0;
        mt2.if_die = 1;
        if_win = 1;
    }
}


void judge_person_attack2()
{
    int px = person1.curx, py = person1.cury;
    int pl = px - person1.w, pr = px + person1.w;
    int mx = mt2.curx, my = mt2.cury;
    int ml = mx - mt2.w, mr = mx + mt2.w;
    if (person1.if_attack == 1 || person1.if_dj == 1 || person1.if_u == 1 || person1.if_i == 1 || person1.if_o == 1 || person1.if_p == 1)
    {
        if(pr >= ml && pl <= mr)
        {
            if (mt2.cur_hp > 0)
            {

                if (mt2.if_resist == 1)
                {
                    if (mt2.resist_cnt >= 1)
                    {
                        mt2.cur_hp += mt2.recover;
                        if (mt2.cur_hp >= mt2.hp)
                            mt2.cur_hp = mt2.hp;
                    }
                    return;
                }
                if (mt2.if_rush == 1 && mt2.rush_cnt >= 2 && mt2.rush_cnt <= 4)
                {
                    mt2.cur_hp -= 5;
                    return;
                }

                if (person1.if_attack == 1 && person1.attack_cnt  >= 2)
                {
                    mt2.if_attack = 0;
                    mt2.if_stand = 0;
                    mt2.if_walk = 0;
                    mt2.if_run = 0;
                    mt2.if_be_attacked = 1;
                }
                else if (person1.if_attack == 0)
                {
                    mt2.if_attack = 0;
                    mt2.if_stand = 0;
                    mt2.if_walk = 0;
                    mt2.if_run = 0;
                    mt2.if_be_attacked = 1;
                }

                if (person1.if_attack == 1)
                    mt2.cur_hp -= person1.attack_harm;
                else if (person1.if_dj == 1)
                    mt2.cur_hp -= person1.dj_harm;
               else if (person1.if_u == 1)
                    mt2.cur_hp -= person1.u_harm;
                else if (person1.if_i == 1)
                {
                    if (person1.cur_hp <= person1.hp)
                    {
                        person1.cur_hp += 20;
                        if (person1.cur_hp >= person1.hp)
                            person1.cur_hp = person1.hp;
                    }
                    mt2.cur_hp -= person1.i_harm;
                }
                else if (person1.if_o == 1)
                    mt2.cur_hp -= person1.o_harm;
                else if (person1.if_p == 1)
                    mt2.cur_hp -= person1.p_harm;
            }
        }
    }

}


void judge_monsters_attack2()
{
    int px = person1.curx, py = person1.cury;
    int pl = px - person1.w, pr = px + person1.w, ph = py + person1.h;

    int mx = mt2.curx, my = mt2.cury;
    int ml = mx - mt2.w, mr = mx + mt2.w, mh= my - mt2.h;

    if (mt2.if_attack == 1 || mt2.if_rush == 1 || (mt2.if_kj == 1 && mt2.kj_cnt >= 1 && mt2.kj_cnt <= 4) )
    {
        if(mr >= pl && ml <= pr && ph >= mh)
        {
            if (person1.cur_hp > 0)
            {
                if (person1.if_o == 1 || person1.if_p == 1)
                    return;

                if (mt2.if_attack == 1 && mt2.attack_cnt >= 3)
                {
                    clear_state();
                    person1.if_u = 0;
                    person1.if_i = 0;
                    person1.if_attack = 0;
                    person1.if_be_attacked = 1;
                }
                else if (mt2.if_attack == 0)
                {
                    clear_state();
                    person1.if_u = 0;
                    person1.if_i = 0;
                    person1.if_attack = 0;
                    person1.if_be_attacked = 1;
                }

                if (mt2.if_attack == 1)
                    person1.cur_hp -= mt2.attack_harm;
                else if(mt2.if_rush == 1)
                    person1.cur_hp -= mt2.rush_all_cnt;
                else if(mt2.if_kj == 1)
                    person1.cur_hp -= mt2.kj_harm;
            }
        }
    }

    int rx = mt2.ra_curx, ry = mt2.ra_cury;
    int rl = rx - mt2.ra_w, rr = rx + mt2.ra_w, rh= ry - mt2.ra_h;
    if (mt2.if_ra == 1 && mt2.ra_cnt >= 1)
    {
        if(rr >= pl && rl <= pr && person1.if_jump == 0)
        {
            if (person1.if_o == 1 || person1.if_p == 1)
                    return;
            if (person1.cur_hp > 0)
            {
                clear_state();
                person1.if_u = 0;
                person1.if_i = 0;
                person1.if_attack = 0;
                person1.if_be_attacked = 1;
                person1.cur_hp -= mt2.ra_harm;
            }
        }
    }

}


void monsters_chase2()
{
    int px = person1.curx, py = person1.cury;
    int mx = mt2.curx, my = mt2.cury;
    int attack_eye = mt2.w;

    if (person1.if_die == 1)
    {
        mt2.if_stand = 1;
        mt2.if_walk = 0;
        mt2.if_run = 0;
        mt2.if_attack = 0;
        mt2.if_resist = 0;
        mt2.if_rush = 0;
        mt2.if_ra = 0;
        return;
    }

    if (mt2.if_die == 1)
    {
        return;
    }
    if (mt2.if_attack == 1 || mt2.if_be_attacked == 1 || mt2.if_resist == 1 || mt2.if_rush == 1 || mt2.if_kj == 1)
    {
        if (mt2.if_be_attacked == 1)
        {
            srand(time(NULL));
            int tmp = rand() % 5;
            if (tmp == 1)
            {
                mt2.if_be_attacked = 0;
                mt2.if_resist = 1;
            }
        }
        return;
    }
    if (mt2.if_ra == 1 && mt2.ra_cnt == 0)
        return;

    mt2.if_stand = 1;
    mt2.if_walk = 0;
    mt2.if_run = 0;

    if (px < mx)
        mt2.direction = 0;
    else if (px >= mx)
        mt2.direction = 1;

    srand(time(NULL));
    int tmp = rand() % 10;

    if (abs(mx - px) <= mt2.rush_all_cnt * mt2.rush_dis)
    {
        if (tmp == 1)
        {
            mt2.if_stand = 0;
            mt2.if_rush = 1;
            return;
        }
    }

    if (mt2.if_ra == 0 && abs(mx - px) <= (mt2.ra_all_cnt - 1) * mt2.ra_dis)
    {
        if (tmp == 2)
        {
            mt2.if_stand = 0;
            mt2.if_ra = 1;
            return;
        }
    }

    if (abs(mx - px) <= (mt2.kj_all_cnt - 1) * mt2.kj_dis)
    {
        if (tmp == 3)
        {
            mt2.if_stand = 0;
            mt2.if_kj = 1;
            return;
        }
    }

    if (abs(mx - px) <= attack_eye)
    {
        mt2.if_stand =0;
        mt2.if_attack = 1;
    }
    else if (abs(mx - px) <= mt2.eye)
    {
        mt2.if_stand = 0;
        mt2.if_run = 1;
    }
    else if (abs(mx - px) <= mt2.eye * 2)
    {
        mt2.if_stand = 0;
        mt2.if_walk = 1;
    }

}
