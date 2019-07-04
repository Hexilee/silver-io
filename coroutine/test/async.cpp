/*
 * Created by 李晨曦 on 2019-07-02.
 */
#include "gtest/gtest.h"
#include "coroutine/async.hpp"

using namespace sio::coroutine;
using namespace sio::future;

auto async_with_counter_future(uint64_t n) {
    auto async_task = async [=] {
        for (uint64_t i = 0; i < n; i++) {
            auto f = CounterFuture(n, n);
            EXPECT_EQ(n, await std::move(f));
        }
        return n * n;
    };
    
    uint64_t counter = 0;
    auto poll_result = async_task->poll();
    while (poll_result.status() == PollStatus::Pending) {
        counter++;
        poll_result = async_task->poll();
    }
    EXPECT_EQ(n * n, counter);
    EXPECT_EQ(n * n, poll_result.get());
}

TEST(AsyncCounterFuture, AsyncTest) {
    async_with_counter_future(1);
    async_with_counter_future(2);
    async_with_counter_future(3);
    async_with_counter_future(10);
    async_with_counter_future(100);
}