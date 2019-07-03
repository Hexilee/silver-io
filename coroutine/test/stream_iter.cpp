/*
 * Created by 李晨曦 on 2019-07-03.
 */

#include "gtest/gtest.h"
#include "coroutine/stream_iter.hpp"
#include "coroutine/async.hpp"
#include "future/stream.hpp"

using namespace sio::future;
using namespace sio::coroutine;

TEST(RangeStreamTest, StreamIter) {
    auto iter_future = async [] {
        auto stream = RangeStream<0, 20, 2>();
        auto iter = StreamIter(std::move(stream));
        auto ret = 0;
        for (auto i = iter.begin(); i != iter.end(); i++) {
            ret++;
            std::cout << "i = " << *i << std::endl;
        }
        return ret;
    };
    uint64_t counter = 0;
    auto poll_result = iter_future->poll();
    while (poll_result.status() == PollStatus::Pending) {
        counter++;
        poll_result = iter_future->poll();
    }
    std::cout << "counter = " << counter << std::endl;
    std::cout << "poll_result = " << poll_result.get() << std::endl;
}
