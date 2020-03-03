/****************************************************************************
** Filename:    - observer.hpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - observer
** Date:        - 26/2/2018
** Version:     - 1
*****************************************************************************/

/****************************************************************************
** Filename:    - observer.hpp
** Purpose:     - observer header
** Date:        - 26/02/2018
** Version:     - 3
*****************************************************************************/
#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

#include <list>
#include <boost/noncopyable.hpp> // noncopyable

namespace ilrd
{

template <class Event>
class Dispatcher;

// *****************************************************************************
// *                         class CallBackInterface                           *
// *****************************************************************************
template <class Event>
class CallBackBase: private boost::noncopyable
{
public:

protected:
    // can only be called by CallBack (derived class)
    explicit CallBackBase(): m_dis(NULL) {}

    // Will unsubscribe itself from the dispatcher
    virtual ~CallBackBase();

private:
    // must be able to use CallBackBase's functions
    friend class Dispatcher<Event>;

    // can only be called by Dispatcher
    virtual void Notify(const Event& e) = 0;

    // can only be called by Dispatcher
    virtual void DisDead() = 0;

    // can only be called by Dispatcher
    void SetDispatcher(Dispatcher<Event> *dis);

    Dispatcher<Event> *m_dis; // pointer to Dispatcher
};

// *****************************************************************************
// *                               class CallBack                              *
// *****************************************************************************
template <class Event, class Observer>
class CallBack: public CallBackBase<Event>
{
public:
    explicit CallBack(Observer *obs,
                      void (Observer::*m_f_notify)(const Event& e),
                      void (Observer::*m_f_disdead)() = NULL);
    virtual ~CallBack();

private:
    // will be called from CallBackBase (base class)
    virtual void Notify(const Event& e);
    virtual void DisDead();

    // A pointer to user's class
    Observer *const m_obs;

    // A pointer to a method that sends user a  notification/event
    void (Observer::*m_f_notify)(const Event& e);

    // A pointer to a method that notifies the
    // user that Dispatcher no longer exists
    void (Observer::*m_f_disdead)();
};

// *****************************************************************************
// *                             class Dispatcher                              *
// *****************************************************************************
template <class Event>
class Dispatcher: private boost::noncopyable
{
public:
    ~Dispatcher(); // Will call NotifyAllOnDeath

    void NotifyAll(const Event& e) const;
    void Subscribe(CallBackBase<Event> *cb);

private:
    friend class CallBackBase<Event>;

    void NotifyAllOnDeath() const; // notify observers
    void UnSubscribe(CallBackBase<Event> *cb);

    std::list< CallBackBase<Event>* > m_call_backs;
};

} //namespace ilrd

#include "observer.inl" /* implementation */

#endif // __OBSERVER_HPP__
