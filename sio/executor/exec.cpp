/*
 * Created by 李晨曦 on 2019-06-29.
 */

#include "sio/executor/exec.hpp"

template<class Output>
auto sio::executor::block_on(const Future<Output> &main_task) -> Output {
    auto&& loop_thread = init_event_loop();
    auto result = main_task.wait();
    EventLoop->stop();
    loop_thread->join();
    return result;
}
