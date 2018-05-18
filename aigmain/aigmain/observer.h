#pragma once
#include <deque>
#include <vector>

namespace aig
{
    template <typename GameT>
    class Observer
    {
        public:
        bool EventsAvailable();
        typename GameT::EventT GetEvent();

        void PushEvent(typename GameT::EventT event);

        private:
        std::deque<typename GameT::EventT> _event_queue;
    };

    //An Observer observes an ObservationTarget for events, see?
    template <typename GameT>
    class ObservationTarget
    {
        public:
        void AddObserver(Observer<GameT>* observer);

        void Broadcast(typename GameT::EventT event);

        private:
        std::vector<Observer<GameT>*> _observers;
    };
}