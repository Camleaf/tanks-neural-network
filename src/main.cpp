#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <future>
#include <gameInstance.hpp>
#include <constants.hpp>
#include <X11/Xlib.h>
#include <thread>
using namespace std::chrono_literals;

#define GAME_COUNTS 1

typedef void (*threadRef)(int id);
/*
int main()
{   
    XInitThreads();
    std::vector<std::thread> gameMainloops;
    
    for (int i = 0;i<GAME_COUNTS;i++){
        gameMainloops.push_back(std::thread(instance_mainloop,i)); 
    }

    while (!gameMainloops.empty()) {
        for (auto it = gameMainloops.begin(); it != gameMainloops.end();){
            if (!it->joinable()) {
                it = gameMainloops.erase(it);
            } else {
                ++it;
            }
        }
    }
}*/

int main(){
    instance_mainloop(0);
}
