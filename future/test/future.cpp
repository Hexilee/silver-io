/*
 * Created by 李晨曦 on 2019-07-10.
 */

#include "gtest/gtest.h"
#include "future/future.hpp"

using sio::future::Future;
using sio::future::PollStatus;
using sio::future::FutureOk;
using sio::future::CounterFuture;

TEST(FutrueOk, FutrueTest) {
    EXPECT_EQ(1, FutureOk(1).poll().release());
    auto p = FutureOk(std::make_unique<int>(1)).poll();
    decltype(auto) ref = p.release();
    EXPECT_EQ(1, *ref);
    auto moved = p.release();
    EXPECT_EQ(1, *moved);
    EXPECT_EQ(nullptr, p.release().get());
}

template<typename T>
auto poll(Future<T> &&f) {
    auto ret = f.poll();
    while (ret.status() == PollStatus::Pending) {
        ret = f.poll();
    }
    return ret;
}

TEST(CounterFuture, FutrueTest) {
    EXPECT_EQ(1, poll(CounterFuture(1, 5)).release());
    auto p = poll(CounterFuture(std::make_unique<int>(1), 5));
    decltype(auto) ref = p.release();
    EXPECT_EQ(1, *ref);
    auto moved = p.release();
    EXPECT_EQ(1, *moved);
    EXPECT_EQ(nullptr, p.release().get());
}