#include <gtest/gtest.h>
#include <string_view>

// Function prototype from the provided code
inline bool isUtf8WithBom(std::string_view str);

// TEST: Verify that the function correctly identifies UTF-8 strings with BOM
TEST_F(UTFTest_1281, IdentifiesUtf8WithBomCorrectly_1281) {
    // Test case 1: String with a BOM at the start
    std::string_view validUtf8WithBom = "\xef\xbb\xbfHello, World!";
    EXPECT_TRUE(isUtf8WithBom(validUtf8WithBom)) << "Expected the string to be identified as UTF-8 with BOM.";
    
    // Test case 2: String without a BOM
    std::string_view validUtf8WithoutBom = "Hello, World!";
    EXPECT_FALSE(isUtf8WithBom(validUtf8WithoutBom)) << "Expected the string to not be identified as UTF-8 with BOM.";
    
    // Test case 3: Empty string
    std::string_view emptyStr = "";
    EXPECT_FALSE(isUtf8WithBom(emptyStr)) << "Expected the empty string to not be identified as UTF-8 with BOM.";

    // Test case 4: String with fewer than 3 characters (cannot have BOM)
    std::string_view shortStr = "\xef\xbb";
    EXPECT_FALSE(isUtf8WithBom(shortStr)) << "Expected the short string to not be identified as UTF-8 with BOM.";
}

// TEST: Verify boundary conditions
TEST_F(UTFTest_1281, HandlesSmallStrings_1281) {
    // Test case 5: String exactly 3 characters long
    std::string_view threeCharsStr = "\xef\xbb\xbf";
    EXPECT_TRUE(isUtf8WithBom(threeCharsStr)) << "Expected the string to be identified as UTF-8 with BOM.";
    
    // Test case 6: String exactly 4 characters long (still valid UTF-8 with BOM)
    std::string_view fourCharsStr = "\xef\xbb\xbfH";
    EXPECT_TRUE(isUtf8WithBom(fourCharsStr)) << "Expected the string to be identified as UTF-8 with BOM.";
}

// TEST: Verify exceptional or error cases (if observable through the interface)
TEST_F(UTFTest_1281, HandlesInvalidUtf8_1281) {
    // Test case 7: String with invalid BOM bytes
    std::string_view invalidBomStr = "\xef\xbb\xff";
    EXPECT_FALSE(isUtf8WithBom(invalidBomStr)) << "Expected the string with an invalid BOM to not be identified as UTF-8 with BOM.";
}