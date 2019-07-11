/*
 * Created by 李晨曦 on 2019-06-25.
 */
#include "sio/sio.hpp"

using std::make_unique;
thread_local auto sio::EventLoop = uvw::Loop::create();

// TODO: block event loop
auto sio::init_event_loop() -> std::unique_ptr<thread> {
    return make_unique<thread>([event_loop = sio::EventLoop]() {
        event_loop->run();
        spdlog::debug("thread {:s}: event loop stop", (std::stringstream() << std::this_thread::get_id()).str());
    });
}
