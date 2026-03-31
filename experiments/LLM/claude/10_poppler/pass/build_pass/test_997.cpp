#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "UnicodeMap.h"

// Test fixture for UnicodeMap tests
class UnicodeMapTest_997 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test isUnicode returns true when constructed with unicodeOut = true
TEST_F(UnicodeMapTest_997, IsUnicodeReturnsTrueWhenUnicodeOutTrue_997) {
    // Construct with unicodeOut = true
    UnicodeMap map("UTF-8", true, 0);
    EXPECT_TRUE(map.isUnicode());
}

// Test isUnicode returns false when constructed with unicodeOut = false
TEST_F(UnicodeMapTest_997, IsUnicodeReturnsFalseWhenUnicodeOutFalse_997) {
    UnicodeMap map("Latin1", false, 0);
    EXPECT_FALSE(map.isUnicode());
}

// Test getEncodingName returns the correct encoding name
TEST_F(UnicodeMapTest_997, GetEncodingNameReturnsCorrectName_997) {
    UnicodeMap map("UTF-8", true, 0);
    EXPECT_EQ(map.getEncodingName(), "UTF-8");
}

// Test getEncodingName with a different encoding
TEST_F(UnicodeMapTest_997, GetEncodingNameReturnsDifferentName_997) {
    UnicodeMap map("ISO-8859-1", false, 0);
    EXPECT_EQ(map.getEncodingName(), "ISO-8859-1");
}

// Test match returns true for matching encoding name
TEST_F(UnicodeMapTest_997, MatchReturnsTrueForMatchingName_997) {
    UnicodeMap map("UTF-8", true, 0);
    EXPECT_TRUE(map.match("UTF-8"));
}

// Test match returns false for non-matching encoding name
TEST_F(UnicodeMapTest_997, MatchReturnsFalseForNonMatchingName_997) {
    UnicodeMap map("UTF-8", true, 0);
    EXPECT_FALSE(map.match("Latin1"));
}

// Test match with empty string
TEST_F(UnicodeMapTest_997, MatchReturnsFalseForEmptyString_997) {
    UnicodeMap map("UTF-8", true, 0);
    EXPECT_FALSE(map.match(""));
}

// Test move constructor preserves encoding name
TEST_F(UnicodeMapTest_997, MoveConstructorPreservesEncodingName_997) {
    UnicodeMap original("UTF-8", true, 0);
    UnicodeMap moved(std::move(original));
    EXPECT_EQ(moved.getEncodingName(), "UTF-8");
}

// Test move constructor preserves isUnicode
TEST_F(UnicodeMapTest_997, MoveConstructorPreservesIsUnicode_997) {
    UnicodeMap original("UTF-8", true, 0);
    UnicodeMap moved(std::move(original));
    EXPECT_TRUE(moved.isUnicode());
}

// Test move assignment operator
TEST_F(UnicodeMapTest_997, MoveAssignmentPreservesState_997) {
    UnicodeMap map1("UTF-8", true, 0);
    UnicodeMap map2("Latin1", false, 0);
    map2 = std::move(map1);
    EXPECT_EQ(map2.getEncodingName(), "UTF-8");
    EXPECT_TRUE(map2.isUnicode());
}

// Test swap functionality
TEST_F(UnicodeMapTest_997, SwapExchangesState_997) {
    UnicodeMap map1("UTF-8", true, 0);
    UnicodeMap map2("Latin1", false, 0);
    map1.swap(map2);
    EXPECT_EQ(map1.getEncodingName(), "Latin1");
    EXPECT_FALSE(map1.isUnicode());
    EXPECT_EQ(map2.getEncodingName(), "UTF-8");
    EXPECT_TRUE(map2.isUnicode());
}

// Test mapUnicode with a basic ASCII character and sufficient buffer
TEST_F(UnicodeMapTest_997, MapUnicodeBasicCharacter_997) {
    UnicodeMap map("Latin1", false, 0);
    char buf[8];
    int result = map.mapUnicode('A', buf, sizeof(buf));
    // Result should be >= 0; 0 means no mapping found, >0 means bytes written
    EXPECT_GE(result, 0);
}

// Test mapUnicode with zero buffer size
TEST_F(UnicodeMapTest_997, MapUnicodeZeroBufferSize_997) {
    UnicodeMap map("Latin1", false, 0);
    char buf[1];
    int result = map.mapUnicode('A', buf, 0);
    // With zero buffer size, should return 0 or handle gracefully
    EXPECT_GE(result, 0);
}

// Test getEncodingName with empty encoding name
TEST_F(UnicodeMapTest_997, GetEncodingNameEmpty_997) {
    UnicodeMap map("", false, 0);
    EXPECT_EQ(map.getEncodingName(), "");
}

// Test match with same empty encoding name
TEST_F(UnicodeMapTest_997, MatchEmptyEncodingName_997) {
    UnicodeMap map("", false, 0);
    EXPECT_TRUE(map.match(""));
}

// Test parse static method returns a valid unique_ptr or nullptr
TEST_F(UnicodeMapTest_997, ParseReturnsUniquePtr_997) {
    auto result = UnicodeMap::parse("Latin1");
    // parse may return nullptr if the encoding is not found in the config
    // We just verify it doesn't crash and returns a valid smart pointer state
    if (result) {
        EXPECT_FALSE(result->getEncodingName().empty());
    }
}

// Test parse with unknown encoding name
TEST_F(UnicodeMapTest_997, ParseUnknownEncodingReturnsNull_997) {
    auto result = UnicodeMap::parse("CompletelyFakeEncoding12345");
    // Unknown encodings should return nullptr
    EXPECT_EQ(result, nullptr);
}
