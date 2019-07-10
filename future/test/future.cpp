/*
 * Created by 李晨曦 on 2019-07-10.
 */

#include "gtest/gtest.h"
#include "future/future.hpp"

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

TEST(CounterFuture, FutrueTest) {
    EXPECT_EQ(1, FutureOk(1).poll().release());
    auto p = FutureOk(std::make_unique<int>(1)).poll();
    decltype(auto) ref = p.release();
    EXPECT_EQ(1, *ref);
    auto moved = p.release();
    EXPECT_EQ(1, *moved);
    EXPECT_EQ(nullptr, p.release().get());
}