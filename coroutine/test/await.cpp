/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "gtest/gtest.h"

#include "coroutine/async.hpp"
#include "future/future.hpp"
#include "future/stream.hpp"

using namespace sio::future;
using namespace sio::coroutine;

TEST(FutureOk, AwaitFutureTest) {
    EXPECT_EQ(1, await FutureOk(1));
    EXPECT_EQ("name", await FutureOk((char*)"name"));
    EXPECT_EQ(true, await FutureOk(true));
    EXPECT_NE(1, await FutureOk(2));
    EXPECT_NE("name", await FutureOk((char*)"age"));
    EXPECT_NE(true, await FutureOk(false));
}

template<int64_t From, int64_t To, int64_t Diff = 1>
auto async_stream() {
    auto iter_future = async [] {
        auto ret = 0;
        for (auto i: await RangeStream<From, To, Diff>()) {
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
    EXPECT_EQ(To - From - poll_result.get(), counter); //pending times = total times - continue times
}

TEST(RangeStream, AwaitStreamTest) {
    async_stream<0, 20, 2>();
    async_stream<1, 20, 2>();
    async_stream<1, 20, 3>();
    async_stream<3, 200, 7>();
}
