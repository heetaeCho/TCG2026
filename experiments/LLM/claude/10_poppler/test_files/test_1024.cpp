#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include "UTF.h"

class HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024 : public ::testing::Test {
protected:
};

// Normal operation: string starts with BOM and has even length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMPresentAndEvenLength_1024) {
    // BOM is "\xFE\xFF" (2 bytes), total length 4 (even)
    std::string s = "\xFE\xFF\x00\x41";
    std::string_view sv(s.data(), 4);
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Normal operation: string starts with BOM and length is exactly 2 (just the BOM)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMOnlyEvenLength_1024) {
    std::string s = "\xFE\xFF";
    std::string_view sv(s.data(), 2);
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// BOM present but odd length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMPresentButOddLength_1024) {
    std::string s = "\xFE\xFF\x00";
    std::string_view sv(s.data(), 3);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// No BOM, even length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, NoBOMEvenLength_1024) {
    std::string s = "ABCD";
    std::string_view sv(s);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// No BOM, odd length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, NoBOMOddLength_1024) {
    std::string s = "ABC";
    std::string_view sv(s);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Empty string
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, EmptyString_1024) {
    std::string_view sv("");
    // Length 0 is even, but doesn't start with BOM
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Single byte string (no BOM possible, odd length)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, SingleByte_1024) {
    std::string s = "\xFE";
    std::string_view sv(s.data(), 1);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// BOM with longer even content
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMWithLongerEvenContent_1024) {
    // BOM (2 bytes) + 4 more bytes = 6 bytes total (even)
    std::string s = "\xFE\xFF\x00\x48\x00\x69";
    std::string_view sv(s.data(), 6);
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// BOM with longer odd content
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMWithLongerOddContent_1024) {
    // BOM (2 bytes) + 3 more bytes = 5 bytes total (odd)
    std::string s = "\xFE\xFF\x00\x48\x00";
    std::string_view sv(s.data(), 5);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Reversed BOM (little-endian BOM \xFF\xFE should not match)
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, ReversedBOMNotMatching_1024) {
    std::string s = "\xFF\xFE\x00\x41";
    std::string_view sv(s.data(), 4);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// First byte matches BOM but second doesn't
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, PartialBOMFirstByteOnly_1024) {
    std::string s = "\xFE\x00\x00\x41";
    std::string_view sv(s.data(), 4);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// BOM appears in the middle but not at the start
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMInMiddleNotStart_1024) {
    std::string s = "\x00\x00\xFE\xFF";
    std::string_view sv(s.data(), 4);
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// String with embedded null characters, BOM present, even length
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, BOMWithEmbeddedNulls_1024) {
    std::string s("\xFE\xFF\x00\x00", 4);
    std::string_view sv(s.data(), 4);
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Large even-length string with BOM
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, LargeEvenLengthWithBOM_1024) {
    std::string s = "\xFE\xFF";
    // Add 998 more bytes to make total 1000 (even)
    s.append(998, 'A');
    std::string_view sv(s.data(), s.size());
    EXPECT_TRUE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}

// Large odd-length string with BOM
TEST_F(HasUnicodeByteOrderMarkAndLengthIsEvenTest_1024, LargeOddLengthWithBOM_1024) {
    std::string s = "\xFE\xFF";
    // Add 999 more bytes to make total 1001 (odd)
    s.append(999, 'A');
    std::string_view sv(s.data(), s.size());
    EXPECT_FALSE(hasUnicodeByteOrderMarkAndLengthIsEven(sv));
}
