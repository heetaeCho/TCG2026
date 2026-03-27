// File: counts_allok_tests_307.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_totals.hpp"

using Catch::Counts;

class CountsTest_307 : public ::testing::Test {
protected:
    Counts c{};
};

// [Normal] allOk should be true when there are zero failed tests
TEST_F(CountsTest_307, AllOkTrueWhenNoFailed_307) {
    c.passed = 5;
    c.failed = 0;
    c.failedButOk = 0;
    c.skipped = 0;

    EXPECT_TRUE(c.allOk());
}

// [Error case] allOk should be false when there is at least one failed test
TEST_F(CountsTest_307, AllOkFalseWhenThereIsAFailed_307) {
    c.passed = 0;
    c.failed = 1;
    c.failedButOk = 0;
    c.skipped = 0;

    EXPECT_FALSE(c.allOk());
}

// [Boundary/Interaction] allOk depends only on `failed`, not on other counters
TEST_F(CountsTest_307, AllOkIgnoresOtherCountersWhenFailedIsZero_307) {
    c.passed = 0;
    c.failed = 0;
    c.failedButOk = 123;   // even if there are "failed but ok"
    c.skipped = 456;       // or skipped
    EXPECT_TRUE(c.allOk()); // still OK because failed == 0
}

// [Boundary] Large values: if failed is large non-zero, allOk must be false
TEST_F(CountsTest_307, AllOkWithMaxFailedIsFalse_307) {
    c.passed = std::numeric_limits<std::uint64_t>::max();
    c.failed = std::numeric_limits<std::uint64_t>::max();
    c.failedButOk = std::numeric_limits<std::uint64_t>::max();
    c.skipped = std::numeric_limits<std::uint64_t>::max();

    EXPECT_FALSE(c.allOk());
}

// [Boundary] Mixed large counters but failed == 0 keeps allOk true
TEST_F(CountsTest_307, AllOkWithLargeCountsButZeroFailedIsTrue_307) {
    c.passed = std::numeric_limits<std::uint64_t>::max();
    c.failed = 0;
    c.failedButOk = std::numeric_limits<std::uint64_t>::max();
    c.skipped = std::numeric_limits<std::uint64_t>::max();

    EXPECT_TRUE(c.allOk());
}
