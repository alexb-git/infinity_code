
/***************************************************************************
** Filename:    - factory.hpp
** Purpose:     - design pattern - factory
** Date:        - 25/2/2018
** Version:     - 2
*****************************************************************************/
#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <map>      /* map */
#include <iostream> /* cout */
#include <boost/noncopyable.hpp> // noncopyable
                                 // (sudo apt-get install libboost-dev)
namespace ilrd
{
/* ==================== Factory class Declaration =================== */

template<class Base,                    // Base class that define factory family
         class KeyType,                 // Type of key that will be used in map
         class Arg,                     // Type of argument for the Creator
         class Creator = Base*(*)(Arg)> // A function that is able to create the
                                        // required object
class Factory: private boost::noncopyable
{
public:
  void Add(KeyType key, Creator create);
  Base* Create(KeyType key, Arg arg) const;

private:
  std::map<KeyType, Creator> m_map;

}; // End of class factory


/* ==================== Factory class Implementation =================== */

/* ============================== Ctor ============================= */
template<class Base, class KeyType, class Arg, class Creator>
void Factory<Base, KeyType, Arg, Creator>::Add(KeyType key, Creator create)
{
    m_map[key] = create;
}

/* ============================== Ctor ============================= */
template<class Base, class KeyType, class Arg, class Creator>
Base* Factory<Base, KeyType, Arg, Creator>::Create(KeyType key, Arg arg) const
{
    return m_map.at(key)(arg);
}


} // End of namespace ilrd

#endif /* end of __FACTORY_H__ */
