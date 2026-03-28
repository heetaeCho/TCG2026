// File: test_iptc_detectCharset_702.cpp

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>

#include <cstring>
#include <string>

namespace {

class IptcDataDetectCharsetTest_702 : public ::testing::Test {
protected:
  static std::string ToStdStringOrEmpty(const char* s) { return s ? std::string(s) : std::string(); }
};

TEST_F(IptcDataDetectCharsetTest_702, ReturnsUtf8WhenEnvelopeCharacterSetEscapeIsPresent_702) {
  Exiv2::IptcData data;

  data["Iptc.Envelope.CharacterSet"] = std::string("\033%G");  // ESC % G
  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "UTF-8");
}

TEST_F(IptcDataDetectCharsetTest_702, ReturnsAsciiWhenEmpty_702) {
  Exiv2::IptcData data;

  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "ASCII");
}

TEST_F(IptcDataDetectCharsetTest_702, ReturnsAsciiWhenAllValuesAreAsciiAndNoCharsetTag_702) {
  Exiv2::IptcData data;

  data["Iptc.Application2.Caption"] = std::string("Hello World");
  data["Iptc.Application2.ObjectName"] = std::string("Sample");
  data["Iptc.Application2.Keywords"] = std::string("alpha,beta,gamma");

  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "ASCII");
}

TEST_F(IptcDataDetectCharsetTest_702, ReturnsUtf8WhenContainsValidUtf8NonAsciiAndNoCharsetTag_702) {
  Exiv2::IptcData data;

  // "Café" in UTF-8: 'é' = 0xC3 0xA9
  const std::string cafe_utf8 = std::string("Caf") + std::string("\xC3\xA9", 2);
  data["Iptc.Application2.Caption"] = cafe_utf8;

  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "UTF-8");
}

TEST_F(IptcDataDetectCharsetTest_702, ReturnsNullptrWhenContainsInvalidUtf8Sequence_702) {
  Exiv2::IptcData data;

  // Start of a 2-byte UTF-8 sequence (0xC3) followed by an invalid continuation (0x41 'A').
  data["Iptc.Application2.Caption"] = std::string("\xC3\x41", 2);

  const char* charset = data.detectCharset();

  EXPECT_EQ(charset, nullptr);
}

TEST_F(IptcDataDetectCharsetTest_702, IgnoresNonMatchingCharsetTagAndFallsBackToContentDetection_702) {
  Exiv2::IptcData data;

  // Present but not the ESC % G sequence; should not force UTF-8 via the tag path.
  data["Iptc.Envelope.CharacterSet"] = std::string("NOT_UTF8_ESCAPE");

  // Still contains valid UTF-8 non-ASCII content, so detection should yield UTF-8.
  data["Iptc.Application2.Caption"] = std::string("x") + std::string("\xE2\x82\xAC", 3);  // "€"

  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "UTF-8");
}

TEST_F(IptcDataDetectCharsetTest_702, ReturnsAsciiWhenContainsOnlyHighBitClearEvenIfCharsetTagAbsent_702) {
  Exiv2::IptcData data;

  data["Iptc.Application2.City"] = std::string("Seoul");
  data["Iptc.Application2.CountryName"] = std::string("Korea");

  const char* charset = data.detectCharset();

  ASSERT_NE(charset, nullptr);
  EXPECT_STREQ(charset, "ASCII");
}

}  // namespace