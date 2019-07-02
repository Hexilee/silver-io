/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "gtest/gtest.h"
#include "future/future.hpp"
#include "future/stream.hpp"

using namespace sio::future;

TEST(PollNormal, Poll) {
    int i = 1;
    EXPECT_EQ(i, Poll(i).get());
    EXPECT_EQ(PollStatus::Ready, Poll(i).status());
    EXPECT_EQ(PollStatus::Pending, Poll<int>().status());
}

TEST(FlowNormal, Flow) {
    int i = 1;
    EXPECT_EQ(i, Flow(i).get());
    EXPECT_EQ(FlowStatus::Continue, Flow(i).status());
    EXPECT_EQ(FlowStatus::Pending, Flow<int>().status());
    EXPECT_EQ(FlowStatus::Break, Flow<int>::Break().status());
}

