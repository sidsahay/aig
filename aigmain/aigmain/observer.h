#pragma once
#include <deque>
#include <vector>

namespace aig
{
    //Observers receive events from ObservationTargets.
    template <typename GameT>
    class Observer
    {
        public:
        bool EventsAvailable();

        //Call this ONLY after checking whether events are available via EventsAvailable()
        typename GameT::EventT GetEvent();

        void PushEvent(typename GameT::EventT event);

        private:
        std::deque<typename GameT::EventT> _event_queue;
    };

    //ObservationTargets emit events for Observers to receive.
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