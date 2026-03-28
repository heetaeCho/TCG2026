// File: parse_unsigned_char_test_271.cc
#include <gtest/gtest.h>

// Forward declare the specialized function under test.
namespace re2 { namespace re2_internal {
  bool Parse(const char* str, size_t n, unsigned char* dest);
}}

// Test suite name includes TEST_ID as requested.
class ParseUnsignedCharTest_271 : public ::testing::Test {};

TEST_F(ParseUnsignedCharTest_271, ReturnsTrueAndCopiesByte_WhenNIsOne_271) {
  const char input[] = "Z"; // 'Z' = 0x5A
  unsigned char out = 0x00;

  bool ok = re2::re2_internal::Parse(input, 1, &out);

  ASSERT_TRUE(ok);
  EXPECT_EQ(static_cast<unsigned char>('Z'), out);
}

TEST_F(ParseUnsignedCharTest_271, HandlesNullByteInput_WhenNIsOne_271) {
  const char input[] = "\0"; // first byte is 0x00
  unsigned char out = 0xAB; // sentinel

  bool ok = re2::re2_internal::Parse(input, 1, &out);

  ASSERT_TRUE(ok);
  EXPECT_EQ(static_cast<unsigned char>(0x00), out);
}

TEST_F(ParseUnsignedCharTest_271, CopiesHighBitByteFF_WhenNIsOne_271) {
  const char input[] = "\xFF"; // 0xFF; signedness of char is implementation-defined
  unsigned char out = 0x00;

  bool ok = re2::re2_internal::Parse(input, 1, &out);

  ASSERT_TRUE(ok);
  EXPECT_EQ(static_cast<unsigned char>(0xFF), out);
}

TEST_F(ParseUnsignedCharTest_271, ReturnsTrueAndDoesNotWrite_WhenDestIsNullAndNIsOne_271) {
  const char input[] = "A";

  // Should succeed without writing when dest == nullptr.
  bool ok = re2::re2_internal::Parse(input, 1, nullptr);

  ASSERT_TRUE(ok);
  // No crash and return value is the only observable outcome here.
}

TEST_F(ParseUnsignedCharTest_271, ReturnsFalse_WhenNIsZero_271) {
  const char input[] = "B"; // any non-empty buffer is fine; n will be 0
  unsigned char out = 0xEE; // sentinel to detect unintended writes

  bool ok = re2::re2_internal::Parse(input, 0, &out);

  ASSERT_FALSE(ok);
  // Since function indicates failure, verify no observable modification.
  EXPECT_EQ(static_cast<unsigned char>(0xEE), out);
}

TEST_F(ParseUnsignedCharTest_271, ReturnsFalse_WhenNGreaterThanOne_271) {
  const char input[] = "CD";
  unsigned char out = 0xCC; // sentinel

  bool ok = re2::re2_internal::Parse(input, 2, &out);

  ASSERT_FALSE(ok);
  EXPECT_EQ(static_cast<unsigned char>(0xCC), out);
}

TEST_F(ParseUnsignedCharTest_271, ReturnsFalse_WhenNGreaterThanOneAndDestIsNull_271) {
  const char input[] = "EF";

  bool ok = re2::re2_internal::Parse(input, 2, nullptr);

  ASSERT_FALSE(ok);
  // No further observable effect to assert; absence of crash plus return value is sufficient.
}
