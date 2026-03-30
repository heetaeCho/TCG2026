// File: poppler_named_dest_to_bytestring_test_2158.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
guint8 *poppler_named_dest_to_bytestring(const char *name, gsize *length);
}

namespace {

class PopplerNamedDestToBytestringTest_2158 : public ::testing::Test {
protected:
  static void ExpectBytesEq_2158(const guint8* actual, gsize actual_len,
                                const std::vector<guint8>& expected) {
    ASSERT_EQ(actual_len, expected.size());
    if (expected.empty()) {
      return;
    }
    ASSERT_NE(actual, nullptr);
    EXPECT_EQ(0, std::memcmp(actual, expected.data(), expected.size()));
  }
};

TEST_F(PopplerNamedDestToBytestringTest_2158, NullNameReturnsNull_2158) {
  gsize len = 123;
  guint8* out = poppler_named_dest_to_bytestring(nullptr, &len);
  EXPECT_EQ(out, nullptr);
  // Do not assert on len: g_return_val_if_fail may or may not modify it.
}

TEST_F(PopplerNamedDestToBytestringTest_2158, NullLengthReturnsNull_2158) {
  guint8* out = poppler_named_dest_to_bytestring("ABC", nullptr);
  EXPECT_EQ(out, nullptr);
}

TEST_F(PopplerNamedDestToBytestringTest_2158, NoEscapesCopiesBytesAndLength_2158) {
  gsize len = 0;
  const char* name = "SimpleName123";
  guint8* out = poppler_named_dest_to_bytestring(name, &len);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(len, static_cast<gsize>(std::strlen(name)));

  std::vector<guint8> expected(reinterpret_cast<const guint8*>(name),
                               reinterpret_cast<const guint8*>(name) + std::strlen(name));
  ExpectBytesEq_2158(out, len, expected);

  g_free(out);
}

TEST_F(PopplerNamedDestToBytestringTest_2158, BackslashZeroProducesEmbeddedNullAndShorterLength_2158) {
  gsize len = 0;
  // Bytes: 'A' '\' '0' 'B'
  const char* name = "A\\0B";
  guint8* out = poppler_named_dest_to_bytestring(name, &len);
  ASSERT_NE(out, nullptr);

  // Expected bytes: 'A' '\0' 'B' (length 3)
  std::vector<guint8> expected = {static_cast<guint8>('A'),
                                  static_cast<guint8>('\0'),
                                  static_cast<guint8>('B')};
  ExpectBytesEq_2158(out, len, expected);

  g_free(out);
}

TEST_F(PopplerNamedDestToBytestringTest_2158, DoubleBackslashBecomesSingleBackslashAndShorterLength_2158) {
  gsize len = 0;
  // C literal "A\\\\B" => bytes: 'A' '\' '\' 'B'
  const char* name = "A\\\\B";
  guint8* out = poppler_named_dest_to_bytestring(name, &len);
  ASSERT_NE(out, nullptr);

  // Expected bytes: 'A' '\' 'B' (length 3)
  std::vector<guint8> expected = {static_cast<guint8>('A'),
                                  static_cast<guint8>('\\'),
                                  static_cast<guint8>('B')};
  ExpectBytesEq_2158(out, len, expected);

  g_free(out);
}

TEST_F(PopplerNamedDestToBytestringTest_2158, InvalidEscapeReturnsNullAndZerosLength_2158) {
  gsize len = 999;
  const char* name = "A\\xB"; // '\' followed by 'x' is invalid per interface behavior
  guint8* out = poppler_named_dest_to_bytestring(name, &len);
  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(len, static_cast<gsize>(0));
}

TEST_F(PopplerNamedDestToBytestringTest_2158, TrailingBackslashReturnsNullAndZerosLength_2158) {
  gsize len = 999;
  const char* name = "A\\"; // '\' at end => invalid
  guint8* out = poppler_named_dest_to_bytestring(name, &len);
  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(len, static_cast<gsize>(0));
}

TEST_F(PopplerNamedDestToBytestringTest_2158, EmptyStringProducesZeroLength_2158) {
  gsize len = 123;
  const char* name = "";
  guint8* out = poppler_named_dest_to_bytestring(name, &len);

  // Only observable contract we rely on: length becomes 0 on successful parse of empty input.
  EXPECT_EQ(len, static_cast<gsize>(0));

  // g_malloc(0) may return nullptr or a unique pointer depending on allocator; both are acceptable.
  if (out) {
    g_free(out);
  }
}

} // namespace