// File: poppler-goo-string-to-utf8-test_2163.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>
#include <vector>

#include "goo/GooString.h"

// Black-box entry under test (implemented in poppler-document.cc)
extern "C" char *_poppler_goo_string_to_utf8(const GooString *s);

namespace {

class PopplerGooStringToUtf8Test_2163 : public ::testing::Test {
protected:
  static GooString MakeGooStringFromBytes(const std::vector<unsigned char> &bytes) {
    const char *ptr = reinterpret_cast<const char *>(bytes.data());
    return GooString(ptr, bytes.size());
  }

  static void ExpectValidUtf8(const char *s) {
    ASSERT_NE(s, nullptr);
    EXPECT_TRUE(g_utf8_validate(s, -1, nullptr));
  }
};

TEST_F(PopplerGooStringToUtf8Test_2163, NullInputReturnsNull_2163) {
  EXPECT_EQ(_poppler_goo_string_to_utf8(nullptr), nullptr);
}

TEST_F(PopplerGooStringToUtf8Test_2163, EmptyStringReturnsEmptyUtf8_2163) {
  GooString gs("", 0);
  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
  ExpectValidUtf8(out);

  g_free(out);
}

TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BeBomConvertsSimpleAscii_2163) {
  // UTF-16BE BOM: FE FF, then 'H' (00 48), 'i' (00 69)
  const std::vector<unsigned char> bytes = {0xFE, 0xFF, 0x00, 0x48, 0x00, 0x69};
  GooString gs = MakeGooStringFromBytes(bytes);

  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "Hi");
  ExpectValidUtf8(out);

  g_free(out);
}

TEST_F(PopplerGooStringToUtf8Test_2163, Utf16LeBomConvertsSimpleAscii_2163) {
  // UTF-16LE BOM: FF FE, then 'H' (48 00), 'i' (69 00)
  const std::vector<unsigned char> bytes = {0xFF, 0xFE, 0x48, 0x00, 0x69, 0x00};
  GooString gs = MakeGooStringFromBytes(bytes);

  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "Hi");
  ExpectValidUtf8(out);

  g_free(out);
}

TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BeBomOnlyProducesEmptyOrNull_2163) {
  // BOM only, no payload.
  const std::vector<unsigned char> bytes = {0xFE, 0xFF};
  GooString gs = MakeGooStringFromBytes(bytes);

  char *out = _poppler_goo_string_to_utf8(&gs);

  // Depending on GLib conversion behavior/config, this may return "" or nullptr.
  if (out) {
    EXPECT_STREQ(out, "");
    ExpectValidUtf8(out);
    g_free(out);
  } else {
    SUCCEED();
  }
}

TEST_F(PopplerGooStringToUtf8Test_2163, Utf16BeInvalidOddLengthReturnsNull_2163) {
  // BOM + 1 byte payload (odd length) should be an invalid UTF-16 sequence for conversion.
  const std::vector<unsigned char> bytes = {0xFE, 0xFF, 0x00};
  GooString gs = MakeGooStringFromBytes(bytes);

  char *out = _poppler_goo_string_to_utf8(&gs);
  EXPECT_EQ(out, nullptr);
}

TEST_F(PopplerGooStringToUtf8Test_2163, NoBomAsciiRoundTrips_2163) {
  GooString gs("Poppler");
  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "Poppler");
  ExpectValidUtf8(out);

  g_free(out);
}

TEST_F(PopplerGooStringToUtf8Test_2163, NoBomHighBitStillProducesValidUtf8_2163) {
  // Include a byte >= 0x80; mapping is implementation-defined via pdfDocEncoding,
  // but output should still be valid UTF-8 (or at least non-crashing / non-null).
  const std::vector<unsigned char> bytes = {'A', 0x80, 'B'};
  GooString gs = MakeGooStringFromBytes(bytes);

  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  ExpectValidUtf8(out);

  g_free(out);
}

TEST_F(PopplerGooStringToUtf8Test_2163, NoBomLargeAsciiInputConverts_2163) {
  std::string large(4096, 'A');
  GooString gs(large.c_str(), large.size());

  char *out = _poppler_goo_string_to_utf8(&gs);

  ASSERT_NE(out, nullptr);
  // For pure ASCII, a stable observable expectation is identical text.
  EXPECT_EQ(std::string(out), large);
  ExpectValidUtf8(out);

  g_free(out);
}

} // namespace