#include <gtest/gtest.h>
#include <string_view>
#include "UTF.h"

// Test normal case: string that starts with Unicode BOM LE (\xFF\xFE)
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsTrueForStringStartingWithBOMLE_1023)
{
    std::string_view s("\xFF\xFE" "hello", 7);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

// Test normal case: string that does NOT start with Unicode BOM LE
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForStringWithoutBOMLE_1023)
{
    std::string_view s("hello world");
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test boundary: empty string
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForEmptyString_1023)
{
    std::string_view s("");
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test boundary: string with only one byte (too short to contain BOM)
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForSingleByteString_1023)
{
    std::string_view s("\xFF", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test boundary: string that is exactly the BOM LE (2 bytes)
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsTrueForExactBOMLE_1023)
{
    std::string_view s("\xFF\xFE", 2);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

// Test: BOM BE (\xFE\xFF) should return false — it's the wrong byte order
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForBOMBE_1023)
{
    std::string_view s("\xFE\xFF" "data", 6);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test: BOM LE appears in the middle but not at start
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseWhenBOMLENotAtStart_1023)
{
    std::string_view s("ab\xFF\xFE" "cd", 6);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test: string starting with \xFF but second byte is not \xFE
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseWhenFirstByteMatchesButSecondDoesNot_1023)
{
    std::string_view s("\xFF\x00", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test: string starting with \xFE but not \xFF first
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseWhenOnlySecondBOMBytePresent_1023)
{
    std::string_view s("\xFE\xFE", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test: BOM LE followed by null bytes (simulating a UTF-16LE encoded string)
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsTrueForBOMLEFollowedByNullBytes_1023)
{
    std::string_view s("\xFF\xFE\x00\x00", 4);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

// Test: string with embedded null after BOM LE
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsTrueForBOMLEWithEmbeddedNulls_1023)
{
    std::string s("\xFF\xFE\x41\x00\x42\x00", 6);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(std::string_view(s.data(), s.size())));
}

// Test: all 0xFF bytes (first two are \xFF\xFF, not BOM LE)
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForAllFFBytes_1023)
{
    std::string_view s("\xFF\xFF\xFF", 3);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

// Test: all 0xFE bytes
TEST(HasUnicodeByteOrderMarkLETest_1023, ReturnsFalseForAllFEBytes_1023)
{
    std::string_view s("\xFE\xFE\xFE", 3);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}
