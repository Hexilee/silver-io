/*
 * Created by 李晨曦 on 2019-07-03.
 */

#include "gtest/gtest.h"
#include "coroutine/stream_iter.hpp"
#include "future/stream.hpp"

using namespace sio::future;
using namespace sio::coroutine;

TEST(RangeStreamTest, StreamIter) {
    auto stream = RangeStream<0, 20, 2>();
    auto iter = StreamIter(std::move(stream));
    for (auto i: iter) {
        std::cout << i << std::endl;
    }
}
