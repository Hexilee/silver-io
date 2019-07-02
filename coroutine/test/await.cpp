/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "gtest/gtest.h"

#include "coroutine/async.hpp"
#include "future/future.hpp"
using sio::future::FutureOk;

TEST(AwaitFutureOk, AwaitTest) {
    EXPECT_EQ(1, await FutureOk(1));
    EXPECT_EQ("name", await FutureOk((char*)"name"));
    EXPECT_EQ(true, await FutureOk(true));
    EXPECT_NE(1, await FutureOk(2));
    EXPECT_NE("name", await FutureOk((char*)"age"));
    EXPECT_NE(true, await FutureOk(false));
}