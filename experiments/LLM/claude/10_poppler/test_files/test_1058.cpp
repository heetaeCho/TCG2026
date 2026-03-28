#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "OutputDev.h"

// Test fixture for OutputDev
class OutputDevTest_1058 : public ::testing::Test {
protected:
    OutputDev dev;
};

// Test that useShadedFills returns false for type 0
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType0_1058) {
    EXPECT_FALSE(dev.useShadedFills(0));
}

// Test that useShadedFills returns false for type 1
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType1_1058) {
    EXPECT_FALSE(dev.useShadedFills(1));
}

// Test that useShadedFills returns false for type 2
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType2_1058) {
    EXPECT_FALSE(dev.useShadedFills(2));
}

// Test that useShadedFills returns false for type 3
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType3_1058) {
    EXPECT_FALSE(dev.useShadedFills(3));
}

// Test that useShadedFills returns false for type 4
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType4_1058) {
    EXPECT_FALSE(dev.useShadedFills(4));
}

// Test that useShadedFills returns false for type 5
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType5_1058) {
    EXPECT_FALSE(dev.useShadedFills(5));
}

// Test that useShadedFills returns false for type 6
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType6_1058) {
    EXPECT_FALSE(dev.useShadedFills(6));
}

// Test that useShadedFills returns false for type 7
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForType7_1058) {
    EXPECT_FALSE(dev.useShadedFills(7));
}

// Boundary: negative type value
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForNegativeType_1058) {
    EXPECT_FALSE(dev.useShadedFills(-1));
}

// Boundary: large type value
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForLargeType_1058) {
    EXPECT_FALSE(dev.useShadedFills(100));
}

// Boundary: INT_MAX
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForIntMax_1058) {
    EXPECT_FALSE(dev.useShadedFills(std::numeric_limits<int>::max()));
}

// Boundary: INT_MIN
TEST_F(OutputDevTest_1058, UseShadedFillsReturnsFalseForIntMin_1058) {
    EXPECT_FALSE(dev.useShadedFills(std::numeric_limits<int>::min()));
}

// Test that a derived class can override useShadedFills
class DerivedOutputDev_1058 : public OutputDev {
public:
    bool useShadedFills(int type) override {
        if (type >= 1 && type <= 7) {
            return true;
        }
        return false;
    }
};

TEST_F(OutputDevTest_1058, DerivedClassCanOverrideUseShadedFills_1058) {
    DerivedOutputDev_1058 derived;
    EXPECT_TRUE(derived.useShadedFills(1));
    EXPECT_TRUE(derived.useShadedFills(7));
    EXPECT_FALSE(derived.useShadedFills(0));
    EXPECT_FALSE(derived.useShadedFills(-1));
}

// Test polymorphic behavior via base pointer
TEST_F(OutputDevTest_1058, PolymorphicBehaviorViaBasePointer_1058) {
    DerivedOutputDev_1058 derived;
    OutputDev* basePtr = &derived;
    EXPECT_TRUE(basePtr->useShadedFills(3));
    EXPECT_FALSE(basePtr->useShadedFills(0));
}

// Test that base class default returns false consistently across multiple calls
TEST_F(OutputDevTest_1058, ConsistentReturnValueAcrossMultipleCalls_1058) {
    for (int i = -10; i <= 10; ++i) {
        EXPECT_FALSE(dev.useShadedFills(i)) << "Failed for type: " << i;
    }
}
