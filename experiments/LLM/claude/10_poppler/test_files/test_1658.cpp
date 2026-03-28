#include <gtest/gtest.h>
#include "PreScanOutputDev.h"

class PreScanOutputDevTest_1658 : public ::testing::Test {
protected:
    PreScanOutputDev dev;
};

// Test that useShadedFills returns true for type 0
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForTypeZero_1658) {
    EXPECT_TRUE(dev.useShadedFills(0));
}

// Test that useShadedFills returns true for type 1
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType1_1658) {
    EXPECT_TRUE(dev.useShadedFills(1));
}

// Test that useShadedFills returns true for type 2
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType2_1658) {
    EXPECT_TRUE(dev.useShadedFills(2));
}

// Test that useShadedFills returns true for type 3
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType3_1658) {
    EXPECT_TRUE(dev.useShadedFills(3));
}

// Test that useShadedFills returns true for type 4
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType4_1658) {
    EXPECT_TRUE(dev.useShadedFills(4));
}

// Test that useShadedFills returns true for type 5
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType5_1658) {
    EXPECT_TRUE(dev.useShadedFills(5));
}

// Test that useShadedFills returns true for type 6
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType6_1658) {
    EXPECT_TRUE(dev.useShadedFills(6));
}

// Test that useShadedFills returns true for type 7
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForType7_1658) {
    EXPECT_TRUE(dev.useShadedFills(7));
}

// Boundary: negative type value
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForNegativeType_1658) {
    EXPECT_TRUE(dev.useShadedFills(-1));
}

// Boundary: large negative type value
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForLargeNegativeType_1658) {
    EXPECT_TRUE(dev.useShadedFills(-1000));
}

// Boundary: large positive type value
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForLargePositiveType_1658) {
    EXPECT_TRUE(dev.useShadedFills(1000));
}

// Boundary: INT_MAX
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForIntMax_1658) {
    EXPECT_TRUE(dev.useShadedFills(std::numeric_limits<int>::max()));
}

// Boundary: INT_MIN
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsReturnsTrueForIntMin_1658) {
    EXPECT_TRUE(dev.useShadedFills(std::numeric_limits<int>::min()));
}

// Test consistency: calling multiple times returns same result
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsConsistentAcrossMultipleCalls_1658) {
    EXPECT_TRUE(dev.useShadedFills(1));
    EXPECT_TRUE(dev.useShadedFills(1));
    EXPECT_TRUE(dev.useShadedFills(2));
    EXPECT_TRUE(dev.useShadedFills(0));
}

// Test that the parameter value does not affect the return value
TEST_F(PreScanOutputDevTest_1658, UseShadedFillsAlwaysTrueRegardlessOfType_1658) {
    for (int i = -10; i <= 10; ++i) {
        EXPECT_TRUE(dev.useShadedFills(i)) << "Failed for type=" << i;
    }
}
