/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#define await(future_obj) ({\
    auto result = future_obj.poll(sio::ThreadLocalContext);\
    while (!result.is_complete()) {\
        yield(coroutine::Yield());\
        result = future_obj.poll(sio::ThreadLocalContext);\
    }\
    result.get()\
})

namespace coroutine {
    struct Yield {};
}
#endif //SILVER_IO_ASYNC_HPP
