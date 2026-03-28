#include <gtest/gtest.h>
#include "yaml-cpp/emittermanip.h"

// Test normal operation with a typical precision value
TEST(PrecisionTest_22, NormalValue_22) {
    YAML::_Precision p = YAML::Precision(5);
    EXPECT_EQ(p.floatPrecision, 5);
    EXPECT_EQ(p.doublePrecision, 5);
}

// Test with zero precision
TEST(PrecisionTest_22, ZeroPrecision_22) {
    YAML::_Precision p = YAML::Precision(0);
    EXPECT_EQ(p.floatPrecision, 0);
    EXPECT_EQ(p.doublePrecision, 0);
}

// Test with precision of 1
TEST(PrecisionTest_22, PrecisionOne_22) {
    YAML::_Precision p = YAML::Precision(1);
    EXPECT_EQ(p.floatPrecision, 1);
    EXPECT_EQ(p.doublePrecision, 1);
}

// Test with a large precision value
TEST(PrecisionTest_22, LargePrecision_22) {
    YAML::_Precision p = YAML::Precision(20);
    EXPECT_EQ(p.floatPrecision, 20);
    EXPECT_EQ(p.doublePrecision, 20);
}

// Test that float and double precision are both set to the same value
TEST(PrecisionTest_22, FloatAndDoubleAreEqual_22) {
    for (int i = 0; i <= 15; ++i) {
        YAML::_Precision p = YAML::Precision(i);
        EXPECT_EQ(p.floatPrecision, p.doublePrecision)
            << "Float and double precision should be equal for input " << i;
    }
}

// Test with negative precision value (boundary/edge case)
TEST(PrecisionTest_22, NegativePrecision_22) {
    YAML::_Precision p = YAML::Precision(-1);
    EXPECT_EQ(p.floatPrecision, -1);
    EXPECT_EQ(p.doublePrecision, -1);
}

// Test with max int-like precision
TEST(PrecisionTest_22, MaxReasonablePrecision_22) {
    YAML::_Precision p = YAML::Precision(std::numeric_limits<int>::max());
    EXPECT_EQ(p.floatPrecision, std::numeric_limits<int>::max());
    EXPECT_EQ(p.doublePrecision, std::numeric_limits<int>::max());
}

// Test typical float precision (6-7 digits)
TEST(PrecisionTest_22, TypicalFloatPrecision_22) {
    YAML::_Precision p = YAML::Precision(6);
    EXPECT_EQ(p.floatPrecision, 6);
    EXPECT_EQ(p.doublePrecision, 6);
}

// Test typical double precision (15-17 digits)
TEST(PrecisionTest_22, TypicalDoublePrecision_22) {
    YAML::_Precision p = YAML::Precision(15);
    EXPECT_EQ(p.floatPrecision, 15);
    EXPECT_EQ(p.doublePrecision, 15);
}

// Test multiple calls return independent objects
TEST(PrecisionTest_22, IndependentObjects_22) {
    YAML::_Precision p1 = YAML::Precision(3);
    YAML::_Precision p2 = YAML::Precision(7);
    EXPECT_EQ(p1.floatPrecision, 3);
    EXPECT_EQ(p1.doublePrecision, 3);
    EXPECT_EQ(p2.floatPrecision, 7);
    EXPECT_EQ(p2.doublePrecision, 7);
}
