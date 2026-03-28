#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Test fixture for GfxPattern
class GfxPatternTest_491 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getPatternRefNum returns the correct pattern reference number
TEST_F(GfxPatternTest_491, GetPatternRefNum_ReturnsCorrectValue_491) {
    // We need to construct a GfxPattern with known values
    // Using the constructor GfxPattern(int typeA, int patternRefNumA)
    // Since GfxPattern has a virtual destructor and copy is deleted,
    // we test through the public interface

    int testType = 1;
    int testRefNum = 42;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), testRefNum);
}

// Test getPatternRefNum with zero reference number
TEST_F(GfxPatternTest_491, GetPatternRefNum_ZeroValue_491) {
    int testType = 1;
    int testRefNum = 0;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), 0);
}

// Test getPatternRefNum with negative reference number
TEST_F(GfxPatternTest_491, GetPatternRefNum_NegativeValue_491) {
    int testType = 2;
    int testRefNum = -1;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), -1);
}

// Test getPatternRefNum with large reference number
TEST_F(GfxPatternTest_491, GetPatternRefNum_LargeValue_491) {
    int testType = 1;
    int testRefNum = 999999;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), 999999);
}

// Test getType returns the correct type
TEST_F(GfxPatternTest_491, GetType_ReturnsCorrectValue_491) {
    int testType = 2;
    int testRefNum = 10;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getType(), testType);
}

// Test getType with type 1 (tiling pattern)
TEST_F(GfxPatternTest_491, GetType_TilingPattern_491) {
    int testType = 1;
    int testRefNum = 5;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getType(), 1);
}

// Test getType with type 2 (shading pattern)
TEST_F(GfxPatternTest_491, GetType_ShadingPattern_491) {
    int testType = 2;
    int testRefNum = 7;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getType(), 2);
}

// Test that multiple GfxPattern instances have independent state
TEST_F(GfxPatternTest_491, MultipleInstances_IndependentState_491) {
    GfxPattern pattern1(1, 100);
    GfxPattern pattern2(2, 200);
    
    EXPECT_EQ(pattern1.getPatternRefNum(), 100);
    EXPECT_EQ(pattern2.getPatternRefNum(), 200);
    EXPECT_EQ(pattern1.getType(), 1);
    EXPECT_EQ(pattern2.getType(), 2);
}

// Test getPatternRefNum with INT_MAX boundary
TEST_F(GfxPatternTest_491, GetPatternRefNum_IntMaxBoundary_491) {
    int testType = 1;
    int testRefNum = INT_MAX;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), INT_MAX);
}

// Test getPatternRefNum with INT_MIN boundary
TEST_F(GfxPatternTest_491, GetPatternRefNum_IntMinBoundary_491) {
    int testType = 1;
    int testRefNum = INT_MIN;
    GfxPattern pattern(testType, testRefNum);
    
    EXPECT_EQ(pattern.getPatternRefNum(), INT_MIN);
}

// Test that const correctness is maintained - getPatternRefNum is const
TEST_F(GfxPatternTest_491, GetPatternRefNum_ConstCorrectness_491) {
    const GfxPattern pattern(1, 55);
    
    EXPECT_EQ(pattern.getPatternRefNum(), 55);
}

// Test that const correctness is maintained - getType is const
TEST_F(GfxPatternTest_491, GetType_ConstCorrectness_491) {
    const GfxPattern pattern(2, 33);
    
    EXPECT_EQ(pattern.getType(), 2);
}
