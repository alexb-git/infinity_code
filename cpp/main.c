/*Just compile
main.c:
gcc main.c  `
export LD_LIBRARY_PATH=.
*/
#include <stdio.h>
#include <stdlib.h>

#include "glut_utils.h"

#include "shape.h"    /* my shapes API */


/*==========================  Global var  ==========================*/
int drawCircle = 1;
int xCircle = 0;
int yCircle = 0;

ilrd::Circle Circ1(COLOR_GREEN, 25, 100, 25);
ilrd::Circle Circ2(COLOR_BLUE, 550, 350, 15);

ilrd::Rectangle Rec(COLOR_RED, 600, 100, 660, 130);


/****************************************************************************/
void DrawFunction()
{
    // printf("Drawing F U\n");

    DrawPolygon(COLOR_PURPLE, 5,
                (int)150,  /* x1 - coordinate */
                (int)50,   /* y1 - coordinate */

                (int)200,  /* x2 - coordinate */
                (int)100,  /* y2 - coordinate */

                (int)200,  /* x3 - coordinate */
                (int)200,  /* y3 - coordinate */

                (int)100,  /* x4 - coordinate */
                (int)200,  /* y4 - coordinate */

                (int)100,  /* x5 - coordinate */
                (int)100   /* y5 - coordinate */    );

    Circ1.Draw();
    Circ1.Move(1,2);

    Circ2.Draw();
    Circ2.Rotate(350, 350, 10);

    Rec.Draw();

    if (drawCircle)
    {
        DrawCircle(COLOR_GREEN, xCircle, yCircle, 70);
    }

    DrawCircle(COLOR_CYAN, 350, 350, 200);

}

/****************************************************************************/
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

/****************************************************************************/
int TimerFunction(int value)
{
    xCircle += 1;
    yCircle += 1;

    DrawSetTimerFunc(TimerFunction, 100);

    return 1;  /* draw */
}

/****************************************************************************/
int main(int argc, char** argv)
{
    DrawInit(argc, argv, 700, 700, DrawFunction);

    DrawSetMouseFunc(MouseFunction);

    DrawSetTimerFunc(TimerFunction, 3000);

    DrawMain();

    return 0;
}
