#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Declaration of the function under test
namespace Catch {
    bool isnan(double d);
}

TEST(CatchIsNanTest_636, RegularPositiveNumber_636) {
    EXPECT_FALSE(Catch::isnan(1.0));
}

TEST(CatchIsNanTest_636, RegularNegativeNumber_636) {
    EXPECT_FALSE(Catch::isnan(-1.0));
}

TEST(CatchIsNanTest_636, Zero_636) {
    EXPECT_FALSE(Catch::isnan(0.0));
}

TEST(CatchIsNanTest_636, NegativeZero_636) {
    EXPECT_FALSE(Catch::isnan(-0.0));
}

TEST(CatchIsNanTest_636, QuietNaN_636) {
    EXPECT_TRUE(Catch::isnan(std::numeric_limits<double>::quiet_NaN()));
}

TEST(CatchIsNanTest_636, SignalingNaN_636) {
    EXPECT_TRUE(Catch::isnan(std::numeric_limits<double>::signaling_NaN()));
}

TEST(CatchIsNanTest_636, PositiveInfinity_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::infinity()));
}

TEST(CatchIsNanTest_636, NegativeInfinity_636) {
    EXPECT_FALSE(Catch::isnan(-std::numeric_limits<double>::infinity()));
}

TEST(CatchIsNanTest_636, MaxDouble_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::max()));
}

TEST(CatchIsNanTest_636, MinDouble_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::min()));
}

TEST(CatchIsNanTest_636, LowestDouble_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::lowest()));
}

TEST(CatchIsNanTest_636, DenormMin_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::denorm_min()));
}

TEST(CatchIsNanTest_636, Epsilon_636) {
    EXPECT_FALSE(Catch::isnan(std::numeric_limits<double>::epsilon()));
}

TEST(CatchIsNanTest_636, NanFromArithmetic_636) {
    double result = 0.0 / 0.0;
    EXPECT_TRUE(Catch::isnan(result));
}

TEST(CatchIsNanTest_636, InfinityMinusInfinity_636) {
    double inf = std::numeric_limits<double>::infinity();
    double result = inf - inf;
    EXPECT_TRUE(Catch::isnan(result));
}

TEST(CatchIsNanTest_636, SmallPositiveValue_636) {
    EXPECT_FALSE(Catch::isnan(1e-308));
}

TEST(CatchIsNanTest_636, LargePositiveValue_636) {
    EXPECT_FALSE(Catch::isnan(1e+308));
}

TEST(CatchIsNanTest_636, NanGeneratedByStdNan_636) {
    EXPECT_TRUE(Catch::isnan(std::nan("")));
}
