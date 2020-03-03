/*Just compile
shape_test.c:
gcc shape_test.c  `
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
ilrd::Circle C_base1(500, 500, 100, COLOR_WHITE);
ilrd::Circle C_base2(500, 500, 200, COLOR_WHITE);
ilrd::Circle C_base3(500, 500, 300, COLOR_WHITE);
ilrd::Circle C_base4(500, 500, 400, COLOR_WHITE);


ilrd::Circle Circ1(500, 400, 50, COLOR_BLUE);
ilrd::Circle Circ2(500, 300, 50, COLOR_GREEN);
ilrd::Circle Circ3(500, 200, 50, COLOR_RED);

  /* relative point (400, 500, 400, 500) */
ilrd::Rectangle Rec1(356, 478, 444, 522, COLOR_BLUE);
ilrd::Rectangle Rec2(256, 478, 344, 522, COLOR_GREEN);
ilrd::Rectangle Rec3(156, 478, 244, 522, COLOR_RED);


ilrd::Triangle Tri1(/*p1*/450, 600, /*p2*/544, 578, /*p3*/544, 622, COLOR_BLUE);
ilrd::Triangle Tri2(/*p1*/450, 700, /*p2*/544, 678, /*p3*/544, 722, COLOR_GREEN);
ilrd::Triangle Tri3(/*p1*/450, 800, /*p2*/544, 778, /*p3*/544, 822, COLOR_RED);


/*==========================  Group #1  =========================*/
ilrd::Circle    CircGr1(600, 500, 50, COLOR_BLUE);
ilrd::Rectangle RecGr1 (556, 478, 644, 522, COLOR_RED);
ilrd::Triangle  TriGr1 (556, 500, 644, 478, 644, 522, COLOR_GREEN);

ilrd::Group Gr1(&CircGr1);

/*==========================  Group #2  =========================*/
ilrd::Circle    CircGr2(700, 500, 50, COLOR_BLUE);
ilrd::Rectangle RecGr2 (656, 478, 744, 522, COLOR_RED);
ilrd::Triangle  TriGr2 (656, 500, 744, 478, 744, 522, COLOR_GREEN);

ilrd::Group Gr2(&CircGr2);

/*==========================  Group #3  =========================*/
ilrd::Circle    CircGr3(800, 500, 50, COLOR_BLUE);
ilrd::Rectangle RecGr3 (756, 478, 844, 522, COLOR_RED);
ilrd::Triangle  TriGr3 (756, 500, 844, 478, 844, 522, COLOR_GREEN);

ilrd::Group Gr3(&CircGr3);

/*==========================  Group #4  =========================*/
ilrd::Circle    CircGr4(900, 500, 50, COLOR_BLUE);
ilrd::Rectangle RecGr4 (856, 478, 944, 522, COLOR_RED);
ilrd::Triangle  TriGr4 (856, 500, 944, 478, 944, 522, COLOR_GREEN);

ilrd::Group Gr4(&CircGr4);


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

    C_base1.Draw();
    C_base2.Draw();
    C_base3.Draw();
    C_base4.Draw();

    {
        Circ1.Draw();
        Circ1.Rotate(5);

        Circ2.Draw();
        Circ2.AxisRotate(500, 500, 5);

        Circ3.Draw();
        Circ3.Revolve(500, 500, 5);
    }

    {
        Rec1.Draw();
        Rec1.Rotate(5);

        Rec2.Draw();
        Rec2.AxisRotate(500, 500, 5);

        Rec3.Draw();
        Rec3.Revolve(500, 500, 5);
    }

    {
        Tri1.Draw();
        Tri1.Rotate(5);

        Tri2.Draw();
        Tri2.AxisRotate(500, 500, 5);

        Tri3.Draw();
        Tri3.Revolve(500, 500, 5);
    }



    {
        Gr1.Draw();
        Gr1.Rotate(5);

        Gr2.Draw();
        Gr2.AxisRotate(500, 500, 5);

        Gr3.Draw();
        Gr3.Revolve(500, 500, 5);

        Gr4.Draw();
        Gr4.MoveToDirection(-1, -5);
    }


    // if (drawCircle)
    // {
    //     DrawCircle(COLOR_GREEN, xCircle, yCircle, 70);
    // }
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
    Gr1.Add(&TriGr1);
    Gr1.Add(&RecGr1);

    Gr2.Add(&TriGr2);
    Gr2.Add(&RecGr2);

    Gr3.Add(&TriGr3);
    Gr3.Add(&RecGr3);

    Gr4.Add(&TriGr4);
    Gr4.Add(&RecGr4);

    DrawInit(argc, argv, 1000, 1000, DrawFunction);

    DrawSetMouseFunc(MouseFunction);

    DrawSetTimerFunc(TimerFunction, 5000);

    DrawMain();

    return 0;
}
