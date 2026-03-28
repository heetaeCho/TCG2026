#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
namespace YAML {
bool IsNullString(const char* str, std::size_t size);
}

// Normal operation tests

TEST(IsNullStringTest_589, EmptyStringReturnsTrue_589) {
    EXPECT_TRUE(YAML::IsNullString("", 0));
}

TEST(IsNullStringTest_589, TildeReturnsTrue_589) {
    const char* str = "~";
    EXPECT_TRUE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, LowercaseNullReturnsTrue_589) {
    const char* str = "null";
    EXPECT_TRUE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, CapitalizedNullReturnsTrue_589) {
    const char* str = "Null";
    EXPECT_TRUE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, UppercaseNULLReturnsTrue_589) {
    const char* str = "NULL";
    EXPECT_TRUE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, SizeZeroWithNonEmptyPointerReturnsTrue_589) {
    const char* str = "hello";
    EXPECT_TRUE(YAML::IsNullString(str, 0));
}

// Negative / non-null string tests

TEST(IsNullStringTest_589, RegularStringReturnsFalse_589) {
    const char* str = "hello";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, MixedCaseNuLlReturnsFalse_589) {
    const char* str = "nULL";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, MixedCaseNuLLReturnsFalse_589) {
    const char* str = "NuLL";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, MixedCaseNulLReturnsFalse_589) {
    const char* str = "nulL";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, MixedCaseNULlReturnsFalse_589) {
    const char* str = "NULl";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, SingleCharNonTildeReturnsFalse_589) {
    const char* str = "n";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, SingleCharNReturnsFalse_589) {
    const char* str = "N";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

// Boundary conditions - partial matches

TEST(IsNullStringTest_589, NullWithExtraSizeReturnsFalse_589) {
    const char* str = "null ";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, NullPrefixReturnsFalse_589) {
    const char* str = "nullx";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, TildeWithExtraCharsReturnsFalse_589) {
    const char* str = "~x";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, PartialNullSizeTruncatedReturnsFalse_589) {
    const char* str = "null";
    // Only pass size 3 -> "nul"
    EXPECT_FALSE(YAML::IsNullString(str, 3));
}

TEST(IsNullStringTest_589, NULLWithPartialSizeReturnsFalse_589) {
    const char* str = "NULL";
    // Only pass size 3 -> "NUL"
    EXPECT_FALSE(YAML::IsNullString(str, 3));
}

TEST(IsNullStringTest_589, WhitespaceOnlyReturnsFalse_589) {
    const char* str = " ";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, SpacePrefixedNullReturnsFalse_589) {
    const char* str = " null";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, NullWithTrailingSpaceReturnsFalse_589) {
    const char* str = "null ";
    EXPECT_FALSE(YAML::IsNullString(str, 5));
}

TEST(IsNullStringTest_589, TrueStringReturnsFalse_589) {
    const char* str = "true";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, FalseStringReturnsFalse_589) {
    const char* str = "false";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, NumberStringReturnsFalse_589) {
    const char* str = "0";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, NilStringReturnsFalse_589) {
    const char* str = "nil";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

TEST(IsNullStringTest_589, NoneStringReturnsFalse_589) {
    const char* str = "None";
    EXPECT_FALSE(YAML::IsNullString(str, std::strlen(str)));
}

// Edge case: exact tilde
TEST(IsNullStringTest_589, ExactTildeSizeOneReturnsTrue_589) {
    const char str[] = "~";
    EXPECT_TRUE(YAML::IsNullString(str, 1));
}

// Edge case: embedded null character
TEST(IsNullStringTest_589, NullCharInStringReturnsFalse_589) {
    const char str[] = "nu\0l";
    EXPECT_FALSE(YAML::IsNullString(str, 4));
}
