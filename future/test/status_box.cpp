/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "gtest/gtest.h"
#include "future/future.hpp"
#include "future/stream.hpp"

using namespace sio::future;

TEST(Poll, StatusBoxTest) {
    EXPECT_EQ(1, Poll(1).release());
    EXPECT_EQ(PollStatus::Ready, Poll(1).status());
    EXPECT_EQ(PollStatus::Pending, Poll<int>().status());
}

TEST(Flow, StatusBoxTest) {
    EXPECT_EQ(1, Flow(1).release());
    EXPECT_EQ(FlowStatus::Continue, Flow(1).status());
    EXPECT_EQ(FlowStatus::Pending, Flow<int>().status());
    EXPECT_EQ(FlowStatus::Break, Flow<int>::Break().status());
}

