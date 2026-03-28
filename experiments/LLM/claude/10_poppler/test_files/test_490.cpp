#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"

// Since GfxPattern has a protected/private constructor and we can't instantiate it directly,
// we need to work through available means. Based on the interface, GfxPattern is a base class
// with virtual methods, and parse() is the factory method. However, since we're treating this
// as a black box and the constructor takes (int typeA, int patternRefNumA), we can create
// a concrete subclass for testing purposes if needed.

// Helper subclass to access GfxPattern's constructor for testing
class TestableGfxPattern : public GfxPattern {
public:
    TestableGfxPattern(int typeA, int patternRefNumA) : GfxPattern(typeA, patternRefNumA) {}
    
    const std::unique_ptr<GfxPattern> copy() override {
        return std::make_unique<TestableGfxPattern>(getType(), getPatternRefNum());
    }
};

class GfxPatternTest_490 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getType returns the type passed to the constructor
TEST_F(GfxPatternTest_490, GetTypeReturnsCorrectType_490) {
    TestableGfxPattern pattern(1, 100);
    EXPECT_EQ(pattern.getType(), 1);
}

// Test that getType returns correct type for type 2 (shading pattern)
TEST_F(GfxPatternTest_490, GetTypeReturnsShadingPatternType_490) {
    TestableGfxPattern pattern(2, 200);
    EXPECT_EQ(pattern.getType(), 2);
}

// Test that getPatternRefNum returns the ref num passed to the constructor
TEST_F(GfxPatternTest_490, GetPatternRefNumReturnsCorrectRefNum_490) {
    TestableGfxPattern pattern(1, 42);
    EXPECT_EQ(pattern.getPatternRefNum(), 42);
}

// Test with type 0 (boundary/edge case)
TEST_F(GfxPatternTest_490, GetTypeReturnsZero_490) {
    TestableGfxPattern pattern(0, 0);
    EXPECT_EQ(pattern.getType(), 0);
}

// Test with negative type (edge case)
TEST_F(GfxPatternTest_490, GetTypeReturnsNegativeType_490) {
    TestableGfxPattern pattern(-1, 50);
    EXPECT_EQ(pattern.getType(), -1);
}

// Test with zero pattern ref num
TEST_F(GfxPatternTest_490, GetPatternRefNumReturnsZero_490) {
    TestableGfxPattern pattern(1, 0);
    EXPECT_EQ(pattern.getPatternRefNum(), 0);
}

// Test with negative pattern ref num (edge case)
TEST_F(GfxPatternTest_490, GetPatternRefNumReturnsNegative_490) {
    TestableGfxPattern pattern(1, -1);
    EXPECT_EQ(pattern.getPatternRefNum(), -1);
}

// Test that copy produces a pattern with the same type
TEST_F(GfxPatternTest_490, CopyPreservesType_490) {
    TestableGfxPattern pattern(1, 100);
    auto copied = pattern.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getType(), pattern.getType());
}

// Test that copy produces a pattern with the same pattern ref num
TEST_F(GfxPatternTest_490, CopyPreservesPatternRefNum_490) {
    TestableGfxPattern pattern(2, 55);
    auto copied = pattern.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getPatternRefNum(), pattern.getPatternRefNum());
}

// Test that copy returns a distinct object
TEST_F(GfxPatternTest_490, CopyReturnsDifferentPointer_490) {
    TestableGfxPattern pattern(1, 100);
    auto copied = pattern.copy();
    ASSERT_NE(copied, nullptr);
    EXPECT_NE(copied.get(), &pattern);
}

// Test with large type value
TEST_F(GfxPatternTest_490, GetTypeLargeValue_490) {
    TestableGfxPattern pattern(999999, 1);
    EXPECT_EQ(pattern.getType(), 999999);
}

// Test with large pattern ref num
TEST_F(GfxPatternTest_490, GetPatternRefNumLargeValue_490) {
    TestableGfxPattern pattern(1, 999999);
    EXPECT_EQ(pattern.getPatternRefNum(), 999999);
}

// Test parse with null object returns nullptr (if applicable)
TEST_F(GfxPatternTest_490, ParseWithNullObjectReturnsNull_490) {
    auto result = GfxPattern::parse(nullptr, nullptr, nullptr, nullptr, 0);
    EXPECT_EQ(result, nullptr);
}
