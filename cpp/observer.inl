/****************************************************************************
** Filename:    - observer.inl
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - design pattern - observer implementation
** Date:        - 26/2/2018
** Version:     - 1
*****************************************************************************/
#include <algorithm>    // std::find

namespace ilrd
{


// *****************************************************************************
// *                         class CallBackInterface                           *
// *****************************************************************************

// Will unsubscribe itself from the dispatcher
template <class Event>
inline CallBackBase<Event>::~CallBackBase()
{
    /* panic programing. don't try to Unsubscribe a NULL pointer */
    if ( m_dis != NULL )
    {
        /* 'UnSubscribe' is dispatchers' function */
        m_dis->UnSubscribe(this);
        m_dis = NULL;
    }
}

// can only be called by Dispatcher
template <class Event>
inline void CallBackBase<Event>::SetDispatcher(Dispatcher<Event> *dis)
{
    /* 'connect' to dispatcher */
    m_dis = dis;
}


// *****************************************************************************
// *                               class CallBack                              *
// *****************************************************************************
template <class Event, class Observer>
inline CallBack<Event, Observer>::
     CallBack( Observer *obs,
               void (Observer::*f_notify)(const Event& e),
               void (Observer::*f_disdead)()) :
                                                m_obs(obs),
                                                m_f_notify(f_notify),
                                                m_f_disdead(f_disdead)
{
    // empty
}

template <class Event, class Observer>
inline CallBack<Event, Observer>::~CallBack()
{
    // empty
}


// will be called from CallBackBase (base class)
template <class Event, class Observer>
inline void CallBack<Event, Observer>::Notify(const Event& e)
{
    (m_obs->*m_f_notify)(e);
}


// will be called from CallBackBase (base class)
template <class Event, class Observer>
inline void CallBack<Event, Observer>::DisDead()
{
    /*  default value of pointer to function is NULL
        need to check if user inserted a function of his own */
    if ( m_f_disdead )
    {
        (m_obs->*m_f_disdead)();
    }
}



// *****************************************************************************
// *                             class Dispatcher                              *
// *****************************************************************************

// Will call NotifyAllOnDeath
template <class Event>
inline Dispatcher<Event>::~Dispatcher()
{
    NotifyAllOnDeath();
}

template <class Event>
inline void Dispatcher<Event>::NotifyAll(const Event& e) const
{
    typename std::list< CallBackBase<Event>* >::const_iterator itr, itr_last;
    itr_last = m_call_backs.end();

    for (   itr  = m_call_backs.begin() ;
            itr != itr_last             ;
          ++itr                         )
    {
        ((*itr)->Notify)(e);
    }
}

template <class Event>
inline void Dispatcher<Event>::Subscribe(CallBackBase<Event> *cb)
{
    /* 'connect' to CallBack */
    m_call_backs.push_back(cb);

    /* 'SetDispatcher' is CallBacks' function */
	cb->SetDispatcher(this);
}

// notify observers
template <class Event>
inline void Dispatcher<Event>::NotifyAllOnDeath() const
{
    typename std::list< CallBackBase<Event>* >::const_iterator itr, itr_last;
    itr_last = m_call_backs.end();

    for (   itr  = m_call_backs.begin() ;
            itr != itr_last             ;
          ++itr                         )
    {
        /* call users' function that notifies closed communication */
        ((*itr)->DisDead)();

        /*  observer/CallBack needs to disconnect from Dispatcher.
            Otherwise, when CallBack UnSubscribes function on
            dungling pointer will be called */
        (*itr)->SetDispatcher(NULL);
    }
}

template <class Event>
inline void Dispatcher<Event>::UnSubscribe(CallBackBase<Event> *cb)
{
    m_call_backs.erase(std::find ( m_call_backs.begin(),
                                   m_call_backs.end()  ,
                                   cb                  ));
}


} //namespace ilrd
