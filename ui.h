#include <windows.h>
#include <math.h>
#include <stdio.h>
#include "character.h"


#ifndef UI_H
#define UI_H


extern void draw_ui(HDC hdc, HDC mdc, HDC bufdc, int start_map);

extern void draw_skill(HDC hdc, HDC mdc, HDC bufdc, int start_map);

extern void draw_p_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map);

extern void draw_boss_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map);

extern void draw_mt1_hp(HDC hdc, HDC mdc, HDC bufdc, int start_map);

extern double cal_hp(int who, int i);

extern double cal_mp();




#endif
