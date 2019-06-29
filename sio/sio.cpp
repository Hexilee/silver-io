/*
 * Created by 李晨曦 on 2019-06-25.
 */
#include "sio/sio.hpp"

using namespace sio;
using std::make_unique;

auto init_event_loop() -> std::unique_ptr<thread> {
    return make_unique<thread>([event_loop = EventLoop](){
        event_loop->run();
    });
}
