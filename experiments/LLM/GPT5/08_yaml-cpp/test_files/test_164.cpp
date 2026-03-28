// TEST_ID: 164
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"
#include "yaml-cpp/exceptions.h"

// Forward declaration (function is implemented in src/scantag.cpp).
namespace YAML {
const std::string ScanTagSuffix(Stream& INPUT);
}

namespace {

class ScanTagSuffixTest_164 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& s, std::stringstream& backing) {
    backing.str(s);
    backing.clear();
    return YAML::Stream(backing);
  }
};

TEST_F(ScanTagSuffixTest_164, ThrowsParserExceptionOnEmptyInput_164) {
  std::stringstream ss;
  YAML::Stream in = MakeStream("", ss);

  try {
    (void)YAML::ScanTagSuffix(in);
    FAIL() << "Expected YAML::ParserException to be thrown";
  } catch (const YAML::ParserException& e) {
    // Message should be related to "tag handle with no suffix" (exact formatting may vary).
    EXPECT_NE(std::string(e.what()).find(YAML::ErrorMsg::TAG_WITH_NO_SUFFIX), std::string::npos);
  } catch (...) {
    FAIL() << "Expected YAML::ParserException";
  }
}

TEST_F(ScanTagSuffixTest_164, ThrowsParserExceptionWhenFirstCharIsNotSuffix_164) {
  // Use a clearly "non-suffix-like" starting character (whitespace).
  std::stringstream ss;
  YAML::Stream in = MakeStream(" \t\n", ss);

  try {
    (void)YAML::ScanTagSuffix(in);
    FAIL() << "Expected YAML::ParserException to be thrown";
  } catch (const YAML::ParserException& e) {
    EXPECT_NE(std::string(e.what()).find(YAML::ErrorMsg::TAG_WITH_NO_SUFFIX), std::string::npos);
  } catch (...) {
    FAIL() << "Expected YAML::ParserException";
  }
}

TEST_F(ScanTagSuffixTest_164, ReturnsSingleCharacterSuffix_164) {
  std::stringstream ss;
  YAML::Stream in = MakeStream("a", ss);

  const std::string out = YAML::ScanTagSuffix(in);
  EXPECT_EQ(out, "a");

  // After consuming the single character, stream should be at EOF.
  EXPECT_EQ(in.peek(), YAML::Stream::eof());
}

TEST_F(ScanTagSuffixTest_164, ReturnsSuffixAndStopsBeforeDelimiter_164) {
  std::stringstream ss;
  YAML::Stream in = MakeStream("abc def", ss);

  const std::string out = YAML::ScanTagSuffix(in);

  // Expect it to read the contiguous suffix and stop before the delimiter (space).
  EXPECT_EQ(out, "abc");
  EXPECT_EQ(in.peek(), ' ');
}

TEST_F(ScanTagSuffixTest_164, ConsumesOnlySuffixLeavingFollowingContent_164) {
  std::stringstream ss;
  YAML::Stream in = MakeStream("tag123\nnext", ss);

  const std::string out = YAML::ScanTagSuffix(in);
  EXPECT_EQ(out, "tag123");

  // Next character should be the newline delimiter.
  EXPECT_EQ(in.peek(), '\n');

  // Consume delimiter and verify following content still present.
  (void)in.get();
  EXPECT_EQ(in.peek(), 'n');
}

TEST_F(ScanTagSuffixTest_164, HandlesLongerSuffix_164) {
  // Boundary-ish: longer contiguous suffix.
  std::string long_suffix(1024, 'x');
  std::stringstream ss;
  YAML::Stream in = MakeStream(long_suffix + " ", ss);

  const std::string out = YAML::ScanTagSuffix(in);
  EXPECT_EQ(out.size(), long_suffix.size());
  EXPECT_EQ(out, long_suffix);
  EXPECT_EQ(in.peek(), ' ');
}

}  // namespace