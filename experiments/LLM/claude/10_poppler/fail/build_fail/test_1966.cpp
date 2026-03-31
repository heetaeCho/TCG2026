#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include the necessary headers
#include "BuiltinFont.h"

// We need to define a mock/stub for the GetWidthFunction type
// Based on the interface, f is a function that takes (const char*, size_t) and returns const BuiltinFontWidth*

// Define test fixture
class BuiltinFontTest_1966 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper: a BuiltinFontWidth lookup function that returns a known width for known glyph names
static BuiltinFontWidth knownWidth = { 500 };
static BuiltinFontWidth anotherWidth = { 750 };
static BuiltinFontWidth zeroWidth = { 0 };

static const BuiltinFontWidth *mockLookupFound(const char *name, unsigned int len) {
    if (len == 1 && name[0] == 'A') {
        return &knownWidth;
    }
    if (len == 5 && strncmp(name, "space", 5) == 0) {
        return &anotherWidth;
    }
    if (len == 4 && strncmp(name, "zero", 4) == 0) {
        return &zeroWidth;
    }
    return nullptr;
}

static const BuiltinFontWidth *mockLookupAlwaysNull(const char *name, unsigned int len) {
    (void)name;
    (void)len;
    return nullptr;
}

static const BuiltinFontWidth *mockLookupAlwaysFound(const char *name, unsigned int len) {
    (void)name;
    (void)len;
    static BuiltinFontWidth w = { 333 };
    return &w;
}

// Test: getWidth returns true and sets correct width for a known glyph name
TEST_F(BuiltinFontTest_1966, GetWidthReturnsTrueForKnownGlyph_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w = 0;
    bool result = font.getWidth("A", &w);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(w, 500);
}

// Test: getWidth returns false for an unknown glyph name
TEST_F(BuiltinFontTest_1966, GetWidthReturnsFalseForUnknownGlyph_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w = 9999;
    bool result = font.getWidth("unknown", &w);
    
    EXPECT_FALSE(result);
    // w should remain unchanged (not modified when returning false)
    EXPECT_EQ(w, 9999);
}

// Test: getWidth returns true and correct width for multi-character glyph name
TEST_F(BuiltinFontTest_1966, GetWidthReturnsTrueForMultiCharGlyphName_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w = 0;
    bool result = font.getWidth("space", &w);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(w, 750);
}

// Test: getWidth handles zero-width glyph correctly
TEST_F(BuiltinFontTest_1966, GetWidthReturnsZeroWidthGlyph_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w = 9999;
    bool result = font.getWidth("zero", &w);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(w, 0);
}

// Test: getWidth returns false for all queries when lookup always returns null
TEST_F(BuiltinFontTest_1966, GetWidthAlwaysFalseWhenLookupReturnsNull_1966) {
    BuiltinFont font;
    font.f = mockLookupAlwaysNull;
    
    unsigned short w = 1234;
    bool result = font.getWidth("anything", &w);
    
    EXPECT_FALSE(result);
    EXPECT_EQ(w, 1234);
}

// Test: getWidth returns true for all queries when lookup always returns a valid width
TEST_F(BuiltinFontTest_1966, GetWidthAlwaysTrueWhenLookupAlwaysFinds_1966) {
    BuiltinFont font;
    font.f = mockLookupAlwaysFound;
    
    unsigned short w = 0;
    bool result = font.getWidth("anyglyph", &w);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(w, 333);
}

// Test: getWidth with empty string
TEST_F(BuiltinFontTest_1966, GetWidthWithEmptyString_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w = 5555;
    bool result = font.getWidth("", &w);
    
    // Empty string is not a known glyph in our mock
    EXPECT_FALSE(result);
    EXPECT_EQ(w, 5555);
}

// Test: getWidth called multiple times returns consistent results
TEST_F(BuiltinFontTest_1966, GetWidthMultipleCallsConsistent_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w1 = 0, w2 = 0;
    bool r1 = font.getWidth("A", &w1);
    bool r2 = font.getWidth("A", &w2);
    
    EXPECT_TRUE(r1);
    EXPECT_TRUE(r2);
    EXPECT_EQ(w1, w2);
    EXPECT_EQ(w1, 500);
}

// Test: getWidth with different glyph names returns different widths
TEST_F(BuiltinFontTest_1966, GetWidthDifferentGlyphsDifferentWidths_1966) {
    BuiltinFont font;
    font.f = mockLookupFound;
    
    unsigned short w1 = 0, w2 = 0;
    bool r1 = font.getWidth("A", &w1);
    bool r2 = font.getWidth("space", &w2);
    
    EXPECT_TRUE(r1);
    EXPECT_TRUE(r2);
    EXPECT_NE(w1, w2);
    EXPECT_EQ(w1, 500);
    EXPECT_EQ(w2, 750);
}

// Test: getWidth does not modify output parameter when glyph is not found
TEST_F(BuiltinFontTest_1966, GetWidthDoesNotModifyOutputOnFailure_1966) {
    BuiltinFont font;
    font.f = mockLookupAlwaysNull;
    
    unsigned short w = 42;
    font.getWidth("notfound", &w);
    
    EXPECT_EQ(w, 42);
}
