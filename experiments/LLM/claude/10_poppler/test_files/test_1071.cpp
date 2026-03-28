#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test the default implementation of OutputDev
class OutputDevTest_1071 : public ::testing::Test {
protected:
    OutputDev dev;
};

// Test that the default radialShadedFill returns false with nullptr arguments
TEST_F(OutputDevTest_1071, RadialShadedFillReturnsFalseWithNullArgs_1071) {
    bool result = dev.radialShadedFill(nullptr, nullptr, 0.0, 1.0);
    EXPECT_FALSE(result);
}

// Test that the default radialShadedFill returns false with various sMin/sMax values
TEST_F(OutputDevTest_1071, RadialShadedFillReturnsFalseWithVariousMinMax_1071) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, -1.0, 1.0));
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.0, 0.0));
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 1.0, -1.0));
}

// Test boundary conditions with extreme double values
TEST_F(OutputDevTest_1071, RadialShadedFillReturnsFalseWithExtremeValues_1071) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 
        std::numeric_limits<double>::min(), std::numeric_limits<double>::max()));
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 
        -std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 
        std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity()));
}

// Test with zero range (sMin == sMax)
TEST_F(OutputDevTest_1071, RadialShadedFillReturnsFalseWithZeroRange_1071) {
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 0.5, 0.5));
}

// Test with NaN values
TEST_F(OutputDevTest_1071, RadialShadedFillReturnsFalseWithNaN_1071) {
    double nan_val = std::numeric_limits<double>::quiet_NaN();
    EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, nan_val, nan_val));
}

// Test that a derived class can override the behavior
class MockOutputDev : public OutputDev {
public:
    MOCK_METHOD(bool, radialShadedFill, (GfxState*, GfxRadialShading*, double, double), (override));
};

TEST_F(OutputDevTest_1071, DerivedClassCanOverrideRadialShadedFill_1071) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, radialShadedFill(nullptr, nullptr, 0.0, 1.0))
        .WillOnce(::testing::Return(true));
    
    bool result = mockDev.radialShadedFill(nullptr, nullptr, 0.0, 1.0);
    EXPECT_TRUE(result);
}

// Test that derived class override returning false also works
TEST_F(OutputDevTest_1071, DerivedClassCanReturnFalse_1071) {
    MockOutputDev mockDev;
    EXPECT_CALL(mockDev, radialShadedFill(nullptr, nullptr, 0.0, 1.0))
        .WillOnce(::testing::Return(false));
    
    bool result = mockDev.radialShadedFill(nullptr, nullptr, 0.0, 1.0);
    EXPECT_FALSE(result);
}

// Test multiple calls to the default implementation all return false
TEST_F(OutputDevTest_1071, RadialShadedFillConsistentlyReturnsFalse_1071) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(dev.radialShadedFill(nullptr, nullptr, 
            static_cast<double>(i), static_cast<double>(i + 1)));
    }
}
