#include "judge2.h"
#include "character.h"
#include "ui.h"
#include "replay.h"

void init_game2();

void draw_game2(HDC hdc, HDC mdc, HDC bufdc);

void draw_map2(HDC hdc, HDC mdc, HDC bufdc);

void draw_person2(HDC hdc, HDC mdc, HDC bufdc);

void draw_monsters2(HDC hdc, HDC mdc, HDC bufdc);

void draw_success2(HDC hdc, HDC mdc, HDC bufdc, int start_map);

int get_start_map2();
