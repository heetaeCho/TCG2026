#include <gtest/gtest.h>
#include <cstdlib>
#include <set>
#include <cmath>

// Declaration of the function under test
int random(int low, int high);

TEST(RandomFunctionTest_119, ReturnsSameValueWhenLowEqualsHigh_119) {
    // When low == high, the function should always return that value
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(5, random(5, 5));
    }
}

TEST(RandomFunctionTest_119, ReturnsValueWithinRange_119) {
    // The returned value should be within [low, high] range
    srand(42);
    for (int i = 0; i < 1000; ++i) {
        int result = random(0, 10);
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 10);
    }
}

TEST(RandomFunctionTest_119, ReturnsValueWithinRangeNegative_119) {
    // Test with negative range
    srand(123);
    for (int i = 0; i < 1000; ++i) {
        int result = random(-10, -1);
        EXPECT_GE(result, -10);
        EXPECT_LE(result, -1);
    }
}

TEST(RandomFunctionTest_119, ReturnsValueWithinRangeMixed_119) {
    // Test with a range spanning negative to positive
    srand(456);
    for (int i = 0; i < 1000; ++i) {
        int result = random(-5, 5);
        EXPECT_GE(result, -5);
        EXPECT_LE(result, 5);
    }
}

TEST(RandomFunctionTest_119, ReturnsLowWhenRangeIsZero_119) {
    EXPECT_EQ(0, random(0, 0));
    EXPECT_EQ(-1, random(-1, -1));
    EXPECT_EQ(100, random(100, 100));
}

TEST(RandomFunctionTest_119, ProducesVariousValues_119) {
    // Over many iterations, we should see more than one distinct value
    srand(789);
    std::set<int> seen;
    for (int i = 0; i < 1000; ++i) {
        seen.insert(random(0, 100));
    }
    // We should see a good distribution - at least several distinct values
    EXPECT_GT(seen.size(), 1u);
}

TEST(RandomFunctionTest_119, LargeRange_119) {
    srand(101);
    for (int i = 0; i < 1000; ++i) {
        int result = random(0, 1000000);
        EXPECT_GE(result, 0);
        EXPECT_LE(result, 1000000);
    }
}

TEST(RandomFunctionTest_119, SmallRangeOfOne_119) {
    srand(202);
    for (int i = 0; i < 100; ++i) {
        int result = random(3, 4);
        EXPECT_GE(result, 3);
        EXPECT_LE(result, 4);
    }
}

TEST(RandomFunctionTest_119, BoundaryValuesReachable_119) {
    // With enough iterations, both low and high should be reachable
    srand(303);
    bool saw_low = false;
    bool saw_high = false;
    for (int i = 0; i < 10000; ++i) {
        int result = random(0, 1);
        if (result == 0) saw_low = true;
        if (result == 1) saw_high = true;
        if (saw_low && saw_high) break;
    }
    EXPECT_TRUE(saw_low);
    EXPECT_TRUE(saw_high);
}

TEST(RandomFunctionTest_119, DeterministicWithSameSeed_119) {
    // With the same seed, should produce the same sequence
    srand(12345);
    int result1 = random(0, 100);
    int result2 = random(0, 100);
    int result3 = random(0, 100);

    srand(12345);
    EXPECT_EQ(result1, random(0, 100));
    EXPECT_EQ(result2, random(0, 100));
    EXPECT_EQ(result3, random(0, 100));
}

TEST(RandomFunctionTest_119, ZeroToZero_119) {
    EXPECT_EQ(0, random(0, 0));
}

TEST(RandomFunctionTest_119, LargeNegativeRange_119) {
    srand(404);
    for (int i = 0; i < 1000; ++i) {
        int result = random(-1000000, -1);
        EXPECT_GE(result, -1000000);
        EXPECT_LE(result, -1);
    }
}
