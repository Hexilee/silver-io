/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_ASYNC_HPP
#define SILVER_IO_ASYNC_HPP
#include <thread>
#define await(future_obj) ({\
    auto result = future_obj.poll(future::ThreadLocalContext);\
    while (!result.is_complete()) {\
        yield();\
        result = future_obj.poll(sio::ThreadLocalContext);\
    }\
    result.get()\
})

#endif //SILVER_IO_ASYNC_HPP
