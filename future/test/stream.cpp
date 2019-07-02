/*
 * Created by 李晨曦 on 2019-07-02.
 */

#include "gtest/gtest.h"
#include "future/stream.hpp"

using namespace sio::future;

TEST(RangeStreamTest, RangeStream) {
    auto stream = RangeStream<0, 100, 2>();
    for (auto i = 0; i < 100; i++) {
        auto flow = stream.flow();
        if (i % 2 == 0) {
            EXPECT_EQ(FlowStatus::Continue, flow.status());
            EXPECT_EQ(i, flow.get());
        } else {
            EXPECT_EQ(FlowStatus::Pending, flow.status());
        }
    }
    EXPECT_EQ(FlowStatus::Break, stream.flow().status());
}
