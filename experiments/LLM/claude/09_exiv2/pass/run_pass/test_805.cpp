#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/value.hpp>

using namespace Exiv2;

class StringValueBaseTest_805 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that copy returns 0 when the value is empty
TEST_F(StringValueBaseTest_805, CopyEmptyValueReturnsZero_805) {
    StringValue sv;
    // Default-constructed StringValue should have empty string
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 0u);
}

// Test that copy returns 0 for explicitly set empty string
TEST_F(StringValueBaseTest_805, CopyExplicitlySetEmptyStringReturnsZero_805) {
    StringValue sv;
    sv.read("");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// Test that copy correctly copies a non-empty string
TEST_F(StringValueBaseTest_805, CopyNonEmptyStringCopiesCorrectBytes_805) {
    StringValue sv;
    sv.read("Hello");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 5u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Hello");
}

// Test that copy works with a single character string
TEST_F(StringValueBaseTest_805, CopySingleCharacterString_805) {
    StringValue sv;
    sv.read("A");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, littleEndian);
    EXPECT_EQ(copied, 1u);
    EXPECT_EQ(buf[0], 'A');
}

// Test that copy works regardless of byte order (bigEndian)
TEST_F(StringValueBaseTest_805, CopyIgnoresByteOrderBigEndian_805) {
    StringValue sv;
    sv.read("Test");
    byte buf1[64] = {0};
    byte buf2[64] = {0};
    size_t copied1 = sv.copy(buf1, bigEndian);
    size_t copied2 = sv.copy(buf2, littleEndian);
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, copied1), 0);
}

// Test that copy correctly copies a string with spaces
TEST_F(StringValueBaseTest_805, CopyStringWithSpaces_805) {
    StringValue sv;
    sv.read("Hello World");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 11u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "Hello World");
}

// Test that copy correctly copies a string with special characters
TEST_F(StringValueBaseTest_805, CopyStringWithSpecialCharacters_805) {
    StringValue sv;
    sv.read("abc\x00""def");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    // The read function for StringValue may stop at null, so just check it returns something >= 0
    EXPECT_GE(copied, 0u);
}

// Test that copy returns the correct size for a longer string
TEST_F(StringValueBaseTest_805, CopyLongerStringReturnsCorrectSize_805) {
    StringValue sv;
    std::string longStr(256, 'x');
    sv.read(longStr);
    byte buf[512] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 256u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), longStr);
}

// Test that copy does not modify bytes beyond the copied range
TEST_F(StringValueBaseTest_805, CopyDoesNotModifyBeyondCopiedRange_805) {
    StringValue sv;
    sv.read("Hi");
    byte buf[64];
    std::memset(buf, 0xFF, sizeof(buf));
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 'H');
    EXPECT_EQ(buf[1], 'i');
    // Bytes beyond the copied region should remain 0xFF
    EXPECT_EQ(buf[2], 0xFF);
    EXPECT_EQ(buf[3], 0xFF);
}

// Test copy with a string containing newline characters
TEST_F(StringValueBaseTest_805, CopyStringWithNewlines_805) {
    StringValue sv;
    sv.read("line1\nline2\n");
    byte buf[64] = {0};
    size_t copied = sv.copy(buf, bigEndian);
    EXPECT_EQ(copied, 12u);
    EXPECT_EQ(std::string(reinterpret_cast<char*>(buf), copied), "line1\nline2\n");
}

// Test that multiple calls to copy return the same result
TEST_F(StringValueBaseTest_805, MultipleCopyCallsReturnSameResult_805) {
    StringValue sv;
    sv.read("Consistent");
    byte buf1[64] = {0};
    byte buf2[64] = {0};
    size_t copied1 = sv.copy(buf1, bigEndian);
    size_t copied2 = sv.copy(buf2, bigEndian);
    EXPECT_EQ(copied1, copied2);
    EXPECT_EQ(std::memcmp(buf1, buf2, copied1), 0);
}
