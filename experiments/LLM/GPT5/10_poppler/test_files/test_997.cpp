#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "UnicodeMap.h"

// Test suite for the UnicodeMap class.
class UnicodeMapTest : public ::testing::Test {
protected:
    // Set up any common test initialization here.
    void SetUp() override {
        // Create test instances with predefined values for testing
        unicodeMapValid = std::make_unique<UnicodeMap>("UTF-8", true, 10);
        unicodeMapInvalid = std::make_unique<UnicodeMap>("ISO-8859-1", false, 10);
    }

    // Test instances
    std::unique_ptr<UnicodeMap> unicodeMapValid;
    std::unique_ptr<UnicodeMap> unicodeMapInvalid;
};

// Test for checking if the UnicodeMap is initialized correctly with unicodeOut = true
TEST_F(UnicodeMapTest, IsUnicode_True) {
    ASSERT_TRUE(unicodeMapValid->isUnicode());  // Should return true for valid Unicode map
}

// Test for checking if the UnicodeMap is initialized correctly with unicodeOut = false
TEST_F(UnicodeMapTest, IsUnicode_False) {
    ASSERT_FALSE(unicodeMapInvalid->isUnicode());  // Should return false for non-Unicode map
}

// Test for the constructor using valid parameters
TEST_F(UnicodeMapTest, Constructor_ValidParameters) {
    std::unique_ptr<UnicodeMap> testMap = std::make_unique<UnicodeMap>("UTF-8", true, 10);
    ASSERT_TRUE(testMap->isUnicode());  // Should return true
    ASSERT_EQ(testMap->getEncodingName(), "UTF-8");  // Check if encoding name is correct
}

// Test for the constructor using invalid parameters (with non-Unicode flag)
TEST_F(UnicodeMapTest, Constructor_InvalidParameters) {
    std::unique_ptr<UnicodeMap> testMap = std::make_unique<UnicodeMap>("ISO-8859-1", false, 10);
    ASSERT_FALSE(testMap->isUnicode());  // Should return false for non-Unicode map
    ASSERT_EQ(testMap->getEncodingName(), "ISO-8859-1");  // Check if encoding name is correct
}

// Test for the match function that checks the encoding name
TEST_F(UnicodeMapTest, Match_True) {
    ASSERT_TRUE(unicodeMapValid->match("UTF-8"));  // Should return true for a matching encoding
}

TEST_F(UnicodeMapTest, Match_False) {
    ASSERT_FALSE(unicodeMapValid->match("ISO-8859-1"));  // Should return false for a non-matching encoding
}

// Test for the parse static function with a valid encoding name
TEST_F(UnicodeMapTest, Parse_ValidEncodingName) {
    auto parsedMap = UnicodeMap::parse("UTF-8");
    ASSERT_TRUE(parsedMap->isUnicode());  // Should return true for valid encoding
}

// Test for the parse static function with an invalid encoding name
TEST_F(UnicodeMapTest, Parse_InvalidEncodingName) {
    auto parsedMap = UnicodeMap::parse("ISO-8859-1");
    ASSERT_FALSE(parsedMap->isUnicode());  // Should return false for invalid encoding
}

// Test for boundary condition: constructor with no ranges (0)
TEST_F(UnicodeMapTest, Constructor_ZeroRanges) {
    std::unique_ptr<UnicodeMap> testMap = std::make_unique<UnicodeMap>("UTF-8", true, 0);
    ASSERT_TRUE(testMap->isUnicode());  // Should return true for valid Unicode map
}

// Test for exceptional case: if `mapUnicode` is called with a null buffer (boundary case)
TEST_F(UnicodeMapTest, MapUnicode_NullBuffer) {
    char* nullBuffer = nullptr;
    int result = unicodeMapValid->mapUnicode('A', nullBuffer, 0);  // Should handle null buffer gracefully
    ASSERT_EQ(result, -1);  // Expecting -1 (error) since buffer is null
}

// Test for exceptional case: if `mapUnicode` is called with a buffer of size 0
TEST_F(UnicodeMapTest, MapUnicode_ZeroBufferSize) {
    char buffer[1];
    int result = unicodeMapValid->mapUnicode('A', buffer, 0);  // Should handle buffer of size 0
    ASSERT_EQ(result, -1);  // Expecting -1 (error) due to zero buffer size
}

// Test for exceptional case: if `mapUnicode` is called with an invalid Unicode value
TEST_F(UnicodeMapTest, MapUnicode_InvalidUnicode) {
    char buffer[10];
    int result = unicodeMapValid->mapUnicode(0x110000, buffer, sizeof(buffer));  // Invalid Unicode character
    ASSERT_EQ(result, -1);  // Expecting -1 (error) due to invalid Unicode value
}

// Test for move constructor (ensure proper transfer of ownership)
TEST_F(UnicodeMapTest, MoveConstructor) {
    UnicodeMap movedMap = std::move(*unicodeMapValid);  // Moving instance
    ASSERT_TRUE(movedMap.isUnicode());  // Should retain the correct unicodeOut value
    ASSERT_EQ(movedMap.getEncodingName(), "UTF-8");  // Encoding name should remain the same
}

// Test for swap function
TEST_F(UnicodeMapTest, Swap) {
    UnicodeMap swapMap1("UTF-8", true, 10);
    UnicodeMap swapMap2("ISO-8859-1", false, 10);
    
    swap(swapMap1, swapMap2);  // Swap maps
    
    ASSERT_FALSE(swapMap1.isUnicode());  // After swap, map 1 should now be non-Unicode
    ASSERT_TRUE(swapMap2.isUnicode());   // After swap, map 2 should now be Unicode
}

// Test for destructor
TEST_F(UnicodeMapTest, Destructor) {
    // Ensure that the destructor works without crashing
    {
        std::unique_ptr<UnicodeMap> tempMap = std::make_unique<UnicodeMap>("UTF-8", true, 10);
        ASSERT_NO_THROW({ tempMap.reset(); });  // Should not throw an exception
    }
}