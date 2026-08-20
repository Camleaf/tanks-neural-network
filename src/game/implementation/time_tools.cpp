#include <time_tools.hpp>
#include <chrono>
#include <thread>

Clock::Clock(unsigned int hz) {
    hz = hz;
    delayTime = std::chrono::milliseconds(1000/hz);
    savedTime = Clock::get_current_millis();
}

std::chrono::milliseconds Clock::get_current_millis() {
    auto now = std::chrono::steady_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
}

void Clock::tick(){
    savedTime+=delayTime;
    std::chrono::milliseconds new_delay = savedTime - Clock::get_current_millis();
    if (delayTime.count()>0){
        std::this_thread::sleep_for(delayTime);
    } else {
        savedTime= Clock::get_current_millis();
    }
}


Interval::Interval(unsigned int ms){
    delayTime = std::chrono::milliseconds(ms);
    reset_time();
}

void Interval::reset_time(){
    savedTime = Clock::get_current_millis();
}

bool Interval::interval_passed(){
    bool passed = peek_interval_passed();
    if (passed) reset_time();
    return passed;
}

bool Interval::peek_interval_passed(){
    return (Clock::get_current_millis()-savedTime)>=delayTime;
}
