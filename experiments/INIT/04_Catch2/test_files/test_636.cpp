// File: tests/catch_polyfills_isnan_test.cpp

#include <gtest/gtest.h>
#include <limits>
#include <cmath>

// The function under test:
// namespace Catch { bool isnan(double d); }
namespace Catch { bool isnan(double d); }

// ---------- Normal operation: NaN values ----------
TEST(CatchIsNanTest_636, ReturnsTrueForQuietNaN_636) {
    const double qnan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(Catch::isnan(qnan));
}

TEST(CatchIsNanTest_636, ReturnsTrueForSignalingNaNIfAvailable_636) {
#if defined(__cpp_lib_numeric_limits)
    if (!std::numeric_limits<double>::has_signaling_NaN) {
        GTEST_SKIP() << "This platform does not provide signaling NaN for double.";
    }
#endif
    const double snan = std::numeric_limits<double>::signaling_NaN();
    EXPECT_TRUE(Catch::isnan(snan));
}

// ---------- Boundary conditions: infinities, zeros, extremes ----------
TEST(CatchIsNanTest_636, ReturnsFalseForPositiveInfinity_636) {
    const double pos_inf = std::numeric_limits<double>::infinity();
    EXPECT_FALSE(Catch::isnan(pos_inf));
}

TEST(CatchIsNanTest_636, ReturnsFalseForNegativeInfinity_636) {
    const double neg_inf = -std::numeric_limits<double>::infinity();
    EXPECT_FALSE(Catch::isnan(neg_inf));
}

TEST(CatchIsNanTest_636, ReturnsFalseForPositiveZero_636) {
    const double pos_zero = 0.0;
    EXPECT_FALSE(Catch::isnan(pos_zero));
}

TEST(CatchIsNanTest_636, ReturnsFalseForNegativeZero_636) {
    const double neg_zero = -0.0;
    EXPECT_FALSE(Catch::isnan(neg_zero));
}

TEST(CatchIsNanTest_636, ReturnsFalseForMaxFinite_636) {
    const double max_finite = std::numeric_limits<double>::max();
    EXPECT_FALSE(Catch::isnan(max_finite));
}

TEST(CatchIsNanTest_636, ReturnsFalseForMinPositiveNormal_636) {
    const double min_normal = std::numeric_limits<double>::min(); // smallest positive normal
    EXPECT_FALSE(Catch::isnan(min_normal));
}

TEST(CatchIsNanTest_636, ReturnsFalseForSubnormalIfSupported_636) {
    // Some platforms may not support subnormals (denormals)
#if defined(__cpp_lib_numeric_limits)
    if (std::numeric_limits<double>::has_denorm == std::denorm_absent) {
        GTEST_SKIP() << "Subnormals are not supported on this platform.";
    }
#endif
    const double subnormal = std::numeric_limits<double>::denorm_min();
    EXPECT_FALSE(Catch::isnan(subnormal));
}

// ---------- Typical finite numbers ----------
TEST(CatchIsNanTest_636, ReturnsFalseForTypicalFiniteValues_636) {
    EXPECT_FALSE(Catch::isnan(1.0));
    EXPECT_FALSE(Catch::isnan(-123.456));
    EXPECT_FALSE(Catch::isnan(1e-12));
    EXPECT_FALSE(Catch::isnan(1e12));
}
