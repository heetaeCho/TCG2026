#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <random>
#include <set>
#include <vector>

// Include the header under test
#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

class UniformFloatingPointDistributionTest_343 : public ::testing::Test {
protected:
    std::mt19937 gen{42}; // Fixed seed for reproducibility
};

// Test that a() returns the lower bound
TEST_F(UniformFloatingPointDistributionTest_343, ReturnsCorrectLowerBound_343) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(dist.a(), 1.0f);
}

// Test that b() returns the upper bound
TEST_F(UniformFloatingPointDistributionTest_343, ReturnsCorrectUpperBound_343) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(dist.b(), 2.0f);
}

// Test that a() and b() work for double
TEST_F(UniformFloatingPointDistributionTest_343, ReturnsCorrectBoundsDouble_343) {
    Catch::uniform_floating_point_distribution<double> dist(3.14, 6.28);
    EXPECT_DOUBLE_EQ(dist.a(), 3.14);
    EXPECT_DOUBLE_EQ(dist.b(), 6.28);
}

// Test that generated values are within [a, b]
TEST_F(UniformFloatingPointDistributionTest_343, GeneratedValuesWithinRange_343) {
    Catch::uniform_floating_point_distribution<float> dist(1.0f, 2.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, 1.0f) << "Value " << val << " is less than lower bound";
        EXPECT_LE(val, 2.0f) << "Value " << val << " is greater than upper bound";
    }
}

// Test with double precision
TEST_F(UniformFloatingPointDistributionTest_343, GeneratedValuesWithinRangeDouble_343) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0) << "Value " << val << " is less than lower bound";
        EXPECT_LE(val, 1.0) << "Value " << val << " is greater than upper bound";
    }
}

// Test with negative range
TEST_F(UniformFloatingPointDistributionTest_343, NegativeRange_343) {
    Catch::uniform_floating_point_distribution<float> dist(-5.0f, -1.0f);
    EXPECT_FLOAT_EQ(dist.a(), -5.0f);
    EXPECT_FLOAT_EQ(dist.b(), -1.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, -5.0f);
        EXPECT_LE(val, -1.0f);
    }
}

// Test with range spanning zero
TEST_F(UniformFloatingPointDistributionTest_343, RangeSpanningZero_343) {
    Catch::uniform_floating_point_distribution<float> dist(-1.0f, 1.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, -1.0f);
        EXPECT_LE(val, 1.0f);
    }
}

// Test with very small range
TEST_F(UniformFloatingPointDistributionTest_343, VerySmallRange_343) {
    float a = 1.0f;
    float b = std::nextafter(a, std::numeric_limits<float>::max());
    Catch::uniform_floating_point_distribution<float> dist(a, b);
    for (int i = 0; i < 100; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// Test that distribution produces varied results
TEST_F(UniformFloatingPointDistributionTest_343, ProducesVariedResults_343) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 100.0);
    std::set<double> values;
    for (int i = 0; i < 1000; ++i) {
        values.insert(dist(gen));
    }
    // We expect many distinct values from a continuous distribution
    EXPECT_GT(values.size(), 100u);
}

// Test with range where a has smaller magnitude than b
TEST_F(UniformFloatingPointDistributionTest_343, AHasLessOrEqualMagnitude_343) {
    Catch::uniform_floating_point_distribution<float> dist(0.5f, 10.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, 0.5f);
        EXPECT_LE(val, 10.0f);
    }
}

// Test with range where a has greater magnitude than b
TEST_F(UniformFloatingPointDistributionTest_343, AHasGreaterMagnitude_343) {
    Catch::uniform_floating_point_distribution<float> dist(-10.0f, 0.5f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, -10.0f);
        EXPECT_LE(val, 0.5f);
    }
}

// Test with zero as lower bound
TEST_F(UniformFloatingPointDistributionTest_343, ZeroLowerBound_343) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test with zero as upper bound
TEST_F(UniformFloatingPointDistributionTest_343, ZeroUpperBound_343) {
    Catch::uniform_floating_point_distribution<double> dist(-1.0, 0.0);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -1.0);
        EXPECT_LE(val, 0.0);
    }
}

// Test that both endpoints can be reached (or values very close to them)
TEST_F(UniformFloatingPointDistributionTest_343, EndpointsCanBeReached_343) {
    Catch::uniform_floating_point_distribution<float> dist(0.0f, 1.0f);
    float min_val = 1.0f;
    float max_val = 0.0f;
    for (int i = 0; i < 100000; ++i) {
        float val = dist(gen);
        min_val = std::min(min_val, val);
        max_val = std::max(max_val, val);
    }
    // The values should get very close to the endpoints
    EXPECT_LE(min_val, 0.01f);
    EXPECT_GE(max_val, 0.99f);
}

// Test large range
TEST_F(UniformFloatingPointDistributionTest_343, LargeRange_343) {
    Catch::uniform_floating_point_distribution<double> dist(-1e10, 1e10);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -1e10);
        EXPECT_LE(val, 1e10);
    }
}

// Test with different generators (e.g., mt19937_64)
TEST_F(UniformFloatingPointDistributionTest_343, WorksWithDifferentGenerators_343) {
    std::mt19937_64 gen64{123};
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen64);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1.0);
    }
}

// Test that same seed produces same sequence
TEST_F(UniformFloatingPointDistributionTest_343, DeterministicWithSameSeed_343) {
    std::mt19937 gen1{99};
    std::mt19937 gen2{99};
    Catch::uniform_floating_point_distribution<float> dist1(0.0f, 1.0f);
    Catch::uniform_floating_point_distribution<float> dist2(0.0f, 1.0f);
    for (int i = 0; i < 100; ++i) {
        EXPECT_FLOAT_EQ(dist1(gen1), dist2(gen2));
    }
}

// Test with equal magnitude endpoints
TEST_F(UniformFloatingPointDistributionTest_343, EqualMagnitudeEndpoints_343) {
    Catch::uniform_floating_point_distribution<float> dist(-5.0f, 5.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, -5.0f);
        EXPECT_LE(val, 5.0f);
    }
}

// Test with very small positive numbers
TEST_F(UniformFloatingPointDistributionTest_343, SmallPositiveNumbers_343) {
    Catch::uniform_floating_point_distribution<double> dist(1e-300, 1e-299);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 1e-300);
        EXPECT_LE(val, 1e-299);
    }
}

// Test result type matches template parameter for float
TEST_F(UniformFloatingPointDistributionTest_343, ResultTypeIsFloat_343) {
    Catch::uniform_floating_point_distribution<float> dist(0.0f, 1.0f);
    auto val = dist(gen);
    bool is_float = std::is_same<decltype(val), float>::value;
    EXPECT_TRUE(is_float);
}

// Test result type matches template parameter for double
TEST_F(UniformFloatingPointDistributionTest_343, ResultTypeIsDouble_343) {
    Catch::uniform_floating_point_distribution<double> dist(0.0, 1.0);
    auto val = dist(gen);
    bool is_double = std::is_same<decltype(val), double>::value;
    EXPECT_TRUE(is_double);
}

// Test that generated values are not NaN
TEST_F(UniformFloatingPointDistributionTest_343, NoNaNValues_343) {
    Catch::uniform_floating_point_distribution<float> dist(-100.0f, 100.0f);
    for (int i = 0; i < 10000; ++i) {
        float val = dist(gen);
        EXPECT_FALSE(std::isnan(val));
    }
}

// Test that generated values are finite
TEST_F(UniformFloatingPointDistributionTest_343, FiniteValues_343) {
    Catch::uniform_floating_point_distribution<double> dist(-1e300, 1e300);
    for (int i = 0; i < 10000; ++i) {
        double val = dist(gen);
        EXPECT_TRUE(std::isfinite(val));
    }
}
