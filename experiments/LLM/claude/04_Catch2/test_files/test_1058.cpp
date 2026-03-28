#include <gtest/gtest.h>
#include <cmath>
#include <random>
#include <limits>
#include <set>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

class UniformFloatingPointDistributionTest_1058 : public ::testing::Test {
protected:
    std::minstd_rand generator{42};
};

// Test that a() returns the lower bound passed to the constructor (float)
TEST_F(UniformFloatingPointDistributionTest_1058, AReturnsLowerBoundFloat_1058) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 5.0f);
    EXPECT_FLOAT_EQ(dist.a(), 1.0f);
}

// Test that b() returns the upper bound passed to the constructor (float)
TEST_F(UniformFloatingPointDistributionTest_1058, BReturnsUpperBoundFloat_1058) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 5.0f);
    EXPECT_FLOAT_EQ(dist.b(), 5.0f);
}

// Test that a() returns the lower bound passed to the constructor (double)
TEST_F(UniformFloatingPointDistributionTest_1058, AReturnsLowerBoundDouble_1058) {
    Catch::uniform_floating_point_distribution<double> dist(2.0, 10.0);
    EXPECT_DOUBLE_EQ(dist.a(), 2.0);
}

// Test that b() returns the upper bound passed to the constructor (double)
TEST_F(UniformFloatingPointDistributionTest_1058, BReturnsUpperBoundDouble_1058) {
    Catch::uniform_floating_point_distribution<double> dist(2.0, 10.0);
    EXPECT_DOUBLE_EQ(dist.b(), 10.0);
}

// Test that generated values fall within [a, b] for float
TEST_F(UniformFloatingPointDistributionTest_1058, GeneratedValuesInRangeFloat_1058) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 5.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(generator);
        EXPECT_GE(val, 1.0f);
        EXPECT_LE(val, 5.0f);
    }
}

// Test that generated values fall within [a, b] for double
TEST_F(UniformFloatingPointDistributionTest_1058, GeneratedValuesInRangeDouble_1058) {
    Catch::uniform_floating_point_distribution<double> dist(2.0, 10.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, 2.0);
        EXPECT_LE(val, 10.0);
    }
}

// Test with a == b (degenerate range), should always return a
TEST_F(UniformFloatingPointDistributionTest_1058, DegenerateRangeFloat_1058) {
    Catch::uniform_floating_point_distribution<float> dist(3.0f, 3.0f);
    EXPECT_FLOAT_EQ(dist.a(), 3.0f);
    EXPECT_FLOAT_EQ(dist.b(), 3.0f);
    for (int i = 0; i < 100; ++i) {
        float val = dist(generator);
        EXPECT_FLOAT_EQ(val, 3.0f);
    }
}

// Test with a == b (degenerate range) for double
TEST_F(UniformFloatingPointDistributionTest_1058, DegenerateRangeDouble_1058) {
    Catch::uniform_floating_point_distribution<double> dist(7.5, 7.5);
    EXPECT_DOUBLE_EQ(dist.a(), 7.5);
    EXPECT_DOUBLE_EQ(dist.b(), 7.5);
    for (int i = 0; i < 100; ++i) {
        double val = dist(generator);
        EXPECT_DOUBLE_EQ(val, 7.5);
    }
}

// Test with zero as lower bound
TEST_F(UniformFloatingPointDistributionTest_1058, ZeroLowerBound_1058) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    EXPECT_DOUBLE_EQ(dist.a(), 0.0);
    EXPECT_DOUBLE_EQ(dist.b(), 1.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test with negative range
TEST_F(UniformFloatingPointDistributionTest_1058, NegativeRange_1058) {
    Catch::uniform_floating_point_distribution<double> dist(-5.0, -1.0);
    EXPECT_DOUBLE_EQ(dist.a(), -5.0);
    EXPECT_DOUBLE_EQ(dist.b(), -1.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, -5.0);
        EXPECT_LE(val, -1.0);
    }
}

// Test with range spanning zero (negative to positive)
TEST_F(UniformFloatingPointDistributionTest_1058, RangeSpanningZero_1058) {
    Catch::uniform_floating_point_distribution<double> dist(-3.0, 3.0);
    EXPECT_DOUBLE_EQ(dist.a(), -3.0);
    EXPECT_DOUBLE_EQ(dist.b(), 3.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, -3.0);
        EXPECT_LE(val, 3.0);
    }
}

// Test with very small range
TEST_F(UniformFloatingPointDistributionTest_1058, VerySmallRange_1058) {
    double a = 1.0;
    double b = 1.0 + 1e-10;
    Catch::uniform_floating_point_distribution<double> dist(a, b);
    EXPECT_DOUBLE_EQ(dist.a(), a);
    EXPECT_DOUBLE_EQ(dist.b(), b);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test that the distribution produces different values (not always the same)
TEST_F(UniformFloatingPointDistributionTest_1058, ProducesDifferentValues_1058) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 100.0);
    std::set<double> values;
    for (int i = 0; i < 1000; ++i) {
        values.insert(dist(generator));
    }
    // Should produce many distinct values
    EXPECT_GT(values.size(), 1u);
}

// Test with different generator types
TEST_F(UniformFloatingPointDistributionTest_1058, WorksWithMT19937_1058) {
    std::mt19937 mt_gen(12345);
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(mt_gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test with large range
TEST_F(UniformFloatingPointDistributionTest_1058, LargeRange_1058) {
    Catch::uniform_floating_point_distribution<double> dist(-1e15, 1e15);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, -1e15);
        EXPECT_LE(val, 1e15);
    }
}

// Test with float very small positive range near zero
TEST_F(UniformFloatingPointDistributionTest_1058, SmallPositiveRangeNearZeroFloat_1058) {
    float a = 0.0f;
    float b = std::numeric_limits<float>::min();
    Catch::uniform_floating_point_distribution<float> dist(a, b);
    EXPECT_FLOAT_EQ(dist.a(), a);
    EXPECT_FLOAT_EQ(dist.b(), b);
    for (int i = 0; i < 100; ++i) {
        float val = dist(generator);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test construction with both bounds being zero
TEST_F(UniformFloatingPointDistributionTest_1058, BothBoundsZero_1058) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 0.0);
    EXPECT_DOUBLE_EQ(dist.a(), 0.0);
    EXPECT_DOUBLE_EQ(dist.b(), 0.0);
    for (int i = 0; i < 100; ++i) {
        double val = dist(generator);
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test that a() and b() are consistent after multiple calls to operator()
TEST_F(UniformFloatingPointDistributionTest_1058, AccessorsConsistentAfterGeneration_1058) {
    Catch::uniform_floating_point_distribution<double> dist(1.5, 9.5);
    for (int i = 0; i < 100; ++i) {
        dist(generator);
    }
    EXPECT_DOUBLE_EQ(dist.a(), 1.5);
    EXPECT_DOUBLE_EQ(dist.b(), 9.5);
}

// Test with negative lower bound and zero upper bound
TEST_F(UniformFloatingPointDistributionTest_1058, NegativeToZero_1058) {
    Catch::uniform_floating_point_distribution<double> dist(-10.0, 0.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(generator);
        EXPECT_GE(val, -10.0);
        EXPECT_LE(val, 0.0);
    }
}

// Test that values are somewhat uniformly distributed (basic statistical check)
TEST_F(UniformFloatingPointDistributionTest_1058, RoughlyUniformDistribution_1058) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    int below_half = 0;
    int above_half = 0;
    const int N = 100000;
    for (int i = 0; i < N; ++i) {
        double val = dist(generator);
        if (val < 0.5) {
            below_half++;
        } else {
            above_half++;
        }
    }
    // Expect roughly 50/50 split, with some tolerance
    double ratio = static_cast<double>(below_half) / N;
    EXPECT_GT(ratio, 0.45);
    EXPECT_LT(ratio, 0.55);
}
