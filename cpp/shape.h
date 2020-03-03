
/***********************************************
  Filename: shape.hpp
  Purpose:  implementation of shape API
  Version:  2
***********************************************/
#ifndef __SHAPE_H_CPP__
#define __SHAPE_H_CPP__

#include <cstddef>          /* size_t */
#include <vector>           /* vector */

#include "glut_utils.h"     /* glib draw api */

namespace ilrd
{

/****************************************************************************/
class Point
{
public:
    Point(int x, int y);                         // ctor

    void SetPoint(int x, int y);                 // x & y are new coordinates
    void MoveToDirection(int dx, int dy);        // move to direction
    void AxisRotate(int x, int y, int degrees);  // (x,y) = pov

    /* getters */
    int GetX() const;
    int GetY() const;

private:
    int m_x;
    int m_y;
};

/****************************************************************************/
class Shape
{
public:
    Shape(int x, int y);    // ctor

    virtual ~Shape();      // dtor

    // move center of mass to new location
    virtual void SetCenterPoint(int center_x, int center_y);

    // move center of mass according to delta
    virtual void MoveToDirection(int dx, int dy);

    // pov - point of view, rotate around center of mass
    virtual void AxisRotate(int x, int y, int degrees);

    /*=============  PURE VIRTUAL  ============*/
    virtual void Draw() const = 0;
    virtual void Revolve(int center_x, int center_y, int degrees) = 0;

    /*========= Setters =========*/
    int GetCntrX() const;
    int GetCntrY() const;

protected:
    // to disable default cctor
    Shape(const Shape&);
    //to disable default assigment operator
    Shape& operator=(const Shape&);

    Point m_center;
};

/****************************************************************************/
class SingleShape : public Shape
{
public:
    SingleShape( int x, int y,
                 COLORS color = COLOR_WHITE,
                 int gradient = 0);

    virtual ~SingleShape();

    // rotate around center of mass
    void Rotate(int degrees);

    // revolve around point x, y degrees
    void Revolve(int x, int y, int degrees);

    /*========= Getters =========*/
    void SetColor(COLORS color);
    void SetGrad(int degrees);

    /*========= Setters =========*/
    COLORS  GetColor() const;
    int     GetGrad()  const;

protected:
    COLORS m_color;
    int m_gradient;
};

/****************************************************************************/
class Circle : public SingleShape
{
public:
    Circle( int center_x, int center_y,
            size_t radius,
            COLORS color = COLOR_WHITE);

    ~Circle();

    void Draw() const;

    /*========= Setters =========*/
    void SetRadius(size_t radius);

    /*========= Getters =========*/
    size_t GetRadius() const;

private:
    size_t m_radius;
};

/****************************************************************************/
class Rectangle : public SingleShape
{
public:
    // (x1,y1), (x2,y2) are the diagonal points of the rectangle
    Rectangle( int x1, int y1, int x2, int y2,
               COLORS color = COLOR_WHITE, int gradient = 0);
    ~Rectangle();

    void Draw() const;

    /*========= Setters =========*/
    void SetHeight(size_t height);
    void SetWidth(size_t width);

    /*========= Getters =========*/
    size_t GetHeight() const;
    size_t GetWidth() const;

private:
    size_t m_height;
    size_t m_width;
};

/****************************************************************************/
class Triangle : public SingleShape
{
public:
    Triangle( int x1, int y1,         /* x1, y1 - coordinate */
              int x2, int y2,         /* x2, y2 - coordinate */
              int x3, int y3,         /* x3, y3 - coordinate */
              COLORS color = COLOR_WHITE,
              int gradient = 0           );
    ~Triangle();

    void Draw() const;

    /*  Setters:
        ver_num - the spicific vertex to set - between [0 , 2] */
    void SetVertices(int x, int y, int ver_num);

private:
    Point m_p1, m_p2, m_p3;
};

/****************************************************************************/

class Group : public Shape
{
public:
    explicit Group(Shape *shape);
    ~Group();

    /*======== Shape functions ========*/
    void Draw() const;
    void Rotate(int degrees);
    void MoveToDirection(int dx, int dy);
    void SetCenterPoint(int center_x, int center_y);
    void Revolve(int x, int y, int degrees);
    void AxisRotate(int x, int y, int degrees);

    void Add(Shape *shape); // add shape to the vector

private:
    // to disable default cctor
    Group(const Group& other_);
    //to disable default assigment operator
    Group& operator=(const Group& other_);

    std::vector<Shape*> m_vector;
};




} // namespace ilrd

#endif /* end of __SHAPE_H_CPP__ */
