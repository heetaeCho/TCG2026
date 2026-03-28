// File: prog_set_start_test_113.cc

#include <gtest/gtest.h>
#include <climits>
#include "./TestProjects/re2/re2/prog.h"

using namespace re2;

class ProgTest_113 : public ::testing::Test {
protected:
    Prog prog_;
};

// Normal operation: setting typical values should be observable via start()
TEST_F(ProgTest_113, SetStartUpdatesValue_113) {
    prog_.set_start(0);
    EXPECT_EQ(prog_.start(), 0);

    prog_.set_start(1);
    EXPECT_EQ(prog_.start(), 1);

    prog_.set_start(42);
    EXPECT_EQ(prog_.start(), 42);
}

// Boundary: negative values (interface accepts int; verify observable result)
TEST_F(ProgTest_113, SetStart_AllowsNegative_113) {
    prog_.set_start(-5);
    EXPECT_EQ(prog_.start(), -5);
}

// Boundary: INT_MAX and INT_MIN should round-trip through the public API
TEST_F(ProgTest_113, SetStart_IntMaxMin_113) {
    prog_.set_start(INT_MAX);
    EXPECT_EQ(prog_.start(), INT_MAX);

    prog_.set_start(INT_MIN);
    EXPECT_EQ(prog_.start(), INT_MIN);
}

// Idempotence with same value: setting the same value again keeps the observable value
TEST_F(ProgTest_113, SetStart_Idempotent_113) {
    prog_.set_start(7);
    EXPECT_EQ(prog_.start(), 7);

    prog_.set_start(7);
    EXPECT_EQ(prog_.start(), 7);
}

// Independence: separate instances should not affect each other’s start value
TEST_F(ProgTest_113, MultipleInstances_IndependentState_113) {
    Prog a;
    Prog b;

    a.set_start(10);
    b.set_start(-20);

    EXPECT_EQ(a.start(), 10);
    EXPECT_EQ(b.start(), -20);

    // Changing one should not change the other
    a.set_start(30);
    EXPECT_EQ(a.start(), 30);
    EXPECT_EQ(b.start(), -20);
}
