#include "home.h"
#include "maphome.h"
#include "game1.h"
#include "game2.h"
#include "character.h"
#include "replay.h"

//全局变量声明
HDC hdc, mdc, bufdc;
HWND	hWnd;
DWORD tPre, tNow;
const DWORD KEY_REPEAT_MIN = 100, KEY_REPEAT_MAX = 200;
DWORD lastKeyPressTime = 0;
int bgsound = 0;

//全局函数声明
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void MyPaint(HDC hdc);
void MySound();
bool AreKeysPressed(char key1, char key2) {
    return (GetAsyncKeyState(key1) & 0x8000) && (GetAsyncKeyState(key2) & 0x8000);
}
bool IsKeyPressedContinuously(char key) {
    DWORD currentTime = GetTickCount();
    if (GetAsyncKeyState(key) & 0x8000) {
        if ( ((currentTime - lastKeyPressTime) > KEY_REPEAT_MIN && (currentTime - lastKeyPressTime) < KEY_REPEAT_MAX)) {
            if (key == 'D')
            {
                person1.curx += 10;
                person1.if_run = 1;
            }
            else
            {
                person1.curx -= 10;
                person1.if_run = 1;
            }
            lastKeyPressTime = currentTime;
            return true;
        }
        if ( person1.if_run == 1) {
            person1.if_run = 1;
            lastKeyPressTime = currentTime;
            return true;
        }
        lastKeyPressTime = currentTime;
    }
    return false;
}


//WinMain函数，程序入口点函数
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	GetMessage(&msg,NULL,NULL,NULL);
	//游戏循环
    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		else
		{
			tNow = GetTickCount();
		    if (if_replay == 1)
            {
                if (tNow - tPre >= 80)
                {
                    replay(hdc);
                    MyPaint(hdc);
                    t++;
                }
                continue;
            }
            if ( (person1.if_die == 1 && person1.die_cnt < person1.die_all_cnt) || (mt2.if_die == 1 && mt2.die_cnt < mt2.die_all_cnt) )
            {
                if(tNow-tPre >= 400)
                {
                    if (flag == 2)
                        record();
                    MyPaint(hdc);
                }
                if(tNow-tPre >= 200)
                {
                    //MySound();
                }
            }
            else
            {
                if(tNow-tPre >= 80)
                {
                    if (flag == 2)
                        record();
                    MyPaint(hdc);
                }
                if(tNow-tPre >= 200)
                {
                    //MySound();
                }
            }
		}
    }
	return msg.wParam;
}

//设计一个窗口类
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//初始化函数
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hWnd = CreateWindow("canvas", "冒险岛" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	MoveWindow(hWnd,0,0,1024,640,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

    //全局初始化
    init_person_state();
    init_game1();
    init_game2();


	MyPaint(hdc);

	return TRUE;
}

//自定义绘图函数
void MyPaint(HDC hdc)
{
//    if (flag == 1 || flag == 2)
//    {
//        ShowCursor(FALSE);
//    }
//    else
//    {
//        ShowCursor(TRUE);
//    }

    if (flag == -1)
    {
        draw_home(hdc, mdc, bufdc);
    }
    if (flag == -2)
    {
        draw_maphome(hdc, mdc, bufdc, nowgame);
    }
    if (flag == 0)
    {
        if (nowgame == 1)
            draw_pause(hdc, mdc, bufdc, get_start_map());
        else if (nowgame == 2)
            draw_pause(hdc, mdc, bufdc, get_start_map2());
    }
    if (flag == 1)
    {
        nowgame = 1;
        draw_game1(hdc, mdc, bufdc);
    }
    if (flag == 2)
    {
        nowgame = 2;
        draw_game2(hdc, mdc, bufdc);
    }


	tPre = GetTickCount();
}


//****消息处理函数***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int lx = LOWORD(lParam);
    static int ly = HIWORD(lParam);
	switch (message)
	{
        case WM_KEYUP:
        {
            if (flag == -1 || flag == -2 || flag == 0 || if_replay == 1)
                break;
            if (person1.if_jump == 1 || person1.if_u == 1 || person1.if_i == 1 || person1.if_o == 1 || person1.if_p == 1 || person1.if_be_attacked == 1 || person1.if_die == 1)
            {
                break;
            }
            clear_state();
            person1.if_stand = 1;
            break;
        }
		case WM_KEYDOWN:
        {
            if (if_replay == 1)
            {
                if (wParam == VK_ESCAPE)
                {
                    if_replay = 0;
                    flag = -2;
                }
                break;
            }

            if (wParam == VK_RETURN && flag == -1)
            {
                flag = -2;
                break;
            }
            else if (flag == -1)
            {
                if (wParam == VK_ESCAPE)
                    PostQuitMessage(0);
                break;
            }

            if (wParam == VK_RETURN && flag == -2)
            {
                init_game2();
                flag = 2;
                nowgame = 2;
                StartTime = GetTickCount();
                t = 0;
                break;
            }
            else if (flag == -2)
            {
                if (wParam == VK_ESCAPE)
                    flag = -1;
                break;
            }

            if (wParam == VK_ESCAPE)
            {
                if (flag == 0)
                {
                    if (nowgame == 1)
                        flag = 1;
                    if (nowgame == 2)
                        flag = 2;
                }
                else
                {
                    flag = 0;
                }
                break;
            }

            if (if_win == 1)
            {
                if (person1.curx >= 1800 && person1.curx <= 1890 && wParam == 'W')
                    flag = -2;
            }

            if (person1.if_jump == 1 || person1.if_u == 1 || person1.if_i == 1 || person1.if_o == 1 || person1.if_p == 1 || person1.if_be_attacked == 1 || person1.if_die == 1)
            {
                if (person1.if_be_attacked == 1 && wParam == 'O')
                {
                    clear_state();
                    person1.if_be_attacked = 0;
                    person1.if_o = 1;
                }
                if (person1.if_be_attacked == 1 && wParam == 'I')
                {
                    clear_state();
                    person1.if_be_attacked = 0;
                    person1.if_i = 1;
                }
                break;
            }
            if ( IsKeyPressedContinuously('D') )
            {
                clear_state();
                person1.if_run = 1;
                person1.direction = 1;
            }
            else if (wParam == 'D')
            {
                clear_state();
                person1.if_walk = 1;
                person1.direction = 1;
            }
            if ( IsKeyPressedContinuously('A') )
            {
                clear_state();
                person1.if_run= 1;
                person1.direction = 0;
            }
            else if (wParam == 'A')
            {
                clear_state();
                person1.if_walk = 1;
                person1.direction = 0;
            }
            if (wParam == 'K')
            {
                clear_state();
                person1.if_jump = 1;
            }
            if (wParam == 'J')
            {
                clear_state();
                person1.if_attack = 1;
            }
            if (wParam == 'U' && person1.cur_mp >= 50)
            {
                person1.cur_mp -= 50;
                clear_state();
                person1.if_u = 1;
            }
            if (wParam == 'I' && person1.cur_mp >= 70)
            {
                person1.cur_mp -= 70;
                clear_state();
                person1.if_i = 1;
            }
            if (wParam == 'O' && person1.cur_mp >= 50)
            {
                person1.cur_mp -= 50;
                clear_state();
                person1.if_o = 1;
            }
            if (wParam == 'P' && person1.cur_mp >= 40)
            {
                person1.cur_mp -= 40;
                clear_state();
                person1.if_p = 1;
            }
            if ( AreKeysPressed('D', 'J') )
            {
                clear_state();
                person1.if_dj = 1;
            }
            break;
        }
        case WM_MOUSEMOVE:
        {
            lx = LOWORD(lParam);
            ly = HIWORD(lParam);
            if (flag == -2)
            {
                if (lx <= 270 && ly <= 240)
                    nowgame = 1;
                else if (lx <= 270 && ly <= 550)
                    nowgame = 2;
                else
                    nowgame = -1;
            }
            break;
        }
        case WM_LBUTTONDOWN:
        {
            if (if_replay == 1)
                break;

            if (flag == 0)
            {
                if (lx >= 298 && lx <= 410 && ly >= 218 && ly <= 338)
                {
                    if (nowgame == 1)
                        flag = 1;
                    else if (nowgame == 2)
                        flag = 2;
                }
                else if (lx >= 474 && lx <= 581 && ly >= 218 && ly <= 338)
                {
                    if (nowgame == 1)
                    {
                        init_game1();
                        if_win = 0;
                        flag = 1;
                        t = 0;
                        StartTime = GetTickCount();
                    }
                    else if (nowgame == 2)
                    {
                        init_game2();
                        if_win = 0;
                        flag = 2;
                        StartTime = GetTickCount();
                        t = 0;
                    }
                }
                else if (lx >= 646 && lx <= 752 && ly >= 218 && ly <= 338)
                {
                    flag = -2;
                    nowgame = -1;
                }
            }
            if (flag == -1)
            {
                if (lx >= 370 && lx <= 370 + 250 && ly >= 470 && ly <= 470 + 60)
                {
                    flag = -2;
                }
            }
            if (flag == -2)
            {
                if (nowgame == 1)
                {
                    if_win = 0;
                    init_game1();
                    StartTime = GetTickCount();
                    t = 0;
                    flag = 1;
                }
                else if (nowgame == 2)
                {
                    if_win = 0;
                    init_game2();
                    StartTime = GetTickCount();
                    t = 0;
                    flag = 2;
                }
            }
            if (flag == 2)
            {
                if (if_win == -1)
                {
                    if (lx >= 244 && lx <= 468 && ly >= 390 && ly <= 440)
                    {
                        flag = -2;
                    }
                    else if (lx >= 588 && lx <= 767 && ly >= 390 && ly <= 440)
                    {
                        init_game2();
                        if_win = 0;
                        t = 1;
                        if_replay = 1;
                    }
                }
            }
            break;
        }
        case WM_RBUTTONDOWN:
        {
            break;
        }
        case WM_LBUTTONUP:
        {
            break;
        }
        case WM_DESTROY:
        {
            DeleteDC(mdc);
            DeleteDC(bufdc);
            ReleaseDC(hWnd,hdc);
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

