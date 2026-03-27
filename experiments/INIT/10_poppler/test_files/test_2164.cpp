// poppler-document_goo_string_from_utf8_test_2164.cc
#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

// Include the implementation file to access the internal (static) helper.
// This keeps the function black-box while allowing direct invocation.
#include "TestProjects/poppler/glib/poppler-document.cc"

namespace {

static std::vector<uint8_t> ToBytes(const std::string &s) {
  return std::vector<uint8_t>(s.begin(), s.end());
}

static void ExpectBeginsWithUtf16BeBom(const std::string &bytes) {
  ASSERT_GE(bytes.size(), 2u);
  EXPECT_EQ(static_cast<uint8_t>(bytes[0]), 0xFE);
  EXPECT_EQ(static_cast<uint8_t>(bytes[1]), 0xFF);
}

}  // namespace

class PopplerGooStringFromUtf8Test_2164 : public ::testing::Test {};

TEST_F(PopplerGooStringFromUtf8Test_2164, NullInputReturnsNull_2164) {
  auto gs = _poppler_goo_string_from_utf8(nullptr);
  EXPECT_EQ(gs, nullptr);
}

TEST_F(PopplerGooStringFromUtf8Test_2164, ValidAsciiPrependsBomAndEncodesUtf16Be_2164) {
  // "A" in UTF-16BE is 00 41; expected output should be BOM (FE FF) + 00 41.
  auto gs = _poppler_goo_string_from_utf8("A");
  ASSERT_NE(gs, nullptr);

  const std::string out = gs->toStr();
  ExpectBeginsWithUtf16BeBom(out);

  // Length should be even for UTF-16BE bytes; and at least BOM + one code unit.
  EXPECT_EQ(out.size() % 2u, 0u);
  ASSERT_GE(out.size(), 4u);

  EXPECT_EQ(static_cast<uint8_t>(out[2]), 0x00);
  EXPECT_EQ(static_cast<uint8_t>(out[3]), 0x41);
}

TEST_F(PopplerGooStringFromUtf8Test_2164, EmptyStringResultsInOnlyBom_2164) {
  auto gs = _poppler_goo_string_from_utf8("");
  ASSERT_NE(gs, nullptr);

  const std::string out = gs->toStr();
  // For empty input, observable behavior should be a valid UTF-16BE string with BOM only.
  ASSERT_EQ(out.size(), 2u);
  ExpectBeginsWithUtf16BeBom(out);
}

TEST_F(PopplerGooStringFromUtf8Test_2164, Utf8WithLeadingBomDoesNotDuplicateBom_2164) {
  // UTF-8 BOM (EF BB BF) followed by 'A'.
  const char kUtf8BomPlusA[] = "\xEF\xBB\xBF"
                               "A";
  auto gs = _poppler_goo_string_from_utf8(kUtf8BomPlusA);
  ASSERT_NE(gs, nullptr);

  const std::string out = gs->toStr();
  ExpectBeginsWithUtf16BeBom(out);

  // Ensure we don't end up with two BOMs at the start: FE FF FE FF ...
  ASSERT_GE(out.size(), 2u);
  if (out.size() >= 4u) {
    const bool hasSecondBom =
        (static_cast<uint8_t>(out[2]) == 0xFE) && (static_cast<uint8_t>(out[3]) == 0xFF);
    EXPECT_FALSE(hasSecondBom);
  }
}

TEST_F(PopplerGooStringFromUtf8Test_2164, InvalidUtf8ReturnsNull_2164) {
  // Invalid UTF-8 sequence: 0xC3 must be followed by a continuation byte; 0x28 is '('.
  const char kInvalidUtf8[] = "\xC3\x28";
  auto gs = _poppler_goo_string_from_utf8(kInvalidUtf8);
  EXPECT_EQ(gs, nullptr);
}

TEST_F(PopplerGooStringFromUtf8Test_2164, NonAsciiCharacterEncodesAndHasBom_2164) {
  // "가" (U+AC00) in UTF-8: EA B0 80
  const char kHangulGa[] = "\xEA\xB0\x80";
  auto gs = _poppler_goo_string_from_utf8(kHangulGa);
  ASSERT_NE(gs, nullptr);

  const std::string out = gs->toStr();
  ExpectBeginsWithUtf16BeBom(out);

  // UTF-16BE for U+AC00 is AC 00; with BOM: FE FF AC 00
  ASSERT_GE(out.size(), 4u);
  EXPECT_EQ(static_cast<uint8_t>(out[2]), 0xAC);
  EXPECT_EQ(static_cast<uint8_t>(out[3]), 0x00);
  EXPECT_EQ(out.size() % 2u, 0u);
}