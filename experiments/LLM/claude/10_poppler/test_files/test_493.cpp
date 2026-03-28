#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxState.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "PDFDoc.h"

class GfxTilingPatternTest_493 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parse returns nullptr for an invalid/empty object
TEST_F(GfxTilingPatternTest_493, ParseInvalidObjectReturnsNull_493) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a non-stream object
TEST_F(GfxTilingPatternTest_493, ParseNonStreamObjectReturnsNull_493) {
    Object obj(42);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse returns nullptr for a null object
TEST_F(GfxTilingPatternTest_493, ParseNullTypeObjectReturnsNull_493) {
    Object obj(objNull);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test getTilingType accessor - since constructor is private, we test through parse
// If parse fails, we can only test null returns. But let's also test copy if we get a valid pattern.

// Test that parse with a bool object returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseBoolObjectReturnsNull_493) {
    Object obj(true);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a string object returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseStringObjectReturnsNull_493) {
    Object obj(new GooString("test"));
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a real number object returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseRealObjectReturnsNull_493) {
    Object obj(3.14);
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test that parse with a name object returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseNameObjectReturnsNull_493) {
    Object obj(objName, "TestName");
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test parse with negative pattern ref number and invalid object
TEST_F(GfxTilingPatternTest_493, ParseWithNegativeRefNumInvalidObject_493) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, -1);
    EXPECT_EQ(pattern, nullptr);
}

// Test parse with large pattern ref number and invalid object
TEST_F(GfxTilingPatternTest_493, ParseWithLargeRefNumInvalidObject_493) {
    Object obj;
    auto pattern = GfxTilingPattern::parse(&obj, 999999);
    EXPECT_EQ(pattern, nullptr);
}

// Test parse with array object returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseArrayObjectReturnsNull_493) {
    Object obj(new Array(nullptr));
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}

// Test parse with dict object (not stream) returns nullptr
TEST_F(GfxTilingPatternTest_493, ParseDictObjectReturnsNull_493) {
    Object obj(new Dict(nullptr));
    auto pattern = GfxTilingPattern::parse(&obj, 0);
    EXPECT_EQ(pattern, nullptr);
}
