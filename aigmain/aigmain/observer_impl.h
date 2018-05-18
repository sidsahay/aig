#pragma once
#include "observer.h"

template<typename GameT>
inline bool aig::Observer<GameT>::EventsAvailable()
{
    return _event_queue.size() != 0;
}

template<typename GameT>
inline typename GameT::EventT aig::Observer<GameT>::GetEvent()
{
    typename GameT::EventT front = _event_queue.front();
    _event_queue.pop_front();
    return front;
}

template<typename GameT>
inline void aig::Observer<GameT>::PushEvent(typename GameT::EventT event)
{
    _event_queue.push_back(event);
}

template<typename GameT>
inline void aig::ObservationTarget<GameT>::AddObserver(Observer<GameT>* observer)
{
    _observers.push_back(observer);
}

template<typename GameT>
inline void aig::ObservationTarget<GameT>::Broadcast(typename GameT::EventT event)
{
    for (auto observer : _observers)
    {
        observer->PushEvent(event);
    }
}
