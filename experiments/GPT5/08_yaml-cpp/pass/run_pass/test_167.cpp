// TEST_ID: 167
// File: ./TestProjects/yaml-cpp/test/exp_escape_test_167.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "TestProjects/yaml-cpp/src/stream.h"
#include "yaml-cpp/exceptions.h"  // ParserException, ErrorMsg

// Forward declaration (avoid depending on an "exp.h" header that may not exist in this snippet).
namespace YAML {
namespace Exp {
std::string Escape(Stream& in, int codeLength);
}  // namespace Exp
}  // namespace YAML

namespace {

using ::testing::HasSubstr;

static std::string Bytes(std::initializer_list<unsigned int> b) {
  std::string out;
  out.reserve(b.size());
  for (auto v : b) out.push_back(static_cast<char>(static_cast<unsigned char>(v)));
  return out;
}

class EscapeTest_167 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& s, std::istringstream& backing) {
    backing.clear();
    backing.str(s);
    return YAML::Stream(backing);
  }
};

TEST_F(EscapeTest_167, EscapeAscii_0041_ReturnsA_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("0041Z", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, "A");
  EXPECT_EQ(in.peek(), 'Z');  // consumed exactly 4 chars
}

TEST_F(EscapeTest_167, EscapeBoundary_007F_ReturnsSingleByte7F_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("007F.", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(static_cast<unsigned char>(out[0]), 0x7F);
  EXPECT_EQ(in.peek(), '.');
}

TEST_F(EscapeTest_167, EscapeBoundary_0080_ReturnsTwoByteUtf8_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("0080X", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xC2, 0x80}));
  EXPECT_EQ(in.peek(), 'X');
}

TEST_F(EscapeTest_167, EscapeTwoByte_00A9_ReturnsUtf8Copyright_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("00A9!", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xC2, 0xA9}));
  EXPECT_EQ(in.peek(), '!');
}

TEST_F(EscapeTest_167, EscapeBoundary_07FF_ReturnsTwoByteUtf8_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("07FF?", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xDF, 0xBF}));
  EXPECT_EQ(in.peek(), '?');
}

TEST_F(EscapeTest_167, EscapeBoundary_0800_ReturnsThreeByteUtf8_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("0800@", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xE0, 0xA0, 0x80}));
  EXPECT_EQ(in.peek(), '@');
}

TEST_F(EscapeTest_167, EscapeThreeByte_20AC_ReturnsUtf8EuroSign_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("20AC#", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xE2, 0x82, 0xAC}));
  EXPECT_EQ(in.peek(), '#');
}

TEST_F(EscapeTest_167, EscapeBoundary_FFFF_ReturnsThreeByteUtf8_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("FFFF$", iss);

  const std::string out = YAML::Exp::Escape(in, 4);

  EXPECT_EQ(out, Bytes({0xEF, 0xBF, 0xBF}));
  EXPECT_EQ(in.peek(), '$');
}

TEST_F(EscapeTest_167, EscapeBoundary_10000_ReturnsFourByteUtf8_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("10000%", iss);

  const std::string out = YAML::Exp::Escape(in, 5);

  EXPECT_EQ(out, Bytes({0xF0, 0x90, 0x80, 0x80}));
  EXPECT_EQ(in.peek(), '%');
}

TEST_F(EscapeTest_167, EscapeFourByte_1F600_ReturnsUtf8GrinningFace_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("1F600~", iss);

  const std::string out = YAML::Exp::Escape(in, 5);

  EXPECT_EQ(out, Bytes({0xF0, 0x9F, 0x98, 0x80}));
  EXPECT_EQ(in.peek(), '~');
}

TEST_F(EscapeTest_167, EscapeSurrogate_D800_ThrowsParserExceptionWithInvalidUnicodePrefix_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("D800", iss);

  try {
    (void)YAML::Exp::Escape(in, 4);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    // Observable behavior: throws ParserException and message includes INVALID_UNICODE prefix.
    EXPECT_THAT(std::string(e.what()), HasSubstr(YAML::ErrorMsg::INVALID_UNICODE));
  }
}

TEST_F(EscapeTest_167, EscapeSurrogate_DFFF_ThrowsParserException_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("DFFF", iss);

  EXPECT_THROW((void)YAML::Exp::Escape(in, 4), YAML::ParserException);
}

TEST_F(EscapeTest_167, EscapeAboveMax_110000_ThrowsParserException_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("110000", iss);

  try {
    (void)YAML::Exp::Escape(in, 6);
    FAIL() << "Expected YAML::ParserException";
  } catch (const YAML::ParserException& e) {
    EXPECT_THAT(std::string(e.what()), HasSubstr(YAML::ErrorMsg::INVALID_UNICODE));
    // Also check the numeric value appears (formatting is implementation-defined but should include "110000").
    EXPECT_THAT(std::string(e.what()), HasSubstr("110000"));
  }
}

TEST_F(EscapeTest_167, EscapeInvalidHex_ThrowsSomeException_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("ZZZZ", iss);

  // ParseHex is an external dependency; we only assert an error is observable.
  EXPECT_ANY_THROW((void)YAML::Exp::Escape(in, 4));
}

TEST_F(EscapeTest_167, EscapeZeroLength_ThrowsSomeException_167) {
  std::istringstream iss;
  YAML::Stream in = MakeStream("ABCD", iss);

  // Boundary: codeLength == 0. Observable behavior should be an error (parsing empty hex).
  EXPECT_ANY_THROW((void)YAML::Exp::Escape(in, 0));
}

}  // namespac