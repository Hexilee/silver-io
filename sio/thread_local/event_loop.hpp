/*
 * Created by 李晨曦 on 2019-06-28.
 */

#ifndef SILVER_IO_EVENT_LOOP_HPP
#define SILVER_IO_EVENT_LOOP_HPP
#include "src/uvw/loop.hpp"
namespace sio::tls {
    thread_local auto EventLoop = uvw::Loop::create();
}
#endif //SILVER_IO_EVENT_LOOP_HPP
