/*
 * Created by 李晨曦 on 2019-06-25.
 */

#ifndef SILVER_IO_SIO_HPP
#define SILVER_IO_SIO_HPP
#include "future/future.hpp"
#include <thread>
#include "uvw.hpp"
namespace sio {
    using std::thread;
    using std::shared_ptr;
    extern thread_local shared_ptr<uvw::Loop> EventLoop;
    auto init_event_loop() -> std::unique_ptr<thread>;
}

#endif //SILVER_IO_SIO_HPP
