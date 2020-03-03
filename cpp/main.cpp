/*Just compile
main.c:
gcc main.c  `
export LD_LIBRARY_PATH=.
*/
#include <stdio.h>
#include <stdlib.h>

// #include "glut_utils.h"  /* glib draw api */
#include "shape.h"       /* my shapes API */


/*==========================  Global var  ==========================*/
int drawCircle = 1;
int xCircle = 0;
int yCircle = 0;

                /* (x , y , radius, color' , gradient') */
ilrd::Circle Circ1(25, 100, 25, COLOR_GREEN);
ilrd::Circle Circ2(550, 350, 15, COLOR_BLUE);

ilrd::Circle Circ3(1000, 1, 1, COLOR_BLUE);

ilrd::Rectangle Rec1(600, 100, 660, 130, COLOR_RED);
ilrd::Rectangle Rec2(300, 560, 400, 600, COLOR_YELLOW);
ilrd::Rectangle Rec3(950, 950, 1000, 1000, COLOR_YELLOW);

ilrd::Triangle Tri1(825, 900, 850, 950, 800, 950, COLOR_YELLOW);
ilrd::Triangle Tri2(340, 140, 340, 160, 360, 150, COLOR_GREEN);


/****************************************************************************/
void DrawFunction()
{
    // printf("Drawing F U\n");

    DrawPolygon(COLOR_PURPLE, 5,
            (int)150,  /* x1 */ (int)50,   /* y1 */
            (int)200,  /* x2 */ (int)100,  /* y2 */
            (int)200,  /* x3 */ (int)200,  /* y3 */
            (int)100,  /* x4 */ (int)200,  /* y4 */
            (int)100,  /* x5 */ (int)100   /* y5 */);

    Circ1.Draw();
    Circ1.MoveToDirection(1,2);

    Circ2.Draw();
    Circ2.Revolve(350, 350, 5);

    Rec1.Draw();
    Rec1.Rotate(2);

    Rec2.Draw();
    Rec2.Revolve(350, 350, 5);

    Circ3.Draw();
    Circ3.SetRadius(Circ3.GetRadius() + 1);
    Circ3.SetGrad(60);
    Circ3.SetColor(COLOR_CYAN);
    Circ3.SetCenterPoint(350, 350);

    Rec3.Draw();
    Rec3.SetGrad(Rec3.GetGrad() + 1);
    Rec3.SetWidth( Rec3.GetWidth() + 1);
    Rec3.SetHeight(Rec3.GetHeight() + 1);
    Rec3.MoveToDirection(-1, -1);

    Tri1.Draw();
    Tri1.Rotate(2);

    Tri2.Draw();
    Tri2.Revolve(350, 350, 5);



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
    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    DrawSetMouseFunc(MouseFunction);

    DrawSetTimerFunc(TimerFunction, 2000);

    DrawMain();

    return 0;
}
