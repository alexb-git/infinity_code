/****************************************************************************
** Filename:    - shape.cpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementation of shape API
** Date:        - 18/1/2018
** Version:     - 1
*****************************************************************************/
#include <cmath>        /* sin, cos */
#include <iostream>

#include "shape.h"      /* shape API */

namespace ilrd
{

/****************************************************************************
    Point class methods
*****************************************************************************/
Point::Point(int x, int y): m_x(x), m_y(y)
{}

void Point::SetPoint(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Point::MoveToDirection(int dx, int dy)
{
    m_x += dx;
    m_y += dy;
}

void Point::AxisRotate(int x, int y, int degrees)
{
    const double PI = 3.14159265;

    int x_p = m_x;
    double radians = (degrees / 180.0) * PI;

    m_x = round( x + (m_x - x) * std::cos(radians)
                   - (m_y - y) * std::sin(radians));

    m_y = round( y + (x_p - x) * std::sin(radians)
                   + (m_y - y) * std::cos(radians));
}

int Point::GetX() const
{
    return m_x;
}

int Point::GetY() const
{
    return m_y;
}

/****************************************************************************
    Shape class methods
*****************************************************************************/
Shape::Shape(int x, int y) : m_center(x, y) {}

Shape::~Shape() {}

void Shape::SetCenterPoint(int x, int y)
{
    m_center.SetPoint(x, y);
}

void Shape::MoveToDirection(int dx, int dy)
{
    m_center.MoveToDirection(dx, dy);
}

void Shape::AxisRotate(int x, int y, int degrees)
{
    m_center.AxisRotate(x, y, degrees);
}

int Shape::GetCntrX() const
{
    return m_center.GetX();
}

int Shape::GetCntrY() const
{
    return m_center.GetY();
}

/*===============  PURE VIRTUAL  ===============*/
void Shape::Draw() const {}
void Shape::Revolve(int x, int y, int degrees) {}



/****************************************************************************
    SingleShape class methods
*****************************************************************************/
SingleShape::SingleShape( int x, int y,
                          COLORS color,
                          int gradient) :
                                        Shape(x, y),
                                        m_color(color),
                                        m_gradient(gradient)
{}

SingleShape::~SingleShape() {}

void SingleShape::Rotate(int degrees)
{
    m_gradient += degrees;
    m_gradient %= 360;
}

void SingleShape::Revolve(int x, int y, int degrees)
{
    /* update the gradient of the shape */
    Rotate(degrees);

    /* update x and y coordinates according to the movement */
    m_center.AxisRotate(x, y, degrees);
}

void SingleShape::SetColor(COLORS color)
{
    m_color = color;
}

void SingleShape::SetGrad(int degrees)
{
    m_gradient = degrees;
}

COLORS SingleShape::GetColor() const
{
    return m_color;
}

int SingleShape::GetGrad() const
{
    return m_gradient;
}


/****************************************************************************
    Circle class methods
*****************************************************************************/
Circle::Circle( int center_x, int center_y,
                size_t radius,
                COLORS color) :
                                SingleShape(center_x, center_y, color),
                                m_radius(radius)
{}

Circle::~Circle() {}

void Circle::Draw() const
{
    DrawCircle( m_color,
                m_center.GetX(),
                m_center.GetY(),
                m_radius);
}

size_t Circle::GetRadius() const
{
    return m_radius;
}

void Circle::SetRadius(size_t radius)
{
    m_radius = radius;
}

/****************************************************************************
    Point class methods
*****************************************************************************/
Rectangle::Rectangle( int x1, int y1,
                      int x2, int y2,
                      COLORS color,
                      int gradient):

                            SingleShape( (x1 + x2) / 2  ,
                                         (y1 + y2) / 2  ,
                                         color, gradient)   ,
                            m_height( std::abs(y2 - y1) / 2),
                            m_width(  std::abs(x2 - x1) / 2)
{}

Rectangle::~Rectangle() {}

void Rectangle::Draw() const
{
    int cntr_x = m_center.GetX();
    int cntr_y = m_center.GetY();

    Point p1(cntr_x - m_width, cntr_y - m_height);
    p1.AxisRotate(cntr_x, cntr_y, m_gradient);

    Point p2(cntr_x + m_width, cntr_y - m_height);
    p2.AxisRotate(cntr_x, cntr_y, m_gradient);

    Point p3(cntr_x + m_width, cntr_y + m_height);
    p3.AxisRotate(cntr_x, cntr_y, m_gradient);

    Point p4(cntr_x - m_width, cntr_y + m_height);
    p4.AxisRotate(cntr_x, cntr_y, m_gradient);


    DrawPolygon(m_color, 4,
                p1.GetX() /*x1*/, p1.GetY() /*y1*/,
                p2.GetX() /*x2*/, p2.GetY() /*y2*/,
                p3.GetX() /*x3*/, p3.GetY() /*y3*/,
                p4.GetX() /*x4*/, p4.GetY() /*y4*/ );
}

void Rectangle::SetHeight(size_t height)
{
    m_height = round(0.5 * height);
}

void Rectangle::SetWidth(size_t width)
{
    m_width = round(0.5 * width);
}

size_t Rectangle::GetHeight() const
{
    return (2 * m_height);
}

size_t Rectangle::GetWidth() const
{
    return (2 * m_width);
}


/****************************************************************************
    Triangle class methods
*****************************************************************************/
Triangle::Triangle( int x1, int y1,         /* x1, y1 - coordinate */
                    int x2, int y2,         /* x2, y2 - coordinate */
                    int x3, int y3,         /* x3, y3 - coordinate */
                    COLORS color,
                    int gradient):
                            SingleShape(round((x1+x2+x3)/3),
                                        round((y1+y2+y3)/3),
                                        color, gradient),

                            m_p1(x1 - m_center.GetX(),y1 - m_center.GetY()),
                            m_p2(x2 - m_center.GetX(),y2 - m_center.GetY()),
                            m_p3(x3 - m_center.GetX(),y3 - m_center.GetY())
{}


Triangle::~Triangle() {}

void Triangle::Draw() const
{
    int cntr_x = m_center.GetX();
    int cntr_y = m_center.GetY();


    Point temp1(cntr_x + m_p1.GetX(), cntr_y + m_p1.GetY());
    Point temp2(cntr_x + m_p2.GetX(), cntr_y + m_p2.GetY());
    Point temp3(cntr_x + m_p3.GetX(), cntr_y + m_p3.GetY());


    temp1.AxisRotate(cntr_x, cntr_y, m_gradient);
    temp2.AxisRotate(cntr_x, cntr_y, m_gradient);
    temp3.AxisRotate(cntr_x, cntr_y, m_gradient);


    DrawPolygon(m_color, 3,
                temp1.GetX() /*x1*/, temp1.GetY() /*y1*/,
                temp2.GetX() /*x2*/, temp2.GetY() /*y2*/,
                temp3.GetX() /*x3*/, temp3.GetY() /*y3*/);
}

//ver_num - the spicific vertex to set - between [0 , 2]
void Triangle::SetVertices(int x, int y, int ver_num)
{}

/****************************************************************************
    Group class methods
*****************************************************************************/
Group::Group(Shape *shape) :
                            Shape( shape->GetCntrX() ,
                                   shape->GetCntrY() )
{
    m_vector.push_back(shape);
}

Group::~Group() {}

void Group::Draw() const
{
    std::vector<Shape*>::const_iterator itr = m_vector.begin();

    for ( ; itr != m_vector.end() ; ++itr )
    {
        (*itr)->Draw();
    }
}

void Group::Rotate(int degrees)
{
    /* each object revolves around center of mass of group with degree  */
    Revolve(m_center.GetX(), m_center.GetY(), degrees);
}

void Group::MoveToDirection(int dx, int dy)
{
    std::vector<Shape*>::iterator itr = m_vector.begin();

    for ( ; itr != m_vector.end() ; ++itr )
    {
        (*itr)->MoveToDirection(dx, dy);
    }
}

void Group::SetCenterPoint(int center_x, int center_y)
{
    int dx = center_x - m_center.GetX();
    int dy = center_y - m_center.GetY();

    std::vector<Shape*>::iterator itr = m_vector.begin();

    for ( ; itr != m_vector.end() ; ++itr )
    {
        (*itr)->MoveToDirection(dx, dy);
    }

    SetCenterPoint(center_x, center_y);
}

void Group::Revolve(int x, int y, int degrees)
{
    std::vector<Shape*>::iterator itr = m_vector.begin();

    for ( ; itr != m_vector.end() ; ++itr )
    {
        /* each object revolves around x, y with degree */
        (*itr)->Revolve(x, y, degrees);
    }
}

void Group::AxisRotate(int x, int y, int degrees)
{
    std::vector<Shape*>::iterator itr = m_vector.begin();

    for ( ; itr != m_vector.end() ; ++itr )
    {
        /* each object AxisRotate around x, y with degree */
        (*itr)->AxisRotate(x, y, degrees);
    }
}


void Group::Add(Shape *shape)
{
    int nmemb = m_vector.size();

    int x = round((nmemb * m_center.GetX() + 1.0 * shape->GetCntrX())
          / (nmemb + 1) * 1.0);

    int y = round((nmemb * m_center.GetY() + 1.0 * shape->GetCntrY())
          / (nmemb + 1) * 1.0);

    m_center.SetPoint(x, y);

    m_vector.push_back(shape);
}


} // namespace ilrd
