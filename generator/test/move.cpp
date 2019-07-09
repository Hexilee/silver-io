/*
 * Created by 李晨曦 on 2019-07-09.
 */

#include "generator/generator.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <memory>

using sio::generator::Generator;
using std::make_unique;

auto fab(int n) {
    return new Generator<int, std::unique_ptr<int>>([=] {
        int a = 0, b = 1, next;
        for (int i = 0; i < n; i++) {
            Generator<int, int>::yield(a);
            next = a + b;
            a = b;
            b = next;
        }
        return make_unique<int>(a);
    });
}

TEST(Move, GeneratorMoveTest) {
    auto g = fab(100);
    auto a = g->resume();
    auto b = g->resume();
    int next;
    while (!g->is_complete()) {
        next = g->resume();
        EXPECT_EQ(a + b, next);
        a = b;
        b = next;
    }
    EXPECT_EQ(a + b, *g->result());
    EXPECT_EQ(a + b, *g->result());
    auto to = g->result();
    EXPECT_EQ(nullptr, g->result().get());
}