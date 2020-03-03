/***************************************************************************
** Filename:    - serializer.hpp
** Purpose:     - design pattern - factory (serializer)
** Date:        - 26/2/2018
** Version:     - 1
*****************************************************************************/
#ifndef __SERIALIZE_H__
#define __SERIALIZE_H__

#include <iostream>
#include <boost/noncopyable.hpp> // noncopyable
                                 // (sudo apt-get install libboost-dev)
#include <typeinfo>
#include "factory.hpp"

namespace ilrd
{

/* ==================== Serialize class Declaration =================== */
template <class B>
class Serializer: private boost::noncopyable
{

public:
    void Serialize(const B& t_, std::ostream& os_) const;
    B* Deserialize(std::istream& is_) const;

    template <class D>
    void Add();

private:
    Factory<B, std::string, std::istream&> m_factory;

    template <class D>
    static B* Create(std::istream& is_);

}; // End of class Serialize


/* ==================== Factory class Implementation =================== */

template <class B>
B* Serializer<B>::Deserialize(std::istream& is_) const
{
    /*  get name of class from the stream and call
        default ctor of that class */
        std::string class_key;
        is_ >> class_key;
        return (m_factory.Create(class_key, is_));
}

template <class B>
void Serializer<B>::Serialize(const B& t_, std::ostream& os_) const
{
    /* put name of B into the ostream */
    os_ << typeid(t_).name() << ' ' << t_;
}

template <class B>
template <class D>
void Serializer<B>::Add()
{
    /* load all the bossible classes here */
    m_factory.Add(typeid(D).name(), Create<D>);
}

template <class B>
template <class D>
B* Serializer<B>::Create(std::istream& is_)
{
    B* temp = new D;
    is_ >> *temp;
    return (temp);
}


} // End of namespace ilrd

#endif /* end of __SERIALIZE_H__ */
