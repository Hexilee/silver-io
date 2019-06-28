/*
 * Created by 李晨曦 on 2019-06-28.
 */

#ifndef SILVER_IO_CONTEXT_HPP
#define SILVER_IO_CONTEXT_HPP
#include "future/future.hpp"
#include <memory>
#include <exception>
namespace sio::tls {
    using namespace future;
    using std::shared_ptr;
    using std::make_shared;
    thread_local shared_ptr<Context> ThreadLocalContext = make_shared<FuncContext>([](){
        // do nothing
    });
}
#endif //SILVER_IO_CONTEXT_HPP
