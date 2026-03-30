#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxFont.h"
#include "./TestProjects/poppler/poppler/GfxFont.cc"

// Test Fixture for testing cmpWidthExcepFunctor
class GfxFontTest_1971 : public testing::Test {
protected:
    // Setup and TearDown methods can be added here if needed
    void SetUp() override {}
    void TearDown() override {}
};

// Test case for normal operation of cmpWidthExcepFunctor
TEST_F(GfxFontTest_1971, cmpWidthExcepFunctor_CompareValidWidthExcep_1971) {
    GfxFontCIDWidthExcep w1{CID(1), CID(10)};
    GfxFontCIDWidthExcep w2{CID(2), CID(15)};
    
    cmpWidthExcepFunctor cmp;
    
    // w1.first < w2.first so cmp(w1, w2) should return true
    EXPECT_TRUE(cmp(w1, w2));
    
    // w2.first < w1.first should return false
    EXPECT_FALSE(cmp(w2, w1));
}

// Test case for boundary conditions - same CID values
TEST_F(GfxFontTest_1971, cmpWidthExcepFunctor_CompareEqualWidthExcep_1971) {
    GfxFontCIDWidthExcep w1{CID(10), CID(20)};
    GfxFontCIDWidthExcep w2{CID(10), CID(25)};
    
    cmpWidthExcepFunctor cmp;
    
    // Same first CID, so cmp(w1, w2) should return false
    EXPECT_FALSE(cmp(w1, w2));
    // Same first CID, so cmp(w2, w1) should also return false
    EXPECT_FALSE(cmp(w2, w1));
}

// Test case for exceptional case when CID is invalid or out of range
TEST_F(GfxFontTest_1971, cmpWidthExcepFunctor_CompareInvalidCID_1971) {
    GfxFontCIDWidthExcep w1{CID(-1), CID(10)}; // invalid CID
    GfxFontCIDWidthExcep w2{CID(1), CID(10)};  // valid CID
    
    cmpWidthExcepFunctor cmp;
    
    // Invalid CID w1.first should be considered less than valid CID w2.first
    EXPECT_TRUE(cmp(w1, w2));
    EXPECT_FALSE(cmp(w2, w1));  // valid CID should not be less than invalid CID
}