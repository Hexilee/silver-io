/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_SIO_HPP
#define SILVER_IO_SIO_HPP
#include <memory>
#include <thread>
#include "uvw.hpp"
namespace sio {
    using std::thread;
    thread_local auto EventLoop = uvw::Loop::create();
    auto init_event_loop() -> std::unique_ptr<thread>;
}

#endif //SILVER_IO_SIO_HPP
