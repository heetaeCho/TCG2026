#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <random>

#include "catch2/internal/catch_uniform_floating_point_distribution.hpp"

// Test fixture for uniform_floating_point_distribution with float
class UniformFloatingPointDistributionFloatTest_344 : public ::testing::Test {
protected:
    using DistFloat = Catch::uniform_floating_point_distribution<float>;
};

// Test fixture for uniform_floating_point_distribution with double
class UniformFloatingPointDistributionDoubleTest_344 : public ::testing::Test {
protected:
    using DistDouble = Catch::uniform_floating_point_distribution<double>;
};

// ==================== Constructor and accessor tests ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, ConstructorSetsAAndB_344) {
    DistDouble dist(1.0, 10.0);
    EXPECT_DOUBLE_EQ(dist.a(), 1.0);
    EXPECT_DOUBLE_EQ(dist.b(), 10.0);
}

TEST_F(UniformFloatingPointDistributionFloatTest_344, ConstructorSetsAAndBFloat_344) {
    DistFloat dist(0.0f, 1.0f);
    EXPECT_FLOAT_EQ(dist.a(), 0.0f);
    EXPECT_FLOAT_EQ(dist.b(), 1.0f);
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, AReturnsLowerBound_344) {
    DistDouble dist(-5.0, 5.0);
    EXPECT_DOUBLE_EQ(dist.a(), -5.0);
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, BReturnsUpperBound_344) {
    DistDouble dist(-5.0, 5.0);
    EXPECT_DOUBLE_EQ(dist.b(), 5.0);
}

// ==================== Normal operation: generated values in range ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, GeneratedValuesInRange_344) {
    DistDouble dist(0.0, 1.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0) << "Value " << val << " is below lower bound";
        EXPECT_LE(val, 1.0) << "Value " << val << " is above upper bound";
    }
}

TEST_F(UniformFloatingPointDistributionFloatTest_344, GeneratedValuesInRangeFloat_344) {
    DistFloat dist(0.0f, 1.0f);
    std::minstd_rand gen(123);
    for (int i = 0; i < 1000; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, 0.0f) << "Value " << val << " is below lower bound";
        EXPECT_LE(val, 1.0f) << "Value " << val << " is above upper bound";
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, NegativeRange_344) {
    DistDouble dist(-10.0, -1.0);
    std::minstd_rand gen(99);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -10.0);
        EXPECT_LE(val, -1.0);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, RangeSpanningZero_344) {
    DistDouble dist(-5.0, 5.0);
    std::minstd_rand gen(77);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -5.0);
        EXPECT_LE(val, 5.0);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, LargeRange_344) {
    DistDouble dist(-1e10, 1e10);
    std::minstd_rand gen(55);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -1e10);
        EXPECT_LE(val, 1e10);
    }
}

// ==================== Boundary conditions ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, ZeroToZeroRange_344) {
    DistDouble dist(0.0, 0.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, SameValueRange_344) {
    DistDouble dist(3.14, 3.14);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_DOUBLE_EQ(val, 3.14);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, VerySmallRange_344) {
    double a = 1.0;
    double b = std::nextafter(1.0, 2.0);
    DistDouble dist(a, b);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(UniformFloatingPointDistributionFloatTest_344, VerySmallRangeFloat_344) {
    float a = 1.0f;
    float b = std::nextafter(1.0f, 2.0f);
    DistFloat dist(a, b);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        float val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, ZeroToSmallPositive_344) {
    DistDouble dist(0.0, 1e-300);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 1e-300);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, NegativeSmallToZero_344) {
    DistDouble dist(-1e-300, 0.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -1e-300);
        EXPECT_LE(val, 0.0);
    }
}

// ==================== Different generators ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, WorksWithMt19937_344) {
    DistDouble dist(0.0, 100.0);
    std::mt19937 gen(12345);
    for (int i = 0; i < 500; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.0);
        EXPECT_LE(val, 100.0);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, WorksWithMt19937_64_344) {
    DistDouble dist(-50.0, 50.0);
    std::mt19937_64 gen(54321);
    for (int i = 0; i < 500; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -50.0);
        EXPECT_LE(val, 50.0);
    }
}

// ==================== Variety: not all same value for non-degenerate ranges ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, ProducesVariety_344) {
    DistDouble dist(0.0, 1.0);
    std::minstd_rand gen(42);
    double first = dist(gen);
    bool found_different = false;
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        if (val != first) {
            found_different = true;
            break;
        }
    }
    EXPECT_TRUE(found_different) << "Distribution should produce varied values over a non-degenerate range";
}

TEST_F(UniformFloatingPointDistributionFloatTest_344, ProducesVarietyFloat_344) {
    DistFloat dist(0.0f, 1.0f);
    std::minstd_rand gen(42);
    float first = dist(gen);
    bool found_different = false;
    for (int i = 0; i < 1000; ++i) {
        float val = dist(gen);
        if (val != first) {
            found_different = true;
            break;
        }
    }
    EXPECT_TRUE(found_different) << "Distribution should produce varied values over a non-degenerate range";
}

// ==================== Accessors consistency ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, AccessorsAreConsistent_344) {
    DistDouble dist(2.5, 7.5);
    // Call multiple times to ensure they're consistent
    EXPECT_DOUBLE_EQ(dist.a(), 2.5);
    EXPECT_DOUBLE_EQ(dist.a(), 2.5);
    EXPECT_DOUBLE_EQ(dist.b(), 7.5);
    EXPECT_DOUBLE_EQ(dist.b(), 7.5);
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, AccessorsUnchangedAfterGeneration_344) {
    DistDouble dist(1.0, 2.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        dist(gen);
    }
    EXPECT_DOUBLE_EQ(dist.a(), 1.0);
    EXPECT_DOUBLE_EQ(dist.b(), 2.0);
}

// ==================== Negative zero ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, NegativeZeroToPositiveZero_344) {
    DistDouble dist(-0.0, 0.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -0.0);
        EXPECT_LE(val, 0.0);
    }
}

// ==================== Subnormal range ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, SubnormalRange_344) {
    double a = std::numeric_limits<double>::denorm_min();
    double b = std::numeric_limits<double>::min(); // smallest normal
    DistDouble dist(a, b);
    std::minstd_rand gen(42);
    for (int i = 0; i < 100; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, a);
        EXPECT_LE(val, b);
    }
}

// ==================== Asymmetric magnitude (a_has_leq_magnitude path) ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, AsymmetricMagnitudeASmaller_344) {
    // |a| < |b|
    DistDouble dist(0.1, 100.0);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, 0.1);
        EXPECT_LE(val, 100.0);
    }
}

TEST_F(UniformFloatingPointDistributionDoubleTest_344, AsymmetricMagnitudeBSmaller_344) {
    // |a| > |b|
    DistDouble dist(-100.0, -0.1);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_GE(val, -100.0);
        EXPECT_LE(val, -0.1);
    }
}

// ==================== Float type: generated values are finite ====================

TEST_F(UniformFloatingPointDistributionDoubleTest_344, GeneratedValuesAreFinite_344) {
    DistDouble dist(-1e100, 1e100);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        double val = dist(gen);
        EXPECT_TRUE(std::isfinite(val)) << "Generated value should be finite, got: " << val;
    }
}

TEST_F(UniformFloatingPointDistributionFloatTest_344, GeneratedValuesAreFiniteFloat_344) {
    DistFloat dist(-1e30f, 1e30f);
    std::minstd_rand gen(42);
    for (int i = 0; i < 1000; ++i) {
        float val = dist(gen);
        EXPECT_TRUE(std::isfinite(val)) << "Generated value should be finite, got: " << val;
    }
}
