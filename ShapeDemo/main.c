/*Just compile 
main.c:
gcc main.c  `
export LD_LIBRARY_PATH=.
*/

#include <stdio.h>
#include <stdlib.h>

#include "glut_utils.h"


int drawCircle = 1;
int xCircle = 250;
int yCircle = 300;

void DrawFunction()
{
    printf("Drawing\n");

    DrawPolygon(COLOR_PURPLE, 4, (int)150, (int)400, (int)150, (int)650, (int)300, (int)650, (int)300, (int)400);

    if (drawCircle)
        DrawCircle(COLOR_GREEN, xCircle, yCircle, 100);
}


int MouseFunction(int button, int state, int x, int y)
{
    printf("Mouse: %d,%d,%d,%d\n", button, state, x, y);

    if (button == MOUSE_LEFT)
    {
        drawCircle = state;
        return 1;
    }

    return 0;
}


int TimerFunction(int value)
{
    xCircle += 5;
    yCircle += 5;

    DrawSetTimerFunc(TimerFunction, 100);

    return 1;  /* draw */
}


int main(int argc, char** argv)
{
    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    /* advanced: extra functionality */
    DrawSetMouseFunc(MouseFunction);
    DrawSetTimerFunc(TimerFunction, 100);

    DrawMain();

    return 0;
}
