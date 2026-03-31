#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class HasUnicodeByteOrderMarkLETest_1279 : public ::testing::Test {
protected:
    // Unicode BOM LE is FF FE
    const std::string bom_le = std::string("\xFF\xFE", 2);
};

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsTrueForExactBOMLE_1279)
{
    std::string s("\xFF\xFE", 2);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsTrueForBOMLEFollowedByContent_1279)
{
    std::string s("\xFF\xFE" "Hello, World!", 15);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForEmptyString_1279)
{
    std::string s;
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForSingleByteFF_1279)
{
    std::string s("\xFF", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForSingleByteFE_1279)
{
    std::string s("\xFE", 1);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForReversedBOMBigEndian_1279)
{
    // BOM BE is FE FF, which is the reverse
    std::string s("\xFE\xFF", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForRandomContent_1279)
{
    std::string s("Hello, World!");
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForBOMLEInMiddle_1279)
{
    // BOM LE appears in the middle but not at the start
    std::string s("AB\xFF\xFE", 4);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsTrueForBOMLEFollowedByNullBytes_1279)
{
    std::string s("\xFF\xFE\x00\x00", 4);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForAllZeroBytes_1279)
{
    std::string s("\x00\x00", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForFFFollowedByNonFE_1279)
{
    std::string s("\xFF\xFD", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForNonFFFollowedByFE_1279)
{
    std::string s("\xFD\xFE", 2);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, WorksWithStringView_1279)
{
    const char data[] = "\xFF\xFE" "test";
    std::string_view sv(data, 6);
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(sv));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsTrueForBOMLEWithUTF16LEContent_1279)
{
    // Simulate a UTF-16LE encoded string starting with BOM
    std::string s("\xFF\xFE\x41\x00\x42\x00", 6); // BOM + "AB" in UTF-16LE
    EXPECT_TRUE(hasUnicodeByteOrderMarkLE(s));
}

TEST_F(HasUnicodeByteOrderMarkLETest_1279, ReturnsFalseForUTF8BOM_1279)
{
    // UTF-8 BOM is EF BB BF
    std::string s("\xEF\xBB\xBF", 3);
    EXPECT_FALSE(hasUnicodeByteOrderMarkLE(s));
}
