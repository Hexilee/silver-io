/*
 * Created by 李晨曦 on 2019-07-03.
 */

#include "gtest/gtest.h"
#include "coroutine/stream_iter.hpp"
#include "coroutine/async.hpp"
#include "future/stream.hpp"

using namespace sio::future;
using namespace sio::coroutine;

template<int64_t From, int64_t To, int64_t Diff = 1>
auto rang_stream_to_iter() {
    auto iter_future = async [] {
        auto stream = RangeStream<From, To, Diff>();
        auto iter = StreamIter(stream);
        auto ret = 0;
        for (auto i: iter) {
            EXPECT_EQ(ret * Diff + From, i);
            ret++;
        }
        return ret;
    };
    auto counter = 0;
    auto poll_result = iter_future->poll();
    while (poll_result.status() == PollStatus::Pending) {
        counter++;
        poll_result = iter_future->poll();
    }
    EXPECT_EQ((To - 1 - From) / Diff + 1, poll_result.get()); // continue times
    EXPECT_EQ(To - From - 1 - poll_result.get(), counter); //pending times = total times - continue times
}

TEST(RangeStreamTest, StreamIter) {
    rang_stream_to_iter<0, 20, 2>();
    rang_stream_to_iter<1, 20, 2>();
    rang_stream_to_iter<1, 20, 3>();
    rang_stream_to_iter<3, 200, 7>();
}
