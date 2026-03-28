#include <gtest/gtest.h>
#include "exiv2/types.hpp"

// We need to access the internal function. Since it's in an anonymous-like internal namespace,
// we declare it here to link against.
namespace Exiv2 {
namespace Internal {
static bool equalsQTimeTag(Exiv2::DataBuf& buf, const char str[5]) {
  return std::equal(buf.begin(), buf.begin() + 4, str, [](auto b, auto s) {
    return std::tolower(b) == std::tolower(s);
  });
}
}  // namespace Internal
}  // namespace Exiv2

class EqualsQTimeTagTest_653 : public ::testing::Test {
 protected:
  // Helper to create a DataBuf from a 4-character string
  Exiv2::DataBuf makeBuf(const char* data, size_t len) {
    return Exiv2::DataBuf(reinterpret_cast<const Exiv2::byte*>(data), len);
  }
};

// Test exact match with lowercase
TEST_F(EqualsQTimeTagTest_653, ExactMatchLowercase_653) {
  Exiv2::DataBuf buf = makeBuf("moov", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

// Test exact match with uppercase
TEST_F(EqualsQTimeTagTest_653, ExactMatchUppercase_653) {
  Exiv2::DataBuf buf = makeBuf("MOOV", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "MOOV"));
}

// Test case-insensitive match: buf uppercase, str lowercase
TEST_F(EqualsQTimeTagTest_653, CaseInsensitiveBufUpperStrLower_653) {
  Exiv2::DataBuf buf = makeBuf("MOOV", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

// Test case-insensitive match: buf lowercase, str uppercase
TEST_F(EqualsQTimeTagTest_653, CaseInsensitiveBufLowerStrUpper_653) {
  Exiv2::DataBuf buf = makeBuf("moov", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "MOOV"));
}

// Test case-insensitive match: mixed case
TEST_F(EqualsQTimeTagTest_653, CaseInsensitiveMixedCase_653) {
  Exiv2::DataBuf buf = makeBuf("MoOv", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "mOoV"));
}

// Test mismatch: completely different strings
TEST_F(EqualsQTimeTagTest_653, MismatchDifferentStrings_653) {
  Exiv2::DataBuf buf = makeBuf("moov", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

// Test mismatch: one character different
TEST_F(EqualsQTimeTagTest_653, MismatchOneCharDiff_653) {
  Exiv2::DataBuf buf = makeBuf("moov", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "moox"));
}

// Test mismatch: first character different
TEST_F(EqualsQTimeTagTest_653, MismatchFirstCharDiff_653) {
  Exiv2::DataBuf buf = makeBuf("moov", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "xoov"));
}

// Test with "ftyp" tag
TEST_F(EqualsQTimeTagTest_653, FtypTag_653) {
  Exiv2::DataBuf buf = makeBuf("ftyp", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

// Test with "FTYP" in buf and "ftyp" as str
TEST_F(EqualsQTimeTagTest_653, FtypCaseInsensitive_653) {
  Exiv2::DataBuf buf = makeBuf("FTYP", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "ftyp"));
}

// Test with numeric/special characters (case insensitivity doesn't apply to digits)
TEST_F(EqualsQTimeTagTest_653, NumericCharacters_653) {
  Exiv2::DataBuf buf = makeBuf("mp41", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "mp41"));
}

// Test with numeric characters mismatch
TEST_F(EqualsQTimeTagTest_653, NumericCharactersMismatch_653) {
  Exiv2::DataBuf buf = makeBuf("mp41", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "mp42"));
}

// Test buffer larger than 4 bytes — only first 4 should be compared
TEST_F(EqualsQTimeTagTest_653, BufferLargerThan4Bytes_653) {
  Exiv2::DataBuf buf = makeBuf("moovextra", 9);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

// Test buffer larger than 4 bytes with different trailing data
TEST_F(EqualsQTimeTagTest_653, BufferLargerDifferentTrailing_653) {
  Exiv2::DataBuf buf = makeBuf("moovXXXX", 8);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

// Test with all same characters
TEST_F(EqualsQTimeTagTest_653, AllSameChars_653) {
  Exiv2::DataBuf buf = makeBuf("aaaa", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "AAAA"));
}

// Test with null bytes in data (non-alphabetic)
TEST_F(EqualsQTimeTagTest_653, NullBytesMatch_653) {
  const char data[] = {'\0', '\0', '\0', '\0'};
  Exiv2::DataBuf buf = makeBuf(data, 4);
  const char str[5] = {'\0', '\0', '\0', '\0', '\0'};
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, str));
}

// Test with space characters
TEST_F(EqualsQTimeTagTest_653, SpaceCharacters_653) {
  Exiv2::DataBuf buf = makeBuf("    ", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "    "));
}

// Test "trak" tag
TEST_F(EqualsQTimeTagTest_653, TrakTag_653) {
  Exiv2::DataBuf buf = makeBuf("trak", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "TRAK"));
}

// Test "mdat" tag
TEST_F(EqualsQTimeTagTest_653, MdatTag_653) {
  Exiv2::DataBuf buf = makeBuf("MDAT", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "mdat"));
}

// Test partial match should fail
TEST_F(EqualsQTimeTagTest_653, PartialMatchFails_653) {
  Exiv2::DataBuf buf = makeBuf("moox", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "moov"));
}

// Test with mixed alphanumeric
TEST_F(EqualsQTimeTagTest_653, MixedAlphanumericMatch_653) {
  Exiv2::DataBuf buf = makeBuf("H264", 4);
  EXPECT_TRUE(Exiv2::Internal::equalsQTimeTag(buf, "h264"));
}

// Test with mixed alphanumeric mismatch
TEST_F(EqualsQTimeTagTest_653, MixedAlphanumericMismatch_653) {
  Exiv2::DataBuf buf = makeBuf("H264", 4);
  EXPECT_FALSE(Exiv2::Internal::equalsQTimeTag(buf, "h265"));
}
