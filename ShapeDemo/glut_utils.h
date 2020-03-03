
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


enum COLORS
{
    COLOR_RED    = 0x010000,
    COLOR_GREEN  = 0x000100,
    COLOR_BLUE   = 0x000001,
    COLOR_YELLOW = 0x010100,
    COLOR_PURPLE = 0x010001,
    COLOR_CYAN   = 0x000101,
    COLOR_WHITE  = 0x010101,
    COLOR_FILL   = 0x80000000
};

enum MOUSE_BUTTONS
{
    MOUSE_LEFT   = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT  = 2
};

typedef void (*DRAW_FUNC_T)();
typedef int (*MOUSE_FUNC_T)(int button, int state, int x, int y);
typedef int (*TIMER_FUNC_T)(int value);
typedef int (*MENU_FUNC_T)(int option);

void DrawInit(int argc, char** argv, int w, int h, DRAW_FUNC_T draw_func_p);
void DrawSetMouseFunc(MOUSE_FUNC_T mouse_func_p);
void DrawSetTimerFunc(TIMER_FUNC_T timer_func_p, int msecs);
void DrawSetMenuFunc(MENU_FUNC_T menu_func_p);
void DrawMain();

void DrawCircle(int color, int x, int y, int radius);
/*
void DrawRectangle(int x1, int y1, int x2, int y2, int color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
*/
void DrawPolygon(int color, int nPoints, ...);


#ifdef __cplusplus
}
#endif // __cplusplus
