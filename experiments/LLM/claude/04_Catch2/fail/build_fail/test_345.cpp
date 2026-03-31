#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <random>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

class UniformFloatingPointDistributionTest_345 : public ::testing::Test {
protected:
};

// Test that a() and b() return the constructor parameters for double
TEST_F(UniformFloatingPointDistributionTest_345, ConstructorStoresParameters_345) {
    Catch::uniform_floating_point_distribution<double> dist(1.0, 10.0);
    EXPECT_DOUBLE_EQ(dist.a(), 1.0);
    EXPECT_DOUBLE_EQ(dist.b(), 10.0);
}

// Test that a() and b() return the constructor parameters for float
TEST_F(UniformFloatingPointDistributionTest_345, ConstructorStoresParametersFloat_345) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 10.0f);
    EXPECT_FLOAT_EQ(dist.a(), 1.0f);
    EXPECT_FLOAT_EQ(dist.b(), 10.0f);
}

// Test with zero range (a == b)
TEST_F(UniformFloatingPointDistributionTest_345, ZeroRangeDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(5.0, 5.0);
    EXPECT_DOUBLE_EQ(dist.a(), 5.0);
    EXPECT_DOUBLE_EQ(dist.b(), 5.0);

    std::mt19937 gen(42);
    double val = dist(gen);
    EXPECT_DOUBLE_EQ(val, 5.0);
}

// Test with zero range for float
TEST_F(UniformFloatingPointDistributionTest_345, ZeroRangeFloat_345) {
    Catch::uniform_floating_point_distribution<float> dist(3.0f, 3.0f);
    EXPECT_FLOAT_EQ(dist.a(), 3.0f);
    EXPECT_FLOAT_EQ(dist.b(), 3.0f);

    std::mt19937 gen(42);
    float val = dist(gen);
    EXPECT_FLOAT_EQ(val, 3.0f);
}

// Test generated values are within range [a, b] for double
TEST_F(UniformFloatingPointDistributionTest_345, GeneratedValuesInRangeDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(1.0, 10.0);
    std::mt19937 gen(12345);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 1.0) << "Value " << val << " is less than a=1.0";
        EXPECT_LE(val, 10.0) << "Value " << val << " is greater than b=10.0";
    }
}

// Test generated values are within range [a, b] for float
TEST_F(UniformFloatingPointDistributionTest_345, GeneratedValuesInRangeFloat_345) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 10.0f);
    std::mt19937 gen(12345);

    for (int i = 0; i < 1000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, 1.0f) << "Value " << val << " is less than a=1.0f";
        EXPECT_LE(val, 10.0f) << "Value " << val << " is greater than b=10.0f";
    }
}

// Test with negative range
TEST_F(UniformFloatingPointDistributionTest_345, NegativeRangeDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(-10.0, -1.0);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), -10.0);
    EXPECT_DOUBLE_EQ(dist.b(), -1.0);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -10.0);
        EXPECT_LE(val, -1.0);
    }
}

// Test with range crossing zero
TEST_F(UniformFloatingPointDistributionTest_345, RangeCrossingZeroDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(-5.0, 5.0);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), -5.0);
    EXPECT_DOUBLE_EQ(dist.b(), 5.0);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -5.0);
        EXPECT_LE(val, 5.0);
    }
}

// Test with very small range
TEST_F(UniformFloatingPointDistributionTest_345, VerySmallRangeDouble_345) {
    double a = 1.0;
    double b = 1.0 + 1e-10;
    Catch::uniform_floating_point_distribution<double> dist(a, b);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), a);
    EXPECT_DOUBLE_EQ(dist.b(), b);

    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test with a = 0.0
TEST_F(UniformFloatingPointDistributionTest_345, RangeStartingAtZeroDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), 0.0);
    EXPECT_DOUBLE_EQ(dist.b(), 1.0);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test with b = 0.0
TEST_F(UniformFloatingPointDistributionTest_345, RangeEndingAtZeroDouble_345) {
    Catch::uniform_floating_point_distribution<double> dist(-1.0, 0.0);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), -1.0);
    EXPECT_DOUBLE_EQ(dist.b(), 0.0);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -1.0);
        EXPECT_LE(val, 0.0);
    }
}

// Test with different generators
TEST_F(UniformFloatingPointDistributionTest_345, DifferentGenerator_345) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 100.0);
    std::mt19937_64 gen(42);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 100.0);
    }
}

// Test that different seeds produce different sequences (statistical test)
TEST_F(UniformFloatingPointDistributionTest_345, DifferentSeedsProduceDifferentValues_345) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    std::mt19937 gen1(42);
    std::mt19937 gen2(123456);

    bool all_same = true;
    for (int i = 0; i < 100; ++i) {
        double v1 = dist(gen1);
        double v2 = dist(gen2);
        if (v1 != v2) {
            all_same = false;
            break;
        }
    }
    EXPECT_FALSE(all_same);
}

// Test that same seed produces same sequence (determinism)
TEST_F(UniformFloatingPointDistributionTest_345, SameSeedProducesSameSequence_345) {
    Catch::uniform_floating_point_distribution<double> dist1(0.0, 1.0);
    Catch::uniform_floating_point_distribution<double> dist2(0.0, 1.0);
    std::mt19937 gen1(42);
    std::mt19937 gen2(42);

    for (int i = 0; i < 100; ++i) {
        double v1 = dist1(gen1);
        double v2 = dist2(gen2);
        EXPECT_DOUBLE_EQ(v1, v2);
    }
}

// Test with large range
TEST_F(UniformFloatingPointDistributionTest_345, LargeRangeDouble_345) {
    double a = -1e15;
    double b = 1e15;
    Catch::uniform_floating_point_distribution<double> dist(a, b);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), a);
    EXPECT_DOUBLE_EQ(dist.b(), b);

    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test adjacent floats range for float type
TEST_F(UniformFloatingPointDistributionTest_345, AdjacentFloatsRangeFloat_345) {
    float a = 1.0f;
    float b = std::nextafter(a, std::numeric_limits<float>::max());
    Catch::uniform_floating_point_distribution<float> dist(a, b);
    std::mt19937 gen(42);

    for (int i = 0; i < 100; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test adjacent floats range for double type
TEST_F(UniformFloatingPointDistributionTest_345, AdjacentFloatsRangeDouble_345) {
    double a = 1.0;
    double b = std::nextafter(a, std::numeric_limits<double>::max());
    Catch::uniform_floating_point_distribution<double> dist(a, b);
    std::mt19937 gen(42);

    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test with very small positive values near zero
TEST_F(UniformFloatingPointDistributionTest_345, SmallPositiveValuesNearZero_345) {
    double a = std::numeric_limits<double>::min();
    double b = 2.0 * std::numeric_limits<double>::min();
    Catch::uniform_floating_point_distribution<double> dist(a, b);
    std::mt19937 gen(42);

    EXPECT_DOUBLE_EQ(dist.a(), a);
    EXPECT_DOUBLE_EQ(dist.b(), b);

    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}
