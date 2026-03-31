#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class IsUtf8WithBomTest_1281 : public ::testing::Test {
protected:
};

// Normal operation: string with valid UTF-8 BOM followed by content
TEST_F(IsUtf8WithBomTest_1281, ValidBomWithContent_1281) {
    std::string str = "\xef\xbb\xbf" "Hello World";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Normal operation: string with valid UTF-8 BOM and exactly 4 bytes total
TEST_F(IsUtf8WithBomTest_1281, ValidBomWithOneExtraChar_1281) {
    std::string str = "\xef\xbb\xbf" "X";
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Normal operation: string without BOM
TEST_F(IsUtf8WithBomTest_1281, NoBomRegularAscii_1281) {
    std::string str = "Hello World";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: empty string
TEST_F(IsUtf8WithBomTest_1281, EmptyString_1281) {
    std::string str = "";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: string with exactly 1 byte
TEST_F(IsUtf8WithBomTest_1281, OneByteString_1281) {
    std::string str = "A";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: string with exactly 2 bytes
TEST_F(IsUtf8WithBomTest_1281, TwoByteString_1281) {
    std::string str = "AB";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: string with exactly 3 bytes (BOM only, size < 4)
TEST_F(IsUtf8WithBomTest_1281, ThreeBytesBomOnly_1281) {
    std::string str = "\xef\xbb\xbf";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: string with exactly 3 bytes that are not BOM
TEST_F(IsUtf8WithBomTest_1281, ThreeBytesNoBom_1281) {
    std::string str = "ABC";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: string with exactly 4 bytes, valid BOM
TEST_F(IsUtf8WithBomTest_1281, FourBytesWithBom_1281) {
    std::string str = "\xef\xbb\xbf" "A";
    ASSERT_EQ(str.size(), 4u);
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Boundary: string with exactly 4 bytes, no BOM
TEST_F(IsUtf8WithBomTest_1281, FourBytesNoBom_1281) {
    std::string str = "ABCD";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: partial BOM - first byte matches only
TEST_F(IsUtf8WithBomTest_1281, PartialBomFirstByteOnly_1281) {
    std::string str = "\xef" "BCD";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: partial BOM - first two bytes match
TEST_F(IsUtf8WithBomTest_1281, PartialBomFirstTwoBytes_1281) {
    std::string str = "\xef\xbb" "CD";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: BOM bytes in wrong order
TEST_F(IsUtf8WithBomTest_1281, BomBytesWrongOrder_1281) {
    std::string str = "\xbb\xbf\xef" "A";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: UTF-16 LE BOM instead of UTF-8 BOM
TEST_F(IsUtf8WithBomTest_1281, Utf16LeBom_1281) {
    std::string str = "\xff\xfe" "AB";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: UTF-16 BE BOM instead of UTF-8 BOM
TEST_F(IsUtf8WithBomTest_1281, Utf16BeBom_1281) {
    std::string str = "\xfe\xff" "AB";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Normal operation: BOM followed by null bytes (embedded nulls)
TEST_F(IsUtf8WithBomTest_1281, BomFollowedByNullBytes_1281) {
    std::string str("\xef\xbb\xbf\x00", 4);
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Boundary: string with all zero bytes, size >= 4
TEST_F(IsUtf8WithBomTest_1281, AllZeroBytes_1281) {
    std::string str("\x00\x00\x00\x00", 4);
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Normal: large string with BOM at beginning
TEST_F(IsUtf8WithBomTest_1281, LargeStringWithBom_1281) {
    std::string str = "\xef\xbb\xbf";
    str.append(10000, 'X');
    EXPECT_TRUE(isUtf8WithBom(str));
}

// Normal: large string without BOM
TEST_F(IsUtf8WithBomTest_1281, LargeStringWithoutBom_1281) {
    std::string str(10000, 'Y');
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Error case: BOM bytes not at beginning (offset in string)
TEST_F(IsUtf8WithBomTest_1281, BomNotAtBeginning_1281) {
    std::string str = "A\xef\xbb\xbf" "BCD";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: third BOM byte is wrong
TEST_F(IsUtf8WithBomTest_1281, ThirdBomByteWrong_1281) {
    std::string str = "\xef\xbb\xbc" "A";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Boundary: second BOM byte is wrong
TEST_F(IsUtf8WithBomTest_1281, SecondBomByteWrong_1281) {
    std::string str = "\xef\xba\xbf" "A";
    EXPECT_FALSE(isUtf8WithBom(str));
}

// Using string_view directly
TEST_F(IsUtf8WithBomTest_1281, StringViewDirectly_1281) {
    const char data[] = "\xef\xbb\xbf" "test";
    std::string_view sv(data, 7);
    EXPECT_TRUE(isUtf8WithBom(sv));
}

// String_view with size < 4
TEST_F(IsUtf8WithBomTest_1281, StringViewTooShort_1281) {
    const char data[] = "\xef\xbb\xbf";
    std::string_view sv(data, 3);
    EXPECT_FALSE(isUtf8WithBom(sv));
}
