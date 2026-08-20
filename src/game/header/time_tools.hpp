#ifndef TIMETOOLS 
#define TIMETOOLS

#include <chrono>

class Clock{
    private:
        std::chrono::milliseconds savedTime;
        int hz;
        std::chrono::milliseconds delayTime;
    public:
        Clock(unsigned int hz);
        void tick();
        static std::chrono::milliseconds get_current_millis();
};


class Interval{
    private:
        std::chrono::milliseconds savedTime;
        std::chrono::milliseconds  delayTime;
    public:
        Interval(unsigned int ms);
        void reset_time();
        bool interval_passed();
        bool peek_interval_passed();
};




#endif



