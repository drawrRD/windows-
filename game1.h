#include "judge1.h"
#include "character.h"
#include "ui.h"

void init_game1();

void draw_game1(HDC hdc, HDC mdc, HDC bufdc);

void draw_map1(HDC hdc, HDC mdc, HDC bufdc);

void draw_person1(HDC hdc, HDC mdc, HDC bufdc);

void draw_monsters(HDC hdc, HDC mdc, HDC bufdc);

void draw_success1(HDC hdc, HDC mdc, HDC bufdc);

int get_start_map();
