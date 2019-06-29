/*
 * Created by 李晨曦 on 2019-06-29.
 */

#ifndef SILVER_IO_EXEC_HPP
#define SILVER_IO_EXEC_HPP
#include "sio/sio.hpp"
namespace sio::executor {
    using namespace sio;
    using namespace future;
    template <class Output>
    auto block_on(const Future<Output>& main_task) -> Output;
}
#endif //SILVER_IO_EXEC_HPP
