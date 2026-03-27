// File: poppler_named_dest_from_bytestring_test_2157.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>
#include <string>

// Function under test (implemented in poppler-document.cc)
extern "C" char *poppler_named_dest_from_bytestring(const guint8 *data, gsize length);

class PopplerNamedDestFromByteStringTest_2157 : public ::testing::Test {
protected:
  static std::string StrFromBytes(const char *s) { return std::string(s ? s : ""); }
};

TEST_F(PopplerNamedDestFromByteStringTest_2157, NullDataAndZeroLengthReturnsNull_2157) {
  char *out = poppler_named_dest_from_bytestring(nullptr, 0);
  EXPECT_EQ(out, nullptr);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, NonNullDataAndZeroLengthReturnsEmptyString_2157) {
  // Any non-null pointer should satisfy the precondition when length==0.
  const guint8 dummy = 0xAB;
  char *out = poppler_named_dest_from_bytestring(&dummy, 0);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, CopiesPlainBytesWithoutEscapes_2157) {
  const guint8 data[] = {'A', 'B', 'C', '1', '2', '3'};
  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "ABC123");
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, EscapesEmbeddedNullAsBackslashZero_2157) {
  const guint8 data[] = {'a', 0x00, 'b'};
  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "a\\0b"); // backslash + zero
  EXPECT_EQ(std::strlen(out), 4u);
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, EscapesBackslashAsDoubleBackslash_2157) {
  const guint8 data[] = {'x', '\\', 'y'};
  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "x\\\\y"); // two backslashes in the resulting C string
  EXPECT_EQ(std::strlen(out), 4u);
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, EscapesMixedNullAndBackslashInOrder_2157) {
  const guint8 data[] = {'\\', 0x00, 'A', '\\', 'B', 0x00};
  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  // Expected mapping:
  // '\'  -> "\\"
  // '\0' -> "\0" (as two chars: backslash + '0')
  // 'A'  -> 'A'
  // '\'  -> "\\"
  // 'B'  -> 'B'
  // '\0' -> "\0"
  EXPECT_STREQ(out, "\\\\\\0A\\\\B\\0");
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, OutputIsAlwaysZeroTerminatedAndHasNoEmbeddedNullsAfterEscaping_2157) {
  const guint8 data[] = {0x00, 0x00, 'Z'};
  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  // Two null bytes become four printable chars, plus 'Z'
  EXPECT_STREQ(out, "\\0\\0Z");
  // Ensure the reported C-string length matches expectation (no embedded '\0')
  EXPECT_EQ(std::strlen(out), 5u);
  g_free(out);
}

TEST_F(PopplerNamedDestFromByteStringTest_2157, DoesNotModifyInputBuffer_2157) {
  guint8 data[] = {'a', 0x00, '\\', 'b'};
  const guint8 before[] = {'a', 0x00, '\\', 'b'};

  char *out = poppler_named_dest_from_bytestring(data, sizeof(data));

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(0, std::memcmp(data, before, sizeof(data)));
  EXPECT_STREQ(out, "a\\0\\\\b");
  g_free(out);
}