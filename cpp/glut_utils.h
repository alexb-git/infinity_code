
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


enum COLORS
{
    COLOR_BLUE   = 0x000001,
    COLOR_GREEN  = 0x000100,
    COLOR_CYAN   = 0x000101,
    COLOR_RED    = 0x010000,
    COLOR_PURPLE = 0x010001,
    COLOR_YELLOW = 0x010100,
    COLOR_WHITE  = 0x010101,
    COLOR_FILL   = 0x80000000
};

enum MOUSE_BUTTONS
{
    MOUSE_LEFT   = 0,
    MOUSE_MIDDLE = 1,
    MOUSE_RIGHT  = 2
};

typedef void (*DRAW_FUNC_T) ();
typedef int  (*MOUSE_FUNC_T)(int button, int state, int x, int y);
typedef int  (*TIMER_FUNC_T)(int value);
typedef int  (*MENU_FUNC_T) (int option);


/****************************************************************************
** description:  opens OpenGl window
** arguments:    argc - ?
**               argv - ?
**               draw_func_p - the function we will invoke when init
**               w - width of the window
**               h - hight of the window
** return value: none
** notes:
*****************************************************************************/
void DrawInit(int argc, char** argv, int w, int h, DRAW_FUNC_T draw_func_p);

/****************************************************************************
** description:  can create the illusion of movement
** arguments:    timer_func_p - some function that is called every msec
**               msecs        - the shape is refreshed every msecs [seconds]
** return value: none
** notes:
*****************************************************************************/
void DrawSetTimerFunc(TIMER_FUNC_T timer_func_p, int msecs);

/****************************************************************************
** description:  the function that runs the show
** arguments:    none
** return value: none
** notes:        THE FUNCTION THAT RUNS THE SHOW
*****************************************************************************/
void DrawMain();

/****************************************************************************
** description:  functions that allow us to draw the required shapes
** arguments:    color - outer shape color
**               points/radius - relative to the shape
** return value: none
*****************************************************************************/
void DrawCircle(int color, int x, int y, int radius);
void DrawPolygon(int color, int nPoints, ...);
/* ======  EXAMPLES OF USAGE (FUNCTION CALLS)  ======
void DrawRectangle(int x1, int y1, int x2, int y2, int color);
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
*/


/****************************************************************************
    YET TO BE DISCOVERED, DOESNT WORK
    probably enables user to add shapes with a mouse click
*****************************************************************************/
void DrawSetMenuFunc(MENU_FUNC_T menu_func_p);
void DrawSetMouseFunc(MOUSE_FUNC_T mouse_func_p);

#ifdef __cplusplus
}
#endif // __cplusplus
