/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_EXEC_HPP
#define SILVER_IO_EXEC_HPP
#include "sio/sio.hpp"
#include "coroutine/co_future.hpp"
#include "coroutine/async.hpp"
#include <type_traits>
#include <memory>

#define block_on sio::executor::Blocker() <<
namespace sio::executor {
    using namespace sio;
    using namespace future;
    using sio::coroutine::Ret;
    
    class Blocker {
      public:
        template<typename T>
        auto operator<<(Future<T> &&main_task) -> T;
        
        template<typename Fn>
        auto operator<<(Fn &&main_task) -> Ret<Fn>;
        
        template<class T>
        auto operator<<(std::unique_ptr<Future<T>> &&main_task) -> T;
    };
    
    template<class T>
    auto Blocker::operator<<(Future<T> &&main_task) -> T {
        auto loop_thread = init_event_loop();
        auto result = main_task.wait();
        EventLoop->stop();
        loop_thread->join();
        return std::move(result);
    }
    
    template<class Fn>
    auto Blocker::operator<<(Fn &&main_task) -> Ret<Fn> {
        return this << (async main_task);
    }
    
    template<class T>
    auto Blocker::operator<<(unique_ptr<Future<T>> &&main_task) -> T {
        return this << std::move(*main_task);
    }
    
}
#endif //SILVER_IO_EXEC_HPP
